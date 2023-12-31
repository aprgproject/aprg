#include <UniqueProblems/SearchProblems/FindSmallestValueWithTrue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValueForTest = int;
using SearchForTest = FindSmallestValueWithTrue<ValueForTest>;
}  // namespace

TEST(FindSmallestValueWithTrueTest, GetNearestValueWorksWhenItsAlwaysFalse) {
    SearchForTest const binarySearch([](ValueForTest const) { return false; });

    EXPECT_EQ(0, binarySearch.getSmallestValueWithTrue(45, 500));
}

TEST(FindSmallestValueWithTrueTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    SearchForTest const binarySearch([](ValueForTest const value) { return value >= 111; });

    EXPECT_EQ(111, binarySearch.getSmallestValueWithTrue(45, 500));
}

}  // namespace alba::algorithm
