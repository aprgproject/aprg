#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

namespace alba::ThreeDimensions {

class EllipticHyperboloid {
public:
    EllipticHyperboloid();

    EllipticHyperboloid(
        Point const& center, double const aCoefficient, double const bCoefficient, double const cCoefficient,
        bool const isOneNegative);

    // ((x-center.x)^2/aCoefficient^2) + ((y-center.y)^2/bCoefficient^2) - ((z-center.z)^2/cCoefficient^2) = 1
    bool operator==(EllipticHyperboloid const& ellipticHyperboloid) const;
    bool operator!=(EllipticHyperboloid const& ellipticHyperboloid) const;
    [[nodiscard]] bool isInside(Point const& point) const;
    [[nodiscard]] double getAValue() const;
    [[nodiscard]] double getBValue() const;
    [[nodiscard]] double getCValue() const;
    [[nodiscard]] double calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const;
    [[nodiscard]] double calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const;
    [[nodiscard]] double calculateZFromXAndY(double const x, double const y, double const signOfRoot) const;
    [[nodiscard]] Point getCenter() const;

private:
    friend std::ostream& operator<<(std::ostream& out, EllipticHyperboloid const& ellipticHyperboloid);
    Point m_center;
    double m_aValue;
    double m_bValue;
    double m_cValue;
    int m_oneWithSign;
};

using EllipticHyperboloids = std::vector<EllipticHyperboloid>;

}  // namespace alba::ThreeDimensions
