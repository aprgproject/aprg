#pragma once

#include <Statistics/DataStatistics.hpp>

#include <filesystem>  //>
#include <set>
#include <string>

namespace alba::AprgBitmap {

class AprgColorStatistics {
public:
    using OneDimensionStatistics = DataStatistics<1>;
    void gatherStatistics(std::filesystem::path const& filePath);
    void saveColorData(std::filesystem::path const& filePath);
    void saveColorStatistics(std::filesystem::path const& filePath);

private:
    std::multiset<double> colorIntensitySet;
    std::multiset<double> luma601Set;
    std::multiset<double> luma709Set;
    std::multiset<double> hueDegreesSet;
    std::multiset<double> saturationLightnessSet;
    std::multiset<double> lightnessSet;
    std::multiset<double> saturationValueSet;
    std::multiset<double> valueSet;
    OneDimensionStatistics::Samples colorIntensitySamples;
    OneDimensionStatistics::Samples saturationLightnessSamples;
    OneDimensionStatistics::Samples lightnessSamples;
    OneDimensionStatistics::Samples saturationValueSamples;
    OneDimensionStatistics::Samples valueSamples;
    OneDimensionStatistics::Samples luma601Samples;
    OneDimensionStatistics::Samples luma709Samples;
};

void gatherAndSaveColorStatistics(std::filesystem::path const& filePath);

}  // namespace alba::AprgBitmap
