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

.. flat-table:: Board Interface
    :header-rows: 1

    * - Board Interface
      - EIA-485 #1 isolated (X7)
      - EIA-485 #2 (X8)
    * - Linux Interface
      - /dev/ttymxc0
      - /dev/ttymxc4
    * - Termination
      - yes, 120 Ohm enableable via SW1 (factory default: not activated)
      - yes, 120 Ohm permanently activated
    * - :rspan:`1` Failsafe Biasing [#]_ 
      - PCB board revision ≤ V0R32 [2]_ :no
      - :rspan:`1` yes
    * - PCB board revision > V0R32 [2]_ :yes
    * - :rspan:`2` Intended Usage
      - Charge Control C 100
      - link to backend / internal peripheral
      - -not available-
    * - Charge Control C 200
      - link to backend / internal peripheral
      - -not available-
    * - Charge Control C 300
      - link to backend
      - internal peripheral

.. [#] 390 Ohm Pull-up & 390 Ohm Pull-down resistors permanently activated
.. [2] PCB board revision string can be found on the left side of the board near the relays

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

.. flat-table:: Communication parameters for Modbus peripherals
    :header-rows: 1
    
    * - Peripherals Device
      - Baud rate
      - Parity
      - Modbus Address
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
      -	This meter responds very slowly (up to 10s) to each Modbus query. So it is recommended to use it as single device on a dedicated RS-485 port only. Please also consider this when using real-time load balancing.
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
      -	This Eastron model is shipped with factory defaults set to baud rate 2400 and settings 8E1, so customer usually needs to change baud rate and parity values in customer.json.
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

.. flat-table:: Supported Electricity Meter Features/Measurands
    :header-rows: 2
    :stub-columns: 1

    * - :rspan:`1` Meter Model
      - :cspan:`4` Reading via Modbus

    * - Meter Serial number
      - Eichrecht Supported
      - Active Power (Overall Consumption)
      - Active Energy (Overall Consuption)
      - Voltage/Current/Power per phases

    * - ABB EV3
      - yes
      -	no
      - yes
      - yes
      -	yes/yes/yes

    * - BZR Bauer BSM-WS36x-Hxx-1xxx-000x
      -	yes
      -	planned
      -	yes
      -	yes
      -	yes/yes/yes

    * - Carlo Gavazzi EM300/ET300/EM100/ET100 series
      -	yes
      -	no
      -	yes
      -	yes
      - yes/yes/yes

    * - DZG DVH4013
      -	yes
      -	no
      -	yes
      - yes
      - yes/yes/no

    * - Eastron SDM72D-M (HW revision: v1)
      - no
      -	no
      -	yes
      -	yes
      -	no/no/no

    * - Eastron SDM72D-M (HW revision: v2)
      -	yes
      - no
      -	yes
      -	yes
      -	yes/yes/yes

    * - Eastron SDM230
      -	yes
      -	no
      -	yes
      -	yes
      -	yes/yes/yes

    * - Eastron SDM630 v2
      -	no
      -	no
      -	yes
      -	yes
      -	yes/yes/yes

    * - Elecnova DDS1946-2P/2M
      -	no
      -	no
      -	yes
      -	yes
      -	yes/yes/yes

    * - Elecnova DTS1946-4P/4M
      -	no
      -	no
      -	yes
      -	yes
      -	yes/yes/yes

    * - Klefr 693x/694x
      - yes
      -	no
      -	yes
      - yes
      -	yes/yes/yes

    * - Iskra WM3M4/WM3M4C
      -	yes
      -	WM3M4C only
      -	yes
      - yes
      -	yes/yes/yes

    * - Phoenix Contact EEM-350-D-MCB
      - yes
      - no
      -	yes
      -	yes
      -	yes/yes/yes

    * - Socomec Countis E03/04
      -	yes
      -	no
      -	yes
      -	yes
      -	yes/yes/yes

For SunSpec compatible meters it depends on the specific device and model which register values are filled by the meter's firmware. 
For the single phase meter models, the overall consumption/energy corresponds to the available single phase which is internally handled as L1 phase.

Some meters also support bidirectional counting, so please double check, whether the meter is installed in correct direction. 
The current charging stack does not yet support bidirectional charging, so it's always looking for import (aka "consumption") registers. 
Depending on the actual meter protocol implementation, exported current/power reported by the meter might be filtered out and forwarded as zero value in 
internal MQTT API.

*General Assumptions*

An EIA-485 bus is not considered a plug and play bus. It is assumed that peripheral devices are connected before powering the charging station, 
or at least power up simultaneously with the Charge Control C board.

*Advices/Requirements for Customer Applications*

Since the implementation of peripheral device support on charging stack side consists of multiple daemons, 
all daemons must coordinate their access to the same UART interface when communicating with devices on the same EIA-485 bus.

So any access to the EIA-485 serial UART device (e.g. /dev/ttymxc0) must be protected by TIOCEXCL/TIOCNXCL ioctl calls. 
These ioctls are functionally only ensured for non-root users. For this reason, all daemons accessing serial ports must be 
run as user "daemon" and group "dialout". While factory shipped start scripts take care of this, customers' start scripts should mimic this behavior. 
Special care must also be taken during development, e.g. when manually starting and testing daemons via SSH to run with appropriate changed uid/guid.

Another point to consider is, that serial accesses of each daemon should be limited to a short time (<1 s). 
Otherwise, the functionality of other daemons using the same serial port is limited.

On Charge Control C platform, customers writing their own serial port application need be aware about the hardware echo while sending data to the serial port. 
It is up to the (customer) software to discard this local echo since it is not possible to disable the echo on hardware-side.

Customers who want to access Modbus peripherals are advised to also use libmodbus, an open-source C library for this protocol, as factory shipped daemons do. 
The libmodbus variant deployed on Charge Control C was already extended with functionality to discard the local echo on library side. Moreover, 
the TIOCEXCL functionality was added. While the port locking is done transparently, the echo discarding functionality must be enabled by customers' applications 
by calling modbus_rtu_set_suppress_echo.

A customer implementation in C might look like the following example. It detects whether libmodbus provides the modbus_rtu_set_suppress_echo call and is thus 
usable in native PC environments with standard libmodbus as shipped by Linux distributions, 
but also uses the feature when available/running on a Charge Control C device.

.. code-block:: c++

    ...
    #include <modbus/modbus.h>
    int modbus_rtu_set_suppress_echo(modbus_t *ctx, bool on) __attribute__((weak));
    
    ...
    
    int main(int argc, char *argv[])
    {
        /* the libmodbus context */
        modbus_t *mbctx;
    
        /* set local_echo to true if you run on a platform which has local hardware echo */
        bool local_echo = true;
    
        ...
    
        mbctx = modbus_new_rtu(...);
    
        if (modbus_rtu_set_suppress_echo) {
            printf("Info: %senabling local echo suppression", local_echo ? "" : "not ");
            modbus_rtu_set_suppress_echo(mbctx, local_echo);
        } else {
            if (local_echo) {
                printf("Error: local echo suppression support requested, but no support in libmodbus.");
                exit(1);
            } else {
                printf("Info: libmodbus without local echo suppression support");
            }
        }
    
        ...
    }

Our modified source code of libmodbus can be found on Github.

We also included a libmodbus recipe in our Yocto BSP distribution layer 
which uses our libmodbus repository as source when building/including libmodbus in the firmware image.

*Metering daemon*

**Start-up Behavior**

When configured for "dzg" in customer.json and no meter serial number is provided, 
then during power up of the charging station a single scan of the Modbus address range 01 - 99 is performed by the metering daemon. 
In worst case this takes up to nearly 60 seconds. While the scan is active, no other access to the EIA-485 bus is possible.

For other meter protocols, no such bus scan is implemented, and the factory defaults of the electricity meter are assumed (i.e. Modbus address). 
This can be overwritten via customer.json by configuring a Modbus address explicitly.

**Behavior in case of unavailability**

During power up, no further scan attempt is made in case no meter was found during scan or when no meter was found under the expected Modbus address.

However, during normal operation, the metering daemon is safe against temporary disconnects or unavailability.

For example, the Klefr meters make a CRC check after power cycling during which the meters do not respond to Modbus queries and thus cause temporary 
unavailabilities. In order to workaround this behavior and to prevent reporting power meter failures during charging, 
a specific timeout of 10 seconds is implemented for these meters, 
while for all other meter types the timeout is set to 2 seconds before reporting an error.

*RFID / Recloser Daemons*

In contrast to the metering daemon, when these daemons do not find their peripheral devices during booting up, they continue to try to communicate with the peripherals.

Main PLC
^^^^^^^^
This device supports 10 Mbit/s HomePlug Green PHY™ power line communication on mains. 
This interface is available (if present) as eth2. Please note, that for security reasons this 
interface does not ship from factory with the Network Management Key (NMK) set to "HomePlugAV" like 
traditional powerline devices did for a long time to ease installation. During the manufacturing process, 
a random NMK is generated for each device and installed as factory default setting. 
This prevents attackers from accessing the device over mains powerline with a well-known NMK.

.. flat-table:: Supported Electricity Meter Features/Measurands
    :header-rows: 1
    :stub-columns: 1

    * - Board Interface
      - Linux Interface
    
    * - Mains PLC
      - eth2

**Pairing**

When your HomePlug compatible companion is already setup and working, you are ready to join the powerline network.

For this you need to pair the Charge Control C with your HomePlug compatible companion.

There are currently two different ways of pairing PLC devices with Charge Control C.

**Putting into service the Powerline connection by means of the push button method**

The push button pairing method is the most famous method. Charge Control C has no push button to activate this method, but the push button can be simulated with on-board tools.

    1. Press the powerline security button on the companion (e.g. wallplug adapter) to start the pairing process.
    2. Run the following command on Charge Control C - this emulates pressing the pairing button of the evaluation board: 
        .. code-block:: linux
         :align: left
         root@tarragon:˜ $ plctool −B join −i eth2
         eth2 00:B0:52:00:00:01 Join Network
         eth2 00:01:87:FF:FF:2B Joining ...
         root@tarragon:˜ $

    3. You should see the remote powerline adapter after a short while:
        .. code-block:: linux
         :align: left

         root@tarragon:˜ $ plcstat −t −i eth2
         P/L NET TEI −−−−−− MAC −−−−−− −−−−−− BDA −−−−−−  TX  RX CHIPSET FIRMWARE
         LOC STA 002 00:01:87:FF:FF:2B 00:01:87:FF:FF:FE n/a n/a QCA7000 MAC−QCA7000−1.1.3.1531−00−20150204−CS
         REM CCO 001 00:0B:3B:AA:86:55 E0:CB:4E:ED:1F:53 009 009 INT6400 INT6000−MAC−4−1−4102−00−3679−20090724−FINAL−B
         root@tarragon:˜ $
    
    4. You have successfully created a powerline connection.

**Putting into service the Powerline connection using software**

You can also add the device by means of DAK (Device Access Key, often also called device password or security ID) to an existing powerline network or couple it with a powerline Ethernet adapter. The DAK is indicated in the device labels 2D DataMatrix code of the Charge Control C. It consists of 4 x 4 letters, separated by hyphens.

1. Note this DAK and install the device in the power grid.
2. After the device has been put into service, you can add the device to the existing powerline network using the software of your powerline companion (e.g. FRITZ!Powerline or Devolo Cockpit for powerline ethernet adapter as powerline companion).
3. In doing so, the DAK is to be entered.
4. Please refer to the documentation of your powerline companion for further information about this process.  

Control Pilot / Proximity Pilot
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Locking motors
^^^^^^^^^^^^^^

Relays
^^^^^^
1-Wire
^^^^^^
Digital Input & Output
^^^^^^^^^^^^^^^^^^^^^^
4-wire-fan
^^^^^^^^^^

Board connections
-----------------

Device Marking
--------------
