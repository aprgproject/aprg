#include <Algorithm/Search/SumSearch/ThreeSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using SumSearch = ThreeSum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using ThreeValuesForTest = SumSearch::ThreeValues;
}  // namespace

TEST(ThreeSumTest, GetNonDuplicateThreeValuesWithSumWorksOnExample1) {
    ValuesForTest const sortedValues{1, 4, 5, 6, 7, 9, 10};
    SumSearch const search(sortedValues);

    ThreeValuesForTest const threeValuesToVerify(search.getNonDuplicateThreeValuesWithSum(18));

    ThreeValuesForTest const threeValuesToExpect{1, 7, 10};
    EXPECT_EQ(threeValuesToExpect, threeValuesToVerify);
}

TEST(ThreeSumTest, GetPossibleDuplicatedThreeValuesWithSumWorksOnExample1) {
    ValuesForTest const sortedValues{1, 4, 5, 6, 7, 9, 10};
    SumSearch const search(sortedValues);

    ThreeValuesForTest const threeValuesToVerify(search.getPossibleDuplicatedThreeValuesWithSum(30));

    ThreeValuesForTest const threeValuesToExpect{10, 10, 10};
    EXPECT_EQ(threeValuesToExpect, threeValuesToVerify);
}

}  // namespace alba::algorithm
