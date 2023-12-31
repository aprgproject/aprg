#include <Geometry/TwoDimensions/Constructs/Limacon.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::TwoDimensions {

TEST(LimaconTest, ConstructionWorks) { Limacon(1, 1, LimaconTrigonometricFunctionType::Sine); }

TEST(LimaconTest, EqualityOperatorWorks) {
    EXPECT_TRUE(
        Limacon(1, 1, LimaconTrigonometricFunctionType::Sine) == Limacon(1, 1, LimaconTrigonometricFunctionType::Sine));
    EXPECT_FALSE(
        Limacon(1, 1, LimaconTrigonometricFunctionType::Sine) == Limacon(2, 1, LimaconTrigonometricFunctionType::Sine));
    EXPECT_FALSE(
        Limacon(1, 1, LimaconTrigonometricFunctionType::Sine) == Limacon(1, 2, LimaconTrigonometricFunctionType::Sine));
    EXPECT_FALSE(
        Limacon(1, 1, LimaconTrigonometricFunctionType::Sine) ==
        Limacon(1, 1, LimaconTrigonometricFunctionType::Cosine));
}

TEST(LimaconTest, NonEqualityOperatorWorks) {
    EXPECT_FALSE(
        Limacon(1, 1, LimaconTrigonometricFunctionType::Sine) != Limacon(1, 1, LimaconTrigonometricFunctionType::Sine));
    EXPECT_TRUE(
        Limacon(1, 1, LimaconTrigonometricFunctionType::Sine) != Limacon(2, 1, LimaconTrigonometricFunctionType::Sine));
    EXPECT_TRUE(
        Limacon(1, 1, LimaconTrigonometricFunctionType::Sine) != Limacon(1, 2, LimaconTrigonometricFunctionType::Sine));
    EXPECT_TRUE(
        Limacon(1, 1, LimaconTrigonometricFunctionType::Sine) !=
        Limacon(1, 1, LimaconTrigonometricFunctionType::Cosine));
}

TEST(LimaconTest, CalculateThetaFromRadiusWorks) {
    Limacon const limacon(10, 13, LimaconTrigonometricFunctionType::Cosine);

    EXPECT_DOUBLE_EQ(90, limacon.calculateThetaFromRadius(10).getDegrees());
    EXPECT_DOUBLE_EQ(57.421029607195877, limacon.calculateThetaFromRadius(17).getDegrees());
    EXPECT_DOUBLE_EQ(0, limacon.calculateThetaFromRadius(23).getDegrees());
}

TEST(LimaconTest, GetTrigonometricFunctionTypeWorks) {
    Limacon const limacon(10, 13, LimaconTrigonometricFunctionType::Cosine);

    EXPECT_EQ(LimaconTrigonometricFunctionType::Cosine, limacon.getTrigonometricFunctionType());
}

TEST(LimaconTest, GetLimaconTypeWorks) {
    Limacon const limacon1(1, 2, LimaconTrigonometricFunctionType::Cosine);
    Limacon const limacon2(1, 1, LimaconTrigonometricFunctionType::Cosine);
    Limacon const limacon3(3, 2, LimaconTrigonometricFunctionType::Cosine);
    Limacon const limacon4(2, 1, LimaconTrigonometricFunctionType::Cosine);

    EXPECT_EQ(LimaconType::WithALoop, limacon1.getLimaconType());
    EXPECT_EQ(LimaconType::Cardioid, limacon2.getLimaconType());
    EXPECT_EQ(LimaconType::WithADent, limacon3.getLimaconType());
    EXPECT_EQ(LimaconType::Convex, limacon4.getLimaconType());
}

TEST(LimaconTest, GetPointsForShapeWorks) {
    Limacon const limacon(10, 13, LimaconTrigonometricFunctionType::Cosine);

    Points points(limacon.getPointsForShape(AlbaAngle(AngleUnitType::Degrees, 90)));
    ASSERT_EQ(4U, points.size());
    EXPECT_EQ(Point(23, 0), points[0]);
    EXPECT_EQ(Point(0, 10), points[1]);
    EXPECT_EQ(Point(3, 0), points[2]);
    EXPECT_EQ(Point(0, -10), points[3]);
}

TEST(LimaconTest, GetAValueWorks) {
    Limacon const limacon(10, 13, LimaconTrigonometricFunctionType::Cosine);

    EXPECT_DOUBLE_EQ(10, limacon.getAValue());
}

TEST(LimaconTest, GetBValueWorks) {
    Limacon const limacon(10, 13, LimaconTrigonometricFunctionType::Cosine);

    EXPECT_DOUBLE_EQ(13, limacon.getBValue());
}

TEST(LimaconTest, CalculateRadiusFromThetaWorks) {
    Limacon const limacon(10, 13, LimaconTrigonometricFunctionType::Cosine);

    EXPECT_DOUBLE_EQ(10, limacon.calculateRadiusFromTheta(AlbaAngle(AngleUnitType::Degrees, 90)));
    EXPECT_DOUBLE_EQ(-3, limacon.calculateRadiusFromTheta(AlbaAngle(AngleUnitType::Degrees, 180)));
    EXPECT_DOUBLE_EQ(10, limacon.calculateRadiusFromTheta(AlbaAngle(AngleUnitType::Degrees, 270)));
    EXPECT_DOUBLE_EQ(23, limacon.calculateRadiusFromTheta(AlbaAngle(AngleUnitType::Degrees, 360)));
}

}  // namespace alba::TwoDimensions
