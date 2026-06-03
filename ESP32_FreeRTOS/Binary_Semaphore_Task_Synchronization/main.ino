#include <Arduino.h>

#define BuzzerPin 5

// Semaphore Handle
SemaphoreHandle_t VibrationSemaphore;

// Task Handle
TaskHandle_t BuzzerTaskHandle;
TaskHandle_t ADXLTaskHandle;

void setup() {

  Serial.begin(115200);

  pinMode(BuzzerPin, OUTPUT);

  // Creation of Semaphore 
  VibrationSemaphore = xSemaphoreCreateBinary();

  // Creation of Task
  xTaskCreate(BuzzerTask, "Buzzzer Task", 2048, NULL, 1, &BuzzerTaskHandle);
  xTaskCreate(ADXLTask, "ADXL Task", 2048, NULL, 1, &ADXLTaskHandle);

}

void BuzzerTask (void *pvParameters) {

  while (1) {
    xSemaphoreTake(VibrationSemaphore, portMAX_DELAY);

    Serial.println("Buzzer ON...");
    digitalWrite(BuzzerPin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));
    digitalWrite(BuzzerPin, LOW);
    Serial.println("Buzzer OFF...");

  }
}

void ADXLTask (void *pvParameters) {

  int vibration;

  while (1) {

    vibration = random(0, 100);

    Serial.print("Vibration: ");
    Serial.println(vibration);

    if (vibration > 70){
      Serial.println("Threshold Crossed");
      xSemaphoreGive(VibrationSemaphore);
    }
    
    vTaskDelay(pdMS_TO_TICKS(500));

  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
