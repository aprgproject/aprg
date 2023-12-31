#include <Geometry/TwoDimensions/Constructs/Parabola.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::TwoDimensions {

TEST(ParabolaTest, ParabolaCanBeCreated) {
    Parabola<ParabolaOrientation::PolynomialX>{1, 2, 3};
    Parabola<ParabolaOrientation::PolynomialY>{1, 2, 3};
}

TEST(ParabolaTest, GetPointsWorksForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{1, 2, 3};
    Points points(parabola.getPoints(-2, 2, 1));

    ASSERT_EQ(5U, points.size());
    EXPECT_EQ(Point(-2, 3), points[0]);
    EXPECT_EQ(Point(-1, 2), points[1]);
    EXPECT_EQ(Point(0, 3), points[2]);
    EXPECT_EQ(Point(1, 6), points[3]);
    EXPECT_EQ(Point(2, 11), points[4]);
}

TEST(ParabolaTest, GetPointsWorksForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola{1, 2, 3};
    Points points(parabola.getPoints(-2, 2, 1));

    ASSERT_EQ(5U, points.size());
    EXPECT_EQ(Point(3, -2), points[0]);
    EXPECT_EQ(Point(2, -1), points[1]);
    EXPECT_EQ(Point(3, 0), points[2]);
    EXPECT_EQ(Point(6, 1), points[3]);
    EXPECT_EQ(Point(11, 2), points[4]);
}

TEST(ParabolaTest, GetPointsWorksWhenBoundariesAreReversedForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{1, 2, 3};
    Points points(parabola.getPoints(2, -2, 1));

    ASSERT_EQ(5U, points.size());
    EXPECT_EQ(Point(2, 11), points[0]);
    EXPECT_EQ(Point(1, 6), points[1]);
    EXPECT_EQ(Point(0, 3), points[2]);
    EXPECT_EQ(Point(-1, 2), points[3]);
    EXPECT_EQ(Point(-2, 3), points[4]);
}

TEST(ParabolaTest, GetSlopeIsCorrectForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{1, 2, 3};

    EXPECT_DOUBLE_EQ(-198, parabola.getSlopeAt(-100));
    EXPECT_DOUBLE_EQ(-18, parabola.getSlopeAt(-10));
    EXPECT_DOUBLE_EQ(0, parabola.getSlopeAt(-1));
    EXPECT_DOUBLE_EQ(2, parabola.getSlopeAt(0));
    EXPECT_DOUBLE_EQ(4, parabola.getSlopeAt(1));
    EXPECT_DOUBLE_EQ(22, parabola.getSlopeAt(10));
    EXPECT_DOUBLE_EQ(202, parabola.getSlopeAt(100));
}

TEST(ParabolaTest, GetSlopeIsCorrectForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola{1, 2, 3};

    EXPECT_DOUBLE_EQ(-0.055555555555555552, parabola.getSlopeAt(-10));
    EXPECT_DOUBLE_EQ(0.5, parabola.getSlopeAt(0));
    EXPECT_DOUBLE_EQ(0.045454545454545456, parabola.getSlopeAt(10));
}

TEST(ParabolaTest, GetDirectrixWorksForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{-0.2, -2, -4};

    EXPECT_EQ(Line(Point(0, 2.25), Point(1, 2.25)), parabola.getDirectrix());
}

TEST(ParabolaTest, GetDirectrixWorksForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola{-0.2, -2, -4};

    EXPECT_EQ(Line(Point(-3.75, 0), Point(-3.75, 1)), parabola.getDirectrix());
}

TEST(ParabolaTest, GetVertexWorksForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola1{1, 2, 4};
    Parabola<ParabolaOrientation::PolynomialX> const parabola2{1, -1, -6};

    EXPECT_EQ(Point(-1, 3), parabola1.getVertex());
    EXPECT_EQ(Point(0.5, -6.25), parabola2.getVertex());
}

TEST(ParabolaTest, GetVertexWorksForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola1{1, 2, 4};
    Parabola<ParabolaOrientation::PolynomialY> const parabola2{1, -1, -6};

    EXPECT_EQ(Point(3, -1), parabola1.getVertex());
    EXPECT_EQ(Point(-6.25, 0.5), parabola2.getVertex());
}

TEST(ParabolaTest, GetFocusWorksForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{-0.2, -2, -4};

    EXPECT_EQ(Point(-5, -0.25), parabola.getFocus());
}

TEST(ParabolaTest, GetFocusWorksForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola{-0.2, -2, -4};

    EXPECT_EQ(Point(-6.25, 1), parabola.getFocus());
}

TEST(ParabolaTest, GetCoefficientsWorksForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{1, 2, 3};

    EXPECT_DOUBLE_EQ(1, parabola.getA());
    EXPECT_DOUBLE_EQ(2, parabola.getB());
    EXPECT_DOUBLE_EQ(3, parabola.getC());
}

TEST(ParabolaTest, GetCoefficientsWorksForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola{1, 2, 3};

    EXPECT_DOUBLE_EQ(1, parabola.getA());
    EXPECT_DOUBLE_EQ(2, parabola.getB());
    EXPECT_DOUBLE_EQ(3, parabola.getC());
}

TEST(ParabolaTest, GetPWorksForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{-0.125, 0, 0};

    EXPECT_DOUBLE_EQ(-2, parabola.getP());
}

TEST(ParabolaTest, GetPWorksForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola{-0.125, 0, 0};

    EXPECT_DOUBLE_EQ(-2, parabola.getP());
}

TEST(ParabolaTest, GetTranslationXAndYWorksForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{-0.2, -2, -4};

    EXPECT_DOUBLE_EQ(-5, parabola.getTranslationInX());
    EXPECT_DOUBLE_EQ(1, parabola.getTranslationInY());
}

TEST(ParabolaTest, GetTranslationXAndYWorksForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola{-0.2, -2, -4};

    EXPECT_DOUBLE_EQ(-5, parabola.getTranslationInX());
    EXPECT_DOUBLE_EQ(1, parabola.getTranslationInY());
}

TEST(ParabolaTest, GetEccentricityWorks) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola1{1, 2, 4};
    Parabola<ParabolaOrientation::PolynomialX> const parabola2{1, 2, 4};

    EXPECT_DOUBLE_EQ(1, parabola1.getEccentricity());
    EXPECT_DOUBLE_EQ(1, parabola2.getEccentricity());
}

TEST(ParabolaTest, GetLengthOfLatusRectumWorksForParabolaOrientatedInX) {
    Parabola<ParabolaOrientation::PolynomialX> const parabola{-0.2, -2, -4};

    EXPECT_DOUBLE_EQ(5, parabola.getLengthOfLatusRectum());
}

TEST(ParabolaTest, GetLengthOfLatusRectumWorksForParabolaOrientatedInY) {
    Parabola<ParabolaOrientation::PolynomialY> const parabola{-0.2, -2, -4};

    EXPECT_DOUBLE_EQ(5, parabola.getLengthOfLatusRectum());
}

}  // namespace alba::TwoDimensions
