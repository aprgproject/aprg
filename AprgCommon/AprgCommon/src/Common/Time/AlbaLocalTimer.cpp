#include "AlbaLocalTimer.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimeHelper.hpp>

using namespace alba::stringHelper;
using namespace std::chrono;
using namespace std;

namespace alba {

AlbaLocalTimer::AlbaLocalTimer() : m_time1(getSteadyTimeNow()), m_time2(m_time1) {}

AlbaDateTime AlbaLocalTimer::getDifferenceAsAlbaDateTime() const {
    AlbaDateTime result(0, 0, 0, 0, 0, 0, getElapsedTimeInMicroseconds());  // might overflow
    result.reorganizeValues();
    return result;
}

size_t AlbaLocalTimer::getElapsedTimeInNanoseconds() const {
    return duration_cast<std::chrono::nanoseconds>(m_time2 - m_time1).count();
}

size_t AlbaLocalTimer::getElapsedTimeInMicroseconds() const {
    return duration_cast<std::chrono::microseconds>(m_time2 - m_time1).count();
}

size_t AlbaLocalTimer::getElapsedTimeInMilliseconds() const {
    return duration_cast<std::chrono::milliseconds>(m_time2 - m_time1).count();
}

size_t AlbaLocalTimer::getElapsedTimeInSeconds() const {
    return duration_cast<std::chrono::seconds>(m_time2 - m_time1).count();
}

size_t AlbaLocalTimer::getElapsedTimeInMinutes() const {
    return duration_cast<std::chrono::minutes>(m_time2 - m_time1).count();
}

size_t AlbaLocalTimer::getElapsedTimeInHours() const {
    return duration_cast<std::chrono::hours>(m_time2 - m_time1).count();
}

void AlbaLocalTimer::resetTimer() {
    m_time1 = getSteadyTimeNow();
    m_time2 = m_time1;
}

void AlbaLocalTimer::stopTimer() { m_time2 = getSteadyTimeNow(); }

}  // namespace alba
