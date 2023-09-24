#include <Algorithm/Sort/RadixSorter/MostSignificantDigitSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba::algorithm {

namespace {

constexpr int MAX_NUMBER_OF_NIBBLES = 16;
constexpr int MAX_NUMBER_OF_CHARACTERS = 256;
using Characters = vector<char>;
using Integers = vector<int>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = MostSignificantDigitSorter<Characters, MAX_NUMBER_OF_NIBBLES>;
using SmallIntegerSorter = MostSignificantDigitSorter<Integers, MAX_NUMBER_OF_NIBBLES>;
using StringsSorter = MostSignificantDigitSorter<Strings, MAX_NUMBER_OF_CHARACTERS>;
using StabilityCheckObjectsSorter = MostSignificantDigitSorter<StabilityCheckObjects, MAX_NUMBER_OF_NIBBLES>;

CharactersSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value,
                                                                  int const mostSignificantDigitIndex) -> int {
    return (value >> ((1 - mostSignificantDigitIndex) * 4)) & 0xF;
};

SmallIntegerSorter::GetDigitAtFunction getNibbleAtForSmallInteger = [](int const& value,
                                                                       int const mostSignificantDigitIndex) -> int {
    return ((value + 10) >> ((7 - mostSignificantDigitIndex) * 4)) & 0xF;
};

StringsSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value,
                                                               int const mostSignificantDigitIndex) -> int {
    int digitValue{};
    if (mostSignificantDigitIndex < static_cast<int>(value.length())) {
        digitValue = static_cast<int>(static_cast<unsigned char>(value[mostSignificantDigitIndex]));
    }
    return digitValue;
};

StabilityCheckObjectsSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject =
    [](StabilityCheckObject const& value, int const mostSignificantDigitIndex) -> int {
    return (value.getVisiblePart() >> ((1 - mostSignificantDigitIndex) * 4)) & 0xF;
};

CharactersSorter::IsDigitFunction isNibbleDigitInvalidForCharacter = [](char const&, int const digitIndex) -> bool {
    return digitIndex >= 2;
};

SmallIntegerSorter::IsDigitFunction isNibbleDigitInvalidForSmallInteger = [](int const&, int const digitIndex) -> bool {
    return digitIndex >= 8;
};

StringsSorter::IsDigitFunction isDigitInvalidForString = [](string const& value, int const digitIndex) -> bool {
    return digitIndex >= static_cast<int>(value.length());
};

StabilityCheckObjectsSorter::IsDigitFunction isNibbleDigitInvalidForStabilityCheckObject =
    [](StabilityCheckObject const&, int const digitIndex) -> bool { return digitIndex >= 2; };

}  // namespace

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter const sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter const sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter const sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter const sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST
TEST(MostSignificantDigitSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    SmallIntegerSorter const sorter(getNibbleAtForSmallInteger, isNibbleDigitInvalidForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES
TEST(MostSignificantDigitSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter const sorter(getCharacterAtForString, isDigitInvalidForString);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter const sorter(
        getNibbleAtForStabilityCheckObject, isNibbleDigitInvalidForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInAllStrings) {
    StringsSorter const sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                          "ms. puff",  "pearl",   "larry",     "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2, 5, 1);

    Strings const expectedStrings{"spongebob", "patrick", "sandy", "squidward", "mr. crabs",
                                  "ms. puff",  "pearl",   "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings) {
    StringsSorter const sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                          "ms. puff",  "pearl",   "larry",     "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2, 5, 6);

    Strings const expectedStrings{"spongebob", "patrick", "sandy", "mr. crabs", "squidward",
                                  "ms. puff",  "pearl",   "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings) {
    StringsSorter const sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                          "ms. puff",  "pearl",   "larry",     "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2, 5, 9);

    Strings const expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                                  "ms. puff",  "pearl",   "larry",     "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}  // namespace alba::algorithm
