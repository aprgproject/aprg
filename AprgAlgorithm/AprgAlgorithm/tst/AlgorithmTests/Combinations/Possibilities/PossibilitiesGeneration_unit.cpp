#include <Algorithm/Combinatorics/Possibilities/PossibilitiesGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using Objects = vector<int>;
using GenerationForTest = PossibilitiesGeneration<Objects>;
using Possibilities = GenerationForTest::Possibilities;
}  // namespace

TEST(PossibilitiesGenerationTest, GeneratePossibilitiesUsingRecursionWorks) {
    Possibilities const actualPossibilities(GenerationForTest::generatePossibilitiesUsingRecursion({1, 3, 5}));

    Possibilities const expectedPossibilities{
        {1, 1, 1}, {1, 1, 3}, {1, 1, 5}, {1, 3, 1}, {1, 3, 3}, {1, 3, 5}, {1, 5, 1}, {1, 5, 3}, {1, 5, 5},
        {3, 1, 1}, {3, 1, 3}, {3, 1, 5}, {3, 3, 1}, {3, 3, 3}, {3, 3, 5}, {3, 5, 1}, {3, 5, 3}, {3, 5, 5},
        {5, 1, 1}, {5, 1, 3}, {5, 1, 5}, {5, 3, 1}, {5, 3, 3}, {5, 3, 5}, {5, 5, 1}, {5, 5, 3}, {5, 5, 5}};
    EXPECT_EQ(expectedPossibilities, actualPossibilities);
}

TEST(PossibilitiesGenerationTest, GeneratePossibilitiesWithLengthWorks) {
    Possibilities const actualPossibilities(GenerationForTest::generatePossibilitiesWithLength({1, 3, 5}, 2));

    Possibilities const expectedPossibilities{{1, 1}, {1, 3}, {1, 5}, {3, 1}, {3, 3}, {3, 5}, {5, 1}, {5, 3}, {5, 5}};
    EXPECT_EQ(expectedPossibilities, actualPossibilities);
}

}  // namespace alba::algorithm
