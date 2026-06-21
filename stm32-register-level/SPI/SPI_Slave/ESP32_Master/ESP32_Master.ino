#include <SPI.h>

#define CS_PIN 5

void setup()
{
    Serial.begin(115200);

    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);

    SPI.begin();   // SCK=18, MISO=19, MOSI=23

    Serial.println("ESP32 SPI Master Ready");
}

void loop()
{
    digitalWrite(CS_PIN, LOW);

    SPI.transfer('A');

    digitalWrite(CS_PIN, HIGH);

    Serial.println("Sent: A");

    delay(100);
}