#include "DateTimeUtilities.hpp"

#include <gtest/gtest.h>

using namespace std;

namespace alba {

bool isDifferenceAcceptable(AlbaDateTime const& first, AlbaDateTime const& second) {
    AlbaDateTime const difference(second - first);
    AlbaDateTime const minDifference(0, 0, 0, 0, 0, 0, 1);  // 1 microsecond
    AlbaDateTime const maxDifference(0, 0, 0, 0, 1, 0, 0);  // 1 minute
    EXPECT_LT(minDifference, difference);
    EXPECT_LT(difference, maxDifference);
    return minDifference < difference && difference < maxDifference;
}

}  // namespace alba
