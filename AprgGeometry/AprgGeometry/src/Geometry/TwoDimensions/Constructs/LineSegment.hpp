#pragma once

#include <Geometry/TwoDimensions/Constructs/Point.hpp>

namespace alba::TwoDimensions {
using LineSegment = std::pair<Point, Point>;
using LineSegments = std::vector<LineSegment>;
}  // namespace alba::TwoDimensions
