#include <Algorithm/Sort/ShellSorter/ShellSorter.hpp>
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
using CharactersSorter = ShellSorter<Characters>;
using IntegersSorter = ShellSorter<Integers>;
using DoublesSorter = ShellSorter<Doubles>;
using StringsSorter = ShellSorter<Strings>;
using StabilityCheckObjectsSorter = ShellSorter<StabilityCheckObjects>;
}  // namespace

TEST(ShellSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter const sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(ShellSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter const sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(ShellSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter const sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(ShellSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter const sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST
TEST(ShellSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter const sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(ShellSorterTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter const sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(ShellSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter const sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(ShellSorterTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter const sorter;
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

}  // namespace alba::algorithm
