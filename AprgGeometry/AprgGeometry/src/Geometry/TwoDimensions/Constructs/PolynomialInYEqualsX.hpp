#pragma once

#include <Geometry/TwoDimensions/Constructs/Polynomial.hpp>

namespace alba::TwoDimensions {

template <int numberOfCoefficients>
class PolynomialInYEqualsX : public Polynomial<numberOfCoefficients> {
public:
    using PolynomialInYEqualsXParent = Polynomial<numberOfCoefficients>;
    PolynomialInYEqualsX() : PolynomialInYEqualsXParent() {}

    PolynomialInYEqualsX(std::initializer_list<double> const& coefficients)
        : PolynomialInYEqualsXParent(coefficients) {}

    [[nodiscard]] Points getPoints(double const startValueOfY, double const endValueOfY, double const interval) const {
        Points points;
        AlbaValueRange<double> const range(startValueOfY, endValueOfY, interval);
        range.traverse([&](double const traverseValueOfY) {
            points.emplace_back(calculateXfromY(traverseValueOfY), traverseValueOfY);
        });
        return points;
    }

    [[nodiscard]] double calculateXfromY(double const y) const {
        return PolynomialInYEqualsXParent::calculateOutputFromInput(y);
    }

    [[nodiscard]] double getSlopeAt(double const y) const {
        return 1 / PolynomialInYEqualsXParent::getValueOfFirstDerivative(y);
    }
};

}  // namespace alba::TwoDimensions
