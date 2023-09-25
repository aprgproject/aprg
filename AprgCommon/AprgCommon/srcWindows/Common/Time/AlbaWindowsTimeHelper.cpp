#include "AlbaWindowsTimeHelper.hpp"

namespace alba {

AlbaDateTime convertSystemTimeToAlbaDateTime(SYSTEMTIME const& systemTime) {
    return {
        static_cast<uint16_t>(systemTime.wYear),
        static_cast<uint8_t>(systemTime.wMonth),
        static_cast<uint8_t>(systemTime.wDay),
        static_cast<uint8_t>(systemTime.wHour),
        static_cast<uint8_t>(systemTime.wMinute),
        static_cast<uint8_t>(systemTime.wSecond),
        static_cast<uint32_t>(systemTime.wMilliseconds * 1000)};
}

}  // namespace alba
