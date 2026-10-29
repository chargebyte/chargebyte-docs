WebUI
=====

The WebUI provides browser-based access to the most important configuration,
maintenance, and diagnostic functions of the charging controller. The pages
shown in the navigation depend on the device configuration and the available
EVerest modules.

Open the WebUI using the address supplied for the device. On first use, define
the initial password; afterwards, sign in with the configured credentials. Use
**Logout** when leaving a shared service computer. Configuration changes can
restart services or the complete device, so perform maintenance only while the
charging point is not in use.

EVerest Config
--------------

**EVerest Config** shows the settings exposed by the active EVerest
configuration, for example charging modes and Profinet parameters. Select
**Save Configuration** to apply edited values or **Reload Configuration** to
discard unsaved edits and read the current values again.

The complete ``config.yaml`` can also be downloaded for backup. **Upload and
Apply** checks and installs a selected YAML configuration and then restarts
EVerest. Keep a known-good backup: an invalid or incomplete configuration can
prevent EVerest from starting.

.. figure:: ../../includes/_static/images/webui/everest-config.png
   :alt: EVerest Config page
   :align: center
   :width: 100%
   :target: ../../includes/_static/images/webui/everest-config.png

   Editing and transferring the EVerest configuration.

Safety Controller
-----------------

**Safety Controller** displays the current settings of each detected safety
controller in a separate section. Depending on the hardware, these settings
include PT1000 overtemperature protection, contactor feedback and timing, and
emergency-stop input behavior. Unavailable or read-only controllers are
identified on the page.

Review every value before selecting **Save Configuration**. Applying these
settings temporarily stops EVerest and writes the safety controller. Do not
disconnect power or operate the charging point until verification has
finished.

.. figure:: ../../includes/_static/images/webui/safety-controller.png
   :alt: Safety Controller page
   :align: center
   :width: 100%
   :target: ../../includes/_static/images/webui/safety-controller.png

   Safety settings for a detected controller.

OCPP Config
-----------

Use **OCPP Config** to set the CSMS endpoint, Charge Point ID, security
controller identity, authentication password, and OCPP security profile.
Fields that are not supported by the active EVerest configuration are marked
as unavailable. Select **Save Configuration** after checking the endpoint and
credentials with the CSMS operator.

.. figure:: ../../includes/_static/images/webui/ocpp-config.png
   :alt: OCPP Config page
   :align: center
   :width: 100%
   :target: ../../includes/_static/images/webui/ocpp-config.png

   OCPP connection and security settings.

PCAP Trace
----------

**PCAP Trace** records network traffic for troubleshooting. Select the network
interface and, if required, enable the V2G HLC filter to limit the capture to
IPv6 and SLAC traffic. Start the recording, reproduce the problem, then stop
and download the ``.pcap`` file. Captures can contain addresses, identifiers,
and protocol data; share them only through approved support channels.

.. figure:: ../../includes/_static/images/webui/pcap-trace.png
   :alt: PCAP Trace page
   :align: center
   :width: 100%
   :target: ../../includes/_static/images/webui/pcap-trace.png

   Selecting an interface and recording a network trace.

Firmware Update
---------------

**Firmware Update** displays the installed version and accepts a controller
firmware image. Choose the image, select **Start Update**, and wait until the
upload and installation finish. If requested, use **Reboot** and wait for the
login page to return. Never interrupt power during an update.

This page also contains **Factory Reset**. A factory reset removes local
settings and requires confirmation; use it only when the resulting data loss
is intended.

.. figure:: ../../includes/_static/images/webui/firmware-update.png
   :alt: Firmware Update page
   :align: center
   :width: 100%
   :target: ../../includes/_static/images/webui/firmware-update.png

   Firmware upload, reboot, and factory-reset controls.

System Logs
-----------

**System Logs** provides downloadable diagnostic files and an extract from the
system journal. Select one or more listed files and choose **Download
Selected**. For a journal extract, choose the boot range, optionally limit the
output to ``everest.service``, and display or download the generated text.
Review logs for sensitive information before forwarding them.

.. figure:: ../../includes/_static/images/webui/system-logs.png
   :alt: System Logs page
   :align: center
   :width: 100%
   :target: ../../includes/_static/images/webui/system-logs.png

   Downloadable files and system-journal extraction.

Network Configuration
---------------------

**Network Configuration** shows the detected Ethernet and CAN interfaces. For
Ethernet, select DHCP or enter a static IPv4 address, prefix, gateway, and DNS
servers. For CAN, select a standard or custom bitrate. **Save** stages the
settings and **Apply** activates them; factory defaults can also be staged and
applied.

Applying network changes can immediately disconnect the browser. Verify the
new address and ensure that an alternative access method is available before
changing the management interface.

.. figure:: ../../includes/_static/images/webui/network-configuration.png
   :alt: Network Configuration page
   :align: center
   :width: 100%
   :target: ../../includes/_static/images/webui/network-configuration.png

   IPv4 and CAN interface configuration.

SSH Configuration
-----------------

**SSH Configuration** shows whether SSH is enabled. Use **Enable SSH** or
**Disable SSH** to control remote shell access. When SSH is enabled, enter and
repeat a new root password, then select **Set Password**. Use a unique, strong
password and disable SSH when maintenance is complete. Disabling the service
does not terminate sessions that are already connected.

.. figure:: ../../includes/_static/images/webui/ssh-configuration.png
   :alt: SSH Configuration page
   :align: center
   :width: 100%
   :target: ../../includes/_static/images/webui/ssh-configuration.png

   SSH service status and root-password controls.
