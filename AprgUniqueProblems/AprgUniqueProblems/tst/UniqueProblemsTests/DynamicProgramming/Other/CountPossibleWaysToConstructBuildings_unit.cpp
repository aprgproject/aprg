#include <UniqueProblems/DynamicProgramming/Other/CountPossibleWaysToConstructBuildings.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOZeroSections) {
    CountPossibleWaysToConstructBuildings const queryForTest(0);

    EXPECT_EQ(1, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(1, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(1, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample1) {
    CountPossibleWaysToConstructBuildings const queryForTest(1);

    EXPECT_EQ(4, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(4, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(4, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample2) {
    CountPossibleWaysToConstructBuildings const queryForTest(2);

    EXPECT_EQ(9, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(9, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(9, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample3) {
    CountPossibleWaysToConstructBuildings const queryForTest(3);

    EXPECT_EQ(25, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(25, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(25, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample4) {
    CountPossibleWaysToConstructBuildings const queryForTest(4);

    EXPECT_EQ(64, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(64, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(64, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample5) {
    CountPossibleWaysToConstructBuildings const queryForTest(5);

    EXPECT_EQ(169, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(169, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(169, queryForTest.getNumberOfWaysUsingCombinations());
}

}  // namespace alba
