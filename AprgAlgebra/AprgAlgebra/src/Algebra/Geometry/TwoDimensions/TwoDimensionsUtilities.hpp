#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba::algebra::TwoDimensions {

enum class LimaconTrigonometricFunctionType { Cosine, Sine };

enum class ParabolaOrientation {
    PolynomialX,
    PolynomialY,
};

Equation getCircleEquation();
Equation getEllipseEquation();
Equation getHyperbolaEquation();
Equation getLimaconEquation(LimaconTrigonometricFunctionType const type);
Equation getLineEquation();
Equation getParabolaEquation(ParabolaOrientation const parabolaOrientation);

Term getSurfaceAreaOfAConicalFrustum();
Term getVolumeOfAConicalFrustum();

}  // namespace alba::algebra::TwoDimensions
