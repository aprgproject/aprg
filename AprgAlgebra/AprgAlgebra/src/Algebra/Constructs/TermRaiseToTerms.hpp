#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class TermRaiseToTerms {
public:
    explicit TermRaiseToTerms(TermsWithDetails const& termsInRaiseToPowerExpression);
    TermRaiseToTerms() = default;
    TermRaiseToTerms(Term const& base, Terms const& exponents);
    TermRaiseToTerms(Term&& base, Terms const& exponents);
    TermRaiseToTerms(Term const& base, Term const& exponent);
    TermRaiseToTerms(Term&& base, Term const& exponent);
    [[nodiscard]] Term getCombinedTerm() const;
    [[nodiscard]] Term getCombinedExponents() const;
    [[nodiscard]] Term const& getBase() const;
    [[nodiscard]] TermsWithDetails const& getExponents() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool doesEvenExponentCancellationHappen() const;
    void setBase(Term const& base);
    void setBaseAndExponent(Term const& base, Term const& exponent);
    void setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors);
    void setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(bool const shouldSimplify);
    void setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(bool const shouldSimplify);
    void simplify();
    Term& getBaseReference();

private:
    [[nodiscard]] Term getCombinedBaseAndExponents() const;
    void simplifyByCheckingPolynomialRaiseToAnUnsignedIntIfNeeded();
    void simplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseIfNeeded();
    void simplifyBaseAndExponents();
    void initializeUsingTermsInRaiseToPowerExpression(TermsWithDetails const& termsInRaiseToPowerExpression);
    void initializeExponentsInTerms(Terms const& exponents);
    static void simplifyConstantRaiseToFunction(
        Term& base, TermsWithDetails& exponents, Term const& exponentCombinedTerm);
    static void simplifyMonomialRaiseToConstant(Term& base, Monomial const& monomialBase, AlbaNumber const& exponent);
    static void simplifyPolynomialRaiseToPositiveInteger(
        Term& base, Polynomial const& polynomialBase, int const exponent);
    static void simplifyAdditionAndSubtractionExpressionRaiseToPositiveInteger(
        Term& base, Expression const& expressionBase, int const exponent);
    static void simplifyConstantRaiseToMultiplicationAndDivisionExpression(
        Term& base, TermsWithDetails& exponents, Term const& exponentCombinedTerm);
    Term m_base;
    TermsWithDetails m_exponents;
    bool m_shouldSimplifyToFactors{false};
    bool m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt{false};
    bool m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase{false};
};

}  // namespace alba::algebra
