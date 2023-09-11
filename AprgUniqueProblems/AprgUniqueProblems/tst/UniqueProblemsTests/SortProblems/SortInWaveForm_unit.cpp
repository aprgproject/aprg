#include <UniqueProblems/SortProblems/SortInWaveForm.hpp>

#include <gtest/gtest.h>

#include <forward_list>

using namespace std;

namespace alba::algorithm {

namespace {
using Integers = vector<int>;
using IntegersInForwardList = vector<int>;
using IntegersSorter = SortInWaveForm<Integers>;
using IntegersInForwardListSorter = SortInWaveForm<IntegersInForwardList>;
}  // namespace

TEST(SortInWaveFormTest, SortWorksOnIntegersAndDoesNotCrashUsingEmptyExample) {
    IntegersSorter const sorter;
    Integers emptyContainer;

    sorter.sort(emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(SortInWaveFormTest, SortWorksOnIntegersUsingOneValueExample) {
    IntegersSorter const sorter;
    Integers valuesToTest{5};

    sorter.sort(valuesToTest);

    Integers const valuesToExpect{5};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortInWaveFormTest, SortWorksOnIntegersUsingExample1) {
    IntegersSorter const sorter;
    Integers valuesToTest{6, 5, 3, 2, 8, 10, 9};

    sorter.sort(valuesToTest);

    Integers const valuesToExpect{6, 3, 5, 2, 10, 8, 9};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortInWaveFormTest, SortWorksOnIntegersUsingExample2) {
    IntegersSorter const sorter;
    Integers valuesToTest{10, 90, 49, 2, 1, 5, 23};

    sorter.sort(valuesToTest);

    Integers const valuesToExpect{90, 10, 49, 1, 5, 2, 23};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortInWaveFormTest, SortWorksOnIntegersUsingForwardListExample) {
    IntegersInForwardListSorter const sorter;
    IntegersInForwardList valuesToTest{10, 90, 49, 2, 1, 5, 23};

    sorter.sort(valuesToTest);

    Integers const valuesToExpect{90, 10, 49, 1, 5, 2, 23};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}  // namespace alba::algorithm
