#include <Algorithm/Search/SumSearch/MaximumSubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using ValuesForTest = vector<int>;
using SumSearch = MaximumSubArraySum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using SubArrayDetailsForTest = SumSearch::SubArrayDetails;
}  // namespace

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWithDetailsWorksOnExample1) {
    ValuesForTest const valuesToSearch{-1, 2, 4, -3, 5, 2, -5, 2};
    SumSearch search(valuesToSearch);

    SubArrayDetailsForTest const subArrayDetailsToVerify(search.getMaximumSubArraySumWithDetails());

    EXPECT_EQ(1, subArrayDetailsToVerify.lowIndex);
    EXPECT_EQ(5, subArrayDetailsToVerify.highIndex);
    EXPECT_EQ(10, subArrayDetailsToVerify.sum);
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWorksOnExample1) {
    ValuesForTest const valuesToSearch{-1, 2, 4, -3, 5, 2, -5, 2};
    SumSearch search(valuesToSearch);

    EXPECT_EQ(10, search.getMaximumSubArraySum());
}

}  // namespace alba::algorithm
