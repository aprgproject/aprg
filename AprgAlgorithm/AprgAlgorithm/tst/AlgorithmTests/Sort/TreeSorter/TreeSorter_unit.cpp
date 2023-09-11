#include <Algorithm/Sort/TreeSorter/TreeSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba::algorithm {

namespace {
using Characters = vector<char>;
using ListOfCharacters = list<char>;
using Integers = vector<int>;
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = TreeSorter<Characters>;
using ListOfCharactersSorter = TreeSorter<ListOfCharacters>;
using IntegersSorter = TreeSorter<Integers>;
using DoublesSorter = TreeSorter<Doubles>;
using StringsSorter = TreeSorter<Strings>;
using StabilityCheckObjectsSorter = TreeSorter<StabilityCheckObjects>;
}  // namespace

TEST(TreeSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter const sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(TreeSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter const sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(TreeSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter const sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(TreeSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter const sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(TreeSorterTest, SortWorksOnListOfCharactersUsingExample1) {
    ListOfCharactersSorter const sorter;
    testSortUsingExample1WithCharacters<ListOfCharactersSorter, ListOfCharacters>(sorter);
}

TEST(TreeSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter const sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(TreeSorterTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter const sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(TreeSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter const sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(TreeSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter const sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}  // namespace alba::algorithm
