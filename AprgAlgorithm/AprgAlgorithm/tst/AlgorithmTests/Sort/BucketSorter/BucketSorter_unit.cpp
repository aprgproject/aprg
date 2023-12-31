#include <Algorithm/Sort/BucketSorter/BucketSorter.hpp>
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
using CharactersSorter = BucketSorter<Characters, 10>;
using ListOfCharactersSorter = BucketSorter<ListOfCharacters, 10>;
using IntegersSorter = BucketSorter<Integers, 10>;
using DoublesSorter = BucketSorter<Doubles, 10>;
using StringsSorter = BucketSorter<Strings, 10>;
using StabilityCheckObjectsSorter = BucketSorter<StabilityCheckObjects, 10>;
}  // namespace

TEST(BucketSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter const sorter('A', 'Z');
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter const sorter('A', 'Z');
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter const sorter('A', 'Z');
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter const sorter('A', 'Z');
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnListOfCharactersUsingExample1) {
    ListOfCharactersSorter const sorter('A', 'Z');
    testSortUsingExample1WithCharacters<ListOfCharactersSorter, ListOfCharacters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    // Input is {-5, -10, 0, -3, 8, 5, -1, 10}
    IntegersSorter const sorter(-10, 10);
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(BucketSorterTest, SortWorksOnDoublesUsingExample1) {
    // Input is {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    DoublesSorter const sorter(0, 1);
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

// CANNOT SORT STRINGS
TEST(BucketSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) {
    // NOT REALLY STABLE
    // Not really stable but samples are too few
    StabilityCheckObjectsSorter const sorter(StabilityCheckObject('A', 0), StabilityCheckObject('Z', 0));
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}  // namespace alba::algorithm
