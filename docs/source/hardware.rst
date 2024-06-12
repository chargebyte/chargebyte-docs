.. hardware.rst:

========
Hardware
========

HMI
---
LEDs
^^^^

Charge Control C has three LEDs populated.

- LED1 (green)
- LED2 (yellow)
- LED3 (red)

.. image:: _static/images/leds.svg
    :width: 500pt

**LED1(green)**

    Default behavior is:

    - blinking: booting
    - permanently on: boot is finished and charging software is operational

**LED2 (yellow)**

    Default behavior is:

    - permanently on: USB Stick was plugged in and is being searched for update images
    - blinking (250ms on / 250ms off): update in progress

**LED3 (red)**

    Default behavior is:

    - Linux Heartbeat (pulsing depending on load)

Switches
^^^^^^^^

Charge Control C comes with three switches as shown in Figure Switches on Charge Control C.

.. image:: _static/images/switches.svg
    :width: 500pt

**SW1 - EA-485 Termination**

SW1 enables or disables the termination resistor of the EIA-485 1 available on X7.

.. csv-table:: SW1 - EIA-485 Termination
   :widths: 20 20
   :header-rows: 1
   :file: _static/tables/termination.csv
   :align: left

**SW2 - Rotary Coded Switch**

The rotary coded switch is intended to provide a setup possibility for field service technicians or similar personnel.
The switch is read in software - the default use is to set up the maximum current that the charge controller may allow for charging, 
and the number of phases used. The use of the switch can be changed in software if desired.

The currently implemented current limits are:

.. csv-table:: Current limits
   :widths: 20 20 20
   :header-rows: 1
   :file: _static/tables/current_limits.csv
   :align: left

**CAUTION!**
**Electrical shock hazard!**
The switch is usually locking the position of the selector at a valid position, 
but it is possible to leave the selector in an invalid position between two states. 
Changing the selection should only be done in power-off state!

**SW3**

SW3 is reserved for future use and is not populated at the moment.

Mechanical dimensions
---------------------
The mechanical dimensions and mounting holes of this product are dimensioned in Figure mechanical drawing.

.. image:: _static/images/dimensions.svg
    :width: 500pt

Mounting
--------
* Mounting position is irrelevant as long as operating parameters are met.
* Every mounting hole has a copper restrict area to support mounting via enclosure domes and screws. 
Screws and domes should not exceed a diameter of 7.8 mm.
* Tightening torque should not exceed 4 Nm.

Hardware interfaces
-------------------
Ethernet
^^^^^^^^
This device supports 10/100 Mbit/s Ethernet. In the Linux operating system it is available as network interface eth0. 
Starting with Yocto-based firmware releases, this interface is part of a bridge interface br0, see following sections for details.

.. csv-table:: Ethernet
   :widths: 20 20
   :header-rows: 1
   :file: _static/tables/ethernet.csv
   :align: left

USB
^^^
USB support is composed of a USB OTG core controller. It is compliant with the USB 2.0 specification.
USB is mainly used for USB internet dongles, firmware updates and for commissioning purposes.

.. csv-table:: Currently supported peripherals
   :widths: 20 20 20 20
   :header-rows: 1
   :file: _static/tables/peripherals.csv
   :align: left
   :delim: ;

EIA-485
^^^^^^^
In order to connect Charge Control C to a backend or an internal peripheral (e.g. smart meters, display and RFID readers), 
the board supports up to two EIA-485 interfaces.
While the charging stack ships with included support for some peripheral devices, 
the "link to backend" functionality is not implemented by default.
The baud rate of each EIA-485 interface is configurable up to 115200 bps. 

.. csv-table:: Board Interface
   :widths: 20 20 20 20
   :header-rows: 1
   :file: _static/tables/board_interface.csv
   :align: left
   :delim: ;

1: 390 Ohm Pull-up & 390 Ohm Pull-down resistors permanently activated

2: PCB board revision string can be found on the left side of the board near the relays

**Supported Peripheral Devices**
The factory shipped charging stack supports several peripheral devices out-of-the-box. 
For each type of peripheral, the charging stack support is provided in the form of a dedicated daemon, i.e. "rfidd", "meteringd", "recloserd".

Since Charge Control C can be freely programmed, it is possible that customers add additional device support on their own, 
writing a customer specific daemon which then replaces the functionality of the factory shipped daemon.

*Currently supported internal peripherals using Modbus:*

* Electricity meter
    * ABB EV3 012-100
    * BZR Bauer BSM-WS36x-Hxx-1xxx-000x (as SunSpec compatible device)
    * Carlo Gavazzi EM300/ET300/EM100/ET100 series
    * DZG DVH4013
    * Eastron SDM72D-M
    * Eastron SDM230
    * Eastron SDM630 v2
    * Elecnova DDS1946-2P/2M
    * Elecnova DTS1946-4P/4M
    * Klefr 693x/694x
    * Iskra WM3M4/WM3M4C
    * Phoenix Contact EEM-350-D-MCB
    * Socomec Countis E03/04
    * SunSpec compatible meters (meter model 203)
* Recloser devices
    * Geya GRD9M/L-S
* RFID reader
    * StrongLink SL032 (with customized Modbus protocol)
    * InTallyCom RFBT001 (compatible with 'stronglink-modbus' protocol)

*Currently supported internal peripherals using proprietary protocols:*
* RFID reader
    * StrongLink SL032 (public available, proprietary protocol)
    * SMART Technologies ID RFID Einbaumodul MCR LEGIC

:underline:`Note`: It should be avoided to use different protocols on the same connector.

The following table documents the default communication parameters for Modbus peripherals used by the charging stack unless configured explicitly. 
Usually, these defaults are derived from the meter's default settings to allow Plug & Play. 
But especially in cases where a meter implementation supports several models, it must be cross-checked that the 
connected meter's (default) settings matches - adapt the configuration of the meter and/or change the charging stack configuration to make it work.

.. list-table:: Communication parameters for Modbus peripherals
    :header-rows: 1
    
    * - Peripherals Device
      - Baud rate
      - Parity"
      - Modbus Address"
      - Note
    * - ABB EV3
      -	9600
      -	even
      -	1
      - Parity cannot be changed on meter devices, so customer needs to configure it in customer.json.
    * - BZR Bauer BSM-WS36x-Hxx-1xxx-000x
      -	19200
      -	even
      -	42
      -	This meter responds very slowly (up to 10s) to each Modbus query. 
      So it is recommended to use it as single device on a dedicated RS-485 port only. Please also consider this when using real-time load balancing.
    * - Carlo Gavazzi EM300/ET300/EM100/ET100 series
      -	9600
      -	none	
      - 1
      - 
    * - DZG DVH4013
      - 9600
      - none
      - Modbus Address scan is performed
      - DZG devices ships with parity set to "even" by default, so customer needs to configure it in customer.json.
    * - Eastron SDM72D-M
      - 9600
      - none
      - 1
      - Only parity "even" is documented as default in device manuals.
    * - Eastron SDM230
      - 9600
      -	none
      - 1
      -	This Eastron model is shipped with factory defaults set to baud rate 2400 and settings 8E1, 
      so customer usually needs to change baud rate and parity values in customer.json.
    * - Eastron SDM630 v2
      - 9600
      - none
      - 1
      -	No documented defaults in device manuals.
    * - Elecnova DDS1946-2P/2M
      - 9600
      -	none
      -	1
      -	No documented defaults in device manuals. The factory Modbus address is usually derived from the serial number.
    * - Elecnova DTS1946-4P/4M
      - 9600
      -	none
      -	1
      -	No documented defaults in device manuals. The factory Modbus address is usually derived from the serial number.
    * - Geya GRD9M/L-S
      - 9600
      - none
      -	3
      -    
    * - Iskra WM3M4/WM3M4C
      - 115200
      -	none
      -	33
    * - Klefr 693x/694x
      - 9600
      - none
      - 1
      - 
    * - Phoenix Contact EEM-350-D-MCB
      - 9600
      - none
      - 1
      - 
    * - Socomec Countis E03/04
      -	38400
      -	none
      -	5
      -	The factory default settings for Modbus communication interface are not documented in the datasheet.
    * - StrongLink SL032 (with customized Modbus protocol)
      - 9600
      -	none
      -	17

*Supported Electricity Meter Features/Measurands*
While the supported electricity meters all use Modbus as communication protocol, there are differences in the supported measurands/features by the meters.

.. list-table:: Supported Electricity Meter Features/Measurands
    :header-rows: 2
    
    * - Meter Model
      - Baud rate
      - Parity"
      - Modbus Address"
      - Note

Board connections
-----------------

Device Marking
--------------
