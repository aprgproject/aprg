#include <UniqueProblems/SearchProblems/GetMinAdjacentSwapsToPutMaxAtFirstAndMinAtLast.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using QueryForTest = GetMinAdjacentSwapsToPutMaxAtFirstAndMinAtLast<ValuesForTest>;
}  // namespace

TEST(GetMinAdjacentSwapsToPutMaxAtFirstAndMinAtLastTest, WorksOnEmpty) {
    ValuesForTest const valuesForTest;
    QueryForTest query;

    EXPECT_EQ(0, query.getMinAdjacentSwaps(valuesForTest));
}

TEST(GetMinAdjacentSwapsToPutMaxAtFirstAndMinAtLastTest, WorksOnOneValue) {
    ValuesForTest const valuesForTest{3};
    QueryForTest query;

    EXPECT_EQ(0, query.getMinAdjacentSwaps(valuesForTest));
}

TEST(GetMinAdjacentSwapsToPutMaxAtFirstAndMinAtLastTest, WorksOnExample1) {
    ValuesForTest const valuesForTest{3, 1, 5, 3, 5, 5, 2};
    QueryForTest query;

    EXPECT_EQ(6, query.getMinAdjacentSwaps(valuesForTest));
}

TEST(GetMinAdjacentSwapsToPutMaxAtFirstAndMinAtLastTest, WorksOnExample2) {
    ValuesForTest const valuesForTest{5, 6, 1, 3};
    QueryForTest query;

    EXPECT_EQ(2, query.getMinAdjacentSwaps(valuesForTest));
}

}  // namespace alba::algorithm
