#include <UniqueProblems/DynamicProgramming/Grid/MinimumInitialPointsToReachDestination.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Grid = MinimumInitialPointsToReachDestination::Grid;
}  // namespace

TEST(MinimumInitialPointsToReachDestinationTest, GetMinimalInitialPointsUsingIterativeDPWorksOnExample1) {
    Grid const inputGrid(3, 3, {-2, -3, 3, -5, -10, 1, 10, 30, -5});
    MinimumInitialPointsToReachDestination const queryForTest(inputGrid);

    EXPECT_EQ(7, queryForTest.getMinimalInitialPointsUsingIterativeDP());
}

}  // namespace alba
