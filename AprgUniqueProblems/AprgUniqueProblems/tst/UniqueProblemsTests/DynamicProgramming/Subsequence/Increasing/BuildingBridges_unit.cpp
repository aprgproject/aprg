#include <UniqueProblems/DynamicProgramming/Subsequence/Increasing/BuildingBridges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Bridges = BuildingBridges::Bridges;
}  // namespace

TEST(BuildingBridgesTest, GetLongestSubsequenceWorksOnExample1) {
    BuildingBridges const queryForTest({{6, 2}, {4, 3}, {2, 6}, {1, 5}});

    EXPECT_EQ((Bridges{{2, 6}, {1, 5}}), queryForTest.getPossibleBridges());
}

TEST(BuildingBridgesTest, GetLongestSubsequenceWorksOnExample2) {
    BuildingBridges const queryForTest({{8, 1}, {1, 2}, {4, 3}, {3, 4}, {5, 5}, {2, 6}, {6, 7}, {7, 8}});

    EXPECT_EQ((Bridges{{7, 8}, {6, 7}, {5, 5}, {4, 3}, {1, 2}}), queryForTest.getPossibleBridges());
}

TEST(BuildingBridgesTest, GetLongestLengthWorksOnExample1) {
    BuildingBridges const queryForTest({{6, 2}, {4, 3}, {2, 6}, {1, 5}});

    EXPECT_EQ(2, queryForTest.getNumberOfPossibleBridges());
}

TEST(BuildingBridgesTest, GetLongestLengthWorksOnExample2) {
    BuildingBridges const queryForTest({{8, 1}, {1, 2}, {4, 3}, {3, 4}, {5, 5}, {2, 6}, {6, 7}, {7, 8}});

    EXPECT_EQ(5, queryForTest.getNumberOfPossibleBridges());
}

}  // namespace alba
