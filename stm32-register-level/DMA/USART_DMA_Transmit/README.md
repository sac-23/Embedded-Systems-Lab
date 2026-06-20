# DMA USART TX STM32 to ESP32

## Overview

This project demonstrates DMA-based UART transmission using the STM32F103C8T6 (Blue Pill). Data is transferred from memory to the USART1 data register using DMA1 Channel 4 and received by an ESP32.

## Hardware Used

* STM32F103C8T6 (Blue Pill)
* ESP32
* Jumper Wires

## Connections

| STM32           | ESP32        |
| --------------- | ------------ |
| PA9 (USART1_TX) | GPIO16 (RX2) |
| GND             | GND          |

## Features

* Register-Level Programming
* USART1 Communication
* DMA1 Channel 4
* Memory-to-Peripheral Transfer
* STM32 to ESP32 UART Communication

## Output

```text
Hello DMA
Hello DMA
Hello DMA
```

## Learning Outcomes

* DMA Configuration
* USART Communication
* Memory-to-Peripheral Data Transfer
* STM32 Register-Level Programming
