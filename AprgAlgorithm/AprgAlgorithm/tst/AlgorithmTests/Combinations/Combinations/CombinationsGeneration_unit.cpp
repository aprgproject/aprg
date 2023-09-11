#include <Algorithm/Combinatorics/Combinations/CombinationsGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using Objects = vector<int>;
using GenerationForTest = CombinationsGeneration<Objects>;
using Combinations = GenerationForTest::Combinations;
}  // namespace

TEST(CombinationsGenerationTest, GenerateCombinationsWithLengthWorksWhenCombinationLengthIsLessThanSize) {
    Combinations const actualCombinations(GenerationForTest::generateCombinationsWithLength({1, 3, 5}, 2));

    Combinations const expectedCombinations{{1, 3}, {1, 5}, {3, 5}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

TEST(CombinationsGenerationTest, GenerateCombinationsWithLengthWorksWhenCombinationLengthIsEqualToSize) {
    Combinations const actualCombinations(GenerationForTest::generateCombinationsWithLength({1, 3, 5}, 3));

    Combinations const expectedCombinations{{1, 3, 5}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

}  // namespace alba::algorithm
