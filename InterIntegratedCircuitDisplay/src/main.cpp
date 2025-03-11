#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27 // I2C address of the LCD
#define LCD_COLS 16 // Number of columns of the LCD
#define LCD_ROWS 2 // Number of rows of the LCD

long randNumber; // To store a random number
float randFloat; // To store a random float

void writeFirstLine(LiquidCrystal_I2C lcd, String message);
void writeSecondLine(LiquidCrystal_I2C lcd, String message);

// Create an LCD object
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDR, LCD_COLS, LCD_ROWS);

// the setup routine runs once when you press reset
void setup()
{
  // Initialize the LCD
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
  // seed the random number generator
  randomSeed(analogRead(0));

  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear();
}

// the loop routine runs over and over again forever
void loop()
{
  // Generate a random number and a random float
  randNumber = random(0, 100);
  randFloat = (float)random(0, 100) / 100.0;

  writeFirstLine(lcd, "Number: " + String(randNumber));
  writeSecondLine(lcd, "Float: " + String(randFloat, 2));
  delay(1000);
}

void writeFirstLine(LiquidCrystal_I2C lcd, String message)
{
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void writeSecondLine(LiquidCrystal_I2C lcd, String message)
{
  lcd.setCursor(0, 1);
  lcd.print(message);
}
