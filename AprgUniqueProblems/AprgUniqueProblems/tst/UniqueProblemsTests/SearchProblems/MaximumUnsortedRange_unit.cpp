#include <UniqueProblems/SearchProblems/MaximumUnsortedRange.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = MaximumUnsortedRange<ValuesForTest>;
}  // namespace

TEST(MaximumUnsortedRangeTest, GetMaximumUnsortedRangeWorksOnEmpty) {
    ValuesForTest const valuesForTest;
    QueryForTest const query;

    QueryForTest::IndexPair const expectedIndexPair{QueryForTest::INVALID_INDEX, QueryForTest::INVALID_INDEX};
    EXPECT_EQ(expectedIndexPair, query.getMaximumUnsortedRange(valuesForTest));
}

TEST(MaximumUnsortedRangeTest, GetMaximumUnsortedRangeWorksOnOneValue) {
    ValuesForTest const valuesForTest{10};
    QueryForTest const query;

    QueryForTest::IndexPair const expectedIndexPair{QueryForTest::INVALID_INDEX, QueryForTest::INVALID_INDEX};
    EXPECT_EQ(expectedIndexPair, query.getMaximumUnsortedRange(valuesForTest));
}

TEST(MaximumUnsortedRangeTest, GetMaximumUnsortedRangeWorksOnExample1) {
    ValuesForTest const valuesForTest{10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
    QueryForTest const query;

    QueryForTest::IndexPair const expectedIndexPair{3, 8};
    EXPECT_EQ(expectedIndexPair, query.getMaximumUnsortedRange(valuesForTest));
}

TEST(MaximumUnsortedRangeTest, GetMaximumUnsortedRangeWorksOnExample2) {
    ValuesForTest const valuesForTest{0, 1, 15, 25, 6, 7, 30, 40, 50};
    QueryForTest const query;

    QueryForTest::IndexPair const expectedIndexPair{2, 5};
    EXPECT_EQ(expectedIndexPair, query.getMaximumUnsortedRange(valuesForTest));
}

}  // namespace alba::algorithm
