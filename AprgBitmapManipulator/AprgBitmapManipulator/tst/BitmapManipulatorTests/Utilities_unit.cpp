#include <BitmapManipulator/Utilities.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace alba::TwoDimensions;
using namespace std;

namespace alba::AprgBitmap {

TEST(UtilitiesTest, ConvertPointToBitmapXYWorks) {
    Point const point1;
    Point const point2(1.4, 1.4);
    Point const point3(1.5, 1.5);

    BitmapXY const bitmapXY1(convertPointToBitmapXY(point1));
    BitmapXY const bitmapXY2(convertPointToBitmapXY(point2));
    BitmapXY const bitmapXY3(convertPointToBitmapXY(point3));

    EXPECT_EQ(BitmapXY(0, 0), bitmapXY1);
    EXPECT_EQ(BitmapXY(1, 1), bitmapXY2);
    EXPECT_EQ(BitmapXY(2, 2), bitmapXY3);
}

TEST(UtilitiesTest, ConvertBitmapXYToPointWorks) {
    BitmapXY const bitmapXY1;
    BitmapXY const bitmapXY2(12, 34);

    Point const point1(convertBitmapXYToPoint(bitmapXY1));
    Point const point2(convertBitmapXYToPoint(bitmapXY2));

    EXPECT_EQ(Point(0, 0), point1);
    EXPECT_EQ(Point(12, 34), point2);
}

}  // namespace alba::AprgBitmap
