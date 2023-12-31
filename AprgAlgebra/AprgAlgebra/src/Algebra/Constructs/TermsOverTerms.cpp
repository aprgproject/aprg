#include "TermsOverTerms.hpp"

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Factorization/FactorizationOfTerm.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>

#include <algorithm>
#include <sstream>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

TermsOverTerms::TermsOverTerms()
    : m_factorizationConfiguration(Factorization::Configuration::getInstance().getConfigurationDetails()) {}

TermsOverTerms::TermsOverTerms(TermsWithDetails const& termsInMultiplicationAndDivision)
    : m_factorizationConfiguration(Factorization::Configuration::getInstance().getConfigurationDetails()) {
    TermsWithDetails numeratorsWithDetails;
    TermsWithDetails denominatorsWithDetails;
    segregateTermsWithPositiveAndNegativeAssociations(
        termsInMultiplicationAndDivision, numeratorsWithDetails, denominatorsWithDetails);
    retrieveTermsFromTermsWithDetails(m_numerators, numeratorsWithDetails);
    retrieveTermsFromTermsWithDetails(m_denominators, denominatorsWithDetails);
}

TermsOverTerms::TermsOverTerms(Terms const& numerators, Terms const& denominators)
    : m_numerators(numerators),
      m_denominators(denominators),
      m_factorizationConfiguration(Factorization::Configuration::getInstance().getConfigurationDetails()) {}

TermsOverTerms::TermsOverTerms(Terms&& numerators, Terms&& denominators)
    : m_numerators(numerators),
      m_denominators(denominators),
      m_factorizationConfiguration(Factorization::Configuration::getInstance().getConfigurationDetails()) {}

Term TermsOverTerms::getCombinedTerm() const {
    Term combinedTerm(1);
    if (m_shouldSimplifyToFactors) {
        combinedTerm =
            createTermWithMultiplicationAndDivisionTermsWithDetails(getNumeratorAndDenominatorAsTermWithDetails());
    } else {
        accumulateTermsForMultiplicationAndDivision(combinedTerm, getNumeratorAndDenominatorAsTermWithDetails());
    }
    return combinedTerm;
}

Term TermsOverTerms::getCombinedNumerator() const {
    Term combinedTerm(1);
    TermsWithDetails numeratorsWithPositiveAssociation;
    numeratorsWithPositiveAssociation.reserve(m_numerators.size());
    transform(
        m_numerators.cbegin(), m_numerators.cend(), back_inserter(numeratorsWithPositiveAssociation),
        [](Term const& numerator) { return TermWithDetails(numerator, TermAssociationType::Positive); });
    if (m_shouldSimplifyToFactors) {
        combinedTerm = createTermWithMultiplicationAndDivisionTermsWithDetails(numeratorsWithPositiveAssociation);
    } else {
        accumulateTermsForMultiplicationAndDivision(combinedTerm, numeratorsWithPositiveAssociation);
    }
    return combinedTerm;
}

Term TermsOverTerms::getCombinedDenominator() const {
    Term combinedTerm(1);
    TermsWithDetails denominatorsWithPositiveAssociation;
    denominatorsWithPositiveAssociation.reserve(m_denominators.size());
    transform(
        m_denominators.cbegin(), m_denominators.cend(), back_inserter(denominatorsWithPositiveAssociation),
        [](Term const& denominator) { return TermWithDetails(denominator, TermAssociationType::Positive); });
    if (m_shouldSimplifyToFactors) {
        combinedTerm = createTermWithMultiplicationAndDivisionTermsWithDetails(denominatorsWithPositiveAssociation);
    } else {
        accumulateTermsForMultiplicationAndDivision(combinedTerm, denominatorsWithPositiveAssociation);
    }
    return combinedTerm;
}

Terms const& TermsOverTerms::getNumerators() const { return m_numerators; }
Terms const& TermsOverTerms::getDenominators() const { return m_denominators; }

TermsRaiseToNumbers TermsOverTerms::getTermsRaiseToNumbers() const {
    TermsRaiseToNumbers result;
    Terms const factorizedNumerators(factorizeTerms(m_numerators));
    Terms const factorizedDenominators(factorizeTerms(m_denominators));

    result.putTerms(factorizedNumerators, TermAssociationType::Positive);
    result.putTerms(factorizedDenominators, TermAssociationType::Negative);
    return result;
}

TermsRaiseToTerms TermsOverTerms::getTermsRaiseToTerms() const {
    TermsRaiseToTerms result;
    Terms const factorizedNumerators(factorizeTerms(m_numerators));
    Terms const factorizedDenominators(factorizeTerms(m_denominators));

    result.putTerms(factorizedNumerators, TermAssociationType::Positive);
    result.putTerms(factorizedDenominators, TermAssociationType::Negative);
    return result;
}

TermsWithDetails TermsOverTerms::getNumeratorAndDenominatorAsTermWithDetails() const {
    TermsWithDetails result;
    result.reserve(m_numerators.size() + m_denominators.size());
    transform(m_numerators.cbegin(), m_numerators.cend(), back_inserter(result), [](Term const& numerator) {
        return TermWithDetails(numerator, TermAssociationType::Positive);
    });
    transform(m_denominators.cbegin(), m_denominators.cend(), back_inserter(result), [](Term const& denominator) {
        return TermWithDetails(denominator, TermAssociationType::Negative);
    });
    return result;
}

void TermsOverTerms::retrievePolynomialAndNonPolynomialNumerators(
    Polynomial& polynomialNumerator, Terms& nonPolynomialNumerators) const {
    retrievePolynomialAndNonPolynomialsTerms(m_numerators, polynomialNumerator, nonPolynomialNumerators);
}

void TermsOverTerms::retrievePolynomialAndNonPolynomialsDenominators(
    Polynomial& polynomialDenominator, Terms& nonPolynomialDenominators) const {
    retrievePolynomialAndNonPolynomialsTerms(m_denominators, polynomialDenominator, nonPolynomialDenominators);
}

void TermsOverTerms::flip() { swap(m_numerators, m_denominators); }

void TermsOverTerms::setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors) {
    m_shouldSimplifyToFactors = shouldSimplifyToFactors;
}

void TermsOverTerms::setFactorizationConfigurationDetails(
    Factorization::ConfigurationDetails const& configurationDetails) {
    m_factorizationConfiguration = configurationDetails;
}

void TermsOverTerms::simplify() {
    putTermsOnNumeratorAndDenominatorCorrectly(m_numerators, m_denominators);
    Terms newNumerators(factorize(m_numerators));
    Terms newDenominators(factorize(m_denominators));
    if (m_shouldSimplifyToFactors) {
        continueToSimplifyToFactors(newNumerators, newDenominators);
    } else {
        continueToSimplifyAndCombineFactors(newNumerators, newDenominators);
    }
}

Terms TermsOverTerms::factorizeIfNeeded(Terms const& terms) const {
    if (m_shouldSimplifyToFactors || !(m_numerators.empty() && m_denominators.empty())) {
        return factorize(terms);
    }
    return terms;
}

Terms TermsOverTerms::factorize(Terms const& terms) const {
    ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(m_factorizationConfiguration);

    return factorizeTerms(terms);
}

void TermsOverTerms::putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToTerms(
    Terms& numeratorTerms, Terms& denominatorTerms, TermsRaiseToTerms const& termsRaiseToTerms) const {
    for (auto const& [base, exponent] : termsRaiseToTerms.getBaseToExponentMap()) {
        if (!isIntegerConstant(exponent) || m_shouldSimplifyToFactors) {
            if (isANegativeTerm(exponent)) {
                TermRaiseToTerms const termRaiseToTerms(base, exponent * -1);
                denominatorTerms.emplace_back(termRaiseToTerms.getCombinedTerm());
            } else if (!isTheValue(exponent, 0)) {
                TermRaiseToTerms const termRaiseToTerms(base, exponent);
                numeratorTerms.emplace_back(termRaiseToTerms.getCombinedTerm());
            }
        } else {
            AlbaNumber const& exponentValue(exponent.getAsNumber());
            if (isANegativeTerm(exponent)) {
                populateTermsWithBase(denominatorTerms, base, exponentValue);
            } else if (!isTheValue(exponent, 0)) {
                populateTermsWithBase(numeratorTerms, base, exponentValue);
            }
        }
    }
}

void TermsOverTerms::putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToNumbers(
    Terms& numeratorTerms, Terms& denominatorTerms, TermsRaiseToNumbers const& termsRaiseToNumbers) const {
    for (auto const& [base, exponent] : termsRaiseToNumbers.getBaseToExponentMap()) {
        if (!exponent.isIntegerType() || m_shouldSimplifyToFactors) {
            if (exponent > 0) {
                TermRaiseToANumber const termRaiseToANumber(base, exponent);
                numeratorTerms.emplace_back(termRaiseToANumber.getCombinedTerm());
            } else if (exponent < 0) {
                TermRaiseToANumber const termRaiseToANumber(base, exponent * -1);
                denominatorTerms.emplace_back(termRaiseToANumber.getCombinedTerm());
            }
        } else {
            if (exponent > 0) {
                populateTermsWithBase(numeratorTerms, base, exponent);
            } else if (exponent < 0) {
                populateTermsWithBase(denominatorTerms, base, exponent);
            }
        }
    }
}

void TermsOverTerms::continueToSimplifyToFactors(Terms& factorizedNumerators, Terms& factorizedDenominators) {
    removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(factorizedNumerators, factorizedDenominators);
    m_numerators = factorizedNumerators;
    m_denominators = factorizedDenominators;
    simplifyMonomialsToPolynomialOverPolynomial();
}

void TermsOverTerms::continueToSimplifyAndCombineFactors(Terms& factorizedNumerators, Terms& factorizedDenominators) {
    bool const areSomeFactorsRemoved(
        removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(factorizedNumerators, factorizedDenominators));
    if (areSomeFactorsRemoved) {
        m_numerators = factorizedNumerators;
        m_denominators = factorizedDenominators;
    }
    simplifyPolynomialsToPolynomialOverPolynomial();
}

void TermsOverTerms::calculateBasesAndExponentsAndPutThatToNumeratorsAndDenominators(
    Terms& numeratorTerms, Terms& denominatorTerms) {
    TermsRaiseToTerms basesAndExponents;
    basesAndExponents.putTerms(numeratorTerms, TermAssociationType::Positive);
    basesAndExponents.putTerms(denominatorTerms, TermAssociationType::Negative);

    numeratorTerms.clear();
    denominatorTerms.clear();

    putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToTerms(numeratorTerms, denominatorTerms, basesAndExponents);
}

void TermsOverTerms::simplifyMonomialsToPolynomialOverPolynomial() {
    Terms monomialsNumerators;
    Terms nonMonomialNumerators;
    Terms monomialDenominators;
    Terms nonMonomialDenominators;
    segregateMonomialsAndNonMonomials(m_numerators, monomialsNumerators, nonMonomialNumerators);
    segregateMonomialsAndNonMonomials(m_denominators, monomialDenominators, nonMonomialDenominators);
    Polynomial polynomialNumerator(multiplyPolynomialTerms(monomialsNumerators));
    Polynomial polynomialDenominator(multiplyPolynomialTerms(monomialDenominators));
    simplifyPolynomialNumeratorAndPolynomialDenominator(polynomialNumerator, polynomialDenominator);
    clearTermsThenEmplacePolynomialAndRemainingTerms(polynomialNumerator, nonMonomialNumerators, m_numerators);
    clearTermsThenEmplacePolynomialAndRemainingTerms(polynomialDenominator, nonMonomialDenominators, m_denominators);
}

void TermsOverTerms::simplifyPolynomialsToPolynomialOverPolynomial() {
    Terms polynomialNumerators;
    Terms nonPolynomialNumerators;
    Terms polynomialDenominators;
    Terms nonPolynomialDenominators;
    segregatePolynomialAndNonPolynomials(m_numerators, polynomialNumerators, nonPolynomialNumerators);
    segregatePolynomialAndNonPolynomials(m_denominators, polynomialDenominators, nonPolynomialDenominators);
    Polynomial polynomialNumerator(multiplyPolynomialTerms(polynomialNumerators));
    Polynomial polynomialDenominator(multiplyPolynomialTerms(polynomialDenominators));
    simplifyPolynomialNumeratorAndPolynomialDenominator(polynomialNumerator, polynomialDenominator);
    clearTermsThenEmplacePolynomialAndRemainingTerms(polynomialNumerator, nonPolynomialNumerators, m_numerators);
    clearTermsThenEmplacePolynomialAndRemainingTerms(polynomialDenominator, nonPolynomialDenominators, m_denominators);
}

bool TermsOverTerms::removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(Terms& numerators, Terms& denominators) {
    int const previousNumberOfNumerators = static_cast<int>(numerators.size());
    int const previousNumberOfDenominators = static_cast<int>(denominators.size());

    handleZerosInNumeratorOrDenominator(denominators, numerators);
    removeTermsThatHaveNoEffect(numerators);
    removeTermsThatHaveNoEffect(denominators);
    calculateBasesAndExponentsAndPutThatToNumeratorsAndDenominators(numerators, denominators);

    return previousNumberOfNumerators != static_cast<int>(numerators.size()) ||
           previousNumberOfDenominators != static_cast<int>(denominators.size());
}

void TermsOverTerms::clearTermsThenEmplacePolynomialAndRemainingTerms(
    Polynomial const& polynomialNumerator, Terms const& remainingNumerators, Terms& termsToUpdate) {
    termsToUpdate.clear();
    emplacePolynomialIfNeeded(termsToUpdate, polynomialNumerator);
    termsToUpdate.reserve(remainingNumerators.size());
    copy(remainingNumerators.cbegin(), remainingNumerators.cend(), back_inserter(termsToUpdate));
}

void TermsOverTerms::emplacePolynomialIfNeeded(Terms& termsResult, Polynomial const& polynomial) {
    if (isTheValue(polynomial, 0)) {
        termsResult.emplace_back(0);
    } else if (!isTheValue(polynomial, 1)) {
        termsResult.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomial));
    }
}

void TermsOverTerms::retrievePolynomialAndNonPolynomialsTerms(
    Terms const& termsToCheck, Polynomial& polynomial, Terms& nonPolynomialTerms) {
    polynomial = (createPolynomialFromNumber(1));
    for (Term const& termToCheck : termsToCheck) {
        if (canBeConvertedToPolynomial(termToCheck)) {
            polynomial.multiplyPolynomial(createPolynomialIfPossible(termToCheck));
        } else {
            nonPolynomialTerms.emplace_back(termToCheck);
        }
    }
}

void TermsOverTerms::handleZerosInNumeratorOrDenominator(Terms& denominators, Terms& numerators) {
    bool const hasZeroOnNumerators(hasZero(numerators));
    bool const hasZeroOnDenominators(hasZero(denominators));
    if (hasZeroOnNumerators && hasZeroOnDenominators) {
        numerators.clear();
        denominators.clear();
        numerators.emplace_back(ALBA_NUMBER_NOT_A_NUMBER);
    } else if (hasZeroOnNumerators) {
        numerators.clear();
        denominators.clear();
        numerators.emplace_back(0);
    } else if (hasZeroOnDenominators) {
        denominators.clear();
        denominators.emplace_back(0);
    }
}

void TermsOverTerms::populateTermsWithBase(Terms& termsToUpdate, Term const& base, AlbaNumber const& exponent) {
    int const exponentCount = static_cast<int>(getAbsoluteValue(exponent).getInteger());
    for (int i = 0; i < exponentCount; ++i) {
        termsToUpdate.emplace_back(base);
    }
}

void TermsOverTerms::removeTermsThatHaveNoEffect(Terms& terms) {
    terms.erase(
        remove_if(
            terms.begin(), terms.end(),
            [](Term const& term) { return willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term); }),
        terms.end());
}

void TermsOverTerms::putTermsOnNumeratorAndDenominatorCorrectly(Terms& numerators, Terms& denominators) {
    Terms retainedNumerators;
    Terms retainedDenominators;
    Terms termsToPutInNumerators;
    Terms termsToPutInDenominators;
    putTermsToRetainAndOnTheOtherSide(numerators, retainedNumerators, termsToPutInDenominators);
    putTermsToRetainAndOnTheOtherSide(denominators, retainedDenominators, termsToPutInNumerators);

    numerators.clear();
    denominators.clear();

    numerators.reserve(retainedNumerators.size() + termsToPutInNumerators.size());
    copy(retainedNumerators.cbegin(), retainedNumerators.cend(), back_inserter(numerators));
    copy(termsToPutInNumerators.cbegin(), termsToPutInNumerators.cend(), back_inserter(numerators));

    denominators.reserve(retainedDenominators.size() + termsToPutInDenominators.size());
    copy(retainedDenominators.cbegin(), retainedDenominators.cend(), back_inserter(denominators));
    copy(termsToPutInDenominators.cbegin(), termsToPutInDenominators.cend(), back_inserter(denominators));
}

void TermsOverTerms::putTermsToRetainAndOnTheOtherSide(
    Terms const& termsToCheck, Terms& termsToRetain, Terms& termsToPutOnTheOtherSide) {
    for (Term const& termToCheck : termsToCheck) {
        bool isNeededToPutOnTheOtherSide(false);
        Term transformedTermOnTheOtherSide;
        if (termToCheck.isExpression()) {
            Expression const& expression(termToCheck.getAsExpression());
            TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
            if (OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel() && termsWithDetails.size() == 2) {
                Term const& base(getTermConstReferenceFromUniquePointer(termsWithDetails[0].baseTermPointer));
                Term const& exponent(getTermConstReferenceFromUniquePointer(termsWithDetails[1].baseTermPointer));
                isNeededToPutOnTheOtherSide = isANegativeTerm(exponent);
                transformedTermOnTheOtherSide = createExpressionIfPossible({base, "^", negateTerm(exponent)});
            }
        }
        if (isNeededToPutOnTheOtherSide) {
            transformedTermOnTheOtherSide.simplify();
            termsToPutOnTheOtherSide.emplace_back(transformedTermOnTheOtherSide);
        } else {
            termsToRetain.emplace_back(termToCheck);
        }
    }
}

void TermsOverTerms::simplifyPolynomialNumeratorAndPolynomialDenominator(
    Polynomial& polynomialNumerator, Polynomial& polynomialDenominator) {
    PolynomialOverPolynomial numeratorAndDenominator(polynomialNumerator, polynomialDenominator);
    numeratorAndDenominator.simplifyWithoutFactorization();
    polynomialNumerator = numeratorAndDenominator.getNumerator();
    polynomialDenominator = numeratorAndDenominator.getDenominator();
}

Polynomial TermsOverTerms::multiplyPolynomialTerms(Terms const& polynomialTerms) {
    Polynomial polynomialResult(createPolynomialFromNumber(1));
    for (Term const& polynomialTerm : polynomialTerms) {
        if (canBeConvertedToPolynomial(polynomialTerm)) {
            polynomialResult.multiplyPolynomial(createPolynomialIfPossible(polynomialTerm));
        }
    }
    return polynomialResult;
}

ostream& operator<<(ostream& out, TermsOverTerms const& termsOverTerms) {
    printParameterWithName(out, "Numerators:", termsOverTerms.m_numerators);
    printParameterWithName(out, "Denominators:", termsOverTerms.m_denominators);
    return out;
}

}  // namespace alba::algebra
