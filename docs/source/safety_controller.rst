.. _safety_controller.rst:

Safety Controller
=================

Overview
--------

The Charge Control Y is equipped with an additional MCU (aka Safety Controller) which is responsible for
managing all low-level aspects which are critical for electrical safety. The firmware for this MCU is
developed by chargebyte and is not open-source. The Charge Control Y is shiped with the safety controller firmware
preinstalled.

The host controller firmware, e.g. the Linux system, communicates with the safety controller using an UART.
On Linux side, this is UART interface ``/dev/ttyLP2``. The communication with the safety controller firmware
over this UART requires a proprietary protocol, see the following chapter. The required UART settings are listed
in the following table.

+-----------------+-------------+
| Setting         | Value       |
+=================+=============+
| Linux Interface | /dev/ttyLP2 |
+-----------------+-------------+
| Baudrate        | 115200      |
+-----------------+-------------+
| Databits        | 8           |
+-----------------+-------------+
| Parity          | none        |
+-----------------+-------------+
| Stopbits        | 1           |
+-----------------+-------------+


System Architecture
-------------------

.. figure:: _static/images/system_architecture_ccy.svg
   :width: 1000pt

   Simplified System Architecture for the Safety Controller on the Charge Control Y

The safety controller manages the Charge Enable (CE) line, acting as a critical interface for monitoring
Insertion Detection (ID) as well as Emergency Input and temperature sensors and therefore controlling the
HV ready switch in accordance with EV safety standards.
Its core function is to **enforce safe operating states** based on system diagnostics and environmental conditions.


Fault Detection & Safety Response
---------------------------------

When an error is detected — such as a fault in the system, a triggered emergency input, or a thermal violation — the
controller transitions to **State EC**, a fail-safe state that prevents further system operation to protect both
the hardware and the user.


HV Ready Enablement
-------------------

The controller verifies that **no system errors are present** and that the CE line is in **State C**.
Only under these safe conditions it does enable the HV Ready signal, which may be used to energize the HV interlock or
permit charging/operation.


Emergency Input
---------------

The input is active-low. This means an emergency stop needs to pull the input to Gnd (EVSE).


Temperature Monitoring
----------------------

The simplified system architecture shows only one temperature input. In the real system, there are 4 independent
temperature measurement circuits for PT1000 sensors. The safety software monitors the temperature circuit for
hardware errors and for overtemperaure. The temperature threshold can be parameterized.


Reset Behaviour and Controller States
-------------------------------------

The safety controller starts in an initialization state, to give the peripherals time to reach a defined state.
It leaves the initialization state to a running state, after the reception of the first UART message from the host.
Only periodic messages leave the init state. With the reception of inquiry messages, the safety controller stays in
initialization. This gives the option to fetch version information in the init state. In running state, it monitors the
peripherals and sends out UART messages. If any error occurs, the system goes into safe state.
This state can only be left by a reset.

.. figure:: _static/images/safety_controller_states.svg
   :width: 1000pt

.. include:: safety_controller_uart.rst

.. include:: everest_bsp.rst
