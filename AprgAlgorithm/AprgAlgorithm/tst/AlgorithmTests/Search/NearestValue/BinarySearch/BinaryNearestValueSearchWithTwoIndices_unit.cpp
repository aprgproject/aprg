#include <Algorithm/Search/NearestValue/BinarySearch/BinaryNearestValueSearchWithTwoIndices.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = BinaryNearestValueSearchWithTwoIndices<ValuesForTest>;
}  // namespace

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereIsOneValue) {
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreDuplicateValues) {
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    testGetNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsLower) {
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsHigher) {
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    testGetIndexOfNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower) {
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher) {
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerIndexAndGetHigherIndexWorksWithoutGetNearestValue) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(0, search.getLowerIndex());
    EXPECT_EQ(14, search.getHigherIndex());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerIndexAndGetHigherIndexWorksAfterGetNearestValue) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);
    EXPECT_EQ(33, search.getNearestValue(34));

    EXPECT_EQ(4, search.getLowerIndex());
    EXPECT_EQ(5, search.getHigherIndex());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithOneItem) {
    ValuesForTest const sortedValues{6};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(6, search.getLowerValue());
    EXPECT_EQ(6, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithTwoItems) {
    ValuesForTest const sortedValues{6, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(6, search.getLowerValue());
    EXPECT_EQ(97, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithFourItems) {
    ValuesForTest const sortedValues{6, 13, 96, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(6, search.getLowerValue());
    EXPECT_EQ(97, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithoutGetNearestValue) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(6, search.getLowerValue());
    EXPECT_EQ(97, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksAfterGetNearestValue) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);
    EXPECT_EQ(33, search.getNearestValue(34));

    EXPECT_EQ(33, search.getLowerValue());
    EXPECT_EQ(43, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(5, 6, sortedValues);

    EXPECT_EQ(43, search.getLowerValue());
    EXPECT_EQ(51, search.getHigherValue());
    EXPECT_EQ(43, search.getNearestValue(33));
    EXPECT_EQ(43, search.getLowerValue());
    EXPECT_EQ(43, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(3, 5, sortedValues);

    EXPECT_EQ(25, search.getLowerValue());
    EXPECT_EQ(43, search.getHigherValue());
    EXPECT_EQ(33, search.getNearestValue(33));
    EXPECT_EQ(33, search.getLowerValue());
    EXPECT_EQ(33, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOdd) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1, 8, sortedValues);

    EXPECT_EQ(13, search.getLowerValue());
    EXPECT_EQ(64, search.getHigherValue());
    EXPECT_EQ(33, search.getNearestValue(33));
    EXPECT_EQ(33, search.getLowerValue());
    EXPECT_EQ(33, search.getHigherValue());
}

TEST(
    BinaryNearestValueSearchWithTwoIndicesTest,
    SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOddAndValueIsHigher) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1, 8, sortedValues);

    EXPECT_EQ(13, search.getLowerValue());
    EXPECT_EQ(64, search.getHigherValue());
    EXPECT_EQ(33, search.getNearestValue(34));
    EXPECT_EQ(33, search.getLowerValue());
    EXPECT_EQ(43, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest const duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(33));
}

}  // namespace alba::algorithm
