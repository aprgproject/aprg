#include <UniqueProblems/SearchProblems/FindCommonElementsInThreeSortedContainers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = FindCommonElementsInThreeSortedContainers<ValuesForTest>;
}  // namespace

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenFirstContainerIsEmpty) {
    ValuesForTest const values1{1, 5, 10, 20, 40, 80};
    ValuesForTest const values2;
    ValuesForTest const values3;
    QueryForTest query;

    ValuesForTest const expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenSecondContainerIsEmpty) {
    ValuesForTest const values1;
    ValuesForTest const values2{6, 7, 20, 80, 100};
    ValuesForTest const values3;
    QueryForTest query;

    ValuesForTest const expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenThirdContainerIsEmpty) {
    ValuesForTest const values1;
    ValuesForTest const values2;
    ValuesForTest const values3{3, 4, 15, 20, 30, 70, 80, 120};
    QueryForTest query;

    ValuesForTest const expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksOnExample1) {
    ValuesForTest const values1{1, 5, 10, 20, 40, 80};
    ValuesForTest const values2{6, 7, 20, 80, 100};
    ValuesForTest const values3{3, 4, 15, 20, 30, 70, 80, 120};
    QueryForTest query;

    ValuesForTest const expectedValues1{20, 80};
    EXPECT_EQ(expectedValues1, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksOnExample2) {
    ValuesForTest const values1{1, 5, 5};
    ValuesForTest const values2{3, 4, 5, 5, 10};
    ValuesForTest const values3{5, 5, 10, 20};
    QueryForTest query;

    ValuesForTest const expectedValues1{5, 5};
    EXPECT_EQ(expectedValues1, query.getCommonElements(values1, values2, values3));
}

}  // namespace alba::algorithm
