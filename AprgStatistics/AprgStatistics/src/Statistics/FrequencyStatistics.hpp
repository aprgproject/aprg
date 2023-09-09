#pragma once

#include <map>
#include <vector>

namespace alba::FrequencyStatistics {
using FrequencySamples = std::map<int, int>;
using FrequencyPair = std::pair<int, int>;
using MultipleValues = std::vector<int>;
MultipleValues calculateMode(FrequencySamples const& samples);
double calculateSum(FrequencySamples const& samples);
double calculateMean(FrequencySamples const& samples);
double calculateMedian(FrequencySamples const& samples);
int calculateNumberOfSamples(FrequencySamples const& samples);
}  // namespace alba::FrequencyStatistics
