#pragma once

#include <TwoDimensions/Polygon.hpp>

namespace alba
{

namespace TwoDimensions
{

using TrianglePolygonParent = Polygon<3>;

class Triangle : public TrianglePolygonParent
{
    friend std::ostream & operator<<(std::ostream & out, Triangle const& triangle);
public:
    Triangle();
    Triangle(Point const& first, Point const& second, Point const& third);
    bool isIsoceles() const;
    bool isRightTriangle() const;

    std::string getDisplayableString() const;
};

std::ostream & operator<<(std::ostream & out, Triangle const& triangle);

}
}