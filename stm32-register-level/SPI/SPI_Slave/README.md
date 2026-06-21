# STM32 SPI Slave Communication with ESP32 Master

## Overview

This project demonstrates SPI communication between an STM32F103C8T6 (Blue Pill) configured as an SPI slave and an ESP32 configured as an SPI master. The ESP32 periodically transmits data over SPI, and the STM32 receives the data using register-level programming without relying on HAL libraries.

## Hardware Used

* STM32F103C8T6 (Blue Pill)
* ESP32 Dev Board
* Jumper Wires
* Breadboard (Optional)

## Connections

| ESP32 (Master) | STM32F103 (Slave) |
| -------------- | ----------------- |
| GPIO5 (CS)     | PA4 (NSS)         |
| GPIO18 (SCK)   | PA5 (SCK)         |
| GPIO23 (MOSI)  | PA7 (MOSI)        |
| GPIO19 (MISO)  | PA6 (MISO)        |
| GND            | GND               |

## Features

* Register-Level Programming
* SPI1 Peripheral Configuration
* SPI Slave Mode Operation
* Hardware NSS Management
* Full-Duplex SPI Support
* STM32 to ESP32 Communication
* Polling-Based Data Reception

## SPI Configuration

### STM32 (Slave)

* SPI1 Peripheral
* Mode 0 (CPOL = 0, CPHA = 0)
* 8-bit Data Frame
* Hardware Slave Select (NSS)
* MSB First

### ESP32 (Master)

* VSPI Interface
* SPI Mode 0
* MSB First
* Manual Chip Select Control

## Data Flow

ESP32 transmits the character:

```text
'A'
```

STM32 receives the byte through SPI1 and processes the received data.

## Example Output

### ESP32 Serial Monitor

```text
ESP32 SPI Master Ready
Sent: A
Sent: A
Sent: A
Sent: A
```

### STM32

```text
LED Toggled
LED Toggled
LED Toggled
```

depending on the application logic.

## Learning Outcomes

* SPI Protocol Fundamentals
* Master-Slave Communication
* STM32 SPI1 Register Configuration
* GPIO Alternate Function Configuration
* Hardware NSS Management
* Embedded C Register-Level Programming
* Interfacing STM32 with ESP32

## Author

Sachin Narendra S
