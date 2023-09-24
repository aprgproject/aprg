#include "Utilities.hpp"

#include <AudioManipulator/AudioManipulator.hpp>
#include <AudioManipulator/NearestSamples.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <algorithm>
#include <numeric>

using namespace alba::mathHelper;
using namespace std;
using namespace std::filesystem;

namespace alba::AprgAudio {

void retrieveDeltas(Samples& deltaSamples, Samples const& pointerOfSampleToCheck, int const numberOfSamples) {
    deltaSamples.reserve(numberOfSamples);
    double previousValue(0);
    for (int i = 0; i < numberOfSamples; ++i) {
        deltaSamples.emplace_back(pointerOfSampleToCheck[i] - previousValue);
        previousValue = pointerOfSampleToCheck[i];
    }
}

void multiplyValueToAllSamples(Samples& samples, double const value) {
    for_each(samples.begin(), samples.end(), [value](double& sample) { sample *= value; });
}

void searchForBestSampleIndexes(
    SearchResultsDetails& replicateAndSearchIndexes, int const sampleIntervalForReplication,
    int const numberOfSamplesForReplication, int const numberOfSearchSamplesPerReplication,
    Samples const& samplesToReplicate, Samples const& samplesToSearch) {
    Samples deltaSamplesToReplicate;
    retrieveDeltas(deltaSamplesToReplicate, samplesToReplicate, static_cast<int>(samplesToReplicate.size()));

    Samples deltaSamplesToSearch;
    retrieveDeltas(deltaSamplesToSearch, samplesToSearch, static_cast<int>(samplesToSearch.size()));

    NearestSamples nearestSamplesToSearch(samplesToSearch);

    for (int replicationIndex = 0; replicationIndex < static_cast<int>(deltaSamplesToReplicate.size());
         replicationIndex += sampleIntervalForReplication) {
        int const numberOfSamplesToCompare =
            min(numberOfSamplesForReplication, static_cast<int>(deltaSamplesToReplicate.size() - replicationIndex));
        double const commonMultiplierInReplicate = getCommonMultiplierForDeltaSamples(
            deltaSamplesToReplicate, replicationIndex, replicationIndex + numberOfSamplesToCompare);
        Indexes const searchIndexes(nearestSamplesToSearch.getNearestSamplesIndexes(
            samplesToReplicate[replicationIndex], numberOfSearchSamplesPerReplication));
        bool isFirst(true);
        SearchResultDetails searchResult{false, replicationIndex, 0, 0, 0.0, 0.0};
        for (int const searchIndex : searchIndexes) {
            int const lastExcludedIndex = searchIndex + numberOfSamplesToCompare;
            if (lastExcludedIndex <= static_cast<int>(deltaSamplesToSearch.size())) {
                double const commonMultiplierInSearch =
                    getCommonMultiplierForDeltaSamples(deltaSamplesToSearch, searchIndex, lastExcludedIndex);
                double const multiplierForSearch = commonMultiplierInReplicate / commonMultiplierInSearch;
                DoubleOptional differenceOptional = compareDeltasAndGetDifference(
                    deltaSamplesToReplicate, deltaSamplesToSearch, multiplierForSearch, replicationIndex, searchIndex,
                    numberOfSamplesToCompare);
                if (differenceOptional) {
                    if (isFirst || searchResult.minDifference > differenceOptional.value()) {
                        searchResult.isSampleFound = true;
                        searchResult.searchIndex = searchIndex;
                        searchResult.numberOfSamples = numberOfSamplesToCompare;
                        searchResult.multiplierForSearch = multiplierForSearch;
                        searchResult.minDifference = differenceOptional.value();
                        isFirst = false;
                    }
                }
            }
        }
        replicateAndSearchIndexes.emplace_back(searchResult);
    }
}

void searchAndTryToReplicateSamples(
    AudioInDouble& audioToChange, AudioInDouble const& audioToReplicate, AudioInDouble const& audioToSearch,
    int const channelIndexInAudioToChange, int const channelIndexInAudioToReplicate,
    int const channelIndexInAudioToSearch, bool const alwaysPutNewValue) {
    SearchResultsDetails replicateAndSearchIndexes;
    Samples const& samplesToReplicate(audioToReplicate.getSamplesAtChannel(channelIndexInAudioToReplicate));
    Samples const& samplesToSearch(audioToSearch.getSamplesAtChannel(channelIndexInAudioToSearch));
    searchForBestSampleIndexes(replicateAndSearchIndexes, 24000, 48000, 100, samplesToReplicate, samplesToSearch);

    Samples& samplesToChange(audioToChange.getSamplesReferenceAtChannel(channelIndexInAudioToChange));
    NewSamplesBuilder newSamplesBuilder(samplesToReplicate);
    newSamplesBuilder.putSamplesBasedOnSearchResultAndSamples(
        samplesToChange, replicateAndSearchIndexes, samplesToSearch, alwaysPutNewValue);
}

void searchAndTryToReplicate(
    path const& filePathForAudioToChange, path const& filePathForAudioToReplicate, path const& filePathForAudioToSearch,
    bool const alwaysPutNewValue) {
    AudioManipulator const audioToReplicateManipulator(filePathForAudioToReplicate);
    AudioManipulator const audioToSearchManipulator(filePathForAudioToSearch);
    AudioManipulator audioToChangeManipulator(filePathForAudioToChange);
    AudioInDouble const& audioToReplicate(audioToReplicateManipulator.getAudio());
    AudioInDouble const& audioToSearch(audioToSearchManipulator.getAudio());
    AudioInDouble& audioToChange(audioToChangeManipulator.getAudioReference());

    int const numberOfChannels =
        max(max(audioToReplicate.getNumberOfChannels(), audioToSearch.getNumberOfChannels()),
            audioToChange.getNumberOfChannels());
    for (int i = 0; i < numberOfChannels; ++i) {
        searchAndTryToReplicateSamples(
            audioToChange, audioToReplicate, audioToSearch, clampHigherBound(i, audioToChange.getNumberOfChannels()),
            clampHigherBound(i, audioToReplicate.getNumberOfChannels()),
            clampHigherBound(i, audioToSearch.getNumberOfChannels()), alwaysPutNewValue);
    }
    audioToChangeManipulator.saveAudioIntoCurrentFile();
}

DoubleOptional compareDeltasAndGetDifference(
    Samples const& deltaSamples1, Samples const& deltaSamples2, double const multiplierToSample2,
    int const startOfDeltaSamples1, int const startOfDeltaSamples2, int const numberOfSamples) {
    constexpr double limitOfOneDifference = 2;
    DoubleOptional result;
    double currentValue1(0);
    double currentValue2(0);
    double totalDifference(0);
    bool hasLimitExceeded(false);

    for (int i = 0; i < numberOfSamples; i += 1) {
        double const deltaSample1 = deltaSamples1[startOfDeltaSamples1 + i];
        double const deltaSample2 = deltaSamples2[startOfDeltaSamples2 + i];
        currentValue1 += deltaSample1;
        currentValue2 += (deltaSample2 * multiplierToSample2);
        double const currentPositiveDifference = getAbsoluteValue(currentValue1 - currentValue2);
        if (limitOfOneDifference < currentPositiveDifference) {
            hasLimitExceeded = true;
            break;
        }
        totalDifference += currentPositiveDifference;
    }
    if (!hasLimitExceeded) {
        result = totalDifference / numberOfSamples;
    }
    return result;
}

double getSumInRange(Samples const& samples, int const startIndexIncluded, int const endIndexExcluded) {
    return accumulate(samples.cbegin() + startIndexIncluded, samples.cbegin() + endIndexExcluded, 0.0);
}

double getAverageOfSamples(Samples const& samples) {
    return accumulate(samples.cbegin(), samples.cend(), 0.0) / static_cast<double>(samples.size());
}

double getAverageInRange(Samples const& samples, int const startIndexIncluded, int const endIndexExcluded) {
    return accumulate(samples.cbegin() + startIndexIncluded, samples.cbegin() + endIndexExcluded, 0.0) /
           static_cast<double>(samples.size());
}

double getCommonMultiplierForDeltaSamples(
    Samples const& samples, int const startIndexIncluded, int const endIndexExcluded) {
    double multiplier = getAverageInRange(samples, startIndexIncluded, endIndexExcluded);
    if (isAlmostEqual(multiplier, 0.0)) {
        multiplier = 1;
    }
    return multiplier;
}

double getCommonMultiplierUsingSumAndNumberOfItems(double const sum, int const numberOfItems) {
    double multiplier = sum / numberOfItems;
    if (isAlmostEqual(multiplier, 0.0)) {
        multiplier = 1;
    }
    return multiplier;
}

}  // namespace alba::AprgAudio
