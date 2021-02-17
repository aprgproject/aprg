#include "TermsOverTerms.hpp"

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
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
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <sstream>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

TermsOverTerms::TermsOverTerms()
    : m_numerators()
    , m_denominators()
    , m_shouldSimplifyToFactors(false)
    , m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(false)
{}

TermsOverTerms::TermsOverTerms(
        TermsWithDetails const& termsInMultiplicationAndDivision)
    : m_shouldSimplifyToFactors(false)
    , m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(false)
{
    TermsWithDetails numeratorsWithDetails;
    TermsWithDetails denominatorsWithDetails;
    segregateTermsWithPositiveAndNegativeAssociations(termsInMultiplicationAndDivision, numeratorsWithDetails, denominatorsWithDetails);
    retrieveTermsFromTermsWithDetails(m_numerators, numeratorsWithDetails);
    retrieveTermsFromTermsWithDetails(m_denominators, denominatorsWithDetails);
}

TermsOverTerms::TermsOverTerms(Terms const& numerators, Terms const& denominators)
    : m_numerators(numerators)
    , m_denominators(denominators)
    , m_shouldSimplifyToFactors(false)
    , m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(false)
{}

TermsOverTerms::TermsOverTerms(
        TermsWithDetails const& numeratorsWithDetails,
        TermsWithDetails const& denominatorsWithDetails)
    : m_shouldSimplifyToFactors(false)
    , m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(false)
{
    retrieveTermsFromTermsWithDetails(m_numerators, numeratorsWithDetails);
    retrieveTermsFromTermsWithDetails(m_denominators, denominatorsWithDetails);
}

Terms const& TermsOverTerms::getNumerators() const
{
    return m_numerators;
}

Terms const& TermsOverTerms::getDenominators() const
{
    return m_denominators;
}

TermsWithDetails TermsOverTerms::getNumeratorAndDenominatorAsTermWithDetails() const
{
    TermsWithDetails result;
    for(Term const& numerator : m_numerators)
    {
        result.emplace_back(numerator, TermAssociationType::Positive);
    }
    for(Term const& denominator : m_denominators)
    {
        result.emplace_back(denominator, TermAssociationType::Negative);
    }
    return result;
}

Term TermsOverTerms::getCombinedTerm() const
{
    Term combinedTerm(1);
    if(m_shouldSimplifyToFactors)
    {
        combinedTerm = createTermWithMultiplicationAndDivisionTermsWithDetails(getNumeratorAndDenominatorAsTermWithDetails());
    }
    else
    {
        accumulateTermsForMultiplicationAndDivision(
                    combinedTerm,
                    getNumeratorAndDenominatorAsTermWithDetails());
    }
    return combinedTerm;
}

Term TermsOverTerms::getCombinedNumerator() const
{
    Term combinedTerm(1);
    TermsWithDetails numeratorsWithPositiveAssociation;
    for(Term const& numerator : m_numerators)
    {
        numeratorsWithPositiveAssociation.emplace_back(numerator, TermAssociationType::Positive);
    }
    if(m_shouldSimplifyToFactors)
    {
        combinedTerm = createTermWithMultiplicationAndDivisionTermsWithDetails(numeratorsWithPositiveAssociation);
    }
    else
    {
        accumulateTermsForMultiplicationAndDivision(combinedTerm, numeratorsWithPositiveAssociation);
    }
    return combinedTerm;
}

Term TermsOverTerms::getCombinedDenominator() const
{
    Term combinedTerm(1);
    TermsWithDetails denominatorsWithPositiveAssociation;
    for(Term const& denominator : m_denominators)
    {
        denominatorsWithPositiveAssociation.emplace_back(denominator, TermAssociationType::Positive);
    }
    if(m_shouldSimplifyToFactors)
    {
        combinedTerm = createTermWithMultiplicationAndDivisionTermsWithDetails(denominatorsWithPositiveAssociation);
    }
    else
    {
        accumulateTermsForMultiplicationAndDivision(combinedTerm, denominatorsWithPositiveAssociation);
    }
    return combinedTerm;
}

void TermsOverTerms::retrievePolynomialAndNonPolynomialNumerators(
        Polynomial & polynomialNumerator,
        Terms & nonPolynomialNumerators) const
{
    retrievePolynomialAndNonPolynomialsTerms(m_numerators, polynomialNumerator, nonPolynomialNumerators);
}

void TermsOverTerms::retrievePolynomialAndNonPolynomialsDenominators(
        Polynomial & polynomialDenominator,
        Terms & nonPolynomialDenominators) const
{
    retrievePolynomialAndNonPolynomialsTerms(m_denominators, polynomialDenominator, nonPolynomialDenominators);
}

TermsRaiseToNumbers TermsOverTerms::getTermsRaiseToNumbers() const
{
    TermsRaiseToNumbers result;
    Terms factorizedNumerators(factorizeTermsAsNeeded(m_numerators));
    Terms factorizedDenominators(factorizeTermsAsNeeded(m_denominators));

    result.putTerms(factorizedNumerators, TermAssociationType::Positive);
    result.putTerms(factorizedDenominators, TermAssociationType::Negative);
    return result;
}

void TermsOverTerms::flip()
{
    swap(m_numerators, m_denominators);
}

string TermsOverTerms::getDisplayableString() const
{
    stringstream result;
    result << "Numerators:" << endl;
    for(Term const& numerator : m_numerators)
    {
        result << "[" << numerator.getDisplayableString() << "]" << endl;
    }
    result << "Denominators:" << endl;
    for(Term const& denominator : m_denominators)
    {
        result << "[" << denominator.getDisplayableString() << "]" << endl;
    }
    return result.str();
}

void TermsOverTerms::setAsShouldSimplifyToFactors(
        bool const shouldSimplifyToFactors)
{
    m_shouldSimplifyToFactors = shouldSimplifyToFactors;
}

void TermsOverTerms::setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(
        bool const shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue)
{
    m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
}

void TermsOverTerms::simplify()
{
    putTermsOnNumeratorAndDenominatorCorrectly(m_numerators, m_denominators);
    Terms newNumerators = factorizeTermsAsNeeded(m_numerators);
    Terms newDenominators = factorizeTermsAsNeeded(m_denominators);
    if(m_shouldSimplifyToFactors)
    {
        continueToSimplifyToFactors(newNumerators, newDenominators);
    }
    else
    {
        continueToSimplifyAndCombineFactors(newNumerators, newDenominators);
    }
}

Terms TermsOverTerms::factorizeTermsAsNeeded(Terms const& terms) const
{
    ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = m_shouldSimplifyToFactors;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue
            = m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    return factorizeTerms(terms);
}

void TermsOverTerms::continueToSimplifyToFactors(
        Terms & factorizedNumerators,
        Terms & factorizedDenominators)
{
    removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(factorizedNumerators, factorizedDenominators);
    m_numerators = factorizedNumerators;
    m_denominators = factorizedDenominators;
    simplifyMonomialsToPolynomialOverPolynomial();
}

void TermsOverTerms::continueToSimplifyAndCombineFactors(
        Terms & factorizedNumerators,
        Terms & factorizedDenominators)
{
    bool areSomeFactorsRemoved(removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(factorizedNumerators, factorizedDenominators));
    if(areSomeFactorsRemoved)
    {
        m_numerators = factorizedNumerators;
        m_denominators = factorizedDenominators;
    }
    simplifyPolynomialsToPolynomialOverPolynomial();
}

Polynomial TermsOverTerms::multiplyPolynomialTerms(Terms const& polynomialTerms) const
{
    Polynomial polynomialResult(createPolynomialFromConstant(1));
    for(Term const& polynomialTerm : polynomialTerms)
    {
        if(canBeConvertedToPolynomial(polynomialTerm))
        {
            polynomialResult.multiplyPolynomial(createPolynomialIfPossible(polynomialTerm));
        }
    }
    return polynomialResult;
}

bool TermsOverTerms::removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(
        Terms & numerators,
        Terms & denominators)
{
    unsigned int previousNumberOfNumerators = numerators.size();
    unsigned int previousNumberOfDenominators = denominators.size();

    handleZerosInNumeratorOrDenominator(denominators, numerators);
    removeTermsThatHaveNoEffect(numerators);
    removeTermsThatHaveNoEffect(denominators);
    calculateBasesAndExponentsAndPutThatToNumeratorsAndDenominators(numerators, denominators);

    return previousNumberOfNumerators != numerators.size()
            || previousNumberOfDenominators != denominators.size();
}

void TermsOverTerms::handleZerosInNumeratorOrDenominator(
        Terms& denominators, Terms& numerators)
{
    bool hasZeroOnNumerators(hasZero(numerators));
    bool hasZeroOnDenominators(hasZero(denominators));
    if(hasZeroOnNumerators && hasZeroOnDenominators)
    {
        numerators.clear();
        denominators.clear();
        numerators.emplace_back(Term(AlbaNumber(AlbaNumber::Value::NotANumber)));
    }
    else if(hasZeroOnNumerators)
    {
        numerators.clear();
        denominators.clear();
        numerators.emplace_back(Term(Constant(0)));
    }
    else if(hasZeroOnDenominators)
    {
        denominators.clear();
        denominators.emplace_back(Term(Constant(0)));
    }
}

void TermsOverTerms::clearTermsThenEmplacePolynomialAndRemainingTerms(
        Polynomial const& polynomialNumerator,
        Terms const& remainingNumerators,
        Terms & termsToUpdate) const
{
    termsToUpdate.clear();
    emplacePolynomialIfNeeded(termsToUpdate, polynomialNumerator);
    termsToUpdate.reserve(remainingNumerators.size());
    copy(remainingNumerators.cbegin(), remainingNumerators.cend(), back_inserter(termsToUpdate));
}

void TermsOverTerms::emplacePolynomialIfNeeded(Terms & termsResult, Polynomial const& polynomial) const
{
    if(isTheValue(polynomial, 0))
    {
        termsResult.emplace_back(Term(Constant(0)));
    }
    else if(!isTheValue(polynomial, 1))
    {
        termsResult.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomial));
    }
}

void TermsOverTerms::retrievePolynomialAndNonPolynomialsTerms(
        Terms const& termsToCheck,
        Polynomial & polynomial,
        Terms & nonPolynomialTerms) const
{
    polynomial = (createPolynomialFromConstant(1));
    for(Term const& termToCheck : termsToCheck)
    {
        if(canBeConvertedToPolynomial(termToCheck))
        {
            polynomial.multiplyPolynomial(createPolynomialIfPossible(termToCheck));
        }
        else
        {
            nonPolynomialTerms.emplace_back(termToCheck);
        }
    }
}

void TermsOverTerms::calculateBasesAndExponentsAndPutThatToNumeratorsAndDenominators(
        Terms & numeratorTerms,
        Terms & denominatorTerms)
{
    TermsRaiseToNumbers basesAndExponents;
    basesAndExponents.putTerms(numeratorTerms, TermAssociationType::Positive);
    basesAndExponents.putTerms(denominatorTerms, TermAssociationType::Negative);

    numeratorTerms.clear();
    denominatorTerms.clear();

    putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToNumbers(numeratorTerms, denominatorTerms, basesAndExponents);
}

void TermsOverTerms::putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToNumbers(
        Terms & numeratorTerms,
        Terms & denominatorTerms,
        TermsRaiseToNumbers const& termsRaiseToNumbers)
{
    for(auto const& baseExponentPair : termsRaiseToNumbers.getBaseToExponentMap())
    {
        Term const& base(baseExponentPair.first);
        AlbaNumber const& exponent(baseExponentPair.second);
        if(!exponent.isIntegerType() || m_shouldSimplifyToFactors)
        {
            if(exponent > 0)
            {
                TermRaiseToANumber termRaiseToANumber(base, exponent);
                numeratorTerms.emplace_back(termRaiseToANumber.getCombinedTerm());
            }
            else if(exponent < 0)
            {
                TermRaiseToANumber termRaiseToANumber(base, exponent*-1);
                denominatorTerms.emplace_back(termRaiseToANumber.getCombinedTerm());
            }
        }
        else
        {
            if(exponent > 0)
            {
                populateTermsWithBase(numeratorTerms, base, exponent);
            }
            else if(exponent < 0)
            {
                populateTermsWithBase(denominatorTerms, base, exponent);
            }
        }
    }
}

void TermsOverTerms::populateTermsWithBase(
        Terms & termsToUpdate,
        Term const& base,
        AlbaNumber const& exponent)
{
    unsigned int exponentCount = static_cast<unsigned int>(getAbsoluteValueForAlbaNumber(exponent).getInteger());
    for(unsigned int i=0; i<exponentCount; i++)
    {
        termsToUpdate.emplace_back(base);
    }
}

void TermsOverTerms::removeTermsThatHaveNoEffect(Terms & terms) const
{
    terms.erase(remove_if(terms.begin(), terms.end(), [](Term const& term){
                    return willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term);
                }), terms.end());
}

void TermsOverTerms::putTermsOnNumeratorAndDenominatorCorrectly(
        Terms & numerators,
        Terms & denominators)
{
    Terms retainedNumerators, retainedDenominators, termsToPutInNumerators, termsToPutInDenominators;
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
        Terms const& termsToCheck,
        Terms & termsToRetain,
        Terms & termsToPutOnTheOtherSide) const
{
    for(Term const& termToCheck : termsToCheck)
    {
        bool isNeededToPutOnTheOtherSide(false);
        Term transformedTermOnTheOtherSide(termToCheck);
        if(termToCheck.isExpression())
        {
            Expression const& expression(termToCheck.getExpressionConstReference());
            TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
            if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel()
                    && termsWithDetails.size() == 2)
            {
                Term const& base(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
                Term const& exponent(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
                isNeededToPutOnTheOtherSide = isANegativeTerm(exponent);
                transformedTermOnTheOtherSide = Term(createExpressionIfPossible({base, Term("^"), negateTerm(exponent)}));
            }
        }
        if(isNeededToPutOnTheOtherSide)
        {
            transformedTermOnTheOtherSide.simplify();
            termsToPutOnTheOtherSide.emplace_back(transformedTermOnTheOtherSide);
        }
        else
        {
            termsToRetain.emplace_back(termToCheck);
        }
    }
}

void TermsOverTerms::simplifyPolynomialNumeratorAndPolynomialDenominator(
        Polynomial & polynomialNumerator,
        Polynomial & polynomialDenominator) const
{
    PolynomialOverPolynomial numeratorAndDenominator(polynomialNumerator, polynomialDenominator);
    numeratorAndDenominator.simplify();
    polynomialNumerator = numeratorAndDenominator.getNumerator();
    polynomialDenominator = numeratorAndDenominator.getDenominator();
}


void TermsOverTerms::simplifyMonomialsToPolynomialOverPolynomial()
{
    Terms monomialsNumerators, nonMonomialNumerators, monomialDenominators, nonMonomialDenominators;
    segregateMonomialsAndNonMonomials(m_numerators, monomialsNumerators, nonMonomialNumerators);
    segregateMonomialsAndNonMonomials(m_denominators, monomialDenominators, nonMonomialDenominators);
    Polynomial polynomialNumerator(multiplyPolynomialTerms(monomialsNumerators));
    Polynomial polynomialDenominator(multiplyPolynomialTerms(monomialDenominators));
    simplifyPolynomialNumeratorAndPolynomialDenominator(polynomialNumerator, polynomialDenominator);
    clearTermsThenEmplacePolynomialAndRemainingTerms(polynomialNumerator, nonMonomialNumerators, m_numerators);
    clearTermsThenEmplacePolynomialAndRemainingTerms(polynomialDenominator, nonMonomialDenominators, m_denominators);
}

void TermsOverTerms::simplifyPolynomialsToPolynomialOverPolynomial()
{
    Terms polynomialNumerators, nonPolynomialNumerators, polynomialDenominators, nonPolynomialDenominators;
    segregatePolynomialAndNonPolynomials(m_numerators, polynomialNumerators, nonPolynomialNumerators);
    segregatePolynomialAndNonPolynomials(m_denominators, polynomialDenominators, nonPolynomialDenominators);
    Polynomial polynomialNumerator(multiplyPolynomialTerms(polynomialNumerators));
    Polynomial polynomialDenominator(multiplyPolynomialTerms(polynomialDenominators));
    simplifyPolynomialNumeratorAndPolynomialDenominator(polynomialNumerator, polynomialDenominator);
    clearTermsThenEmplacePolynomialAndRemainingTerms(polynomialNumerator, nonPolynomialNumerators, m_numerators);
    clearTermsThenEmplacePolynomialAndRemainingTerms(polynomialDenominator, nonPolynomialDenominators, m_denominators);
}

}

}
