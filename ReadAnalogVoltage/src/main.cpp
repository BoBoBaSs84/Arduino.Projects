#include <Arduino.h>

// declare constants
const unsigned long interval = 2000; // interval at which to read the sensor value in milliseconds

// declare functions
int getSensorValue(uint8_t pin);
float getVoltage(int sensorValue, float maxVoltage);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // wait for the serial monitor to open
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = getSensorValue(A0);
  // print the sensor value:
  Serial.println("Sensor Value: " + String(sensorValue));
  // calculate the voltage:
  float voltage = getVoltage(sensorValue, 5.0);
  // print the voltage:
  Serial.println("Voltage: " + String(voltage) + "V");
  // wait 2 seconds for the next reading:
  delay(interval);
}

/// @brief This function reads the sensor value from the given pin.
/// @param pin The pin to read the sensor value from.
/// @return The sensor value.
int getSensorValue(uint8_t pin) {
  return analogRead(pin);
}

/// @brief This function calculates the voltage by taking the sensor value and dividing it by 1023, then multiplying it by the maximum voltage.
/// @param sensorValue The sensor value to use.
/// @param maxVoltage The maximum voltage to use.
/// @return The calculated voltage.
float getVoltage(int sensorValue, float maxVoltage) {
  return sensorValue * (maxVoltage / 1023.0);
}
 