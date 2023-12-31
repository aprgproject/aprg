#include <Geometry/TwoDimensions/Constructs/Hyperbola.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

namespace alba::TwoDimensions {

TEST(HyperbolaTest, AreaTraversalIsCorrect) {
    // traversal
}

TEST(HyperbolaTest, GetAsymptotesWorks) {
    Hyperbola const hyperbola1(Point(0, 0), 1, 1);
    Hyperbola const hyperbola2(Point(0, 0), 3, 4);
    Hyperbola const hyperbola3(Point(0, 0), -3, -4);

    Lines asymptotes1(hyperbola1.getAsymptotes());
    Lines asymptotes2(hyperbola2.getAsymptotes());
    Lines asymptotes3(hyperbola3.getAsymptotes());

    ASSERT_EQ(2U, asymptotes1.size());
    EXPECT_EQ(Line(1, 1, 0), asymptotes1[0]);
    EXPECT_EQ(Line(1, -1, 0), asymptotes1[1]);
    ASSERT_EQ(2U, asymptotes2.size());
    EXPECT_EQ(Line(4, 3, 0), asymptotes2[0]);
    EXPECT_EQ(Line(4, -3, 0), asymptotes2[1]);
    ASSERT_EQ(2U, asymptotes3.size());
    EXPECT_EQ(Line(-4, -3, 0), asymptotes3[0]);
    EXPECT_EQ(Line(-4, 3, 0), asymptotes3[1]);
}

TEST(HyperbolaTest, EmptyHyperbola) {
    Hyperbola const hyperbola;

    EXPECT_EQ(Point(0, 0), hyperbola.getCenter());
    EXPECT_DOUBLE_EQ(0, hyperbola.getAValue());
    EXPECT_DOUBLE_EQ(0, hyperbola.getBValue());
    EXPECT_DOUBLE_EQ(0, hyperbola.getCValue());
    EXPECT_NE(0, hyperbola.getEccentricity());
    EXPECT_NE(0, hyperbola.getSemiLactusRectum());

    Points const points(hyperbola.getPointsForShape(1));
    ASSERT_TRUE(points.empty());
}

TEST(HyperbolaTest, HyperbolaAtOriginWithRadius) {
    Hyperbola const hyperbola(Point(0, 0), 3, 2);

    EXPECT_EQ(Point(0, 0), hyperbola.getCenter());
    EXPECT_DOUBLE_EQ(3, hyperbola.getAValue());
    EXPECT_DOUBLE_EQ(2, hyperbola.getBValue());
    EXPECT_DOUBLE_EQ(3.6055512754639891, hyperbola.getCValue());
    EXPECT_DOUBLE_EQ(1.2018504251546631, hyperbola.getEccentricity());
    EXPECT_DOUBLE_EQ(1.3333333333333333, hyperbola.getSemiLactusRectum());

    Points points(hyperbola.getPointsForShape(1));
    ASSERT_EQ(22U, points.size());
    EXPECT_EQ(Point(6, 3.4641016151377543864), points[0]);
    EXPECT_EQ(Point(5, 2.6666666666666669627), points[1]);
    EXPECT_EQ(Point(4.2426406871192856585, 2), points[2]);
    EXPECT_EQ(Point(4, 1.7638342073763935147), points[3]);
    EXPECT_EQ(Point(3.3541019662496847076, 1), points[4]);
    EXPECT_EQ(Point(3, 0), points[5]);
    EXPECT_EQ(Point(3.3541019662496847076, -1), points[6]);
    EXPECT_EQ(Point(4, -1.7638342073763935147), points[7]);
    EXPECT_EQ(Point(4.2426406871192856585, -2), points[8]);
    EXPECT_EQ(Point(5, -2.6666666666666669627), points[9]);
    EXPECT_EQ(Point(6, -3.4641016151377543864), points[10]);
    EXPECT_EQ(Point(-6, 3.4641016151377543864), points[11]);
    EXPECT_EQ(Point(-5, 2.6666666666666669627), points[12]);
    EXPECT_EQ(Point(-4.2426406871192856585, 2), points[13]);
    EXPECT_EQ(Point(-4, 1.7638342073763935147), points[14]);
    EXPECT_EQ(Point(-3.3541019662496847076, 1), points[15]);
    EXPECT_EQ(Point(-3, 0), points[16]);
    EXPECT_EQ(Point(-3.3541019662496847076, -1), points[17]);
    EXPECT_EQ(Point(-4, -1.7638342073763935147), points[18]);
    EXPECT_EQ(Point(-4.2426406871192856585, -2), points[19]);
    EXPECT_EQ(Point(-5, -2.6666666666666669627), points[20]);
    EXPECT_EQ(Point(-6, -3.4641016151377543864), points[21]);
}

TEST(HyperbolaTest, GetFociWorks) {
    Hyperbola const hyperbola1(Point(0, 0), 1, 1);
    Hyperbola const hyperbola2(Point(0, 0), 3, 4);
    Hyperbola const hyperbola3(Point(0, 0), -3, -4);

    Points foci1(hyperbola1.getFoci());
    Points foci2(hyperbola2.getFoci());
    Points foci3(hyperbola3.getFoci());

    ASSERT_EQ(2U, foci2.size());
    EXPECT_EQ(Point(1.41421356237309514547462185874, 0), foci1[0]);
    EXPECT_EQ(Point(-1.41421356237309514547462185874, 0), foci1[1]);
    ASSERT_EQ(2U, foci2.size());
    EXPECT_EQ(Point(5, 0), foci2[0]);
    EXPECT_EQ(Point(-5, 0), foci2[1]);
    ASSERT_EQ(2U, foci3.size());
    EXPECT_EQ(Point(0, 5), foci3[0]);
    EXPECT_EQ(Point(0, -5), foci3[1]);
}

TEST(HyperbolaTest, GetVerticesWorks) {
    Hyperbola const hyperbola1(Point(0, 0), 1, 1);
    Hyperbola const hyperbola2(Point(0, 0), 3, 4);
    Hyperbola const hyperbola3(Point(0, 0), -3, -4);

    Points vertices1(hyperbola1.getVertices());
    Points vertices2(hyperbola2.getVertices());
    Points vertices3(hyperbola3.getVertices());

    ASSERT_EQ(2U, vertices2.size());
    EXPECT_EQ(Point(1, 0), vertices1[0]);
    EXPECT_EQ(Point(-1, 0), vertices1[1]);
    ASSERT_EQ(2U, vertices2.size());
    EXPECT_EQ(Point(3, 0), vertices2[0]);
    EXPECT_EQ(Point(-3, 0), vertices2[1]);
    ASSERT_EQ(2U, vertices3.size());
    EXPECT_EQ(Point(0, 4), vertices3[0]);
    EXPECT_EQ(Point(0, -4), vertices3[1]);
}

}  // namespace alba::TwoDimensions
