#include "ThreeDimensionsUtilities.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba::algebra::ThreeDimensions {

Equation getEllipsoidEquation() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term const zSquared(createExpressionIfPossible({zMinusZ0, "^", 2}));
    Term const aSquared(createExpressionIfPossible({a, "^", 2}));
    Term const bSquared(createExpressionIfPossible({b, "^", 2}));
    Term const cSquared(createExpressionIfPossible({c, "^", 2}));
    return {
        createExpressionIfPossible(
            {xSquared, "/", aSquared, "+", ySquared, "/", bSquared, "+", zSquared, "/", cSquared}),
        "=", 1};
}

Equation getEllipticConeEquation() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term const zSquared(createExpressionIfPossible({zMinusZ0, "^", 2}));
    Term const aSquared(createExpressionIfPossible({a, "^", 2}));
    Term const bSquared(createExpressionIfPossible({b, "^", 2}));
    Term const cSquared(createExpressionIfPossible({c, "^", 2}));
    return {
        createExpressionIfPossible(
            {xSquared, "/", aSquared, "+", ySquared, "/", bSquared, "+", zSquared, "/", cSquared}),
        "=", 0};
}

Equation getEllipticHyperboloidEquation(bool const isOneNegative) {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term const zSquared(createExpressionIfPossible({zMinusZ0, "^", 2}));
    Term const aSquared(createExpressionIfPossible({a, "^", 2}));
    Term const bSquared(createExpressionIfPossible({b, "^", 2}));
    Term const cSquared(createExpressionIfPossible({c, "^", 2}));
    return {
        createExpressionIfPossible(
            {xSquared, "/", aSquared, "+", ySquared, "/", bSquared, "-", zSquared, "/", cSquared}),
        "=", isOneNegative ? -1 : 1};
}

Equation getEllipticParaboloidEquation() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term const aSquared(createExpressionIfPossible({a, "^", 2}));
    Term const bSquared(createExpressionIfPossible({b, "^", 2}));
    return {
        createExpressionIfPossible({xSquared, "/", aSquared, "+", ySquared, "/", bSquared}), "=",
        createExpressionIfPossible({zMinusZ0, "/", c})};
}

Equation getHyperbolicParaboloidEquation() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term const aSquared(createExpressionIfPossible({a, "^", 2}));
    Term const bSquared(createExpressionIfPossible({b, "^", 2}));
    return {
        createExpressionIfPossible({ySquared, "/", bSquared, "-", xSquared, "/", aSquared}), "=",
        createExpressionIfPossible({zMinusZ0, "/", c})};
}

Equation getPlaneEquation() {
    return {createExpressionIfPossible({a, "*", x, "+", b, "*", y, "+", c, "*", z, "+", d}), "=", 0};
}

Equation getPlaneEquationWithPointCoordinates() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    return {createExpressionIfPossible({a, "*", xMinusX0, "+", b, "*", yMinusY0, "+", c, "*", zMinusZ0}), "=", 0};
}

Equation getSphereEquation() {
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term const xSquared(createExpressionIfPossible({xMinusX0, "^", 2}));
    Term const ySquared(createExpressionIfPossible({yMinusY0, "^", 2}));
    Term const zSquared(createExpressionIfPossible({zMinusZ0, "^", 2}));
    return {
        createExpressionIfPossible({xSquared, "+", ySquared, "+", zSquared}), "=",
        createExpressionIfPossible({r, "^", 2})};
}

Equations getLineEquations() {
    Equations result;
    Term const xMinusX0(createExpressionIfPossible({x, "-", x0}));
    Term const yMinusY0(createExpressionIfPossible({y, "-", y0}));
    Term const zMinusZ0(createExpressionIfPossible({z, "-", z0}));
    Term const xSide(createExpressionIfPossible({xMinusX0, "/", a}));
    Term const ySide(createExpressionIfPossible({yMinusY0, "/", b}));
    Term const zSide(createExpressionIfPossible({zMinusZ0, "/", c}));
    result.emplace_back(xSide, "=", ySide);
    result.emplace_back(xSide, "=", zSide);
    return result;
}

}  // namespace alba::algebra::ThreeDimensions
