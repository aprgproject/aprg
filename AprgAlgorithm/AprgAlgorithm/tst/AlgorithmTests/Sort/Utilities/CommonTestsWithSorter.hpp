#pragma once

#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>
#include <Common/Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>

#include <algorithm>

namespace alba::algorithm::CommonTestsWithSorter {

template <typename Sorter, typename Values>
void testSortUsingEmptyExampleWithCharacters(Sorter const& sorter) {
    Values emptyContainer;

    sorter.sort(emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

template <typename Sorter, typename Values>
void testSortUsingOneValueExampleWithCharacters(Sorter const& sorter) {
    Values valuesToSort{'E'};

    sorter.sort(valuesToSort);

    Values valuesToExpect{'E'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

template <typename Sorter, typename Values>
void testSortUsingExample1WithCharacters(Sorter const& sorter) {
    Values valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    sorter.sort(valuesToSort);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

template <typename Sorter, typename Values>
void testSortUsingExample2WithCharacters(Sorter const& sorter) {
    Values valuesToSort{'C', 'O', 'M', 'P', 'L', 'I', 'C', 'A', 'T', 'E', 'D', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    sorter.sort(valuesToSort);

    Values valuesToExpect{'A', 'A', 'C', 'C', 'D', 'E', 'E', 'E', 'I', 'L', 'L', 'M', 'M', 'O', 'P', 'P', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

template <typename Sorter, typename Values>
void testSortUsingExample1WithPositiveAndNegativeIntegers(Sorter const& sorter) {
    Values valuesToSort{-5, -10, 0, -3, 8, 5, -1, 10};

    sorter.sort(valuesToSort);

    Values valuesToExpect{-10, -5, -3, -1, 0, 5, 8, 10};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

template <typename Sorter, typename Values>
void testSortUsingExample1WithDoubleValues(Sorter const& sorter) {
    Values valuesToSort{0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};

    sorter.sort(valuesToSort);

    Values valuesToExpect{0.1234, 0.3434, 0.565, 0.656, 0.665, 0.897};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

template <typename Sorter, typename Values>
void testSortUsingExample1WithStrings(Sorter const& sorter) {
    ALBA_DBG_PRINT1("pass100");
    Values valuesToSort{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                        "ms. puff",  "pearl",   "larry",     "plankton"};

    ALBA_DBG_PRINT1("pass101");
    sorter.sort(valuesToSort);

    ALBA_DBG_PRINT1("pass102");
    Values valuesToExpect{"larry",    "mr. crabs", "ms. puff",  "patrick",  "pearl",
                          "plankton", "sandy",     "spongebob", "squidward"};
    ALBA_DBG_PRINT1("pass103");
    EXPECT_EQ(valuesToExpect, valuesToSort);
    ALBA_DBG_PRINT1("pass104");
}

template <typename Sorter, typename Values>
void testSortAsStableUsingExample1WithStabilityCheckObjects(Sorter const& sorter) {
    Values valuesToSort{{'A', 1}, {'C', 1}, {'D', 1}, {'A', 2}, {'B', 1}, {'A', 3}, {'F', 1},
                        {'E', 1}, {'B', 2}, {'D', 2}, {'D', 3}, {'B', 3}, {'A', 4}};

    sorter.sort(valuesToSort);

    Values valuesToExpect{{'A', 1}, {'A', 2}, {'A', 3}, {'A', 4}, {'B', 1}, {'B', 2}, {'B', 3},
                          {'C', 1}, {'D', 1}, {'D', 2}, {'D', 3}, {'E', 1}, {'F', 1}};
    bool const isStableSorted = std::equal(
        valuesToSort.cbegin(), valuesToSort.cend(), valuesToExpect.cbegin(), valuesToExpect.cend(),
        areObjectsEqualOnVisibleAndNotVisiblePart);
    EXPECT_TRUE(isStableSorted);
}

template <typename Sorter, typename Values>
void testSortAsNotStableUsingExample1WithStabilityCheckObjects(Sorter const& sorter) {
    Values valuesToSort{{'A', 1}, {'C', 1}, {'D', 1}, {'A', 2}, {'B', 1}, {'A', 3}, {'F', 1},
                        {'E', 1}, {'B', 2}, {'D', 2}, {'D', 3}, {'B', 3}, {'A', 4}};

    sorter.sort(valuesToSort);

    Values valuesToExpect{{'A', 1}, {'A', 2}, {'A', 3}, {'A', 4}, {'B', 1}, {'B', 2}, {'B', 3},
                          {'C', 1}, {'D', 1}, {'D', 2}, {'D', 3}, {'E', 1}, {'F', 1}};
    bool const isSortedButNotStable = std::equal(
        valuesToSort.cbegin(), valuesToSort.cend(), valuesToExpect.cbegin(), valuesToExpect.cend(),
        areObjectsEqualOnVisibleOnly);
    EXPECT_TRUE(isSortedButNotStable);
}

}  // namespace alba::algorithm::CommonTestsWithSorter
