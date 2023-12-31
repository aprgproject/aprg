#include <UniqueProblems/SpecialProblems/JosephusProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

using Values = JosephusProblem::Values;

TEST(JosephusProblemTest, GetJosephusPermutationUsingIntervalTreeWorks) {
    JosephusProblem const josephusProblem;

    EXPECT_EQ((Values{3, 6, 2, 7, 5, 1, 4}), josephusProblem.getJosephusPermutationUsingIntervalTree(7, 3));
    EXPECT_EQ((Values{5, 10, 6, 2, 9, 8, 1, 4, 7, 3}), josephusProblem.getJosephusPermutationUsingIntervalTree(10, 5));
}

}  // namespace alba
