#include <Algorithm/Search/NearestValue/JumpSearch/JumpNearestValueSearch.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = JumpNearestValueSearch<ValuesForTest>;
}  // namespace

TEST(JumpNearestValueSearchTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetNearestValueWorksWhenThereIsOneValue) {
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetNearestValueWorksWhenThereAreDuplicateValues) {
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    testGetNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetNearestValueWorksWhenNearestValueIsLower) {
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetNearestValueWorksWhenNearestValueIsHigher) {
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    testGetIndexOfNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower) {
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher) {
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest const duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(33));
}

}  // namespace alba::algorithm
