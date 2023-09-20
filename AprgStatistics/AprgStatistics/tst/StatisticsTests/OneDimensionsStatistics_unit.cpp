#include <Statistics/OneDimensionsStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

using LocalSample = OneDimensionsStatistics::Sample;
using LocalSamples = OneDimensionsStatistics::Samples;

TEST(OneDimensionsStatisticsTest, MinMaxValuesCanFetched) {
    LocalSamples samples;
    // NOLINTBEGIN(hicpp-use-emplace,modernize-use-emplace)
    samples.emplace_back(LocalSample{-100});
    samples.emplace_back(LocalSample{-10});
    samples.emplace_back(LocalSample{-1});
    samples.emplace_back(LocalSample{1});
    samples.emplace_back(LocalSample{10});
    samples.emplace_back(LocalSample{100});
    // NOLINTEND(hicpp-use-emplace,modernize-use-emplace)
    OneDimensionsStatistics::PairOfDoubles const minMax(OneDimensionsStatistics::getMinMaxFromSamples(samples));

    EXPECT_EQ(-100, minMax.first);
    EXPECT_EQ(100, minMax.second);
}

}  // namespace alba
