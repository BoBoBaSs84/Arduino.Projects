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

// define message stuff
#define MESSAGE_SIZE 32 // in bytes

// create the LCD object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// function prototypes
void showOnDisplay(String firstRow, String secondRow);
void deviceScanner(int adressArray[], int adressArraySize, int currentAdressArrayIndex);

// global variables
int adressArray[8]; // the array that holds the addresses of the devices
int adressArraySize = sizeof(adressArray) / sizeof(adressArray[0]); // the size of the adress array
int currentAdressArrayIndex = 0; // the current adress array index
int foundDevices = 0; // the number of devices found

// the setup function runs once when you press reset or power the board
void setup()
{
    // set up the LCD's number of columns and rows
    lcd.begin(LCD_COLUMNS, LCD_ROWS);
    // print a message to the LCD
    showOnDisplay("Message Broker", "Version: 1.0");
    // wait for a second
    delay(1000);
    // set up the I2C bus
    Wire.begin();
}

// the loop function runs over and over again forever
void loop()
{
    // iterate over the addresses and recieve the data
    for (int a = 0; a < 127; a++)
    {
        byte errorCode;
        // begin the transmission
        Wire.beginTransmission(a);
        // end the transmission and store the error code
        errorCode = Wire.endTransmission();
        // if the transmission was successful
        if (errorCode == 0)
        {
            // show a read data message on the display
            showOnDisplay("Reading data...", "Please wait...");
            // wait for 1 second
            delay(1000);
            // request 32 bytes from the device
            Wire.requestFrom(a, MESSAGE_SIZE);
            // if there are 32 bytes available
            while (Wire.available())
            {
                // define the message data array
                char data[MESSAGE_SIZE];
                // read the data char by char
                for (int d = 0; d < MESSAGE_SIZE; d++)
                {
                    data[d] = Wire.read();
                }
                // show the sender adress on the display
                showOnDisplay("Sender: " + String(a, HEX) + "h", "Data received!");
                delay(1000);
                // process the data as needed
                String firstRow = String(data).substring(0, 16); // assuming first 16 bytes for first row
                String secondRow = String(data).substring(16, 32); // assuming last 16 bytes for secon row
                // show the data on the display
                showOnDisplay(firstRow, secondRow);
                // wait for 5 seconds
                delay(2000);
            }
        }
    }
}

/// @brief This function shows the given strings on the display.
/// @param firstRow The text to show on the first row.
/// @param secondRow The text to show on the second row.
void showOnDisplay(String firstRow, String secondRow)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(firstRow);
    lcd.setCursor(0, 1);
    lcd.print(secondRow);
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
        showOnDisplay("Found device!", "Address: " + String(i, HEX) + "h");
        
        // store the address in the array
        for (foundDevices; foundDevices < adressArraySize; foundDevices++)
        {
            adressArray[foundDevices] = i;
            break;
        }

        // wait for 1 seconds
        delay(1000);
    }
  }
}
