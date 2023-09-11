#include <Algorithm/Combinatorics/Combinations/CombinationsWithSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using Values = vector<int>;
using GenerationForTest = CombinationsWithSum<Values>;
using Combinations = GenerationForTest::Combinations;
}  // namespace

TEST(CombinationsWithSumTest, GetCombinationsWithSumUsingRecursionWorks) {
    Values const inputValues{1, 2, 3, 4};
    GenerationForTest generation(inputValues);

    Combinations const actualCombinations(generation.getCombinationsWithSumUsingRecursion(4));

    Combinations const expectedCombinations{{1, 1, 1, 1}, {1, 1, 2}, {1, 3}, {2, 2}, {4}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

TEST(CombinationsWithSumTest, GetCombinationsWithSumUsingLoopsWorks) {
    Values const inputValues{1, 2, 3, 4};
    GenerationForTest generation(inputValues);

    Combinations const actualCombinations(generation.getCombinationsWithSumUsingLoops(4));

    Combinations const expectedCombinations{{1, 1, 1, 1}, {1, 1, 2}, {1, 3}, {2, 2}, {4}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

}  // namespace alba::algorithm
