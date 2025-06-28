//
// Author: BoBoBaSs84
// This code is a simple Arduino sketch that reads the current date and time from a DS3231 RTC (Real Time Clock) module
// and displays it on an I2C LCD. It initializes the DS3231 with a specific date and time, retrieves the current date
// and time and shows it on the LCD display. The code uses the Wire library for I2C communication and the LiquidCrystal_I2C
// library for controlling the LCD.
// In addition, it sets up a web server to allow users to view and set the time and date via a web interface.
//
#include <Arduino.h>
#include <DateTime.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// the address of the external clock
#define DS3231_I2C_ADDRESS 0x68
// the data length to read
#define DS3231_DATA_LENGTH (uint8_t)7
// the address of the I2C LCD display
#define LCD_I2C_ADDRESS 0x23
// the columns of the lcd display
#define LCD_COLUMNS 16
// the rows of the lcd display
#define LCD_ROWS 2

// WiFi credentials - CHANGE THESE TO YOUR NETWORK
const char* ssid = "e-Haus";
const char* password = "e-Haus_Wlan";

// Web server on port 80
WebServer server(80);

// initialize the I2C LCD object (address, columns, rows)
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void showOnDisplay(String, String);
void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
DateTime getCurrentDateTime(byte address);
void showDateTimeOnDisplay(DateTime dateTime);
void setupWiFi();
void setupWebServer();
void handleDateTime();
void handleSetTime();
void handleRoot();

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
  // initialize the I2C LCD
  lcd.init();
  // clear the display
  lcd.clear();
  // turn on the backlight
  lcd.backlight();
  // setup WiFi connection
  setupWiFi();
  // setup web server routes
  setupWebServer();
  // set the time and date on the DS3231
  setTime(0, 0, 0, 7, 1, 1, 25); // set the current time and date
}

// the loop function runs over and over again forever
void loop()
{
  // handle web server requests
  server.handleClient();
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
  // set the cursor to the first row
  lcd.setCursor(0, 0);
  // print the first row
  lcd.print(firstRow);
  // set the cursor to the second row
  lcd.setCursor(0, 1);
  // print the second row
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
DateTime getCurrentDateTime(uint8_t address)
{
  // start transmitting  
  Wire.beginTransmission(address);
  // set DS3231 register pointer to 00h
  Wire.write(0);
  // stop transmitting
  Wire.endTransmission();
  // request seven bytes of data from DS3231 starting from register 00h
  Wire.requestFrom(address, DS3231_DATA_LENGTH);

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

/// @brief Setup WiFi connection
void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  // Show connecting status on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(1000);
    Serial.print(".");
    lcd.setCursor(attempts % 16, 1);
    lcd.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("WiFi connected! IP address: ");
    Serial.println(WiFi.localIP());
    
    // Show IP address on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected!");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    delay(3000);
  } else {
    Serial.println("Failed to connect to WiFi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Failed!");
    delay(3000);
  }
}

/// @brief Setup web server routes
void setupWebServer() {
  // Root endpoint - API documentation
  server.on("/", handleRoot);
  
  // GET current date and time
  server.on("/api/datetime", HTTP_GET, handleDateTime);
  
  // POST to set date and time
  server.on("/api/settime", HTTP_POST, handleSetTime);
  
  // Enable CORS for all routes
  server.enableCORS(true);
  
  // Start the server
  server.begin();
  Serial.println("Web server started");
}

/// @brief Handle root endpoint - show API documentation
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 Clock API</title></head><body>";
  html += "<h1>ESP32 Real-Time Clock API</h1>";
  html += "<h2>Available Endpoints:</h2>";
  html += "<ul>";
  html += "<li><strong>GET /api/datetime</strong> - Get current date and time in JSON format</li>";
  html += "<li><strong>POST /api/settime</strong> - Set date and time (JSON body required)</li>";
  html += "</ul>";
  html += "<h2>Current Time:</h2>";
  
  DateTime dt = getCurrentDateTime(DS3231_I2C_ADDRESS);
  char dateStr[11];
  char timeStr[9];
  sprintf(dateStr, "%04lu-%02lu-%02lu", (unsigned long)(dt.year + 2000), (unsigned long)dt.month, (unsigned long)dt.dayOfMonth);
  sprintf(timeStr, "%02lu:%02lu:%02lu", (unsigned long)dt.hour, (unsigned long)dt.minute, (unsigned long)dt.second);
  
  html += "<p>Date: " + String(dateStr) + "</p>";
  html += "<p>Time: " + String(timeStr) + "</p>";
  html += "<h2>Example Usage:</h2>";
  html += "<pre>curl http://" + WiFi.localIP().toString() + "/api/datetime</pre>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

/// @brief Handle GET /api/datetime - return current date and time as JSON
void handleDateTime() {
  DateTime dt = getCurrentDateTime(DS3231_I2C_ADDRESS);
  
  // Create JSON response
  JsonDocument doc;
  doc["year"] = dt.year + 2000;
  doc["month"] = dt.month;
  doc["day"] = dt.dayOfMonth;
  doc["hour"] = dt.hour;
  doc["minute"] = dt.minute;
  doc["second"] = dt.second;
  doc["dayOfWeek"] = dt.dayOfWeek;
  
  // Format as ISO 8601 datetime string
  char isoDateTime[25];
  sprintf(isoDateTime, "%04lu-%02lu-%02luT%02lu:%02lu:%02lZ", 
          (unsigned long)(dt.year + 2000), (unsigned long)dt.month, (unsigned long)dt.dayOfMonth,
          (unsigned long)dt.hour, (unsigned long)dt.minute, (unsigned long)dt.second);
  doc["iso8601"] = isoDateTime;
  
  // Format as readable strings
  char dateStr[11];
  char timeStr[9];
  sprintf(dateStr, "%04lu-%02lu-%02lu", (unsigned long)(dt.year + 2000), (unsigned long)dt.month, (unsigned long)dt.dayOfMonth);
  sprintf(timeStr, "%02lu:%02lu:%02lu", (unsigned long)dt.hour, (unsigned long)dt.minute, (unsigned long)dt.second);
  doc["date"] = dateStr;
  doc["time"] = timeStr;
  
  String response;
  serializeJson(doc, response);
  
  server.send(200, "application/json", response);
}

/// @brief Handle POST /api/settime - set date and time from JSON
void handleSetTime() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    JsonDocument doc;
    
    DeserializationError error = deserializeJson(doc, body);
    if (error) {
      server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }
    
    // Extract date and time components
    int year = doc["year"];
    int month = doc["month"];
    int day = doc["day"]; // Default to 1 if not provided
    int hour = doc["hour"];
    int minute = doc["minute"];
    int second = doc["second"];
    int dayOfWeek = doc["dayOfWeek"];
    
    // Validate ranges
    if (year < 2000 || year > 2099 || month < 1 || month > 12 || 
        day < 1 || day > 31 || hour < 0 || hour > 23 || 
        minute < 0 || minute > 59 || second < 0 || second > 59 ||
        dayOfWeek < 1 || dayOfWeek > 7) {
      server.send(400, "application/json", "{\"error\":\"Invalid date/time values\"}");
      return;
    }
    
    // Set the time on DS3231
    setTime(second, minute, hour, dayOfWeek, day, month, year - 2000);
    
    // Return success response
    JsonDocument response;
    response["success"] = true;
    response["message"] = "Time set successfully";
    response["year"] = year;
    response["month"] = month;
    response["day"] = day;
    response["hour"] = hour;
    response["minute"] = minute;
    response["second"] = second;
    response["dayOfWeek"] = dayOfWeek;
    
    String responseStr;
    serializeJson(response, responseStr);
    server.send(200, "application/json", responseStr);
    
  } else {
    server.send(400, "application/json", "{\"error\":\"No JSON body provided\"}");
  }
}
