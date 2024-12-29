#include <Arduino.h>
#include <math.h>

// Pin connected to SV1:3 -> SH_CP(11)
const uint8_t clockPin = 3;
// Pin connected to SV1:4 -> ST_CP(12)
const uint8_t latchPin = 4;
// Pin connected to SV1:5 -> DS(14)
const uint8_t dataPin = 5;

const uint8_t ledPin1 = 0;
const uint8_t layerGround1 = 16;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
}

// the loop function runs over and over again forever
void loop() {
  int32_t i = pow(2, ledPin1) + pow(2, layerGround1);
  Serial.println("Number is:" + String(i));
  unsigned char bytes[3];
  bytes[0] = (i >> 16) & 0xFF;
  bytes[1] = (i >> 8) & 0xFF;
  bytes[2] = i & 0xFF;
  Serial.println("Byte[0] is:" + String(bytes[0]));
  Serial.println("Byte[1] is:" + String(bytes[1]));
  Serial.println("Byte[2] is:" + String(bytes[2]));

  // ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, LOW);
  delay(1000);

  shiftOut(dataPin, clockPin, MSBFIRST, bytes[0]);
  shiftOut(dataPin, clockPin, MSBFIRST, bytes[1]);
  shiftOut(dataPin, clockPin, MSBFIRST, bytes[3]);

  // return the latch pin high to signal chip that it
  // no longer needs to listen for information
  digitalWrite(latchPin, HIGH);
  delay(1000);
}