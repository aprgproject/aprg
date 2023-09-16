#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <ctime>

namespace alba {
AlbaDateTime convertSystemTimeToAlbaDateTime(timespec const& timeSpec);
}  // namespace alba
