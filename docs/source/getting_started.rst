.. _getting_started.rst:

Getting Started
===============

This chapter is intended to help you get started as easily as possible with EV charging together
with the Charge SOM Evaluation Kit and the EVerest charging stack. For this purpose, a basic DC 
charger is set up as an example and explained step by step.


Setting Up the Hardware
------------------------


Hardware Components
^^^^^^^^^^^^^^^^^^^

The following hardware components are required to set up the basic DC charger:

- Charge SOM Evaluation Kit
- 12 V DC Power Supply
- Ethernet cable for SSH connection or USB to serial adapter for serial connection
- DIN70121 or ISO15118-2 EV simulator (e.g. Charge Module S Evaluation board)
- Wiring material


Hardware Overview
^^^^^^^^^^^^^^^^^

The following figure shows the basic setup of the DC charger with the Charge SOM Evaluation Kit:

.. figure:: _static/images/dc_charger_charge_som_setup.svg
    :width: 800pt

    Figure: Basic Setup of the DC charger with the Charge SOM

.. note::
   The pin assignment of the Charge SOM Evaluation Kit can be found in the datasheet.

.. note::
   Before you start setting up the hardware, please check whether the HW components used are also
   listed in `Hardware Components section`_.

.. _Hardware Components section: #hardware-components


First Startup
-------------

Boot Process
^^^^^^^^^^^^

Here are some key points about the boot process of the Charge controller:

- The file system basically consists of three ext4 partitions. Two partitions are used as slots for
  the RAUC update process. The third partition is not touched by the RAUC update process and is usually
  used for storing update bundles, logs, etc.
- After connecting the Charge controller to the power supply, the U-Boot bootloader starts the
  currently active slot managed by RAUC.
- The LED status indicators on the Charge controller provide information about the current status of
  the boot process.
- EVerest is automatically started with the default configuration of chargebyte after the boot
  process is completed. The initial configuration is explained in the `Initial Configuration`_ section.


Understanding LED Status Indicators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Now you can plug in the Charge SOM Evaluation Kit to the power supply. The LED status indicator on the
carrier board provide information about the current status of the boot process. The following table
shows the meaning of the LED status indicators:

.. raw:: html
 
   <div style="text-align: center;">
     Table: Charge SOM Evaluation Kit LED Status Indicators
   </div>

+--------------------------+---------------------------------+--------------------------------------+
| State                    | LED indication                  | Behavior                             |
+==========================+=================================+======================================+
| Boot process running     | LED (red)                       | periodic blinking for approx. 4 sec. |
+--------------------------+---------------------------------+--------------------------------------+
| Operating system running | LED (red)                       | rhythmic blinking                    |
+--------------------------+---------------------------------+--------------------------------------+


.. include:: ../../includes/connecting.inc


Initial Configuration
---------------------

Now you are connected to the Charge SOM and we can take a deeper look at the initial
configuration.

The configuration files of the EVerest charging stack are stored in the directory "/etc/everest".
EVerest uses the YAML format for the configuration files. EVerest runs as a systemd service that
by default uses "/etc/everest/config.yaml" as a configuration setup. If you take a look at the
content of the configuration file, you will see that it is only a reference to the
"bsp-only-dc.yaml" file.

.. note::
   If you create an own configuration file, you can also store it in the "/etc/everest" directory
   and create a symbolic link to it like "ln -sf /etc/everest/my-config.yaml /etc/everest/config.yaml".

.. code-block:: bash

   root@chargesom:/etc/everest# ls -l /etc/everest/
   total 28
   -rw-r--r-- 1 root root 1134 Jun 20 07:45 bsp-only-dc.yaml
   lrwxrwxrwx 1 root root   14 Jun 25 19:26 config.yaml ->  my-config.yaml

Let's take a look at the content of the bsp-only-dc.yaml configuration file. This file is already
prepared for the basic DC charger setup.

Just type "less /etc/everest/bsp-only-dc.conf" to see the content of the configuration file:

.. literalinclude:: _static/files/bsp-only-dc.yaml
   :language: yaml
   :linenos:

In general, the EVerest charging stack consists of different modules, each of which fulfills a
specific task. An EVerest module provides and requests interfaces. The configuration file shows
which EVerest modules are activated, how they are configured and how they are connected to each
other over the interfaces. The following figure illustrates how the EVerest modules are connected
to each other:

.. figure:: _static/images/admin_panel_bsp_only.png
    :width: 600pt
    :name: admin_panel_bsp_only

    Figure: EVerest admin panel view of the bsp-only-dc.yaml configuration

However, not all configuration parameters of the modules are shown here. Only the configuration
parameters that do not match the default configuration of the respective module need
to be specified here. Depending on the installed hardware components, the configuration file may
need to be adapted. The hardware related tasks are mainly handled by the CbChargeSOMDriver module.
The configuration of the CbChargeSOMDriver module can be found in "/usr/libexec/everest/modules/CbChargeSOMDriver"
directory.

Each module has a specific configuration file. This file is called "manifest.yaml" and is stored 
in the main directory of the module.
Here you can also see all other configuration parameters of the respective module. 
Now please type "less /usr/libexec/everest/modules/CbChargeSOMDriver/manifest.yaml" to see the
content of the configuration file and check whether the configuration fits to your hardware setup.

If you want to change a configuration parameter of a module, which is not part of your EVerest YAML
configuration file, just copy the specific configuration key from the "manifest.yaml" file of the
module to the module specific "config_module" space in your EVerest configuration and adjust the
value. Please note if you change it directly in the "manifest.yaml" file of a module, the changes
will be get lost after a software update.

Here is an excerpt of an EVerest configuration to change the parameter "evse_id" to
"MY*CUS*T654321*1" of the CbChargeSOMDriver module.

.. code-block:: sh

  bsp:
    module: CbChargeSOMDriver
  connector:
    module: EvseManager
    config_module:
      connector_id: 1
      charge_mode: DC
      evse_id: MY*CUS*T654321*1

After adjusting the configuration file, you have to restart the EVerest charging stack to apply the
changes. Just type "systemctl restart everest" to restart the EVerest charging stack.

.. note::
   You can also use the EVerest admin panel to adjust the EVerest configuration in a GUI.
   This tool must currently be installed manually on your developer computer,
   because the resources on the board are limited.

.. note::
   If you have made a mistake in the configuration file, the EVerest charging stack will not
   start. Therefore, it is recommended to back up the original configuration file before making
   changes.


Starting and Monitoring the Charging Process
--------------------------------------------

Before we start the first charging session, we shall open the EVerest log to monitor the charging
process. The EVerest log is stored in the systemd journal and can be accessed via the journalctl
command. The journalctl command provides a lot of options to filter the log messages. 
Now just type "journalctl -f -u everest -n 50" to see the last 50 log messages of the EVerest
charging stack and to follow the charging process in real time.

The EVerest log should look like this:

.. code-block:: sh

   root@chargesom:~# journalctl -f -u everest -n 50
   2024-12-13T15:45:00.514151+0100 chargesom sh[237]: Starting to migrate EVerest configurations
   2024-12-13T15:45:00.532706+0100 chargesom sh[237]: EVerest configurations migrated successfully
   2024-12-13T15:45:00.561214+0100 chargesom systemd[1]: Started EVerest.
   2024-12-13T15:45:00.779573+0100 chargesom manager[241]: [INFO] manager          ::   ________      __                _
   2024-12-13T15:45:00.779573+0100 chargesom manager[241]: [INFO] manager          ::  |  ____\ \    / /               | |
   2024-12-13T15:45:00.779573+0100 chargesom manager[241]: [INFO] manager          ::  | |__   \ \  / /__ _ __ ___  ___| |_
   2024-12-13T15:45:00.779573+0100 chargesom manager[241]: [INFO] manager          ::  |  __|   \ \/ / _ \ '__/ _ \/ __| __|
   2024-12-13T15:45:00.779573+0100 chargesom manager[241]: [INFO] manager          ::  | |____   \  /  __/ | |  __/\__ \ |_
   2024-12-13T15:45:00.779573+0100 chargesom manager[241]: [INFO] manager          ::  |______|   \/ \___|_|  \___||___/\__|
   2024-12-13T15:45:00.779573+0100 chargesom manager[241]: [INFO] manager          ::
   2024-12-13T15:45:00.781629+0100 chargesom manager[241]: [INFO] manager          :: everest-framework 0.17.2 main@v0.17.2-dirty
   2024-12-13T15:45:00.781629+0100 chargesom manager[241]: [INFO] manager          :: everest-core 2024.9.0 main@2024.9.0-rc1-40-g1e06aaab-dirty
   2024-12-13T15:45:00.781629+0100 chargesom manager[241]: [INFO] manager          ::
   2024-12-13T15:45:00.781629+0100 chargesom manager[241]: [INFO] manager          :: Using MQTT broker localhost:1883
   2024-12-13T15:45:00.811618+0100 chargesom manager[242]: [INFO] everest_ctrl     :: Launching controller service on port 8849
   2024-12-13T15:45:00.862280+0100 chargesom manager[241]: [INFO] manager          :: Loading config file at: /etc/everest/config.yaml
   2024-12-13T15:45:01.239004+0100 chargesom manager[241]: [INFO] manager          :: Config loading completed in 451ms
   2024-12-13T15:45:03.899562+0100 chargesom manager[260]: [INFO] api:API          :: Module api initialized [2594ms]
   2024-12-13T15:45:04.376658+0100 chargesom manager[266]: [INFO] evse_security:E  :: Module evse_security initialized [2751ms]
   2024-12-13T15:45:04.704404+0100 chargesom manager[264]: [INFO] energy_manager:  :: Module energy_manager initialized [3237ms]
   2024-12-13T15:45:05.093575+0100 chargesom manager[261]: [INFO] auth:Auth        :: Module auth initialized [3776ms]
   2024-12-13T15:45:05.237957+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Module evse_slac initialized [3623ms]
   2024-12-13T15:45:05.364804+0100 chargesom manager[269]: [INFO] imd:IMDSimulato  :: Module imd initialized [3755ms]
   2024-12-13T15:45:05.485234+0100 chargesom manager[262]: [INFO] bsp:CbChargeSOM  :: chargebyte's Charge SOM EVerest module (version: 0.16.0)
   2024-12-13T15:45:05.486334+0100 chargesom manager[262]: [INFO] bsp:CbChargeSOM  :: Module bsp initialized [4145ms]
   2024-12-13T15:45:05.569128+0100 chargesom manager[271]: [INFO] powersupply_dc:  :: Module powersupply_dc initialized [3777ms]
   2024-12-13T15:45:05.578465+0100 chargesom manager[268]: [INFO] grid_connection  :: Module grid_connection_point initialized [4042ms]
   2024-12-13T15:45:05.643080+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Module iso15118_charger initialized [3811ms]
   2024-12-13T15:45:05.660663+0100 chargesom manager[265]: [INFO] error_history:E  :: Resetting database
   2024-12-13T15:45:05.672632+0100 chargesom manager[273]: [INFO] token_validator  :: Module token_validator initialized [3779ms]
   2024-12-13T15:45:05.684368+0100 chargesom manager[265]: [INFO] error_history:E  :: Module error_history initialized [4205ms]
   2024-12-13T15:45:05.706916+0100 chargesom manager[272]: [INFO] token_provider:  :: Module token_provider initialized [3957ms]
   2024-12-13T15:45:05.857535+0100 chargesom manager[263]: [INFO] connector:EvseM  :: Module connector initialized [4295ms]
   2024-12-13T15:45:05.904734+0100 chargesom manager[241]: [INFO] manager          :: 🚙🚙🚙 All modules are initialized. EVerest up and running [5162ms] 🚙🚙🚙
   2024-12-13T15:45:05.911103+0100 chargesom manager[270]: [INFO] iso15118_charge  :: TCP server on eth1 is listening on port [fe80::2c04:d5ff:fe18:78a7%3]:61341
   2024-12-13T15:45:05.911444+0100 chargesom manager[270]: [INFO] iso15118_charge  :: SDP socket setup succeeded
   2024-12-13T15:45:05.937212+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Starting the SLAC state machine
   2024-12-13T15:45:06.137657+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Entered Reset state
   2024-12-13T15:45:06.138098+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: New NMK key: 32:47:36:36:38:36:4F:55:58:34:4A:39:45:4A:46:4A
   2024-12-13T15:45:06.141405+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Received CM_SET_KEY_CNF
   2024-12-13T15:45:06.142173+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Entered Idle state
   2024-12-13T15:45:06.390594+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Ignoring bidirectional SupportedEnergyTransferMode
   2024-12-13T15:45:11.539400+0100 chargesom manager[263]: [INFO] connector:EvseM  :: Cleaning up any other transaction on start up
   2024-12-13T15:45:11.672232+0100 chargesom manager[263]: [INFO] connector:EvseM  :: 🌀🌀🌀 Ready to start charging 🌀🌀🌀
   2024-12-13T15:45:11.672232+0100 chargesom manager[263]: [WARN] connector:EvseM void module::EvseManager::ready_to_start_charging() :: No powermeter value received yet!
   2024-12-13T15:45:11.805756+0100 chargesom manager[262]: [INFO] bsp:CbChargeSOM  :: handle_enable: Setting new duty cycle of 100.00%
   2024-12-13T15:45:12.119474+0100 chargesom manager[262]: [INFO] bsp:CbChargeSOM  :: handle_pwm_off: Setting new duty cycle of 100.00%
   2024-12-13T15:45:12.190889+0100 chargesom manager[263]: [INFO] connector:EvseM  :: All errors cleared
   2024-12-13T15:45:12.260924+0100 chargesom manager[262]: [INFO] bsp:CbChargeSOM  :: CP state change from PowerOn to A, U_CP+: 12196 mV, U_CP-: -303 mV
   2024-12-13T15:45:12.305158+0100 chargesom manager[262]: [INFO] bsp:CbChargeSOM  :: handle_pwm_off: Setting new duty cycle of 100.00%

Before connecting the CP line between Charge SOM Evaluation Kit and the EV simulator, please make
sure that the following things are fulfilled:

- GND from X18 is connected to the EV simulator
- PP from X18 is not connected to the EV simulator
- EV simulator is powered up
- EV simulator must configured to DIN 70121 or ISO 15118-2 DC EIM (No TLS)

After connecting the CP line, a CP state change from "A" to "B" should be visible in the EVerest log.
The duty cycle should directly switch from 100% to 5%. The duty cycle change indicates the EVSE is
now ready for high level communication.

The EVerest log messages should look like this:

.. code-block:: sh

   2024-12-13T15:52:01.800939+0100 chargesom manager[262]: [INFO] bsp:CbChargeSOM  :: CP state change from A to B, U_CP+: 9150 mV, U_CP-: -300 mV
   2024-12-13T15:52:01.843375+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Entered Matching state, waiting for CM_SLAC_PARM_REQ
   2024-12-13T15:52:01.959010+0100 chargesom manager[263]: [INFO] connector:EvseM  :: SYS  Session logging started.
   2024-12-13T15:52:01.960014+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE IEC Session Started: EVConnected
   2024-12-13T15:52:01.962704+0100 chargesom manager[272]: [INFO] token_provider:  :: Publishing new dummy token: {
   2024-12-13T15:52:01.962704+0100 chargesom manager[272]:     "type": "ISO14443",
   2024-12-13T15:52:01.962704+0100 chargesom manager[272]:     "value": "DEADBEEF"
   2024-12-13T15:52:01.962704+0100 chargesom manager[272]: } (RFID)
   2024-12-13T15:52:01.967069+0100 chargesom manager[261]: [INFO] auth:Auth        :: Received new token: {
   2024-12-13T15:52:01.967069+0100 chargesom manager[261]:     "authorization_type": "RFID",
   2024-12-13T15:52:01.967069+0100 chargesom manager[261]:     "id_token": {
   2024-12-13T15:52:01.967069+0100 chargesom manager[261]:         "type": "ISO14443",
   2024-12-13T15:52:01.967069+0100 chargesom manager[261]:         "value": "DEADBEEF"
   2024-12-13T15:52:01.967069+0100 chargesom manager[261]:     }
   2024-12-13T15:52:01.967069+0100 chargesom manager[261]: }
   2024-12-13T15:52:01.970206+0100 chargesom manager[273]: [INFO] token_validator  :: Got validation request for token: DEADBEEF
   2024-12-13T15:52:02.220655+0100 chargesom manager[273]: [INFO] token_validator  :: Returning validation status: Accepted
   2024-12-13T15:52:02.223254+0100 chargesom manager[261]: [INFO] auth:Auth        :: Providing authorization to connector#1
   2024-12-13T15:52:02.960278+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE IEC Set PWM On (5.000000074505806%) took 0 ms
   2024-12-13T15:52:02.962409+0100 chargesom manager[262]: [INFO] bsp:CbChargeSOM  :: handle_pwm_on: Setting new duty cycle of 5.00%
   2024-12-13T15:52:03.105628+0100 chargesom manager[261]: [INFO] auth:Auth        :: Result for token: DEADBEEF: ACCEPTED
   2024-12-13T15:52:03.155035+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE IEC EIM Authorization received
   2024-12-13T15:52:03.155499+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE IEC Transaction Started (0 kWh)
   2024-12-13T15:52:03.156415+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE IEC DC mode. We are in 5percent mode so we can continue without further action.
   2024-12-13T15:52:03.156895+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE IEC Charger state: Wait for Auth->PrepareCharging
   
After that the EV simulator should establish a powerline connection to the Charge SOM via SLAC.

.. code-block:: sh

   2024-12-13T15:52:04.060237+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): initialized, waiting for CM_START_ATTEN_CHAR_IND
   2024-12-13T15:52:04.076565+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_START_ATTEN_CHAR_IND, going to substate SOUNDING
   2024-12-13T15:52:04.116823+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): needs to be in state WAIT_FOR_START_ATTEN_CHAR for CM_START_ATTEN_CHAR_IND
   2024-12-13T15:52:04.153137+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): needs to be in state WAIT_FOR_START_ATTEN_CHAR for CM_START_ATTEN_CHAR_IND
   2024-12-13T15:52:04.187964+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.195990+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.223092+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.230817+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.259234+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.267262+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.294947+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.302506+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.330610+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.338308+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.365795+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.373390+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.401378+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.409026+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.437202+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.444880+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.473470+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.481479+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.509108+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_MNBC_SOUND_IND
   2024-12-13T15:52:04.517101+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_PROFILE_IND
   2024-12-13T15:52:04.517383+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received all sounds, going to substate FINALIZE_SOUNDING
   2024-12-13T15:52:04.561486+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): Finalize sounding, sending CM_ATTEN_CHAR_IND
   2024-12-13T15:52:04.577453+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): received CM_ATTEN_CHAR_RSP, going to substate WAIT_FOR_SLAC_MATCH
   2024-12-13T15:52:04.615447+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Session (run_id=D895B977488179F2, ev_mac=00:01:87:05:A0:84): Received CM_SLAC_MATCH_REQ, sending CM_SLAC_MATCH_CNF -> session complete
   2024-12-13T15:52:04.616909+0100 chargesom manager[267]: [INFO] evse_slac:EvseS  :: Entered Matched state
   2024-12-13T15:52:04.637408+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO SLAC MATCHED
   2024-12-13T15:52:04.661360+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO D-LINK_READY (true)

Now the EV simulator discovers the V2G service of the Charge SOM and establish a TCP connection.
Both hosts negotiate the protocol ISO 15118-2 and start a charging session. Since the setup
lacks some components of a real DC charger (e.g. HV contactors, power modules) only the state
ChargeParameterDiscovery will be reached.

.. code-block:: sh

   2024-12-13T15:52:06.094909+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Received packet from [fe80::201:87ff:fe05:a084]:52403 with security 0x10 and protocol 0x00
   2024-12-13T15:52:06.094909+0100 chargesom manager[270]: [INFO] iso15118_charge  :: SDP requested NO-TLS, announcing NO-TLS
   2024-12-13T15:52:06.094909+0100 chargesom manager[270]: [INFO] iso15118_charge  :: sendto([fe80::201:87ff:fe05:a084]:52403) succeeded
   2024-12-13T15:52:06.136758+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Incoming connection on eth1 from [a00:f192:0:0:fe80::]:61842
   2024-12-13T15:52:06.137338+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Started new TCP connection thread
   2024-12-13T15:52:06.413206+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Handling SupportedAppProtocolReq
   2024-12-13T15:52:06.414011+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Protocol negotiation was successful. Selected protocol is ISO15118
   2024-12-13T15:52:06.445910+0100 chargesom manager[263]: [INFO] connector:EvseM  ::                                     CAR ISO V2G SupportedAppProtocolReq
   2024-12-13T15:52:06.457489+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO V2G SupportedAppProtocolRes
   2024-12-13T15:52:06.735253+0100 chargesom manager[270]: [INFO] iso15118_charge  :: SessionSetupReq.EVCCID: 00:01:87:05:A0:84
   2024-12-13T15:52:06.735253+0100 chargesom manager[270]: [INFO] iso15118_charge  :: No session_id found or not equal to the id from the preceding v2g session. Generating random session id.
   2024-12-13T15:52:06.735253+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Created new session with id 0x17000314371076655851
   2024-12-13T15:52:06.736833+0100 chargesom manager[263]: [INFO] connector:EvseM  ::                                     CAR ISO V2G SessionSetupReq
   2024-12-13T15:52:06.845708+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO V2G SessionSetupRes
   2024-12-13T15:52:07.142205+0100 chargesom manager[263]: [INFO] connector:EvseM  ::                                     CAR ISO V2G ServiceDiscoveryReq
   2024-12-13T15:52:07.240688+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO V2G ServiceDiscoveryRes
   2024-12-13T15:52:07.567095+0100 chargesom manager[263]: [INFO] connector:EvseM  ::                                     CAR ISO V2G ServiceDetailReq
   2024-12-13T15:52:07.621170+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO V2G ServiceDetailRes
   2024-12-13T15:52:07.921406+0100 chargesom manager[270]: [INFO] iso15118_charge  :: SelectedPaymentOption: ExternalPayment
   2024-12-13T15:52:07.924122+0100 chargesom manager[263]: [INFO] connector:EvseM  ::                                     CAR ISO V2G PaymentServiceSelectionReq
   2024-12-13T15:52:08.053648+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO V2G PaymentServiceSelectionRes
   2024-12-13T15:52:08.338864+0100 chargesom manager[263]: [INFO] connector:EvseM  ::                                     CAR ISO V2G AuthorizationReq
   2024-12-13T15:52:08.391710+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO V2G AuthorizationRes
   2024-12-13T15:52:08.689864+0100 chargesom manager[263]: [INFO] connector:EvseM  ::                                     CAR ISO V2G AuthorizationReq
   2024-12-13T15:52:08.764375+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO V2G AuthorizationRes
   2024-12-13T15:52:09.049641+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Parameter-phase started
   2024-12-13T15:52:09.049641+0100 chargesom manager[270]: [INFO] iso15118_charge  :: Selected energy transfer mode: DC_extended
   2024-12-13T15:52:09.057571+0100 chargesom manager[263]: [INFO] connector:EvseM  :: Received EV maximum limits: {
   2024-12-13T15:52:09.057571+0100 chargesom manager[263]:     "dc_ev_maximum_current_limit": 0.0,
   2024-12-13T15:52:09.057571+0100 chargesom manager[263]:     "dc_ev_maximum_voltage_limit": 0.0
   2024-12-13T15:52:09.057571+0100 chargesom manager[263]: }
   2024-12-13T15:52:09.058568+0100 chargesom manager[263]: [INFO] connector:EvseM  ::                                     CAR ISO V2G ChargeParameterDiscoveryReq
   2024-12-13T15:52:09.147996+0100 chargesom manager[263]: [INFO] connector:EvseM  :: EVSE ISO V2G ChargeParameterDiscoveryRes

Congratulations! You have successfully established a charging session with the EVerest
charging stack and the Charge SOM. Now you are prepared to start your own charging project and
adjust your setup to your needs. The following chapters will help you understand the EVerest
charging stack and Charge SOM in more detail and gain deeper insight into the configuration.
