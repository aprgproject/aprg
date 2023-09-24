#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

#include <optional>

namespace alba::ThreeDimensions {

class Sphere {
public:
    Sphere();
    Sphere(Point const& center, double const radius);  // (x-center.x)^2 + (y-center.y)^2 + (z-center.z)^2 = r^2
    bool operator==(Sphere const& sphere) const;
    bool operator!=(Sphere const& sphere) const;
    bool operator<(Sphere const& sphere) const;
    [[nodiscard]] Point getCenter() const;

    [[nodiscard]] std::optional<double> calculateXFromYAndZ(
        double const y, double const z, double const signOfRoot) const;

    [[nodiscard]] std::optional<double> calculateYFromXAndZ(
        double const x, double const z, double const signOfRoot) const;

    [[nodiscard]] std::optional<double> calculateZFromXAndY(
        double const x, double const y, double const signOfRoot) const;

    [[nodiscard]] double getRadius() const;
    [[nodiscard]] bool isInside(Point const& point) const;

private:
    friend std::ostream& operator<<(std::ostream& out, Sphere const& sphere);
    Point m_center;
    double m_radius;
    double m_radiusSquared;
};

using Spheres = std::vector<Sphere>;

}  // namespace alba::ThreeDimensions
