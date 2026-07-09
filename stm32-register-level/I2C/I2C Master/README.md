# STM32 I²C Master Driver with ADXL345 Accelerometer (Register-Level Programming)

## Overview

This project demonstrates register-level I²C communication between an **STM32F103C8T6 (Blue Pill)** configured as an **I²C Master** and an **ADXL345 3-axis digital accelerometer** configured as an **I²C Slave**.

The STM32 initializes the I²C peripheral, communicates with the ADXL345 using the I²C protocol, verifies the sensor by reading its **Device ID (DEVID)** register, configures the accelerometer for measurement mode, and continuously reads the **X, Y, and Z acceleration values** using burst (multi-byte) read operations.

The project is implemented entirely using **register-level programming** without using HAL or external libraries.

---

# Hardware Used

* STM32F103C8T6 (Blue Pill)
* ADXL345 3-Axis Digital Accelerometer
* Breadboard
* Jumper Wires
* USB to ST-Link Programmer

---

# Connections

| STM32F103 (Master) | ADXL345 (Slave)          |
| ------------------ | ------------------------ |
| PB6 (I2C1_SCL)     | SCL                      |
| PB7 (I2C1_SDA)     | SDA                      |
| 3.3V               | VCC                      |
| GND                | GND                      |
| 3.3V               | CS (Select I²C Mode)     |
| GND                | SDO (I²C Address = 0x53) |

---

# Features

* Register-Level Programming
* I²C1 Peripheral Configuration
* I²C Master Mode Operation
* Standard Mode (100 kHz)
* START and Repeated START Generation
* STOP Condition Generation
* 7-bit Slave Addressing
* Single Register Read
* Single Register Write
* Multi-byte (Burst) Register Read
* ADXL345 Device Driver
* ADXL345 Initialization
* Device ID Verification
* Continuous X, Y, Z Axis Data Acquisition
* Modular Driver Architecture

---

# I²C Configuration

## STM32 (Master)

* I²C1 Peripheral
* Master Mode
* Standard Mode (100 kHz)
* 7-bit Addressing
* ACK/NACK Handling
* Register-Level Configuration
* PB6 → SCL
* PB7 → SDA

## ADXL345 (Slave)

* 7-bit I²C Address: **0x53**
* Full Resolution Mode
* ±2g Measurement Range
* Right-Justified Data Format
* Continuous Measurement Mode

---

# Communication Flow

```
STM32 Generates START
        ↓
Send ADXL345 Address + Write
        ↓
Send Register Address
        ↓
Repeated START
        ↓
Send ADXL345 Address + Read
        ↓
Read Data Byte(s)
        ↓
ACK / NACK
        ↓
STOP Condition
```

---

# Driver Architecture

```
Application Layer
        │
        ▼
ADXL345 Driver
        │
        ▼
I²C Driver
        │
        ▼
STM32 I²C1 Peripheral
        │
        ▼
ADXL345 Sensor
```

---

# Data Flow

### Device Detection

STM32 reads:

```
DEVID (0x00)
```

Expected response:

```
0xE5
```

If the Device ID matches, the sensor is initialized.

---

### Sensor Initialization

The driver configures:

```
DATA_FORMAT Register
```

* Full Resolution Enabled
* ±2g Range
* Right Justified Data

Then enables:

```
POWER_CTL Register
```

* Measurement Mode

---

### Burst Read Operation

STM32 performs a multi-byte read beginning from:

```
DATAX0
```

Registers read:

```
DATAX0
DATAX1
DATAY0
DATAY1
DATAZ0
DATAZ1
```

The driver combines each LSB and MSB into signed 16-bit values.

Example:

```
X = (DATAX1 << 8) | DATAX0
Y = (DATAY1 << 8) | DATAY0
Z = (DATAZ1 << 8) | DATAZ0
```

---

# Program Flow

```
Initialize GPIO
        ↓
Initialize I²C1
        ↓
Read ADXL345 Device ID
        ↓
Device Found?
      │
 ┌────┴────┐
 │         │
Yes        No
 │         │
 ▼         ▼
Initialize  LED Error Indication
Sensor
 │
 ▼
Read XYZ Data Continuously
 │
 ▼
Update Acceleration Structure
```

---

# Example Output (Live Expressions)

```
accel.x = 18
accel.y = -12
accel.z = 258
```

Tilting the sensor changes the values in real time.

---

# Project Structure

```
Application
│
├── main.c
│
Drivers
│
├── gpio.c
├── gpio.h
│
├── i2c.c
├── i2c.h
│
├── adxl345.c
├── adxl345.h
│
CMSIS
│
└── stm32f103x6.h
```

---

# Learning Outcomes

* I²C Protocol Fundamentals
* Master-Slave Communication
* START, STOP and Repeated START Conditions
* ACK and NACK Handling
* 7-bit Slave Addressing
* Register-Level Peripheral Programming
* STM32 I²C1 Register Configuration
* Device Driver Development
* ADXL345 Register Map
* Burst (Multi-byte) Data Transfer
* Sensor Initialization and Configuration
* Embedded C Modular Driver Design
* Live Debugging Using STM32CubeIDE

---

# Future Improvements

* USART Data Transmission
* Interrupt-Driven I²C Communication
* DMA-Based I²C Data Transfer
* Real-Time Acceleration Display
* Pitch and Roll Angle Calculation
* Free-Fall and Activity Detection
* FIFO Buffer Support
* RTOS Integration (FreeRTOS)

---

# Author

**Sachin Narendra S**

Embedded Systems | Firmware Development | Register-Level Programming | STM32 | ESP32 | Embedded C
