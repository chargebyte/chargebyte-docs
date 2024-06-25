.. _everest_charging_stack.rst:

**********************
EVerest charging stack
**********************

Introduction to EVerest
=======================

EVerest is an open-source modular framework designed to create a comprehensive software stack for
electric vehicle (EV) charging.

The modular software architecture promotes flexibility and customization, allowing users to configure specific charging
scenarios using interchangeable modules. This architecture is integrated and coordinated using MQTT (Message Queuing
Telemetry Transport). EVerest aims to standardize and simplify the development of EV charging
infrastructure, making it easier for developers and companies to implement robust and scalable charging solutions.
The project includes support for various protocols like ISO 15118, OCPP, and IEC 61851, ensuring broad
compatibility and future-proofing of the charging systems.

For more information, visit the `EVerest GitHub repository <https://github.com/EVerest/EVerest>`_.

Basic configuration
===================

In order to test EVerest, you need to build it either natively on host Linux machine or integrate it into a
firmware suitable for a specific target platform using Yocto. To build it natively, follow the instructions
found in the main EVerest repository "`everest-core <https://github.com/EVerest/everest-core>`_".
Additionally, there is a `quickstart guide <https://everest.github.io/nightly/general/03_quick_start_guide.html>`_
to EVerest, which presents the different EVerest tools, build instructions, and a dive into simulating EVerest.

For Yocto, EVerest offers "`meta-everest <https://github.com/EVerest/meta-everest>`_"; a Yocto meta layer
that can be used to integrate the EVerest charging stack into a platform-specific firmware image.
chargebyte utilizes this layer to produce firmware images suitable for Charge Control C. Detailed instructions on
how to integrate EVerest into a Charge Control C firmware image can be found on `GitHub <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest>`_.

For setting up a use case with EVerest, such as basic PWM charging, a YAML configuration file is needed.
Various example configurations, including those for software-in-the-loop tests, can be found in
the "`config <https://github.com/EVerest/everest-core/tree/main/config>`_" folder of the everest-core repository.
Below is an example configuration file provided by chargebyte in its images:

.. literalinclude:: _static/files/bsp-only.yaml

The use case described in this configuration file includes the following:

* IEC 61851 / AC basic charging
* Single connector with a fixed cable
* CP state D is rejected
* 1 contactor for 3 phase
* No phase switching

The modules :code:`CbTarragonDriver` and :code:`CbTarragonDIs` are part of the Hardware Abstraction Layer (HAL)
used to integrate Charge Control C with EVerest. This will be explained in the next section.

Required modules for Charge Control C
=====================================

As seen from the previous configuration file, some modules are required in order to use EVerest with Charge Control C.

**EvseManager** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/EvseManager>`_)

The main module in a charging infrastructure EVerest setup. It manages a single EVSE (i.e., one connector for
charging a car) and may control multiple connectors under some circumstances. It handles charging
logic (basic charging and HLC), gathers all relevant data for the charging session, such as energy
delivered during the session, and provides control over the charging port/session. For more information about
its capabilities, refer to the `module documentation <https://github.com/EVerest/everest-core/blob/main/modules/EvseManager/doc.rst>`_.

**EnergyManager** (`view on GitHub <https://github.com/EVerest/everest-core/tree/main/modules/EnergyManager>`__)

This module is the global Energy Manager for all EVSE/Charging stations in a building.

**CbTarragonDriver** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonDriver>`__)

This is the Hardware Abstraction Layer (HAL) for Charge Control C in EVerest. It implements
the `evse_board_support <https://github.com/EVerest/everest-core/blob/main/interfaces/evse_board_support.yaml>`_
interface, enabling communication with the :code:`EvseManager` and control of the board. The EVerest community
often refers to these HAL modules as BSPs, such as MicroMegaWattBSP and PhyVersoBSP. This module is
essential for controlling the Charge Control C. The term "Tarragon" in :code:`CbTarragonDriver` refers to
the Charge Control C hardware platform.

**CbTarragonDIs** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonDIs>`__)

The Charge Control C is equipped with multiple digital inputs (For more information, refer to section :ref:`digital_input`).
The module :code:`CbTarragonDIs` is used for setting the reference PWM for these DIs. The reference PWM
sets the threshold voltage for all 12V digital inputs, which is essential for their operation.
The use of this module is optional and depends on the EVSE requirements where the Charge Control C is integrated.

**CbSystem** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbSystem>`__)

This module is an adaptation of the "`System <https://github.com/EVerest/everest-core/tree/main/modules/System>`_"
module in EVerest. It implements the "`system <https://github.com/EVerest/everest-core/blob/main/interfaces/system.yaml>`__"
interface and, like the :code:`System` module, is responsible for performing system-wide operations but
tailored for chargebyte's hardware platforms. The use of this module depends on the specific use case,
such as if OCPP is required. In such cases, the :code:`CbSystem` module is responsible for executing
commands from OCPP e.g. :code:`UpdateFirmware`.

**CbTarragonPlugLock** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonPlugLock>`__)

This module is not mandatory for an EVSE setup using Charge Control C in EVerest. However, if EVerest
is configured for an AC supply equipment with a socket connector, the module :code:`CbTarragonPlugLock`
can be utilized. This module is a driver for plug lock control and implements
`connector_lock <https://github.com/EVerest/everest-core/blob/main/interfaces/connector_lock.yaml>`_ interface.
It is designed to support all types of plug locks on connector X9 of the Charge Control C. Check
section :ref:`locking_motor` to understand how to connect the locking motor to the Charge Control C.

Further reading
===============

For more information on getting started with EVerest, including an overview of the necessary tools and
instructions on writing your own modules, please refer to the official
`EVerest documentation <https://everest.github.io/nightly>`_.

EVerest consists of multiple repositories, such as "`everest-core <https://github.com/EVerest/everest-core>`_"
and "`libocpp <https://github.com/EVerest/libocpp>`_". Each repository has its own documentation detailing its
specific role within EVerest. It should be noted that Pionix GmbH and the EVerest community maintain
all repositories that are a part of the EVerest GitHub organization. Only the EVerest modules that chargebyte
implemented and that are located in "`everest-chargebyte <https://github.com/chargebyte/everest-chargebyte>`_"
are maintained by chargebyte.

For interesting discussions and solutions to common problems, visit the EVerest community's
`Zulip <https://lfenergy.zulipchat.com/>`_ channels.

For support and issues related to the EVerest modules developed by chargebyte, refer to section X for
instructions on how to report problems and insights on contribution.
