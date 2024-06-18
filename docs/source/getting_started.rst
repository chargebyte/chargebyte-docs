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
    :width: 500pt
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

Starting and Monitoring the Charging Process
--------------------------------------------

Next Steps
----------
