#pragma once

#include <Audio/Audio.hpp>
#include <AudioManipulator/AudioManipulator.hpp>
#include <AudioManipulator/CommonTypes.hpp>
#include <AudioManipulator/NewSamplesBuilder.hpp>

namespace alba::AprgAudio {

double getSumInRange(Samples const& samples, int const startIndexIncluded, int const endIndexExcluded);
double getAverageOfSamples(Samples const& samples);
double getAverageInRange(Samples const& samples, int const startIndexIncluded, int const endIndexExcluded);
double getCommonMultiplierForDeltaSamples(
    Samples const& samples, int const startIndexIncluded, int const endIndexExcluded);
double getCommonMultiplierUsingSumAndNumberOfItems(double const sum, int const numberOfItems);

DoubleOptional compareDeltasAndGetDifference(
    Samples const& deltaSamples1, Samples const& deltaSamples2, double const multiplierToSample2,
    int const startOfDeltaSamples1, int const startOfDeltaSamples2, int const numberOfSamples);

void retrieveDeltas(Samples& deltaSamples, Samples const& pointerOfSampleToCheck, int const numberOfSamples);
void multiplyValueToAllSamples(Samples& samples, double const value);

void searchForBestSampleIndexes(
    SearchResultsDetails& replicateAndSearchIndexes, int const sampleIntervalForReplication,
    int const numberOfSamplesForReplication, int const numberOfSearchSamplesPerReplication,
    Samples const& samplesToReplicate, Samples const& samplesToSearch);

void searchAndTryToReplicateSamples(
    AudioInDouble& audioToChange, AudioInDouble const& audioToReplicate, AudioInDouble const& audioToSearch,
    int const channelIndexInAudioToChange, int const channelIndexInAudioToReplicate,
    int const channelIndexInAudioToSearch, bool const alwaysPutNewValue);

void searchAndTryToReplicate(
    std::string const& filePathForAudioToChange, std::string const& filePathForAudioToReplicate,
    std::string const& filePathForAudioToSearch, bool const alwaysPutNewValue);

}  // namespace alba::AprgAudio
