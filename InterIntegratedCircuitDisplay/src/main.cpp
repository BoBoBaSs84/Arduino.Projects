#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27 // I2C address of the LCD
#define LCD_COLS 16 // Number of columns of the LCD
#define LCD_ROWS 2 // Number of rows of the LCD

// Create an LCD object
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDR, LCD_COLS, LCD_ROWS);

// the setup routine runs once when you press reset
void setup()
{
  // Initialize the LCD
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
}

// the loop routine runs over and over again forever
void loop()
{
  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear();
  delay(1000);
}
