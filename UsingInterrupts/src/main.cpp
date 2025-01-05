#include <Arduino.h>

const byte ledPin = 5; // Pin 5 is connected to the LED
const byte interruptPin = 2; // Pin 2 is connected to the interrupt
volatile byte state = LOW; // The state of the LED

void blink();

// The setup function runs once when you press reset or power the board
void setup() {
  pinMode(ledPin, OUTPUT); // Initialize the digital pin as an output
  pinMode(interruptPin, INPUT_PULLUP); // Initialize the digital pin as an input with a pull-up resistor
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE); // Attach the interrupt to the interrupt pin
}

// The loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, state); // Turn the LED on or off
}

// The interrupt service routine
void blink() {
  state = !state; // Toggle the state of the LED
}
