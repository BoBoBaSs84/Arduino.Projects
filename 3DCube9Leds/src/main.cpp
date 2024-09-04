#include <Arduino.h>

const uint8_t groundPins[] = {14, 15, 16};
const uint8_t numGrounds = sizeof(groundPins) / sizeof(groundPins[0]);
const uint8_t ledPins[] = {6, 2, 3, 4, 5, 8, 9, 10, 7};
const uint8_t numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

void SelfTest(int delayTime);
void Rotate(int delayTime);

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
  Rotate(5);
}

void SelfTest(int delayTime)
{
  Serial.println("Starting self test...");
  for (uint8_t i = 0; i < numGrounds; i++)
  {
    digitalWrite(groundPins[i], 0x0);

    for (uint8_t i = 0; i < numLeds; i++)
    {
      digitalWrite(ledPins[i], 0x1);
      delay(delayTime);
      digitalWrite(ledPins[i], 0x0);
    }

    digitalWrite(groundPins[i], 0x1);
  }
  Serial.println("Finished self test...");
  delay(delayTime);
}

void Rotate(int delayTime)
{
  for (uint8_t l = 1; l <= numLeds; l++)
  {
    for (uint8_t i = 0; i < numGrounds; i++)
    {
      digitalWrite(groundPins[i], 0x0);
      digitalWrite(ledPins[0], 0x1);
      delay(delayTime);
      digitalWrite(ledPins[0], 0x0);
      digitalWrite(groundPins[i], 0x1);
    }

    for (uint8_t g = 0; g < numGrounds; g++)
    {
      digitalWrite(groundPins[g], 0x0);
      digitalWrite(ledPins[l], 0x1);
      delay(delayTime);
      digitalWrite(ledPins[l], 0x0);
      digitalWrite(groundPins[g], 0x1);
    }
  }
}