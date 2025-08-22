.. _everest_charging_stack.rst:

**********************
EVerest Charging Stack
**********************

.. include:: ../../includes/everest_introduction_to_everest.inc

.. include:: ../../includes/everest_basic_configuration.inc

Below is an example configuration file provided by chargebyte in its images:

.. literalinclude:: _static/files/bsp-only.yaml

The use case described in this configuration file includes the following:

* IEC 61851 / AC basic charging
* Single connector with a fixed cable
* CP state D is rejected
* 1 contactor for 3 phase
* No phase switching

An overview of the EVerest modules that are defined within a configuration file is shown in the next section.

.. include:: ../../includes/everest_overview_of_everest_modules.inc

**CbTarragonDriver** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonDriver>`__)

This is the Hardware Abstraction Layer (HAL) for Charge Control C in EVerest. It implements
the `evse_board_support <https://github.com/EVerest/everest-core/blob/main/interfaces/evse_board_support.yaml>`_
interface, enabling communication with the :code:`EvseManager` and control of the board. The EVerest community
often refers to these HAL modules as BSPs, such as MicroMegaWattBSP and PhyVersoBSP. This module is
essential for controlling the Charge Control C. The term "Tarragon" in :code:`CbTarragonDriver` refers to
the Charge Control C hardware platform.

**CbTarragonPlugLock** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonPlugLock>`__)

This module is not mandatory for an EVSE setup using Charge Control C in EVerest. However, if EVerest
is configured for an AC supply equipment with a socket connector, the module :code:`CbTarragonPlugLock`
can be utilized. This module is a driver for plug lock control and implements
`connector_lock <https://github.com/EVerest/everest-core/blob/main/interfaces/connector_lock.yaml>`_ interface.
It is designed to support all types of plug locks on connector X9 of the Charge Control C. Check
section :ref:`locking_motor` to understand how to connect the locking motor to the Charge Control C.

**CbTarragonDIs** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonDIs>`__)

The Charge Control C is equipped with multiple digital inputs (For more information, refer to section :ref:`digital_input`).
The module :code:`CbTarragonDIs` is used for setting the reference PWM for these DIs. The reference PWM
sets the threshold voltage for all 12V digital inputs, which is essential for their operation.
The use of this module is optional and depends on the EVSE requirements where the Charge Control C is integrated.


Energy Management: 3 phase / 1 phase switching
==============================================

During AC charging, it is sometimes desired to charge with less than 4.2 kW (= 6 A * 230 V * 3 phases),
e.g. for solar charging setups. EVerest comes with built-in support for such setups and can dynamically
switch the count of phases provided to the car. It only requires a corresponding hardware setup and
support in the used hardware abstractation layer.

The Charge Control C is equipped with two independent onboard relays. This makes this hardware platform
ideal for setting up such a phase count switching setup.
Also the BSP driver `CbTarragonDriver <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbTarragonDriver>`_
(aka HAL) for this platform gained support for this.

A phase count switching setup always consists of two contactors which are controlled by the charging
stack more or less independently. There exists two different kinds of hardware setups which are
different in the physical wiring:

* **serial** setup type: In this setup type both contactors are wired in 'series'. This means, that
  the primary contactor always switches all phases (directly or indirectly) while the secondary contactor
  only switches the phases 2 and 3. The advantage of such a connection is that all phases appear
  simultaneously on the car side, not one after another.
  To achieve this, the primary contactor either switches all phases or, in addition to the neutral line
  and one phase, also switches the control path from the secondary contactor.
  From the software perspective, the secondary contactor is switched on first, but switched off last.
  In contrast to the primary contactor: this one is switched on last, but switched off first.
  This ensures - in combination with the physical setup - a homogeneous view of the grid to
  the car. Thus the charger appears to be a single-phase only or a three-phase charger.

.. _switch-3ph1ph-serial-1:
.. figure:: _static/images/switch-3ph1ph-serial-4p-contactor.drawio.svg
    :width: 80%

    Example wiring with two contactors 'in series', both with auxiliary contacts for feedback generation.
    Both contactors must be rated for 400 V in this setup.

.. _switch-3ph1ph-serial-2:
.. figure:: _static/images/switch-3ph1ph-serial-3p-contactor.drawio.svg
    :width: 80%

    Another example wiring with two contactors 'in series'. Here too, both contactors must be
    rated for 400 V. In this example, the primary contactor only needs to switch 3 wires.

* **mutual** setup type: In this setup type, two different contactors are used 'in parallel'. However,
  it is important that only one contactor can be active at a time, i.e. they exclude each other *mutually*.
  This is ensured by the software implementation, but should already be enforced in hardware,
  e.g. by using the auxiliary contacts as shown in :numref:`switch-3ph1ph-mutual`.
  This setup allow to use a single 400 V-rated contactor in combination with a (cheaper) 230 V-rated one.

.. _switch-3ph1ph-mutual:
.. figure:: _static/images/switch-3ph1ph-mutual.drawio.svg
    :width: 80%

    Example wiring with two contactors in 'mutual' setup. The primary contactor must be
    rated for 400 V, the secondary contactor can be rated for 230 V only.

As mentioned, the **CbTarragonDriver** module is the relevant hardware abstraction layer for EVerest
for the Charge Control C platform. The module must know which wiring type is used in the charger
and offers the configuration parameter **switch_3ph1ph_wiring** for this which can take the following strings:

*  **none** (default): No phase-count switching is supported - only R1/S1 is used to switch on/off a single contactor.
* **serial**: Phase-count switching support is enabled using the serial wiring as described above: R1/S1 switches
  the primary contactor, R2/S2 is attached to the secondary contactor.
* **mutual**: Phase-count switching support is enabled using the mutual wiring as described above. R1/S1 is wired to
  the three-phase contactor, R2/S2 is wired to the single-phase contactor.

Snippet of an EVerest configuration file which fits the configuration for :numref:`switch-3ph1ph-mutual`:

.. code-block:: yaml

   ...
   bsp:
     module: CbTarragonDriver
     config_module:
       contactor_1_feedback_type: no
       contactor_2_feedback_type: no
       switch_3ph1ph_wiring: mutual
       connector_type: IEC62196Type2Socket
   ...

.. note::
   Older chargebyte configurations shipped with a `CbTarragonDriver` module parameter `relay_2_name` set to value `none`.
   This was part of an older approach and should not be used that way. Remove it when it is still present,
   so that the default value is applied automatically.

However, enabling support for phase-count switching in the BSP module is not sufficient.
The EVerest configuration must include a module of type 'EnergyManager' which is linked
to an 'EnergyNode', which in turn must be properly linked to the 'EvseManager' module.
This 'EnergyManger' has also a configuration switch **switch_3ph1ph_while_charging_mode** which controls the
phase-count switching in general:

* **Never**: Do not use 1 phase / 3 phase switching even if supported by the BSP.
* **Oneway**: Only switch from 3 phase to 1 phase if power is not enough, but never switch back to 3 phase for a session.
* **Both**: Switch in both directions, i.e. from 3 phase to 1 phase and back to 3 phase if available power changes.

The EnergyManager module has also additional configuration options to allow fine-tuning of the behavior, but
all ship with reasonable default values and thus are not explained in detail here.
A description of all these parameters can be found in the
`EnergyManager manifest <https://github.com/EVerest/everest-core/blob/main/modules/EnergyManager/manifest.yaml>`_.

And also the 'EvseManager' module allows fine-tuning the switching process with two configuration parameters:

* **switch_3ph1ph_delay_s**: This takes an integer and defines, how many seconds the charging stack waits between
  the switching process. In combination with Charge Control C, this value should be at least 11 seconds since the
  onboard relays are enforced to only switch on every 10 seconds, using this exact value or less generates a warning
  but does not result in faster switching.
* **switch_3ph1ph_cp_state**: Allows to configure the CP state used during phase count switching. The default value
  of 'X1' should work with all cars and thus it's recommended to leave it on this default value.

The full description of all these parameters can be found in the
`EvseManager manifest <https://github.com/EVerest/everest-core/blob/main/modules/EvseManager/manifest.yaml>`_.

.. note::
   Phase count switching is only possible in basic charging mode.

.. include:: ../../includes/everest_further_reading.inc
