#pragma once

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Constructs/TermsOverTerms.hpp>

namespace alba::algebra {

void createTermRaiseToANumberFromRaiseToPowerExpression(TermRaiseToANumber& result, Expression const& expression);

void createTermRaiseToANumberFromMultiplicationAndDivisionExpression(
    TermRaiseToANumber& result, Expression const& expression);

void createTermRaiseToTermsFromRaiseToPowerExpression(TermRaiseToTerms& result, Expression const& expression);

void createTermRaiseToTermsFromMultiplicationAndDivisionExpression(
    TermRaiseToTerms& result, Expression const& expression);

PolynomialOverPolynomialOptional createPolynomialOverPolynomialFromTermIfPossible(Term const& term);
TermRaiseToANumber createTermRaiseToANumberFromTerm(Term const& term);
TermRaiseToANumber createTermRaiseToANumberFromMonomial(Monomial const& monomial);
TermRaiseToANumber createTermRaiseToANumberFromPolynomial(Polynomial const& polynomial);
TermRaiseToANumber createTermRaiseToANumberFromExpression(Expression const& expression);
TermRaiseToTerms createTermRaiseToTermsFromTerm(Term const& term);
TermRaiseToTerms createTermRaiseToTermsFromExpression(Expression const& expression);
TermsOverTerms createTermsOverTermsFromTerm(Term const& term);

}  // namespace alba::algebra
