#pragma once

#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <functional>

namespace alba::TwoDimensions {

class Ellipse {
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Ellipse();

    Ellipse(
        Point const& center, double const aCoefficient,
        double const bCoefficient);  // ((x-center.x)^2/aCoefficient^2) + ((y-center.y)^2/bCoefficient^2) = 1

    bool operator==(Ellipse const& ellipse) const;
    bool operator!=(Ellipse const& ellipse) const;
    [[nodiscard]] Line getMajorAxis() const;
    [[nodiscard]] Line getMinorAxis() const;
    [[nodiscard]] Point getCenter() const;
    [[nodiscard]] Points getFoci() const;
    [[nodiscard]] Points getMajorVertices() const;
    [[nodiscard]] Points getMinorVertices() const;
    [[nodiscard]] Points getPointsForCircumference(double const interval) const;
    [[nodiscard]] double getAValue() const;
    [[nodiscard]] double getBValue() const;
    [[nodiscard]] double getCValue() const;
    [[nodiscard]] double getEccentricity() const;
    [[nodiscard]] double getSemiLatusRectum() const;
    [[nodiscard]] double getArea() const;
    [[nodiscard]] double calculateYFromX(double const x, double const signOfRoot) const;
    [[nodiscard]] double calculateXFromY(double const y, double const signOfRoot) const;
    [[nodiscard]] double calculateYFromXWithoutCenter(double const x, double const signOfRoot) const;
    [[nodiscard]] double calculateXFromYWithoutCenter(double const y, double const signOfRoot) const;
    // double getCircumference() const;
    [[nodiscard]] bool isInside(Point const& point) const;
    void traverseArea(double const interval, TraverseOperation const& traverseOperation) const;

private:
    [[nodiscard]] Points getPointsInTraversingXAndY(
        double const signOfX, double const signOfY, double const interval) const;

    [[nodiscard]] Points getPointsInTraversingY(
        double const signOfX, double const signOfY, double const interval) const;

    [[nodiscard]] Points getPointsInTraversingX(
        double const signOfX, double const signOfY, double const interval) const;

    friend std::ostream& operator<<(std::ostream& out, Ellipse const& ellipse);
    Point m_center;
    double m_aValue;
    double m_bValue;
};

using Ellipses = std::vector<Ellipse>;

}  // namespace alba::TwoDimensions
