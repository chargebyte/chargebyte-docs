.. getting_started.rst:

Getting Started
===============

This chapter is intended to help you get started as easily as possible with EV charging together
with the Charge Control C and the EVerest charging stack. For this purpose, a basic AC PWM charger
is set up as an example and explained step by step.

Setting Up the Hardware
------------------------

Hardware Components
^^^^^^^^^^^^^^^^^^^

The following hardware components are required to set up the basic AC PWM charger:

- Charge Control C (100, 200 or 300)
- 12 V DC Power Supply
- Contactor (Link to supported contactors)
- Type2 Socket
- Ethernet cable for SSH connection or USB to serial adapter for serial connection
- Type2 EVSE Test Adapter (e.g. Metrel or Benning) to simulate the EV

Hardware Overview
^^^^^^^^^^^^^^^^^

The following figure shows the basic setup of the AC PWM charger with the Charge Control C:

.. image:: _static/images/ac_pwm_charger_ccc_setup.svg
    :width: 500pt

Note: Before you start setting up the setup, please check whether the HW components used are also
listed in `Hardware Components section`_.

.. _Hardware Components section: #hardware-components

First Startup
-------------

Boot Process
^^^^^^^^^^^^

Understanding LED Status Indicators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Connecting via SSH or Serial Interface
--------------------------------------

SSH Connection with PuTTY
^^^^^^^^^^^^^^^^^^^^^^^^^

Serial Connection with PuTTY
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Initial Configuration
---------------------

Starting and Monitoring the Charging Process
--------------------------------------------

Next Steps
----------
