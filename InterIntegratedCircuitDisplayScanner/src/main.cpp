#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define LCD_ROWS 2 // Number of rows on the LCD
#define LCD_COLS 16 // Number of columns on the LCD

void DisplayTest(LiquidCrystal_I2C lcd);

/// @brief The setup function is called once at startup of the sketch
void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect. Needed for native USB port only  
  Serial.println("\nI2C Scanner");  
}

/// @brief The loop function is called in an endless loop
void loop() {
  byte error, address;
  int nDevices = 0;
 
  Serial.println("Scanning...");
 
  // Scan all I2C addresses from 1 to 127
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if a
    // device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address: ");
      
      if (address < 16)
        Serial.print("0x0");

      Serial.print("0x");
      Serial.print(address, HEX);

      LiquidCrystal_I2C lcd(address, LCD_COLS, LCD_ROWS);
      lcd.init();
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print("Device: #");
      lcd.print(nDevices);
      lcd.setCursor(0, 1);
      lcd.print("Address: 0x");
      lcd.print(address, HEX);
      
      delay(1000);
      DisplayTest(lcd);

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");

      if (address < 16)
        Serial.print("0");

      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
    
  // Wait 5 seconds for the next I2C scan
  delay(5000);
}

void DisplayTest(LiquidCrystal_I2C lcd)
{
  for (size_t r = 0; r < LCD_ROWS; r++)
  {
    for (size_t c = 0; c < LCD_COLS; c++)
    {
      lcd.setCursor(c, r);
      lcd.print("X");
      delay(250);
      lcd.setCursor(c, r);
      lcd.print(" ");
    }
  }
}
