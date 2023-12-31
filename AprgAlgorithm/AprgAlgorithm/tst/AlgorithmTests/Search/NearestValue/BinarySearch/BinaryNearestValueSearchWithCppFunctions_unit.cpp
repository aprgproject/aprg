#include <Algorithm/Search/NearestValue/BinarySearch/BinaryNearestValueSearchWithCppFunctions.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = BinaryNearestValueSearchWithCppFunctions<ValuesForTest>;
}  // namespace

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetNearestValueWorksWhenThereIsOneValue) {
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetNearestValueWorksWhenThereAreDuplicateValues) {
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    testGetNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetNearestValueWorksWhenNearestValueIsLower) {
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetNearestValueWorksWhenNearestValueIsHigher) {
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    testGetIndexOfNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower) {
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher) {
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest const duplicateValues{0, 0, 0, 0, 0};
    SearchForTest const search(duplicateValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(33));
}

TEST(BinaryNearestValueSearchWithCppFunctionsTest, GetLowerBoundAndGetHigherBoundWorks) {
    ValuesForTest const sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest const search(sortedValues);

    EXPECT_EQ(43, search.getLowerBound(34));
    EXPECT_EQ(43, search.getHigherBound(34));
}

}  // namespace alba::algorithm
