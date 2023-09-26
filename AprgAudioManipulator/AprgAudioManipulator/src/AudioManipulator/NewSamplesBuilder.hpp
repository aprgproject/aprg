#pragma once

#include <AudioManipulator/CommonTypes.hpp>

#include <map>

namespace alba::AprgAudio {

class NewSamplesBuilder {
public:
    struct SampleMergingDetails {
        SampleMergingDetails() = default;
        bool isChanged{false};
        double totalValue{0};
        double weight{0};
    };

    using SamplesMergingDetails = std::map<int, SampleMergingDetails>;
    explicit NewSamplesBuilder(Samples const& oldSamples);

    void putSamplesBasedOnSearchResultAndSamples(
        Samples& samplesToChange, SearchResultsDetails const& details, Samples const& searchSamples,
        bool const alwaysPutNewValue);

private:
    void saveToNewSamples(
        Samples& newSamples, SamplesMergingDetails const& samplesMergingDetails, bool const alwaysPutNewValue);

    static void retrieveSampleMergingDetails(
        SamplesMergingDetails& samplesMergingDetails, SearchResultsDetails const& details,
        Samples const& searchSamples);

    Samples const& m_oldSamples;
};

}  // namespace alba::AprgAudio
