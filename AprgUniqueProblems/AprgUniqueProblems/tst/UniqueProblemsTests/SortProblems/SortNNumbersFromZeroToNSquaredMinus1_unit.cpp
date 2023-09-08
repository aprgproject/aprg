#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>
#include <UniqueProblems/SortProblems/SortNNumbersFromZeroToNSquaredMinus1.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba::algorithm {

namespace {
using Characters = vector<char>;
using Integers = vector<int>;
using CharactersSorter = SortNNumbersFromZeroToNSquaredMinus1<Characters>;
using SmallIntegerSorter = SortNNumbersFromZeroToNSquaredMinus1<Integers>;
}  // namespace

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators
// CANNOT SORT POSITIVE AND NEGATIVE VALUES
// CANNOT SORT DOUBLE VALUES
// CANNOT SORT STRINGS
// CANNOT SORT STABILITY OBJECTS

TEST(SortNNumbersFromZeroToNSquaredMinus1Test, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SortNNumbersFromZeroToNSquaredMinus1Test, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SortNNumbersFromZeroToNSquaredMinus1Test, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SortNNumbersFromZeroToNSquaredMinus1Test, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

}  // namespace alba::algorithm
