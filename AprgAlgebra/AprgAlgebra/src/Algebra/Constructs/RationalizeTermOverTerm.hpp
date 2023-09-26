#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class RationalizeTermOverTerm {
public:
    struct RationalizationDetails {
        bool canBeRationalized;
        Term termToRationalize;
        Term otherTerm;
    };

    RationalizeTermOverTerm() = default;
    RationalizeTermOverTerm(Term const& numerator, Term const& denominator);
    RationalizeTermOverTerm(Term&& numerator, Term&& denominator);
    [[nodiscard]] Term const& getNumerator() const;
    [[nodiscard]] Term const& getDenominator() const;
    [[nodiscard]] Term getCombinedTerm() const;
    void rationalizeNumerator();
    void rationalizeDenominator();

private:
    static void rationalize(Term& termToRationalize, Term& otherTerm);
    static void simplifyForRationalize(Term& term);
    static void retrieveTermsForRationalization(Term& rationalizedTerm, Term& multiplier, Term const& term);

    static void retrieveTermsForRationalizationForPolynomial(
        Term& rationalizedTerm, Term& multiplier, Polynomial const& polynomial);

    static void retrieveTermsForRationalizationForPolynomial(
        Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial);

    static void retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByTwo(
        Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial);

    static void retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByThree(
        Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial);

    static void retrieveTermsForRationalizationForExpression(
        Term& rationalizedTerm, Term& multiplier, Expression const& expression);

    static void retrieveTermsForRationalizationForExpression(
        Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails);

    static void retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByTwo(
        Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails);

    static void retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByThree(
        Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails);

    Term m_numerator;
    Term m_denominator;
};

}  // namespace alba::algebra
