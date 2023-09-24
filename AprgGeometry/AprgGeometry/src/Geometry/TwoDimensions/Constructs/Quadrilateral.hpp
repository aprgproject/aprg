#pragma once

#include <Geometry/TwoDimensions/Constructs/Polygon.hpp>

#include <functional>

namespace alba::TwoDimensions {

using QuadrilateralPolygonParent = Polygon<4>;

class Quadrilateral : public QuadrilateralPolygonParent {
public:
    struct StartEndOfXAndY {
        StartEndOfXAndY(double const xStartParameter, double const xEndParameter, double const yParameter);
        double xStart;
        double xEnd;
        double y;
    };

    using TraverseOperation = std::function<void(Point const&)>;
    using GroupOfPoints = std::vector<Points>;
    using ListOfStartEndOfXAndY = std::vector<StartEndOfXAndY>;
    Quadrilateral();
    Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth);
    void traverseArea(double const interval, TraverseOperation const& traverseOperation) const;

private:
    [[nodiscard]] GroupOfPoints getGroupOfPointsBasedOnYValue() const;

    static ListOfStartEndOfXAndY getStartEndForXs(
        GroupOfPoints const& groupOfPointsBasedOnYValue, double const interval);

    static ListOfStartEndOfXAndY getStartEndForXsFor1Points(Points const& points);

    static ListOfStartEndOfXAndY getStartEndForXsFor2Points(
        Points const& points1, Points const& points2, double const interval);

    static ListOfStartEndOfXAndY getStartEndForXsFor3Points(
        Points const& points1, Points const& points2, Points const& points3, double const interval);

    static ListOfStartEndOfXAndY getStartEndForXsFor4Points(
        Points const& points1, Points const& points2, Points const& points3, Points const& points4,
        double const interval);

    friend std::ostream& operator<<(std::ostream& out, Quadrilateral const& quadrilateral);
};

}  // namespace alba::TwoDimensions
