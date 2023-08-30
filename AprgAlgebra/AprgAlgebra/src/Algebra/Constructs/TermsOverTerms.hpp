#pragma once

#include <Algebra/Constructs/TermsRaiseToNumbers.hpp>
#include <Algebra/Constructs/TermsRaiseToTerms.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

class TermsOverTerms {
public:
    TermsOverTerms();
    explicit TermsOverTerms(TermsWithDetails const& termsInMultiplicationAndDivision);
    TermsOverTerms(Terms const& numerators, Terms const& denominators);

    [[nodiscard]] Terms const& getNumerators() const;
    [[nodiscard]] Terms const& getDenominators() const;
    [[nodiscard]] TermsWithDetails getNumeratorAndDenominatorAsTermWithDetails() const;
    [[nodiscard]] Term getCombinedTerm() const;
    [[nodiscard]] Term getCombinedNumerator() const;
    [[nodiscard]] Term getCombinedDenominator() const;
    void retrievePolynomialAndNonPolynomialNumerators(
        Polynomial& polynomialNumerator, Terms& nonPolynomialNumerators) const;
    void retrievePolynomialAndNonPolynomialsDenominators(
        Polynomial& polynomialDenominator, Terms& nonPolynomialDenominators) const;
    [[nodiscard]] TermsRaiseToNumbers getTermsRaiseToNumbers() const;
    [[nodiscard]] TermsRaiseToTerms getTermsRaiseToTerms() const;

    void flip();

    void setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors);
    void setFactorizationConfigurationDetails(Factorization::ConfigurationDetails const& configurationDetails);

    void simplify();

private:
    [[nodiscard]] Terms factorizeIfNeeded(Terms const& terms) const;
    [[nodiscard]] Terms factorize(Terms const& terms) const;
    void continueToSimplifyToFactors(Terms& factorizedNumerators, Terms& factorizedDenominators);
    void continueToSimplifyAndCombineFactors(Terms& factorizedNumerators, Terms& factorizedDenominators);
    static Polynomial multiplyPolynomialTerms(Terms const& polynomialTerms);
    bool removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(Terms& numerators, Terms& denominators);
    static void clearTermsThenEmplacePolynomialAndRemainingTerms(
        Polynomial const& polynomialNumerator, Terms const& remainingNumerators, Terms& termsToUpdate);
    static void emplacePolynomialIfNeeded(Terms& termsResult, Polynomial const& polynomialNumerator);
    static void retrievePolynomialAndNonPolynomialsTerms(
        Terms const& termsToCheck, Polynomial& polynomial, Terms& nonPolynomialTerms);
    void calculateBasesAndExponentsAndPutThatToNumeratorsAndDenominators(
        Terms& numeratorTerms, Terms& denominatorTerms);
    void putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToTerms(
        Terms& numeratorTerms, Terms& denominatorTerms, TermsRaiseToTerms const& termsRaiseToTerms) const;
    void putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToNumbers(
        Terms& numeratorTerms, Terms& denominatorTerms, TermsRaiseToNumbers const& termsRaiseToNumbers) const;
    static void handleZerosInNumeratorOrDenominator(Terms& denominators, Terms& numerators);
    static void populateTermsWithBase(Terms& termsToUpdate, Term const& base, AlbaNumber const& exponent);
    static void removeTermsThatHaveNoEffect(Terms& terms);
    static void putTermsOnNumeratorAndDenominatorCorrectly(Terms& numerators, Terms& denominators);
    static void putTermsToRetainAndOnTheOtherSide(
        Terms const& termsToCheck, Terms& termsToRetain, Terms& termsToPutOnTheOtherSide);
    static void simplifyPolynomialNumeratorAndPolynomialDenominator(
        Polynomial& polynomialNumerator, Polynomial& polynomialDenominator);
    void simplifyMonomialsToPolynomialOverPolynomial();
    void simplifyPolynomialsToPolynomialOverPolynomial();

    friend std::ostream& operator<<(std::ostream& out, TermsOverTerms const& termsOverTerms);

    Terms m_numerators;
    Terms m_denominators;
    bool m_shouldSimplifyToFactors;
    Factorization::ConfigurationDetails m_factorizationConfiguration;
};

using VectorOfTermsOverTerms = std::vector<TermsOverTerms>;

}  // namespace alba::algebra
