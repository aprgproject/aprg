#pragma once

#include <Common/Container/AlbaXY.hpp>

#include <vector>

namespace alba::TwoDimensions {

using PointParent = AlbaXY<double>;

class Point : public PointParent {
public:
    Point();
    explicit Point(PointParent const& pointParent);
    Point(double const xValue, double const yValue);

private:
    friend std::ostream& operator<<(std::ostream& out, Point const& point);
};

using Points = std::vector<Point>;

}  // namespace alba::TwoDimensions
