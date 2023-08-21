#include "AlbaDateTimeHelper.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <array>
#include <cmath>

using namespace alba::AlbaDateTimeConstants;
using namespace alba::mathHelper;
using namespace std;

namespace {
constexpr uint32_t HOURS_12 = 12U;
constexpr uint32_t YEARS_4 = 4U;
constexpr uint32_t YEARS_100 = 100U;
constexpr uint32_t YEARS_400 = 400U;
constexpr uint32_t DAYS_28_IN_MONTH = 28U;
constexpr uint32_t DAYS_29_IN_MONTH = 29U;
constexpr uint32_t DAYS_30_IN_MONTH = 30U;
constexpr uint32_t DAYS_31_IN_MONTH = 31U;
}  // namespace

namespace alba::dateTimeHelper {

std::string_view getMonthString(uint32_t const month) {
    switch (month) {
        case JANUARY:
            return "January";
        case FEBRUARY:
            return "February";
        case MARCH:
            return "March";
        case APRIL:
            return "April";
        case MAY:
            return "May";
        case JUNE:
            return "June";
        case JULY:
            return "July";
        case AUGUST:
            return "August";
        case SEPTEMBER:
            return "September";
        case OCTOBER:
            return "October";
        case NOVEMBER:
            return "November";
        case DECEMBER:
            return "December";
        default:
            break;
    }
    return {};
}

std::string_view getAmPmSuffix(uint32_t const hours) { return hours < HOURS_12 ? "AM" : "PM"; }

uint32_t convertTo12HourFormat(uint32_t const hours) {
    return hours > HOURS_12 ? hours - HOURS_12 : (hours == 0 ? HOURS_12 : hours);
}

bool isLeapYear(uint32_t const year) {
    return (year % YEARS_4 == 0 && year % YEARS_100 != 0) || (year % YEARS_400 == 0);
}

uint32_t getNumberOfDaysInAYear(uint32_t const year) {
    return isLeapYear(year) ? NUMBER_OF_DAYS_IN_LEAP_YEAR : NUMBER_OF_DAYS_IN_NON_LEAP_YEAR;
}

uint32_t getNumberOfDaysInAMonth(uint32_t const month, uint32_t const year) {
    uint32_t numberOfDays(0);
    if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) {
        numberOfDays = DAYS_30_IN_MONTH;
    } else if (month == FEBRUARY) {
        if (isLeapYear(year)) {
            numberOfDays = DAYS_29_IN_MONTH;
        } else {
            numberOfDays = DAYS_28_IN_MONTH;
        }
    } else if (month > 0) {
        numberOfDays = DAYS_31_IN_MONTH;
    }
    return numberOfDays;
}

uint32_t getNumberOfLeapYearsBeforeThisYear(uint32_t const year) {
    uint32_t numberOfLeapYears(0);
    if (year > 0) {
        auto beforeThisYear = year - 1;
        numberOfLeapYears =
            (beforeThisYear / YEARS_4) - (beforeThisYear / YEARS_100) + (beforeThisYear / YEARS_400) + 1;
    }
    return numberOfLeapYears;
}

uint32_t getNumberOfDaysInTheYearBeforeThisMonth(uint32_t const month, uint32_t const year) {
    uint32_t numberOfDays(0);
    switch (month) {
        case JANUARY:
            numberOfDays = 0;
            break;
        case FEBRUARY:
            numberOfDays = 31;  // NOLINT(readability-magic-numbers)
            break;
        case MARCH:
            numberOfDays = 59;  // NOLINT(readability-magic-numbers)
            break;
        case APRIL:
            numberOfDays = 90;  // NOLINT(readability-magic-numbers)
            break;
        case MAY:
            numberOfDays = 120;  // NOLINT(readability-magic-numbers)
            break;
        case JUNE:
            numberOfDays = 151;  // NOLINT(readability-magic-numbers)
            break;
        case JULY:
            numberOfDays = 181;  // NOLINT(readability-magic-numbers)
            break;
        case AUGUST:
            numberOfDays = 212;  // NOLINT(readability-magic-numbers)
            break;
        case SEPTEMBER:
            numberOfDays = 243;  // NOLINT(readability-magic-numbers)
            break;
        case OCTOBER:
            numberOfDays = 273;  // NOLINT(readability-magic-numbers)
            break;
        case NOVEMBER:
            numberOfDays = 304;  // NOLINT(readability-magic-numbers)
            break;
        case DECEMBER:
            numberOfDays = 334;  // NOLINT(readability-magic-numbers)
            break;
        default:
            numberOfDays = 0;
            break;
    }
    if (month > FEBRUARY && year > 0 && isLeapYear(year)) {
        numberOfDays++;
    }
    return numberOfDays;
}

uint32_t getMonthFromNumberOfDaysInANonLeapYear(uint32_t const numberOfDays) {
    constexpr array<uint32_t, 11> accumulatedDaysForEachMonth{31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    // NOLINTNEXTLINE(llvm-qualified-auto,readability-qualified-auto)
    auto const itMonth =
        lower_bound(accumulatedDaysForEachMonth.cbegin(), accumulatedDaysForEachMonth.cend(), numberOfDays);
    return static_cast<uint32_t>(JANUARY) + distance(accumulatedDaysForEachMonth.cbegin(), itMonth);
}

uint32_t getMonthFromNumberOfDaysInALeapYear(uint32_t const numberOfDays) {
    constexpr array<uint32_t, 11> accumulatedDaysForEachMonth{31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    // NOLINTNEXTLINE(llvm-qualified-auto,readability-qualified-auto)
    auto const itMonth =
        lower_bound(accumulatedDaysForEachMonth.cbegin(), accumulatedDaysForEachMonth.cend(), numberOfDays);
    return static_cast<uint32_t>(JANUARY) + distance(accumulatedDaysForEachMonth.cbegin(), itMonth);
}

uint32_t getMonthFromNumberOfDays(uint32_t const numberOfDays, uint32_t const year) {
    uint32_t result(0);
    if (numberOfDays > 0) {
        result = isLeapYear(year) ? getMonthFromNumberOfDaysInALeapYear(numberOfDays)
                                  : getMonthFromNumberOfDaysInANonLeapYear(numberOfDays);
    }
    return result;
}

uint32_t getNumberOfDaysBeforeThisYear(uint32_t const year) {
    return year * NUMBER_OF_DAYS_IN_NON_LEAP_YEAR + getNumberOfLeapYearsBeforeThisYear(year);
}

uint32_t getTotalDays(uint32_t const years, uint32_t const month, uint32_t const days) {
    return getNumberOfDaysBeforeThisYear(years) + getNumberOfDaysInTheYearBeforeThisMonth(month, years) + days;
}

uint32_t getTotalSeconds(uint32_t const hours, uint32_t const minutes, uint32_t const seconds) {
    return (hours * NUMBER_OF_SECONDS_IN_AN_HOUR) + (minutes * NUMBER_OF_SECONDS_IN_A_MINUTE) + seconds;
}

DayOfTheWeek getDayOfTheWeek(uint32_t const years, uint32_t const month, uint32_t const days) {
    // https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
    // Based from Sakamoto Methods
    // 1 <= month <= 12,  years > 1752 (in the U.K.)

    uint32_t yearValue = years;
    static constexpr array<uint32_t, 12> monthOffset = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    yearValue -= (month < 3) ? 1 : 0;
    return static_cast<DayOfTheWeek>(
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        (yearValue + yearValue / YEARS_4 - yearValue / YEARS_100 + yearValue / YEARS_400 + monthOffset[month - 1] +
         days) %
        7);
}

uint32_t getAndRemoveYearsFromNumberOfDays(uint32_t& remainingDays) {
    uint32_t years(remainingDays / NUMBER_OF_DAYS_IN_NON_LEAP_YEAR);
    int32_t remainingDaysTemp =
        static_cast<int32_t>(remainingDays) - static_cast<int32_t>(getNumberOfDaysBeforeThisYear(years));
    while (remainingDaysTemp <= 0 && years > 0) {
        years--;
        remainingDaysTemp += static_cast<int32_t>(getNumberOfDaysInAYear(years));
    }
    remainingDays = static_cast<uint32_t>(remainingDaysTemp);
    return years;
}

uint32_t getAndRemoveMonthsFromNumberOfDays(uint32_t& remainingDays, uint32_t const year) {
    uint32_t month(getMonthFromNumberOfDays(remainingDays, year));
    remainingDays -= getNumberOfDaysInTheYearBeforeThisMonth(month, year);
    return month;
}

uint32_t getAndRemoveHoursFromNumberOfSeconds(uint32_t& remainingSeconds) {
    uint32_t hours = remainingSeconds / NUMBER_OF_SECONDS_IN_AN_HOUR;
    remainingSeconds = remainingSeconds % NUMBER_OF_SECONDS_IN_AN_HOUR;
    return hours;
}

uint32_t getAndRemoveMinutesFromNumberOfSeconds(uint32_t& remainingSeconds) {
    uint32_t minutes = remainingSeconds / NUMBER_OF_SECONDS_IN_A_MINUTE;
    remainingSeconds = remainingSeconds % NUMBER_OF_SECONDS_IN_A_MINUTE;
    return minutes;
}

void reorganizeOverflowValues(uint32_t& totalDays, uint32_t& totalSeconds, uint32_t& totalMicroSeconds) {
    totalSeconds += totalMicroSeconds / NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    totalMicroSeconds = totalMicroSeconds % NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    totalDays += totalSeconds / NUMBER_OF_SECONDS_IN_A_DAY;
    totalSeconds = totalSeconds % NUMBER_OF_SECONDS_IN_A_DAY;
}

void reorganizeUnderflowValues(int32_t& totalDays, int32_t& totalSeconds, int32_t& totalMicroSeconds) {
    if (totalMicroSeconds < 0) {
        int32_t neededSeconds = (static_cast<int32_t>(totalMicroSeconds) * -1 +
                                 static_cast<int32_t>(NUMBER_OF_MICROSECONDS_IN_A_SECOND) - 1) /
                                static_cast<int32_t>(NUMBER_OF_MICROSECONDS_IN_A_SECOND);
        totalSeconds -= neededSeconds;
        totalMicroSeconds +=
            static_cast<int32_t>(neededSeconds) * static_cast<int32_t>(NUMBER_OF_MICROSECONDS_IN_A_SECOND);
    }
    if (totalSeconds < 0) {
        int32_t neededDays = (totalSeconds * -1 + static_cast<int32_t>(NUMBER_OF_SECONDS_IN_A_DAY) - 1) /
                             static_cast<int32_t>(NUMBER_OF_SECONDS_IN_A_DAY);
        totalDays -= neededDays;
        totalSeconds += neededDays * static_cast<int32_t>(NUMBER_OF_SECONDS_IN_A_DAY);
    }
}

}  // namespace alba::dateTimeHelper
