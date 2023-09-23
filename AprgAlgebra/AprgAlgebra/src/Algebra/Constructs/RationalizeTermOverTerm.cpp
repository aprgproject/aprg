#include "RationalizeTermOverTerm.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Common/Math/Helpers/FactorAndMultiplesHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;

namespace alba::algebra {

RationalizeTermOverTerm::RationalizeTermOverTerm(Term const& numerator, Term const& denominator)
    : m_numerator(numerator), m_denominator(denominator) {}
RationalizeTermOverTerm::RationalizeTermOverTerm(Term&& numerator, Term&& denominator)
    : m_numerator(numerator), m_denominator(denominator) {}
Term const& RationalizeTermOverTerm::getNumerator() const { return m_numerator; }
Term const& RationalizeTermOverTerm::getDenominator() const { return m_denominator; }
Term RationalizeTermOverTerm::getCombinedTerm() const { return m_numerator / m_denominator; }
void RationalizeTermOverTerm::rationalizeNumerator() { rationalize(m_numerator, m_denominator); }
void RationalizeTermOverTerm::rationalizeDenominator() { rationalize(m_denominator, m_numerator); }

void RationalizeTermOverTerm::rationalize(Term& termToRationalize, Term& otherTerm) {
    Term rationalizedTerm;
    Term multiplier;
    retrieveTermsForRationalization(rationalizedTerm, multiplier, termToRationalize);
    while (!multiplier.isEmpty()) {
        termToRationalize = rationalizedTerm;
        otherTerm = otherTerm * multiplier;
        simplifyForRationalize(termToRationalize);
        simplifyForRationalize(otherTerm);
        rationalizedTerm.clear();
        multiplier.clear();
        retrieveTermsForRationalization(rationalizedTerm, multiplier, termToRationalize);
    }
}

void RationalizeTermOverTerm::simplifyForRationalize(Term& term) {
    SimplificationOfExpression::ConfigurationDetails rationalizeConfigurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    rationalizeConfigurationDetails.shouldSimplifyToACommonDenominator = true;
    rationalizeConfigurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    rationalizeConfigurationDetails.shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = true;

    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(rationalizeConfigurationDetails);
    term.simplify();
}

void RationalizeTermOverTerm::retrieveTermsForRationalization(
    Term& rationalizedTerm, Term& multiplier, Term const& term) {
    if (term.isPolynomial()) {
        retrieveTermsForRationalizationForPolynomial(rationalizedTerm, multiplier, term.getAsPolynomial());
    } else if (term.isExpression()) {
        retrieveTermsForRationalizationForExpression(rationalizedTerm, multiplier, term.getAsExpression());
    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForPolynomial(
    Term& rationalizedTerm, Term& multiplier, Polynomial const& polynomial) {
    Monomials const& monomials(polynomial.getMonomials());
    if (monomials.size() == 2) {
        Monomial const& firstMonomial(monomials[0]);
        Monomial const& secondMonomial(monomials[1]);
        retrieveTermsForRationalizationForPolynomial(rationalizedTerm, multiplier, firstMonomial, secondMonomial);
    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForPolynomial(
    Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial) {
    AlbaNumber const gcfOfExponents = getGreatestCommonFactor(
        getGcfOfExponentsInMonomial(firstMonomial), getGcfOfExponentsInMonomial(secondMonomial));
    if (gcfOfExponents.isFractionType()) {
        AlbaNumber::FractionData const exponentFraction(gcfOfExponents.getFractionData());
        if (isDivisible(exponentFraction.denominator, 2U)) {
            retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByTwo(
                rationalizedTerm, multiplier, firstMonomial, secondMonomial);
        } else if (isDivisible(exponentFraction.denominator, 3U)) {
            retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByThree(
                rationalizedTerm, multiplier, firstMonomial, secondMonomial);
        }
    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByTwo(
    Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial) {
    Monomial newSecondMonomialOfRemainder(secondMonomial);
    newSecondMonomialOfRemainder.multiplyNumber(-1);
    multiplier = Polynomial{firstMonomial, newSecondMonomialOfRemainder};

    Monomial rationalizedFirstMonomial(firstMonomial);
    rationalizedFirstMonomial.raiseToPowerNumber(2);
    Monomial rationalizedSecondMonomial(secondMonomial);
    rationalizedSecondMonomial.raiseToPowerNumber(2);
    rationalizedSecondMonomial.multiplyNumber(-1);
    rationalizedTerm = Polynomial{rationalizedFirstMonomial, rationalizedSecondMonomial};
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByThree(
    Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial) {
    Monomial newFirstMonomial(firstMonomial);
    Monomial newThirdMonomial(secondMonomial);
    newFirstMonomial.raiseToPowerNumber(2);
    newThirdMonomial.raiseToPowerNumber(2);
    Monomial newSecondMonomial(firstMonomial);
    newSecondMonomial.multiplyMonomial(secondMonomial);
    newSecondMonomial.multiplyNumber(-1);
    multiplier = Polynomial{newFirstMonomial, newSecondMonomial, newThirdMonomial};

    Monomial rationalizedFirstMonomial(firstMonomial);
    rationalizedFirstMonomial.raiseToPowerNumber(3);
    Monomial rationalizedSecondMonomial(secondMonomial);
    rationalizedSecondMonomial.raiseToPowerNumber(3);
    rationalizedTerm = Polynomial{rationalizedFirstMonomial, rationalizedSecondMonomial};
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForExpression(
    Term& rationalizedTerm, Term& multiplier, Expression const& expression) {
    if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
        TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
        if (termsWithDetails.size() == 2) {
            TermWithDetails const& firstTermWithDetails(termsWithDetails[0]);
            TermWithDetails const& secondTermWithDetails(termsWithDetails[1]);
            retrieveTermsForRationalizationForExpression(
                rationalizedTerm, multiplier, firstTermWithDetails, secondTermWithDetails);
        }
    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForExpression(
    Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
    TermWithDetails const& secondTermWithDetails) {
    Term const& firstTerm(getTermConstReferenceFromUniquePointer(firstTermWithDetails.baseTermPointer));
    Term const& secondTerm(getTermConstReferenceFromUniquePointer(secondTermWithDetails.baseTermPointer));
    TermRaiseToANumber const firstTermRaiseToANumber(createTermRaiseToANumberFromTerm(firstTerm));
    TermRaiseToANumber const secondTermRaiseToANumber(createTermRaiseToANumberFromTerm(secondTerm));

    AlbaNumber const gcfOfExponents =
        getGreatestCommonFactor(firstTermRaiseToANumber.getExponent(), secondTermRaiseToANumber.getExponent());
    if (gcfOfExponents.isFractionType()) {
        AlbaNumber::FractionData const exponentFraction(gcfOfExponents.getFractionData());
        if (isDivisible(exponentFraction.denominator, 2U)) {
            retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByTwo(
                rationalizedTerm, multiplier, firstTermWithDetails, secondTermWithDetails);
        } else if (isDivisible(exponentFraction.denominator, 3U)) {
            retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByThree(
                rationalizedTerm, multiplier, firstTermWithDetails, secondTermWithDetails);
        }
    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByTwo(
    Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
    TermWithDetails const& secondTermWithDetails) {
    Term const& firstTerm(getTermConstReferenceFromUniquePointer(firstTermWithDetails.baseTermPointer));
    Term const& secondTerm(getTermConstReferenceFromUniquePointer(secondTermWithDetails.baseTermPointer));

    TermWithDetails secondMultiplierTerm(secondTermWithDetails);
    secondMultiplierTerm.association =
        secondTermWithDetails.hasPositiveAssociation() ? TermAssociationType::Negative : TermAssociationType::Positive;
    TermsWithDetails const multiplierTermsWithDetails{firstTermWithDetails, secondMultiplierTerm};
    multiplier = createTermWithAdditionAndSubtractionTermsWithDetails(multiplierTermsWithDetails);

    Term const firstRationalizedTerm(firstTerm ^ 2);
    Term const secondRationalizedTerm(secondTerm ^ 2);
    TermWithDetails const firstRationalizedTermWithDetails(firstRationalizedTerm, TermAssociationType::Positive);
    TermWithDetails const secondRationalizedTermTermWithDetails(secondRationalizedTerm, TermAssociationType::Negative);
    TermsWithDetails const rationalizedTermsWithDetails{
        firstRationalizedTermWithDetails, secondRationalizedTermTermWithDetails};
    rationalizedTerm = createTermWithAdditionAndSubtractionTermsWithDetails(rationalizedTermsWithDetails);
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByThree(
    Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
    TermWithDetails const& secondTermWithDetails) {
    Term const& firstTerm(getTermConstReferenceFromUniquePointer(firstTermWithDetails.baseTermPointer));
    Term const& secondTerm(getTermConstReferenceFromUniquePointer(secondTermWithDetails.baseTermPointer));

    Term const firstMultiplierTerm(firstTerm ^ 2);
    Term const secondMultiplierTerm(firstTerm * secondTerm);
    Term const thirdMultiplierTerm(secondTerm ^ 2);
    TermAssociationType const newSecondAssociationType =
        secondTermWithDetails.hasPositiveAssociation() ? TermAssociationType::Negative : TermAssociationType::Positive;
    TermWithDetails const firstMultiplierTermWithDetails(firstMultiplierTerm, TermAssociationType::Positive);
    TermWithDetails const secondMultiplierTermWithDetails(secondMultiplierTerm, newSecondAssociationType);
    TermWithDetails const thirdMultiplierTermWithDetails(thirdMultiplierTerm, TermAssociationType::Positive);
    TermsWithDetails const multiplierTermsWithDetails{
        firstMultiplierTermWithDetails, secondMultiplierTermWithDetails, thirdMultiplierTermWithDetails};
    multiplier = createTermWithAdditionAndSubtractionTermsWithDetails(multiplierTermsWithDetails);

    Term const firstRationalizedTerm(firstTerm ^ 3);
    Term const secondRationalizedTerm(secondTerm ^ 3);
    TermWithDetails const firstRationalizedTermWithDetails(firstRationalizedTerm, firstTermWithDetails.association);
    TermWithDetails const secondRationalizedTermTermWithDetails(
        secondRationalizedTerm, secondTermWithDetails.association);
    TermsWithDetails const rationalizedTermsWithDetails{
        firstRationalizedTermWithDetails, secondRationalizedTermTermWithDetails};
    rationalizedTerm = createTermWithAdditionAndSubtractionTermsWithDetails(rationalizedTermsWithDetails);
}

RationalizeTermOverTerm::RationalizeTermOverTerm() = default;

}  // namespace alba::algebra
