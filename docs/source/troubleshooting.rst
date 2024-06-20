.. troubleshooting.rst:

Troubleshooting
===============

Frequently Asked Questions
--------------------------

.. contents::
   :local:


Is it possible to use the Charge Control C as EV simulator?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

No, the Control Pilot interface on Charge Control C is not able to operate as an EV. Please look at
our `website <https://www.chargebyte.com/>`_ for more suitable products.


Is it possible to use the Charge Control C as DC charge controller?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Yes, for prototypes it’s possible to use the Charge Control C as DC SECC for DIN 70121 or ISO 15118.

   
How can I use CAN with Charge Control C?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There is no Charge Control C with onboard CAN interface available, so we suggest to use a PeakCAN
USB adapter.


Is it possible to upgrade the firmware from proprietary stack to EVerest and vice versa?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Yes it is, but be aware that the configuration and database files will not be converted.


How can I access the EVerest admin panel on Charge Control C?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Charge Control C doesn’t have an EVerest admin panel because of its limited resources. Please
use your development environment to setup your configuration file or just use a plain text editor.


Does EVerest on Charge Control C support ISO 15118-20 yet?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ISO15118-20 implementation is currently still under development and currently not included in
our EVerest releases. The implementation is located on a 
`test branch of the everest-core repository <https://github.com/EVerest/everest-core/tree/testing/iso15118-20>`_.
As soon as the implementation has been merged to the main branch, we will include this module in the
next release cycle.


How do I set up OCPP 2.0.1 on Charge Control C with EVerest?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Unfortunately, there are some manual steps on a development PC necessary. At first checkout the
libocpp and change into the OCPP 2.0.1 config directory:

.. code-block:: console

   git clone https://github.com/EVerest/libocpp.git
   cd libocpp/config/v201

Now adapt OCPP 2.0.1 config.json to your needs (e.g. NetworkConnectionProfiles):

.. code-block:: console

   gedit config.json

After that you can create device model database and insert the configuration:

.. code-block:: console
   
   python3 init_device_model_db.py --db device_model_storage.db --schemas component_schemas/ init
   python3 init_device_model_db.py --db device_model_storage.db --schemas component_schemas/ --config config.json insert
   
Then copy the device model database on Charge Control C (adapt IP address to your environment):

.. code-block:: console

   scp device_model_storage.db root@<ip-address>:/var/lib/everest/ocpp201
   
Finally make sure the DeviceModelDatabasePath in your EVerest configuration points to
/var/lib/everest/ocpp201/device_model_storage.db and then restart EVerest on the Charge Control C.



