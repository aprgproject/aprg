#pragma once

#include <Common/Container/AlbaXY.hpp>

#include <vector>

namespace alba
{

namespace TwoDimensions
{

using PointParent = AlbaXY<double>;

class Point : public PointParent
{
public:
    Point();
    Point(PointParent const& pointParent);
    Point(double const xValue, double const yValue);
};

using Points = std::vector<Point>;

std::ostream & operator<<(std::ostream & out, Point const& point);

}
}