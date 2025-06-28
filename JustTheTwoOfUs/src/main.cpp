// Description: This code scans the I2C bus for devices and shows the addresses on an LCD display
// Author:      Robert Peter Meyer
// Date:        2025-01-11
// Version:     1.0

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// define the LCD pins
#define LCD_RS 12 // Reset pin
#define LCD_EN 11 // Enable pin
#define LCD_D4 5 // Data pin five (D4)
#define LCD_D5 4 // Data pin four (D5)
#define LCD_D6 3 // Data pin three (D6)
#define LCD_D7 2 // Data pin two (D7)

// define the LCD dimensions
#define LCD_COLUMNS 16 // 16 columns
#define LCD_ROWS 2 // 2 rows

// create the LCD object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// function prototypes
void deviceScanner(int adressArray[], int adressArraySize, int currentAdressArrayIndex);
void showOnDisplay(String firstRow, String secondRow);

// global variables
int adressArray[8]; // the array that holds the addresses of the devices
int adressArraySize = sizeof(adressArray) / sizeof(adressArray[0]); // the size of the adress array
int currentAdressArrayIndex = 0; // the current adress array index

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize the serial communication
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // set up the LCD's number of columns and rows
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  // set up the I2C bus
  Wire.begin();
  // scan the I2C bus for devices
  deviceScanner(adressArray, adressArraySize, currentAdressArrayIndex);
}

// the loop function runs over and over again forever
void loop()
{
  // iterate over the addresses and print them to the serial monitor
  for (int i = 0; i < adressArraySize; i++)
  {
    // begin the transmission
    Wire.beginTransmission(adressArray[i]);
    // if the transmission was successful
    if (Wire.endTransmission() == 0)
    {
      // print the address to the serial monitor
      Serial.print("Found device at address: ");
      Serial.println(adressArray[i]);
      // show the address on the display as hex value
      showOnDisplay("Device at", "address: " + String(adressArray[i], HEX) + "h");
      // wait for 2 seconds
      delay(2000);
    }
  }
}

/// @brief This funtion scans the I2C bus for devices and stores the addresses in an array
/// @param adressArray The array that holds the addresses of the devices
/// @param adressArraySize The size of the adress array
/// @param currentAdressArrayIndex The current adress array index
void deviceScanner(int adressArray[], int adressArraySize, int currentAdressArrayIndex)
{
  // iterate over the addresses and print them to the serial monitor
  for (int i = 0; i < 127; i++)
  {
     // begin the transmission
    Wire.beginTransmission(i);
     // if the transmission was successful
    if (Wire.endTransmission() == 0)
    {
      // print the address to the serial monitor
      Serial.print("Found device at address: ");
      Serial.println(i);
      
      // store the address in the array
      for (currentAdressArrayIndex; currentAdressArrayIndex < adressArraySize; currentAdressArrayIndex++)
      {
        adressArray[currentAdressArrayIndex] = i;
        break;
      }
    }
  }
}

/// @brief This function shows the given text on the display
/// @param firstRow The text to show on the first row
/// @param secondRow The text to show on the second row
void showOnDisplay(String firstRow, String secondRow)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstRow);
  lcd.setCursor(0, 1);
  lcd.print(secondRow);
}
