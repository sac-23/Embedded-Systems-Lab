#include <Arduino.h>

// Queue Handle
QueueHandle_t MqQueue;
QueueHandle_t AnalysisQueue;

// Task Handle 
TaskHandle_t MqTaskHandle;
TaskHandle_t DisplayHandle;
TaskHandle_t AnalysisHandle;

void setup() {

  Serial.begin(115200);

  // Queue Creation
  MqQueue = xQueueCreate(5, sizeof(int));
  AnalysisQueue = xQueueCreate(5, sizeof(int));

  // Task Creation
  xTaskCreate(MqTask, "MQ Task", 2048, NULL, 1, &MqTaskHandle);
  xTaskCreate(DisplayTask, "Display Task", 2048, NULL, 1, &DisplayHandle);
  xTaskCreate(AnalysisTask, "Analysis Task", 2048, NULL, 1, &AnalysisHandle);


}

void MqTask(void *pvParameters)
{
  int MqValue;

  while(1)
  {
    MqValue = random(200, 1000);
    xQueueSend(MqQueue, &MqValue, portMAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void DisplayTask(void *pvParameters)
{ 
  int ReceivedValue;
  while(1)
  {
    xQueueReceive(MqQueue, &ReceivedValue, portMAX_DELAY);
    Serial.print("MQ Value:");
    Serial.println(ReceivedValue);
    xQueueSend(AnalysisQueue, &ReceivedValue, portMAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void AnalysisTask(void *pvParameters)
{
  int AnalysisValue;
  
  while (1) {
    xQueueReceive(AnalysisQueue, &AnalysisValue, portMAX_DELAY);

    if (AnalysisValue > 500){
      Serial.println("Danger.....");
    }
    else {
      Serial.println("Normal.....");
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
