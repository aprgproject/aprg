#pragma once

#include <Math/Types.hpp>

namespace alba::math {
double getDerangementsProbability(UnsignedInteger const n);
UnsignedInteger getNumberOfDerangements(UnsignedInteger const n);
UnsignedInteger getNumberOfDerangementsApproximation(UnsignedInteger const n);
}  // namespace alba::math
