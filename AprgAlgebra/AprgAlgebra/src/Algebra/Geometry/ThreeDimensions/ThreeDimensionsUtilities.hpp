#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba::algebra::ThreeDimensions {
Equation getEllipsoidEquation();
Equation getEllipticConeEquation();
Equation getEllipticHyperboloidEquation(bool const isOneNegative);
Equation getEllipticParaboloidEquation();
Equation getHyperbolicParaboloidEquation();
Equation getPlaneEquation();
Equation getPlaneEquationWithPointCoordinates();
Equation getSphereEquation();
Equations getLineEquations();
}  // namespace alba::algebra::ThreeDimensions
