.. _troubleshooting.rst:

Troubleshooting
===============

Frequently Asked Questions
--------------------------

.. contents::
   :local:


Is it possible to use the Charge Control C as an EV simulator?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

No, the Control Pilot interface on Charge Control C is not able to operate as an EV. Please look at
our `website <https://www.chargebyte.com/>`_ for more suitable products.


Is it possible to use the Charge Control C as a DC charge controller?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Yes, for prototypes it’s possible to use the Charge Control C as DC SECC for DIN 70121 or ISO 15118.
But the Charge Control C was designed with the AC use case in mind.


How can I use CAN with Charge Control C?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There is no Charge Control C with onboard CAN interface available, so we suggest to use a PeakCAN
USB adapter.


I want to control EVerest via CAN, how can I achieve this?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Currently there is no such EVerest module available, you will need to implement it on your own. But
at least there is a `module <https://github.com/EVerest/everest-core/tree/main/modules/DPM1000>`_
and a `library <https://github.com/EVerest/everest-core/tree/main/lib/staging/can_dpm1000>`_,
which uses the CAN interface.


Is it possible to upgrade the firmware from proprietary stack to EVerest and vice versa?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Yes it is, but be aware that the configuration and database files will not be converted.

.. note::
   Before installation of a chargebyte EVerest image, please check whether you are installing a
   developer or release image and prepare the Charge Control C accordingly. How to do this is
   explained in the :ref:`release_vs_development_images` section.

For more information, please refer to the :ref:`update_from_chargebyte_to_everest` section.


How can I access the EVerest admin panel on Charge Control C?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Charge Control C doesn't have an `EVerest admin panel <https://github.com/EVerest/everest-admin-panel>`_
because of its limited resources. Please use your development environment to set up your configuration
file or just use a plain text editor.


Does EVerest on Charge Control C support ISO 15118-20 yet?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The required module for ISO 15118-20 has been included in the image since the chargebyte EVerest 1.0.0 release.
Please note that the implementation is still under development and integrated into the image only for test purposes.


How do I set up OCPP 2.0.1 on Charge Control C with EVerest?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Unfortunately, some manual steps on a development PC are necessary. First, check out the
libocpp and change into the OCPP 2.0.1 config directory:

.. code-block:: console

   git clone https://github.com/EVerest/libocpp.git
   cd libocpp/config/v201

Now adapt OCPP 2.0.1 config.json to your needs (e.g. NetworkConnectionProfiles):

.. code-block:: console

   gedit config.json

After that you can create the device model database and insert the configuration:

.. code-block:: console
   
   python3 init_device_model_db.py --db device_model_storage.db --schemas component_schemas/ init
   python3 init_device_model_db.py --db device_model_storage.db --schemas component_schemas/ --config config.json insert
   
Then copy the device model database onto the Charge Control C (adapt IP address to your environment):

.. code-block:: console

   scp device_model_storage.db root@<ip-address>:/var/lib/everest/ocpp201
   
Finally make sure the DeviceModelDatabasePath in your global YAML configuration points to
/var/lib/everest/ocpp201/device_model_storage.db and then restart EVerest on the Charge Control C.

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

Contact
-------

Support
^^^^^^^

EVerest is an open-source project with a lot of modules, which is supported by a big community.
chargebyte is an active part of this community. However chargebyte is not able to provide support
for every aspect of EVerest. In order to get quick answers, here are some suggestions:

Do you have general questions about EVerest, please use the EVerest community's
`Zulip <https://lfenergy.zulipchat.com/>`_.

Do you have questions about the chargebyte BSP (incl. Yocto), please use
`our support desk <https://chargebyte.com/support>`_.

Address
^^^^^^^

chargebyte GmbH

Bitterfelder Straße 1-5

04129 Leipzig

Germany

Website: `<https://chargebyte.com>`_


