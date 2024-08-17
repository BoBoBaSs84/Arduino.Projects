#include <Arduino.h>

// Define the pins for the LEDs
const uint8_t ledPins[] = { 3, 5, 6, 9, 10, 11 };
// Calculate the number of LEDs
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
// Define the maximum PWM value
const int maxPWM = 255;
// Define the PWM value step
const int pwmStep = 5;
// Define the minimum PWM value
const int minPWM = 0;

void setup() {
  // Set the pins for the LEDs as output
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // Start the serial communication
  Serial.begin(9600);
}

// The loop function will turn on each LED one by one
void loop() {
  // Turn on each LED one by one
  for (uint8_t i = 0; i < numLeds; i++)
  {
    // Turn on the LED
    digitalWrite(ledPins[i], HIGH);
    // Wait for 100ms
    delay(50);
    // Turn off the LED
    digitalWrite(ledPins[i], LOW);
    // Wait for 100ms
    delay(50);
  }
  // Wait for 250ms
  delay(250);

  // Turn on each LED one by one
  for (uint8_t i = numLeds; i > 0; i--)
  {
    // Turn on the LED
    digitalWrite(ledPins[i], HIGH);
    // Wait for 100ms
    delay(50);
    // Turn off the LED
    digitalWrite(ledPins[i], LOW);
    // Wait for 100ms
    delay(50);
  }
  // Wait for 250ms
  delay(250);
}