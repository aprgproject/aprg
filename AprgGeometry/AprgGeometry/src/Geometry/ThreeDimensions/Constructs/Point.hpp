#pragma once

#include <Common/Container/AlbaXYZ.hpp>

#include <vector>

namespace alba::ThreeDimensions {

using PointParent = AlbaXYZ<double>;

class Point : public PointParent {
public:
    Point();
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    Point(PointParent const& pointParent);
    Point(double const xValue, double const yValue, double const zValue);

private:
    friend std::ostream& operator<<(std::ostream& out, Point const& point);
};

using Points = std::vector<Point>;

}  // namespace alba::ThreeDimensions
