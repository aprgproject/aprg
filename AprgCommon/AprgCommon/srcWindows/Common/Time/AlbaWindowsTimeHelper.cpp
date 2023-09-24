#include "AlbaWindowsTimeHelper.hpp"

namespace alba {

AlbaDateTime convertSystemTimeToAlbaDateTime(SYSTEMTIME const& systemTime) {
    return {systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond,
        systemTime.wMilliseconds * 1000};
}

}  // namespace alba
