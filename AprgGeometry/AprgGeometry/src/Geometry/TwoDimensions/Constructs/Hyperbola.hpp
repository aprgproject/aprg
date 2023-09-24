#pragma once

#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <functional>

namespace alba::TwoDimensions {

class Hyperbola {
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Hyperbola();

    Hyperbola(
        Point const& center, double const aCoefficient,
        double const bCoefficient);  // ((x-center.x)^2/aCoefficient^2) - ((y-center.y)^2/bCoefficient^2) = 1

    bool operator==(Hyperbola const& hyperbola) const;
    bool operator!=(Hyperbola const& hyperbola) const;
    [[nodiscard]] Lines getAsymptotes() const;
    [[nodiscard]] Point getCenter() const;
    [[nodiscard]] Points getFoci() const;
    [[nodiscard]] Points getVertices() const;
    [[nodiscard]] Points getPointsForShape(double const interval) const;
    [[nodiscard]] double getAValue() const;
    [[nodiscard]] double getBValue() const;
    [[nodiscard]] double getCValue() const;
    [[nodiscard]] double getEccentricity() const;
    [[nodiscard]] double getSemiLactusRectum() const;
    [[nodiscard]] double calculateYFromX(double const x, double const signOfRoot) const;
    [[nodiscard]] double calculateXFromY(double const y, double const signOfRoot) const;
    [[nodiscard]] double calculateYFromXWithoutCenter(double const x, double const signOfRoot) const;
    [[nodiscard]] double calculateXFromYWithoutCenter(double const y, double const signOfRoot) const;

private:
    [[nodiscard]] Points getPointsInTraversingXAndY(
        double const signOfX, double const signOfY, double const interval) const;

    [[nodiscard]] Points getPointsInTraversingY(
        double const signOfX, double const signOfY, double const interval) const;

    [[nodiscard]] Points getPointsInTraversingX(
        double const signOfX, double const signOfY, double const interval) const;

    friend std::ostream& operator<<(std::ostream& out, Hyperbola const& hyperbola);
    Point m_center;
    double m_aValue;
    double m_bValue;
};

using Hyperbolas = std::vector<Hyperbola>;

}  // namespace alba::TwoDimensions
