#include <UniqueProblems/DynamicProgramming/String/WordWrapProblemWithLineWidth.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(WordWrapProblemWithLineWidthTest, GetWordWrapProblemWithLineWidthWorksOnExample1) {
    WordWrapProblemWithLineWidth const queryForTest(
        15, {"Geeks", "for", "Geeks", "presents", "word", "wrap", "problem"});

    EXPECT_EQ(35, queryForTest.getOptimizedCostUsingNaiveRecursion());
    EXPECT_EQ(35, queryForTest.getOptimizedCostByTryingAllLengths());
    EXPECT_EQ(35, queryForTest.getOptimizedCostByCheckingFirstAndLastWords());
}

TEST(WordWrapProblemWithLineWidthTest, GetWordWrapProblemWithLineWidthWorksOnExample2) {
    WordWrapProblemWithLineWidth const queryForTest(6, {"aaa", "bb", "cc", "ddddd"});

    EXPECT_EQ(29, queryForTest.getOptimizedCostUsingNaiveRecursion());
    EXPECT_EQ(29, queryForTest.getOptimizedCostByTryingAllLengths());
    EXPECT_EQ(29, queryForTest.getOptimizedCostByCheckingFirstAndLastWords());
}

}  // namespace alba
