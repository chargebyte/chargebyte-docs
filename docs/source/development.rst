.. _development.rst:

.. include:: ../../includes/development.inc

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

   .. literalinclude:: ../../includes/_static/files/toolchain.cmake

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

      dist/libexec/everest/modules/MyModule/MyModule: ELF 32-bit LSB shared object, ARM, EABI5 version 1 (GNU/Linux),
      dynamically linked, interpreter /lib/ld-linux-armhf.so.3, BuildID[sha1]=9f287c2dbdcacd9ecde770df4820de9218deb439, for GNU/Linux 3.2.0, not stripped

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
