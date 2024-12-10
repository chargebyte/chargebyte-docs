Connecting via SSH or Serial Interface
--------------------------------------

For debugging, there are two ways to connect the developer computer to the Charge controller: via SSH
or via serial interface. The following sections explain how to connect to the Charge controller using
PuTTY. You can also use other terminal programs (like e.g. MobaXTerm) to connect to the
Charge controller.


SSH Connection with PuTTY
^^^^^^^^^^^^^^^^^^^^^^^^^

Here are the steps to connect to the Charge controller via SSH using PuTTY:

#. Install PuTTY on your computer. You can download PuTTY from the following link:
   `PuTTY Download <https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html>`_.
#. Connect the Charge controller over Ethernet to your computer.
#. Start PuTTY and enter the IPv4 fallback address "169.254.12.53" of the Charge controller in
   the "Host Name (or IP address)" field (See figure :ref:`PuTTY SSH Configuration <PuTTY_Serial_Configuration_2>`).
#. Click on "Save" to save the configuration and then click on "Open" to start the connection.
#. A PuTTY Security Alert window will appear. Click on "Accept" to continue.
#. Enter the username "root" and the password "zebematado" to log in to the Charge controller.

.. note::
   The username can also be stored under "Connection -> Data -> Auto-login username" in the
   PuTTY configuration.

.. note::
   It is also possible to install an SSH key on the Charge controller to log in without a
   password. Please look online for instructions on how to do this on a Linux system.

.. figure:: _static/images/putty_config_ssh_fallback_ip.png
    :width: 300pt

    Figure: PuTTY SSH Configuration


Serial Connection with PuTTY
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are the steps to connect to the Charge controller via serial interface using PuTTY:

#. Install PuTTY on your computer. You can download PuTTY from the following link:
   `PuTTY Download <https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html>`_.
#. Connect the Charge controller to your computer via USB to serial adapter.
#. Start PuTTY and configure the COM port of the USB to serial adapter (e.g. "COM1") in the
   "Serial line" field.
   Note: You can find the COM port of the USB to serial adapter in the Windows Device Manager
   under "Ports (COM & LPT)".
#. Switch to Connection -> Serial configuration and set the "Speed" to 115200, "Data bits" to 8,
   "Stop bits" to 1, "Parity" to "None" and "Flow control" to "None" (See figure
   :ref:`PuTTY Serial Configuration <PuTTY_Serial_Configuration_1>`).
#. Switch back to the "Session" and click on "Save" to save the configuration
   (See figure :ref:`PuTTY Save Serial Connection <PuTTY_Serial_Configuration_2>`).
#. Click on "Open" to start the connection.
#. Now a black window will appear. Press enter to get the login prompt.
#. Enter the username "root" and the password "zebematado" to log in to the Charge controller.

.. figure:: _static/images/putty_config_serial_1.png
    :width: 300pt
    :name: PuTTY_Serial_Configuration_1

    Figure: PuTTY Serial Configuration

.. figure:: _static/images/putty_config_serial_2.png
    :width: 300pt
    :name: PuTTY_Serial_Configuration_2

    Figure: PuTTY Save Serial Connection
