#include <UniqueProblems/SearchProblems/FindThePairWithClosestToSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = FindThePairWithClosestToSum<ValuesForTest>;
}  // namespace

TEST(FindThePairWithClosestToSumTest, GetValuePairThatIsClosestToSumWorksWhenFirstContainerIsEmpty) {
    ValuesForTest const values1{1, 4, 5, 7};
    ValuesForTest const values2;
    QueryForTest query;

    QueryForTest::ValuePair const expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairThatIsClosestToSum(values1, values2, 32));
}

TEST(FindThePairWithClosestToSumTest, GetValuePairThatIsClosestToSumWorksWhenSecondContainerIsEmpty) {
    ValuesForTest const values1;
    ValuesForTest const values2{10, 20, 30, 40};
    QueryForTest query;

    QueryForTest::ValuePair const expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairThatIsClosestToSum(values1, values2, 32));
}

TEST(FindThePairWithClosestToSumTest, GetValuePairThatIsClosestToSumWorksOnExample1) {
    ValuesForTest const values1{1, 4, 5, 7};
    ValuesForTest const values2{10, 20, 30, 40};
    QueryForTest query;

    QueryForTest::ValuePair const expectedValuePair1{1, 30};
    QueryForTest::ValuePair const expectedValuePair2{7, 40};
    EXPECT_EQ(expectedValuePair1, query.getValuePairThatIsClosestToSum(values1, values2, 32));
    EXPECT_EQ(expectedValuePair2, query.getValuePairThatIsClosestToSum(values1, values2, 50));
}

}  // namespace alba::algorithm
