#include <Geometry/TwoDimensions/Constructs/Triangle.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

namespace alba::TwoDimensions {

TEST(TriangleTest, TriangleCanBeCreated) { Triangle const triangle(Point(1, 1), Point(2, 3), Point(0, 17)); }

TEST(TriangleTest, GetLengthOfSidesAreCorrect) {
    Triangle const triangle(Point(0, 0), Point(0, 4), Point(4, 0));
    array<double, 3> lengthOfSides(triangle.getLengthOfSides());

    EXPECT_DOUBLE_EQ(4, lengthOfSides[0]);
    EXPECT_DOUBLE_EQ(5.6568542494923806, lengthOfSides[1]);
    EXPECT_DOUBLE_EQ(4, lengthOfSides[2]);
}

TEST(TriangleTest, GetAnglesAreCorrect) {
    Triangle const triangle(Point(0, 0), Point(0, 4), Point(4, 0));
    AlbaAngles angles(triangle.getAnglesAtVertices());

    ASSERT_EQ(3U, angles.size());
    EXPECT_DOUBLE_EQ(90, angles[0].getDegrees());
    EXPECT_DOUBLE_EQ(45, angles[1].getDegrees());
    EXPECT_DOUBLE_EQ(45, angles[2].getDegrees());
}

TEST(TriangleTest, GetSumOfAnglesIsCorrect) {
    Triangle const triangle(Point(0, 0), Point(0, 4), Point(4, 0));

    EXPECT_DOUBLE_EQ(180, triangle.getSumOfAngles().getDegrees());
}

TEST(TriangleTest, IsEquilateralWorks) {
    Triangle const regularTriangle(Point(1, 0), Point(-1, 0), Point(0, sqrt(3)));
    Triangle const nonRegularTriangle(Point(0, 0), Point(0, 4), Point(4, 0));

    EXPECT_TRUE(regularTriangle.isEquilateral());
    EXPECT_FALSE(nonRegularTriangle.isEquilateral());
}

TEST(TriangleTest, IsEquiangularWorksCorrect) {
    Triangle const regularTriangle(Point(1, 0), Point(-1, 0), Point(0, sqrt(3)));
    Triangle const nonRegularTriangle(Point(0, 0), Point(0, 4), Point(4, 0));

    EXPECT_TRUE(regularTriangle.isEquiangular());
    EXPECT_FALSE(nonRegularTriangle.isEquiangular());
}

TEST(TriangleTest, IsRegularWorksCorrect) {
    Triangle const regularTriangle(Point(1, 0), Point(-1, 0), Point(0, sqrt(3)));
    Triangle const nonRegularTriangle(Point(0, 0), Point(0, 4), Point(4, 0));

    EXPECT_TRUE(regularTriangle.isRegular());
    EXPECT_FALSE(nonRegularTriangle.isRegular());
}

TEST(TriangleTest, GetPointsWorks) {
    Triangle const triangle(Point(0, 0), Point(3, 3), Point(0, 6));
    Points points(triangle.getPoints(1));

    ASSERT_EQ(12U, points.size());
    EXPECT_EQ(Point(0, 0), points[0]);
    EXPECT_EQ(Point(1, 1), points[1]);
    EXPECT_EQ(Point(2, 2), points[2]);
    EXPECT_EQ(Point(3, 3), points[3]);
    EXPECT_EQ(Point(2, 4), points[4]);
    EXPECT_EQ(Point(1, 5), points[5]);
    EXPECT_EQ(Point(0, 6), points[6]);
    EXPECT_EQ(Point(0, 5), points[7]);
    EXPECT_EQ(Point(0, 4), points[8]);
    EXPECT_EQ(Point(0, 3), points[9]);
    EXPECT_EQ(Point(0, 2), points[10]);
    EXPECT_EQ(Point(0, 1), points[11]);
}

TEST(TriangleTest, IsIsocelesWorksCorrect) {
    Triangle const regularTriangle(Point(1, 0), Point(-1, 0), Point(0, sqrt(3)));
    Triangle const isocelesTriangle(Point(0, 0), Point(0, 4), Point(4, 0));
    Triangle const nonIsocelesTriangle(Point(0, 0), Point(0, 4), Point(5, 0));

    EXPECT_TRUE(regularTriangle.isIsoceles());
    EXPECT_TRUE(isocelesTriangle.isIsoceles());
    EXPECT_FALSE(nonIsocelesTriangle.isIsoceles());
}

TEST(TriangleTest, IsRightTriangleWorksCorrect) {
    Triangle const regularTriangle(Point(1, 0), Point(-1, 0), Point(0, sqrt(3)));
    Triangle const rightTriangle(Point(0, 0), Point(0, 4), Point(4, 0));

    EXPECT_FALSE(regularTriangle.isRightTriangle());
    EXPECT_TRUE(rightTriangle.isRightTriangle());
}

}  // namespace alba::TwoDimensions
