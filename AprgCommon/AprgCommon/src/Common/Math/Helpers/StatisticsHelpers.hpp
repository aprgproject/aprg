#pragma once

#include <cstddef>

namespace alba::mathHelper {

double getCumulativeStandardDistributionApproximation(double const zValue);
double getInverseCumulativeStandardDistributionApproximation(double const probability, size_t const numberOfIterations);

}  // namespace alba::mathHelper
