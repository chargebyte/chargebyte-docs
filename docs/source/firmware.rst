.. _firmware.rst:

.. include:: ../../includes/firmware_upgrade.inc


Partitioning
-------------

The internal eMMC storage of a chargebyte device is divided into several partitions to support two independent systems: system A and system B. This setup enables firmware updates to run in the background while the device continues normal charging operations. Once the update is complete, the system can switch to the updated version with a reboot of the device. Additionally, this approach supports a rollback mechanism in case of update failures. In other words, during a firmware update, the active root file system switches from A to B (or vice versa), leaving the other partition available for rollback if needed.

.. list-table:: eMMC Partitioning
   :header-rows: 1
   :widths: 20 10 50

   * - Partition
     - Size
     - Description
   * - /dev/mmcblk0p1
     - 2 GB
     - Root file system A
   * - /dev/mmcblk0p2
     - 2 GB
     - Root file system B
   * - /dev/mmcblk0p3
     - 3.3 GB
     - Extended Partition Container
   * - /dev/mmcblk0p5
     - 2.8 GB
     - Data Partition (/srv). This partition can be accessed by both root file systems and will be not changed during update process.
   * - /dev/mmcblk0p6
     - 256 MB
     - Logging file system A (/var/log)
   * - /dev/mmcblk0p7
     - 256 MB
     - Logging file system B (/var/log)

.. image:: ../../includes/_static/images/mountpoints.svg
   :alt: Filesystem-Mountpoints
   :align: center

.. adding a center-aligned caption for the image
.. raw:: html

   <div style="text-align: center;">
     Filesystem Mountpoints
   </div>

.. include:: ../../includes/firmware_programming.inc
