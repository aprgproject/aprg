#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {
Operator reverse(Operator const& operatorToReverse);
Term simplifyAndConvertMonomialToSimplestTerm(Monomial const& monomial);
Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial);
Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression);
Term simplifyAndConvertFunctionToSimplestTerm(Function const& functionObject);
Term convertMonomialToSimplestTerm(Monomial const& monomial);
Term convertPolynomialToSimplestTerm(Polynomial const& polynomial);
Term convertExpressionToSimplestTerm(Expression const& expression);
Term convertFunctionToSimplestTerm(Function const& functionObject);
bool canBeConvertedToConstant(Polynomial const& polynomial);
bool canBeConvertedToMonomial(Term const& term);
bool canBeConvertedToPolynomial(Term const& term);
}  // namespace alba::algebra
