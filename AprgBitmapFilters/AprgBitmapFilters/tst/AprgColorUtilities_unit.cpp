#include <AprgColorUtilities.hpp>

#include <gtest/gtest.h>


#include <Debug/AlbaDebug.hpp>

using namespace alba;
using namespace alba::ColorUtilities;
using namespace std;

TEST(ColorUtilitiesTest, CalculateColorPercentagesDataWorks)
{
    ColorPercentagesData data3(calculateColorPercentagesData(0xB2C368));

    EXPECT_DOUBLE_EQ(0.69803921568627447236, data3.redPercentage);
    EXPECT_DOUBLE_EQ(0.76470588235294112422, data3.greenPercentage);
    EXPECT_DOUBLE_EQ(0.40784313725490195512, data3.bluePercentage);
    EXPECT_DOUBLE_EQ(0.76470588235294112422, data3.colorPercentageMax);
    EXPECT_DOUBLE_EQ(0.40784313725490195512, data3.colorPercentageMin);
    EXPECT_DOUBLE_EQ(0.3568627450980391691, data3.deltaMaxMinPercentage);
}

TEST(ColorUtilitiesTest, CalculateHueDegreesWorks)
{
    double hueDegrees1(calculateHueDegrees(calculateColorPercentagesData(0x0)));
    double hueDegrees2(calculateHueDegrees(calculateColorPercentagesData(0xFFFFFF)));
    double hueDegrees3(calculateHueDegrees(calculateColorPercentagesData(0x83A96E)));

    EXPECT_DOUBLE_EQ(0, hueDegrees1);
    EXPECT_DOUBLE_EQ(0, hueDegrees2);    EXPECT_DOUBLE_EQ(98.644067796610187315, hueDegrees3);
}

TEST(ColorUtilitiesTest, CalculateColorIntensityDecimalWorks)
{
    double colorIntensityDecimal1(calculateColorIntensityDecimal(0x0));
    double colorIntensityDecimal2(calculateColorIntensityDecimal(0xFFFFFF));
    double colorIntensityDecimal3(calculateColorIntensityDecimal(0x3C534D));

    EXPECT_DOUBLE_EQ(0, colorIntensityDecimal1);
    EXPECT_DOUBLE_EQ(1, colorIntensityDecimal2);
    EXPECT_DOUBLE_EQ(0.28758169934640520626, colorIntensityDecimal3);
}

TEST(ColorUtilitiesTest, CalculateLuma601DecimalWorks)
{
    double luma1(calculateLuma601Decimal(0x0));
    double luma2(calculateLuma601Decimal(0xFFFFFF));
    double luma3(calculateLuma601Decimal(0x3C534D));

    EXPECT_DOUBLE_EQ(0, luma1);
    EXPECT_DOUBLE_EQ(1, luma2);
    EXPECT_DOUBLE_EQ(0.29583921568627452592, luma3);
}

TEST(ColorUtilitiesTest, CalculateLuma709DecimalWorks)
{
    double luma1(calculateLuma709Decimal(0x0));
    double luma2(calculateLuma709Decimal(0xFFFFFF));
    double luma3(calculateLuma709Decimal(0xADBEFC));

    EXPECT_DOUBLE_EQ(0, luma1);
    EXPECT_DOUBLE_EQ(1, luma2);
    EXPECT_DOUBLE_EQ(0.74847921568627451272, luma3);
}

TEST(ColorUtilitiesTest, CalculateSaturationColorIntensityDecimalWorks)
{
    double saturationColorIntensityDecimal1(calculateSaturationColorIntensityDecimal(0x0));
    double saturationColorIntensityDecimal2(calculateSaturationColorIntensityDecimal(0xFFFFFF));
    double saturationColorIntensityDecimal3(calculateSaturationColorIntensityDecimal(0xF9B88C));

    EXPECT_DOUBLE_EQ(0, saturationColorIntensityDecimal1);
    EXPECT_DOUBLE_EQ(0, saturationColorIntensityDecimal2);
    EXPECT_DOUBLE_EQ(0.26701570680628272658, saturationColorIntensityDecimal3);
    ALBA_PRECISION(20);
    ALBA_PRINT1(saturationColorIntensityDecimal3);
}

TEST(ColorUtilitiesTest, CreateHueSaturationLightnessDataWorks)
{
    HueSaturationLightnessData hslData(createHueSaturationLightnessData(1.1, 2.2, 3.3));
    EXPECT_DOUBLE_EQ(1.1, hslData.hueDegrees);
    EXPECT_DOUBLE_EQ(2.2, hslData.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(3.3, hslData.lightnessDecimal);
}

TEST(ColorUtilitiesTest, CreateHueSaturationValueDataWorks)
{
    HueSaturationValueData hsvData(createHueSaturationValueData(1.1, 2.2, 3));

    EXPECT_DOUBLE_EQ(1.1, hsvData.hueDegrees);
    EXPECT_DOUBLE_EQ(2.2, hsvData.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(3, hsvData.valueDecimalOfColorMax);
}

TEST(ColorUtilitiesTest, CombineRgbColorWorks)
{
    EXPECT_EQ(0x0u, combineRgbToColor(0x0, 0x0, 0x0));
    EXPECT_EQ(0x6A0000u, combineRgbToColor(0x6A, 0x0, 0x0));
    EXPECT_EQ(0x005A00u, combineRgbToColor(0x0, 0x5A, 0x0));
    EXPECT_EQ(0x0000CDu, combineRgbToColor(0x0, 0x0, 0xCD));
    EXPECT_EQ(0x6A5ACDu, combineRgbToColor(0x6A, 0x5A, 0xCD));
}

TEST(ColorUtilitiesTest, ConvertColorToHueSaturationLightnessDataWorks)
{
    HueSaturationLightnessData hslData1(convertColorToHueSaturationLightnessData(0x0));
    HueSaturationLightnessData hslData2(convertColorToHueSaturationLightnessData(0xFFFFFF));
    HueSaturationLightnessData hslData3(convertColorToHueSaturationLightnessData(0xA7E6ABu));

    EXPECT_DOUBLE_EQ(0, hslData1.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hslData1.saturationLightnessDecimal);    EXPECT_DOUBLE_EQ(0, hslData1.lightnessDecimal);
    EXPECT_DOUBLE_EQ(0, hslData2.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hslData2.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(1, hslData2.lightnessDecimal);
    EXPECT_DOUBLE_EQ(123.80952380952379599, hslData3.hueDegrees);
    EXPECT_DOUBLE_EQ(0.55752212389380539914, hslData3.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(0.77843137254901961786, hslData3.lightnessDecimal);
}

TEST(ColorUtilitiesTest, ConvertColorToHueSaturationValueDataWorks){
    HueSaturationValueData hsvData1(convertColorToHueSaturationValueData(0x0));
    HueSaturationValueData hsvData2(convertColorToHueSaturationValueData(0xFFFFFF));
    HueSaturationValueData hsvData3(convertColorToHueSaturationValueData(0xA7E6ABu));

    EXPECT_DOUBLE_EQ(0, hsvData1.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hsvData1.saturationValueDecimal);    EXPECT_DOUBLE_EQ(0, hsvData1.valueDecimalOfColorMax);
    EXPECT_DOUBLE_EQ(0, hsvData2.hueDegrees);
    EXPECT_DOUBLE_EQ(0, hsvData2.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(1, hsvData2.valueDecimalOfColorMax);
    EXPECT_DOUBLE_EQ(123.80952380952379599, hsvData3.hueDegrees);
    EXPECT_DOUBLE_EQ(0.27391304347826089804, hsvData3.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(0.90196078431372550543, hsvData3.valueDecimalOfColorMax);
}

TEST(ColorUtilitiesTest, ConvertHueSaturationLightnessDataToColorWorks){
    HueSaturationLightnessData hslData1(createHueSaturationLightnessData(0, 0, 0));
    HueSaturationLightnessData hslData2(createHueSaturationLightnessData(360, 1, 1));
    HueSaturationLightnessData hslData3(createHueSaturationLightnessData(123.80952380952379599, 0.55752212389380539914, 0.77843137254901961786));

    EXPECT_EQ(0x0u, convertHueSaturationLightnessDataToColor(hslData1));
    EXPECT_EQ(0xFFFFFFu, convertHueSaturationLightnessDataToColor(hslData2));    EXPECT_EQ(0xA7E6ABu, convertHueSaturationLightnessDataToColor(hslData3));
}

TEST(ColorUtilitiesTest, ConvertHueSaturationValueDataToColorWorks)
{
    HueSaturationValueData hsvData1(createHueSaturationValueData(0, 0, 0));
    HueSaturationValueData hsvData2(createHueSaturationValueData(360, 0, 1));
    HueSaturationValueData hsvData3(createHueSaturationValueData(123.80952380952379599, 0.27391304347826089804, 0.90196078431372550543));

    EXPECT_EQ(0x0u, convertHueSaturationValueDataToColor(hsvData1));
    EXPECT_EQ(0xFFFFFFu, convertHueSaturationValueDataToColor(hsvData2));
    EXPECT_EQ(0xA7E6ABu, convertHueSaturationValueDataToColor(hsvData3));
}

TEST(ColorUtilitiesTest, ConvertHslDataToHsvDataWorks)
{
    HueSaturationLightnessData hslData1(createHueSaturationLightnessData(0, 0, 0));
    HueSaturationLightnessData hslData2(createHueSaturationLightnessData(0, 0, 1));
    HueSaturationLightnessData hslData3(createHueSaturationLightnessData(123.80952380952379599, 0.55752212389380539914, 0.77843137254901961786));

    HueSaturationValueData expectedHsvData1(convertHslDataToHsvData(hslData1));
    HueSaturationValueData expectedHsvData2(convertHslDataToHsvData(hslData2));
    HueSaturationValueData expectedHsvData3(convertHslDataToHsvData(hslData3));

    EXPECT_DOUBLE_EQ(0, expectedHsvData1.hueDegrees);
    EXPECT_DOUBLE_EQ(0, expectedHsvData1.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(0, expectedHsvData1.valueDecimalOfColorMax);
    EXPECT_DOUBLE_EQ(0, expectedHsvData2.hueDegrees);
    EXPECT_DOUBLE_EQ(0, expectedHsvData2.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(1, expectedHsvData2.valueDecimalOfColorMax);
    EXPECT_DOUBLE_EQ(123.80952380952379599, expectedHsvData3.hueDegrees);
    EXPECT_DOUBLE_EQ(0.27391304347826089804, expectedHsvData3.saturationValueDecimal);
    EXPECT_DOUBLE_EQ(0.90196078431372550543, expectedHsvData3.valueDecimalOfColorMax);
}

TEST(ColorUtilitiesTest, ConvertHsvDataToHslDataWorks)
{
    HueSaturationValueData hsvData1(createHueSaturationValueData(0, 0, 0));
    HueSaturationValueData hsvData2(createHueSaturationValueData(0, 0, 1));
    HueSaturationValueData hsvData3(createHueSaturationValueData(123.80952380952379599, 0.27391304347826089804, 0.90196078431372550543));

    HueSaturationLightnessData expectedHslData1(convertHsvDataToHslData(hsvData1));
    HueSaturationLightnessData expectedHslData2(convertHsvDataToHslData(hsvData2));
    HueSaturationLightnessData expectedHslData3(convertHsvDataToHslData(hsvData3));

    EXPECT_DOUBLE_EQ(0, expectedHslData1.hueDegrees);
    EXPECT_DOUBLE_EQ(0, expectedHslData1.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(0, expectedHslData1.lightnessDecimal);
    EXPECT_DOUBLE_EQ(0, expectedHslData2.hueDegrees);
    EXPECT_DOUBLE_EQ(0, expectedHslData2.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(1, expectedHslData2.lightnessDecimal);
    EXPECT_DOUBLE_EQ(123.80952380952379599, expectedHslData3.hueDegrees);
    EXPECT_DOUBLE_EQ(0.55752212389380539914, expectedHslData3.saturationLightnessDecimal);
    EXPECT_DOUBLE_EQ(0.77843137254901961786, expectedHslData3.lightnessDecimal);
}

TEST(ColorUtilitiesTest, ExtractRedWorks)
{
    EXPECT_EQ(0xFFu, extractRed(0xFFFFFF));    EXPECT_EQ(0x0u, extractRed(0x0));
    EXPECT_EQ(0x32u, extractRed(0x32CD32));
}

TEST(ColorUtilitiesTest, ExtractGreenWorks)
{
    EXPECT_EQ(0xFFu, extractGreen(0xFFFFFF));
    EXPECT_EQ(0x0u, extractGreen(0x0));
    EXPECT_EQ(0xB3u, extractGreen(0x3CB371));
}

TEST(ColorUtilitiesTest, ExtractBlueWorks)
{
    EXPECT_EQ(0xFFu, extractBlue(0xFFFFFF));
    EXPECT_EQ(0x0u, extractBlue(0x0));
    EXPECT_EQ(0x57u, extractBlue(0x2E8B57));
}

