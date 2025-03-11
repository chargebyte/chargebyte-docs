.. _everest_charging_stack.rst:

**********************
EVerest charging stack
**********************

.. include:: ../../includes/everest_introduction_to_everest.inc

.. include:: ../../includes/everest_basic_configuration.inc

Below is an example configuration file provided by chargebyte in its images:

.. literalinclude:: _static/files/bsp-only-dc.yaml

The use case described in this configuration file includes the following:

* DC charging mode
* No TLS (Transport Layer Security) enabled for HLC (High Level Communication)
* 3 phase, 16A fuse limit
* Simulation of the IMD (Insulation Monitoring Device)
* Simulation of the DC Supply Device

An overview of the EVerest modules is shown in the next section.

.. include:: ../../includes/everest_overview_of_everest_modules.inc

**DCSupplySimulator** (`view on GitHub <https://github.com/EVerest/everest-core/blob/main/modules/simulation/DCSupplySimulator/manifest.yaml>`__)

This module simulates a DC power supply device.

**CbChargeSOMDriver** (`view on GitHub <https://github.com/chargebyte/everest-chargebyte/tree/main/modules/CbChargeSOMDriver>`__)

This is the Hardware Abstraction Layer (HAL) for Charge SOM in EVerest. It implements
the `evse_board_support <https://github.com/EVerest/everest-core/blob/main/interfaces/evse_board_support.yaml>`_
interface, enabling communication with the :code:`EvseManager` and control of the board. The EVerest community
often refers to these HAL modules as BSPs, such as MicroMegaWattBSP and PhyVersoBSP. This module is
essential for controlling the Charge SOM.

.. include:: ../../includes/everest_further_reading.inc
