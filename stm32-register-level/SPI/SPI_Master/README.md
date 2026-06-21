# ADXL345 Accelerometer Interface with STM32F103 (SPI Register-Level Programming)

## Overview

This project demonstrates interfacing the ADXL345 3-axis accelerometer with the STM32F103C8T6 (Blue Pill) using the SPI protocol. The STM32 operates as the SPI master and communicates directly with the sensor using register-level programming without relying on HAL libraries.

The application initializes the ADXL345, configures measurement mode, sets the accelerometer range to ±4g, and continuously reads X, Y, and Z axis acceleration data.

## Hardware Used

* STM32F103C8T6 (Blue Pill)
* ADXL345 Accelerometer Module
* Jumper Wires
* Breadboard (Optional)

## Connections

| STM32F103 (SPI1 Remapped) | ADXL345  |
| ------------------------- | -------- |
| PA15 (CS)                 | CS       |
| PB3 (SCK)                 | SCL/SCLK |
| PB5 (MOSI)                | SDA/SDI  |
| PB4 (MISO)                | SDO      |
| 3.3V                      | VCC      |
| GND                       | GND      |

## Features

* Register-Level Programming
* SPI1 Peripheral Configuration
* SPI1 Remapping
* ADXL345 Initialization
* Single Register Read/Write
* Multi-Byte SPI Read
* X, Y, Z Axis Data Acquisition
* Embedded C Development

## SPI Configuration

### STM32

* SPI1 Master Mode
* SPI Mode 3 (CPOL = 1, CPHA = 1)
* Baud Rate = PCLK / 8
* Software Slave Management (SSM)
* Internal Slave Select (SSI)
* 8-bit Data Frame
* MSB First

### ADXL345

* Measurement Mode Enabled
* Range Configured to ±4g
* Multi-Byte Data Read Enabled

## ADXL345 Registers Used

| Register    | Address | Purpose                        |
| ----------- | ------- | ------------------------------ |
| DEVID       | 0x00    | Device Identification          |
| POWER_CTL   | 0x2D    | Enable Measurement Mode        |
| DATA_FORMAT | 0x31    | Configure Measurement Range    |
| DATAX0      | 0x32    | Start Address for X, Y, Z Data |

## Data Acquisition Flow

1. Initialize GPIO and SPI peripherals.
2. Read ADXL345 Device ID.
3. Enable Measurement Mode.
4. Configure ±4g Measurement Range.
5. Perform Multi-Byte Read starting from DATAX0.
6. Combine low and high bytes to obtain:

   * X-axis Acceleration
   * Y-axis Acceleration
   * Z-axis Acceleration

## Example Variables

```c
int16_t x;
int16_t y;
int16_t z;
```

These variables store the raw acceleration data received from the ADXL345.

## Learning Outcomes

* SPI Communication Fundamentals
* STM32 SPI Register Configuration
* Peripheral Remapping using AFIO
* Sensor Interfacing
* Multi-Byte SPI Transactions
* Embedded C Programming
* Register-Level Driver Development
* Accelerometer Data Acquisition

## Author

Sachin Narendra S
