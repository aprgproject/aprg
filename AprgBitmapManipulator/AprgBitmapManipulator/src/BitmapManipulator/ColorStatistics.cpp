#include "ColorStatistics.hpp"

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapManipulator/ColorUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

using namespace alba::AprgBitmap::ColorUtilities;
using namespace std;
using namespace std::filesystem;

namespace alba::AprgBitmap {

void AprgColorStatistics::gatherStatistics(path const& filePath) {
    Bitmap const bitmap(filePath);
    BitmapSnippet const canvas(bitmap.getSnippetReadFromFileWholeBitmap());
    canvas.traverse([&](BitmapXY const&, uint32_t const color) {
        double const colorIntensity(calculateColorIntensityDecimal(color));
        double const luma601(calculateLuma601Decimal(color));
        double const luma709(calculateLuma709Decimal(color));
        colorIntensitySet.emplace(colorIntensity);
        luma601Set.emplace(luma601);
        luma709Set.emplace(luma709);
        HueSaturationLightnessData const hslData(convertColorToHueSaturationLightnessData(color));
        HueSaturationValueData const hsvData(convertColorToHueSaturationValueData(color));
        hueDegreesSet.emplace(hslData.hueDegrees);
        saturationLightnessSet.emplace(hslData.saturationLightnessDecimal);
        lightnessSet.emplace(hslData.lightnessDecimal);
        saturationValueSet.emplace(hsvData.saturationValueDecimal);
        valueSet.emplace(hsvData.valueDecimalOfColorMax);

        colorIntensitySamples.emplace_back(DataSampleInitializerList{colorIntensity});
        saturationLightnessSamples.emplace_back(DataSampleInitializerList{hslData.saturationLightnessDecimal});
        lightnessSamples.emplace_back(DataSampleInitializerList{hslData.lightnessDecimal});
        saturationValueSamples.emplace_back(DataSampleInitializerList{hsvData.saturationValueDecimal});
        valueSamples.emplace_back(DataSampleInitializerList{hsvData.valueDecimalOfColorMax});
        luma601Samples.emplace_back(DataSampleInitializerList{luma601});
        luma709Samples.emplace_back(DataSampleInitializerList{luma709});
    });
}

void AprgColorStatistics::saveColorData(path const& filePath) {
    ofstream colorDataFileStream(filePath);
    auto colorIntensityIterator(colorIntensitySet.cbegin());
    auto hueDegreesIterator(hueDegreesSet.cbegin());
    auto saturationLightnessIterator(saturationLightnessSet.cbegin());
    auto lightnessIterator(lightnessSet.cbegin());
    auto saturationValueIterator(saturationValueSet.cbegin());
    auto valueIterator(valueSet.cbegin());
    auto luma601Iterator(luma601Set.cbegin());
    auto luma709Iterator(luma709Set.cbegin());

    colorDataFileStream << "colorIntensity, "
                        << "hueDegreesDividedBy360, "
                        << "saturationLightness, "
                        << "lightness, "
                        << "saturationValueI, "
                        << "value, "
                        << "luma601, "
                        << "luma709"
                        << "\n";
    int count = 0;
    int const size = static_cast<int>(
        min(colorIntensitySet.size(),
            min(hueDegreesSet.size(),
                min(saturationLightnessSet.size(),
                    min(lightnessSet.size(), min(saturationValueSet.size(),
                                                 min(valueSet.size(), min(luma601Set.size(), luma601Set.size()))))))));
    while (count < size) {
        colorDataFileStream << *colorIntensityIterator++ << ", " << *hueDegreesIterator++ / 360 << ", "
                            << *saturationLightnessIterator++ << ", " << *lightnessIterator++ << ", "
                            << *saturationValueIterator++ << ", " << *valueIterator++ << ", " << *luma601Iterator++
                            << ", " << *luma709Iterator++ << "\n";
        ++count;
    }
}

void AprgColorStatistics::saveColorStatistics(path const& filePath) {
    ofstream statisticsFileStream(filePath);
    OneDimensionStatistics colorIntensityStatistics(colorIntensitySamples);
    OneDimensionStatistics saturationLightnessStatistics(saturationLightnessSamples);
    OneDimensionStatistics lightnessStatistics(lightnessSamples);
    OneDimensionStatistics saturationValueStatistics(saturationValueSamples);
    OneDimensionStatistics valueStatistics(valueSamples);
    OneDimensionStatistics luma601Statistics(luma601Samples);
    OneDimensionStatistics luma709Statistics(luma709Samples);

    statisticsFileStream << "Color Intensity Mean: " << colorIntensityStatistics.getMean()
                         << " StdDev: " << colorIntensityStatistics.getSampleStandardDeviation() << "\n";
    statisticsFileStream << "Saturation Lightness Mean: " << saturationLightnessStatistics.getMean()
                         << " StdDev: " << saturationLightnessStatistics.getSampleStandardDeviation() << "\n";
    statisticsFileStream << "Lightness Mean: " << lightnessStatistics.getMean()
                         << " StdDev: " << lightnessStatistics.getSampleStandardDeviation() << "\n";
    statisticsFileStream << "Saturation Value Mean: " << saturationValueStatistics.getMean()
                         << " StdDev: " << saturationValueStatistics.getSampleStandardDeviation() << "\n";
    statisticsFileStream << "Value Mean: " << valueStatistics.getMean()
                         << " StdDev: " << valueStatistics.getSampleStandardDeviation() << "\n";
    statisticsFileStream << "Luma 601 Mean: " << luma601Statistics.getMean()
                         << " StdDev: " << luma601Statistics.getSampleStandardDeviation() << "\n";
    statisticsFileStream << "Luma 709 Mean: " << luma709Statistics.getMean()
                         << " StdDev: " << luma709Statistics.getSampleStandardDeviation() << "\n";
}

void gatherAndSaveColorStatistics(path const& filePath) {
    AlbaLocalPathHandler const bitmapPathHandler(filePath);
    AlbaLocalPathHandler const colorDataPathHandler(
        bitmapPathHandler.getDirectory() / bitmapPathHandler.getFilenameOnly() / R"(_SortedColorData.csv)");
    AlbaLocalPathHandler const colorStatisticsPathHandler(
        bitmapPathHandler.getDirectory() / bitmapPathHandler.getFilenameOnly() / R"(_Statistics.txt)");

    AprgColorStatistics statistics;
    statistics.gatherStatistics(bitmapPathHandler.getPath());
    statistics.saveColorData(colorDataPathHandler.getPath());
    statistics.saveColorStatistics(colorStatisticsPathHandler.getPath());
}

}  // namespace alba::AprgBitmap
