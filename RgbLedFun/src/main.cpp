#include <Arduino.h>

// Define the pins for the RGB LED
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int delayTime = 250;

// define custom function to set the color of the RGB LED
void setColor(int red, int green, int blue);

void setup() {
  // Set the RGB LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Example: Set the RGB LED to purple
  setColor(255, 0, 0); // Red and Blue at full brightness, Green off
  delay(delayTime); // Wait for 1 second

  // Example: Set the RGB LED to cyan
  setColor(0, 255, 225); // Green and Blue at full brightness, Red off
  delay(delayTime); // Wait for 1 second

  // Example: Set the RGB LED to yellow
  setColor(0, 0, 255); // Red and Green at full brightness, Blue off
  delay(delayTime); // Wait for 1 second

  // Example: Turn off the RGB LED
  setColor(0, 0, 0); // All colors off
  delay(delayTime); // Wait for 1 second
}

// Function to set the color of the RGB LED
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}