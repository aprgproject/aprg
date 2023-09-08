#pragma once

#include <Common/Container/AlbaXYZ.hpp>

#include <vector>

namespace alba::ThreeDimensions {
using Point = AlbaXYZ<double>;
using Points = std::vector<Point>;
}  // namespace alba::ThreeDimensions
