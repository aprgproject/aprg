#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>

namespace alba::TwoDimensions {

struct PolarCoordinate {
    double radius{};
    AlbaAngle angle;
};

}  // namespace alba::TwoDimensions
