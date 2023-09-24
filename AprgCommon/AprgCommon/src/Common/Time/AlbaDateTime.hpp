#pragma once

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Time/AlbaDateTimeConstants.hpp>

#include <cstdint>
#include <ostream>

namespace alba {

using UInt32BitHelper = AlbaBitManipulation<uint32_t>;

class AlbaYearMonthDay {
public:
    constexpr AlbaYearMonthDay() : m_yearMonthDay{} {}

    constexpr AlbaYearMonthDay(uint16_t const years, uint8_t const month, uint8_t const days)
        : m_yearMonthDay(convertToYearMonthDayFormat(years, month, days)) {}

    bool operator<(AlbaYearMonthDay const& second) const;
    bool operator>(AlbaYearMonthDay const& second) const;
    bool operator==(AlbaYearMonthDay const& second) const;
    bool operator!=(AlbaYearMonthDay const& second) const;
    bool operator<=(AlbaYearMonthDay const& second) const;
    bool operator>=(AlbaYearMonthDay const& second) const;
    [[nodiscard]] AlbaDateTimeConstants::DayOfTheWeek getDayOfTheWeek() const;
    [[nodiscard]] uint32_t getYears() const;
    [[nodiscard]] uint32_t getMonths() const;
    [[nodiscard]] uint32_t getDays() const;
    [[nodiscard]] uint32_t getTotalDays() const;
    [[nodiscard]] bool isEmpty() const;
    void clear();
    void setTime(uint32_t const totalDays);
    void setTime(uint16_t const years, uint8_t const month, uint8_t const days);
    // rule of zero
    static AlbaYearMonthDay createFromTotalDays(uint32_t const totalDays);

private:
    static constexpr uint32_t convertToYearMonthDayFormat(
        uint16_t const years, uint8_t const month, uint8_t const days) {
        return UInt32BitHelper::shiftBytesToTheLeft<2>(years) | UInt32BitHelper::shiftBytesToTheLeft<1>(month) | days;
    }

    uint32_t m_yearMonthDay;
};

class AlbaHourMinuteSecond {
public:
    constexpr AlbaHourMinuteSecond() : m_hourMinuteSecond{} {}

    constexpr AlbaHourMinuteSecond(uint8_t const hours, uint8_t const minutes, uint8_t const seconds)
        : m_hourMinuteSecond(convertToHourMinuteSecondFormat(hours, minutes, seconds)) {}

    bool operator<(AlbaHourMinuteSecond const& second) const;
    bool operator>(AlbaHourMinuteSecond const& second) const;
    bool operator==(AlbaHourMinuteSecond const& second) const;
    bool operator!=(AlbaHourMinuteSecond const& second) const;
    bool operator<=(AlbaHourMinuteSecond const& second) const;
    bool operator>=(AlbaHourMinuteSecond const& second) const;
    [[nodiscard]] uint32_t getHours() const;
    [[nodiscard]] uint32_t getMinutes() const;
    [[nodiscard]] uint32_t getSeconds() const;
    [[nodiscard]] uint32_t getTotalSeconds() const;
    [[nodiscard]] bool isEmpty() const;
    void clear();
    void setTime(uint32_t const totalSeconds);
    void setTime(uint8_t const hours, uint8_t const minutes, uint8_t const seconds);
    // rule of zero
    static AlbaHourMinuteSecond createFromTotalSeconds(uint32_t const totalSeconds);

private:
    static constexpr uint32_t convertToHourMinuteSecondFormat(
        uint8_t const hours, uint8_t const minutes, uint8_t const seconds) {
        return UInt32BitHelper::shiftBytesToTheLeft<2>(hours) | UInt32BitHelper::shiftBytesToTheLeft<1>(minutes) |
               seconds;
    }

    uint32_t m_hourMinuteSecond;
};

class AlbaDateTime {
public:
    enum class PrintFormat {
        Standard,                      // YYYY-MM-DD HH:MM:SS.MMMMMM
        StandardWithSign,              // NN YYYY-MM-DD HH:MM:SS.MMMMMM
        Iso8601,                       // YYYY-MM-DDTHH:MM:SS.MMMMMM
        HumanReadable,                 // Month D, Y 12HH:MM:SS.MMMMMM AM/PM
        RelativeTime,                  // TD days, H hours, M minutes, S seconds, M microseconds ago/from now
        TimeWithColon,                 // HH:MM:SS
        TimeWithColonWithMicroSeconds  // HH:MM:SS.MMMMMM
    };

    template <PrintFormat printFormat>
    struct PrintObject {
        explicit PrintObject(AlbaDateTime const& dataTimeToPrint) : savedDateTime(dataTimeToPrint) {}
        AlbaDateTime const& savedDateTime;
    };

    constexpr AlbaDateTime() : m_sign(1), m_microseconds{} {}

    constexpr AlbaDateTime(
        AlbaYearMonthDay const& yearMonthDay, AlbaHourMinuteSecond const& hourMinuteSecond, uint32_t const microseconds)
        : m_sign(1), m_yearMonthDay(yearMonthDay), m_hourMinuteSecond(hourMinuteSecond), m_microseconds(microseconds) {}

    constexpr AlbaDateTime(
        uint16_t const years, uint8_t const months, uint8_t const days, uint8_t const hours, uint8_t const minutes,
        uint8_t const seconds, uint32_t const microseconds)
        : m_sign(1),
          m_yearMonthDay(years, months, days),
          m_hourMinuteSecond(hours, minutes, seconds),
          m_microseconds(microseconds) {}

    AlbaDateTime operator+(AlbaDateTime const& secondDateTime) const;
    AlbaDateTime operator-(AlbaDateTime const& secondDateTime) const;
    bool operator<(AlbaDateTime const& secondDateTime) const;
    bool operator>(AlbaDateTime const& secondDateTime) const;
    bool operator==(AlbaDateTime const& secondDateTime) const;
    bool operator!=(AlbaDateTime const& secondDateTime) const;
    [[nodiscard]] AlbaHourMinuteSecond const& getHourMinutesSecond() const;
    [[nodiscard]] AlbaYearMonthDay const& getYearMonthDay() const;
    [[nodiscard]] uint32_t getYears() const;
    [[nodiscard]] uint32_t getMonths() const;
    [[nodiscard]] uint32_t getDays() const;
    [[nodiscard]] uint32_t getHours() const;
    [[nodiscard]] uint32_t getMinutes() const;
    [[nodiscard]] uint32_t getSeconds() const;
    [[nodiscard]] uint32_t getMicroSeconds() const;
    [[nodiscard]] bool isEmpty() const;
    void clear();
    void negate();

    void setTime(
        uint16_t const years, uint8_t const months, uint8_t const days, uint8_t const hours, uint8_t const minutes,
        uint8_t const seconds, uint32_t const microseconds);

    void reorganizeValues();  // NOTE: AlbaDateTime class needs to be manually reorganized (if needed)
    AlbaHourMinuteSecond& getHourMinutesSecondReference();
    AlbaYearMonthDay& getYearMonthDayReference();
    uint32_t& getMicroSecondsReference();

    // rule of zero
    static AlbaDateTime createFromTotalDaysAndSecondsAndMicroSeconds(
        uint32_t const totalDays, uint32_t const totalSeconds, uint32_t const totalMicroseconds);

    // constructor is constexpr.
    template <PrintFormat printFormat>
    [[nodiscard]] PrintObject<printFormat> getPrintObject() const {
        return PrintObject<printFormat>(*this);
    }

private:
    static AlbaDateTime addDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime);

    static AlbaDateTime subtractDateTimeMagnitude(
        AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime);

    static AlbaDateTime executeAddOrSubtract(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime);
    static bool isLessThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime);
    static bool isGreaterThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime);
    static bool isEqualInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime);

    template <PrintFormat printFormat>
    friend std::ostream& operator<<(std::ostream& out, AlbaDateTime::PrintObject<printFormat> const&);

    friend std::ostream& operator<<(std::ostream& out, AlbaDateTime const& dateTime);
    int32_t m_sign;  // sign is the hottest parameter (based from my evaluation)
    AlbaYearMonthDay m_yearMonthDay;
    AlbaHourMinuteSecond m_hourMinuteSecond;
    uint32_t m_microseconds;
};

}  // namespace alba
