# STM32 SPI Slave RX Interrupt with ESP32 Master

## Overview

This project demonstrates interrupt-driven SPI communication between an STM32F103C8T6 (Blue Pill) configured as an SPI slave and an ESP32 configured as an SPI master.

The ESP32 periodically transmits data over SPI. The STM32 receives the incoming data using the SPI1 RXNE (Receive Buffer Not Empty) interrupt without using polling or HAL libraries.

The project is implemented entirely using register-level programming.

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
* RXNE Interrupt Handling
* NVIC Configuration
* Interrupt Service Routine (ISR)
* STM32 and ESP32 SPI Communication

## SPI Configuration

### STM32 (Slave)

* SPI1 Peripheral
* Mode 0 (CPOL = 0, CPHA = 0)
* 8-bit Data Frame
* Hardware Slave Select (NSS)
* MSB First
* RXNE Interrupt Enabled

### ESP32 (Master)

* VSPI Interface
* SPI Mode 0
* MSB First
* Manual Chip Select Control

## Interrupt Flow

```text
ESP32 sends data
        ↓
SPI1 receives byte
        ↓
RXNE flag set
        ↓
RXNE Interrupt Generated
        ↓
NVIC accepts IRQ35
        ↓
SPI1_IRQHandler()
        ↓
SPI_DR read
        ↓
LED toggled
```

## Data Flow

ESP32 periodically transmits:

```text
'A'
```

STM32 receives the byte through SPI1.

When the received data matches:

```text
'A'
```

the onboard LED connected to PC13 is toggled inside the interrupt service routine.

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
RX Interrupt Triggered
Received: A
LED Toggled
```

depending on the application logic.

## Learning Outcomes

* SPI Protocol Fundamentals
* Interrupt-Driven Communication
* NVIC Configuration
* Interrupt Service Routines (ISR)
* STM32 SPI1 Register Configuration
* Hardware NSS Management
* ESP32 Master and STM32 Slave Communication
* Embedded C Register-Level Programming

## Author

Sachin Narendra S
