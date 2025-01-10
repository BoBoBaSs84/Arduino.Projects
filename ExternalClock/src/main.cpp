#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// the address of the external clock
#define DS3231_I2C_ADDRESS 0x68

// initialize the LCD object
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void showOnDisplay(String, String);
void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Wire.begin();
  lcd.begin(16, 2);
  setTime(0, 42, 19, 6, 10, 1, 25); // set the time and date to Friday the 19:30:00 01/10/2025
}

// the loop function runs over and over again forever
void loop() {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission(); // stop transmitting
  
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7); // request seven bytes of data from DS3231 starting from register 00h
  
  // read the data from DS3231, seven bytes in total
  byte second = Wire.read(); // read the seconds
  byte minute = Wire.read(); // read the minutes
  byte hour = Wire.read(); // read the hours
  byte dayOfWeek = Wire.read(); // read the day of the week
  byte dayOfMonth = Wire.read(); // read the day of the month
  byte month = Wire.read(); // read the month
  byte year = Wire.read(); // read the year
  
  // Convert BCD to decimal
  second = ((second >> 4) * 10 + (second & 0x0F));
  minute = ((minute >> 4) * 10 + (minute & 0x0F));
  hour = ((hour >> 4) * 10 + (hour & 0x0F));
  dayOfWeek = (dayOfWeek & 0x07);
  dayOfMonth = ((dayOfMonth >> 4) * 10 + (dayOfMonth & 0x0F));
  month = ((month >> 4) * 10 + (month & 0x0F));
  year = ((year >> 4) * 10 + (year & 0x0F));
  
  char date[11]; // create a character array to store the date
  sprintf(date, "%02lu-%02lu-%02lu", (unsigned long)(year + 2000), (unsigned long)month, (unsigned long)dayOfMonth); // format the date as YYYY-MM-DD
  char time[9]; // create a character array to store the time
  sprintf(time, "%02lu:%02lu:%02lu", (unsigned long)hour, (unsigned long)minute, (unsigned long)second); // format the time as HH:MM:SS
  showOnDisplay("Date: "+String(date), "Time: "+ String(time)); // show the date and time on the display
  
  delay(1000); // wait for a second
}

/// @brief This function shows the given strings on the display.
/// @param firstRow The string to show on the first row.
/// @param secondRow The string to show on the second row.
void showOnDisplay(String firstRow, String secondRow) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstRow);
  lcd.setCursor(0, 1);
  lcd.print(secondRow);
}

/// @brief This function sets the time and date on the DS3231.
/// @param second The second to set.
/// @param minute The minute to set.
/// @param hour The hour to set.
/// @param dayOfWeek The day of the week to set. (1=Sunday, 7=Saturday)
/// @param dayOfMonth The day of the month to set.
/// @param month The month to set.
/// @param year The year to set.
void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.write(((second / 10) << 4) + (second % 10)); // set seconds
  Wire.write(((minute / 10) << 4) + (minute % 10)); // set minutes
  Wire.write(((hour / 10) << 4) + (hour % 10)); // set hours
  Wire.write(dayOfWeek); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(((dayOfMonth / 10) << 4) + (dayOfMonth % 10)); // set day of month
  Wire.write(((month / 10) << 4) + (month % 10)); // set month
  Wire.write(((year / 10) << 4) + (year % 10)); // set year (last two digits)
  Wire.endTransmission();
}
