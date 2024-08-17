#include <Arduino.h>

// LEDs connected to digital pins 3, 5 and 6
const uint8_t ledPins[] = {3, 5, 6};
// Number of LEDs
const uint8_t ledCount = sizeof(ledPins) / sizeof(ledPins[0]);
// Buttons to brighten LEDs
const uint8_t brighterButtons[] = {8, 10, 12};
// Buttons to darken LEDs
const uint8_t darkerButtons[] = {9, 11, 13};
// Maximum PWM value
const float maxValue = 255.0;
// PWM step value
const float maxPwmStep = 20.0;
// Initialize PWM values for each LED
float pwmValues[] = {0, 0, 0};
// Initialize last PWM values for each LED
float lastPwmValues[] = {0, 0, 0};
// Last debounce time
unsigned long lastDebounceTime = 0;
// Debounce time; increase if output flickers
unsigned long debounceDelay = 50;

void setup() {
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT); // Set LED pins as output
    pinMode(brighterButtons[i], INPUT_PULLUP); // Set brighter button pins with pullup resistor
    pinMode(darkerButtons[i], INPUT_PULLUP); // Set darker button pins with pullup resistor
  }
  Serial.begin(9600); // Initialize serial port
}

void loop() {
  // Get current time
  unsigned long currentTime = millis();

  // Loop through each LED
  for (int i = 0; i < ledCount; i++) {
    // Check if the bright button is pressed for each LED and debounce time has passed and PWM value is less than maximum
    if (digitalRead(brighterButtons[i]) == LOW && currentTime - lastDebounceTime > debounceDelay && pwmValues[i] < maxPwmStep) {
      // Increase PWM value
      pwmValues[i]++;
      // Update last debounce time
      lastDebounceTime = currentTime;
    }
    // Delay to prevent multiple button presses
    delay(100);
    
    // Check if the dark button is pressed for each LED and debounce time has passed and PWM value is greater than 0
    if (digitalRead(darkerButtons[i]) == LOW && currentTime - lastDebounceTime > debounceDelay && pwmValues[i] > 0) {
      // Decrease PWM value
      pwmValues[i]--;
      // Update last debounce time
      lastDebounceTime = currentTime;
    }
    // Delay to prevent multiple button presses
    delay(100);
    // Apply PWM to each LED
    analogWrite(ledPins[i], maxValue * pwmValues[i] / maxPwmStep);
  }

  // Optional: Debugging output
  for (int i = 0; i < ledCount; i++) { // Loop through each LED
    if (pwmValues[i] != lastPwmValues[i]) { // Check if PWM value has changed
      lastPwmValues[i] = pwmValues[i]; // Update last PWM value
      Serial.print("PWM[Led: "); // Print LED 
      Serial.print(i); // Print LED index
      Serial.print(" Percentage: "); // Print PWM digital value
      Serial.print(pwmValues[i] * 100 / maxPwmStep); // Print PWM value
      Serial.print("% AnalogValue: "); // Print PWM digital value
      Serial.print(maxValue * pwmValues[i] / maxPwmStep); // Print PWM value      
      Serial.println("]"); // Print new line
    }
  }
}
