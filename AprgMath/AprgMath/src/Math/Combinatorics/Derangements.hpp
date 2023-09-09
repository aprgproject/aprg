#pragma once

#include <Math/Types.hpp>

namespace alba::math {
UnsignedInteger getNumberOfDerangements(UnsignedInteger const n);
UnsignedInteger getNumberOfDerangementsApproximation(UnsignedInteger const n);
double getDerangementsProbability(UnsignedInteger const n);
}  // namespace alba::math
