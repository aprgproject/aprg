#include <UniqueProblems/DynamicProgramming/Subsequence/Increasing/MaximumLengthChainOfPairs.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Values = MaximumLengthChainOfPairs::Pairs;
}  // namespace

TEST(MaximumLengthChainOfPairsTest, GetLongestLengthWorksOnExample1) {
    MaximumLengthChainOfPairs const queryForTest({{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}});

    EXPECT_EQ(3, queryForTest.getLongestLength());
}

TEST(MaximumLengthChainOfPairsTest, GetLongestSubsequenceWorksOnExample1) {
    MaximumLengthChainOfPairs const queryForTest({{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}});

    EXPECT_EQ((Values{{5, 24}, {27, 40}, {50, 90}}), queryForTest.getLongestSubsequence());
}

}  // namespace alba
