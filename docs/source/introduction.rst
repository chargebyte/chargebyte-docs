.. introduction.rst:

Introduction
============

Thank you very much for your trust. We are happy that you have chosen our Charge Control platform to
operate your eMobility charging solution. This User Guide will help you to understand all features
of our product and configure them properly to fit your and your customer’s requirements best.

Product Description
-------------------

Charge Control C is an IEC 61851 and ISO 15118 compliant charging controller for Electric
Vehicle Supply Equipment (EVSE). For communication between EVSE and PEV it supports Control Pilot, 
Proximity Pilot as well as PWM signaling including Green PHY communication.

The board is also capable of controlling and sensing different kind of actuators and sensors like
LED, relays, contactors and RCDs through its digital I/Os. It comes with the standard interfaces to
be connected to electric meters, RFID devices and different kinds of actuators and sensors.

Charge Control C is provided with a Linux-Yocto operating system. The installed software is based on
EVerest, an open source software stack for EV charging infrastructure. EVerest itself is based on a
modular architecture that allows scalability according to your needs e.g., adding your own
application as an EVerest module. For more information about EVerest, please visit the
`EVerest GitHub project <https://github.com/EVerest/EVerest>`_.

Charge Control C is currently available in three different hardware variants
(Charge Control C 100, 200 and 300) that are suitable for different complexities of
charging stations.

Product Features
----------------


Safety Notes
------------

IMPORTANT: Read the following safety instruction carefully and clearly prior to the assembly and use
of the device. Please keep these safety instructions for future reference.

A coloured icon: :octicon:`report;1em;sd-text-info`, some more text.

* The installation and assembly may only be carried out by a qualified electrician!
* This device, which is supplied with mains power, has to be secured by means of a max. B6A circuit
  breaker. In case of a multi-phase connection, such a circuit breaker has to be provided for each
  connected outer conductor. These circuit breakers are to be installed directly next to each other.
* WARNING! This device is connected to mains power and hazardous voltages which are not covered.
  Hazardous voltages must be covered inside the charging station to prevent electrical shocks.
* Attention! Make sure that the device is not exposed to heat sources which may lead to overheating.
  Charge Control C can be damaged in case of overheating.
* Attention! The device may only be connected in the range of overvoltage category 3 or lower.
  Operating Charge Control C in a higher category can damage the device.
* Attention! Ensure adequate ventilation at the site of installation. Charge Control C can be
  damaged in case of overheating.
* Attention! Do not operate the device in supply networks which do not comply with the
  specifications on the type plate. Operating Charge Control C in networks not compatible with the
  specifications on the type plate can damage the device.
* Attention! The device may only be installed in dry areas. Exposing Charge Control C to wetness can
  damage the device. 
* This device is designed for installation on DIN rails which provide fire protection as per
  DIN EN 60950-1.


Order Information
-----------------

Here are the currently available order codes for Charge Control C with EVerest:

.. raw:: html

   <div style="text-align: center;">
     Table: Currently available order codes for Charge Control C with EVerest
   </div>

+----------------------+-------------------------------+------------+--------------------+
| Available order code | SW-Variant                    | Housing    | HW-Variant         |
+======================+===============================+============+====================+
| I2CCSC-E00-204       | EVerest software stack v0.8.0 | no housing | Charge Control 200 |
+----------------------+-------------------------------+------------+--------------------+
| I2CCSC-E00-303       | EVerest software stack v0.8.0 | no housing | Charge Control 300 |
+----------------------+-------------------------------+------------+--------------------+

The following figure shows the structure of the order code for Charge Control C:

.. figure:: _static/images/Order_Code_Charge_Control_C.svg
    :width: 600pt

    Figure: Order Code Charge Control C EVerest
