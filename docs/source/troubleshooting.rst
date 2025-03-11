.. _troubleshooting.rst:

Troubleshooting
===============

Frequently Asked Questions
--------------------------

.. contents::
   :local:


Is it possible to use the Charge SOM as an EV simulator?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

No, the Control Pilot interface on Charge SOM is not able to operate as an EV. Please look at
our `website <https://www.chargebyte.com/>`_ for more suitable products.


I want to control EVerest via CAN, how can I achieve this?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Currently there is no such EVerest module available, you will need to implement it on your own. But
at least there is a `module <https://github.com/EVerest/everest-core/tree/main/modules/DPM1000>`_
and a `library <https://github.com/EVerest/everest-core/tree/main/lib/staging/can_dpm1000>`_,
which uses the CAN interface.


How can I access the EVerest admin panel on Charge SOM?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Charge SOM doesn't have an `EVerest admin panel <https://github.com/EVerest/everest-admin-panel>`_
because of its limited resources. Please use your development environment to set up your configuration
file or just use a plain text editor.


Does EVerest on Charge SOM support ISO 15118-20 yet?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The required module for ISO 15118-20 has been included in the image since the chargebyte EVerest 0.2.0 release.
Please note that the implementation is still under development.


How do I set up OCPP 2.0.1 on Charge SOM with EVerest?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To support OCPP 2.0.1, the EVerest OCPP201 module must be integrated into the EVerest configuration.
This module uses the `libocpp library <https://github.com/EVerest/libocpp>`_ to implement the OCPP 2.0.1
protocol.
The `OCPP201 module documentation <https://github.com/EVerest/everest-core/blob/main/modules/OCPP201/doc.rst>`_
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
   used to initialize or update the device model database. To update a component config file, just the
   place a `component config file <https://github.com/EVerest/libocpp/tree/v0.16.2/config/v201/component_config>`_
   in the same directory structure in the DeviceModelConfigPath and change the values accordingly.
   Important keys of the component config files are:

   - `standardized/InternalCtrlr.json: ChargePointId`: In "attributes" adapt the "value" key to configure the ChargePointId. Used to identify the Charging Station.
   - `standardized/InternalCtrlr.json: NetworkConnectionProfiles`: In "attributes" adapt the "ocppCsmsUrl" key. The URL in "ocppCsmsUrl" is used to connect to the CSMS.
   - `standardized/SecurityCtrlr.json: SecurityCtrlrIdentity`: In "attributes" adapt the "value" key to configure the SecurityCtrlrIdentity. It is the Charging Station identity.

   For further information about the device model initialization, please refer to the
   `libocpp documentation <https://github.com/EVerest/libocpp/blob/main/doc/v2/ocpp_201_device_model_initialization.md>`_.

I tried to compile chargebyte's Hardware EVerest Modules, but it fails to build. How can it fix this?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
