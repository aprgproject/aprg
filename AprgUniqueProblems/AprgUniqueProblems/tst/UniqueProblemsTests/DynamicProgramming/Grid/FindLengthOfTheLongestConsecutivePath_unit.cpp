#include <UniqueProblems/DynamicProgramming/Grid/FindLengthOfTheLongestConsecutivePath.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Grid = FindLengthOfTheLongestConsecutivePath::ValueGrid;
}  // namespace

TEST(FindLengthOfTheLongestConsecutivePathTest, GetLongestLengthWorksOnExample1) {
    Grid const inputGrid(3, 3, {'a', 'c', 'd', 'h', 'b', 'e', 'i', 'g', 'f'});
    FindLengthOfTheLongestConsecutivePath const queryForTest(inputGrid);

    EXPECT_EQ(9, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(5, queryForTest.getLongestLengthStartingAtUsingNaiveRecursion(2, 1));
    EXPECT_EQ(9, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(5, queryForTest.getLongestLengthStartingAtUsingMemoizationDP(2, 1));
}

TEST(FindLengthOfTheLongestConsecutivePathTest, GetLongestLengthWorksOnExample2) {
    Grid const inputGrid(3, 3, {'b', 'e', 'f', 'h', 'd', 'a', 'i', 'c', 'a'});
    FindLengthOfTheLongestConsecutivePath const queryForTest(inputGrid);

    EXPECT_EQ(4, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(1, queryForTest.getLongestLengthStartingAtUsingNaiveRecursion(0, 0));
    EXPECT_EQ(4, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(1, queryForTest.getLongestLengthStartingAtUsingMemoizationDP(0, 0));
}

}  // namespace alba
