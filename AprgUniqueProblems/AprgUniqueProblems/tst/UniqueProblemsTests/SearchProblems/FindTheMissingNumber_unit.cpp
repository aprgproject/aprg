#include <UniqueProblems/SearchProblems/FindTheMissingNumber.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using QueryForTest = FindTheMissingNumber<ValuesForTest>;
}  // namespace

TEST(FindTheMissingNumberTest, GetTheMissingNumberWorksOnEmpty) {
    ValuesForTest const valuesForTest;
    QueryForTest query;

    EXPECT_EQ(1, query.getTheMissingNumberUsingSum(valuesForTest));
    EXPECT_EQ(1, query.getTheMissingNumberUsingXor(valuesForTest));
}

TEST(FindTheMissingNumberTest, GetTheMissingNumberWorksOnOneValue) {
    ValuesForTest const valuesForTest{2};
    QueryForTest query;

    EXPECT_EQ(1, query.getTheMissingNumberUsingSum(valuesForTest));
    EXPECT_EQ(1, query.getTheMissingNumberUsingXor(valuesForTest));
}

TEST(FindTheMissingNumberTest, GetTheMissingNumberWorksOnExample1) {
    ValuesForTest const valuesForTest{1, 2, 3, 5};
    QueryForTest query;

    EXPECT_EQ(4, query.getTheMissingNumberUsingSum(valuesForTest));
    EXPECT_EQ(4, query.getTheMissingNumberUsingXor(valuesForTest));
}

TEST(FindTheMissingNumberTest, GetTheMissingNumberWorksOnExample2) {
    ValuesForTest const valuesForTest{1, 2, 4, 6, 3, 7, 8};
    QueryForTest query;

    EXPECT_EQ(5, query.getTheMissingNumberUsingSum(valuesForTest));
    EXPECT_EQ(5, query.getTheMissingNumberUsingXor(valuesForTest));
}

}  // namespace alba::algorithm
