#pragma once

#include <Common/Time/AlbaDateTime.hpp>
#include <Common/Time/AlbaDateTimeConstants.hpp>
#include <Common/Time/AlbaLibraryTimeTypes.hpp>

#include <chrono>

namespace alba {

using LibrarySteadyTime = std::chrono::time_point<std::chrono::steady_clock>;
void sleepFor(size_t const milliSeconds);
void sleepUntil(AlbaDateTime const& awakeTime);
AlbaDateTime convertSystemTimeToAlbaDateTime(LibrarySystemTime const& inputTime);
AlbaDateTime convertFileTimeToAlbaDateTime(LibraryFileTime const& inputTime);
AlbaDateTime getCurrentDateTime();
LibrarySteadyTime getSteadyTimeNow();
LibrarySystemTime getSystemTimeNow();

LibrarySystemTime convertTimeInformationToSystemTime(
    std::tm& timeInformation, std::chrono::nanoseconds const& nanosecondsDuration);

LibrarySystemTime convertAlbaDateTimeToSystemTime(AlbaDateTime const& inputTime);

template <typename LibraryTime>
AlbaDateTime convertSinceEpochTimeToAlbaDateTime(LibraryTime const& inputTime) {
    auto microsecondsSinceEpoch =
        std::chrono::time_point_cast<std::chrono::microseconds>(inputTime).time_since_epoch().count();
    auto remainingMicroSeconds =
        static_cast<uint32_t>(microsecondsSinceEpoch % AlbaDateTimeConstants::NUMBER_OF_MICROSECONDS_IN_A_SECOND);
    auto remainingSeconds =
        static_cast<uint32_t>(microsecondsSinceEpoch / AlbaDateTimeConstants::NUMBER_OF_MICROSECONDS_IN_A_SECOND);
    auto remainingDays = static_cast<uint32_t>(remainingSeconds / AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_DAY);
    remainingSeconds = remainingSeconds % AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_DAY;

    return AlbaDateTime::createFromTotalDaysAndSecondsAndMicroSeconds(
        remainingDays, remainingSeconds, remainingMicroSeconds);

    // NOTE: To convert this to local time, you have to:
    // -> Add offset for epoch (Jan 1, 1970 00:00:00)
    // -> Add offset for GMT timezone (so its better to make localtime figure this out)
}

}  // namespace alba
