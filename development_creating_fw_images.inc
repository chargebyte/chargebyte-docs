.. _creating_of_custom_firmware_images:

Creating Customized Firmware Images with Yocto
==============================================

As already mentioned in the :ref:`firmware.rst` chapter, chargebyte's firmware images are built using the Yocto
Project build system. This chapter describes how to set up the Yocto build environment for chargebyte's
firmware images and how to create a customized firmware image by adding a new EVerest module based on
the chargebyte Yocto layer.

Setting up the Yocto Build Environment
--------------------------------------

The Yocto build environment is based on the chargebyte BSP (Board Support Package). Please refer
to our Board Support Package documentation in our public GitHub repository: https://github.com/chargebyte/chargebyte-bsp for detailed instructions.

#. Install the `required packages <https://docs.yoctoproject.org/ref-manual/system-requirements.html#required-packages-for-the-build-host>`_
   for Yocto on a Linux machine or virtual machine. (**Note**: We usually set up the Yocto build environment
   on an Ubuntu 20.04 or later Linux distribution.)
#. Install :code:`repo` to help set up your Yocto environment. The :code:`repo` utility makes it easy
   to reference several Git repositories within a top-level project, which you can then clone to your
   local machine all at once.

   .. code-block:: console

      mkdir ~/bin
      curl http://commondatastorage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
      chmod a+x ~/bin/repo

   Ensure that :code:`~/bin` is added to your :code:`PATH` variable
   (On Ubuntu, this directory is usually added automatically).

   .. code-block:: console

      echo 'export PATH="$PATH":~/bin' >> ~/.bashrc

#. Use the :code:`repo` tool to check out the Yocto layers required to build the firmware image.
   This requires a manifest file that contains information about the repositories for the necessary Yocto
   layers and the specific branches to be checked out. The manifest file can be found in a repository
   called "`chargebyte-bsp <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest>`_".
   (**Note**: chargebyte's Yocto build environment is currently based on 'Kirkstone' – an LTS release
   of the Yocto Project, which ensures long-term support and stability for embedded Linux systems.)

   .. code-block:: console

      mkdir yocto
      cd yocto
      repo init -u https://github.com/chargebyte/chargebyte-bsp -b kirkstone-everest
      repo sync

   It may take a few minutes to download all repositories using the :code:`repo sync` command.
   After execution, you should see three folders in the created :code:`yocto` directory:

   #. :code:`source`: Contains all the repositories representing the layers.
   #. :code:`chargebyte-bsp`: A clone of the 'chargebyte-bsp' repository, including the manifest and configuration files.
   #. :code:`build`: Initially links to the :code:`conf` folder in :code:`chargebyte-bsp`.

Follow the `documentation <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md>`_ in the
'chargebyte-bsp' repository to build a firmware image based on the specific board support package (BSP).
Currently supported hardware platforms are Tarragon (Charge Control C) and Charge SOM.

The next step is to integrate a new EVerest module and build a custom image that incorporates it.

.. _adding-a-custom-everest-module:

Integrating a Custom EVerest Module
-----------------------------------

The EVerest documentation explains the `module concept in detail <https://everest.github.io/nightly/general/04_detail_module_concept.html>`_,
their `configuration <https://everest.github.io/nightly/general/05_existing_modules.html>`_,
and provides a guide on `how to develop a new EVerest module <https://everest.github.io/nightly/tutorials/new_modules>`_.

This section focuses on integrating the module into the Yocto build system.

#. To integrate custom EVerest modules into the Yocto build system, you can either
   `create a new Yocto layer <https://docs.yoctoproject.org/dev-manual/layers.html#creating-your-own-layer>`_
   or extend an existing one. This section assumes that a new layer has been created and added
   to the :code:`BBLAYERS` variable in the :code:`build/conf/bblayers.conf` file.
#. A recipe file is required to build the module. A recipe is a file with the extension :code:`.bb` and
   contains information such as the source code location, dependencies, and build instructions.
   Refer to the Yocto documentation for a `guide on writing recipe files <https://docs.yoctoproject.org/dev-manual/new-recipe.html>`_.
   Let’s assume the new recipe is named :code:`my-module.bb`. It might look like this:

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

#. Add the recipe name :code:`my-module` to the :code:`IMAGE_INSTALL` variable in the
   :code:`build/conf/local.conf` file to include the module in the image.

The module is now integrated into the Yocto build system. The next step is to build the custom image.

Creating a Development Image
----------------------------

To build the custom image, follow the section "`Building an image <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-build>`_"
in the "chargebyte-bsp" repository. This process will generate a Linux root filesystem, which can then be
either `flashed directly <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-flash>`_,
or used to `create a firmware image using RAUC <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-flash>`_.

The resulting custom image should now include your new EVerest module.
