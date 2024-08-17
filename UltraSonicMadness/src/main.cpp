#include <Arduino.h>

// Define the RGB values for the minimum and maximum distances

const uint8_t minDistance = 5;  // Minimum distance in cm
const uint8_t maxDistance = 50; // Maximum distance in cm

const uint8_t minRed = 255;     // Red value for the minimum distance
const uint8_t minGreen = 0;     // Green value for the minimum distance
const uint8_t minBlue = 0;      // Blue value for the minimum distance

const uint8_t maxRed = 0;       // Red value for the maximum distance
const uint8_t maxGreen = 255;   // Green value for the maximum distance
const uint8_t maxBlue = 0;      // Blue value for the maximum distance

// Define the pins for the ultrasonic sensor, the RGB LED and the buzzer

const uint8_t trigPin = 9;      // The pin number of the trigger pin
const uint8_t echoPin = 10;     // The pin number of the echo pin
const uint8_t redPin = 3;       // Define the red pin of the RGB LED
const uint8_t greenPin = 5;     // Define the green pin of the RGB LED
const uint8_t bluePin = 6;      // Define the blue pin of the RGB LED
const uint8_t buzzerPin = 8;    // Define the pin for the buzzer

// Define the variables for the ultrasonic sensor

uint64_t duration;              // The variable that will store the duration of the sound wave travel
uint8_t distance;               // The variable that will store the distance measurement

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Wait for the serial port to connect
  }
  
  // Set the trigPin as OUTPUT and echoPin as INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

   // Set the RGB LED pins as OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set the buzzer pin as OUTPUT
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  // Wait for a short period before the next measurement
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  // Wait for 10 microseconds
  delayMicroseconds(10);
  // Set the trigger pin to LOW again
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance with the speed of sound (343m/s) and the duration of the sound wave travel
  // Divide the result by 2 because the sound wave travels to the object and back
  distance = duration * 0.034 / 2;
  
  // Print the distance on the Serial Monitor
  Serial.println("Distance: " + String(distance) + " cm");

  // Clamp the distance to the range [minDistance, maxDistance]
  distance = constrain(distance, minDistance, maxDistance);

  // Calculate the RGB values based on the distance
  int redValue = map(distance, minDistance, maxDistance, minRed, maxRed);
  int greenValue = map(distance, minDistance, maxDistance, minGreen, maxGreen);
  int blueValue = map(distance, minDistance, maxDistance, minBlue, maxBlue);

  // Set the RGB LED color
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);

  // Check if the distance is less than or equal to the minimum distance
  if (distance <= minDistance) {
    // Activate the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Deactivate the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Wait for a short period before the next measurement
  delay(100);
}
