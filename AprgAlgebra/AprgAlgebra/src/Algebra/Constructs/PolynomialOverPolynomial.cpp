#include "PolynomialOverPolynomial.hpp"

#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMultiplesHelpers.hpp>

#include <iterator>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

PolynomialOverPolynomial::PolynomialOverPolynomial(Polynomial const& numerator, Polynomial const& denominator)
    : m_numerator(numerator), m_denominator(denominator) {}

PolynomialOverPolynomial::PolynomialOverPolynomial(Polynomial&& numerator, Polynomial&& denominator)
    : m_numerator(numerator), m_denominator(denominator) {}

Polynomial const& PolynomialOverPolynomial::getNumerator() const { return m_numerator; }
Polynomial const& PolynomialOverPolynomial::getDenominator() const { return m_denominator; }

PolynomialOverPolynomial::QuotientAndRemainder PolynomialOverPolynomial::divide() const {
    Polynomial currentQuotient;
    Polynomial currentRemainder(m_numerator);
    while (!isTheValue(currentRemainder, 0) && !isNan(currentRemainder)) {
        Monomial const& dividendMonomial(getFirstMonomial(currentRemainder));
        Monomial const& divisorMonomial(getFirstMonomial(m_denominator));
        Monomial currentQuotientMonomial(dividendMonomial);
        currentQuotientMonomial.divideMonomial(divisorMonomial);
        if (!hasNegativeExponents(currentQuotientMonomial)) {
            currentQuotient.addMonomial(currentQuotientMonomial);
            Polynomial polynomialToSubtract(m_denominator);
            polynomialToSubtract.multiplyMonomial(currentQuotientMonomial);
            polynomialToSubtract.multiplyNumber(-1);
            currentRemainder.addPolynomial(polynomialToSubtract);
            currentQuotient.simplify();
            currentRemainder.simplify();
        } else {
            break;
        }
    }
    return QuotientAndRemainder{currentQuotient, currentRemainder};
}

bool PolynomialOverPolynomial::isEmpty() const { return m_numerator.isEmpty() && m_denominator.isEmpty(); }

void PolynomialOverPolynomial::setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(
    bool const shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue) {
    m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue =
        shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
}

void PolynomialOverPolynomial::simplify() {
    convertFractionCoefficientsToInteger();
    convertNegativeExponentsToPositive();
    removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator();
    m_numerator.simplify();
    m_denominator.simplify();
    factorizeRemoveCommonFactorsInNumeratorAndDenominatorAndCombineRemainingFactors();
}

void PolynomialOverPolynomial::simplifyWithoutFactorization() {
    convertFractionCoefficientsToInteger();
    convertNegativeExponentsToPositive();
    removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator();
    m_numerator.simplify();
    m_denominator.simplify();
}

PolynomialOverPolynomial::QuotientAndRemainder PolynomialOverPolynomial::simplifyAndDivide() {
    simplify();
    return divide();
}

bool PolynomialOverPolynomial::shouldPerformFactorization() const {
    return !canBeConvertedToConstant(m_numerator) && !canBeConvertedToConstant(m_denominator);
}

void PolynomialOverPolynomial::convertFractionCoefficientsToInteger() {
    int const numeratorMultiplier(getLcmForDenominatorCoefficients(m_numerator));
    m_numerator.multiplyNumber(numeratorMultiplier);
    m_denominator.multiplyNumber(numeratorMultiplier);
    int const denominatorMultiplier(getLcmForDenominatorCoefficients(m_denominator));
    m_numerator.multiplyNumber(denominatorMultiplier);
    m_denominator.multiplyNumber(denominatorMultiplier);
}

void PolynomialOverPolynomial::convertNegativeExponentsToPositive() {
    Monomial const monomialExponentNumerator(getMonomialWithMaxNegativeExponentsAndConvertItToPositive(m_numerator));
    Monomial const monomialExponentDenominator(
        getMonomialWithMaxNegativeExponentsAndConvertItToPositive(m_denominator));
    m_numerator.multiplyMonomial(monomialExponentNumerator);
    m_numerator.multiplyMonomial(monomialExponentDenominator);
    m_denominator.multiplyMonomial(monomialExponentNumerator);
    m_denominator.multiplyMonomial(monomialExponentDenominator);
}

void PolynomialOverPolynomial::removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator() {
    Monomials numeratorAndDenominatorMonomials;
    Monomials const& numeratorMonomials(m_numerator.getMonomials());
    Monomials const& denominatorMonomials(m_denominator.getMonomials());
    numeratorAndDenominatorMonomials.reserve(numeratorMonomials.size() + denominatorMonomials.size());
    copy(numeratorMonomials.cbegin(), numeratorMonomials.cend(), back_inserter(numeratorAndDenominatorMonomials));
    copy(denominatorMonomials.cbegin(), denominatorMonomials.cend(), back_inserter(numeratorAndDenominatorMonomials));
    Monomial const gcfMonomial(getGcfMonomialInMonomials(numeratorAndDenominatorMonomials));
    if (!isTheValue(gcfMonomial, 0)) {
        m_numerator.divideMonomial(gcfMonomial);
        m_denominator.divideMonomial(gcfMonomial);
        bool const isDenominatorHasNegativeSign = getCommonSignInMonomials(m_denominator.getMonomials()) == -1;
        if (isDenominatorHasNegativeSign) {
            m_numerator.divideMonomial(createMonomialFromNumber(-1));
            m_denominator.divideMonomial(createMonomialFromNumber(-1));
        }
    }
}

void PolynomialOverPolynomial::factorizeRemoveCommonFactorsInNumeratorAndDenominatorAndCombineRemainingFactors() {
    ConfigurationDetails configurationDetails(Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue =
        m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
    ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    if (shouldPerformFactorization()) {
        Polynomials numeratorFactors(factorizeAPolynomial(m_numerator));
        Polynomials denominatorFactors(factorizeAPolynomial(m_denominator));
        bool const areSomeFactorsRemoved(
            removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(numeratorFactors, denominatorFactors));
        if (areSomeFactorsRemoved) {
            m_numerator = multiplyAndSimplifyFactors(numeratorFactors);
            m_denominator = multiplyAndSimplifyFactors(denominatorFactors);
        }
    }
}

Monomial PolynomialOverPolynomial::getMonomialWithMaxNegativeExponentsAndConvertItToPositive(
    Polynomial const& polynomial) {
    Monomial resultMonomial(1, {});
    Monomial::VariablesToExponentsMap const& resultVariableMap(resultMonomial.getVariablesToExponentsMap());
    for (Monomial const& monomial : polynomial.getMonomials()) {
        for (auto const& [variable, exponent] : monomial.getVariablesToExponentsMap()) {
            if (exponent < 0) {
                AlbaNumber existingExponent;
                if (resultVariableMap.find(variable) != resultVariableMap.end()) {
                    existingExponent = resultVariableMap.at(variable);
                }
                AlbaNumber const newPositiveExponent(exponent * -1);
                if (newPositiveExponent > existingExponent) {
                    resultMonomial.putVariableWithExponent(variable, newPositiveExponent);
                }
            }
        }
    }
    return resultMonomial;
}

Polynomial PolynomialOverPolynomial::multiplyAndSimplifyFactors(Polynomials const& factors) {
    Polynomial product{Monomial(1, {})};
    for (Polynomial const& factor : factors) {
        product.multiplyPolynomial(factor);
    }
    product.simplify();
    return product;
}

int PolynomialOverPolynomial::getLcmForDenominatorCoefficients(Polynomial const& polynomial) {
    int lcm(1);
    for (Monomial const& monomial : polynomial.getMonomials()) {
        AlbaNumber const& coefficient(monomial.getCoefficient());
        if (coefficient.isFractionType()) {
            AlbaNumber::FractionData const fractionData(coefficient.getFractionData());
            lcm = getLeastCommonMultiple(lcm, static_cast<int>(fractionData.denominator));
        }
    }
    return lcm;
}

bool PolynomialOverPolynomial::removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(
    Polynomials& numeratorFactors, Polynomials& denominatorFactors) {
    bool areSomeFactorsRemoved(false);
    for (auto numeratorIterator = numeratorFactors.begin(); numeratorIterator != numeratorFactors.end();
         ++numeratorIterator) {
        for (auto denominatorIterator = denominatorFactors.begin(); denominatorIterator != denominatorFactors.end();
             ++denominatorIterator) {
            Polynomial const& numerator(*numeratorIterator);
            Polynomial const& denominator(*denominatorIterator);
            if (!(isOneMonomial(numerator) && isOneMonomial(denominator))) {
                if (numerator == denominator) {
                    auto nextOffsetInNumerator = distance(numeratorFactors.begin(), numeratorIterator);
                    auto nextOffsetInDenominator = distance(denominatorFactors.begin(), denominatorIterator);
                    nextOffsetInNumerator -= nextOffsetInNumerator > 0 ? 1 : 0;
                    nextOffsetInDenominator -= nextOffsetInDenominator > 0 ? 1 : 0;
                    numeratorFactors.erase(numeratorIterator);
                    denominatorFactors.erase(denominatorIterator);
                    numeratorIterator = next(numeratorFactors.begin(), nextOffsetInNumerator);
                    denominatorIterator = next(denominatorFactors.begin(), nextOffsetInDenominator);
                    areSomeFactorsRemoved = true;
                    if (numeratorFactors.empty() || denominatorFactors.empty()) {
                        return areSomeFactorsRemoved;
                    }
                }
            }
        }
    }
    return areSomeFactorsRemoved;
}

}  // namespace alba::algebra
