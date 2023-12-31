#include <Geometry/TwoDimensions/Constructs/Polygon.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::TwoDimensions {
TEST(PolygonTest, PolygonCanBeCreated) { Polygon<3> const polygon{Point(1, 1), Point(2, 3), Point(0, 17)}; }
}  // namespace alba::TwoDimensions
