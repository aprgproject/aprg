#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

namespace alba::algebra::Factorization {
void simplifyThenEmplaceBackIfPolynomialIsNotEmpty(Polynomials& polynomials, Polynomial const& polynomial);
void emplaceBackIfPolynomialIsNotEmpty(Polynomials& polynomials, Polynomial const& polynomial);
void simplifyAndEmplaceBackPolynomialIfListIsEmpty(Polynomials& existingPolynomials, Polynomial const& polynomial);
bool areExponentsDivisible(Monomial const& monomial, int const divisor);
bool isPerfectSquare(Monomial const& monomial);
bool isPerfectCube(Monomial const& monomial);
bool isPerfectNthPower(Monomial const& monomial, int const nthPower);
bool doesNotNeedToBeFactorized(Polynomial const& polynomial);
bool doesContainOnlyConstants(Polynomials const& polynomials);
bool IsEmptyOrContainConstantsOrOneNonConstant(Polynomials const& polynomials);
}  // namespace alba::algebra::Factorization
