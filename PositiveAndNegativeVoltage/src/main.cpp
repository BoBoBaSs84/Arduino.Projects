#include <Arduino.h>

// put function declarations here:
int getSensorValue(int8_t pin);
float getVoltage(int sensorValue, float maximumVoltage, float minimumVoltage);

// put your setup code here, to run once:
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;// wait for serial port to connect. Needed for native USB port only
  }
}

// put your main code here, to run repeatedly:
void loop() {
  int sensorValue = getSensorValue(A0);
  float voltage = getVoltage(sensorValue, 15.0, 15.0);
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(", Voltage: ");
  Serial.println(voltage);
  delay(1000);
}

/// @brief This function reads the sensor value from the analog pin
/// @param pin The analog pin number
/// @return The sensor value
int getSensorValue(int8_t pin) {
  return analogRead(pin);
}

/// @brief This function converts the sensor value to voltage by using the maximum and minimum voltage values
/// @param sensorValue The sensor value to be converted to voltage
/// @param maximumVoltage The maximum voltage value of the sensor
/// @param minimumVoltage The minimum voltage value of the sensor
/// @return The calculated voltage value
float getVoltage(int sensorValue, float maximumVoltage, float minimumVoltage) {
  float voltage = ((float)sensorValue / 1023.0) * (maximumVoltage + minimumVoltage);
  return voltage - minimumVoltage;
}
