#include <Geometry/TwoDimensions/Constructs/Quadrilateral.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::TwoDimensions {

TEST(QuadrilateralTest, QuadilateralCanBeCreated) {
    Quadrilateral const quadrilateral(Point(1, 1), Point(2, 3), Point(0, 17), Point(-100, 4));
}

TEST(QuadrilateralTest, GetPointsWorks) {
    Quadrilateral const quadrilateral(Point(-2, 0), Point(0, -2), Point(2, 0), Point(0, 2));
    Points points(quadrilateral.getPoints(1));

    ASSERT_EQ(8U, points.size());
    EXPECT_EQ(Point(-2, 0), points[0]);
    EXPECT_EQ(Point(-1, -1), points[1]);
    EXPECT_EQ(Point(0, -2), points[2]);
    EXPECT_EQ(Point(1, -1), points[3]);
    EXPECT_EQ(Point(2, 0), points[4]);
    EXPECT_EQ(Point(1, 1), points[5]);
    EXPECT_EQ(Point(0, 2), points[6]);
    EXPECT_EQ(Point(-1, 1), points[7]);
}

TEST(QuadrilateralTest, DISABLED_PointsInQuadilateralAreCorrectWhenOutOfOrderVerticesAreUsed) {
    // how can this be done?
    Quadrilateral const quadrilateral(Point(-2, 0), Point(2, 0), Point(0, 2), Point(0, -2));
    Points points(quadrilateral.getPoints(1));

    ASSERT_EQ(8U, points.size());
    EXPECT_EQ(Point(-2, 0), points[0]);
    EXPECT_EQ(Point(-1, -1), points[1]);
    EXPECT_EQ(Point(0, -2), points[2]);
    EXPECT_EQ(Point(1, -1), points[3]);
    EXPECT_EQ(Point(2, 0), points[4]);
    EXPECT_EQ(Point(1, 1), points[5]);
    EXPECT_EQ(Point(0, 2), points[6]);
    EXPECT_EQ(Point(-1, 1), points[7]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor1YGroup) {
    Quadrilateral const quadrilateral(Point(1, 1), Point(2, 1), Point(4, 1), Point(5, 1));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(5U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(1, 1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2, 1), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(4, 1), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(5, 1), pointsInAreaTraversal[4]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInFirstPattern) {
    Quadrilateral const quadrilateral(Point(3, 1), Point(1, 3), Point(3, 3), Point(5, 3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(1, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(5, 3), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInSecondPattern) {
    Quadrilateral const quadrilateral(Point(2, 2), Point(2, 4), Point(4, 2), Point(4, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInThirdPattern) {
    Quadrilateral const quadrilateral(Point(3, 5), Point(1, 3), Point(3, 3), Point(5, 3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(1, 3), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(5, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(3, 5), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFirstPattern) {
    Quadrilateral const quadrilateral(Point(2, 1), Point(4, 3), Point(2, 4), Point(4, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2, 1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInSecondPattern) {
    Quadrilateral const quadrilateral(Point(4, 1), Point(2, 3), Point(2, 4), Point(4, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(4, 1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInThirdPattern) {
    Quadrilateral const quadrilateral(Point(3, 1), Point(1, 2), Point(5, 2), Point(3, 3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(7U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(1, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(5, 2), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[6]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFourthPattern) {
    Quadrilateral const quadrilateral(Point(2, 3), Point(4, 5), Point(2, 2), Point(4, 2));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(4, 5), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFifthPattern) {
    Quadrilateral const quadrilateral(Point(2, 5), Point(4, 3), Point(2, 2), Point(4, 2));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(2, 5), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor4YGroupsFirstPattern) {
    Quadrilateral const quadrilateral(Point(3, 1), Point(2, 2), Point(4, 3), Point(3, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(8U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(3.5, 2), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(2.5, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(3.5, 3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[7]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor4YGroupsSecondPattern) {
    Quadrilateral const quadrilateral(Point(3, 1), Point(2, 3), Point(4, 2), Point(3, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(8U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2.5, 2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3.5, 2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3.5, 3), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[7]);
}

TEST(QuadrilateralTest, DoesNotCrashExampleDueToNearValues) {
    Quadrilateral const quadrilateral(
        Point(3.57038804403507858964417209791, 37.7082039324993658624407544266),
        Point(-3.57038804403508036600101149816, 37.7082039324993729678681120276),
        Point(2.66121012417164948260506207589, 36.2917960675006270321318879724),
        Point(-2.66121012417165125896190147614, 36.2917960675006341375592455734));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    EXPECT_EQ(24U, pointsInAreaTraversal.size());
}

}  // namespace alba::TwoDimensions
