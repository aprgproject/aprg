#include "NewSamplesBuilder.hpp"

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba::AprgAudio {

NewSamplesBuilder::NewSamplesBuilder(Samples const& oldSamples) : m_oldSamples(oldSamples) {}

void NewSamplesBuilder::saveToNewSamples(
    Samples& newSamples, SamplesMergingDetails const& samplesMergingDetails, bool const alwaysPutNewValue) {
    int const sampleSize = static_cast<int>(min(samplesMergingDetails.size(), newSamples.size()));
    for (int i = 0; i < sampleSize; ++i) {
        SampleMergingDetails const& mergingDetails(samplesMergingDetails.at(i));
        if (mergingDetails.isChanged) {
            double const mergedValue(mergingDetails.totalValue / mergingDetails.weight);
            double const oldSample(m_oldSamples[i]);
            double& currentSample(newSamples[i]);
            double const newValue = mergedValue * 0.5 + oldSample * 0.5;
            if (alwaysPutNewValue ||
                getPositiveDelta(newValue, oldSample) < getPositiveDelta(currentSample, oldSample)) {
                currentSample = newValue;
            }
        }
    }
}

void NewSamplesBuilder::retrieveSampleMergingDetails(
    SamplesMergingDetails& samplesMergingDetails, SearchResultsDetails const& details, Samples const& searchSamples) {
    int const searchSamplesSize = static_cast<int>(searchSamples.size());
    for (SearchResultDetails const& detail : details) {
        double const midpoint = static_cast<double>(detail.numberOfSamples) / 2;
        for (int i = 0; i < detail.numberOfSamples && (i + detail.searchIndex) < searchSamplesSize; ++i) {
            double const distanceFromMidpoint = getPositiveDelta(midpoint, static_cast<double>(i));
            double const weightForPosition = 1 - distanceFromMidpoint / midpoint;
            double const searchSampleValue(searchSamples[i + detail.searchIndex]);
            SampleMergingDetails& newSampleDetail(samplesMergingDetails[i + detail.replicationIndex]);
            newSampleDetail.isChanged = true;
            newSampleDetail.totalValue += searchSampleValue * weightForPosition;
            newSampleDetail.weight += weightForPosition;
        }
    }
}

void NewSamplesBuilder::putSamplesBasedOnSearchResultAndSamples(
    Samples& samplesToChange, SearchResultsDetails const& searchResultDetails, Samples const& searchSamples,
    bool const alwaysPutNewValue) {
    SamplesMergingDetails samplesMergingDetails;
    retrieveSampleMergingDetails(samplesMergingDetails, searchResultDetails, searchSamples);
    saveToNewSamples(samplesToChange, samplesMergingDetails, alwaysPutNewValue);
}

}  // namespace alba::AprgAudio
