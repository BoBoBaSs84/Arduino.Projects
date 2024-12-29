#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ONE_ADRESS 0x20 // define the address of the first display
#define LCD_TWO_ADRESS 0x21 // define the address of the second display
#define LCD_THREE_ADRESS 0x22 // define the address of the third display
#define LCD_ROWS 2 // define the number of rows of the display
#define LCD_COLUMNS 16 // define the number of columns of the display

// create the displays
LiquidCrystal_I2C lcd1(LCD_ONE_ADRESS, LCD_COLUMNS, LCD_ROWS); // create the first display
LiquidCrystal_I2C lcd2(LCD_TWO_ADRESS, LCD_COLUMNS, LCD_ROWS); // create the second display
LiquidCrystal_I2C lcd3(LCD_THREE_ADRESS, LCD_COLUMNS, LCD_ROWS); // create the third display

// put function declarations here:
void initializeDisplay(LiquidCrystal_I2C);
void showOnDisplay(LiquidCrystal_I2C, String, String);

/// @brief This method is called once at the start
void setup() {
  randomSeed(analogRead(0)); // seed the random number generator
  Serial.begin(9600); // initialize the serial port
  initializeDisplay(lcd1); // initialize the first display
  initializeDisplay(lcd2); // initialize the second display
}

/// @brief This method is called repeatedly
void loop() {
  float randVoltage = (float)random(2900, 3100) / 1000.00; // generate a random voltage
  float randCurrent = (float)random(900, 1100) / 1000.00; // generate a random current
  String firstLine = "U: " + String(randVoltage) + "V"; // create the first line
  String secondLine = "I: " + String(randCurrent) + "A"; // create the second line
  showOnDisplay(lcd1, firstLine, secondLine); // show the message on the first display

  Serial.println(firstLine); // print the first line to the serial port
  Serial.println(secondLine); // print the second line to the serial port

  delay(500); // wait for 500 milliseconds

  randVoltage = (float)random(11900, 12100) / 1000.00; // generate a random voltage
  randCurrent = (float)random(900, 1100) / 1000.00; // generate a random current
  firstLine = "U: " + String(randVoltage) + "V"; // create the first line
  secondLine = "I: " + String(randCurrent) + "A"; // create the second line
  showOnDisplay(lcd2, firstLine, secondLine); // show the message on the second display
  
  Serial.println(firstLine); // print the first line to the serial port
  Serial.println(secondLine); // print the second line to the serial port

  delay(500); // wait for 500 milliseconds
}

/// @brief This method initializes the display
/// @param display The display to initialize
void initializeDisplay (LiquidCrystal_I2C display) {  
  display.init(); // initialize the lcd
  display.backlight(); // turn on the backlight
  display.home(); // set the cursor to the top left
}

/// @brief This method shows the message on the display
/// @param display The display to show the message on
/// @param firstLine The first line of the message
/// @param secondLine The second line of the message
void showOnDisplay(LiquidCrystal_I2C display, String firstLine, String secondLine) {
  display.clear(); // clear the display
  display.setCursor(0, 0); // set the cursor to the top left
  display.print(firstLine); // print the voltage
  display.setCursor(0, 1); // set the cursor to the bottom left
  display.print(secondLine); // print the current
}
