.. _development.rst:

***********
Development
***********

As mentioned in the section ":ref:`programming`", customers can create their own applications and
integrate them into a custom firmware image. This section will guide you through the process of creating a custom
EVerest module and integrating it into an image. This is done by either using the Yocto build system or
cross-compiling the application for Tarragon - the Charge Control C hardware platform.


Setting up Yocto Build Environment
==================================

#. Install the `required packages <https://docs.yoctoproject.org/ref-manual/system-requirements.html#required-packages-for-the-build-host>`_
   for Yocto on a Linux machine / virtual machine. (**Note**: We normally set up the Yocto build environment
   on an Ubuntu 20.04 or later Linux distribution.)
#. Install :code:`repo` to help getting your Yocto environment ready. The :code:`repo` utility makes it
   easy to reference several Git repositories within a top-level project, which you can then clone to your
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
   (**Note**: chargebyte's Yocto build environment is currently based on 'Kirkstone' - a LTS release of the Yocto Project).

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
'chargebyte-bsp' repository to build a firmware image based on the Tarragon board support package (BSP).
This will include EVerest and chargebyte's hardware abstraction layer (HAL).

The next step in this chapter is to write a new EVerest module and build a custom image that incorporates
this new module.

Adding a Custom EVerest Module
==============================

The EVerest documentation explains the `modules in detail <https://everest.github.io/nightly/general/04_detail_module_concept.html>`_
and their `configurations <https://everest.github.io/nightly/general/05_existing_modules.html>`_,
and includes a guide on `how to develop an new EVerest module <https://everest.github.io/nightly/tutorials/new_modules>`_.

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
============================

In order to build the custom image, follow the section "`Building an image <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-build>`_"
found in "chargebyte-bsp" repository which produces a Linux root filesystem. This can be either
`flashed <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-flash>`_
directly, or used to `create a firmware image using RAUC <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest/README.md#user-content-flash>`_.

The custom image should now include the new EVerest module.

.. _cross_compiling_for_tarragon:

Cross-compiling for Tarragon
============================

Another way to integrate custom applications into the firmware image is to cross-compile the application
for Tarragon and include it in the image. A pre-requisite for this is to have the latest firmware image
as a developer build. Always keep in mind, if you want to build a new EVerest module it must be
compatible to the EVerest release within the firmware. Please have a look at the official
`EVerest documentation <https://everest.github.io/nightly/dev_tools/edm.html#setting-up-and-updating-a-workspace>`_,
how to checkout a dedicated EVerest release.

#. On an Ubuntu or Debian-based Linux distribution, install the cross-compilers for Tarragon.

   .. code-block:: console

      sudo apt install build-essential libc6-armhf-cross libc6-dev-armhf-cross binutils-arm-linux-gnueabihf gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf

#. Download chargebyte's `digital certificate <https://chargebyte.com/controllers-and-modules/evse-controllers/charge-control-c#downloads>`_
   and use it to extract the root filesystem from the firmware image.

   .. code-block:: console

      rauc extract --keyring=<chargebyte_certificate>.crt <shipped_firmware>.image bundle-staging

   .. note::
      Alternatively, if the above command does not work, you can use the following command:
       .. code-block:: console
       
          unsquashfs -d bundle-staging <shipped_firmware>.image

      But this will not verify the signature of the firmware image.

#. Mount the ext4 root filesystem image as a loop device.

   .. code-block:: console

      sudo mkdir -p /mnt/rootfs
      sudo mount bundle-staging/core-image-minimal-tarragon.ext4 /mnt/rootfs

#. Create a new directory in the folder where the new module was created (my-module) and create a new
   file called :code:`toolchain.cmake`. This file is used to set the toolchain for the cross-compilation.

   .. code-block:: console

      cd my-module
      mkdir toolchain
      cd toolchain
      touch toolchain.cmake


#. Store the following lines in the :code:`toolchain.cmake` file:

   .. code-block:: cmake

      set(CMAKE_SYSTEM_NAME Linux)
      set(CMAKE_SYSTEM_PROCESSOR arm)

      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-psabi" CACHE STRING "" FORCE )
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi" CACHE STRING "" FORCE )

      if(CMAKE_BUILD_TYPE MATCHES Debug)
          # Debug flags
          message("Enabling Debug build")
          set(CMAKE_CXX_FLAGS_DEBUG "-g")
      else()
          # Enable compiler optimization flags
          set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")

          # Strip debug symbols
          set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
      endif()

      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${CMAKE_SYSROOT}/usr/lib")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SYSROOT}/usr/lib")

      if(EXISTS ${CMAKE_SYSROOT} AND IS_DIRECTORY ${CMAKE_SYSROOT})
        message(STATUS "SYSROOT found")
      else()
        message(FATAL_ERROR "ERROR: SYSROOT '${CMAKE_SYSROOT}' not found!!!")
      endif()

      set(ENV{PKG_CONFIG_PATH} "${CMAKE_SYSROOT}/usr/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")

      set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_SYSROOT}/usr/lib/libstdc++.so")

      set(NODEJS_INCLUDE_DIR /usr/include/node) # make sure that nodejs is installed. If not, sudo apt-get install nodejs-dev

      set(PYTHON_INCLUDE_DIRS "${CMAKE_SYSROOT}/usr/include/python3.10")
      set(PYTHON_LIBRARIES "${CMAKE_SYSROOT}/usr/lib/libpython3.10.so")

      set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
      set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

      set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
      set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
      set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#. Create a new :code:`build` directory in "my-module" and navigate to it.

   .. code-block:: console

      mkdir build
      cd build

#. Run the following command inside to configure the build.

   .. code-block:: console

      cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain/toolchain.cmake -DCMAKE_SYSROOT=/mnt/rootfs ..

#. When this ends successfully, start cross-compiling using :code:`make`:

   .. code-block:: console

      make install -j$(nproc)

#. Test that the resulting binaries are compiled for Tarragon as a target:

   .. code-block:: console

      file dist/libexec/everest/modules/MyModule/MyModule

   The output should be something like:

   .. code-block:: console

      dist/libexec/everest/modules/MyModule/MyModule: ELF 32-bit LSB shared object, ARM, EABI5 version 1 (GNU/Linux), dynamically linked, interpreter /lib/ld-linux-armhf.so.3, BuildID[sha1]=9f287c2dbdcacd9ecde770df4820de9218deb439, for GNU/Linux 3.2.0, not stripped

#. The resulting binary and manifest file can be copied to the previously mounted root filesystem.

   .. code-block:: console

      cp dist/libexec/everest/modules/MyModule /mnt/rootfs/usr/libexec/everest/modules/

#. umount the loop device.

   .. code-block:: console

      sudo umount /mnt/rootfs

#. Make sure that the customized filesystem is in a clean state.

   .. code-block:: console

      fsck.ext4 -f bundle-staging/core-image-minimal-tarragon.ext4

#. Follow the steps under the section :ref:`firmware_customization` to install your PKI certificate, pack
   the modified root filesystem image again into the firmware update image, and test the new firmware image.
