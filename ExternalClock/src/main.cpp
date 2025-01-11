#include <Arduino.h>
#include <DateTime.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// define the display pins
#define LCD_RS 12 // register select pin
#define LCD_EN 11 // enable pin
#define LCD_D4 5 // data pin 4
#define LCD_D5 4 // data pin 5
#define LCD_D6 3 // data pin 6
#define LCD_D7 2 // data pin 7

// the address of the external clock
#define DS3231_I2C_ADDRESS 0x68

// initialize the LCD object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void showOnDisplay(String, String);
void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
DateTime getCurrentDateTime(byte address);
void showDateTimeOnDisplay(DateTime dateTime);

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize the serial communication
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial)
  {
  }
  // initialize the I2C communication
  Wire.begin();
  // initialize the LCD
  lcd.begin(16, 2);
  // set the time and date on the DS3231
  setTime(0, 30, 13, 7, 11, 1, 25); // set the current time and date
}

// the loop function runs over and over again forever
void loop()
{
  // get the current date and time
  DateTime dt = getCurrentDateTime(DS3231_I2C_ADDRESS);
  // show the date and time on the display
  showDateTimeOnDisplay(dt);
  // wait for a second
  delay(1000);
}

/// @brief This function shows the given date and time on the display.
/// @param dateTime The date and time to show.
void showDateTimeOnDisplay(DateTime dateTime)
{
  // create a character array to store the date
  char date[9];
  // format the date as YYYY-MM-DD
  sprintf(date, "%02lu-%02lu-%02lu", (unsigned long)(dateTime.year + 2000), (unsigned long)dateTime.month, (unsigned long)dateTime.dayOfMonth);
  // create a character array to store the time
  char time[8];
  // format the time as HH:MM:SS
  sprintf(time, "%02lu:%02lu:%02lu", (unsigned long)dateTime.hour, (unsigned long)dateTime.minute, (unsigned long)dateTime.second);
  // show the date and time on the display
  showOnDisplay("Date: "+String(date), "Time: "+ String(time));
}

/// @brief This function shows the given strings on the display.
/// @param firstRow The string to show on the first row.
/// @param secondRow The string to show on the second row.
void showOnDisplay(String firstRow, String secondRow)
{
  lcd.clear(); // clear the display
  lcd.setCursor(0, 0); // set the cursor to the first row
  lcd.print(firstRow); // print the first row
  lcd.setCursor(0, 1); // set the cursor to the second row
  lcd.print(secondRow); // print the second row
}

/// @brief This function sets the time and date on the DS3231.
/// @param second The second to set.
/// @param minute The minute to set.
/// @param hour The hour to set.
/// @param dayOfWeek The day of the week to set. (1=Sunday, 7=Saturday)
/// @param dayOfMonth The day of the month to set.
/// @param month The month to set.
/// @param year The year to set.
void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
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

/// @brief This function gets the current date and time from the DS3231.
/// @param address The address of the DS3231.
/// @return The current date and time.
DateTime getCurrentDateTime(byte address)
{
  // start transmitting  
  Wire.beginTransmission(address);
  // set DS3231 register pointer to 00h
  Wire.write(0);
  // stop transmitting
  Wire.endTransmission();
  // request seven bytes of data from DS3231 starting from register 00h
  Wire.requestFrom(address, 7);

  // read the data from DS3231, seven bytes in total
  byte second = Wire.read(); // read the seconds
  byte minute = Wire.read(); // read the minutes
  byte hour = Wire.read(); // read the hours
  byte dayOfWeek = Wire.read(); // read the day of the week
  byte dayOfMonth = Wire.read(); // read the day of the month
  byte month = Wire.read(); // read the month
  byte year = Wire.read(); // read the year

  // Convert binary code decimal to decimal base ten integer
  second = ((second >> 4) * 10 + (second & 0x0F));
  minute = ((minute >> 4) * 10 + (minute & 0x0F));
  hour = ((hour >> 4) * 10 + (hour & 0x0F));
  dayOfWeek = (dayOfWeek & 0x07);
  dayOfMonth = ((dayOfMonth >> 4) * 10 + (dayOfMonth & 0x0F));
  month = ((month >> 4) * 10 + (month & 0x0F));
  year = ((year >> 4) * 10 + (year & 0x0F));

  // return the read date and time
  return DateTime(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}
