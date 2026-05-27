.. _connecting-via-ssh-or-serial-interface:

Connecting via SSH or Serial Interface
--------------------------------------

For debugging, there are two ways to connect the developer computer to the charge controller: via SSH
or via serial interface. The following sections explain how to connect to the charge controller using
PuTTY. You can also use other terminal programs (like e.g. MobaXTerm) to connect to the
the charge controller.

.. important::
   On the very first boot, SSH access is disabled and no password is set for the ``root`` user.
   A factory reset also deletes the root password, so a new root password must be set afterward.
   Before connecting via SSH, enable SSH access in the WebUI under "SSH Configuration". You must
   also set a root password either on the same WebUI page or through the serial console. When
   logging in as ``root`` through the serial console for the first time, you will be prompted to
   set a password.


SSH Connection with PuTTY
^^^^^^^^^^^^^^^^^^^^^^^^^

Here are the steps to connect to the charge controller via SSH using PuTTY:

#. Install PuTTY on your computer. You can download PuTTY from the following link:
   `PuTTY Download <https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html>`_.
#. Connect the charge controller over Ethernet to your computer.
#. Start PuTTY and enter the IPv4 fallback address "169.254.12.53" of the charge controller in
   the "Host Name (or IP address)" field (See figure :ref:`PuTTY SSH Configuration <PuTTY_Serial_Configuration_2>`).
#. Click on "Save" to save the configuration and then click on "Open" to start the connection.
#. A PuTTY Security Alert window will appear. Click on "Accept" to continue.
#. Enter the username "root" and the password previously set through the serial console or the
   WebUI to log in to the charge controller.

.. note::
   The username can also be stored under "Connection -> Data -> Auto-login username" in the
   PuTTY configuration.

.. note::
   It is also possible to install an SSH key on the charge controller to log in without a
   password. Please look online for instructions on how to do this on a Linux system.

.. figure:: _static/images/putty_config_ssh_fallback_ip.png
   :width: 300pt

   PuTTY SSH Configuration


Serial Connection with PuTTY
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are the steps to connect to the charge controller via serial interface using PuTTY:

#. Install PuTTY on your computer. You can download PuTTY from the following link:
   `PuTTY Download <https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html>`_.
#. Connect the charge controller to your computer via a USB-to-serial adapter.
#. Start PuTTY and configure the COM port of the USB-to-serial adapter (e.g. "COM1") in the
   "Serial line" field.
   Note: You can find the COM port of the USB-to-serial adapter in the Windows Device Manager
   under "Ports (COM & LPT)".
#. Switch to Connection -> Serial configuration and set the "Speed" to 115200, "Data bits" to 8,
   "Stop bits" to 1, "Parity" to "None" and "Flow control" to "None" (See figure
   :ref:`PuTTY Serial Configuration <PuTTY_Serial_Configuration_1>`).
#. Switch back to the "Session" and click on "Save" to save the configuration
   (See figure :ref:`PuTTY Save Serial Connection <PuTTY_Serial_Configuration_2>`).
#. Click on "Open" to start the connection.
#. Now a black window will appear. Press enter to get the login prompt.
#. Enter the username "root" to log in to the charge controller. On the very first boot, no root
   password is set and you will be prompted to define one. For subsequent logins, enter the
   password you have set.

.. figure:: _static/images/putty_config_serial_1.png
   :width: 300pt
   :name: PuTTY_Serial_Configuration_1

   PuTTY Serial Configuration

.. figure:: _static/images/putty_config_serial_2.png
   :width: 300pt
   :name: PuTTY_Serial_Configuration_2

   PuTTY Save Serial Connection
