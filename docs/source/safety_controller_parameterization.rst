.. _safety_controller_parameterization.rst:

Safety Controller Parameterization
----------------------------------


Overview
^^^^^^^^

The safety controller can or must be parameterized to a certain extent. For example, it is required to know
which temperature channels are actually in use and at which temperature thresholds the charging process needs to
be stopped to avoid injuries to users and/or prevent damage to the EVSE itself.
Futhermore, the safety controller can control high-voltage contactors and can then monitor feedback contacts to
detect contactor welding.
It also supports up to four emergency input channels, each can be disabled when not connected/required in
the actual customer setup.

These safety controller parameters are stored as a binary parameter block, directly in the safety controller's flash.
When shipped from factory, there is a default parameter block installed which allows easy evaluation of the product,
but is not intended for production usage in the field.
Customers are encouraged to adjust the parameters to their requirements/needs during deployment of the board into
an actual charger.

To adjust the parameters, some small command line tools are included in the shipped Linux firmware which allow
to create/modify the parameters on the board itself. However, it is also possible to use these tools on a Linux
host system (e.g. in a virtual machine) and then to transfer the created parameter block to each board
and install it.

The mentioned tools are part of the `ra-utils repository <https://github.com/chargebyte/ra-utils>`__ on Github.

To make the handling of parameters human-friendly, all parameters can be put together using a YAML text file.

.. code-block:: yaml

   pt1000s:
     - 75.0 °C
     - 85.0 °C
     - disabled
     - disabled

   contactors:
     - without-feedback
     - without-feedback

   estops:
     - active-low
     - disabled
     - disabled

.. important::

   The YAML file is required to be encoded in UTF-8. While most parameters are ASCII only, temperature thresholds require
   trailing `°C` suffix which has a special UTF-8 encoding sequence. This might be displayed incorrectly in the editor
   when editing on the device itself and/or finally stored wrong in the YAML file.
   When unsure, adapt/create the YAML file on your Linux host system with your preferred editor and transfer it
   to the board via Ethernet network (e.g. SCP/SFTP).

Such a YAML file must be converted to a binary parameter block file afterwards. And this binary parameter block file
must finally be flashed to the safety controller's flash memory, see below.


Temperature Channel (PT1000) Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The safety controller supports up to 4 PT1000 temperature channels. Thus the YAML file expects for each channel
either a temperature threshold in °C at which the safety controller stops and/or prevents charging.
In a PT1000 channel is not wired/used, it is required to disable this channel using the special word `disabled`
instead of a temperature value.


Contactor and Contactor Feedback Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The safety controller allows to control up to 2 high-voltage contactors and can monitor corresponding mirror contacts.
The mirror contacts need to have `Normally Closed` semantic. In the YAML parameterization, it is possible to
specify whether the safety controller should actually switch the corresponding output pin and whether to monitor
the feedback input pins.

Possible parameter values are:

- `disabled`
- `without-feedback`
- `with-feedback`


Emergency Input Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The safety controller can monitor up to 3 emergency inputs.

Possible configuration values are:

- `disabled`
- `active-low`


Installing a Parameter Block
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Once the YAML file is created and fits your charger setup, it is required to convert it to a binary parameter block file.
In the mentioned repository, there exists a tool `ra-pb-create` to generate such a binary file from the YAML file.
The following session transcript shows how the install procedure works:

.. code-block:: sh

   # create a YAML file on-the-fly
   $ cat <<EOL > /tmp/my-parameters.yaml
   pt1000s:
     - 75.0 °C
     - 85.0 °C
     - disabled
     - disabled

   contactors:
     - without-feedback
     - without-feedback

   estops:
     - active-low
     - disabled
     - disabled
   EOL

   # convert YAML to binary
   ra-pb-create -i /tmp/my-parameters.yaml -o /tmp/my-parameters.bin

   # stop EVerest - to have exclusive access to safety controller
   systemctl stop everest

   # flash the parameter block
   ra-update -a data flash /tmp/my-parameters.bin

   # restart EVerest
   systemctl start everest


Checking the Installed Parameter Block
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To check which settings are currently used by the safety controller firmware, it is possible to read back the parameter block.

.. code-block:: sh

   systemctrl stop everest
   ra-update -a data dump | ra-pb-dump

This will print the current settings in YAML format on stdout.
