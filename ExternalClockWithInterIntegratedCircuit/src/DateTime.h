#include <Arduino.h>

/// @brief This class represents a date and time object.
class DateTime
{
  public:
    /// @brief The constructor of the DateTime class.
    /// @param second The seconds of the current time.
    /// @param minute The minutes of the current time.
    /// @param hour The hours of the current time.
    /// @param dayOfWeek The day of the current week.
    /// @param dayOfMonth The day of the current month.
    /// @param month The month of the current year.
    /// @param year The current year.
    DateTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t dayOfWeek, uint8_t dayOfMonth, uint8_t month, uint16_t year) {
      this->second = second;
      this->minute = minute;
      this->hour = hour;
      this->dayOfWeek = dayOfWeek;
      this->dayOfMonth = dayOfMonth;
      this->month = month;
      this->year = year;
    }
    /// @brief The seconds of the current time.
    uint8_t second;
    /// @brief The minutes of the current time.
    uint8_t minute;
    /// @brief The hours of the current time.
    uint8_t hour;
    /// @brief The day of the current week.
    uint8_t dayOfWeek;
    /// @brief The day of the current month.
    uint8_t dayOfMonth;
    /// @brief The month of the current year.
    uint8_t month;
    /// @brief The current year.
    uint16_t year;
};
