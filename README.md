# Embedded-Systems-Lab

A collection of Embedded Systems projects developed using **STM32F103**, **ESP32**, **Embedded C**, **Register-Level Programming**, and **FreeRTOS**.

## Technologies Used

* Embedded C
* STM32F103 (ARM Cortex-M3)
* ESP32
* Register-Level Programming
* FreeRTOS
* SPI Communication
* USART Communication
* ADC Interfacing

---

## Repository Structure

```text
Embedded-Systems-Lab/
│
├── Register_Level_Programming/
│   ├── GPIO_Blink/
│   ├── USART_TX/
│   ├── USART_RX/
│   ├── ADC_Single_Channel/
│   ├── Sensor_Node_USART/
│   └── ADXL345_SPI_Interface/
│
└── ESP32_FreeRTOS/
    ├── Task_Creation_Priority/
    ├── Queue_InterTask_Communication/
    ├── Binary_Semaphore_Task_Synchronization/
    ├── Mutex_Shared_Resource_Protection/
    ├── Task_Notification_Task_Synchronization/
    └── Dual_Core_Task_Pinning/
```

---

## Register-Level Programming Projects

### GPIO_Blink

* GPIO configuration using direct register access
* LED blinking using GPIO output control

### USART_TX

* USART2 transmitter configuration
* Serial data transmission using polling

### USART_RX

* USART2 receiver configuration
* Serial data reception using polling

### ADC_Single_Channel

* ADC1 configuration
* Single-channel analog data acquisition

### Sensor_Node_USART

* ADC data acquisition
* USART transmission and reception
* Acknowledgment-based communication

### ADXL345_SPI_Interface

* SPI1 master configuration
* ADXL345 accelerometer interfacing
* Device ID verification
* X, Y, and Z axis data acquisition

---

## FreeRTOS Projects

### Task_Creation_Priority

* Task creation using `xTaskCreate()`
* Task priority management
* Task scheduling using `vTaskDelay()`

### Queue_InterTask_Communication

* Queue creation
* Data transfer between multiple tasks
* Sensor data processing workflow

### Binary_Semaphore_Task_Synchronization

* Binary semaphore implementation
* Event-driven task synchronization

### Mutex_Shared_Resource_Protection

* Mutex creation
* Protection of shared resources
* Safe serial communication between tasks

### Task_Notification_Task_Synchronization

* Direct task-to-task notification
* Lightweight synchronization mechanism

### Dual_Core_Task_Pinning

* ESP32 dual-core programming
* Task assignment using `xTaskCreatePinnedToCore()`
* Core identification using `xPortGetCoreID()`

---

## Skills Demonstrated

* Embedded C Programming
* Register-Level Driver Development
* STM32 Peripheral Configuration
* GPIO Programming
* USART Communication
* SPI Communication
* ADC Interfacing
* Sensor Interfacing
* FreeRTOS Task Management
* Inter-Task Communication
* Synchronization Mechanisms
* ESP32 Dual-Core Programming

---

## Author

**Sachin Narendra S**

Bachelor of Engineering (Electronics and Communication Engineering)
Thanthai Periyar Government Institute of Technology
Anna University

```
```
