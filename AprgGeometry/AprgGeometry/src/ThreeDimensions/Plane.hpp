#pragma once

#include <TwoDimensions/Point.hpp>

#include <vector>

//Think about this

namespace alba
{

enum class PlaneType
{
    Horizontal,
    Vertical,
    WithPositiveSlope,
    WithNegativeSlope,
    Invalid
};

class Plane
{
public:
    Plane();
    Plane(Point const& first, Point const& second);
    Plane(double const aCoefficient, double const bCoefficient, double const cCoefficient); //ax+by+c=0
    bool operator==(Plane const& line) const;
    bool operator!=(Plane const& line) const;
    PlaneType getType() const;
    double getXIntercept() const;
    double getYIntercept() const;
    double getInverseSlope() const;
    double getACoefficient() const;
    double getBCoefficient() const;
    double getCCoefficient() const;
    Points getPoints(Point const& first, Point const& second, double const interval) const;
    Points getPointsWithoutLastPoint(Point const& first, Point const& second, double const interval) const;
    double calculateYFromX(double const x) const;
    double calculateXFromY(double const y) const;
private:
    void getPointsForVerticalPlane(Points & points, Point const& first, Point const& second, double const interval) const;
    void getPointsForHorizontalPlane(Points & points, Point const& first, Point const& second, double const interval) const;
    void getPointsForPlaneWithSlope(Points & points, Point const& first, Point const& second, double const interval) const;
    void mergePointsFromPointsFromXAndY(Points & points, Points const& pointsFromXCoordinate, Points const& pointsFromYCoordinate, bool const isDirectionAscendingForX) const;
    PlaneType determinePlaneTypeUsingDeltaXandDeltaY(double const deltaY, double const deltaX) const;
    PlaneType determinePlaneTypeUsingCoefficients(double const aCoefficient, double const bCoefficient) const;
    PlaneType m_type;
    double m_xIntercept; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
    double m_yIntercept; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
    double m_zIntercept; //form: a*(x-x0) + b*(y-y0) + c*(z-z0) = 0
    double m_aCoefficient; //form: a*x + b*y + c*z + d = 0
    double m_bCoefficient; //form: a*x + b*y + c*z + d = 0
    double m_cCoefficient; //form: a*x + b*y + c*z + d = 0
    double m_dCoefficient; //form: a*x + b*y + c*z + d = 0
};

using Planes = std::vector<Plane>;

}
