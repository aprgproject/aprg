#pragma once

#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <PidSimulatorConfiguration.hpp>

#include <vector>

namespace alba {

class PidSimulator {
public:
    explicit PidSimulator(stringHelper::strings const& argumentsInMain);
    [[nodiscard]] double calculatePid(double const input, double const target) const;

    double computeFromMachsModel(
        double const inputDemandSample, double const psuedoMaxTxPower, double& adjustedDemand) const;

    void generateInput();
    void generateTriangleWavesForInput();
    void generateSineWavesForInput();
    void generateStepUpForInput();
    void generateStepDownForInput();
    void generateRandomForInput();
    void calculateAndGenerateOutputImage();

    static double computeFromMachsModel1(
        double const inputDemandSample, double const psuedoMaxTxPower, double& adjustedDemand);

    static double computeFromMachsModel2(
        double const inputDemandSample, double const psuedoMaxTxPower, double& adjustedDemand);

private:
    void calculateMagnificationAndOffset(
        double const xLeftMax, double const xRightMax, double const yBottomMax, double const yTopMax,
        double const bitmapSizeInX, double const bitmapSizeInY);

    static void updateAllMaxWithBuffer(int& xLeftMax, int& xRightMax, int& yBottomMax, int& yTopMax);
    static void updateMaxWithBuffer(int& lowerValue, int& higherValue);

    static void updateMaxPoints(
        int const xCoordinate, int const yCoordinate, int& xLeftMax, int& xRightMax, int& yBottomMax, int& yTopMax);

    static void updateRightMax(int& xRightMax, int const xCoordinate);
    static void updateLeftMax(int& xLeftMax, int const xCoordinate);
    static void updateTopMax(int& yTopMax, int const yCoordinate);
    static void updateBottomMax(int& yBottomMax, int const yCoordinate);
    PidSimulatorConfiguration m_conf;
    double m_xMagnificationToGraph{0};
    double m_yMagnificationToGraph{0};
    unsigned int m_xOffsetToGraph{0};
    unsigned int m_yOffsetToGraph{0};
    double m_xGridInterval{0};
    double m_yGridInterval{0};
    std::vector<double> m_inputSample;
    AlbaUniformNonDeterministicRandomizer<int> m_randomizer;
};

}  // namespace alba
