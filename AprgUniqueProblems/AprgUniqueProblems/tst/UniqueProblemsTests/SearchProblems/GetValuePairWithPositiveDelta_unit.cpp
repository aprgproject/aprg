#include <UniqueProblems/SearchProblems/GetValuePairWithPositiveDelta.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using QueryForTest = GetValuePairWithPositiveDelta<ValuesForTest>;
using ValuePairForTest = QueryForTest::ValuePair;
}  // namespace

TEST(GetValuePairWithPositiveDeltaTest, GetNumberOfOnesInASortedBinaryContainerWorksOnEmpty) {
    ValuesForTest const sortedValues;
    QueryForTest const query(sortedValues);

    ValuePairForTest const pairToExpect{};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8));
}

TEST(GetValuePairWithPositiveDeltaTest, GetNumberOfOnesInASortedBinaryContainerWorksOnOneValue) {
    ValuesForTest const sortedValues{5};
    QueryForTest const query(sortedValues);

    ValuePairForTest const pairToExpect{};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8));
}

TEST(GetValuePairWithPositiveDeltaTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesDoesNotWorkOnExample1) {
    ValuesForTest const sortedValues{1, 4, 5, 6, 7, 9, 10};
    QueryForTest const query(sortedValues);

    ValuePairForTest const pairToExpect{1, 9};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8));
}

}  // namespace alba::algorithm
