#include <UniqueProblems/DynamicProgramming/Subsequence/Increasing/MaximumSumIncreasingSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Values = MaximumSumIncreasingSubsequence::Values;
}  // namespace

TEST(MaximumSumIncreasingSubsequenceTest, GetLongestLengthWorksOnExample1) {
    MaximumSumIncreasingSubsequence const queryForTest({1, 101, 2, 3, 100, 4, 5});

    EXPECT_EQ(106, queryForTest.getMaximumSum());
}

TEST(MaximumSumIncreasingSubsequenceTest, GetSubsequenceWithMaximumSumWorksOnExample1) {
    MaximumSumIncreasingSubsequence const queryForTest({1, 101, 2, 3, 100, 4, 5});

    EXPECT_EQ((Values{1, 2, 3, 100}), queryForTest.getSubsequenceWithMaximumSum());
}

}  // namespace alba
