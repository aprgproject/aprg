#include <UniqueProblems/SearchProblems/CountOnesInASortedBinaryContainer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<bool>;
using QueryForTest = CountOnesInASortedBinaryContainer<ValuesForTest>;
}  // namespace

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnEmpty) {
    ValuesForTest const valuesForTest;
    QueryForTest query;

    EXPECT_EQ(0, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnOneValue) {
    ValuesForTest const valuesForTest{true};
    QueryForTest query;

    EXPECT_EQ(1, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnWhenAllZeroes) {
    ValuesForTest const valuesForTest{false, false, false, false, false, false, false};
    QueryForTest query;

    EXPECT_EQ(0, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnWhenAllOnes) {
    ValuesForTest const valuesForTest{true, true, true, true, true, true, true};
    QueryForTest query;

    EXPECT_EQ(7, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnExample1) {
    ValuesForTest const valuesForTest{false, false, false, true, true, true, true};
    QueryForTest query;

    EXPECT_EQ(4, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

}  // namespace alba::algorithm
