#include <UniqueProblems/DynamicProgramming/String/LongestCommonSubstring.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Distance = LongestCommonSubstring::Index;
}  // namespace

TEST(LongestCommonSubstringTest, GetLongestCommonSubstringWorksOnExample1) {
    LongestCommonSubstring const queryForTest("MOVIE", "LOVE");

    EXPECT_EQ(2, queryForTest.getLongestCommonSubstringLengthUsingNaiveRecursion());
    EXPECT_EQ(2, queryForTest.getLongestCommonSubstringLengthUsingMemoizationDP());
    EXPECT_EQ(2, queryForTest.getLongestCommonSubstringLengthUsingIterativeDP());
    EXPECT_EQ(2, queryForTest.getLongestCommonSubstringLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ("OV", queryForTest.getLongestCommonSubstringUsingIterativeDPAndSpaceEfficient());
}

TEST(LongestCommonSubstringTest, GetLongestCommonSubstringWorksOnExample2) {
    LongestCommonSubstring const queryForTest("This is a statement", "This is not a statement");

    EXPECT_EQ(12, queryForTest.getLongestCommonSubstringLengthUsingNaiveRecursion());
    EXPECT_EQ(12, queryForTest.getLongestCommonSubstringLengthUsingMemoizationDP());
    EXPECT_EQ(12, queryForTest.getLongestCommonSubstringLengthUsingIterativeDP());
    EXPECT_EQ(12, queryForTest.getLongestCommonSubstringLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(" a statement", queryForTest.getLongestCommonSubstringUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
