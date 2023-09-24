#pragma once

#include <filesystem>
#include <map>
#include <string>

namespace alba::AprgBitmap {

class AnimizeColor {
public:
    struct ColorDetails {
        int count;
        double newValue;
    };

    AnimizeColor();
    using ColorDataMap = std::map<double, ColorDetails>;
    using ValueAndColorDataPair = std::pair<double, ColorDetails>;
    [[nodiscard]] double getNewLightness(double const originalValue) const;
    [[nodiscard]] double getNewSaturation(double const originalValue) const;
    [[nodiscard]] uint32_t getNewColor(uint32_t const originalColor) const;
    void gatherStatistics(std::filesystem::path const& filePath);
    void calculateNewValues();
    void saveColorData(std::filesystem::path const& filePath);

private:
    [[nodiscard]] double getNewValue(ColorDataMap const& colorDataMap, double const originalValue) const;
    [[nodiscard]] bool isValueIncluded(double const value) const;
    void calculateNewValues(ColorDataMap& colorDataMap) const;
    void addCountToValue(ColorDataMap& colorDataMap, double const value);
    double m_lowestIncludedValue{0.1};
    double m_highestIncludedValue{0.9};
    ColorDataMap m_lightnessData;
    ColorDataMap m_saturationData;
};

void gatherAndSaveDataInAnimizeColor(std::filesystem::path const& filePath);

}  // namespace alba::AprgBitmap
