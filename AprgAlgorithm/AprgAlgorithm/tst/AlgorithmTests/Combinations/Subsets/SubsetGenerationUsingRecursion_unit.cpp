#include <Algorithm/Combinatorics/Subsets/SubsetGenerationUsingRecursion.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using Objects = vector<int>;
using GenerationForTest = SubsetGenerationUsingRecursion<Objects>;
using Subsets = GenerationForTest::Subsets;
}  // namespace

TEST(SubsetGenerationUsingRecursionTest, GenerateOrderedSubsetsUsingDfsWorks) {
    Subsets const actualSubsets(GenerationForTest::generateOrderedSubsetsUsingDfs({1, 3, 5}));

    Subsets const expectedSubsets{{}, {1}, {1, 3}, {1, 3, 5}, {1, 5}, {3}, {3, 5}, {5}};
    EXPECT_EQ(expectedSubsets, actualSubsets);
}

TEST(SubsetGenerationUsingRecursionTest, GenerateSubsetsUsingOnlyRecursionWorks) {
    Subsets const actualSubsets(GenerationForTest::generateSubsetsUsingOnlyRecursion({1, 3, 5}));

    Subsets const expectedSubsets{{}, {5}, {3}, {3, 5}, {1}, {1, 5}, {1, 3}, {1, 3, 5}};
    EXPECT_EQ(expectedSubsets, actualSubsets);
}

}  // namespace alba::algorithm
