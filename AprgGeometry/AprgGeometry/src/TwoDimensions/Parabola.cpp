#include "Parabola.hpp"

namespace alba
{

Parabola::Parabola()
    : ParabolaPolynomialParent()
{}

Parabola::Parabola(double const aCoefficient, double const bCoefficient, double const cCoefficient) // ax2 + bx + c = 0
    : ParabolaPolynomialParent{cCoefficient, bCoefficient, aCoefficient}
{}

}
