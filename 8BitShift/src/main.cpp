#include <Arduino.h>

// Pin connected to ST_CP of 74HC595
const uint8_t latchPin = 8;
// Pin connected to SH_CP of 74HC595
const uint8_t clockPin = 12;
// Pin connected to DS of 74HC595
const uint8_t dataPin = 11;
// The dalay to count up
const uint8_t countDelay = 50;

// set pins to output because they are addressed in the main loop
void setup()
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop()
{
  // count up routine
  for (int i = 0; i < 256; i++)
  {
    // ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, i);
    Serial.println(String(i));
    // return the latch pin high to signal chip that it
    // no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(countDelay);
  }
}