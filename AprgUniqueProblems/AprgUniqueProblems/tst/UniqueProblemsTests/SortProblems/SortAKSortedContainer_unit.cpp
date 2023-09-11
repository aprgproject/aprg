#include <UniqueProblems/SortProblems/SortAKSortedContainer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using Integers = vector<int>;
using IntegersSorter = SortAKSortedContainer<Integers>;
}  // namespace

TEST(SortAKSortedContainerTest, SortWorksOnIntegersAndDoesNotCrashUsingEmptyExample) {
    IntegersSorter const sorter;
    Integers emptyContainer;

    sorter.sort(3, emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(SortAKSortedContainerTest, SortWorksOnIntegersUsingOneValueExample) {
    IntegersSorter const sorter;
    Integers valuesToTest{5};

    sorter.sort(3, valuesToTest);

    Integers const valuesToExpect{5};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortAKSortedContainerTest, SortWorksOnIntegersUsingExample1) {
    IntegersSorter const sorter;
    Integers valuesToTest{6, 5, 3, 2, 8, 10, 9};

    sorter.sort(3, valuesToTest);

    Integers const valuesToExpect{2, 3, 5, 6, 8, 9, 10};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortAKSortedContainerTest, SortWorksOnIntegersUsingExample2) {
    IntegersSorter const sorter;
    Integers valuesToTest{10, 9, 8, 7, 4, 13, 12, 11};

    sorter.sort(4, valuesToTest);

    Integers const valuesToExpect{4, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}  // namespace alba::algorithm
