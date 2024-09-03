#include <Arduino.h>

const uint8_t ledPins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const uint8_t numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
const uint8_t groundPins[] = {10, 11, 12};
const uint8_t numGrounds = sizeof(groundPins) / sizeof(groundPins[0]);

void setup()
{
  for (uint8_t i = 0; i < numLeds; i++)
    pinMode(i, OUTPUT);

  for (uint8_t i = 0; i < numGrounds; i++)
  {
    pinMode(i, OUTPUT);
    analogWrite(i, 0x1);
  }
}

void loop()
{
}