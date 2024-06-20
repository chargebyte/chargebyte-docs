.. getting_started.rst:

Getting Started
===============

This chapter is intended to help you get started as easily as possible with EV charging together
with the Charge Control C and the EVerest charging stack. For this purpose, a basic AC PWM charger
is set up as an example and explained step by step.


Setting Up the Hardware
------------------------

Hardware Components
^^^^^^^^^^^^^^^^^^^

The following hardware components are required to set up the basic AC PWM charger:

- Charge Control C (100, 200 or 300)
- 12 V DC Power Supply
- Contactor (TODO: Link to supported contactors)
- IEC 62196 Type 2 three-phase EV charging socket outlet
- Ethernet cable for SSH connection or USB to serial adapter for serial connection
- IEC 62196 Type 2 EVSE Test Adapter (e.g. Metrel or Benning) to simulate the EV


Hardware Overview
^^^^^^^^^^^^^^^^^

The following figure shows the basic setup of the AC PWM charger with the Charge Control C:

.. image:: _static/images/ac_pwm_charger_ccc_setup.svg
    :width: 500pt
    :align: center

.. raw:: html

   <div style="text-align: center;">
      Figure: Basic Setup of the AC PWM Charger with the Charge Control C
   </div>

Note: Before you start setting up the setup, please check whether the HW components used are also
listed in `Hardware Components section`_.

.. _Hardware Components section: #hardware-components


First Startup
-------------

Boot Process
^^^^^^^^^^^^

Here some key points about the boot process of the Charge Control C:

- The file system basically consists of three ext4 partionions. Two partitions are used as slots for
  RAUC update process. The third partion is not not touched by the RAUC update process and is usualy
  used to the store update bundles, logs, etc. For more information about the RAUC update process
  see the TODO: ADD LINK HERE section.
- After connecting the Charge Control C to the power supply, the U-Boot bootloader starts the
  currently active slot managed by RAUC.
- The LED status indicators on the Charge Control C provide information about the current status of
  the boot process.
- EVerest is automatically started with the default configuration after the boot process is
  completed. The inital configuration is explained in the `Initial Configuration`_ section.


Understanding LED Status Indicators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Now you can plug in the Charge Control C to the power supply. The LED status indicators on the
Charge Control C provide information about the current status of the boot process. The following
table shows the meaning of the LED status indicators:

.. raw:: html
 
   <div style="text-align: center;">
     Table: Charge Control C LED Status Indicators
   </div>

+--------------------------+---------------------------------+------------------------------------+
| State                    | LED indication                  | Behavior                           |
+==========================+=================================+====================================+
| Bootloader active        | LED1 (green)                    | off                                |
|                          +---------------------------------+------------------------------------+
|                          | LED2 (yellow)                   | off                                |
|                          +---------------------------------+------------------------------------+
|                          | LED3 (red)                      | permanently on for approx. 3 sec.  |
+--------------------------+---------------------------------+------------------------------------+
| Boot process running     | LED1 (green)                    | blinking for approx. 15 sec.       |
|                          +---------------------------------+------------------------------------+
|                          | LED2 (yellow)                   | off                                |
|                          +---------------------------------+------------------------------------+
|                          | LED3 (red)                      | blinking                           |
+--------------------------+---------------------------------+------------------------------------+
| Operating system running | LED1 (green)                    | permanently on                     |
|                          +---------------------------------+------------------------------------+
|                          | LED2 (yellow)                   | off                                |
|                          +---------------------------------+------------------------------------+
|                          | LED3 (red)                      | blinking                           |
+--------------------------+---------------------------------+------------------------------------+


Connecting via SSH or Serial Interface
--------------------------------------

There are two ways to connect to the Charge Control C: via SSH or via serial interface. The
following sections explain how to connect to the Charge Control C using PuTTY. You can also use
other terminal programs (like e.g. MobaXTerm) to connect to the Charge Control C.


SSH Connection with PuTTY
^^^^^^^^^^^^^^^^^^^^^^^^^

Here are the steps to connect to the Charge Control C via SSH using PuTTY:

#. Install PuTTY on your computer. You can download PuTTY from the following link:
   `PuTTY Download <https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html>`_.
#. Connected the Charge Control C over Ethernet to your computer
#. Start PuTTY and enter the IPv4 fallback address "169.254.12.53" of the Charge Control C in
   the "Host Name (or IP address)" field (See figure :ref:`PuTTY SSH Configration <PuTTY_Serial_Configuration_2>`)..
#. Click on "Save" to save the configuration ans then click on "Open" to start the connection.
#. An PuTTY Security Alert window will appear. Click on "Accept" to continue.
#. Enter the username "root" and the password "zebematado" to log in to the Charge Control C.

Note: The user name can also be stored under "Connection -> Data -> Auto-login username" in the
PuTTY configuration.

Note: It is also possible to install a SSH key on the Charge Control C to log in without a
password. For more information, see the TODO: Link section.

.. image:: _static/images/putty_config_ssh_fallback_ip.png
    :width: 300pt
    :align: center
    :name: PuTTY_SSH_Configuration

.. raw:: html
 
   <div style="text-align: center;">
     Figure: PuTTY SSH Configration
   </div>


Serial Connection with PuTTY
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are the steps to connect to the Charge Control C via serial interface using PuTTY:

#. Install PuTTY on your computer. You can download PuTTY from the following link:
   `PuTTY Download <https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html>`_.
#. Connect the Charge Control C to your computer via USB to serial adapter.
#. Start PuTTY and configure the COM port of the USB to serial adapter (e.g. "COM1") in the
   "Serial line" field.
   Note: You can find the COM port of the USB to serial adapter in the Windows Device Manager
   under "Ports (COM & LPT)".
#. Switch to Connection -> Serial configuration and set the "Speed" to 115200, "Data bits" to 8,
   "Stop bits" to 1, "Parity" to "None" and "Flow control" to "None" (See figure
   :ref:`PuTTY Serial Configuration <PuTTY_Serial_Configuration_1>`).
#. Switch back to the "Session" configuration and click on "Save" to save the configuration
   (See figure :ref:`PuTTY Save Serial Connection <PuTTY_Serial_Configuration_2>`).
#. Click on "Open" to start the connection.
#. Now a black window will appear. Press enter to get the login prompt.
#. Enter the username "root" and the password "zebematado" to log in to the Charge Control C.

.. image:: _static/images/putty_config_serial_1.png
    :width: 300pt
    :align: center
    :name: PuTTY_Serial_Configuration_1

.. raw:: html

   <div style="text-align: center;">
     Figure: PuTTY Serial Configuration
   </div>

.. image:: _static/images/putty_config_serial_2.png
    :width: 300pt
    :align: center
    :name: PuTTY_Serial_Configuration_2

.. raw:: html

   <div style="text-align: center;">
     Figure: PuTTY Save Serial Connection
   </div>


Initial Configuration
---------------------

Now you are connected to the Charge Control C and we can have a deeper look at the initial
configuration.

The conifguration files of the EVerest charging stack are stored in the directory "/etc/everest".
EVerest uses the YAML format for the configuration files. The default configuration file of EVerest
is the config.yaml. If you take a look at the content of the configuration file, you will see that
there is only a reference to the "bsp-only.yaml" file.

Note: In case you create an own configuration file, you can also store it in the "/etc/everest"
directory and create a simbolic link to it like
(ln -sf /etc/everest/my-config.yaml /etc/everest/config.yaml).

.. code-block:: bash

   root@chargecontrolc:~# ls -l /etc/everest
   total 8
   -rw-r--r-- 1 root root  0 Jan  1  1970 bsp-only.yaml
   lrwxrwxrwx 1 root root 12 Jan  1  1970 my-config.yaml  -> config.yaml

Let's take a look at the content of the bsp-only.yaml configuration file. This file is already
prepared for the basic AC PWM charger setup.

Just type "less /etc/everest/bsp-only.conf" to see the content of the configuration file:

.. literalinclude:: ../../src/config/bsp-only.yaml
   :language: yaml
   :linenos:

In general, the EVerest charging stack consists of different modules and each of which fulfils a
specific task. An EVerest module provides and requests interfaces. The configuration file shows
which EVerest modules are activated, how they are configured and how they are connected to each
other over the interfaces.

However, not all configuration parameters of the modules are shown here. Only the configuration
parameters that do not match the default configuration of the respective module need
to be specified here. Depending on the installed hardware components, the configuration file may
need to be adapted. The hardware related tasks are maninly handled by the CbTarragonDriver module.
The configuration of the CbTarragonDriver module can be found in "/usr/libexec/everest/modules/cbTarragonDriver"
directory.

Each module has a specific configuration file, this file is called "mainifest.yaml" and is stored 
in the main directory of the module.
Here you can also see all other configuration parameters of the respective module. 
Now please type "less /usr/libexec/everest/modules/cbTarragonDriver/manifest.yaml" to see the
content of the configuration file and check if the configuration fits to your hardware setup.

If you want to change a configuration parameter of a module, which is not part of your EVerest yaml
configuration file, just copy the specific configuration key from the "manifest.yaml" file of the
module to the module specific "config_module" space in your EVerest configuration and adjust the
value. Please note if you change it directly in the "manifest.yaml" file of a mondule, the changes
will be get lost after a software update.

Here is excerpt of an EVerst configuration to change the parameter "connector_type" to
"IEC62196Type2Cable" of the CbTarragonDriver module in the EVerest.

.. code-block:: sh

  tarragon_bsp:
    module: CbTarragonDriver
    config_module:
      contactor_1_feedback_type: none
      relay_2_name: none
      connector_type: IEC62196Type2Cable


After adjusting the configuration file, you can restart the EVerest charging stack to apply the
changes. Just type "systemctl restart everest" to restart the EVerest charging stack.

Note: You can also use the `EVerest admin panel <https://github.com/EVerest/everest-admin-panel>`_
to adjust the EVerest configurationin a GUI. This tool must be currently installed manually on your
developer computer, because the recources on the board are limited.

Note: If you have made a mistake in the configuration file, the EVerest charging stack will not
start. Therefore, it is recommended to back up the original configuration file before making
changes.

Starting and Monitoring the Charging Process
--------------------------------------------

Before we are starting the first charging session, it is possible to monitor the charging process
of the EVerest charging stack. Just type "journalctl -f -u everest -n 100" to see the last 100 log
messages of the EVerest charging stack.

The EVerst log should look like this:

.. code-block:: sh

   root@tarragon:~# journalctl -f -u everest -n 100
   2024-06-19T19:26:08.986317+0200 tarragon systemd[1]: Started EVerest.
   2024-06-19T19:26:09.079641+0200 tarragon manager[11978]: [INFO] manager          ::   ________      __                _
   2024-06-19T19:26:09.086179+0200 tarragon manager[11978]: [INFO] manager          ::  |  ____\ \    / /               | |
   2024-06-19T19:26:09.086179+0200 tarragon manager[11978]: [INFO] manager          ::  | |__   \ \  / /__ _ __ ___  ___| |_
   2024-06-19T19:26:09.086179+0200 tarragon manager[11978]: [INFO] manager          ::  |  __|   \ \/ / _ \ \'__/ _ \/ __| __|
   2024-06-19T19:26:09.086179+0200 tarragon manager[11978]: [INFO] manager          ::  | |____   \  /  __/ | |  __/\__ \ |_
   2024-06-19T19:26:09.086179+0200 tarragon manager[11978]: [INFO] manager          ::  |______|   \/ \___|_|  \___||___/\__|
   2024-06-19T19:26:09.086179+0200 tarragon manager[11978]: [INFO] manager          ::
   2024-06-19T19:26:09.086179+0200 tarragon manager[11978]: [INFO] manager          :: Using MQTT broker localhost:1883
   2024-06-19T19:26:09.188450+0200 tarragon manager[11979]: [INFO] everest_ctrl     :: Launching controller service on port 8849
   2024-06-19T19:26:09.254120+0200 tarragon manager[11978]: [INFO] manager          :: Loading config file at: /etc/everest/bsp-only.yaml
   2024-06-19T19:26:09.818473+0200 tarragon manager[11978]: [INFO] manager          :: Config loading completed in 723ms
   2024-06-19T19:26:14.176961+0200 tarragon manager[11997]: [INFO] energy_manager:  :: Module energy_manager initialized [3968ms]
   2024-06-19T19:26:14.317279+0200 tarragon manager[12000]: [INFO] tarragon_dig_in  :: chargebyte\'s Tarragon driver for configuration of digital input reference PWM (version: 0.10.0)
   2024-06-19T19:26:14.373497+0200 tarragon manager[11998]: [INFO] grid_connection  :: Module grid_connection_point initialized [4076ms]
   2024-06-19T19:26:14.373497+0200 tarragon manager[12000]: [INFO] tarragon_dig_in  :: Enabled digital input reference PWM 2084000.pwm, channel 0 with period 40000 and duty cycle 20000
   2024-06-19T19:26:14.373497+0200 tarragon manager[12000]: [INFO] tarragon_dig_in  :: Module tarragon_dig_in_ref initialized [4066ms]
   2024-06-19T19:26:14.473667+0200 tarragon manager[11995]: [INFO] api:API          :: Module api initialized [4343ms]
   2024-06-19T19:26:14.548188+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: Control Pilot Observation Thread started
   2024-06-19T19:26:14.567183+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: Primary contactor feedback type: \'none\'
   2024-06-19T19:26:14.568825+0200 tarragon manager[11999]: [WARN] tarragon_bsp:Cb CbTarragonContactorControl::CbTarragonContactorControl(const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&) :: The primary contactor has the feedback pin not connected. This is not recommended.
   2024-06-19T19:26:14.570871+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: chargebyte\'s Hardware EVerest Modules (version: 0.10.0)
   2024-06-19T19:26:14.573109+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: Module tarragon_bsp initialized [4248ms]
   2024-06-19T19:26:14.576991+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: Contactor Handling Thread started
   2024-06-19T19:26:14.650925+0200 tarragon manager[11996]: [INFO] connector:EvseM  :: Module connector initialized [4429ms]
   2024-06-19T19:26:14.710204+0200 tarragon manager[11978]: [INFO] manager          :: 🚙🚙🚙 All modules are initialized. EVerest up and running [5638ms] 🚙🚙🚙
   2024-06-19T19:26:14.881674+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: Read PP ampacity value: None (U_PP: 3297 mV)
   2024-06-19T19:26:14.889409+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: Proximity Pilot Observation Thread started
   2024-06-19T19:26:14.957703+0200 tarragon manager[11996]: [INFO] connector:EvseM  :: Max AC hardware capabilities: 32A/3ph
   2024-06-19T19:26:15.164664+0200 tarragon manager[11996]: [INFO] connector:EvseM  :: 🌀🌀🌀 Ready to start charging 🌀🌀🌀
   2024-06-19T19:26:15.322579+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: handle_enable: Setting new duty cycle of 100.00%
   2024-06-19T19:26:15.333875+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: CP state change from PowerOn to A, U_CP+: 11947 mV, U_CP-: 7 mV
   2024-06-19T19:26:15.459775+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: handle_pwm_off: Setting new duty cycle of 100.00%
   2024-06-19T19:26:15.632804+0200 tarragon manager[11999]: [INFO] tarragon_bsp:Cb  :: handle_pwm_off: Setting new duty cycle of 100.00%

Before plugging in the IEC 62196 Type 2 EVSE Test Adapter, please make sure that the CP state of the
EVSE Test Adapter is set to "B" and the current limit (adjustable via the PP state) is configured to
16A. Now you are ready to start the first charging session with EVerest and you can plugin the IEC
62196 Type 2 EVSE Test Adapter.

After plugging in the IEC 62196 Type 2 EVSE Test Adapter, a CP state change from "A" to "B" should
be visible in the EVerest log. Per default the authentication is disabled in the bsp-only.yaml.
The duty cycle shall directly switch from 100% to 20%.

The last EVerest log messages should look like this:

.. code-block:: sh


   2024-06-20T07:45:49.386995+0200 tarragon manager[18942]: [INFO] tarragon_bsp:Cb  :: CP state change from A to B, U_CP+: 9637 mV, U_CP-: -2 mV
   Read PP ampacity value: A_16 (U_PP: 3297 mV)
   2024-06-20T07:45:49.781308+0200 tarragon manager[18942]: [INFO] tarragon_bsp:Cb  :: handle_pwm_on: Setting new duty cycle of 26.67%

