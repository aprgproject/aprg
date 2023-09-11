#include <UniqueProblems/SearchProblems/SearchUnsortedElementOnAlmostSortedContainer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = SearchUnsortedElementOnAlmostSortedContainer<ValuesForTest>;
constexpr SearchForTest::Index INVALID_INDEX = SearchForTest::INVALID_INDEX;
}  // namespace

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    ValuesForTest const emptyValues;
    SearchForTest const search(emptyValues);

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(33));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    ValuesForTest const oneValue{10};
    SearchForTest const search(oneValue);

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(33));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest const duplicateValues{0, 0, 0, 0, 0};
    SearchForTest const search(duplicateValues);

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(33));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 43, 33, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(5, search.getIndexOfValue(33));
}

TEST(
    SearchUnsortedElementOnAlmostSortedContainerTest,
    GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsOne) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 43, 33, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(5, search.getIndexOfValue(5, 6, 33));
}

TEST(
    SearchUnsortedElementOnAlmostSortedContainerTest,
    GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsTwo) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 43, 33, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(5, search.getIndexOfValue(3, 5, 33));
}

TEST(
    SearchUnsortedElementOnAlmostSortedContainerTest,
    GetIndexOfNearestValueWorksWithndexesWhenDistanceFromLowerToHigherIsOdd) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 43, 33, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(5, search.getIndexOfValue(1, 8, 33));
}

}  // namespace alba::algorithm
