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

   version: 1
   pt1000s:
     - abort-temperature: 75.0 °C
       resistance-offset: 0.85 Ω
     - abort-temperature: 85.0 °C
       resistance-offset: 1.042 Ω
     - 80.0 °C
     - disabled

   contactors:
     - type: without-feedback
       close-time: 100 ms
       open-time: 100 ms
     - without-feedback
     - disabled

   estops:
     - active-low
     - disabled
     - disabled

.. important::

   The YAML file is required to be encoded in UTF-8. While most parameters are ASCII only, temperature thresholds require
   trailing `°C` suffix which has a special UTF-8 encoding sequence. This might be displayed incorrectly in the editor
   when editing on the device itself and/or finally stored wrong in the YAML file.
   The same applies to the resistance offsets in Ohm.
   When unsure, adapt/create the YAML file on your Linux host system with your preferred editor and transfer it
   to the board via Ethernet network (e.g. SCP/SFTP).

Such a YAML file must be converted to a binary parameter block file afterwards. And this binary parameter block file
must finally be flashed to the safety controller's flash memory, see below.

.. important::

   The YAML file allows to specify a numeric parameter block version. This version is used internally by the
   safety controller firmware to detect the binary structure of the parameter block. It must thus match the
   safety firmware's expectation, otherwise the safety controller will refuse to work and enters safe state directly.


Temperature Channel (PT1000) Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The safety controller supports up to 4 PT1000 temperature channels. Thus the YAML file expects for each channel
a temperature threshold in °C at which the safety controller stops and/or prevents charging. Also for each channel,
an offset value in Ohm can be specified. This offset depends on the actual physical wiring and must be determined
in the specific customer setup.
If a PT1000 channel is not wired/used, it is required to disable this channel using the special word `disabled`
instead of a temperature value.
The example YAML file above shows that the PT1000 configuration is an array with up to 4 items. Each item can either
be a single temperature threshold, the special token `disabled` or it is a key-value list. Valid keys are
`abort-temperature` and `resistance-offset`. If no `resistance-offset` is given, then it is assumed to be zero.

The accepted value range for `abort-temperature` is -80.0 °C to 200.0 °C and it is stored with one decimal digit.

The range for `resistance-offset` is -32.0 Ω ... 32.0 Ω and these values are stored with three decimal digits internally.


Contactor and Contactor Feedback Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The safety controller allows to control up to 3 high-voltage contactors and can monitor corresponding mirror contacts.
The mirror contacts support `Normally Closed` and `Normally Open` semantic, but customer must follow chargebyte's
Charge SOM's EVB reference design otherwise the logic might be inverted.
In the YAML parameterization, it is possible to specify whether the safety controller should actually switch the
corresponding output pin and whether to monitor the feedback input pins. When using the feedback, it is usually also
required to specify the open and closing times of the used contactor. These times are expected in milliseconds and
used by the Safety Firmware to check after the given time whether the feedback pin has expected level. If the level
differs from the expectation, then Safety Firmware assumes a malfunction and thus enters safe state.

The example YAML file above shows all allowed variants how to parameterize a contactor.
Possible values for the `type` are:

- `disabled`
- `without-feedback`
- `with-feedback-normally-open`
- `with-feedback-normally-closed`

Since the open/close timings make no sense in case of `disabled` or `without-feedback`, it is possible to use these
tokens directly as array item (actually, it is also possible to use the `with-feedback...` ones, but then the timings
are considered zero).

Both `close-time` and `open-time` accept integer values in the range 0 to 2550 ms, however the given value is
divided by 10 before it is actually stored internally.


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
   version: 1
   pt1000s:
     - abort-temperature: 85.0 °C
       resistance-offset: 0.85 Ω
     - abort-temperature: 75.0 °C
       resistance-offset: 1.1 Ω
     - disabled
     - disabled

   contactors:
     - without-feedback
     - without-feedback
     - disabled

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
