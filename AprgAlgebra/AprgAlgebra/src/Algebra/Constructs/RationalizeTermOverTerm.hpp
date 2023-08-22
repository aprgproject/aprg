#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

class RationalizeTermOverTerm {
public:
    struct RationalizationDetails {
        bool canBeRationalized;
        Term termToRationalize;
        Term otherTerm;
    };
    RationalizeTermOverTerm();
    RationalizeTermOverTerm(Term const& numerator, Term const& denominator);

    Term const& getNumerator() const;
    Term const& getDenominator() const;
    Term getCombinedTerm() const;

    void rationalizeNumerator();
    void rationalizeDenominator();

private:
    void rationalize(Term& termToRationalize, Term& otherTerm);
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

}  // namespace algebra

}  // namespace alba
