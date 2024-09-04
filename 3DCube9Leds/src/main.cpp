#include <Arduino.h>

const uint8_t ledPins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const uint8_t numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
const uint8_t groundPins[] = {10, 11, 12};
const uint8_t numGrounds = sizeof(groundPins) / sizeof(groundPins[0]);

void SelfTest();

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }

  for (uint8_t i = 0; i < numLeds; i++)
    pinMode(ledPins[i], 0x1);

  for (uint8_t i = 0; i < numGrounds; i++)
    pinMode(groundPins[i], 0x1);

  SelfTest();
}

void loop()
{
    for (uint8_t i = 0; i < numLeds; i++)
      digitalWrite(ledPins[i], 0x1);
}

void SelfTest()
{
  Serial.println("Starting self test.");
  for (uint8_t i = 0; i < numGrounds; i++)
  {    
    digitalWrite(groundPins[i], 0x1);
    delay(100);

    for (uint8_t i = 0; i < numLeds; i++)
    {
      digitalWrite(ledPins[i], 0x1);
      delay(100);
    }

    for (uint8_t i = 0; i < numLeds; i++)
    {
      digitalWrite(ledPins[i], 0x0);
      delay(100);
    }

    digitalWrite(groundPins[i], 0x0);
    delay(100);
  }
}