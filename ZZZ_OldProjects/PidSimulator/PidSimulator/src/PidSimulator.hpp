#pragma once

#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <PidSimulatorConfiguration.hpp>

#include <vector>

namespace alba {

class PidSimulator {
public:
    PidSimulator(stringHelper::strings const& argumentsInMain);

    double calculatePid(double const input, double const target);
    void generateInput();
    void generateTriangleWavesForInput();
    void generateSineWavesForInput();
    void generateStepUpForInput();
    void generateStepDownForInput();
    void generateRandomForInput();
    void calculateAndGenerateOutputImage();
    double computeFromMachsModel(double const inputDemandSample, double const psuedoMaxTxPower, double& adjustedDemand);
    static double computeFromMachsModel1(
        double const inputDemandSample, double const psuedoMaxTxPower, double& adjustedDemand);
    static double computeFromMachsModel2(
        double const inputDemandSample, double const psuedoMaxTxPower, double& adjustedDemand);

private:
    void updateAllMaxWithBuffer(int& xLeftMax, int& xRightMax, int& yBottomMax, int& yTopMax);
    static void updateMaxWithBuffer(int& lowerValue, int& higherValue);
    void calculateMagnificationAndOffset(
        double const xLeftMax, double const xRightMax, double const yBottomMax, double const yTopMax,
        double const bitmapSizeInX, double const bitmapSizeInY);
    void updateMaxPoints(
        int const xCoordinate, int const yCoordinate, int& xLeftMax, int& xRightMax, int& yBottomMax, int& yTopMax);
    static void updateRightMax(int& xRightMax, int const xCoordinate);
    static void updateLeftMax(int& xLeftMax, int const xCoordinate);
    static void updateTopMax(int& yTopMax, int const yCoordinate);
    static void updateBottomMax(int& yBottomMax, int const yCoordinate);
    PidSimulatorConfiguration m_conf;
    double m_xMagnificationToGraph;
    double m_yMagnificationToGraph;
    unsigned int m_xOffsetToGraph;
    unsigned int m_yOffsetToGraph;
    double m_xGridInterval;
    double m_yGridInterval;
    std::vector<double> m_inputSample;
    AlbaUniformNonDeterministicRandomizer<int> m_randomizer;
};

}  // namespace alba
