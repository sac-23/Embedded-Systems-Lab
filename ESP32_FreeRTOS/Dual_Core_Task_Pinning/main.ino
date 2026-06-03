#include <Arduino.h>

#define LEDPin 2

// Task Handle
TaskHandle_t LEDTaskHandle;
TaskHandle_t DisplayTaskHandle;
TaskHandle_t ADXLTaskHandle;
TaskHandle_t IRTaskHandle;

void setup() {

  Serial.begin(115200);

  pinMode(LEDPin, OUTPUT);

  // TASK Creation
  xTaskCreatePinnedToCore(LEDTask, "LED TASk", 2048, NULL, 1, &LEDTaskHandle, 0);
  xTaskCreatePinnedToCore(DisplayTask, "Display Task", 2048, NULL, 1, &DisplayTaskHandle, 0);
  xTaskCreatePinnedToCore(ADXLTask, "ADXL Task", 2048, NULL, 1, &ADXLTaskHandle, 1);
  xTaskCreatePinnedToCore(IRTask, "IR Task", 2048, NULL, 1, &IRTaskHandle, 1);

}

void LEDTask(void *pvParameters)
{
  pinMode(2,OUTPUT);

  while(1)
  {
    digitalWrite(LEDPin,!digitalRead(LEDPin));

    Serial.print("LED Task Core: ");
    Serial.println(xPortGetCoreID());

    vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void DisplayTask(void *pvParameters)
{
  while (1)
  {
    Serial.print("Display Task Core: ");
    Serial.println(xPortGetCoreID());

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void ADXLTask(void *pvParameters) 
{
  while (1)
  {
    Serial.print("ADXL Task Core: ");
    Serial.println(xPortGetCoreID());

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void IRTask(void *pvParameters) 
{
  while (1)
  {
    Serial.print("IR Task Core: ");
    Serial.println(xPortGetCoreID());

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
