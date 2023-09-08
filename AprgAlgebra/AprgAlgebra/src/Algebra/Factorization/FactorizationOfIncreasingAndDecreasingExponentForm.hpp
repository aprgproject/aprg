#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba::algebra::Factorization {

bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
    Monomials const& monomialsToCheck, Monomials const& monomialsWithExponentsInOrder);
bool areRootsAcceptable(AlbaNumbers const& rootValues);
int calculateMaxExponentDivisor(Monomial const& firstMonomial, Monomial const& lastMonomial);
Polynomials factorizeIncreasingAndDecreasingExponentsForm(Polynomial const& polynomial);
AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(
    Polynomial const& polynomial, Monomials const& monomialsWithExponentsInOrder);
AlbaNumbers calculatePolynomialRoots(AlbaNumbers const& coefficients);
AlbaNumbers calculatePolynomialRootsUsingBrentMethod(
    AlbaNumbers const& previousDerivativeRoots, AlbaNumbers const& coefficients);
AlbaNumber getMaxAbsoluteValueForRootFinding(AlbaNumbers const& coefficients);
AlbaNumbers getDerivativeCoefficients(AlbaNumbers const& coefficients);
Monomials getMonomialsWithExponentsInOrder(
    int const exponentDivisor, Monomial const& firstInPolynomial, Monomial const& lastInPolynomial);
void factorizeIncreasingAndDecreasingExponentsFormIfPossible(Polynomials& result, Polynomial const& polynomial);

void factorizePolynomialForm(
    Polynomials& result, Polynomial const& polynomial, AlbaNumbers const& coefficients,
    Monomial::VariablesToExponentsMap const& firstVariableExponent,
    Monomial::VariablesToExponentsMap const& secondVariableExponent);

void fixCoefficientsOfFactors(
    AlbaNumber& aCoefficient, AlbaNumber& rootFirstCoefficient, AlbaNumber& rootSecondCoefficient);

}  // namespace alba::algebra::Factorization
