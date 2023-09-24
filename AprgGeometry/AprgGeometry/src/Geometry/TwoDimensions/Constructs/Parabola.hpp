#pragma once

#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>
#include <Geometry/TwoDimensions/Constructs/PolynomialInXEqualsY.hpp>
#include <Geometry/TwoDimensions/Constructs/PolynomialInYEqualsX.hpp>

namespace alba::TwoDimensions {

enum class ParabolaOrientation {
    PolynomialX,
    PolynomialY,
};

template <ParabolaOrientation orientation>
struct ParabolaOrientationTraits {
    // causes compilation error
    // static_assert(sizeof(orientation) == -1, "Parabola orientation traits are not defined");
};

template <>
struct ParabolaOrientationTraits<ParabolaOrientation::PolynomialX> {
    using ParabolaOrientationPolynomialType = PolynomialInXEqualsY<3>;
};

template <>
struct ParabolaOrientationTraits<ParabolaOrientation::PolynomialY> {
    using ParabolaOrientationPolynomialType = PolynomialInYEqualsX<3>;
};

template <ParabolaOrientation parabolaOrientation>
using ParabolaPolynomialType =
    typename ParabolaOrientationTraits<parabolaOrientation>::ParabolaOrientationPolynomialType;

template <ParabolaOrientation parabolaOrientation>
class Parabola : public ParabolaPolynomialType<parabolaOrientation> {
public:
    using ParabolaParent = ParabolaPolynomialType<parabolaOrientation>;
    // vertex focus directrix?
    Parabola() : ParabolaParent() {}

    // ax2 + bx + c = y or ay2 + by + c = x
    Parabola(double const aCoefficient, double const bCoefficient, double const cCoefficient)
        : ParabolaParent{aCoefficient, bCoefficient, cCoefficient} {}

    [[nodiscard]] Line getDirectrix() const {
        double const p(getP());
        double const xt(getTranslationInX());
        double const yt(getTranslationInY());
        Line directrix;
        if (ParabolaOrientation::PolynomialX == parabolaOrientation) {
            directrix = Line(Point(0, yt - p), Point(1, yt - p));
        } else {
            directrix = Line(Point(xt - p, 0), Point(xt - p, 1));
        }
        return directrix;
    }

    [[nodiscard]] Point getVertex() const {
        double const a(getA());
        double const b(getB());
        double const c(getC());
        double const vertexCoordinate1 = -b / (2 * a);
        double const vertexCoordinate2 = ((4 * a * c) - (b * b)) / (4 * a);
        Point vertex;
        if (ParabolaOrientation::PolynomialX == parabolaOrientation) {
            vertex = Point(vertexCoordinate1, vertexCoordinate2);
        } else {
            vertex = Point(vertexCoordinate2, vertexCoordinate1);
        }
        return vertex;
    }

    [[nodiscard]] Point getFocus() const {
        double const p(getP());
        double const xt(getTranslationInX());
        double const yt(getTranslationInY());
        Point focus;
        if (ParabolaOrientation::PolynomialX == parabolaOrientation) {
            focus = Point(xt, yt + p);
        } else {
            focus = Point(xt + p, yt);
        }
        return focus;
    }

    [[nodiscard]] double getA() const { return ParabolaParent::m_coefficients[2]; }
    [[nodiscard]] double getB() const { return ParabolaParent::m_coefficients[1]; }
    [[nodiscard]] double getC() const { return ParabolaParent::m_coefficients[0]; }

    [[nodiscard]] double getP() const {
        //(x-xt)^2 = 4p*(y-yt)
        return 1 / (getA() * 4);
    }

    [[nodiscard]] double getTranslationInX() const {
        //(x-xt)^2 = 4p*(y-yt)
        return -2 * getB() * getP();
    }

    [[nodiscard]] double getTranslationInY() const {
        //(x-xt)^2 = 4p*(y-yt)
        return getC() - (pow(getTranslationInX(), 2) / (4 * getP()));
    }

    [[nodiscard]] double getEccentricity() const { return 1; }

    [[nodiscard]] double getLengthOfLatusRectum() const {
        // The horizontal chord through the focus is called the latus rectum; one half of it is the semi-latus rectum.
        return mathHelper::getAbsoluteValue<double>(4 * getP());
    }

    friend std::ostream& operator<<(std::ostream& out, Parabola<parabolaOrientation> const& parabola) {
        if (ParabolaOrientation::PolynomialX == parabola.parabolaOrientation) {
            out << parabola.getA() << "*[x^2] + " << parabola.getB() << "*x + " << parabola.getC() << " = 0";
        } else if (ParabolaOrientation::PolynomialY == parabola.parabolaOrientation) {
            out << parabola.getA() << "*[y^2] + " << parabola.getB() << "*y + " << parabola.getC() << " = 0";
        }
        return out;
    }

private:
};

}  // namespace alba::TwoDimensions
