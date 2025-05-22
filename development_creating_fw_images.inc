.. _creating_of_custom_firmware_images:

Creating Customized Firmware Images with Yocto
==============================================

As already mentioned in the :ref:`firmware.rst` chapter, chargebyte's firmware images are built using the Yocto
Project build system. This chapter describes how to set up the Yocto build environment for chargebyte's
firmware images and how to create a customized firmware image by adding a new EVerest module based on
the chargebyte Yocto layer.

Setting up the Yocto Build Environment

This section describes how to set up the Yocto build environment for chargebyte's firmware images and
how to create a customized firmware image by adding a new EVerest module based on the chargebyte
Yocto layer. The Yocto build environment is based on the chargebyte BSP (Board Support Package),
and please refer to our Board Support Package documentation in our public GitHub
repository at: https://github.com/chargebyte/chargebyte-bsp for detailed instructions.

#. Install the `required packages <https://docs.yoctoproject.org/ref-manual/system-requirements.html#required-packages-for-the-build-host>`_
   for Yocto on a Linux machine / virtual machine. (**Note**: We normally set up the Yocto build environment
   on an Ubuntu 20.04 or later Linux distribution.)
#. Install :code:`repo` to help set up your Yocto environment. The :code:`repo` utility makes it easy
   to reference several Git repositories within a top-level project, which you can then clone to your
   local machine all at once.

   .. code-block:: console

      mkdir ~/bin
      curl http://commondatastorage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
      chmod a+x ~/bin/repo

   You need to also make sure that :code:`~/bin` is added to your :code:`PATH` variable
   (Usually the directory is added automatically in Ubuntu).

   .. code-block:: console

      echo 'export PATH="$PATH":~/bin' >> ~/.bashrc

#. The :code:`repo` tool should be used to checkout the Yocto layers needed to build the firmware image.
   This requires a manifest file containing information about the repositories for the necessary Yocto
   layers and the specific branches to be checked out. The manifest file can be found in a repository
   called "`chargebyte-bsp <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest>`_".
   (**Note**: chargebyte's Yocto build environment is currently based on 'Kirkstone' – a LTS release of the Yocto Project, which ensures long-term support and stability for embedded Linux systems.)

   .. code-block:: console

      mkdir yocto
      cd yocto
      repo init -u https://github.com/chargebyte/chargebyte-bsp -b kirkstone-everest
      repo sync

   It should take a couple of minutes to download all the repositories using the command :code:`repo sync`.
   After the command is executed, you should be able to find three folders in the created yocto directory:

   #. :code:`source`: Where all the repositories representing the layers are cloned.
   #. :code:`chargebyte-bsp`: A clone of the 'chargebyte-bsp' repository containing the manifest file and configurations folder.
   #. :code:`build`: Initially holds a link to the :code:`conf` folder in :code:`chargebyte-bsp`.

Follow the `documentation <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md>`_ in the
'chargebyte-bsp' repository to build a firmware image based on the hardware platform specific board support package (BSP).
Currently supported are the hardware platforms Tarragon (Charge Control C) and Charge SOM.

This will include EVerest and chargebyte's hardware abstraction layer (HAL).

The next step in this chapter is to write a new EVerest module and build a custom image that incorporates
this new module.


.. _adding-a-custom-everest-module:

Adding a Custom EVerest Module
------------------------------

The EVerest documentation explains the `modules in detail <https://everest.github.io/nightly/general/04_detail_module_concept.html>`_
and their `configurations <https://everest.github.io/nightly/general/05_existing_modules.html>`_,
and includes a guide on `how to develop a new EVerest module <https://everest.github.io/nightly/tutorials/new_modules>`_.

This section will focus on integrating the module into the Yocto build system.

#. In order to integrate custom EVerest modules into the Yocto build system, you can either
   `create a new Yocto layer <https://docs.yoctoproject.org/dev-manual/layers.html#creating-your-own-layer>`_
   or extend an existing one. This section will assume that a new layer has been created and added
   to the :code:`BBLAYERS` variable in the :code:`build/conf/bblayers.conf` file.
#. A recipe file is needed to build the module. A recipe is a file with the extension :code:`.bb` and
   contains information about the module, such as the source code location, dependencies, and how to build it.
   The Yocto documentation provides a `guide on how to write a recipe file <https://docs.yoctoproject.org/dev-manual/new-recipe.html>`_.
   Let's assume that the new recipe is called :code:`my-module.bb`. It should look something like this:

   .. code-block:: console

      SUMMARY = "My Module"
      DESCRIPTION = "A new EVerest module"

      LICENSE = "APACHE-2.0"
      LIC_FILES_CHKSUM = "file://LICENSE;md5=1234567890"

      SRC_URI = "git://github.com/my_org/my-module.git;branch=main"
      S = "${WORKDIR}/git"

      inherit cmake

      DEPENDS = "lib1 lib2"

      do_install() {
          install -d ${D}${bindir}
          install -m 0755 ${B}/my-module ${D}${bindir}
      }

#. Add the name of the recipe :code:`my-module` to the :code:`IMAGE_INSTALL` variable in the
   :code:`build/conf/local.conf` file so that the module is included in the image.

The module is now integrated into the Yocto build system. The next step is to build the custom image.


Creating a Development Image
----------------------------

In order to build the custom image, follow the section "`Building an image <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-build>`_"
found in the "chargebyte-bsp" repository which produces a Linux root filesystem. This can be either
`flashed <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-flash>`_
directly, or used to `create a firmware image using RAUC <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-flash>`_.

The custom image should now include the new EVerest module.
