#include <Arduino.h>

const uint8_t groundPins[] = {14, 15, 16}; // Define an array of ground pins
const uint8_t numGrounds = sizeof(groundPins) / sizeof(groundPins[0]); // Calculate the number of ground pins
const uint8_t ledPins[] = {6, 2, 3, 4, 5, 8, 9, 10, 7}; // Define an array of LED pins
const uint8_t numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Calculate the number of LED pins
const uint8_t dt = 100;

void SelfTest(int delayTime); // Function prototype for the SelfTest function
void Rotate(int delayTime); // Function prototype for the Rotate function

void setup()
{
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  while (!Serial) // Wait for the serial port to connect
  {
  }

  Serial.println("Starting setup..."); // Print a message to the serial monitor

  for (uint8_t i = 0; i < numGrounds; i++) // Loop through all ground pins
  {
    pinMode(groundPins[i], 0x1); // Set each ground pin as an output
    digitalWrite(groundPins[i], 0x1); // Set each ground pin to HIGH
  }

  for (uint8_t i = 0; i < numLeds; i++) // Loop through all LED pins
    pinMode(ledPins[i], 0x1); // Set each LED pin as an output

  SelfTest(100); // Call the SelfTest function with a delay time of 100 milliseconds
}

void loop()
{
  // Rotate(5);// Placeholder for the Rotate function, currently commented out
}

void SelfTest(int delayTime)
{  
  Serial.println("Starting self test..."); // Print a message to the serial monitor
  for (uint8_t i = 0; i < numGrounds; i++) // Loop through all ground pins
  {
    digitalWrite(groundPins[i], 0x0); // Set each ground pin to LOW
    delay(delayTime); // Wait for the specified delay time

    for (uint8_t i = 0; i < numLeds; i++) // Loop through all LED pins
    {
      digitalWrite(ledPins[i], 0x1); // Turn on each LED
      delay(delayTime); // Wait for the specified delay time
      digitalWrite(ledPins[i], 0x0); // Turn off each LED
      delay(delayTime); // Wait for the specified delay time
    }

    digitalWrite(groundPins[i], 0x1); // Set each ground pin to HIGH
  }
  Serial.println("Finished self test..."); // Print a message to the serial monitor
  delay(delayTime); // Wait for the specified delay time
}

void Rotate(int delayTime)
{
  for (uint8_t l = 1; l <= numLeds; l++) // Loop through all LED pins
  {
    for (uint8_t i = 0; i < numGrounds; i++) // Loop through all ground pins
    {
      digitalWrite(groundPins[i], 0x0); // Set each ground pin to LOW
      digitalWrite(ledPins[0], 0x1); // Turn on the first LED
      delay(delayTime); // Wait for the specified delay time
      digitalWrite(ledPins[0], 0x0); // Turn off the first LED
      digitalWrite(groundPins[i], 0x1); // Set each ground pin to HIGH
    }

    for (uint8_t g = 0; g < numGrounds; g++) // Loop through all ground pins
    {
      digitalWrite(groundPins[g], 0x0); // Set each ground pin to LOW
      digitalWrite(ledPins[l], 0x1); // Turn on the current LED
      delay(delayTime); // Wait for the specified delay time
      digitalWrite(ledPins[l], 0x0); // Turn off the current LED
      digitalWrite(groundPins[g], 0x1); // Set each ground pin to HIGH
    }
  }
}