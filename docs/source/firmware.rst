.. _firmware.rst:

.. include:: ../../includes/firmware_upgrade.inc


Partitioning
-------------

The internal eMMC storage of a chargebyte device is divided into several partitions. The main aim is to have two independent systems available, i.e. system A and system B. This allows to run firmware updates in background while performing normal charging operation and then switch to the updated system with a fast restart of the device. This also allows to support a rollback mechanism in case of failures during firmware updates. In other words, during a firmware update, the active root file system switches from A to B or vice versa, leaving the other as rollback.

.. list-table:: eMMC Partitioning
   :header-rows: 1
   :widths: 20 10 50

   * - Partition
     - Size
     - Description
   * - /dev/mmcblk0p1
     - 1 GB
     - Root file system A
   * - /dev/mmcblk0p2
     - 1 GB
     - Root file system B
   * - /dev/mmcblk0p3
     - 1.3 GB
     - Extended Partition Container
   * - /dev/mmcblk0p5
     - 1 GB
     - Data Partition (/srv). This partition can be accessed by both root file systems and will be not changed during update process.
   * - /dev/mmcblk0p6
     - 128 MB
     - Logging file system A (/var/log)
   * - /dev/mmcblk0p7
     - 128 MB
     - Logging file system B (/var/log)

.. image:: _static/images/mountpoints_tarragon.svg
   :alt: Filesystem-Mountpoints
   :align: center

.. adding a center-aligned caption for the image
.. raw:: html

   <div style="text-align: center;">
     Filesystem Mountpoints
   </div>

.. _update_from_chargebyte_to_everest:

Updating from chargebyte's proprietary charging stack to EVerest-based charging stack
-------------------------------------------------------------------------------------

The following information is important when updating from chargebyte's proprietary charging stack
to EVerest-based charging stack:

- Please ensure that you have at least installed chargebyte\'s proprietary charging stack v3.x.x,
  before switching your board to EVerest and that this firmware booted once before the update.
  Latest firmware can be found here:
  `Legacy software stack "Truffle" <https://chargebyte.atlassian.net/servicedesk/customer/portal/13>`_.
- A note about configuration files:
  When updating from chargebyte's proprietary charging stack to this EVerest-based charging stack,
  the configuration files (e.g. the :code:`"/etc/secc/customer.json"`) are not preserved and you
  start with a basic, default EVerest configuration.
  It is therefore inevitable that Everest must be reconfigured after starting the board.
  In the worst case EVerest stack does not start up correctly. Also note, that the return path from
  EVerest to chargebyte's proprietary charging stack (when doing a firmware update) is affected:
  since the EVerest configuration files differ significantly from chargebyte's proprietary ones,
  such an update process cannot keep any configuration and uses factory defaults.
- The update process of a chargebyte EVerest image also copies important files and directories
  (like the root password and the network configuration) from the current file system to the new system.
  These are listed in the section :ref:`firmware_update_considerations`.
- Files that are stored under :code:`"/srv"` are retained during the update process.
- **Attention!** Before updating to EVerest, please check if you are installing a developer image or
  a release image. For more information, see the section :ref:`release_vs_development_images`.
- After the update has been completed, you can use the command
  :code:`"rauc status mark-active other && reboot"` to switch back to the chargebyte proprietary
  software. However, this only works as long as the partition with chargebyte's proprietary
  charging stack has not been overwritten with another firmware image.

.. include:: ../../includes/firmware_programming.inc
