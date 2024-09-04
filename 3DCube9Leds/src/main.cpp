#include <Arduino.h>

const uint8_t groundPins[] = {14, 15, 16};
const uint8_t numGrounds = sizeof(groundPins) / sizeof(groundPins[0]);
const uint8_t ledPins[] = {2, 3, 4, 7, 6, 5, 10, 9, 8};
const uint8_t numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

void SelfTest(int delayTime);
void Rotate();

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }

  Serial.println("Starting setup...");

  for (uint8_t i = 0; i < numGrounds; i++)
  {
    pinMode(groundPins[i], 0x1);
    digitalWrite(groundPins[i], 0x1);
  }

  for (uint8_t i = 0; i < numLeds; i++)
    pinMode(ledPins[i], 0x1);

  SelfTest(100);
}

void loop()
{
  SelfTest(5);
}

void SelfTest(int delayTime)
{

  Serial.println("Starting self test...");
  for (uint8_t i = 0; i < numGrounds; i++)
  {
    digitalWrite(groundPins[i], 0x0);
    delay(delayTime);

    for (uint8_t i = 0; i < numLeds; i++)
    {
      digitalWrite(ledPins[i], 0x1);
      delay(delayTime);
      digitalWrite(ledPins[i], 0x0);
      delay(delayTime);
    }

    digitalWrite(groundPins[i], 0x1);
  }
}

void Rotate()
{
}