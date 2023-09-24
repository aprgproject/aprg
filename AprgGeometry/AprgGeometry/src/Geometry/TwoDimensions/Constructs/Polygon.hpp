#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/LineSegment.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <array>

namespace alba::TwoDimensions {

template <int numberOfVertices>
class Polygon {
public:
    using Distances = std::array<double, numberOfVertices>;
    Polygon();
    Polygon(std::initializer_list<Point> const& vertices);
    [[nodiscard]] AlbaAngle getSumOfAngles() const;
    [[nodiscard]] AlbaAngles getAnglesAtVertices() const;
    [[nodiscard]] Distances getLengthOfSides() const;
    [[nodiscard]] LineSegments getLineSegments() const;
    [[nodiscard]] Lines getLines() const;
    [[nodiscard]] Points getVertices() const;
    [[nodiscard]] Points getPoints(double const interval) const;
    [[nodiscard]] bool isEquilateral() const;
    [[nodiscard]] bool isEquiangular() const;
    [[nodiscard]] bool isRegular() const;

    void getPointsFromVerticesWithoutLastPoint(
        Points& points, double const interval, int const vertexIndex1, int const vertexIndex2) const;

protected:
    std::array<Point, numberOfVertices> m_vertices;
};

}  // namespace alba::TwoDimensions
