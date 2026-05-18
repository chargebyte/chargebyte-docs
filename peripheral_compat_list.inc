.. _peripheral_compat_list:

Each charging station consists not only of the actual charging controller,
but also of several connected peripheral devices. Depending on the type of
charging station, i.e., AC or DC, different peripheral devices are required.

The following lists the manufacturers and models supported for different
device classes.

While the open-source EVerest charging stack supports several devices out-of-the-box,
others are implemented and maintained by chargebyte as either open-source or
closed-source EVerest modules.

.. note::
   If you need some specific component implemented, feel free to contact us.



Electricity Meters
==================

.. note::
   Not all electricity meters support/provide all possible measurement values.
   Sometimes, this also depends on the meter's hardware and/or firmware version.
   Therefore, please check whether your desired meter is compatible with your specific requirements.

AC
--

.. table:: Supported AC Electricity Meters
   :align: center
   :width: 100%
   :widths: 3,1,1,1,2,2,1,2

   +---------------------+-----------+----------+-------------+------------------------+-------------------------+---------------+----------------------+
   | Vendor / Product    | Interface | Protocol | Implementer | EVerest Module Name    | German Eichrecht        | MID Compliant | Tested by chargebyte |
   |                     |           |          |             |                        | Supported [#ac-mod]_    | [#ac-dev]_    |                      |
   +=====================+===========+==========+=============+========================+=========================+===============+======================+
   | Eastron SDM230      | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |       ✓       |          ✗           |
   +---------------------+-----------+----------+-------------+------------------------+-------------------------+---------------+----------------------+
   | Eastron SDM72D-M    | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |       ✓       |          ✓           |
   +---------------------+-----------+----------+-------------+------------------------+-------------------------+---------------+----------------------+
   | Eastron SDM72D-M v2 | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |       ✓       |          ✓           |
   +---------------------+-----------+----------+-------------+------------------------+-------------------------+---------------+----------------------+
   | Eastron SDM630 v2   | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |       ✓       |          ✓           |
   +---------------------+-----------+----------+-------------+------------------------+-------------------------+---------------+----------------------+
   | Carlo Gavazzi       | EIA-485   | Modbus   | `EVerest`_  | `CarloGavazzi_EM580`_  |            ✓            |       ✓       |          ✗           |
   | `EM580`_            |           |          |             |                        |                         |               |                      |
   +---------------------+-----------+----------+-------------+------------------------+-------------------------+---------------+----------------------+
   | Klefr 693x/694x     | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |       ✓       |          ✓           |
   +---------------------+-----------+----------+-------------+------------------------+-------------------------+---------------+----------------------+
   | Iskra WM3M4/WM3M4C  | EIA-485   | Modbus   | chargebyte  | PowermeterIskra_WM3M4C |            ✗            |       ✓       |          ✓           |
   +---------------------+-----------+----------+-------------+------------------------+-------------------------+---------------+----------------------+

.. [#ac-mod] Support in the listed EVerest module implementation.
.. [#ac-dev] Compliance of the device itself.

.. _EVerest: https://github.com/EVerest/EVerest
.. _GenericPowermeter: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerMeters/GenericPowermeter
.. _EM580: https://www.gavazziautomation.com/en-gb/product/EM580DINAV23XS2DEB
.. _CarloGavazzi_EM580: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerMeters/CarloGavazzi_EM580
.. _SerialCommHub: https://github.com/EVerest/EVerest/tree/main/modules/Misc/SerialCommHub

.. note::
   Multiple EIA-485 devices, which all use Modbus as protocol, can share the same EIA-485 bus.
   It is required to use the EVerest module `SerialCommHub`_ as low-level module to coordinate the individual
   peripheral modules - even when there is only a single device on the bus.
   The configuration of the `SerialCommHub`_ module can be found on EVerest's documentation platform:
   https://everest.github.io/nightly/reference/modules/Misc/SerialCommHub/autogenerated.html.

.. note::
   Most electricity meters which use Modbus as protocol are covered by EVerest's `GenericPowermeter`_ module. See
   https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerMeters/GenericPowermeter/models for latest supported models.

DC
--

.. table:: Supported DC Electricity Meters
   :align: center
   :width: 100%
   :widths: 3,1,1,1,2,2,1,2

   +----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+---------------+----------------------+
   | Vendor / Product                 | Interface | Protocol | Implementer | EVerest Module Name                   | German Eichrecht        | MID Compliant | Tested by chargebyte |
   |                                  |           |          |             |                                       | Supported [#dc-mod]_    | [#dc-dev]_    |                      |
   +==================================+===========+==========+=============+=======================================+=========================+===============+======================+
   | `AST DC650`_                     | EIA-485   | SLIP     | `EVerest`_  | `AST_DC650`_                          |            ✓            |       ✓       |          ✗           |
   +----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+---------------+----------------------+
   | `Acrel DJSF1352-RN`_             | EIA-485   | Modbus   | `EVerest`_  | `Acrel_DJSF1352_RN`_                  |            ✗            |       ✗       |          ✗           |
   +----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+---------------+----------------------+
   | `DZG GSH01`_                     | EIA-485   | SLIP     | `EVerest`_  | `DZG_GSH01`_                          |            ✓            |       ✓       |          ✗           |
   +----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+---------------+----------------------+
   | `LEM DCBM 400/600`_              | Ethernet  | HTTP     | `EVerest`_  | `LemDCBM400600`_                      |            ✓            |       ✓       |          ✗           |
   +----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+---------------+----------------------+
   | `Isabellenhütte IEM-DCR series`_ | Ethernet  | HTTP     | `EVerest`_  | `IsabellenhuetteIemDcr`_              |            ✓            |       ✓       |          ✗           |
   +----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+---------------+----------------------+

.. [#dc-mod] Support in the listed EVerest module implementation.
.. [#dc-dev] Compliance of the device itself.

.. _AST DC650: https://www.ast-international.com/en.products.dc-meter-overview.dc-meter.html
.. _AST_DC650: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerMeters/AST_DC650
.. _Acrel DJSF1352-RN: https://www.acrel-electric.com/product/djsf1352_rn_rail_mounted_dc_power_meter
.. _Acrel_DJSF1352_RN: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerMeters/Acrel_DJSF1352_RN
.. _DZG GSH01: https://www.dzg.de/en/products/dc-meter/
.. _DZG_GSH01: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerMeters/DZG_GSH01
.. _LEM DCBM 400/600: https://www.lem.com/en/dcbm-400-600
.. _LemDCBM400600: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerMeters/LemDCBM400600
.. _Isabellenhütte IEM-DCR series: https://www.isabellenhuette.de/iem-dcr
.. _IsabellenhuetteIemDcr: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerMeters/IsabellenhuetteIemDcr

.. warning::
   When using SLIP over EIA-485, the interface can only be used for a point-to-point connection between two
   devices. In contrast to Modbus, multiple devices cannot be addressed on the same bus.



DC Power Modules
================

.. table:: Supported DC Power Modules
   :align: center
   :width: 100%
   :widths: 5,1,1,1,2,2,1

   +---------------------------------+-----------+-------------+---------------+--------------------------+---------------+----------------------+
   | Vendor / Product                | Interface | Protocol    | Implementer   | EVerest Module Name      | BPT Supported | Tested by chargebyte |
   |                                 |           |             |               |                          | [#bpt-mod]_   |                      |
   +=================================+===========+=============+===============+==========================+===============+======================+
   | `SCU DPM series`_               | CAN       | Proprietary | `EVerest`_    | `DPM1000`_               |       ✗       |          ✗           |
   +---------------------------------+-----------+-------------+---------------+--------------------------+---------------+----------------------+
   | `UUGreen Power RX1000X0`_       | CAN       | Proprietary | `EVerest`_    | `UUGreenPower_UR1000X0`_ |       ✗       |          ✗           |
   +---------------------------------+-----------+-------------+---------------+--------------------------+---------------+----------------------+
   | `InfyPower`_                    | CAN       | Proprietary | `EVerest`_    | `InfyPower`_             |       ✗       |          ✓           |
   +---------------------------------+-----------+-------------+---------------+--------------------------+---------------+----------------------+
   | `InfyPower BEG1K075G`_          | CAN       | Proprietary | `EVerest`_    | `InfyPower_BEG1K075G`_   |       ✓       |          ✓           |
   +---------------------------------+-----------+-------------+---------------+--------------------------+---------------+----------------------+
   | `Winline`_                      | CAN       | Proprietary | `EVerest`_    | `Winline`_               |       ✗       |          ✗           |
   +---------------------------------+-----------+-------------+---------------+--------------------------+---------------+----------------------+
   | `Infypower BEG series`_         | CAN       | Proprietary | `chargebyte`_ | `InfypowerDCSupply`_     |       ✓       |          ✓           |
   +---------------------------------+-----------+-------------+---------------+--------------------------+---------------+----------------------+
   | Huawei FusionCharge R100040Gx   | CAN       | Proprietary | `EVerest`_    | `Huawei_R100040Gx`_      |       ✗       |          ✗           |
   +---------------------------------+-----------+-------------+---------------+--------------------------+---------------+----------------------+

.. [#bpt-mod] Support in the listed EVerest module implementation.


.. _SCU DPM series: https://www.scupower.com/ev-charger/ev-charger-module/
.. _DPM1000: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerSupplies/DPM1000
.. _UUGreen Power RX1000X0: https://www.uugreenpower.com
.. _UUGreenPower_UR1000X0: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerSupplies/UUGreenPower_UR1000X0
.. _InfyPower: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerSupplies/InfyPower
.. _InfyPower BEG1K075G: https://www.infypower.com/products/power-module-solution-high-power-density-module-bidi-acdc-module-22kw/131
.. _InfyPower_BEG1K075G: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerSupplies/InfyPower_BEG1K075G
.. _Winline: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerSupplies/Winline
.. _Infypower BEG series: https://www.infypower.com/bidirectional-acdc-power-converter.html
.. _InfypowerDCSupply: https://github.com/chargebyte/everest-chargebyte/tree/main/modules/InfypowerDCSupply
.. _Huawei_R100040Gx: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/PowerSupplies/Huawei_R100040Gx
.. _chargebyte: https://github.com/chargebyte/everest-chargebyte



Insulation Monitoring Devices (IMDs)
====================================

.. table:: Supported Insulation Monitoring Devices
   :align: center
   :width: 100%
   :widths: 6,1,1,1,2,2

   +--------------------------------------------------------+-----------+----------+---------------+-----------------------+----------------------+
   | Vendor / Product                                       | Interface | Protocol | Implementer   | EVerest Module Name   | Tested by chargebyte |
   +========================================================+===========+==========+===============+=======================+======================+
   | `Bender ISOMETER® isoCHA425HV with AGH420-1/AGH421-1`_ | EIA-485   | Modbus   | `EVerest`_    | `Bender_isoCHA425HV`_ |          ✗           |
   +--------------------------------------------------------+-----------+----------+---------------+-----------------------+----------------------+

.. _Bender ISOMETER® isoCHA425HV with AGH420-1/AGH421-1: https://www.bender.de/en/products/insulation-monitoring/isometer-isocha425hv-with-agh420-1/
.. _Bender_isoCHA425HV: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/IsolationMonitors/Bender_isoCHA425HV


Residual Current Monitors (RCMs)
================================


.. table:: Supported Residual Current Monitors
   :align: center
   :width: 100%
   :widths: 6,1,1,1,2,2

   +-----------------------------+----------------+----------+-----------------------------+----------------------+----------------------+
   | Vendor / Product            | Interface      | Protocol | Implementer                 | EVerest Module Name  | Tested by chargebyte |
   +=============================+================+==========+=============================+======================+======================+
   | `Western Automation RCM14`_ | Digital In/Out | none     | `chargebyte`_ (in progress) | `CbTarragonDriver`_  |          ✓           |
   +-----------------------------+----------------+----------+-----------------------------+----------------------+----------------------+

.. _Western Automation RCM14: https://emobility.westernautomation.com/ev-protection-devices/type-a/
.. _CbTarragonDriver: https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonDriver



RFID Readers
============

.. table:: Supported RFID Readers
   :align: center
   :width: 100%
   :widths: 6,1,1,1,2,2

   +-----------------------------------------+-----------+-------------+-------------+--------------------------+----------------------+
   | Vendor / Product                        | Interface | Protocol    | Implementer | EVerest Module Name      | Tested by chargebyte |
   +=========================================+===========+=============+=============+==========================+======================+
   | Stronglink SL032 (RS-485 variant with   | EIA-485   | Modbus      | chargebyte  | SL032ModbusTokenProvider |          ✓           |
   | customer specific Modbus firmware)      |           |             |             |                          |                      |
   +-----------------------------------------+-----------+-------------+-------------+--------------------------+----------------------+
   | InTallyCom RFBT001                      | EIA-485   | Modbus      | chargebyte  | SL032ModbusTokenProvider |          ✓           |
   +-----------------------------------------+-----------+-------------+-------------+--------------------------+----------------------+
   | RFID Readers based on NXP's PN532 Chip  | UART      | Proprietary | `EVerest`_  | `PN532TokenProvider`_    |          ✗           |
   +-----------------------------------------+-----------+-------------+-------------+--------------------------+----------------------+

.. _PN532TokenProvider: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/NfcReaders/PN532TokenProvider
.. _PN7160TokenProvider: https://github.com/EVerest/EVerest/tree/main/modules/HardwareDrivers/NfcReaders/PN7160TokenProvider

.. note::
   All EVerest modules which depend on libnfc, such as the `PN7160TokenProvider`_, are not officially supported.
   This library depends on the deprecated GPIO sysfs interface.



HMI Devices
===========

.. table:: Supported HMI Devices
   :align: center
   :width: 100%
   :widths: 6,1,1,1,2,2

   +-----------------------------------------+-------------+-----------+-------------+--------------------------+----------------------+
   | Vendor / Product                        | Interface   | Protocol  | Implementer | EVerest Module Name      | Tested by chargebyte |
   +=========================================+=============+===========+=============+==========================+======================+
   | Generic GPIO/Digital Output connected   | Digital Out | none      | chargebyte  | GpioLedControl + HmiLed  |          ✓           |
   | RGB LEDs (without PWM support)          |             |           |             |                          |                      |
   | for various general charger states      |             |           |             |                          |                      |
   +-----------------------------------------+-------------+-----------+-------------+--------------------------+----------------------+
   | Generic GPIO/Digital Output connected   | Digital Out | none      | chargebyte  | RfidLedFeedback          |          ✓           |
   | Single Color LED (without PWM support)  |             |           |             |                          |                      |
   | for signaling RFID token verification   |             |           |             |                          |                      |
   | result                                  |             |           |             |                          |                      |
   +-----------------------------------------+-------------+-----------+-------------+--------------------------+----------------------+



Locking Motors (Plug Locks)
===========================

Since the electrical interface for plug lock motors is platform-specific, please find the supported motor types and corresponding
configuration parameters in the platform specific module's description (e.g. CbTarragonPlugLock).
