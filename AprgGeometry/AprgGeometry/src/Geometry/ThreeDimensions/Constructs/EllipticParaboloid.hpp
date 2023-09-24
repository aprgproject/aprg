#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

namespace alba::ThreeDimensions {

class EllipticParaboloid {
public:
    EllipticParaboloid();

    EllipticParaboloid(
        Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient);

    // ((x-center.x)^2/aCoefficient^2) + ((y-center.y)^2/bCoefficient^2) = (z-center.z)/c
    bool operator==(EllipticParaboloid const& ellipticParaboloid) const;
    bool operator!=(EllipticParaboloid const& ellipticParaboloid) const;
    [[nodiscard]] Point getCenter() const;
    [[nodiscard]] double getAValue() const;
    [[nodiscard]] double getBValue() const;
    [[nodiscard]] double getCValue() const;
    [[nodiscard]] double calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const;
    [[nodiscard]] double calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const;
    [[nodiscard]] double calculateZFromXAndY(double const x, double const y) const;

private:
    friend std::ostream& operator<<(std::ostream& out, EllipticParaboloid const& ellipticParaboloid);
    Point m_center;
    double m_aValue;
    double m_bValue;
    double m_cValue;
};

using EllipticParaboloids = std::vector<EllipticParaboloid>;

}  // namespace alba::ThreeDimensions
