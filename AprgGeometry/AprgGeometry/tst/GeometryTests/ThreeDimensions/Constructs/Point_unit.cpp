#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

#include <gtest/gtest.h>

using namespace alba::ThreeDimensions;
using namespace std;

namespace alba::ThreeDimensions {

TEST(ThreeDimensionsPointTest, PointsCanBeCreated) {
    Point const point(100, 200, 300);
    EXPECT_EQ(100, point.getX());
    EXPECT_EQ(200, point.getY());
    EXPECT_EQ(300, point.getZ());
}

}  // namespace alba::ThreeDimensions
