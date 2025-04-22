ChargeState1
============

**ID**: 0x7 (7)

**Length**: 8 bytes

**Description**: This message shall be sent from safety controller to host processor for indicating the state of the charging session as well as the state of connected peripherals.

**Senders**: Safety Controller

.. list-table:: Signals in ChargeState1
   :widths: 30 6 6 10 7 7 7 6
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
   * - CS_CurrentDutyCycle
     - 1
     - 10
     - Big Endian
     - No
     - 0.1
     - 0
     - %
   * - CS_PWM_Active
     - 7
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_CurrentCpState
     - 18
     - 3
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_CpShortCircuit
     - 19
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_DiodeFault
     - 20
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_CurrentPpState
     - 26
     - 3
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_Contactor1State
     - 32
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_Contactor2State
     - 33
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_Contactor1Error
     - 34
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_Contactor2Error
     - 35
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_Estop1ChargingAbort
     - 40
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_Estop2ChargingAbort
     - 41
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_Estop3ChargingAbort
     - 42
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_ImdRcmChargingAbort
     - 43
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CS_ImdRcmTestFailure
     - 44
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 

**Value Descriptions**

- **CS_CurrentCpState**

  - 0x8 = Unknown
  - 0x7 = Invalid
  - 0x6 = F
  - 0x5 = E
  - 0x4 = D
  - 0x3 = C
  - 0x2 = B
  - 0x1 = A

- **CS_CurrentPpState**

  - 0x7 = Error
  - 0x6 = Type1_ConnectedButtonPressed
  - 0x5 = Type1_Connected
  - 0x4 = 63/70A
  - 0x3 = 32A
  - 0x2 = 20A
  - 0x1 = 13A
  - 0x0 = NoCableDetected

ChargeControl1
==============

**ID**: 0x6 (6)

**Length**: 8 bytes

**Description**: This message shall be sent from the host processor to the safety controller to control the peripherals connected to the safety controller.

**Senders**: Default_HostController

.. list-table:: Signals in ChargeControl1
   :widths: 30 6 6 10 7 7 7 6
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
   * - CC_TargetDutyCycle
     - 1
     - 10
     - Big Endian
     - No
     - 0.1
     - 0
     - %
   * - CC_PWM_Active
     - 7
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CC_Contactor1State
     - 16
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - CC_Contactor2State
     - 17
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 

PT1000State
===========

**ID**: 0x8 (8)

**Length**: 8 bytes

**Description**: This message shall be sent from safety controller to host processor for indicating the state of the connected temperature sensors

**Senders**: Safety Controller

.. list-table:: Signals in PT1000State
   :widths: 30 6 6 10 7 7 7 6
   :header-rows: 1

   * - Name
     - Start
     - Length
     - ByteOrder
     - Signed
     - Factor
     - Offset
     - Unit
   * - PT1_Temperature
     - 7
     - 14
     - Big Endian
     - No
     - 10
     - 600
     - °C
   * - PT1_ChargingStopped
     - 8
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - PT1_SelftestFailed
     - 9
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - PT2_Temperature
     - 23
     - 14
     - Big Endian
     - No
     - 10
     - 600
     - °C
   * - PT2_ChargingStopped
     - 24
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - PT2_SelftestFailed
     - 25
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - PT3_Temperature
     - 39
     - 14
     - Big Endian
     - No
     - 10
     - 600
     - °C
   * - PT3_ChargingStopped
     - 40
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - PT3_SelftestFailed
     - 41
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - PT4_Temperature
     - 55
     - 14
     - Big Endian
     - No
     - 10
     - 600
     - °C
   * - PT4_ChargingStopped
     - 56
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 
   * - PT4_SelftestFailed
     - 57
     - 1
     - Big Endian
     - No
     - 1
     - 0
     - 

**Value Descriptions**

- **PT1_Temperature**

  - 0x3FFF = TempSensorNotUsed

- **PT2_Temperature**

  - 0x3FFF = TempSensorNotUsed

- **PT3_Temperature**

  - 0x3FFF = TempSensorNotUsed

- **PT4_Temperature**

  - 0x3FFF = TempSensorNotUsed

