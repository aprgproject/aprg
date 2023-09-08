#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class TermRaiseToTerms {
public:
explicit TermRaiseToTerms(TermsWithDetails const& termsInRaiseToPowerExpression);
TermRaiseToTerms();
TermRaiseToTerms(Term const& base, Terms const& exponents);
TermRaiseToTerms(Term const& base, Term const& exponent);
[[nodiscard]] bool isEmpty() const;
[[nodiscard]] bool doesEvenExponentCancellationHappen() const;
[[nodiscard]] Term getCombinedTerm() const;
[[nodiscard]] Term getCombinedExponents() const;
[[nodiscard]] Term const& getBase() const;
[[nodiscard]] TermsWithDetails const& getExponents() const;
Term& getBaseReference();
void setBase(Term const& base);
void setBaseAndExponent(Term const& base, Term const& exponent);
void setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors);
void setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(bool const shouldSimplify);
void setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(bool const shouldSimplify);
void simplify();

private:
static void simplifyConstantRaiseToFunction(
        Term& base, TermsWithDetails& exponents, Term const& exponentCombinedTerm);
static void simplifyMonomialRaiseToConstant(Term& base, Monomial const& monomialBase, AlbaNumber const& exponent);
static void simplifyPolynomialRaiseToPositiveInteger(
        Term& base, Polynomial const& polynomialBase, int const exponent);
static void simplifyAdditionAndSubtractionExpressionRaiseToPositiveInteger(
        Term& base, Expression const& expressionBase, int const exponent);
static void simplifyConstantRaiseToMultiplicationAndDivisionExpression(
        Term& base, TermsWithDetails& exponents, Term const& exponentCombinedTerm);
[[nodiscard]] Term getCombinedBaseAndExponents() const;
void simplifyByCheckingPolynomialRaiseToAnUnsignedIntIfNeeded();
void simplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseIfNeeded();
void simplifyBaseAndExponents();
void initializeUsingTermsInRaiseToPowerExpression(TermsWithDetails const& termsInRaiseToPowerExpression);
void initializeExponentsInTerms(Terms const& exponents);
Term m_base;
TermsWithDetails m_exponents;
bool m_shouldSimplifyToFactors;
bool m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
bool m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;

};

}  // namespace alba::algebra
