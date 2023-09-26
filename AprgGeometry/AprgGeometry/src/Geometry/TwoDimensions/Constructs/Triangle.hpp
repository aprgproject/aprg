#pragma once

#include <Geometry/TwoDimensions/Constructs/Polygon.hpp>

namespace alba::TwoDimensions {

using TrianglePolygonParent = Polygon<3>;

class Triangle : public TrianglePolygonParent {
public:
    Triangle() = default;
    Triangle(Point const& first, Point const& second, Point const& third);
    [[nodiscard]] bool isIsoceles() const;
    [[nodiscard]] bool isRightTriangle() const;

private:
    friend std::ostream& operator<<(std::ostream& out, Triangle const& triangle);
};

}  // namespace alba::TwoDimensions
