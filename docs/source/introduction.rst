.. introduction.rst:

Introduction
============

Thank you very much for your trust. We are happy that you have chosen our Charge SOM platform to
operate your eMobility charging solution. This User Guide will help you to understand all features and will help to configure them properly to fit your requirements best.


Product Description
-------------------

The Charge SOM is an IEC 61851 and ISO 15118 compliant charging controller for Electric Vehicle Supply Equipment (EVSE). For communication between EVSE and PEV it supports Control Pilot, Proximity Pilot as well as PWM signaling including Green PHY communication.

The Charge SOM is a future-proof powerhouse based on i.MX93 with universal compatibility, advanced safety features and lots of options for customization.
It is intended to be used as the core component of stationary Electric Vehicle Supply Equipment like HPCs or any DC or Bi-directional charging unit.

The board is also capable of controlling and sensing different kind of actuators and sensors like power modules, high-voltage contactors, isolation monitoring equipment, temperature sensors and much more through its rich digital I/Os.

The Charge SOM is provided with a Linux-Yocto operating system. The installed software is based on EVerest, an open source software stack for EV charging infrastructure. EVerest represents a modular architecture that allows scalability according to your needs e.g., adding your own application as an EVerest module. For more information about EVerest, please visit the
`EVerest GitHub project <https://github.com/EVerest/EVerest>`_.


Product Features
----------------

* Works with CCS1 / CCS2 and NACS according to IEC 61851, SAE J1772, and ISO 15118, ensuring smooth communication with all types of EVs.
* A dedicated co-processor monitors and controls safety-critical components like CP and PP signals, DC circuit breakers, E-Stops and other vital components in real-time according to functional safety standard IEC 61508
* PT1000 plug temperature monitoring
* Plug-and-Play with the popular `EVerest charging stack <https://github.com/EVerest/EVerest>`_
* Well maintained, open Yocto BSP
* `OCPP <https://openchargealliance.org/protocols/open-charge-point-protocol/>`_ for version 1.6, 2.0.1 and 2.1
* ISO 15118-20 and lower
* HomePlug Green PHY Standard & ISO 15118 Support utilizing the Vertexcom MSE1021 chipset
* TPM 2.0 standard compliant module for secure hardware-based key storage
* RTC support via I2C for precise timekeeping (IC/battery on carrier board)

Host Controller

* NXP i.MX93 1.7 GHz
* 1 GB DDR4 RAM
* 8 GB eMMC

Availability of the interfaces depends on the actual variant - see the product datasheet for more details.


.. _safety_notes:

Safety Notes
------------

.. |attention| image:: _static/images/attention_sign.png
   :height: 4ex

.. warning::

  **Read the following safety instructions carefully and clearly prior to the assembly and
  use of the device. Please keep these safety instructions for future reference.**

  * |attention| The electrical installation and assembly may only be carried out by a qualified electrician!
  * **Attention!** Make sure that the device is not exposed to heat sources which may lead to overheating.
    Charge SOM can be damaged in case of overheating.
  * **Attention!** The device may only be connected in the range of overvoltage category 3 or lower.
    Operating Charge SOM in a higher category can damage the device.
  * **Attention!** Ensure adequate ventilation at the site of installation. Charge SOM can be
    damaged in case of overheating.
  * **Attention!** Do not operate the device in supply networks which do not comply with the
    specifications on the type plate. Operating Charge SOM in networks not compatible with
    the specifications on the type plate can damage the device.
  * **Attention!** The device may only be installed in dry areas. Exposing Charge SOM to wetness
    can damage the device.


Order Information
-----------------

You can acquire an Evaluation Kit using the order code 'CBCSOM-EVAL-KIT-01'.
For more information on different models and peripheral of the Charge SOM,
please contact `info@chargebyte.com <mailto:info@chargebyte.com>`_.
