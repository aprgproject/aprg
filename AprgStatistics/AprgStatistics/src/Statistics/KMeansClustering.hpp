#pragma once

#include <Statistics/DataSample.hpp>
#include <Statistics/DataStatistics.hpp>

#include <algorithm>
#include <iterator>

namespace alba {

template <int DIMENSIONS>
class KMeansClustering {
public:
    using Statistics = DataStatistics<DIMENSIONS>;
    using StatisticsUtilities = DataStatisticsUtilities<DIMENSIONS>;
    using Sample = DataSample<DIMENSIONS>;
    using Samples = std::vector<Sample>;
    using GroupOfSamples = std::vector<Samples>;
    using SamplesGroupPair = std::pair<Sample, int>;
    using SamplesGroupPairs = std::vector<std::pair<Sample, int>>;
    KMeansClustering() = default;

    [[nodiscard]] GroupOfSamples getGroupOfSamplesUsingKMeans(int const numberOfGroups) const {
        SamplesGroupPairs samplesGroupPairs(calculateInitialSamplesGroupPairsFromSavedSamples(numberOfGroups));
        bool isSamplesGroupPairsChanged(true);
        while (isSamplesGroupPairsChanged) {
            isSamplesGroupPairsChanged = false;
            GroupOfSamples const groupOfSamples(
                calculateGroupOfSamplesFromSamplesGroupPairs(samplesGroupPairs, numberOfGroups));
            Samples meanForEachGroup(calculateMeanForEachGroup(groupOfSamples));

            for (SamplesGroupPair& samplesGroupPair : samplesGroupPairs) {
                int nearestGroup(0);
                double nearestDistance(0);
                for (int groupIndex = 0; groupIndex < numberOfGroups; ++groupIndex) {
                    double const currentDistance(
                        StatisticsUtilities::calculateDistance(samplesGroupPair.first, meanForEachGroup[groupIndex]));
                    if (groupIndex == 0 || nearestDistance > currentDistance) {
                        nearestGroup = groupIndex;
                        nearestDistance = currentDistance;
                    }
                }
                isSamplesGroupPairsChanged = isSamplesGroupPairsChanged || (nearestGroup != samplesGroupPair.second);
                samplesGroupPair.second = nearestGroup;
            }
        }
        return calculateGroupOfSamplesFromSamplesGroupPairs(samplesGroupPairs, numberOfGroups);
    }

    [[nodiscard]] Samples getSamples() const { return m_samples; }
    void clear() { m_samples.clear(); }
    void addSample(Sample const& sample) { m_samples.emplace_back(sample); }

    void addSamples(Samples const& samples) {
        m_samples.reserve(m_samples.size() + samples.size());
        std::copy(samples.cbegin(), samples.cend(), std::back_inserter(m_samples));
    }

    Samples& getSamplesReference() { return m_samples; }

private:
    [[nodiscard]] GroupOfSamples calculateGroupOfSamplesFromSamplesGroupPairs(
        SamplesGroupPairs const& samplesGroupPairs, int const numberOfGroups) const {
        GroupOfSamples result;
        for (int groupIndex = 0; groupIndex < numberOfGroups; ++groupIndex) {
            result.emplace_back();
        }
        for (SamplesGroupPair const& samplesGroupPair : samplesGroupPairs) {
            result[samplesGroupPair.second].emplace_back(samplesGroupPair.first);
        }
        return result;
    }

    [[nodiscard]] Samples calculateMeanForEachGroup(GroupOfSamples const& groupOfSamples) const {
        Samples meanForEachGroup;
        for (int groupIndex = 0; groupIndex < static_cast<int>(groupOfSamples.size()); ++groupIndex) {
            Statistics statistics(groupOfSamples[groupIndex]);
            meanForEachGroup.emplace_back(statistics.getMean());
        }
        return meanForEachGroup;
    }

    [[nodiscard]] SamplesGroupPairs calculateInitialSamplesGroupPairsFromSavedSamples(int const numberOfGroups) const {
        SamplesGroupPairs result;
        int count(0);
        int const numberSamplesPerGroup((m_samples.size() / numberOfGroups) + 1);
        result.reserve(m_samples.size());
        transform(m_samples.cbegin(), m_samples.cend(), back_inserter(result), [&](Sample const& sample) {
            return SamplesGroupPair(sample, count++ / numberSamplesPerGroup);
        });
        return result;
    }

    Samples m_samples;
};

}  // namespace alba
