#include <Arduino.h>

#define LEDPin 2

// Task Handle
TaskHandle_t LedTaskHandle;
TaskHandle_t IRTaskHandle;

void setup() {

  Serial.begin(115200);

  pinMode(LEDPin, OUTPUT);

  // Task Creation
  xTaskCreate(LEDTask, "LED Task", 2048, NULL, 1, &LedTaskHandle);
  xTaskCreate(IRTask, "IR Task", 2048, NULL, 1, &IRTaskHandle);

}

void LEDTask(void *pvParameters)
{
  while (1) {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    Serial.println("LED ON...");
    digitalWrite(LEDPin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));
    digitalWrite(LEDPin, LOW);
    Serial.println("LED OFF...");
  }
}

void IRTask (void *pvParameters)
{
  int IRValue;
  while (1){
    IRValue = random(0, 1000);
    Serial.println(IRValue);
    if (IRValue > 700){
      Serial.println("Threshold Crossed...");
      xTaskNotifyGive(LedTaskHandle);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
