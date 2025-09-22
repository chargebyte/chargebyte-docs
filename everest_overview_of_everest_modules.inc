Overview of EVerest modules
============================

As seen from the previous configuration file, some modules are required in order to use EVerest.
Which modules are required is highly dependent on the use case you want to release. The following
is a list of modules that are part of the chargebyte EVerest charging software:

**EvseManager** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/EVSE/EvseManager>`_)

The main module in a charging infrastructure EVerest setup. It manages a single EVSE (i.e., one connector for
charging a car) and may control multiple connectors under some circumstances. It handles charging
logic (basic charging and HLC), gathers all relevant data for the charging session, such as energy
delivered during the session, and provides control over the charging port/session. For more information about
its capabilities, refer to the `module documentation <https://github.com/EVerest/everest-core/blob/main/modules/EVSE/EvseManager/doc.rst>`_.

**EnergyManager** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/EnergyManagement/EnergyManager>`__)

This module is the global Energy Manager for all EVSE/Charging stations in a building.

**API** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/API/API>`__)

This module is not mandatory for a simple EVSE setup in EVerest. However, the module
:code:`API` is responsible for providing a simple MQTT based API to EVerest internals.
Please note that this module will be removed in future releases and replaced by the
:code:`RestAPI` module.

**RpcApi** (`view on GitHub Pull Request <https://github.com/EVerest/everest-core/pull/1324>`__)

This module is not mandatory for a simple EVSE setup in EVerest, but it is required by the CB Energy Management System
:ref:`introduction_nymea` service. This module provides a standardized interface for external applications to interact
with an EVerest-based charge point. It is designed as a lightweight and transport-independent communication layer that
enables monitoring, control, and integration into higher-level energy management systems.

**ErrorHistory** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/Misc/ErrorHistory>`__)

This module is not mandatory for an EVSE setup in EVerest. This module is responsible
for storing EVerest error events in a database file. The location of the database file can be defined
via a configuration parameter.

**ChargerInfo** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/Misc/ChargerInfo>`__)

 This module provides a charger information interface, backed by simple KVS interface. With the optional dependency to
 another charger information node, it is possible to chain multiple sources of information. The module uses a yaml
 file to read charger information like manufacturer, model, serial number, firmware version, etc..
 This file is located in :code:`/etc/everest/charger_info.yaml` by default.

**YamlStore** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/Misc/YamlStore>`__)

This module provides a read-only key-value store interface, backed by a simple YAML file. This module is used by
the :code:`ChargerInfo` module to read charger information from a YAML file.

**DummyTokenProvider** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/Testing/DummyTokenValidator>`__)

This module is used for automatically providing an authorization token, instead of requiring e.g. an
actual RFID reader. It listens to the AuthRequired event from evse_manager module and then publishes one token.

**DummyTokenValidator** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/Testing/DummyTokenValidator>`__)

This module always returns the same configured token validation result for every token. The
validation result is a configuration key in the manifest of the module.

**CbSystem** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbSystem>`__)

This module is an adaptation of the "`System <https://github.com/EVerest/everest-core/tree/main/modules/Misc/System>`_"
module in EVerest. It implements the "`system <https://github.com/EVerest/everest-core/blob/main/interfaces/system.yaml>`__"
interface and, like the :code:`System` module, is responsible for performing system-wide operations but
tailored for chargebyte's hardware platforms. The use of this module depends on the specific use case,
such as if OCPP is required. In such cases, the :code:`CbSystem` module is responsible for executing
commands from OCPP e.g. :code:`UpdateFirmware`.

**OCPP** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/EVSE/OCPP>`__)

This module implements and integrates OCPP 1.6 support within EVerest.

**OCPP201** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/EVSE/OCPP201>`__)

This module implements and integrates OCPP 2.0.1 support within EVerest.

**AuthListValidator**

This module validates if an incoming token exists in a predefined list of authorized tokens.
