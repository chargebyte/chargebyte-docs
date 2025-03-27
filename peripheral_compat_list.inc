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

+---------------------+-----------+----------+-------------+------------------------+-------------------------+----------------------+
| Vendor / Product    | Interface | Protocol | Implementer | EVerest Module Name    | EVerest Module Supports | Tested by chargebyte |
|                     |           |          |             |                        |    German Eichrecht     |                      |
+=====================+===========+==========+=============+========================+=========================+======================+
| Eastron SDM230      | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |          ✗           |
+---------------------+-----------+----------+-------------+------------------------+-------------------------+----------------------+
| Eastron SDM72D-M    | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |          ✓           |
+---------------------+-----------+----------+-------------+------------------------+-------------------------+----------------------+
| Eastron SDM72D-M v2 | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |          ✓           |
+---------------------+-----------+----------+-------------+------------------------+-------------------------+----------------------+
| Eastron SDM630 v2   | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |          ✓           |
+---------------------+-----------+----------+-------------+------------------------+-------------------------+----------------------+
| Klefr 693x/694x     | EIA-485   | Modbus   | `EVerest`_  | `GenericPowermeter`_   |            ✗            |          ✓           |
+---------------------+-----------+----------+-------------+------------------------+-------------------------+----------------------+
| Iskra WM3M4/WM3M4C  | EIA-485   | Modbus   | chargebyte  | PowermeterIskra_WM3M4C |            ✗            |          ✓           |
+---------------------+-----------+----------+-------------+------------------------+-------------------------+----------------------+

.. _EVerest: https://github.com/EVerest/everest-core
.. _GenericPowermeter: https://github.com/EVerest/everest-core/tree/main/modules/GenericPowermeter
.. _SerialCommHub: https://github.com/EVerest/everest-core/tree/main/modules/SerialCommHub

.. note::
   Multiple EIA-485 devices, which all use Modbus as protocol, can share the same EIA-485 bus.
   It is required to use the EVerest module `SerialCommHub`_ as low-level module to coordinate the individual
   peripheral modules - even when there is only a single device on the bus.
   The configuration of the `SerialCommHub`_ module can be found on EVerest's documentation platform:
   https://everest.github.io/nightly/_generated/modules/SerialCommHub.html.

.. note::
   Most electricity meters which use Modbus as protocol are covered by EVerest's `GenericPowermeter`_ module. See
   https://github.com/EVerest/everest-core/tree/main/modules/GenericPowermeter/models for latest supported models.

DC
--

+----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+----------------------+
| Vendor / Product                 | Interface | Protocol | Implementer | EVerest Module Name                   | EVerest Module Supports | Tested by chargebyte |
|                                  |           |          |             |                                       |    German Eichrecht     |                      |
+==================================+===========+==========+=============+=======================================+=========================+======================+
| `LEM DCBM 400/600`_              | Ethernet  | HTTP     | `EVerest`_  | `LemDCBM400600`_                      |            ✓            |          ✗           |
+----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+----------------------+
| `Isabellenhütte IEM-DCR series`_ | Ethernet  | HTTP     | `EVerest`_  | `IsabellenhuetteIemDcr`_ (pending PR) |            ✓            |          ✗           |
+----------------------------------+-----------+----------+-------------+---------------------------------------+-------------------------+----------------------+

.. _LEM DCBM 400/600: https://www.lem.com/en/dcbm-400-600
.. _LemDCBM400600: https://github.com/EVerest/everest-core/tree/main/modules/LemDCBM400600
.. _Isabellenhütte IEM-DCR series: https://www.isabellenhuette.de/iem-dcr
.. _IsabellenhuetteIemDcr: https://github.com/EVerest/everest-core/pull/1059/commits/a9518eb94f53208146c98da9a4c6366e56c5feec



DC Power Modules
================

+-------------------------+-----------+-------------+---------------+----------------------+----------------------+
| Vendor / Product        | Interface | Protocol    | Implementer   | EVerest Module Name  | Tested by chargebyte |
+=========================+===========+=============+===============+======================+======================+
| `SCU DPM series`_       | CAN       | Proprietary | `EVerest`_    | `DPM1000`_           |          ✗           |
+-------------------------+-----------+-------------+---------------+----------------------+----------------------+
| `Infypower BEG series`_ | CAN       | Proprietary | `chargebyte`_ | `InfypowerDCSupply`_ |          ✓           |
+-------------------------+-----------+-------------+---------------+----------------------+----------------------+

.. _SCU DPM series: https://www.scupower.com/ev-charger/ev-charger-module/
.. _DPM1000: https://github.com/EVerest/everest-core/tree/main/modules/DPM1000
.. _Infypower BEG series: https://www.infypower.com/bidirectional-acdc-power-converter.html
.. _InfypowerDCSupply: https://github.com/chargebyte/everest-chargebyte/tree/main/modules/InfypowerDCSupply
.. _chargebyte: https://github.com/chargebyte/everest-chargebyte



Insulation Monitoring Devices (IMDs)
====================================

+--------------------------------------------------------+-----------+----------+-------------------------+----------------------+----------------------+
| Vendor / Product                                       | Interface | Protocol | Implementer             | EVerest Module Name  | Tested by chargebyte |
+========================================================+===========+==========+=========================+======================+======================+
| `Bender ISOMETER® isoCHA425HV with AGH420-1/AGH421-1`_ | EIA-485   | Modbus   | `chargebyte`_ (planned) | TBD                  |                      |
+--------------------------------------------------------+-----------+----------+-------------------------+----------------------+----------------------+

.. _Bender ISOMETER® isoCHA425HV with AGH420-1/AGH421-1: https://www.bender.de/en/products/insulation-monitoring/isometer-isocha425hv-with-agh420-1/



Residual Current Monitors (RCMs)
================================

+-----------------------------+----------------+----------+-----------------------------+----------------------+----------------------+
| Vendor / Product            | Interface      | Protocol | Implementer                 | EVerest Module Name  | Tested by chargebyte |
+=============================+================+==========+=============================+======================+======================+
| `Western Automation RCM14`_ | Digital In/Out | -        | `chargebyte`_ (in progress) | `CbTarragonDriver`_  |          ✓           |
+-----------------------------+----------------+----------+-----------------------------+----------------------+----------------------+

.. _Western Automation RCM14: https://emobility.westernautomation.com/ev-protection-devices/type-a/
.. _CbTarragonDriver: https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonDriver



RFID Readers
============

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
| RFID Readers based on NXP's PN7160 Chip | I²C/SPI   | Proprietary | `EVerest`_  | `PN7160TokenProvider`_   |          ✗           |
+-----------------------------------------+-----------+-------------+-------------+--------------------------+----------------------+

.. _PN532TokenProvider: https://github.com/EVerest/everest-core/tree/main/modules/PN532TokenProvider
.. _PN7160TokenProvider: https://github.com/EVerest/everest-core/tree/main/modules/PN7160TokenProvider



HMI Interfaces
==============

+-----------------------------------------+-------------+-----------+-------------+--------------------------+----------------------+
| Vendor / Product                        | Interface   | Protocol  | Implementer | EVerest Module Name      | Tested by chargebyte |
+=========================================+=============+===========+=============+==========================+======================+
| Generic GPIO/Digital Output connected   | Digital Out | -         | chargebyte  | GpioLedControl + HmiLed  |          ✓           |
| RGB LEDs (without PWM support)          |             |           |             |                          |                      |
| for various general charger states      |             |           |             |                          |                      |
+-----------------------------------------+-------------+-----------+-------------+--------------------------+----------------------+
| Generic GPIO/Digital Output connected   | Digital Out | -         | chargebyte  | RfidLedFeedback          |          ✓           |
| Single Color LED (without PWM support)  |             |           |             |                          |                      |
| for signaling RFID token verification   |             |           |             |                          |                      |
| result                                  |             |           |             |                          |                      |
+-----------------------------------------+-------------+-----------+-------------+--------------------------+----------------------+



Locking Motors (Plug Locks)
===========================

Since the electrical interface for plug lock motors is platform-specific, please find the supported motor types and corresponding
configuration parameters in the platform specific module's description (e.g. CbTarragonPlugLock).
