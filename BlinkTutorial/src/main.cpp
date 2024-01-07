/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework
#define LED_BUILTIN 13
int counter = 0;

void setup()
{
  // initialize LED digital pin as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize serial output monitor
  Serial.begin(9600);
  Serial.print("Setup done.");
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(500);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  delay(500);

  // output via serial monitor
  counter++;
  Serial.println("Blink Number # ");
  Serial.println(counter);  
}