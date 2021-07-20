#include <Algorithm/Search/SingleValue/LinearSearch/LinearSearchWithOneIndex.hpp>
#include <AlgorithmTests/Search/SingleValue/Utilities/CommonTestsWithSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSearch;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = LinearSearchWithOneIndex<ValuesForTest>;
}

TEST(LinearSearchWithOneIndexTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithOneIndexTest, GetNearestValueWorks)
{
    testGetNearestValueWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithOneIndexTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithOneIndexTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithOneIndexTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithOneIndexTest, GetIndexOfNearestValueWorks)
{
    testGetIndexOfNearestValueWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithOneIndexTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithOneIndexTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithOneIndexTest, GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne)
{
    ValuesForTest unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    SearchForTest search(4U, 5U, unsortedValues);

    EXPECT_EQ(72U, search.getNearestValue(33));
}

TEST(LinearSearchWithOneIndexTest, GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo)
{
    ValuesForTest unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    SearchForTest search(4U, 6U, unsortedValues);

    EXPECT_EQ(6U, search.getNearestValue(33));
}

}

}