.. _troubleshooting.rst:

Troubleshooting
===============

Frequently Asked Questions
--------------------------

.. contents::
   :local:

Does the Charge SOM have a CE certification?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Currently, the Charge SOM doesn't have any certification yet.


Does the Charge SOM have Wifi support?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Charge SOM doesn't have builtin Wifi support, but it provides suitable
interfaces (SDIO / USB 2.0 ) via its connectors. For instance the Charge SOM
Single Channel DC Carrier Board provides a mini PCIe connector, which is
connected to USB.


Is it possible to use the Charge SOM as an EV simulator?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Charge SOM hardware is not designed to be used as an EV simulator. Please refer to our
`website <https://www.chargebyte.com/>`_ for more suitable products.


I want to control EVerest via CAN, how can I achieve this?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Currently there is no such EVerest module available, you will need to implement it on your own.

But at least there is are `DC power supply modules <https://github.com/EVerest/everest-core/tree/main/modules/HardwareDrivers/PowerSupplies>`_
and a `library <https://github.com/EVerest/everest-core/tree/main/lib/everest/can_dpm1000>`_,
which uses the CAN interface. This might help as a starting point.


How can I access the GPIOs under Linux?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Since the GPIO sysfs interface /sys/class/gpio has been deprecated since Linux 4.8,
we recommend the usage of chardev GPIO and libgpiod. The modification of the bias
settings via libgpiod is not yet implemented, so it needs to be done via device tree.


My application depends on libgpiod but requires GPIO chip and line, how can I figure them out?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For such applications which doesn't support GPIO line names, you can use the following:

.. code-block:: console

   root@chargesom:/# cat /sys/kernel/debug/gpio
   gpiochip0: GPIOs 512-541, parent: platform/43810000.gpio, 43810000.gpio:
   gpio-512 (SPI_PLC_nCS0        |spi1 CS0            ) out hi ACTIVE LOW
   gpio-519 (                    |int                 ) in  lo IRQ
   ...

The GPIO line is calculated as following:

.. code-block::

   Line = GPIO number - GPIO chip offset
   Line = 519         - 512
   Line = 7


What is the difference between CHSTOP_IN and SAFETY_ESTOPx?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The signal CHSTOP_IN is connected to the i.MX93 SoC and could be used to gracefully stop the charging process. So it is not designed
for timing critical use cases. Currently there is no EVerest module, which is able to handle this signal. This work is pending.

In order to realize realtime emergency stop behavior use the SAFETY_ESTOPx signals, which are connected to the safety processor.


Is there a Linux command to check for connection related CAN issues?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Yes

.. code-block:: console

   root@chargesom:/# ip -details -statistic link show can0


How can I list the available UARTs?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

All UARTs of the i.MX93 are handled by the fsl-lpuart driver, so the following
command should list all available UARTs. Please keep in mind that Linux starts
counting from zero (ttyLP0 = UART1, ...).

.. code-block:: console

   root@chargesom:/# cat /proc/tty/driver/fsl-lpuart
   serinfo:1.0 driver revision:
   0: uart:FSL_LPUART mmio:0x44380010 irq:17 tx:9932 rx:0 RTS|CTS|DTR|DSR|CD
   2: uart:FSL_LPUART mmio:0x42570010 irq:18 tx:12966 rx:26572 RTS|CTS|DTR|DSR|CD
   3: uart:FSL_LPUART mmio:0x42580010 irq:19 tx:936 rx:617 RTS|CTS|DTR|DSR|CD
   4: uart:FSL_LPUART mmio:0x42590010 irq:20 tx:0 rx:0 CTS|DSR|CD


How can I list the available I²C interfaces?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

All I²C interfaces are available via I²C device driver. Please keep in mind that
Linux starts counting from zero (i2c-0 = I2C1, ...).

.. code-block:: console

   root@chargesom:/# i2cdetect -l
   i2c-0   i2c             44340000.i2c                            I2C adapter
   i2c-1   i2c             44350000.i2c                            I2C adapter
   i2c-2   i2c             42530000.i2c                            I2C adapter


How can I print the current pin/pad control settings (e.g. bias, drive strength)?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The current PAD control settings are available under Linux only via debugfs,
but this requires an equivalent pinctrl setting within the device tree:

.. code-block:: console

   root@chargesom:/# cat /sys/kernel/debug/pinctrl/443c0000.pinctrl/pinconf-pins
   Pin config settings per pin
   Format: pin (name): configs
   pin 0 (IMX93_IOMUXC_DAP_TDI): 0x31e
   ...


Which LVDS displays have been tested with the Charge SOM EVB?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The `Distec DD-0700-MC01 <https://www.fortec-integrated.de/en/products/tft-components/tft-displays/detail/fortec-integrated/dd-0700-mc01/>`_
(7 inch, 800x480 resolution) has been tested with the Charge SOM EVB.


I like to create my own DT overlay. Is there an example?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Yes, please have a look at this `commit <https://github.com/chargebyte/linux/commit/125a587a0cf7e8d9db1fdddf9383a67c2b46d107>`_ .


Where can I find the device tree sources of the Charge SOM?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The device tree sources of the Charge SOM are divided into multiple layers:

.. list-table::
   :header-rows: 1

   * - Part
     - Level
     - Layer
     - Filename
   * - i.MX93
     - 0
     - SoC
     - `imx93.dtsi <https://github.com/chargebyte/linux/blob/v6.6.23-2.0.0-phy-cb/arch/arm64/boot/dts/freescale/imx93.dtsi>`_
   * - phyCORE-i.MX93
     - 1
     - SoM
     - `imx93-phycore-som.dtsi <https://github.com/chargebyte/linux/blob/v6.6.23-2.0.0-phy-cb/arch/arm64/boot/dts/freescale/imx93-phycore-som.dtsi>`_
   * - Charge SOM
     - 2
     - SoM
     - `imx93-charge-som.dtsi <https://github.com/chargebyte/linux/blob/v6.6.23-2.0.0-phy-cb/arch/arm64/boot/dts/freescale/imx93-charge-som.dtsi>`_
   * - Charge SOM Single Channel DC Carrier Board
     - 3
     - Board
     - `imx93-charge-som-dc-evb.dts <https://github.com/chargebyte/linux/blob/v6.6.23-2.0.0-phy-cb/arch/arm64/boot/dts/freescale/imx93-charge-som-dc-evb.dts>`_


How can I access the EVerest admin panel on Charge SOM?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Currently, the Charge SOM does not have integrated the `EVerest admin panel <https://github.com/EVerest/everest-admin-panel>`_
Please use your development environment to set up your configuration file. Alternatively, you can use a plain text
editor.


Does EVerest on Charge SOM support ISO 15118-20 yet?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The required module for ISO 15118-20 has been included in the image since the Charge SOM EVerest release 0.2.0.
Please note that the implementation is still under development and integrated into the image only for test purposes.

EVerest integrates the `libiso15118 <https://github.com/EVerest/libiso15118>`_ library to provide support for ISO 15118-20.
Here you can find more information about the current status of the ISO 15118-20 implementation.
Please note, however, that the range of functions described in the linked `libiso15118` library documentation may not
correspond to those already integrated in EVerest, as the library has not yet been fully integrated.
Implementation gaps may exist, particularly in the case of BPT (bidirectional power transfer) functionality.


How do I set up OCPP 2.0.1 on Charge SOM with EVerest?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To support OCPP 2.0.1, the EVerest OCPP201 module must be integrated into the EVerest configuration.
This module uses the `libocpp library <https://github.com/EVerest/libocpp>`_ to implement the OCPP 2.0.1
protocol.
The `OCPP201 module documentation <https://github.com/EVerest/everest-core/blob/main/modules/EVSE/OCPP201/doc.rst>`_
already contains some information about the module parameters, the provided and required interfaces,
and the initial creation of the OCPP 2.0.1 database.

The most important points are summarised here:

1. The OCPP201 module must be included in your EVerest configuration.
2. The CbSystem module can be used to fulfill the requirement of the system interface.
3. While configuring the OCPP 2.0.1 module, ensure that you are using OCPP configuration and database
   paths which are covered by the update mechanism. The following paths are recommended:

   - `CoreDatabasePath`: /var/lib/everest/ocpp201
   - `DeviceModelDatabasePath`: /var/lib/everest/ocpp201/device_model_storage.db
   - `DeviceModelConfigPath`: /var/lib/everest/ocpp201/component_config

   Otherwise, if you don't want to use a persistent storage, you can also deploy those files in your
   RAUC image.
4. The `CoreDatabasePath` is used, among other things, to store OCPP transaction data.
5. The OCPP 2.0.1 device model initialization is done automatically by the OCPP201 module after the
   first start of EVerest. The database is stored the `DeviceModelDatabasePath`.
6. The component config files are stored in the `DeviceModelConfigPath`. Component config files are
   used to initialize or update the device model database. To update a component config file, just
   place a `component config file <https://github.com/EVerest/libocpp/tree/main/config/v2/component_config>`_
   in the same directory structure in the DeviceModelConfigPath and change the values accordingly.
   Important keys of the component config files are:

   - `standardized/InternalCtrlr.json: ChargePointId`: In "attributes" adapt the "value" key to configure the ChargePointId. Used to identify the Charging Station.
   - `standardized/InternalCtrlr.json: NetworkConnectionProfiles`: In "attributes" adapt the "ocppCsmsUrl" key. The URL in "ocppCsmsUrl" is used to connect to the CSMS.
   - `standardized/SecurityCtrlr.json: SecurityCtrlrIdentity`: In "attributes" adapt the "value" key to configure the SecurityCtrlrIdentity. It is the Charging Station identity.

   For further information about the device model initialization, please refer to the
   `libocpp documentation <https://github.com/EVerest/libocpp/blob/main/doc/v2/ocpp_201_device_model_initialization.md>`_.


I tried to compile chargebyte's Hardware EVerest Modules, but it fails to build. How can I fix this?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The EVerest mainline development is very dynamic and doesn't guarantee any
stable API along the EVerest modules. So after almost every EVerest release,
chargebyte needs to adapt their modules to the latest API changes.

Please have a look at the `compatibility matrix <https://github.com/chargebyte/everest-chargebyte/blob/main/README.md>`_
to see which EVerest release works with which chargebyte EVerest Modules release.


I would like to implement a custom Modbus device in EVerest. Where should I start?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

EVerest already has a module which takes care of Modbus communication. Please have a look at
`SerialCommHub <https://everest.github.io/nightly/_generated/modules/SerialCommHub.html>`_,
and let your module interact with this module via the `serial_communication_hub` interface.

.. _contact:

.. include:: ../../includes/troubleshooting_contact.inc
