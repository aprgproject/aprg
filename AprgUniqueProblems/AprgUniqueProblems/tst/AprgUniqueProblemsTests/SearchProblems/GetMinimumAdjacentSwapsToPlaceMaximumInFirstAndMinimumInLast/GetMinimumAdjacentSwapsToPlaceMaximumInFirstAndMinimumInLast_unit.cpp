#include <AprgUniqueProblems/SearchProblems/GetMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLast/GetMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLast.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using QueryForTest = GetMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLast<ValuesForTest>;
}  // namespace
TEST(GetMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLastTest, WorksOnEmpty) {
    ValuesForTest valuesForTest;
    QueryForTest query;

    EXPECT_EQ(0, query.getMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLast(valuesForTest));
}

TEST(GetMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLastTest, WorksOnOneValue) {
    ValuesForTest valuesForTest{3};
    QueryForTest query;

    EXPECT_EQ(0, query.getMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLast(valuesForTest));
}

TEST(GetMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLastTest, WorksOnExample1) {
    ValuesForTest valuesForTest{3, 1, 5, 3, 5, 5, 2};
    QueryForTest query;

    EXPECT_EQ(6, query.getMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLast(valuesForTest));
}

TEST(GetMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLastTest, WorksOnExample2) {
    ValuesForTest valuesForTest{5, 6, 1, 3};
    QueryForTest query;

    EXPECT_EQ(2, query.getMinimumAdjacentSwapsToPlaceMaximumInFirstAndMinimumInLast(valuesForTest));
}

}  // namespace algorithm
}  // namespace alba
