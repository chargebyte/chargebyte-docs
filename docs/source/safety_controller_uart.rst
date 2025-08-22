.. _safety_controller_uart.rst:

Safety Controller Communication Protocol
----------------------------------------

Packet Format Description
^^^^^^^^^^^^^^^^^^^^^^^^^

Data packet format

Data packets contain payload and can be sent out from host to safety controller or vice versa. Data packets from safety
controller to host can be transmitted periodically or by request via an inquiry packet.
Only one inquiry packet can be requested before requesting the next one.

+--------+--------+--------+-------------------+
| Symbol | Size   | Code   | Description       |
+========+========+========+===================+
| SOF    | 1 byte | 0xA5   | Start of Frame    |
+--------+--------+--------+-------------------+
| ID     | 1 byte |        | Packet Identifier |
+--------+--------+--------+-------------------+
| Data   | 8 byte |        | Payload           |
+--------+--------+--------+-------------------+
| CRC    | 1 byte |        | CRC Checksum      |
+--------+--------+--------+-------------------+
| EOF    | 1 byte | 0x03   | End of Frame      |
+--------+--------+--------+-------------------+


Packet Identifier (ID)
^^^^^^^^^^^^^^^^^^^^^^

The values of the packet identifier (PacketId) are mapped to the messages as summarized below.

+----------+---------------------------+---------------------+-------------------------------------------------------------+----------------------+
| PacketId | Description               | Communication Dir.  | Periodicity                                                 | Triggered by Inquiry |
+==========+===========================+=====================+=============================================================+======================+
| 0x11     | Charge Control 2          | Host → Safety       | periodically, every 100ms OR immediately if changes occur   | No                   |
+----------+---------------------------+---------------------+-------------------------------------------------------------+----------------------+
| 0x10     | Charge State 2            | Safety → Host       | periodically, every 100ms                                   | No                   |
+----------+---------------------------+---------------------+-------------------------------------------------------------+----------------------+
| 0x08     | PT1000 State              | Safety → Host       | periodically, every 100ms                                   | No                   |
+----------+---------------------------+---------------------+-------------------------------------------------------------+----------------------+
| 0x0A     | Firmware Version          | Safety → Host       | no, only upon request via inquiry packet                    | Yes                  |
+----------+---------------------------+---------------------+-------------------------------------------------------------+----------------------+
| 0x0B     | GIT Hash                  | Safety → Host       | no, only upon request via inquiry packet                    | Yes                  |
+----------+---------------------------+---------------------+-------------------------------------------------------------+----------------------+
| 0xFF     | Inquiry Packet            | Host → Safety       | no, only to trigger inquiries                               | No                   |
+----------+---------------------------+---------------------+-------------------------------------------------------------+----------------------+

CRC Checksum Field
^^^^^^^^^^^^^^^^^^

The checksum is defined over:

::

    Width       = 8
    Poly        = 0x1d
    XorIn       = 0xff
    ReflectIn   = False
    XorOut      = 0xff
    ReflectOut  = False
    Algorithm   = table-driven
    Name        = CRC8 SAE J1850

.. include:: safety_protocol.rst
