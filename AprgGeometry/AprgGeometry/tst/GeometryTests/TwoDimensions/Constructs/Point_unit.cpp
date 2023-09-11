#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::TwoDimensions {

TEST(TwoDimensionsPointTest, PointsCanBeCreated) {
    Point const point(100, 200);
    EXPECT_EQ(100, point.getX());
    EXPECT_EQ(200, point.getY());
}

}  // namespace alba::TwoDimensions
