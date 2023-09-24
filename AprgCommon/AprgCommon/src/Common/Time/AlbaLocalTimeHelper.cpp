#include "AlbaLocalTimeHelper.hpp"

#include <chrono>
#include <thread>

using namespace alba::AlbaDateTimeConstants;
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

namespace {
constexpr int YEAR_OFFSET = 1900;
constexpr int MONTH_OFFSET = 1;
}  // namespace

namespace alba {

// Walter E Brown technique
template <typename, typename = void>
struct hasToSys : std::false_type {};

template <typename Clock>
struct hasToSys<Clock, std::void_t<decltype(Clock::to_sys(std::declval<LibraryFileTime>()))>> : std::true_type {};

template <typename, typename = void>
struct hasToUtc : std::false_type {};

template <typename Clock>
struct hasToUtc<Clock, std::void_t<decltype(Clock::to_utc(std::declval<LibraryFileTime>()))>> : std::true_type {};

template <typename TimePoint, typename FileClock, typename UtcClock>
std::enable_if_t<hasToSys<FileClock>::value, AlbaDateTime> convertFileTimeToAlbaDateTimeInternal(
    TimePoint const& inputTime) {
    return convertSystemTimeToAlbaDateTime(FileClock::to_sys(inputTime));
}

template <typename TimePoint, typename FileClock, typename UtcClock>
std::enable_if_t<!hasToSys<FileClock>::value && hasToUtc<FileClock>::value, AlbaDateTime>
convertFileTimeToAlbaDateTimeInternal(TimePoint const& inputTime) {
    return convertSystemTimeToAlbaDateTime(UtcClock::to_sys(FileClock::to_utc(inputTime)));
}

void sleepFor(size_t const milliSeconds) { sleep_for(chrono::milliseconds(milliSeconds)); }
void sleepUntil(AlbaDateTime const& awakeTime) { sleep_until(convertAlbaDateTimeToSystemTime(awakeTime)); }

AlbaDateTime convertSystemTimeToAlbaDateTime(LibrarySystemTime const& inputTime) {
    // This is a valid C++20 code, but you can get the correct hour from the timezone
    // year_month_day const ymd{floor<days>(inputTime)};
    // duration durationSinceEpoch = inputTime.time_since_epoch();
    // auto seconds = duration_cast<chrono::seconds>(durationSinceEpoch);
    // durationSinceEpoch -= seconds;
    // auto hours = duration_cast<chrono::hours>(seconds);
    // seconds -= duration_cast<chrono::seconds>(hours);
    // auto minutes = duration_cast<chrono::minutes>(seconds);
    // seconds -= duration_cast<chrono::seconds>(minutes);
    // auto microseconds = duration_cast<chrono::microseconds>(durationSinceEpoch);
    // int year = static_cast<int>(ymd.year());
    // unsigned month = static_cast<unsigned>(ymd.month());
    // unsigned day = static_cast<unsigned>(ymd.day());
    time_t const currentTimeT = system_clock::to_time_t(inputTime);
    tm localTimeValues{};
#ifdef OS_WINDOWS
    auto errorValue = localtime_s(&localTimeValues, &currentTimeT);  // Windows version
    if (errorValue > 0) {
        localTimeValues = {};
    }
#else
    localtime_r(&currentTimeT, &localTimeValues);  // POSIX version
#endif
    auto microseconds = time_point_cast<chrono::microseconds>(inputTime).time_since_epoch().count() %
                        NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    AlbaDateTime result(
        localTimeValues.tm_year + YEAR_OFFSET, localTimeValues.tm_mon + MONTH_OFFSET, localTimeValues.tm_mday,
        localTimeValues.tm_hour, localTimeValues.tm_min, localTimeValues.tm_sec, microseconds);
    result.reorganizeValues();
    return result;
}

AlbaDateTime convertFileTimeToAlbaDateTime(LibraryFileTime const& inputTime) {
    return convertFileTimeToAlbaDateTimeInternal<LibraryFileTime, file_clock, utc_clock>(inputTime);
}

AlbaDateTime getCurrentDateTime() { return convertSystemTimeToAlbaDateTime(getSystemTimeNow()); }
LibrarySteadyTime getSteadyTimeNow() { return steady_clock::now(); }
LibrarySystemTime getSystemTimeNow() { return system_clock::now(); }

LibrarySystemTime convertTimeInformationToSystemTime(
    tm& timeInformation, chrono::nanoseconds const& nanosecondsDuration) {
    time_t const timeUntilSeconds = mktime(&timeInformation);
    if (timeUntilSeconds != -1) {
        // mktime returns -1 if cannot be represented
        return system_clock::from_time_t(timeUntilSeconds) + duration_cast<system_clock::duration>(nanosecondsDuration);
    }
    return {};
}

LibrarySystemTime convertAlbaDateTimeToSystemTime(AlbaDateTime const& inputTime) {
    tm timeInformation{};  // dont brace initialize values
    timeInformation.tm_sec = static_cast<int>(inputTime.getSeconds());
    timeInformation.tm_min = static_cast<int>(inputTime.getMinutes());
    timeInformation.tm_hour = static_cast<int>(inputTime.getHours());
    timeInformation.tm_mday = static_cast<int>(inputTime.getDays());
    timeInformation.tm_mon = static_cast<int>(inputTime.getMonths()) - MONTH_OFFSET;
    timeInformation.tm_year = static_cast<int>(inputTime.getYears()) - YEAR_OFFSET;

    return convertTimeInformationToSystemTime(
        timeInformation, nanoseconds(inputTime.getMicroSeconds() * NUMBER_OF_NANOSECONDS_IN_A_MICROSECOND));
}

}  // namespace alba
