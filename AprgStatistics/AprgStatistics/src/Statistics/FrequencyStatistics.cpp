#include <Statistics/FrequencyStatistics.hpp>

#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

namespace alba {

FrequencyStatistics::MultipleValues FrequencyStatistics::calculateMode(FrequencySamples const& samples) {
    MultipleValues result;
    auto iteratorForMaxFrequency = max_element(
        samples.cbegin(), samples.cend(), [](FrequencyPair const& frequencyPair1, FrequencyPair const& frequencyPair2) {
            return frequencyPair1.second < frequencyPair2.second;
        });
    if (iteratorForMaxFrequency != samples.cend()) {
        int maxFrequency = iteratorForMaxFrequency->second;

        for_each(samples.cbegin(), samples.cend(), [&](FrequencyPair const& frequencyPair) {
            if (maxFrequency == frequencyPair.second) {
                result.push_back(frequencyPair.first);
            }
        });
    }
    return result;
}

double FrequencyStatistics::calculateSum(FrequencySamples const& samples) {
    return accumulate(
        samples.cbegin(), samples.cend(), static_cast<double>(0),
        [](double const partialResult, FrequencyPair const& frequencyPair) {
            return partialResult + (frequencyPair.first * frequencyPair.second);
        });
}

double FrequencyStatistics::calculateMean(FrequencySamples const& samples) {
    double result(0);
    int const numberOfSamples = calculateNumberOfSamples(samples);
    if (numberOfSamples > 0) {
        result = calculateSum(samples) / numberOfSamples;
    }
    return result;
}

double FrequencyStatistics::calculateMedian(FrequencySamples const& samples) {
    int const numberOfSamples = calculateNumberOfSamples(samples);
    double const medianLocation = (static_cast<double>(numberOfSamples) + 1) / 2;
    int rangeOffsetForCurrentValue = 0;
    int previousMinimumValue = 0;
    double previousValue = 0;
    double result(0);
    for (auto const& frequencyPair : samples) {
        int const minimumValueOffset = (frequencyPair.second > 0) ? 1 : 0;
        if (rangeOffsetForCurrentValue + minimumValueOffset <= medianLocation &&
            medianLocation <= rangeOffsetForCurrentValue + frequencyPair.second) {
            result = frequencyPair.first;
            break;
        }
        if (previousMinimumValue <= medianLocation &&
            medianLocation <= rangeOffsetForCurrentValue + frequencyPair.second) {
            result = ((previousValue + frequencyPair.first) / 2);
            break;
        }
        if (frequencyPair.second > 0) {
            previousValue = frequencyPair.first;
            previousMinimumValue = minimumValueOffset + rangeOffsetForCurrentValue;
            rangeOffsetForCurrentValue += frequencyPair.second;
        }
    }
    return result;
}

int FrequencyStatistics::calculateNumberOfSamples(FrequencySamples const& samples) {
    return accumulate(
        samples.cbegin(), samples.cend(), 0, [](int const partialResult, FrequencyPair const& frequencyPair) {
            return partialResult + (static_cast<int>(frequencyPair.second));
        });
}

}  // namespace alba
