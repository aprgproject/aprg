#include <UniqueProblems/SearchProblems/FindAPairInAContainerWithSumClosestToAValue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using QueryForTest = FindAPairInAContainerWithSumClosestToAValue<ValuesForTest>;
using ValuePairForTest = QueryForTest::ValuePair;
}  // namespace

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnEmpty) {
    ValuesForTest const valuesForTest;
    QueryForTest const query(valuesForTest);

    QueryForTest::ValuePair const expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnOneValue) {
    ValuesForTest const valuesForTest{12};
    QueryForTest const query(valuesForTest);

    QueryForTest::ValuePair const expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnExample1) {
    ValuesForTest const valuesForTest{12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
    QueryForTest const query(valuesForTest);

    QueryForTest::ValuePair const expectedValuePair{12, 39};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnExample2) {
    ValuesForTest const valuesForTest{10, 22, 28, 29, 30, 40};
    QueryForTest const query(valuesForTest);

    QueryForTest::ValuePair const expectedValuePair{22, 30};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(54));
}

}  // namespace alba::algorithm
