ChargeControl2
^^^^^^^^^^^^^^

**ID**: 0x11 (17)

**Length**: 8 bytes

**Description**: N/A

**Senders**: CCY_HostController

.. list-table:: Signals in ChargeControl2
   :widths: 30 6 6 10 7 7 7 6 30
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
     - Description
   * - CC_ControllerReset
     - 3
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CC_CCSReady
     - 7
     - 4
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*

**Value Descriptions**

- **CC_CCSReady**

  - 0x0 = CCS_NotReady
  - 0x1 = CCS_Ready
  - 0x2 = CCS_EmergencyStop

**Bitfield Layout**

::

                         Bit

            7   6   5   4   3   2   1   0
          +---+---+---+---+---+---+---+---+
        0 |<-------------x|<-----x|   |   |
          +---+---+---+---+---+---+---+---+
                        |       +-- CC_ControllerReset
                        +-- CC_CCSReady
          +---+---+---+---+---+---+---+---+
        1 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
    B   2 |   |   |   |   |   |   |   |   |
    y     +---+---+---+---+---+---+---+---+
    t   3 |   |   |   |   |   |   |   |   |
    e     +---+---+---+---+---+---+---+---+
        4 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        5 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        6 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        7 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+



ChargeState2
^^^^^^^^^^^^

**ID**: 0x10 (16)

**Length**: 8 bytes

**Description**: N/A

**Senders**: Safety Controller

.. list-table:: Signals in ChargeState2
   :widths: 30 6 6 10 7 7 7 6 30
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
     - Description
   * - CS_ID_State
     - 3
     - 4
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_CE_State
     - 7
     - 4
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_EStop_Reason
     - 15
     - 8
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_SafeStateActive
     - 23
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - This signal reports, if the controller is in safeState or not.

**Value Descriptions**

- **CS_ID_State**

  - 0x0 = Unknown
  - 0x1 = Not Connected
  - 0x2 = Connected
  - 0x3 = Invalid

- **CS_CE_State**

  - 0x0 = Unknown
  - 0x1 = A
  - 0x2 = B0
  - 0x3 = B
  - 0x4 = C
  - 0x5 = E
  - 0x6 = EC
  - 0x7 = Invalid

- **CS_EStop_Reason**

  - 0x0 = NoStop
  - 0x1 = InternalError
  - 0x2 = ComTimeout
  - 0x3 = Temp1_Malfunction
  - 0x4 = Temp2_Malfunction
  - 0x5 = Temp3_Malfunction
  - 0x6 = Temp4_Malfunction
  - 0x7 = Temp1_Overtemp
  - 0x8 = Temp2_Overtemp
  - 0x9 = Temp3_Overtemp
  - 0xA = Temp4_Overtemp
  - 0xB = ID_Malfunction
  - 0xC = CE_Malfunction
  - 0xD = HVReady_Malfunction
  - 0xE = EmergencyInput

- **CS_SafeStateActive**

  - 0x0 = NormalState
  - 0x1 = SafeState
  - 0x3 = SNA

**Bitfield Layout**

::

                         Bit

            7   6   5   4   3   2   1   0
          +---+---+---+---+---+---+---+---+
        0 |<-------------x|<-------------x|
          +---+---+---+---+---+---+---+---+
                        |               +-- CS_ID_State
                        +-- CS_CE_State
          +---+---+---+---+---+---+---+---+
        1 |<-----------------------------x|
          +---+---+---+---+---+---+---+---+
                                        +-- CS_EStop_Reason
          +---+---+---+---+---+---+---+---+
    B   2 |<-----x|   |   |   |   |   |   |
    y     +---+---+---+---+---+---+---+---+
    t           +-- CS_SafeStateActive
    e     +---+---+---+---+---+---+---+---+
        3 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        4 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        5 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        6 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        7 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+



PT1000State
^^^^^^^^^^^

**ID**: 0x8 (8)

**Length**: 8 bytes

**Description**: This message shall be sent from safety controller to host processor for indicating the state of the connected temperature sensors

**Senders**: chargeSOM_SafetyController, Safety Controller

.. list-table:: Signals in PT1000State
   :widths: 30 6 6 10 7 7 7 6 30
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
     - Description
   * - PT1_Temperature
     - 7
     - 14
     - Big Endian
     - Yes
     - 0.1
     - 0
     - °C
     - Current temperature of PT1000 channel in °C with one decimal digit. 0x1FFF stands for: temp sensor not used.
   * - PT1_ChargingStopped
     - 8
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Indicates whether this PT1000 channel prevents charging, multiple channel can signal the condition in parallel.
   * - PT1_SelftestFailed
     - 9
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Indicates whether this PT1000 channel is disturbed, multiple channel can signal the condition in parallel.
   * - PT2_Temperature
     - 23
     - 14
     - Big Endian
     - Yes
     - 0.1
     - 0
     - °C
     - Current temperature of PT1000 channel in °C with one decimal digit. 0x1FFF stands for: temp sensor not used.
   * - PT2_ChargingStopped
     - 24
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Indicates whether this PT1000 channel prevents charging, multiple channel can signal the condition in parallel.
   * - PT2_SelftestFailed
     - 25
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Indicates whether this PT1000 channel is disturbed, multiple channel can signal the condition in parallel.
   * - PT3_Temperature
     - 39
     - 14
     - Big Endian
     - Yes
     - 0.1
     - 0
     - °C
     - Current temperature of PT1000 channel in °C with one decimal digit. 0x1FFF stands for: temp sensor not used.
   * - PT3_ChargingStopped
     - 40
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Indicates whether this PT1000 channel prevents charging, multiple channel can signal the condition in parallel.
   * - PT3_SelftestFailed
     - 41
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Indicates whether this PT1000 channel is disturbed, multiple channel can signal the condition in parallel.
   * - PT4_Temperature
     - 55
     - 14
     - Big Endian
     - Yes
     - 0.1
     - 0
     - °C
     - Current temperature of PT1000 channel in °C with one decimal digit. 0x1FFF stands for: temp sensor not used.
   * - PT4_ChargingStopped
     - 56
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Indicates whether this PT1000 channel prevents charging, multiple channel can signal the condition in parallel.
   * - PT4_SelftestFailed
     - 57
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Indicates whether this PT1000 channel is disturbed, multiple channel can signal the condition in parallel.

**Value Descriptions**

- **PT1_Temperature**

  - 0x1FFF = TempSensorNotUsed

- **PT2_Temperature**

  - 0x1FFF = TempSensorNotUsed

- **PT3_Temperature**

  - 0x1FFF = TempSensorNotUsed

- **PT4_Temperature**

  - 0x1FFF = TempSensorNotUsed

**Bitfield Layout**

::

                         Bit

            7   6   5   4   3   2   1   0
          +---+---+---+---+---+---+---+---+
        0 |<------------------------------|
          +---+---+---+---+---+---+---+---+
        1 |----------------------x|<-x|<-x|
          +---+---+---+---+---+---+---+---+
                                |   |   +-- PT1_ChargingStopped
                                |   +-- PT1_SelftestFailed
                                +-- PT1_Temperature
          +---+---+---+---+---+---+---+---+
        2 |<------------------------------|
          +---+---+---+---+---+---+---+---+
        3 |----------------------x|<-x|<-x|
          +---+---+---+---+---+---+---+---+
                                |   |   +-- PT2_ChargingStopped
    B                           |   +-- PT2_SelftestFailed
    y                           +-- PT2_Temperature
    t     +---+---+---+---+---+---+---+---+
    e   4 |<------------------------------|
          +---+---+---+---+---+---+---+---+
        5 |----------------------x|<-x|<-x|
          +---+---+---+---+---+---+---+---+
                                |   |   +-- PT3_ChargingStopped
                                |   +-- PT3_SelftestFailed
                                +-- PT3_Temperature
          +---+---+---+---+---+---+---+---+
        6 |<------------------------------|
          +---+---+---+---+---+---+---+---+
        7 |----------------------x|<-x|<-x|
          +---+---+---+---+---+---+---+---+
                                |   |   +-- PT4_ChargingStopped
                                |   +-- PT4_SelftestFailed
                                +-- PT4_Temperature



FirmwareVersion
^^^^^^^^^^^^^^^

**ID**: 0xA (10)

**Length**: 8 bytes

**Description**: This message provides information about the type and version of the flashed firmware

**Senders**: chargeSOM_SafetyController, Safety Controller

.. list-table:: Signals in FirmwareVersion
   :widths: 30 6 6 10 7 7 7 6 30
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
     - Description
   * - MajorVersion
     - 7
     - 8
     - 
     - No
     - 1
     - 0
     - 
     - Major version of the firmware
   * - MinorVersion
     - 15
     - 8
     - 
     - No
     - 1
     - 0
     - 
     - Minor version of the firmware
   * - BuildVersion
     - 23
     - 8
     - 
     - No
     - 1
     - 0
     - 
     - Build or patch version of the firmware
   * - PlatformType
     - 31
     - 8
     - 
     - No
     - 1
     - 0
     - 
     - This firmware can be used for several products with minor changes in the build process. The platform type describes the used platform
   * - ApplicationType
     - 39
     - 8
     - 
     - No
     - 1
     - 0
     - 
     - The type of firmware. See possible values below
   * - ParameterVersion
     - 47
     - 16
     - Big Endian
     - No
     - 1
     - 0
     - 
     - Version of the parameter file

**Value Descriptions**

- **PlatformType**

  - 0x81 = chargeSOM
  - 0x82 = CCY

- **ApplicationType**

  - 0x3 = Firmware
  - 0x4 = End Of Line
  - 0x5 = Qualification

**Bitfield Layout**

::

                         Bit

            7   6   5   4   3   2   1   0
          +---+---+---+---+---+---+---+---+
        0 |<-----------------------------x|
          +---+---+---+---+---+---+---+---+
                                        +-- MajorVersion
          +---+---+---+---+---+---+---+---+
        1 |<-----------------------------x|
          +---+---+---+---+---+---+---+---+
                                        +-- MinorVersion
          +---+---+---+---+---+---+---+---+
        2 |<-----------------------------x|
          +---+---+---+---+---+---+---+---+
                                        +-- BuildVersion
    B     +---+---+---+---+---+---+---+---+
    y   3 |<-----------------------------x|
    t     +---+---+---+---+---+---+---+---+
    e                                   +-- PlatformType
          +---+---+---+---+---+---+---+---+
        4 |<-----------------------------x|
          +---+---+---+---+---+---+---+---+
                                        +-- ApplicationType
          +---+---+---+---+---+---+---+---+
        5 |<------------------------------|
          +---+---+---+---+---+---+---+---+
        6 |------------------------------x|
          +---+---+---+---+---+---+---+---+
                                        +-- ParameterVersion
          +---+---+---+---+---+---+---+---+
        7 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+



GitHash
^^^^^^^

**ID**: 0xB (11)

**Length**: 8 bytes

**Description**: This message provides information about the GIT hash, written in the firmware

**Senders**: chargeSOM_SafetyController, Safety Controller

.. list-table:: Signals in GitHash
   :widths: 30 6 6 10 7 7 7 6 30
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
     - Description
   * - HashSignal
     - 7
     - 64
     - Big Endian
     - No
     - 1
     - 0
     - 
     - First 8 byte of the 160 bit (SHA-1) GIT hash

**Bitfield Layout**

::

                         Bit

            7   6   5   4   3   2   1   0
          +---+---+---+---+---+---+---+---+
        0 |<------------------------------|
          +---+---+---+---+---+---+---+---+
        1 |-------------------------------|
          +---+---+---+---+---+---+---+---+
        2 |-------------------------------|
          +---+---+---+---+---+---+---+---+
    B   3 |-------------------------------|
    y     +---+---+---+---+---+---+---+---+
    t   4 |-------------------------------|
    e     +---+---+---+---+---+---+---+---+
        5 |-------------------------------|
          +---+---+---+---+---+---+---+---+
        6 |-------------------------------|
          +---+---+---+---+---+---+---+---+
        7 |------------------------------x|
          +---+---+---+---+---+---+---+---+
                                        +-- HashSignal



InquiryPacket
^^^^^^^^^^^^^

**ID**: 0xFF (255)

**Length**: 8 bytes

**Description**: This packet is used to request a special message from the safety controller

**Senders**: chargeSOM_HostController, CCY_HostController

.. list-table:: Signals in InquiryPacket
   :widths: 30 6 6 10 7 7 7 6 30
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
     - Description
   * - PacketId
     - 7
     - 8
     - 
     - No
     - 1
     - 0
     - 
     - The ID, which message shall be requested. Supported values are described below.

**Value Descriptions**

- **PacketId**

  - 0xA = FirmwareVersion
  - 0xB = GitHash

**Bitfield Layout**

::

                         Bit

            7   6   5   4   3   2   1   0
          +---+---+---+---+---+---+---+---+
        0 |<-----------------------------x|
          +---+---+---+---+---+---+---+---+
                                        +-- PacketId
          +---+---+---+---+---+---+---+---+
        1 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
    B   2 |   |   |   |   |   |   |   |   |
    y     +---+---+---+---+---+---+---+---+
    t   3 |   |   |   |   |   |   |   |   |
    e     +---+---+---+---+---+---+---+---+
        4 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        5 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        6 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+
        7 |   |   |   |   |   |   |   |   |
          +---+---+---+---+---+---+---+---+



