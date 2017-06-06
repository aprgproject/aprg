#pragma once

#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>

#include <functional>

namespace alba
{

namespace twoDimensionsHelper
{

Point getIntersection(Line const& line1, Line const& line2);
double getDistance(Point const& point1, Point const& point2);
Line getLineWithSameSlope(Line const& line, Point const& point);
Line getLineWithInverseSlope(Line const& line, Point const& point);
double getDistance(Point const& point, Line const& line);
void traverseValues(double const startValue, double const endValue, double const interval, std::function<void(double)> performOperation);

}

}
