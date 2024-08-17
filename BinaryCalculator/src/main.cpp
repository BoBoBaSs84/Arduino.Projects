#include <Arduino.h>

// Define the pins for the LEDs
const uint8_t ledPins[] = { 3, 5, 6, 9, 10, 11, 12, 13 };
// Calculate the number of LEDs
const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);
// Define th bits for the LEDs
const uint8_t ints[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
// Calculate the number of bits
const int bitCount = sizeof(ints) / sizeof(ints[0]);

void setup() {
  // put your setup code here, to run once:
  for (size_t i = 0; i < ledCount; i++)
    pinMode(ledPins[i], OUTPUT);
  // Start the serial communication
  Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop() {
  // Loop through the numbers from 0 to 15
  for (int z = 0; z < 16; z++) {
    // Loop through the bits
    for (int b = 0; b < bitCount; b++) {
      // Calculate the power of 2
      int p = pow(b, 2);
      // Calculate the bit
      int i = z / p % 2;
      // Print the bit
      Serial.print(i);
      // Set the LED
      digitalWrite(ledPins[p], i == 1 ? HIGH : LOW);
    }
    Serial.println();
    delay(1000);
  }
}