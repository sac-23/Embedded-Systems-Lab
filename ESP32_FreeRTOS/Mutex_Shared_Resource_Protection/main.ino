#include <Arduino.h>

// Mutex Handle
SemaphoreHandle_t SerialMutex;

// Task Handle
TaskHandle_t Task1Handle;
TaskHandle_t Task2Handle;
TaskHandle_t Task3Handle;

void setup() {
  
  Serial.begin(115200);

  // Mutex Creation
  SerialMutex = xSemaphoreCreateMutex();

  // Task Creation
  xTaskCreate(Task1, "Task 1 Task", 2048, NULL, 1, &Task1Handle);
  xTaskCreate(Task2, "Task 2 Task", 2048, NULL, 1, &Task2Handle);
  xTaskCreate(Task3, "Task 3 Task", 2048, NULL, 1, &Task3Handle);

}

void Task1 (void *pvParameters){

  while (1) {
    xSemaphoreTake(SerialMutex, portMAX_DELAY);

    Serial.println("The TASK 1 is Running");

    xSemaphoreGive(SerialMutex);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void Task2 (void *pvParameters){

  while (1) {
    xSemaphoreTake(SerialMutex, portMAX_DELAY);

    Serial.println("The TASK 2 is Running");

    xSemaphoreGive(SerialMutex);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void Task3 (void *pvParameters){

  while (1) {
    xSemaphoreTake(SerialMutex, portMAX_DELAY);

    Serial.println("The TASK 3 is Running");

    xSemaphoreGive(SerialMutex);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
