#include <Arduino.h>

const int threshold = 375;       // The threshold value
const uint8_t silentPin = 0x2;   // Define the pin for the silent LED
const uint8_t loudPin = 0x4;     // Define the pin for the loud LED

// the setup function runs once when you press reset or power the board
void setup() {  
  pinMode(silentPin, 0x1);    // Initialize the silent pin as a digital output
  pinMode(loudPin, 0x1);      // Initialize the loud pin as a digital output
  Serial.begin(9600);         // Initialize serial communication at 9600 bits per second
  while (!Serial) { }         // Wait for the serial monitor to open
}

// the loop function runs over and over again forever
void loop() {
  int analogValue = analogRead(A0);   // Read the analog input from pin A0

  if (analogValue < threshold) {
    digitalWrite(loudPin, HIGH);       // Turn on the loud pin
    digitalWrite(silentPin, LOW);      // Turn off the silent pin
  } else {
    digitalWrite(loudPin, LOW);        // Turn off the loud pin
    digitalWrite(silentPin, HIGH);     // Turn on the silent pin
  }

  Serial.println("Analog value: " + String(analogValue)); // Print the analog value to the serial monitor
  delay(100); // Add a small delay to avoid flooding the serial monitor
}