#include <Algorithm/Sort/QuickSorter/QuickSorterForList.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba::algorithm {

namespace {
using Characters = list<char>;
using Integers = list<int>;
using Doubles = list<double>;
using Strings = list<string>;
using StabilityCheckObjects = list<StabilityCheckObject>;
using CharactersSorter = QuickSorterForList<char>;
using IntegersSorter = QuickSorterForList<int>;
using DoublesSorter = QuickSorterForList<double>;
using StringsSorter = QuickSorterForList<string>;
using StabilityCheckObjectsSorter = QuickSorterForList<StabilityCheckObject>;
}  // namespace

TEST(QuickSorterForListTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter const sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterForListTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter const sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterForListTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter const sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterForListTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter const sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterForListTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter const sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(QuickSorterForListTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter const sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(QuickSorterForListTest, SortWorksOnStringsUsingExample1) {
    StringsSorter const sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(QuickSorterForListTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter const sorter;
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

}  // namespace alba::algorithm
