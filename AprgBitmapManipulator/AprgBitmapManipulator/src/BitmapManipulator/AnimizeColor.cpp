#include "AnimizeColor.hpp"

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapManipulator/ColorUtilities.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

using namespace alba::AprgBitmap;
using namespace alba::AprgBitmap::ColorUtilities;
using namespace std;
using namespace std::filesystem;

namespace alba::AprgBitmap {

uint32_t AnimizeColor::getNewColor(uint32_t const originalColor) const {
    HueSaturationLightnessData newHslData(convertColorToHueSaturationLightnessData(originalColor));
    newHslData.lightnessDecimal = getNewLightness(newHslData.lightnessDecimal);
    newHslData.saturationLightnessDecimal = getNewSaturation(newHslData.saturationLightnessDecimal);
    return convertHueSaturationLightnessDataToColor(newHslData);
}

double AnimizeColor::getNewLightness(double const originalValue) const {
    return getNewValue(m_lightnessData, originalValue);
}

double AnimizeColor::getNewSaturation(double const originalValue) const {
    return getNewValue(m_saturationData, originalValue);
}

void AnimizeColor::gatherStatistics(path const& filePath) {
    Bitmap const bitmap(filePath);
    BitmapSnippet const canvas(bitmap.getSnippetReadFromFileWholeBitmap());
    canvas.traverse([&](BitmapXY const&, int const color) {
        HueSaturationLightnessData const hslData(convertColorToHueSaturationLightnessData(color));
        addCountToValue(m_lightnessData, hslData.lightnessDecimal);
        addCountToValue(m_saturationData, hslData.saturationLightnessDecimal);
    });
}

void AnimizeColor::calculateNewValues() {
    calculateNewValues(m_lightnessData);
    calculateNewValues(m_saturationData);
}

void AnimizeColor::saveColorData(path const& filePath) {
    ofstream colorDataFileStream(filePath);

    colorDataFileStream << "lightness, newLightness\n";
    for (ValueAndColorDataPair const lightnessCountPair : m_lightnessData) {
        colorDataFileStream << lightnessCountPair.first << ", " << lightnessCountPair.second.newValue << "\n";
        /*for(int i=0; i<lightnessCountPair.second.count; i++)
        {
            colorDataFileStream << lightnessCountPair.first
                                << ", " << lightnessCountPair.second.newLightness
                                << "\n";
        }*/
    }
}

double AnimizeColor::getNewValue(ColorDataMap const& colorDataMap, double const originalValue) const {
    double newValue = originalValue;
    if (isValueIncluded(originalValue)) {
        if (colorDataMap.find(originalValue) != colorDataMap.cend()) {
            newValue = colorDataMap.at(originalValue).newValue;
        } else {
            pair<ColorDataMap::const_iterator, ColorDataMap::const_iterator> const iterators =
                containerHelper::getLowerAndUpperConstIteratorsInMap(colorDataMap, originalValue);
            auto itLower(iterators.first);
            auto itUpper(iterators.second);
            double const deltaX = itUpper->first - itLower->first;
            double const deltaY = itUpper->second.newValue - itLower->second.newValue;
            double const deltaXToInterpolate = originalValue - itLower->first;
            double const deltaYInterpolated = deltaXToInterpolate / deltaX * deltaY;
            newValue = itLower->second.newValue + deltaYInterpolated;
        }
    }
    return newValue;
}

bool AnimizeColor::isValueIncluded(double const value) const {
    return value >= m_lowestIncludedValue && value <= m_highestIncludedValue;
}

void AnimizeColor::calculateNewValues(ColorDataMap& colorDataMap) const {
    int totalCount = accumulate(
        colorDataMap.cbegin(), colorDataMap.cend(), 0,
        [](int const partialResult, auto const& colorDataPair) { return partialResult + colorDataPair.second.count; });
    int partialCount = 0;
    double const diffOfHighestAndLowestValue = m_highestIncludedValue - m_lowestIncludedValue;
    for (auto& colorDataPair : colorDataMap) {
        int const currentCount = colorDataPair.second.count;
        colorDataPair.second.newValue =
            (((static_cast<double>(currentCount) / 2) + partialCount) / totalCount * diffOfHighestAndLowestValue) +
            m_lowestIncludedValue;
        partialCount += currentCount;
    }
}

void AnimizeColor::addCountToValue(ColorDataMap& colorDataMap, double const value) {
    if (isValueIncluded(value)) {
        if (colorDataMap.find(value) == colorDataMap.cend()) {
            ColorDetails details{};
            details.count = 1;
            colorDataMap.emplace(value, details);
        } else {
            colorDataMap.at(value).count++;
        }
    }
}

void gatherAndSaveDataInAnimizeColor(path const& filePath) {
    AlbaLocalPathHandler const bitmapPathHandler(filePath);
    AlbaLocalPathHandler const colorDataPathHandler(
        bitmapPathHandler.getDirectory() / bitmapPathHandler.getFilenameOnly() / R"(_AnimizeColorData.csv)");

    AnimizeColor statistics;
    statistics.gatherStatistics(bitmapPathHandler.getPath());
    statistics.calculateNewValues();
    statistics.saveColorData(colorDataPathHandler.getPath());
}

AnimizeColor::AnimizeColor() = default;

}  // namespace alba::AprgBitmap
