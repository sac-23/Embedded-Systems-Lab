#include <Arduino.h>
#define LED_PIN 2

// Task Handles
TaskHandle_t ledTaskHandle;
TaskHandle_t counterTaskHandle;
TaskHandle_t aliveTaskHandle;

void setup() {

  Serial.begin(115200);

  xTaskCreate(ledTask, "LED Task", 2048, NULL, 3, &ledTaskHandle);
  xTaskCreate(counterTask, "Counter Task", 2048, NULL, 2, &counterTaskHandle);
  xTaskCreate(aliveTask, "Alive Task", 2048, NULL, 1, &aliveTaskHandle);

}

void ledTask(void *pvParameters)
{
    pinMode(LED_PIN, OUTPUT);

    while (1)
    {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");

      vTaskDelay(pdMS_TO_TICKS(500));

      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");

      vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void counterTask(void *pvParameters)
{
    int count = 0;

    while (1)
    {
      count++;

      Serial.print("Counter = ");
      Serial.println(count);

      vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void aliveTask(void *pvParameters)
{
    while (1)
    {
      Serial.println("System Alive");

      vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void loop() { }
