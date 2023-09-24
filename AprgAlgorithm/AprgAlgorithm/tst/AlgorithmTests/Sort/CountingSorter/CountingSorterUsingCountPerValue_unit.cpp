#include <Algorithm/Sort/CountingSorter/CountingSorterUsingCountPerValue.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba::algorithm {

namespace {

constexpr int MAX_NUMBER_OF_CHARACTERS = 256;
constexpr int MAX_NUMBER_OF_SMALL_INTS = 21;
using Characters = vector<char>;
using ListOfCharacters = list<char>;
using Integers = vector<int>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = CountingSorterUsingCountPerValue<Characters, MAX_NUMBER_OF_CHARACTERS>;
using ListOfCharactersSorter = CountingSorterUsingCountPerValue<ListOfCharacters, MAX_NUMBER_OF_CHARACTERS>;
using SmallIntegerSorter = CountingSorterUsingCountPerValue<Integers, MAX_NUMBER_OF_SMALL_INTS>;
using StabilityCheckObjectsSorter = CountingSorterUsingCountPerValue<StabilityCheckObjects, MAX_NUMBER_OF_CHARACTERS>;

CharactersSorter::IndexableValueToValueFunction indexableValueToCharacterFunction =
    [](int const indexableValue) -> char { return static_cast<char>(indexableValue & 0xFF); };

SmallIntegerSorter::IndexableValueToValueFunction indexableValueToSmallIntFunction =
    [](int const indexableValue) -> int {
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return indexableValue - 10;
};

StabilityCheckObjectsSorter::IndexableValueToValueFunction indexableValueToStabilityCheckObjectFunction =
    [](int const indexableValue) -> StabilityCheckObject {
    return {static_cast<char>(indexableValue & 0xFF), 0};
};

CharactersSorter::ValueToIndexableValueFunction characterToIndexableValueFunction = [](char const& value) -> int {
    return value & 0xFF;  // already converts to integer
};

SmallIntegerSorter::ValueToIndexableValueFunction smallIntToIndexableValueFunction = [](int const& value) -> int {
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return 10 + value;
};

StabilityCheckObjectsSorter::ValueToIndexableValueFunction stabilityCheckObjectToIndexableValueFunction =
    [](StabilityCheckObject const& value) -> int {
    return value.getVisiblePart() & 0xFF;  // there is some splicing here
};

}  // namespace

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter const sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter const sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter const sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter const sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnListOfCharactersUsingExample1) {
    ListOfCharactersSorter const sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingExample1WithCharacters<ListOfCharactersSorter, ListOfCharacters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    SmallIntegerSorter const sorter(smallIntToIndexableValueFunction, indexableValueToSmallIntFunction);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES
// CANNOT SORT STRINGS
TEST(CountingSorterUsingCountPerValueTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter const sorter(
        stabilityCheckObjectToIndexableValueFunction, indexableValueToStabilityCheckObjectFunction);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

}  // namespace alba::algorithm
