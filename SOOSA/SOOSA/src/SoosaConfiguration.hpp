#pragma once

#include <map>
#include <string>

namespace alba::soosa {

class SoosaConfiguration {
public:
    using BufferMap = std::map<std::string, std::string>;

    SoosaConfiguration();

    // Line model parameters
    [[nodiscard]] int getAcceptableLineDeviationForLineModelInPixels() const;
    [[nodiscard]] double getRemovalRatioForSquareErrorsInLineModel() const;
    [[nodiscard]] int getMinimumLineSamples() const;

    // Line and bar parameters
    [[nodiscard]] double getBitmapWidthToBarWidthMultiplier() const;
    [[nodiscard]] double getLineBarWidthSearchInitialBlackPointsValue() const;
    [[nodiscard]] double getLineBarWidthSearchAcceptedRunningBlackRatio() const;
    [[nodiscard]] double getAcceptableDistanceOverWidthRatioFromWidthMidpoint() const;
    [[nodiscard]] int getAcceptableMinimumDistanceFromWidthMidpoint() const;
    [[nodiscard]] double getAcceptableSdOverMeanDeviationForLine() const;
    [[nodiscard]] double getAcceptableSdOverMeanDeviationForBar() const;
    [[nodiscard]] double getRemovalRatioForLineAndBar() const;
    [[nodiscard]] double getInitialValueForMaximumDistanceBetweenBarHeights() const;
    [[nodiscard]] double getMultiplierForMaximumDistanceBetweenBarHeights() const;
    [[nodiscard]] double getAcceptableSdOverMeanDeviationForBarHeight() const;
    [[nodiscard]] double getRemovalRatioForBarHeight() const;

    // Choices related parameters
    [[nodiscard]] int getNumberOfChoices() const;
    [[nodiscard]] int getColorIntensityForWhite() const;
    [[nodiscard]] double getBarHeightToDiameterMultiplier() const;
    [[nodiscard]] double getMinimumPercentageOfBlackPixelsForAFilledCircle() const;

    void loadConfigurationFromFile(std::string const& filePath);
    void bufferNameAndValueString(std::string const& nameOfParameter, std::string const& valueString);
    void update();

private:
    void readNamesAndValuesFromFile(std::string const& filePath);

    // Line model parameters
    int m_acceptableLineDeviationForLineModelInPixels;
    double m_removalRatioForSquareErrorsInLineModel;
    int m_minimumLineSamples;

    // Line and bar parameters
    double m_bitmapWidthToBarWidthMultiplier;
    int m_lineBarWidthSearchInitialBlackPointsValue;
    double m_lineBarWidthSearchAcceptedRunningBlackRatio;
    double m_acceptableDistanceOverWidthRatioFromWidthMidpoint;
    double m_acceptableMinimumDistanceFromWidthMidpoint;
    double m_acceptableSdOverMeanDeviationForLine;
    double m_acceptableSdOverMeanDeviationForBar;
    double m_removalRatioForLineAndBar;
    double m_initialValueForMaximumDistanceBetweenBarHeights;
    double m_multiplierForMaximumDistanceBetweenBarHeights;
    double m_acceptableSdOverMeanDeviationForBarHeight;
    double m_removalRatioForBarHeight;

    // Choices related parameters
    int m_numberOfChoices;
    int m_colorIntensityForWhite;
    double m_barHeightToDiameterMultiplier;
    double m_minimumPercentageOfBlackPixelsForAFilledCircle;

    // Buffer
    BufferMap m_nameToValueStringMapBuffer;
};

}  // namespace alba
