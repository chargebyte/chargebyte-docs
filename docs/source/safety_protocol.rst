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
     - Big Endian
     - No
     - 1
     - 0
     - -
     - This flag indicates if the PWM should be activated. At a value of 0, the CP level is also 0V. At a value of 1, the CP level is dependant of the duty cycle
   * - CC_Contactor1State
     - 16
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Request to close the contactor state. A value of 0 means open contactor, a value of 1 means closed contactor. The contactors are only closed if the system has no errors and is in state C.
   * - CC_Contactor2State
     - 17
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
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
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Feedback if PWM is active. 0 means not active, 1 means active
   * - CS_CurrentCpState
     - 18
     - 3
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Current state of the control pilot. See value mappings below
   * - CS_CpShortCircuit
     - 19
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Is set when the safety controller detects a short-circuit condition between CP and PE line.
   * - CS_DiodeFault
     - 20
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Is set when the safety controller detects that the diode on EV side is missing.
   * - CS_CurrentPpState
     - 26
     - 3
     - Big Endian
     - No
     - 1
     - 0
     - -
     - State of the proximity pin. For fixed cables at CCS2, this value is 0x0: No Cable detected
   * - CS_Contactor1State
     - 32
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Is set when the contactor is closed
   * - CS_Contactor2State
     - 33
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Is set when the contactor is closed
   * - CS_Contactor1Error
     - 34
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Is set when an error in the contactor is detected
   * - CS_Contactor2Error
     - 35
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Is set when an error in the contactor is detected
   * - CS_Estop1ChargingAbort
     - 40
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - *No description available*
   * - CS_Estop2ChargingAbort
     - 41
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - *No description available*
   * - CS_Estop3ChargingAbort
     - 42
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - *No description available*
   * - CS_ImdRcmChargingAbort
     - 43
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - *No description available*
   * - CS_ImdRcmTestFailure
     - 44
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
     - *No description available*

**Value Descriptions**

- **CS_CurrentCpState**

  - 0x7 = Invalid
  - 0x6 = F
  - 0x5 = E
  - 0x4 = D
  - 0x3 = C
  - 0x2 = B
  - 0x1 = A
  - 0x0 = Unknown

- **CS_CurrentPpState**

  - 0x7 = Error
  - 0x6 = Type1_ConnectedButtonPressed
  - 0x5 = Type1_Connected
  - 0x4 = 63/70A
  - 0x3 = 32A
  - 0x2 = 20A
  - 0x1 = 13A
  - 0x0 = NoCableDetected

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
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Indicates whether this PT1000 channel prevents charging, multiple channel can signal the condition in parallel.
   * - PT1_SelftestFailed
     - 9
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
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
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Indicates whether this PT1000 channel prevents charging, multiple channel can signal the condition in parallel.
   * - PT2_SelftestFailed
     - 25
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
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
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Indicates whether this PT1000 channel prevents charging, multiple channel can signal the condition in parallel.
   * - PT3_SelftestFailed
     - 41
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
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
     - Big Endian
     - No
     - 1
     - 0
     - -
     - Indicates whether this PT1000 channel prevents charging, multiple channel can signal the condition in parallel.
   * - PT4_SelftestFailed
     - 57
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - -
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

