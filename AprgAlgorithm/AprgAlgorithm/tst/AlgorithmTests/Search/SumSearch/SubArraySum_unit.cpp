#include <Algorithm/Search/SumSearch/SubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using SumSearch = SubArraySum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
}  // namespace

TEST(SubArraySumTest, GetSubArrayWithSumWorksOnExample1) {
    ValuesForTest const valuesToSearch{1, 3, 2, 5, 1, 1, 2, 3};
    SumSearch const search(valuesToSearch);

    ValuesForTest const valuesToVerify(search.getSubArrayWithSum(8));

    ValuesForTest const valuesToExpect{2, 5, 1};
    EXPECT_EQ(valuesToExpect, valuesToVerify);
}

}  // namespace alba::algorithm
