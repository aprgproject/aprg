#pragma once

#include <Statistics/DataSample.hpp>
#include <Statistics/DataStatistics.hpp>

namespace alba::OneDimensionsStatistics {

using Sample = DataSample<1>;
using Statistics = DataStatistics<1>;
using PairOfDoubles = std::pair<double, double>;
using Samples = std::vector<Sample>;

PairOfDoubles getMinMaxFromSamples(Samples const& samples);

}  // namespace alba
