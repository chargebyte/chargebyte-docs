.. _development.rst:

.. include:: ../../includes/development.inc

.. _cross_compiling:

Cross-compilation of EVerest modules
====================================

Cross-compilation is the fastest and most convenient way to test your own modules directly on the target system during development.  
The cross-compiled project can then either be transferred directly via FTP to the charge controller or  
integrated into a firmware image and installed on the target using the `rauc` command.

The following steps describe how to cross-compile a module for the Tarragon platform.

#. On an Ubuntu or Debian-based Linux distribution, install the cross-compilers for Tarragon:

   .. code-block:: console

      sudo apt install build-essential libc6-armhf-cross libc6-dev-armhf-cross binutils-arm-linux-gnueabihf gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf

#. Download chargebyte's `digital certificate <https://chargebyte.com/controllers-and-modules/evse-controllers/charge-control-c#downloads>`_
   and use it to extract the root filesystem from the firmware image:

   .. code-block:: console

      rauc extract --keyring=<chargebyte_certificate>.crt <shipped_firmware>.image bundle-staging

   .. note::
      Alternatively, if the above command does not work, you can use the following command:

       .. code-block:: console
       
          unsquashfs -d bundle-staging <shipped_firmware>.image

      However, this will not verify the signature of the firmware image.

#. Mount the extracted ext4 root filesystem image as a loop device:

   .. code-block:: console

      sudo mkdir -p /mnt/rootfs
      sudo mount bundle-staging/core-image-minimal-tarragon.ext4 /mnt/rootfs

#. Create a new directory in your `everest-workspace` directory (in parallel to the `everest-core` directory) and  
   create a new file named :code:`toolchain.cmake`:

   .. code-block:: console

      cd everest-workspace
      mkdir toolchain
      cd toolchain
      touch toolchain.cmake
      cd ..

#. The resulting directory structure should look like this:

   .. code-block:: console

      everest-workspace/
      |── {MyEVerestModule}
      ├── everest-core
      └── toolchain
          └── toolchain.cmake

#. Save the following content in the :code:`toolchain.cmake` file:

   .. literalinclude:: ../../includes/_static/files/toolchain.cmake

#. Create a new :code:`build_tarragon` directory in the EVerest project directory (e.g. within your own EVerest
   module project directory or :code:`everest-core` if you want to build the everest-core modules):

   .. code-block:: console

      cd {MyEVerestModule}
      mkdir build_tarragon
      cd build_tarragon

#. Run the following command inside the `build_tarragon` directory to configure the build:

   .. code-block:: console

      cmake -DCMAKE_TOOLCHAIN_FILE=../../toolchain/toolchain.cmake -DCMAKE_SYSROOT=/mnt/rootfs ..

#. When this completes successfully, start cross-compiling using :code:`make`:

   .. code-block:: console

      make install -j$(nproc)

#. If the build was successful, a dist directory will be created with the cross-compiled binaries and
   the manifest files of the modules. Please check if the following directory structure was created:

   .. code-block:: console

      dist/
      └── libexec
          └── everest
              └── modules
                  └── {MyEVerestModule}
                      ├── {MyEVerestModule} (binary)
                      └── manifest.yaml (manifest file)

#. Verify that the resulting binaries were compiled for the Tarragon target platform:

   .. code-block:: console

      file dist/libexec/everest/modules/{MyEVerestModule}/{MyEVerestModule}

   The output should be something like:

   .. code-block:: console

      dist/libexec/everest/modules/{MyEVerestModule}/{MyEVerestModule}: ELF 32-bit LSB shared object, ARM, EABI5 version 1 (GNU/Linux),
      dynamically linked, interpreter /lib/ld-linux-armhf.so.3, BuildID[sha1]=9f287c2dbdcacd9ecde770df4820de9218deb439, for GNU/Linux 3.2.0, not stripped

The resulting binary and manifest can be found in the :code:`dist/libexec/everest/modules/{MyEVerestModule}`  
directory. If you want to test the module on the target system, you can copy the module directory using  
:code:`scp` or :code:`rsync`:

   .. code-block:: console

      scp -r dist/libexec/everest/modules/{MyEVerestModule} root@<ip_address>:/usr/libexec/everest/modules/

To include the new module in a firmware image, copy the module directory into the mounted root filesystem:

   .. code-block:: console

      cp -r dist/libexec/everest/modules/{MyEVerestModule} /mnt/rootfs/usr/libexec/everest/modules/

#. Unmount the loop device:

   .. code-block:: console

      sudo umount /mnt/rootfs

#. Ensure that the modified filesystem is in a clean state:

   .. code-block:: console

      fsck.ext4 -f bundle-staging/core-image-minimal-tarragon.ext4

Follow the steps under the section :ref:`firmware_customization` to install your PKI certificate, repackage  
the modified root filesystem into a firmware update image, and test the new firmware.

.. _creating_fw_images:

.. include:: ../../includes/development_creating_fw_images.inc

.. _debugging_and_logging:

.. include:: ../../includes/development_debugging_and_logging.inc
