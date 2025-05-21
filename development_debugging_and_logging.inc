.. _logging_and_debugging:

Logging and Debugging
=====================

There are different ways to analyze the EVerest charging software. In the following, different
ways are described. In preparation for starting this chapter, it is necessary to be connected to the board
via Ethernet. This is also necessary to copy logs and traces from the board to the local PC via a SFTP
tool like `WinSCP <https://winscp.net/eng/download.php>`_ or `FileZilla <https://filezilla-project.org/>`_. 

journalctl Logs
---------------
As already described in the :ref:`start_charging_and_monitoring` section, the EVerest framework uses
journalctl for logging. journalctl is a system service that collects and stores logging data.
To view the logs, connect to the charge controller via SSH and run the following command:

.. code-block:: console

    journalctl -f -n 100 -u everest

The -f flag is used to follow the logs live, and the -n flag is used to view the last 100 lines.
The -u flag is used to filter the logs for the everest service. To stop following the logs, press :code:`Ctrl + C`.

The logs are stored by the systemd journal service in a binary format in
"/var/log/journal". To open the binary in a human-readable format, use the following command:

.. code-block:: console
    
    journalctl -u everest --file /path/to/your/file.journal

As shown in the :ref:`start_charging_and_monitoring` section, a log line consists, among other things,
of a timestamp, a log level, a module id, a module name, and a message. The log level can be one of the following:

    - "VERB" (Verbose)
    - "DEBG" (Debug)
    - "INFO" (Information)
    - "WARN" (Warning)
    - "ERRO" (Error)
    - "CRIT" (Critical)

The log level can be configured for each EVerest module separately in the logging configuration file.
The logging configuration file is located at "/etc/everest/default_logging.cfg". The filter can be configured
using the log level and the module identifier as defined in the EVerest configuration.
Here is an example to configure the message filter to change the log level of the EvseManager module
to DEBUG:

.. code-block:: console

    # The filter expression consists of two parts:
    # 1. Logs with severity level INFO or higher (affects all EVerest modules).
    # 2. Logs from the EvseManager with module id "connector" with severity level DEBUG or higher.
    Filter="(%Severity% >= INFO) or (%Process% contains connector and %Severity% >= DEBG)"

pcap Traces
-----------
pcap traces can be used to debug and analyze the high-level communication (HLC) between SECC and EVCC.
In general, there are two ways to capture pcap traces:

#. Capture via tcpdump command

    .. code-block:: console

        tcpdump -i eth1 -w /srv/charge_com_01.pcap 

    This command captures all packets on the eth1 (PLC) interface and writes them to
    a pcap file. Stop the capture by pressing :code:`Ctrl + C`.

    .. note::
        Please stop the trace before copying the file to a local machine. The file may be incomplete if
        copied while the tcpdump is still running.

#. Using the EVerest "PacketSniffer" module

    The `PacketSniffer <https://github.com/EVerest/everest-core/tree/main/modules/PacketSniffer>`_ module
    is part of everest-core and can be used to capture pcap traces automatically. Please look into
    the module manifest to see how to configure the PacketSniffer module.

pcap traces with V2G communication can be analyzed using Wireshark with a V2G plugin like from `dSPACE <https://www.dspace.com/en/pub/home/news/wireshark-charging-plug-in.cfm>`_.

.. note::
    TLS encrypted communication cannot be analyzed with Wireshark without the TLS session key. Please
    look in the module manifest which is responsible for the TLS handshake and check if there is an option
    to export the TLS session key. E.g. the `IsoMux module <https://github.com/EVerest/everest-core/blob/main/modules/IsoMux/manifest.yaml>`_
    is able to export the TLS session key.

Session Logging of the EVSEManager
----------------------------------
The EVerest "EVSEManager" can generate session log files with information about the current session state,
configured CP state and duty cycle. It can also decode and log the content of the V2G messages.
Please look into the module manifest to see how to configure the EVSEManager module to activate session logging.

.. note::
    The session logging is pretty performance intensive and should only be used for debugging purposes.

MQTT logs
---------
It is also possible to observe the internal MQTT communication between the EVerest modules.
When developing new modules, this can be helpful to better understand the internal processes regarding
the use of the interfaces.
We recommend using the `MQTT Explorer <https://mqtt-explorer.com/>`_ tool to monitor and analyze the MQTT communication.
It is also possible to use the following command to monitor the MQTT communication, but this is not so easy to read:

.. code-block:: console

    mosquitto_sub -F "[@H:@M:@S.@N] %t %p" -t 'everest/#' -t 'everest_api/#' > /srv/charge_com_mqtt_01.log

Summary
-------
There are several ways to debug and analyze the EVerest framework. Which way to choose depends on the
specific use case and the information needed. The most common way is using journalctl logs. If it is
necessary to analyze the high-level communication between SECC and EVCC, pcap traces are the best choice.
If it is not clear how the internal communication between the EVerest modules works, the MQTT logs can
be helpful.
