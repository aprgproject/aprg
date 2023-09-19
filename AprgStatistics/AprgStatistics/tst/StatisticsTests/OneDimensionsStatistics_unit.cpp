#include <Statistics/OneDimensionsStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

using LocalSample = OneDimensionsStatistics::Sample;
using LocalSamples = OneDimensionsStatistics::Samples;

TEST(OneDimensionsStatisticsTest, MinMaxValuesCanFetched) {
    LocalSamples samples;
    samples.emplace_back(-100);
    samples.emplace_back(-10);
    samples.emplace_back(-1);
    samples.emplace_back(1);
    samples.emplace_back(10);
    samples.emplace_back(100);
    OneDimensionsStatistics::PairOfDoubles const minMax(OneDimensionsStatistics::getMinMaxFromSamples(samples));

    EXPECT_EQ(-100, minMax.first);
    EXPECT_EQ(100, minMax.second);
}

}  // namespace alba
