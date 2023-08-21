
#include "AlbaLinuxTimeHelper.hpp"

#include <Common/Time/AlbaDateTimeConstants.hpp>

#include <unistd.h>

namespace alba {

AlbaDateTime convertSystemTimeToAlbaDateTime(struct timespec const& timeSpec) {
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    struct tm timeInformation = *localtime(&(timeSpec.tv_sec));
    return {
        static_cast<uint16_t>(timeInformation.tm_year),
        static_cast<uint8_t>(timeInformation.tm_mon + 1),
        static_cast<uint8_t>(timeInformation.tm_mday),
        static_cast<uint8_t>(timeInformation.tm_hour),
        static_cast<uint8_t>(timeInformation.tm_min),
        static_cast<uint8_t>(timeInformation.tm_sec),
        static_cast<uint32_t>(
            static_cast<double>(timeSpec.tv_nsec) / AlbaDateTimeConstants::NUMBER_OF_NANOSECONDS_IN_A_MICROSECOND)};
}

}  // namespace alba
