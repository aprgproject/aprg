#pragma once

#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/Point.hpp>

namespace alba
{

namespace twoDimensionsHelper
{

Point getIntersection(Line const& line1, Line const& line2);
double getDistance(Point const& point1, Point const& point2);
}

}
