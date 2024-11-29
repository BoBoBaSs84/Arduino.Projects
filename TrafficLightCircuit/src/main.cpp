#include <Arduino.h>
/// Traffic light circuit with a pedestrian walk button
/// The circuit has a traffic light with red, yellow and green lights and a pedestrian walk light with red and green lights.
/// The traffic light sequence is red -> yellow -> green -> yellow -> red
/// The walk light sequence is green -> red
/// The walk light sequence is activated when the pedestrian walk button is pressed

// Pin assignments
const uint8_t carGreenLightPin = 2; // Green light is connected to pin 2
const uint8_t carYellowLightPin = 3; // Yellow light is connected to pin 3
const uint8_t carRedLightPin = 4; // Red light is connected to pin 4
const uint8_t walkGreenLightPin = 5; // Green walk light is connected to pin 5
const uint8_t walkRedLightPin = 6; // Red walk light is connected to pin 6
const uint8_t buttonPin = 7; // Interrupt pin for the walk button

// Timing constants
const int carRedLightDuration = 5000; // 5 seconds
const int carYellowLightDuration = 2000; // 2 seconds
const int carGreenLightDuration = 5000; // 5 seconds
const int walkLightDuration = 5000; // 5 seconds

// Function prototypes
void switchOnTrafficLight(uint8_t red, uint8_t yellow, uint8_t green);
void switchOnWalkLight(uint8_t greenWalk, uint8_t redWalk);
void handleWalkButtonPress();
void normalTrafficLightSequence();
void walkLightSequence();

// Variable to track if the walk button was pressed
volatile bool walkButtonPressed = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // Set the baud rate for the serial monitor
  Serial.begin(9600);
  // Wait for the serial monitor to open
  while (!Serial) {
  }

  // Initialize the digital pins as outputs
  pinMode(carRedLightPin, OUTPUT);
  pinMode(carYellowLightPin, OUTPUT);
  pinMode(carGreenLightPin, OUTPUT);
  pinMode(walkGreenLightPin, OUTPUT);
  pinMode(walkRedLightPin, OUTPUT);
  
  // Initialize the button pin as input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Attach interrupt to the button pin
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleWalkButtonPress, FALLING);
}

// the loop function runs over and over again forever
void loop() {
  if (walkButtonPressed) {
    // Walk light sequence
    walkLightSequence();
  } else {
    // Normal traffic light sequence
    normalTrafficLightSequence();
  }
}

// Function to handle the normal traffic light sequence
void normalTrafficLightSequence() {
  // Switch the red light on
  switchOnTrafficLight(HIGH, LOW, LOW);
  // Wait for the red light duration to pass
  delay(carRedLightDuration);

  // Switch the yellow and red light on
  switchOnTrafficLight(HIGH, HIGH, LOW);
  // Wait for the yellow light duration to pass
  delay(carYellowLightDuration);

  // Switch the green light on
  switchOnTrafficLight(LOW, LOW, HIGH);
  // Wait for the green light duration to pass
  delay(carGreenLightDuration);

  // Switch the yellow light on
  switchOnTrafficLight(LOW, HIGH, LOW);
  // Wait for the yellow light duration to pass
  delay(carYellowLightDuration);
}

// Function to handle the walk light sequence
void walkLightSequence() {
  // Switch the green walk light on
  switchOnWalkLight(HIGH, LOW);
  // Wait for the walk light duration to pass
  delay(walkLightDuration);
  // Switch the red walk light on
  switchOnWalkLight(LOW, HIGH);
  // Reset the walk button pressed flag
  walkButtonPressed = false;
}

// Function to switch on the traffic lights
void switchOnTrafficLight(uint8_t red, uint8_t yellow, uint8_t green) {
  Serial.println("Switching on traffic light");
  digitalWrite(carRedLightPin, red); // Switch the red light on or off
  digitalWrite(carYellowLightPin, yellow); //Switch the yellow light on or off
  digitalWrite(carGreenLightPin, green); // Switch the green light on or off
  digitalWrite(walkGreenLightPin, LOW); // Switch the green walk light off
  digitalWrite(walkRedLightPin, HIGH); // Switch the red walk light off
}

// Function to switch on the walk lights
void switchOnWalkLight(uint8_t greenWalk, uint8_t redWalk) {
  Serial.println("Switching on walk light");
  digitalWrite(carRedLightPin, LOW); // Switch the red light off
  digitalWrite(carYellowLightPin, LOW); //Switch the yellow light off
  digitalWrite(carGreenLightPin, LOW); // Switch the green light off
  digitalWrite(walkGreenLightPin, greenWalk); // Switch the green walk light on or off
  digitalWrite(walkRedLightPin, redWalk); // Switch the red walk light on or off
}

// Function to handle the walk button press
void handleWalkButtonPress() {
  Serial.println("Walk button pressed");
  walkButtonPressed = true; // Set the walk button pressed flag
}
