#pragma once

#include <map>
#include <string>

namespace alba::AprgBitmap {

void gatherAndSaveDataInAnimizeColor(std::string const& bitmapPath);

class AnimizeColor {
public:
    AnimizeColor();
    struct ColorDetails {
        int count;
        double newValue;
    };
    using ColorDataMap = std::map<double, ColorDetails>;
    using ValueAndColorDataPair = std::pair<double, ColorDetails>;

    [[nodiscard]] uint32_t getNewColor(uint32_t const originalColor) const;
    [[nodiscard]] double getNewLightness(double const originalValue) const;
    [[nodiscard]] double getNewSaturation(double const originalValue) const;
    void gatherStatistics(std::string const& bitmapPath);
    void calculateNewValues();
    void saveColorData(std::string const& path);

private:
    [[nodiscard]] bool isValueIncluded(double const value) const;
    void addCountToValue(ColorDataMap& colorDataMap, double const value);
    void calculateNewValues(ColorDataMap& colorDataMap);
    [[nodiscard]] double getNewValue(ColorDataMap const& colorDataMap, double const originalValue) const;
    double m_lowestIncludedValue{0.1};
    double m_highestIncludedValue{0.9};
    ColorDataMap m_lightnessData;
    ColorDataMap m_saturationData;
};

}  // namespace alba::AprgBitmap
