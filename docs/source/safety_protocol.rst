ChargeControl1
==============

**ID**: 0x6 (6)

**Length**: 8 bytes

**Description**: This message shall be sent from the host processor to the safety controller to control the peripherals connected to the safety controller.

**Senders**: Default_HostController

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

ChargeState1
============

**ID**: 0x7 (7)

**Length**: 8 bytes

**Description**: This message shall be sent from safety controller to host processor for indicating the state of the charging session as well as the state of connected peripherals.

**Senders**: Safety Controller

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
     - 32
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Is set when the contactor is closed
   * - CS_Contactor2State
     - 33
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Is set when the contactor is closed
   * - CS_Contactor1Error
     - 34
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Is set when an error in the contactor is detected
   * - CS_Contactor2Error
     - 35
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - Is set when an error in the contactor is detected
   * - CS_Estop1ChargingAbort
     - 40
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_Estop2ChargingAbort
     - 41
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_Estop3ChargingAbort
     - 42
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_ImdRcmChargingAbort
     - 43
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*
   * - CS_ImdRcmTestFailure
     - 44
     - 1
     - 
     - No
     - 1
     - 0
     - 
     - *No description available*

**Value Descriptions**

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

PT1000State
===========

**ID**: 0x8 (8)

**Length**: 8 bytes

**Description**: This message shall be sent from safety controller to host processor for indicating the state of the connected temperature sensors

**Senders**: Safety Controller

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

FirmwareVersion
===============

**ID**: 0xA (10)

**Length**: 8 bytes

**Description**: This message provides information about the type and version of the flashed firmware

**Senders**: Safety Controller

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

**Value Descriptions**

- **PlatformType**

  - 0x81 = chargeSOM
  - 0x82 = CCY

- **ApplicationType**

  - 0x3 = Firmware
  - 0x4 = End Of Line
  - 0x5 = Qualification

GitHash
=======

**ID**: 0xB (11)

**Length**: 8 bytes

**Description**: This message provides information about the GIT hash, written in the firmware

**Senders**: Safety Controller

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

InquiryPacket
=============

**ID**: 0xFF (255)

**Length**: 8 bytes

**Description**: This packet is used to request a special message from the safety controller

**Senders**: Default_HostController, CCY_HostController

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

