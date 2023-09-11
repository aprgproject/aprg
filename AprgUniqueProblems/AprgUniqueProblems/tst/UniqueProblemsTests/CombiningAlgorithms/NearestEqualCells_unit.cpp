#include <UniqueProblems/CombiningAlgorithms/NearestEqualCells.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using ValueMatrix = NearestEqualCells::ValueMatrix;
using CoordinatePair = NearestEqualCells::CoordinatePair;
}  // namespace

TEST(NearestEqualCellsTest, GetNearestEqualPairWorks) {
    ValueMatrix const valueMatrix(4, 4, {1, 6, 2, 1, 3, 5, 7, 5, 2, 4, 1, 6, 1, 3, 2, 4});
    NearestEqualCells const nearestEqualCells(valueMatrix);

    CoordinatePair const expectedCoordinatePair{{2, 0}, {2, 3}};
    EXPECT_EQ(expectedCoordinatePair, nearestEqualCells.getNearestEqualPair(2));
}

TEST(NearestEqualCellsTest, GetNearestEqualPairByCheckingAllPairsWorks) {
    ValueMatrix const valueMatrix(4, 4, {1, 6, 2, 1, 3, 5, 7, 5, 2, 4, 1, 6, 1, 3, 2, 4});
    NearestEqualCells const nearestEqualCells(valueMatrix);

    CoordinatePair const expectedCoordinatePair{{2, 0}, {2, 3}};
    EXPECT_EQ(expectedCoordinatePair, nearestEqualCells.getNearestEqualPairByCheckingAllPairs(2));
}

TEST(NearestEqualCellsTest, GetNearestEqualPairUsingBfsWorks) {
    ValueMatrix const valueMatrix(4, 4, {1, 6, 2, 1, 3, 5, 7, 5, 2, 4, 1, 6, 1, 3, 2, 4});
    NearestEqualCells const nearestEqualCells(valueMatrix);

    CoordinatePair const expectedCoordinatePair{{0, 2}, {2, 3}};
    EXPECT_EQ(expectedCoordinatePair, nearestEqualCells.getNearestEqualPairUsingBfs(2));
}

}  // namespace alba
