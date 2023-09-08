#pragma once

#include <Common/Time/AlbaDateTime.hpp>
#include <Common/Time/AlbaLibraryTimeTypes.hpp>

#include <chrono>
#include <string>

namespace alba {

class AlbaLocalTimer {
public:
    AlbaLocalTimer();
    [[nodiscard]] size_t getElapsedTimeInNanoseconds() const;
    [[nodiscard]] size_t getElapsedTimeInMicroseconds() const;
    [[nodiscard]] size_t getElapsedTimeInMilliseconds() const;
    [[nodiscard]] size_t getElapsedTimeInSeconds() const;
    [[nodiscard]] size_t getElapsedTimeInMinutes() const;
    [[nodiscard]] size_t getElapsedTimeInHours() const;
    [[nodiscard]] AlbaDateTime getDifferenceAsAlbaDateTime() const;
    void resetTimer();
    void stopTimer();

private:
    LibrarySteadyTime m_time1;
    LibrarySteadyTime m_time2;
};

}  // namespace alba
