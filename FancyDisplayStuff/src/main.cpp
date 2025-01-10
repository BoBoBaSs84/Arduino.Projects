#include <Arduino.h>
#include <LiquidCrystal.h>

// put constants here:
const int resetPin = 12 // the reset pin
  , enablePin = 11 // the enable pin
  , lcdDataPin4 = 5 // the rest are data pins
  , lcdDataPin5 = 4
  , lcdDataPin6 = 3
  , lcdDataPin7 = 2;

// put global variables here:
LiquidCrystal lcd(resetPin, enablePin, lcdDataPin4, lcdDataPin5, lcdDataPin6, lcdDataPin7); // initialize the lcd object

// A custom character (a smiley face) is defined using a byte array.
// Each byte represents a row of pixels on the 5x8 dot matrix of the LCD character.
// Custom character definition (a happy smiley face)
byte happySmiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

// Custom character definition (a sad smiley face)
byte sadSmiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
};

// custom character definition (a heart)
byte heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};

void showOnDisplay(String firstLine, String secondLine);
void showFunkyStuff();

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  while (!Serial) // wait for the serial connection to be established:
  {
  }
  lcd.begin(16, 2); // set up the LCD's number of columns and rows
  lcd.createChar(0, happySmiley); // create the custom character at index 0
  lcd.createChar(1, sadSmiley); // create the custom character at index 1
  lcd.createChar(2, heart); // create the custom character at index 2
  lcd.setCursor(0, 0); // set the cursor to the first column of the first row
  lcd.write(byte(0)); // write the custom character stored at index 0
  lcd.setCursor(1, 0); // set the cursor to the second column of the first row
  lcd.write(byte(2)); // write the custom character stored at index 2
  lcd.setCursor(0, 1); // set the cursor to the first column of the second row
  lcd.write(byte(1)); // write the custom character stored at index 1
  
  // showFunkyStuff(); // show some funky stuff on the display
  // delay(2000); // wait for 2 seconds
  // showOnDisplay("Hello, World!", "I'm an LCD!"); // show the message on the display
  // delay(2000); // wait for 2 seconds
}

// the loop function runs over and over again forever
void loop() {
  unsigned long currentMillis = millis(); // get the number of milliseconds since the program started
  unsigned long totalSeconds = currentMillis / 1000; // convert milliseconds to seconds
  unsigned long seconds = totalSeconds % 60; // get the current seconds
  unsigned long minutes = (totalSeconds / 60) % 60; // get the current minutes
  unsigned long hours = (totalSeconds / 3600) % 24; // get the current hours

  char timeString[9]; // create a character array to store the time
  sprintf(timeString, "%02lu:%02lu:%02lu", hours, minutes, seconds); // format the time as HH:MM:SS

  lcd.setCursor(1, 1); // set the cursor to the second column of the second row
  lcd.print(" t: " + String(timeString)); // print the time on the display
}

/// @brief This function shows the given strings on the display.
/// @param firstLine The string to show on the first line.
/// @param secondLine The string to show on the second line.
void showOnDisplay(String firstLine, String secondLine) {
  lcd.clear(); // clear the display
  lcd.setCursor(0, 0); // set the cursor to the first column of the first row
  lcd.print(firstLine); // print the first line
  lcd.setCursor(0, 1); // set the cursor to the first column of the second row
  lcd.print(secondLine); // print the second line
}

/// @brief This function shows some funky stuff on the display.
/// It alternates between two custom characters on the display.
/// The first custom character is a happy smiley face, and the second custom character is a sad smiley face.
void showFunkyStuff(){
  for (size_t r = 0; r < 2; r++) // loop through the rows
  {
    for (size_t c = 0; c < 16; c++) // loop through the columns
    {
      lcd.setCursor(c, r); // set the cursor to the current column and row
      if ((r + c) % 2 == 0) // if the sum of the row and column is even!
      {
        lcd.write(byte(0)); // write the custom character stored at index 0
      }
      else // if the sum of the row and column is odd!
      {
        lcd.write(byte(1)); // write the custom character stored at index 1
      }
      delay(100); // wait for 100 milliseconds
    }
  }

  for (size_t r = 0; r < 2; r++) // loop through the rows
  {
    for (size_t c = 0; c < 16; c++) // loop through the columns
    {
      lcd.setCursor(c, r); // set the cursor to the current column and row
      if ((r + c) % 2 == 0) // if the sum of the row and column is even!
      {
        lcd.write(byte(1)); // write the custom character stored at index 1
      }
      else // if the sum of the row and column is odd!
      {
        lcd.write(byte(0)); // write the custom character stored at index 0
      }
      delay(100); // wait for 100 milliseconds
    }
  }
}
