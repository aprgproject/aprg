#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba::algebra::Factorization {

void factorizeIncreasingAndDecreasingExponentsFormIfPossible(Polynomials& result, Polynomial const& polynomial);

void factorizePolynomialForm(
    Polynomials& result, Polynomial const& polynomial, AlbaNumbers const& coefficients,
    Monomial::VariablesToExponentsMap const& firstVariableExponent,
    Monomial::VariablesToExponentsMap const& secondVariableExponent);

void fixCoefficientsOfFactors(
    AlbaNumber& aCoefficient, AlbaNumber& rootFirstCoefficient, AlbaNumber& rootSecondCoefficient);

AlbaNumber getMaxAbsoluteValueForRootFinding(AlbaNumbers const& coefficients);

AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(
    Polynomial const& polynomial, Monomials const& monomialsWithExponentsInOrder);

AlbaNumbers calculatePolynomialRoots(AlbaNumbers const& coefficients);

AlbaNumbers calculatePolynomialRootsUsingBrentMethod(
    AlbaNumbers const& previousDerivativeRoots, AlbaNumbers const& coefficients);

AlbaNumbers getDerivativeCoefficients(AlbaNumbers const& coefficients);

Monomials getMonomialsWithExponentsInOrder(
    int const exponentDivisor, Monomial const& firstInPolynomial, Monomial const& lastInPolynomial);

Polynomials factorizeIncreasingAndDecreasingExponentsForm(Polynomial const& polynomial);
int calculateMaxExponentDivisor(Monomial const& firstMonomial, Monomial const& lastMonomial);

bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
    Monomials const& monomialsToCheck, Monomials const& monomialsWithExponentsInOrder);

bool areRootsAcceptable(AlbaNumbers const& rootValues);

}  // namespace alba::algebra::Factorization
