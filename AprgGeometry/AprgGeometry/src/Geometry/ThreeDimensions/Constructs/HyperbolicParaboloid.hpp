#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

namespace alba::ThreeDimensions {

class HyperbolicParaboloid {
public:
    HyperbolicParaboloid();

    HyperbolicParaboloid(
        Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient);

    // ((y-center.y)^2/bCoefficient^2) - ((x-center.x)^2/aCoefficient^2) = (z-center.z)/c
    bool operator==(HyperbolicParaboloid const& hyperbolicParaboloid) const;
    bool operator!=(HyperbolicParaboloid const& hyperbolicParaboloid) const;
    [[nodiscard]] Point getCenter() const;
    [[nodiscard]] double getAValue() const;
    [[nodiscard]] double getBValue() const;
    [[nodiscard]] double getCValue() const;
    [[nodiscard]] double calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const;
    [[nodiscard]] double calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const;
    [[nodiscard]] double calculateZFromXAndY(double const x, double const y) const;

private:
    friend std::ostream& operator<<(std::ostream& out, HyperbolicParaboloid const& hyperbolicParaboloid);
    Point m_center;
    double m_aValue;
    double m_bValue;
    double m_cValue;
};

using HyperbolicParaboloids = std::vector<HyperbolicParaboloid>;

}  // namespace alba::ThreeDimensions
