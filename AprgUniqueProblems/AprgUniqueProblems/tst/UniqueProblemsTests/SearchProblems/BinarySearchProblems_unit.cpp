#include <UniqueProblems/SearchProblems/BinarySearchProblems.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = BinarySearchProblems<ValuesForTest>;
}  // namespace

TEST(BinarySearchProblemsTest, GetNumberOfDuplicatesWorks) {
    ValuesForTest const valuesForTest{1, 2, 3, 5, 6, 7, 7, 7, 8, 9, 10};
    QueryForTest query;

    EXPECT_EQ(3, query.getNumberOfDuplicates(valuesForTest, 7));
}

TEST(BinarySearchProblemsTest, GetPositionOfRotationWorks) {
    ValuesForTest const valuesForTest{6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
    QueryForTest query;

    EXPECT_EQ(5, query.getPositionOfRotation(valuesForTest));
}

TEST(BinarySearchProblemsTest, GetNearestFloorWorks) {
    ValuesForTest const valuesForTest{1, 2, 3, 5, 6, 8, 9, 10};
    QueryForTest query;

    EXPECT_EQ(6, query.getNearestFloor(valuesForTest, 7));
}

TEST(BinarySearchProblemsTest, GetNearestCeilWorks) {
    ValuesForTest const valuesForTest{1, 2, 3, 5, 6, 8, 9, 10};
    QueryForTest query;

    EXPECT_EQ(8, query.getNearestCeil(valuesForTest, 7));
}

}  // namespace alba::algorithm
