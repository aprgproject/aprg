#pragma once

#include <Geometry/TwoDimensions/Constructs/Polynomial.hpp>

namespace alba::TwoDimensions {

template <int numberOfCoefficients>
class PolynomialInXEqualsY : public Polynomial<numberOfCoefficients> {
public:
    using PolynomialInXEqualsYParent = Polynomial<numberOfCoefficients>;
    PolynomialInXEqualsY() : PolynomialInXEqualsYParent() {}

    PolynomialInXEqualsY(std::initializer_list<double> const& coefficients)
        : PolynomialInXEqualsYParent(coefficients) {}

    [[nodiscard]] Points getPoints(double const startValueOfX, double const endValueOfX, double const interval) const {
        Points points;
        AlbaValueRange<double> range(startValueOfX, endValueOfX, interval);
        range.traverse([&](double const traverseValueOfX) {
            points.emplace_back(traverseValueOfX, calculateYfromX(traverseValueOfX));
        });
        return points;
    }

    [[nodiscard]] double calculateYfromX(double const x) const {
        return PolynomialInXEqualsYParent::calculateOutputFromInput(x);
    }

    [[nodiscard]] double getSlopeAt(double const x) const {
        return PolynomialInXEqualsYParent::getValueOfFirstDerivative(x);
    }
};

}  // namespace alba::TwoDimensions
