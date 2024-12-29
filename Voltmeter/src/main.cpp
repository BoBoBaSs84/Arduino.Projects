#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ONE_ADRESS 0x20
#define LCD_TWO_ADRESS 0x21
#define LCD_THREE_ADRESS 0x22
#define DISPLAY_ROWS 2
#define DISPLAY_COLUMNS 16

LiquidCrystal_I2C lcd1(LCD_ONE_ADRESS, DISPLAY_COLUMNS, DISPLAY_ROWS);
LiquidCrystal_I2C lcd2(LCD_TWO_ADRESS, DISPLAY_COLUMNS, DISPLAY_ROWS);
LiquidCrystal_I2C lcd3(LCD_THREE_ADRESS, DISPLAY_COLUMNS, DISPLAY_ROWS);

// put function declarations here:
void InitializeDisplay(LiquidCrystal_I2C);
void ShowMessage(LiquidCrystal_I2C, String, String);

/// @brief This method is called once at the start
void setup() {
  // put your setup code here, to run once:
  InitializeDisplay(lcd1);
  InitializeDisplay(lcd2);
  InitializeDisplay(lcd3);

  ShowMessage(lcd1, "U: +5.1V I: 0.1A", "U: -5.1V I: 0.1A");
  ShowMessage(lcd2, "U:+12.0V I: 0.1A", "U:-12.1V I: 0.1A");
  ShowMessage(lcd3, "U:+29.9V I: 0.5A", "");
}

/// @brief This method is called repeatedly
void loop() {
  for (size_t l = 0; l < 2; l++)
  {
    for (size_t p = 0; p < 16; p++)
    {
      lcd1.setCursor(p, l);
      lcd1.print("0");
    }
  }
  for (size_t l = 0; l < 2; l++)
  {
    for (size_t p = 0; p < 16; p++)
    {
      lcd1.setCursor(p, l);
      lcd1.print(" ");
    }
  }
}

/// @brief This method initializes the display and sets the cursor to the top left corner
/// @param display The display to initialize
void InitializeDisplay (LiquidCrystal_I2C display) {  
  display.init(); // initialize the lcd
  display.backlight(); // turn on the backlight
  display.home(); // set the cursor to the top left
}

/// @brief This method shows a message on the display
/// @param display The display to show the message on
/// @param firstLine The first line of the message
/// @param secondLine The second line of the message
void ShowMessage (LiquidCrystal_I2C display, String firstLine, String secondLine) {  
  display.clear(); // clear the display
  display.setCursor(0, 0); // set the cursor to the top left
  display.print(firstLine); // print the first line
  display.setCursor(0, 1); // set the cursor to the second line
  display.print(secondLine); // print the second line
}
