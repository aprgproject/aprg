#include <Algorithm/Sort/QuickSorter/QuickSelector.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSelector.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSelector;
using namespace std;

namespace alba::algorithm {

namespace {
using Characters = vector<char>;
using Integers = vector<int>;
using CharacterSelector = QuickSelector<Characters>;
using IntegerSelector = QuickSelector<Integers>;
}  // namespace

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1) {
    CharacterSelector const selector(PivotType::LowestIndex);
    testDoNthElementUsingExample1WithCharacters<CharacterSelector, Characters>(selector);
}

TEST(QuickSelectorTest, DoNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegerSelector const selector(PivotType::LowestIndex);
    testDoNthElementUsingExample1WithPositiveAndNegativeIntegers<IntegerSelector, Integers>(selector);
}

TEST(QuickSelectorTest, GetNthSelectWorksOnCharactersUsingExample1) {
    CharacterSelector const selector(PivotType::LowestIndex);
    testGetNthElementUsingExample1WithCharacters<CharacterSelector, Characters>(selector);
}

TEST(QuickSelectorTest, GetNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegerSelector const selector(PivotType::LowestIndex);
    testGetNthElementUsingExample1WithPositiveAndNegativeIntegers<IntegerSelector, Integers>(selector);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtLowestIndex) {
    CharacterSelector const selector(PivotType::LowestIndex);
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSort, 5);

    Characters const valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'R', 'P', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtHighestIndex) {
    CharacterSelector const selector(PivotType::HighestIndex);
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSort, 5);

    Characters const valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'R', 'P', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtRandomIndex) {
    CharacterSelector const selector(PivotType::RandomIndex);
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSort, 5);

    EXPECT_EQ('O', valuesToSort[5]);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtMedianOfMedians) {
    CharacterSelector const selector(PivotType::MedianOfMedians);
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSort, 5);

    Characters const valuesToExpect{'E', 'L', 'A', 'E', 'M', 'O', 'P', 'R', 'X', 'S', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

}  // namespace alba::algorithm
