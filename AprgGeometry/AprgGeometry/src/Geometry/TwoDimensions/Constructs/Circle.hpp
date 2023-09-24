#pragma once

#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <functional>
#include <optional>

namespace alba::TwoDimensions {

class Circle {
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Circle();
    Circle(Point const& center, double const radius);                        // (x-center.x)^2 + (y-center.y)^2 = r^2
    Circle(double const a, double const d, double const e, double const f);  // ax2+ay2+dx+ey+f=0
    bool operator==(Circle const& circle) const;
    bool operator!=(Circle const& circle) const;
    bool operator<(Circle const& circle) const;
    [[nodiscard]] Point getCenter() const;
    [[nodiscard]] Point getNearestPointInCircumference(Point const& pointNotCircumference) const;
    [[nodiscard]] Points getLocus(double const interval) const;
    [[nodiscard]] std::optional<double> calculateYFromX(double const x, double const signOfRoot) const;
    [[nodiscard]] std::optional<double> calculateXFromY(double const y, double const signOfRoot) const;
    [[nodiscard]] std::optional<double> calculateYFromXWithoutCenter(double const x, double const signOfRoot) const;
    [[nodiscard]] std::optional<double> calculateXFromYWithoutCenter(double const y, double const signOfRoot) const;
    [[nodiscard]] double getRadius() const;
    [[nodiscard]] double getArea() const;
    [[nodiscard]] double getCircumference() const;
    [[nodiscard]] bool isInside(Point const& point) const;
    void traverseArea(double const interval, TraverseOperation const& traverseOperation) const;
    Point getPointAtAngle(double const angleInRadians);
    static double getEccentricity();

private:
    [[nodiscard]] Points getPointsInTraversingXAndY(
        double const signOfX, double const signOfY, double const interval) const;

    [[nodiscard]] Points getPointsInTraversingY(
        double const signOfX, double const signOfY, double const interval) const;

    [[nodiscard]] Points getPointsInTraversingX(
        double const signOfX, double const signOfY, double const interval) const;

    void determineAndSaveCenterAndRadiusFromCoefficients(
        double const a, double const d, double const e, double const f);

    friend std::ostream& operator<<(std::ostream& out, Circle const& circle);
    Point m_center;
    double m_radius;
    double m_radiusSquared;
};

using Circles = std::vector<Circle>;

}  // namespace alba::TwoDimensions
