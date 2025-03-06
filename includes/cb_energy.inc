.. _introduction_nymea:

Introduction CB energy
======================
CB energy is a (home) energy management system.
A CB energy installation consists of two parts:

The first part is the nymea:core (nymead) which is a server application running on the wallbox.
The main application of the nymea:core is to connect the wallbox with 3rd party local energy assets (PV, meters, home storage, ...) and enables features like:

* load balancing
* overload protection
* surplus charging
* energy management
* spot market charging
* remote access
* providing charging reports
* target time charging
* and more

The second part is the CB energy app running on end user platforms like iOS and Android. The app is used to control
nymea:core.
The nymea:core and the different integration plugins for wallbox, meters and inverters are open source
and can be found on `Github <https://github.com/nymea>`_.
Features like generating chargingsession report and the energy management are closed source and require a license
from chargebyte GmbH. For more information have a look `on our website <https://chargebyte.com/software/energy-manager>`_.


Both parts have to be in the same network. In order to monitor and control the wallboxes, the Everest charging stack is needed. The Everest stack provides an API module, that is used by CB Energy either on localhost (on the same hardware) or to access other instances in the same local network. 

Note: This documentation is a quick start to get the nymea ecosystem running as fast as possible with Everest charging stack. If you are about to test CB Energy on one of chargebyte's Linux controllers, both EVerest and CB Energy are preinstalled in the latest firmware images. A more detailed documentation can be found `on the nymea website <https://nymea.io>`_.

.. important::
  The `API module <https://github.com/EVerest/everest-core/tree/main/modules/API>`_ must be installed and active in the EVerest configuration.


.. _cb_energy_app:

CB energy app
=============

The CB energy app can be installed from the official stores.

.. raw:: html

   <table border="0" align="center">
  <tr>
    <td> 
      <p>
        <a href="https://apps.apple.com/us/app/cb-energy/id6503952899">
          <img border="0" align="middle" alt="iOS Badge" src="https://developer.apple.com/app-store/marketing/guidelines/images/badge-example-preferred_2x.png" width=200>
     </p>
    </td>
    <td> 
      <p>
         <a href="https://play.google.com/store/apps/details?id=com.chargebyte.cbenergy&hl=en">
         <img border="0" align="middle" alt="Android Badge" src="https://play.google.com/intl/en_us/badges/static/images/badges/en_badge_web_generic.png" width=256>
     </p>
    </td>
  </tr>
    </table>

.. _setup_and_configuration:

Setup and configuration
=======================

On a chargebyte controller, the nymea Daemon will start automatically, together with the Everest stack while the system is booting up.
Once the services are running the app will be able to detect the instance automatically on localhost or in the local network.


.. _client_discovery:

Client discovery
================

The CB energy App (client) automatically discovers available instances (servers) in your local network. Please make sure to allow the Smartphone App to have access to your local network devices after installing it.

.. figure:: ../../includes/_static/images/cbenergy/discover.png
	:height: 600px

If the discovery has not found any wallbox in the local network you can try to setup an manual connection as described in :ref:`connection_option`.


.. _user_setup:

User setup
================

Once you are connected to the nymea:core, you can start to set up your system.

.. figure:: ../../includes/_static/images/cbenergy/user.png
	:height: 600px

It is time to create login credentials to keep the CB energy setup protected. When connecting to the system for the first time, it will prompt for a username and a password. Optionally, you can also provide your name and E-Mail address.
This information is stored locally.



.. _setup:

Setup of ecosystem
=========================

In the next step, nymea:core starts a discovery for EV Chargers. This might be the same machine (localhost) or any other supported Charger in the local network.

.. figure:: ../../includes/_static/images/cbenergy/setup.png

If you are trying CB energy on a chargebyte controller an EVerest connector will be discovered.


After discovering and setting up the  wallbox, CB Energy tries to discover other assets like solar inverters and meters. If there aren't any of these devices around, you can skip this step.

.. figure:: ../../includes/_static/images/cbenergy/setup-skip.png
	:height: 600px

Basically, you don't need solar inverters or meters for controlling the wallbox. If you want to make use of the ``Eco mode``, you need to add at least one meter measuring the overall consumption of the house.


The final steps of the wizard are

* to set a grid limit for overload protection
* add your initial EV parameters with name, netto battery capacity and minimum charging current as well as phase count of the on-board-charger

.. figure:: ../../includes/_static/images/cbenergy/setup-final.png

You can change this option later in the settings as well.



.. _home:

Home screen
===========

Well done! At this point you are ready to explore the Home Screen, the charging modes (``Eco`` and ``Quick``) and all the other capabilities of CB energy.
As mentioned in `setup`_, ``Eco mode`` is only available if at least one root meter is registered in the system. With ``Quick mode`` however, you should be able to control basic charging features like starting and stopping a charging session as well as adjusting the charging power. Give it a try!

.. figure:: ../../includes/_static/images/cbenergy/home.png



.. _supported_devices:

Supported devices
=================

Here you find a list of `supported devices <https://www.nymea.energy/integrations/>`_.
CB energy comes with license, maintenance, support and service level agreement. So for the number of integrations you want to use in your final product (e.g. smart EV charger with embedded HEMS), we make sure all integrations are maintained and work as intended.

Since the fundamental IoT middleware of CB energy - nymea - is open source, you can add your own integration to the stack. The developer guide can be found `here <https://nymea.io/documentation/developers/integrations/getting-started-integration>`_.



.. _connection_option:

Manual connection option
========================

If Discovery between CB energy app (client) and nymea:core (server) fails for some reason (e.g. blocked UPnP/ZeroConf in company network), you can still enter the endpoints manually.
There are three options for the connection protocol:

#. TCP
#. Websocket
#. RemoteProxy

For simply hooking up client and server locally, choose TCP and enter the IP address of your nymea:core instance. For the first
time you can keep the port at 2222.

.. figure:: ../../includes/_static/images/cbenergy/manual.png
	:height: 600px
