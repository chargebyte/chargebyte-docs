.. _hardware.rst:

########
Hardware
########

Since the Charge SOM itself is a module which cannot be used without a carrier board,
the following sections refer to the Charge SOM Evaluation Board as an example.


***************
Wiring Overview
***************

.. figure:: _static/images/charge_som_hw_wiring_diagram.svg
   :width: 1000pt

   Wiring Overview Diagram for Charge SOM EVB

This wiring diagram shows an overview of all components which are required at minimum
to build a DC charging station:

* A PSU as 12V DC supply for the Charge SOM EVB
* A controllable power module (rectifier) for converting AC grid power into DC power to the EV.
  In this example, this power module is connected via CAN interface to the Charge SOM EVB which
  is a typical interface type for such devices.
* A DC power meter for measuring the transferred energy. In this example, this electricity meter
  is connected via RS-485 bus and it is assumed that the meter supports the Modbus protocol.
  However, there exists also meters which use Ethernet and other protocols.
* An insulation monitoring device (IMD). In the drawing, only the safety related connection is
  shown, that means that the output pin of the IMD (which switches on insulation faults) is wired
  to an input pin of the Charge SOM. The state of this input pin is observed by the onboard
  safety controller of the Charge SOM which ensures a safe state of the whole system in case
  of emergencies.
* The high-voltage DC contactors for DC plus and minus rails.


**********************************
High-Voltage Connector (HVDC, X19)
**********************************

The X19 connector provides signals to switch the high-voltage contactors,
but also for the corresponding feedback signals to detect contactor welding.

.. figure:: _static/images/charge_som_contactor_wiring.drawio.svg
   :width: 1000pt

   Recommended Contactor Wiring

.. note::
   The precharge contactor might not be necessary in your setup.


********************************************
Insulation Monitoring Device (IMD, X9 + X15)
********************************************

The X9 connector and its pinout is designed to match the signals used by
Bender's ISOMETER® isoCHA425HV with AGH420-1/AGH421-1.

In addition to the direct electrical wiring, the device has to be connected
via RS-485 bus to provide the insulation resistance values which are required
by EVerest's IMD interface.

.. figure:: _static/images/charge_som_wiring_bender_imd.drawio.svg
   :width: 1000pt

   Wiring for Bender's IMD to Charge SOM EVB


**************
I²C Interfaces
**************

The i.MX93 on the Charge SOM provides several I²C interfaces:

+----------+------------+-------------------------------------+-----------------+
| Hardware | Linux      | Usage                               | Clock frequency |
|          |            |                                     |                 |
+==========+============+=====================================+=================+
| I2C1     | i2c-0 [#]_ | on Single Channel DC Carrier Board: | 400 kHz         |
|          |            | RTC (0x52)                          |                 |
+----------+------------+-------------------------------------+-----------------+
| I2C2     | i2c-1      | on Charge SOM:                      | 400 kHz         |
|          |            | Vertexcom MSE102x (0x4a, 0x72)      |                 |
+----------+------------+-------------------------------------+-----------------+
| I2C3     | i2c-2      | on Charge SOM:                      | 400 kHz         |
|          |            | PMIC (0x25) + EEPROM (0x50, 0x58)   |                 |
+----------+------------+-------------------------------------+-----------------+
| I2C5     | disabled   |                                     | disabled        |
+----------+------------+-------------------------------------+-----------------+

.. [#] This interface is only enabled in case of a Charge SOM Single Channel DC Carrier Board.
