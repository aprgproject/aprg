#include <Algorithm/Search/Median/MedianOfTwoSortedContainers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = MedianOfTwoSortedContainers<ValuesForTest>;
}  // namespace

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnWhenBothAreEmpty) {
    ValuesForTest const empty;
    QueryForTest const query(empty, empty);

    EXPECT_EQ(0, query.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnWhenOneIsEmpty) {
    ValuesForTest const empty;
    ValuesForTest const notEmpty{1, 2, 3};
    QueryForTest const query1(empty, notEmpty);
    QueryForTest const query2(notEmpty, empty);

    EXPECT_EQ(2, query1.getMedian());
    EXPECT_EQ(2, query2.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnExample1) {
    ValuesForTest const valuesForTest1{1, 12, 15, 26, 38};
    ValuesForTest const valuesForTest2{2, 13, 17, 30, 45};
    QueryForTest const query(valuesForTest1, valuesForTest2);

    EXPECT_EQ(15, query.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnExample2) {
    ValuesForTest const valuesForTest1{1, 12, 17, 26, 38};
    ValuesForTest const valuesForTest2{2, 13, 15, 30, 45};
    QueryForTest const query(valuesForTest1, valuesForTest2);

    EXPECT_EQ(15, query.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnExample3) {
    ValuesForTest const valuesForTest1{1, 13, 13, 26, 38};
    ValuesForTest const valuesForTest2{2, 12, 17, 30, 45};
    QueryForTest const query(valuesForTest1, valuesForTest2);

    EXPECT_EQ(13, query.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnExample4) {
    ValuesForTest const valuesForTest1{1, 12, 13, 26, 38};
    ValuesForTest const valuesForTest2{2, 13, 17, 30, 45};
    QueryForTest const query(valuesForTest1, valuesForTest2);

    EXPECT_EQ(13, query.getMedian());
}

}  // namespace alba::algorithm
