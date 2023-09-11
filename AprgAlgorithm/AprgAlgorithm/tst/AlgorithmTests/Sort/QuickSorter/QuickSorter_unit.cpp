#include <Algorithm/Sort/QuickSorter/QuickSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba::algorithm {

namespace {
using Characters = vector<char>;
using Integers = vector<int>;
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = QuickSorter<Characters>;
using IntegersSorter = QuickSorter<Integers>;
using DoublesSorter = QuickSorter<Doubles>;
using StringsSorter = QuickSorter<Strings>;
using StabilityCheckObjectsSorter = QuickSorter<StabilityCheckObjects>;
}  // namespace

TEST(QuickSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter const sorter(PivotType::LowestIndex);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter const sorter(PivotType::LowestIndex);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter const sorter(PivotType::LowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter const sorter(PivotType::LowestIndex);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators
TEST(QuickSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter const sorter(PivotType::LowestIndex);
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(QuickSorterTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter const sorter(PivotType::LowestIndex);
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(QuickSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter const sorter(PivotType::LowestIndex);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(QuickSorterTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter const sorter(PivotType::LowestIndex);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtLowestIndex) {
    CharactersSorter const sorter(PivotType::LowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtHighestIndex) {
    CharactersSorter const sorter(PivotType::HighestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtRandomIndex) {
    CharactersSorter const sorter(PivotType::RandomIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtMedianOfMedians) {
    CharactersSorter const sorter(PivotType::MedianOfMedians);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

}  // namespace alba::algorithm
