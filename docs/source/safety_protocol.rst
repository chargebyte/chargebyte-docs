ChargeControl1
^^^^^^^^^^^^^^

**ID**: 0x6 (6)

**Length**: 8 bytes

**Description**: This message shall be sent from the host processor to the safety controller to control the peripherals connected to the safety controller.

**Senders**: chargeSOM_HostController

.. list-table:: Signals in ChargeControl1
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
   * - CC_TargetDutyCycle
     - 1
     - 10
     - Big Endian
     - No
     - 0.1
     - 0
     - %
     - Duty cycle between 0.0 and 100.0%. Values above 100.0% are set as 100%. Only valid if the signal CC_PWM_Active is 1
   * - CC_PWM_Active
     - 7
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - This flag indicates if the PWM should be activated. At a value of 0, the CP level is also 0V. At a value of 1, the CP level is dependant of the duty cycle
   * - CC_Contactor1State
     - 16
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Request to close the contactor state. A value of 0 means open contactor, a value of 1 means closed contactor. The contactors are only closed if the system has no errors and is in state C.
   * - CC_Contactor2State
     - 17
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Request to close the contactor state. A value of 0 means open contactor, a value of 1 means closed contactor. The contactors are only closed if the system has no errors and is in state C.
   * - CC_Contactor3State
     - 18
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Request to close the contactor state. A value of 0 means open contactor, a value of 1 means closed contactor. The contactors are only closed if the system has no errors and is in state C.

**Bitfield Layout**

::

   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
   |         7          |         6          |         5          |         4          |         3          |         2          |         1          |         0          |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  0|   CC_PWM_Active    |                    |                    |                    |                    |                    | CC_TargetDutyCycle |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  1|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  2|                    |                    |                    |                    |                    | CC_Contactor3State | CC_Contactor2State | CC_Contactor1State |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  3|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  4|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  5|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  6|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  7|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+

ChargeState1
^^^^^^^^^^^^

**ID**: 0x7 (7)

**Length**: 8 bytes

**Description**: This message shall be sent from safety controller to host processor for indicating the state of the charging session as well as the state of connected peripherals.

**Senders**: chargeSOM_SafetyController

.. list-table:: Signals in ChargeState1
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
   * - CS_CurrentDutyCycle
     - 1
     - 10
     - Big Endian
     - No
     - 0.1
     - 0
     - %
     - The current duty cycle between 0.0% and 100.0%. If the PWM is not aczive this signal is 0
   * - CS_SafeStateActive
     - 3
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - This signal reports, if the controller is in safeState or not.
   * - CS_PWM_Active
     - 7
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Feedback if PWM is active. 0 means not active, 1 means active
   * - CS_CurrentCpState
     - 18
     - 3
     - 
     - No
     - 1
     - 0
     - 
     - Current state of the control pilot. See value mappings below
   * - CS_CpShortCircuit
     - 19
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Is set when the safety controller detects a short-circuit condition between CP and PE line.
   * - CS_DiodeFault
     - 20
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Is set when the safety controller detects that the diode on EV side is missing.
   * - CS_CurrentPpState
     - 26
     - 3
     - 
     - No
     - 1
     - 0
     - 
     - State of the proximity pin. For fixed cables at CCS2, this value is 0x0: No Cable detected
   * - CS_Contactor1State
     - 33
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - State of contactor 1
   * - CS_Contactor2State
     - 35
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - State of contactor 2
   * - CS_Contactor3State
     - 37
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - State of contactor 3
   * - CS_HV_Ready
     - 38
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - This is the state of the HV ready or State C output. This output is high, if the chargeSOM dont see any errors and CP is at state C. Otherwise it is low.
   * - CS_Estop1ChargingAbort
     - 41
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_Estop2ChargingAbort
     - 43
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_Estop3ChargingAbort
     - 45
     - 2
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_SafeStateReason
     - 55
     - 8
     - 
     - No
     - 1
     - 0
     - 
     - This signal describes in which module a fault was detected, why the controller went into safeState

**Value Descriptions**

- **CS_SafeStateActive**

  - 0x0 = NormalState
  - 0x1 = SafeState
  - 0x3 = SNA

- **CS_CurrentCpState**

  - 0x0 = Unknown
  - 0x1 = A
  - 0x2 = B
  - 0x3 = C
  - 0x4 = D
  - 0x5 = E
  - 0x6 = F
  - 0x7 = Invalid

- **CS_CurrentPpState**

  - 0x0 = NoCableDetected
  - 0x1 = 13A
  - 0x2 = 20A
  - 0x3 = 32A
  - 0x4 = 63/70A
  - 0x5 = Type1_Connected
  - 0x6 = Type1_ConnectedButtonPressed
  - 0x7 = Error

- **CS_Contactor1State**

  - 0x0 = UNDEFINED
  - 0x1 = OPEN
  - 0x2 = CLOSE
  - 0x3 = NotConfigured

- **CS_Contactor2State**

  - 0x0 = UNDEFINED
  - 0x1 = OPEN
  - 0x2 = CLOSE
  - 0x3 = NotConfigured

- **CS_Contactor3State**

  - 0x0 = UNDEFINED
  - 0x1 = OPEN
  - 0x2 = CLOSE
  - 0x3 = NotConfigured

- **CS_Estop1ChargingAbort**

  - 0x0 = FALSE
  - 0x1 = TRUE
  - 0x3 = NotConfigured

- **CS_Estop2ChargingAbort**

  - 0x0 = FALSE
  - 0x1 = TRUE
  - 0x3 = NotConfigured

- **CS_Estop3ChargingAbort**

  - 0x0 = FALSE
  - 0x1 = TRUE
  - 0x3 = NotConfigured

- **CS_SafeStateReason**

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
  - 0xB = PP_Malfunction
  - 0xC = CP_Malfunction
  - 0xD = CP_ShortCircuit
  - 0xE = CP_DiodeFault
  - 0xF = HVSW_Malfunction
  - 0x10 = EmergencyInput1
  - 0x11 = EmergencyInput2
  - 0x12 = EmergencyInput3

**Bitfield Layout**

::

   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
   |         7          |         6          |         5          |         4          |         3          |         2          |         1          |         0          |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  0|   CS_PWM_Active    |                    |                    |                    | CS_SafeStateActive |                    |CS_CurrentDutyCycle |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  1|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  2|                    |                    |                    |   CS_DiodeFault    | CS_CpShortCircuit  | CS_CurrentCpState  |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  3|                    |                    |                    |                    |                    | CS_CurrentPpState  |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  4|                    |    CS_HV_Ready     | CS_Contactor3State |                    | CS_Contactor2State |                    | CS_Contactor1State |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  5|                    |                    |CS_Estop3ChargingAbo|                    |CS_Estop2ChargingAbo|                    |CS_Estop1ChargingAbo|                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  6| CS_SafeStateReason |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  7|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+

PT1000State
^^^^^^^^^^^

**ID**: 0x8 (8)

**Length**: 8 bytes

**Description**: This message shall be sent from safety controller to host processor for indicating the state of the connected temperature sensors

**Senders**: chargeSOM_SafetyController

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

   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
   |         7          |         6          |         5          |         4          |         3          |         2          |         1          |         0          |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  0|  PT1_Temperature   |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  1|  PT2_Temperature   |                    |                    |                    |                    |                    | PT1_SelftestFailed |PT1_ChargingStopped |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  2|  PT2_Temperature   |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  3|  PT3_Temperature   |                    |                    |                    |                    |                    | PT2_SelftestFailed |PT2_ChargingStopped |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  4|  PT3_Temperature   |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  5|  PT4_Temperature   |                    |                    |                    |                    |                    | PT3_SelftestFailed |PT3_ChargingStopped |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  6|  PT4_Temperature   |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  7|                    |                    |                    |                    |                    |                    | PT4_SelftestFailed |PT4_ChargingStopped |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+

FirmwareVersion
^^^^^^^^^^^^^^^

**ID**: 0xA (10)

**Length**: 8 bytes

**Description**: This message provides information about the type and version of the flashed firmware

**Senders**: chargeSOM_SafetyController

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

   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
   |         7          |         6          |         5          |         4          |         3          |         2          |         1          |         0          |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  0|    MajorVersion    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  1|    MinorVersion    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  2|    BuildVersion    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  3|    PlatformType    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  4|  ParameterVersion  |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  5|  ParameterVersion  |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  6|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  7|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+

GitHash
^^^^^^^

**ID**: 0xB (11)

**Length**: 8 bytes

**Description**: This message provides information about the GIT hash, written in the firmware

**Senders**: chargeSOM_SafetyController

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

   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
   |         7          |         6          |         5          |         4          |         3          |         2          |         1          |         0          |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  0|     HashSignal     |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  1|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  2|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  3|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  4|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  5|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  6|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  7|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+

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

   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
   |         7          |         6          |         5          |         4          |         3          |         2          |         1          |         0          |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  0|      PacketId      |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  1|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  2|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  3|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  4|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  5|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  6|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
  7|                    |                    |                    |                    |                    |                    |                    |                    |
   +--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+

