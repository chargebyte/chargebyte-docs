.. _factory_reset:

Factory Reset
=============

A factory reset returns the mutable configuration and operational data of the
charging controller to the defaults supplied with the currently installed
firmware. Use it when preparing a device for a new installation or when local
configuration must be discarded. A factory reset does not install, downgrade,
or otherwise replace the firmware.

Prerequisites
-------------

Before starting a factory reset:

* Disconnect all vehicles and make sure that no charging session is active.
* Back up every configuration, certificate, key, log, or diagnostic file that
  might still be required.
* Ensure a stable power supply. Do not disconnect power while the reset or the
  subsequent reboot is in progress.
* Make sure that the factory network settings and an initial access method are
  known. The configured network address and existing login credentials might
  no longer work after the reset.

In the WebUI, the **Factory Reset** button becomes available only if EVerest is
configured correctly and no charging session is active. All configured charging
ports must be reported as unplugged. EVerest is stopped before the reset tool is
executed. The device reboots automatically after a successful reset.

Affected and Retained Data
--------------------------

The reset restores locally modified settings and persistent application data
managed by the product firmware. This generally includes:

* EVerest and OCPP configuration and runtime data,
* custom network configuration,
* locally installed certificates and keys, and
* local access credentials, including the WebUI login and the ``root``
  password.

The currently installed firmware image and its factory defaults are retained.
Factory-programmed hardware information is not part of the normal reset scope.

.. important::
   The exact reset scope is defined by the product firmware. Files stored
   outside the locations managed by the reset implementation might be retained.
   A factory reset must therefore not be treated as a secure erase of every
   storage location. Contact chargebyte support before transferring or
   decommissioning a device if complete data erasure is required.

Access After the Reset
----------------------

After the device has rebooted:

#. Reconnect using the factory network settings or a local serial connection.
#. Complete the initial access setup. If the WebUI is available, create new
   WebUI login credentials. Otherwise, use the serial console to set the
   initial ``root`` password.
#. Enable SSH explicitly if remote shell access is required; SSH is disabled
   by default after the reset.
#. Restore only the required, verified configuration and credentials, then
   confirm the network, charging, and backend connections before returning the
   charging controller to service.

