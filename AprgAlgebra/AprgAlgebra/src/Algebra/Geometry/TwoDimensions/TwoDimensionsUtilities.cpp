#include "TwoDimensionsUtilities.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

using namespace alba::algebra::Functions;

namespace alba::algebra::TwoDimensions {

Equation getCircleEquation() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    return {createExpressionIfPossible({xSquared, "+", ySquared}), "=", createExpressionIfPossible({r, "^", 2})};
}

Equation getEllipseEquation() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term const aSquared(createExpressionIfPossible({a, "^", 2}));
    Term const bSquared(createExpressionIfPossible({b, "^", 2}));
    return {createExpressionIfPossible({xSquared, "/", aSquared, "+", ySquared, "/", bSquared}), "=", 1};
}

Equation getHyperbolaEquation() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term const aSquared(createExpressionIfPossible({a, "^", 2}));
    Term const bSquared(createExpressionIfPossible({b, "^", 2}));
    return {createExpressionIfPossible({xSquared, "/", aSquared, "-", ySquared, "/", bSquared}), "=", 1};
}

Equation getLimaconEquation(LimaconTrigonometricFunctionType const type) {
    Term trigPart;
    if (LimaconTrigonometricFunctionType::Cosine == type) {
        trigPart = cos(theta);
    } else if (LimaconTrigonometricFunctionType::Sine == type) {
        trigPart = sin(theta);
    }
    return {createExpressionIfPossible({a, "+", b, "*", trigPart}), "=", r};
}

Equation getLineEquation() {
    return {createExpressionIfPossible({a, "*", x, "+", b, "*", y, "+", c}), "=", 0};
}

Equation getParabolaEquation(ParabolaOrientation const parabolaOrientation) {
    Equation result;
    if (ParabolaOrientation::PolynomialX == parabolaOrientation) {
        Term const xSquared(createExpressionIfPossible({x, "^", 2}));
        result = Equation(createExpressionIfPossible({a, "*", xSquared, "+", b, "*", x, "+", c}), "=", y);
    } else if (ParabolaOrientation::PolynomialY == parabolaOrientation) {
        Term const ySquared(createExpressionIfPossible({y, "^", 2}));
        result = Equation(createExpressionIfPossible({a, "*", ySquared, "+", b, "*", y, "+", c}), "=", x);
    }
    return result;
}

// A conical frustum is a frustum created by slicing the top off a cone (with the cut made parallel to the base).
// For a right circular cone, let h be height, rb as bottom radius and rt as bottom radius.
Term getSurfaceAreaOfAConicalFrustum() {
    Term const topCircleArea(createExpressionIfPossible({getPiAsATerm(), "*", "rt", "^", 2}));
    Term const bottomCircleArea(createExpressionIfPossible({getPiAsATerm(), "*", "rb", "^", 2}));
    Term const sideArea(createExpressionIfPossible(
        {getPiAsATerm(),
         "*",
         "(",
         "rb",
         "+",
         "rt",
         ")",
         "*",
         "(",
         "(",
         "rb",
         "-",
         "rt",
         ")",
         "^",
         2,
         "+",
         "h",
         "^",
         2,
         ")",
         "^",
         AlbaNumber::createFraction(1, 2)}));

    return {createExpressionIfPossible({topCircleArea, "+", bottomCircleArea, "+", sideArea})};
}

Term getVolumeOfAConicalFrustum() {
    Term const radiusPart(createExpressionIfPossible({"rt", "^", 2, "+", "rt", "*", "rb", "+", "rb", "^", 2}));
    return Term(
        createExpressionIfPossible({AlbaNumber::createFraction(1, 3), "*", getPiAsATerm(), "*", "h", "*", radiusPart}));
}

}  // namespace alba::algebra::TwoDimensions
