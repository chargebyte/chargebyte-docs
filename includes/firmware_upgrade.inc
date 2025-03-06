********
Firmware
********

Introduction to Yocto
=====================

chargebyte hardware platforms are shipped with pre-flashed firmware including one of the following charging stacks:

* EVerest charging stack along with platform specific EVerest modules e.g. CbSystem.
* chargebyte's proprietary charging stack (only available for Charge Control C)

The shipped firmware was created using the Yocto project; an open-source collaboration initiative that provides templates, tools, and methods to help developers create custom Linux-based systems for embedded devices. It supports a wide range of hardware architectures and provides a consistent, reproducible environment for developing, building, and maintaining embedded systems. To get familiar with the Yocto project, you can find all the required information on the project's `website <https://www.yoctoproject.org/>`_.

.. _firmware_update:

Firmware Upgrade
================

The following sections describe different ways to install a firmware upgrade on your chargebyte product. Please ensure that the power supply is stable during a firmware upgrade. In case of an unsuccessful update or of power loss during the installation of the update, the chargebyte device performs a rollback to the previous stable version of the charging firmware. For more information about the rollback mechanism, see the section :ref:`rollback_mechanism`. The update is finished when the board is rebooted.

The currently installed firmware version can be checked by reading the content of the file :code:`VERSION` found under :code:`/usr/share/secc`.

.. _download_firmware_images:

Download Firmware Images
------------------------

Firmware images are released by chargebyte on our meta-chargebyte-everest repository, which is the Yocto layer to build the firmware images.
The image files can be found in the `"Release" section <https://github.com/chargebyte/meta-chargebyte-everest/releases>`_ of the
repository. Here you can find the latest firmware images and also older released versions.

.. note::

  Please read the release notes of the firmware image before downloading and installing it. In the
  release notes you can find information about the changes and new features of the firmware image and
  also the version information which "everest-core" tag the firmware image is based on. This information
  is especially important if you build up your cross-compile environment in section :ref:`cross_compiling`.
  Please check that your cross-compile environment is using the same "everest-core" tag as the firmware
  image you want to install.

Device Access
-------------

There are different possibilities to access the device for configuration or update purposes. Please look at section :ref:`connecting-via-ssh-or-serial-interface` for further details.

Update via USB
--------------

**Preparation of the USB update**

#. Download the firmware update image file onto your workstation.
#. Plug a USB flash drive into your workstation.
#. Format the USB flash drive as EXT2/3/4, FAT16/32, exFAT or NTFS.
#. Copy the firmware update image file (:code:`*.image`) onto the USB flash drive's root directory.

Please note that you should not place multiple :code:`*.image` files onto the root folder of the USB flash drive, since it is not guaranteed in which order the files are tried and applied.

**Updating the Firmware**

#. Connect the board to the power supply.
#. Wait until the board is booted.
#. Connect to the board via SSH or Debug UART to backup all your own implementation, configuration and databases files.
#. Plug in the USB flash drive with the Firmware Update Image file in the USB port of the board.
#. Observe the LED update indications and wait until the whole firmware update and reboot process is finished - it takes up to 5 minutes.
#. When the firmware update process is finished and the USB flash drive can be unplugged.

Update via SSH and SFTP
-----------------------

#. Connect to the board via SSH (e.g. PuTTY).
#. Backup all your own implementation, configuration and databases files if necessary.
#. Transfer the update image file via SFTP to the board and store it in the directory :code:`/srv` with e.g. filename my-update.image. On Windows systems you can use e.g. WinSCP or Filezilla.
#. Run the following command via SSH console: :code:`rauc install /srv/my-update.image`.
#. The update process should start and report progress and success via console messages.
#. Reboot into the new system by running the following command via SSH console: :code:`reboot`.
#. Re-login into the new system and delete the file :code:`/srv/my-update.image`.

Update via SSH or Serial Console and HTTP or FTP
------------------------------------------------

#. Connect to the board via SSH (e.g. PuTTY) or serial terminal.
#. Backup all your own implementation, configuration and databases files if necessary.
#. Place the update image file on a HTTP or FTP server which is reachable via network by your chargebyte device.
#. Note the URL of the download. In case authentication is required, you must provide the credentials in the URL, e.g. :code:`http://username:passwd@my-site.com/update.image`.
#. Run the following command via SSH console: :code:`rauc install <url>`, where you replace the URL with your actual URL.
#. The update process should start and report progress and success via console messages.
#. After success, reboot into the new system by running the following command via SSH console: :code:`reboot`.

Update via OCPP
---------------

The firmware update via OCPP commands :code:`UpdateFirmware` and :code:`FirmwareStatusNotification` is implemented. Such an update via OCPP automatically triggers a reboot of the charge point after successfully installing the new firmware. The central system is notified about the successful installation before the reboot of the charge point.

Support for casync based Firmware Updates
-----------------------------------------
As mentioned in the previous sections, the firmware update mechanism uses `RAUC <https://rauc.io>`_ as update framework. The traditional method of updating a device is that a big firmware update image file is transferred to the device and then installed. However, this approach is sometimes not ideal, for example when during different firmware releases only few parts changed. To address such scenarios, RAUC itself supports casync based bundles. For more details, please refer to RAUC's own documentation: https://rauc.readthedocs.io/en/latest/advanced.html#rauc-casync-support. It is obvious that such kind of firmware updates require an established Internet connection (or a locally available HTTP/FTP server which can be reached by the charging station) - but the concept does not work for USB pen drive firmware updates.

On casync-enabled chargebyte firmware versions, it is possible to pass a URL referring to a casync firmware update image directly to the RAUC framework via :code:`rauc install <URL>`. Please remember that RAUC will use the passed URL to construct a base URL for accessing the smaller chunks. For example the URL :code:`http://example.com/update.raucb` would lead to the assumption that all chunks can be accessed via the base URL :code:`http://example.com/update.castr/`. Note, that the chunk store is a whole directory with many small files inside, not a simple file - the file extension like directory naming might suggest this.
