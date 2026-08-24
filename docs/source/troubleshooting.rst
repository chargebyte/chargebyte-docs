.. _troubleshooting.rst:

Troubleshooting
===============

Frequently Asked Questions
--------------------------

.. contents::
   :local:

Does the Charge Control V have a CE certification?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Currently, the Charge Control V does not have CE certification yet,
but chargebyte is working on this topic already.


Does the Charge Control V have Wi-Fi support?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

No, the Charge Control V does not have built-in Wi-Fi support, but it
would be possible to use the USB connector of the device to attach a
USB Wifi Dongle.


Is it possible to use the Charge Control V as an EV simulator?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Charge Control V is designed to be used on the EVSE side. Please refer to our
`website <https://www.chargebyte.com/>`_ for more suitable products.


I want to control EVerest via CAN, how can I achieve this?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Currently, this is not possible. Please contact our sales team to discuss your options.


What is the difference between CHSTOP_IN and SAFETY_ESTOPx?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The signal CHSTOP_IN is connected to the i.MX93 SoC and can be used to gracefully stop the charging process.
It is not designed for time-critical use cases. Currently, there is no EVerest module that can handle this
signal. This work is pending.

To implement real-time emergency stop behavior, use the SAFETY_ESTOPx signals, which are connected to the safety
processor.


Is there a Linux command to check for connection related CAN issues?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Yes

.. code-block:: console

   root@chargesom:/# ip -details -statistic link show can0


How can I access the EVerest admin panel on a Charge Control V?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Currently, the Charge Control V does not have the `EVerest admin panel <https://github.com/EVerest/EVerest-admin-panel>`_
integrated.
Please use your development environment to set up your configuration file. Alternatively, you can use a plain text
editor.


How should TLS or Plug & Charge private keys be protected?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For TLS and especially Plug & Charge, private keys should be protected according to the requirements of the
certificate authority or certificate management system. In many production environments, this means using
hardware-backed key storage such as a TPM, HSM, or comparable technology.

Charge Control V includes an integrated TPM to support secure storage of TLS and Plug & Charge private keys.
For more information about using the TPM and implementing a production Plug & Charge scenario, please
contact chargebyte support so that key storage and certificate handling can be aligned with your requirements.


Does EVerest on Charge Control V support ISO 15118-20 yet?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The required module for ISO 15118-20 is included in our firmware builds.
Please note that the implementation is still under development and integrated into the image only for test purposes.

EVerest integrates the `libiso15118 <https://github.com/EVerest/libiso15118>`_ library to provide support for ISO 15118-20.
Here you can find more information about the current status of the ISO 15118-20 implementation.
Please note, however, that the range of functions described in the linked `libiso15118` library documentation may not
correspond to those already integrated in EVerest, as the library has not yet been fully integrated.
Implementation gaps may exist, particularly in the case of BPT (bidirectional power transfer) functionality.


How do I set up OCPP 2.0.1 on Charge Control V with EVerest?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To support OCPP 2.0.1, the EVerest :ref:`OCPP201 <everest_module_ocpp201>` module must be integrated into
the EVerest configuration.
The `OCPP 2.0.1 and 2.1 tutorial <https://everest.github.io/nightly/tutorials/ocpp2.html>`_
already contains information about the module parameters, the provided and required interfaces,
and the initial creation of the OCPP database.

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
   first start of EVerest. The database is stored at the `DeviceModelDatabasePath`.
6. The component config files are stored in the `DeviceModelConfigPath`. Component config files are
   used to initialize or update the device model database. To update a component config file, just
   place a `component config file <https://github.com/EVerest/EVerest/tree/main/lib/everest/ocpp/config/common/component_config>`_
   in the same directory structure in the DeviceModelConfigPath and change the values accordingly.
   Important keys of the component config files are:

   - `standardized/InternalCtrlr.json: ChargePointId`: In "attributes" adapt the "value" key to configure the ChargePointId. Used to identify the Charging Station.
   - `standardized/InternalCtrlr.json: NetworkConnectionProfiles`: In "attributes" adapt the "ocppCsmsUrl" key. The URL in "ocppCsmsUrl" is used to connect to the CSMS.
   - `standardized/SecurityCtrlr.json: SecurityCtrlrIdentity`: In "attributes" adapt the "value" key to configure the SecurityCtrlrIdentity. It is the Charging Station identity.

   For further information about the device model initialization, please refer to the
   `libocpp documentation <https://github.com/EVerest/EVerest/blob/main/lib/everest/ocpp/doc/v2/ocpp_201_device_model_initialization.md>`_.


I tried to compile chargebyte's Hardware EVerest Modules, but it fails to build. How can I fix this?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The EVerest mainline development is very dynamic and does not guarantee
stable APIs across EVerest modules. Therefore, after almost every EVerest release,
chargebyte needs to adapt its modules to the latest API changes.

Please have a look at the `compatibility matrix <https://github.com/chargebyte/everest-chargebyte/blob/main/README.md>`_
to see which EVerest release works with which chargebyte EVerest modules release.


I would like to implement a custom Modbus device in EVerest. Where should I start?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

EVerest already has a module that takes care of Modbus communication. Please have a look at
`SerialCommHub <https://everest.github.io/nightly/reference/modules/Misc/SerialCommHub/autogenerated.html>`_
and let your module interact with this module via the `serial_communication_hub` interface.

.. _contact:

.. include:: ../../includes/troubleshooting_contact.inc
