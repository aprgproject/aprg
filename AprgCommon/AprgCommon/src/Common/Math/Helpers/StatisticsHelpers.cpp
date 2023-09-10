#include "StatisticsHelpers.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

using namespace std;

namespace alba::mathHelper {

double getCumulativeStandardDistributionApproximation(double const zValue) {
    return 0.5 * erfc(-zValue * pow(0.5, 0.5));
}

double getInverseCumulativeStandardDistributionApproximation(
    double const probability, size_t const numberOfIterations) {
    double lowestZ = -10;
    double highestZ = 10;
    double zValue(0);
    for (size_t iterationCount = 0; iterationCount < numberOfIterations; ++iterationCount) {
        auto middleZ = getAverage<double>(lowestZ, highestZ);
        double const probabilityLowest = getCumulativeStandardDistributionApproximation(lowestZ);
        double const probabilityMiddle = getCumulativeStandardDistributionApproximation(middleZ);
        double const probabilityHighest = getCumulativeStandardDistributionApproximation(highestZ);
        if (isAlmostEqual(probability, probabilityLowest)) {
            zValue = lowestZ;
            break;
        }
        if (isAlmostEqual(probability, probabilityMiddle)) {
            zValue = middleZ;
            break;
        }
        if (isAlmostEqual(probability, probabilityHighest)) {
            zValue = highestZ;
            break;
        }
        if (probability > probabilityLowest && probability < probabilityMiddle) {
            highestZ = middleZ;
            zValue = getAverage<double>(lowestZ, middleZ);
        } else if (probability > probabilityMiddle && probability < probabilityHighest) {
            lowestZ = middleZ;
            zValue = getAverage<double>(middleZ, highestZ);
        }
    }
    return zValue;
}

}  // namespace alba::mathHelper
