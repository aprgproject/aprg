#include "FactorizationOfIncreasingAndDecreasingExponentForm.hpp"

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Factorization/BrentMethod.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMultiplesHelpers.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra::Factorization {

namespace {
constexpr int NUMBER_OF_ITERATIONS_IN_BRENT_METHOD = 1000;
}  // namespace

void factorizeIncreasingAndDecreasingExponentsFormIfPossible(Polynomials& result, Polynomial const& polynomial) {
    Monomials monomials(polynomial.getMonomials());
    if (monomials.size() > 1) {
        Monomial const firstMonomial(monomials.front());
        Monomial const lastMonomial(monomials.back());
        int const maxExponentDivisor(calculateMaxExponentDivisor(firstMonomial, lastMonomial));
        for (int exponentDivisor = 2; exponentDivisor <= maxExponentDivisor; ++exponentDivisor) {
            if (areExponentsDivisible(firstMonomial, exponentDivisor) &&
                areExponentsDivisible(lastMonomial, exponentDivisor)) {
                Monomial unitFirstMonomial(1, firstMonomial.getVariablesToExponentsMap());
                Monomial unitSecondMonomial(1, lastMonomial.getVariablesToExponentsMap());
                unitFirstMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, exponentDivisor));
                unitSecondMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, exponentDivisor));
                Monomials const monomialsWithExponentsInOrder(
                    getMonomialsWithExponentsInOrder(exponentDivisor, unitFirstMonomial, unitSecondMonomial));
                if (areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials, monomialsWithExponentsInOrder)) {
                    AlbaNumbers const coefficients(
                        getCoefficientsInMonomialsWithExponentsInOrder(polynomial, monomialsWithExponentsInOrder));
                    factorizePolynomialForm(
                        result, polynomial, coefficients, unitFirstMonomial.getVariablesToExponentsMap(),
                        unitSecondMonomial.getVariablesToExponentsMap());
                }
                if (!result.empty()) {
                    break;
                }
            }
        }
    }
}

void factorizePolynomialForm(
    Polynomials& result, Polynomial const& polynomial, AlbaNumbers const& coefficients,
    Monomial::VariablesToExponentsMap const& firstVariableExponent,
    Monomial::VariablesToExponentsMap const& secondVariableExponent) {
    AlbaNumbers const rootValues(calculatePolynomialRoots(coefficients));
    if (areRootsAcceptable(rootValues)) {
        Polynomial remainingPolynomial(polynomial);
        for (AlbaNumber const& rootValue : rootValues) {
            AlbaNumber rootFirstCoefficient(1);
            AlbaNumber rootSecondCoefficient(rootValue * -1);
            AlbaNumber aCoefficient(getFirstMonomial(remainingPolynomial).getCoefficient());
            if (aCoefficient.isIntegerOrFractionType() && rootSecondCoefficient.isIntegerOrFractionType()) {
                fixCoefficientsOfFactors(aCoefficient, rootFirstCoefficient, rootSecondCoefficient);
            }
            Monomial const rootFirstMonomial(rootFirstCoefficient, firstVariableExponent);
            Monomial const rootSecondMonomial(rootSecondCoefficient, secondVariableExponent);
            Polynomial const rootPolynomial{rootFirstMonomial, rootSecondMonomial};
            PolynomialOverPolynomial const divideProcess(remainingPolynomial, rootPolynomial);
            PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(divideProcess.divide());
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, rootPolynomial);
            remainingPolynomial = quotientAndRemainder.quotient;
        }
        if (!rootValues.empty() && !isTheValue(remainingPolynomial, 1)) {
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, remainingPolynomial);
        }
    }
}

void fixCoefficientsOfFactors(
    AlbaNumber& aCoefficient, AlbaNumber& rootFirstCoefficient, AlbaNumber& rootSecondCoefficient) {
    AlbaNumber::FractionData const aCoefficientFractionData(aCoefficient.getFractionData());
    AlbaNumber::FractionData const secondFractionData(rootSecondCoefficient.getFractionData());
    int const multiplier = getGreatestCommonFactor<int>(
        getAbsoluteValue(static_cast<int>(aCoefficientFractionData.numerator)),
        static_cast<int>(secondFractionData.denominator));
    rootFirstCoefficient = rootFirstCoefficient * multiplier;
    rootSecondCoefficient = rootSecondCoefficient * multiplier;
    aCoefficient = aCoefficient / multiplier;
}

AlbaNumber getMaxAbsoluteValueForRootFinding(AlbaNumbers const& coefficients) {
    AlbaNumber result(0);
    if (!coefficients.empty()) {
        result = max(getAbsoluteValue(coefficients.front()), getAbsoluteValue(coefficients.back()));
    }
    return result;
}

AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(
    Polynomial const& polynomial, Monomials const& monomialsWithExponentsInOrder) {
    AlbaNumbers coefficients;
    coefficients.reserve(monomialsWithExponentsInOrder.size());
    transform(
        monomialsWithExponentsInOrder.cbegin(), monomialsWithExponentsInOrder.cend(), back_inserter(coefficients),
        [&](Monomial const& monomialWithExponentInOrder) {
            return getCoefficientOfVariableExponent(polynomial, monomialWithExponentInOrder);
        });
    return coefficients;
}

AlbaNumbers calculatePolynomialRoots(AlbaNumbers const& coefficients) {
    AlbaNumbers result;
    if (coefficients.size() == 3) {
        result =
            getQuadraticRoots(mathHelper::RootType::RealRootsOnly, coefficients[0], coefficients[1], coefficients[2]);
    } else {
        AlbaNumbers const derivativeRoots(calculatePolynomialRoots(getDerivativeCoefficients(coefficients)));
        result = calculatePolynomialRootsUsingBrentMethod(derivativeRoots, coefficients);
    }
    return result;
}

AlbaNumbers calculatePolynomialRootsUsingBrentMethod(
    AlbaNumbers const& previousDerivativeRoots, AlbaNumbers const& coefficients) {
    AlbaNumbers result;
    AlbaNumbers valuesForRootFinding(previousDerivativeRoots);
    AlbaNumber const maxAbsoluteValue(getMaxAbsoluteValueForRootFinding(coefficients));
    valuesForRootFinding.emplace_back(maxAbsoluteValue * -1);
    valuesForRootFinding.emplace_back(maxAbsoluteValue);
    sort(valuesForRootFinding.begin(), valuesForRootFinding.end());
    BrentMethod brentMethod(coefficients);
    int const size = static_cast<int>(valuesForRootFinding.size());
    for (int i = 0; i < size - 1; ++i) {
        int const j = i + 1;
        brentMethod.resetCalculation(valuesForRootFinding[i], valuesForRootFinding[j]);
        brentMethod.runMaxNumberOfIterationsOrUntilFinished(NUMBER_OF_ITERATIONS_IN_BRENT_METHOD);
        AlbaNumberOptional rootOptional(brentMethod.getSolution());
        if (rootOptional) {
            AlbaNumber const& root(rootOptional.value());
            result.emplace_back(root);
        }
    }
    return result;
}

AlbaNumbers getDerivativeCoefficients(AlbaNumbers const& coefficients) {
    AlbaNumbers derivativeCoefficients(coefficients);
    if (!derivativeCoefficients.empty()) {
        derivativeCoefficients.pop_back();
        AlbaNumber derivativeMultiplier(static_cast<int64_t>(derivativeCoefficients.size()));
        for (AlbaNumber& derivativeCoefficient : derivativeCoefficients) {
            derivativeCoefficient = derivativeCoefficient * derivativeMultiplier;
            derivativeMultiplier = derivativeMultiplier - 1;
        }
    }
    return derivativeCoefficients;
}

Monomials getMonomialsWithExponentsInOrder(
    int const exponentDivisor, Monomial const& firstInPolynomial, Monomial const& lastInPolynomial) {
    Monomials monomialsWithExponentsInOrder;
    for (int i = 0; i <= exponentDivisor; ++i) {
        Monomial firstPart(firstInPolynomial);
        firstPart.raiseToPowerNumber(exponentDivisor - i);
        Monomial secondPart(lastInPolynomial);
        secondPart.raiseToPowerNumber(i);
        Monomial product(firstPart);
        product.multiplyMonomial(secondPart);
        product.simplify();
        monomialsWithExponentsInOrder.emplace_back(product);
    }
    return monomialsWithExponentsInOrder;
}

Polynomials factorizeIncreasingAndDecreasingExponentsForm(Polynomial const& polynomial) {
    Polynomials result;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(result, polynomial);
    simplifyAndEmplaceBackPolynomialIfListIsEmpty(result, polynomial);
    return result;
}

int calculateMaxExponentDivisor(Monomial const& firstMonomial, Monomial const& lastMonomial) {
    AlbaNumber const maxExponent = max(getMaxExponent(firstMonomial), getMaxExponent(lastMonomial));
    int const maxExponentDivisor = getAbsoluteValue(static_cast<int>(maxExponent.getInteger()));
    return maxExponentDivisor;
}

bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
    Monomials const& monomialsToCheck, Monomials const& monomialsWithExponentsInOrder) {
    Polynomial const polynomialWithExponentsInOrder(monomialsWithExponentsInOrder);
    return !any_of(monomialsToCheck.cbegin(), monomialsToCheck.cend(), [&](Monomial const& monomialToCheck) {
        return !isVariableExponentInMonomialFound(polynomialWithExponentsInOrder, monomialToCheck);
    });
}

bool areRootsAcceptable(AlbaNumbers const& rootValues) {
    bool const doAnyRootsHaveDoubleValues =
        any_of(rootValues.cbegin(), rootValues.cend(), [](AlbaNumber const& root) { return root.isDoubleType(); });
    return !(shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue() && doAnyRootsHaveDoubleValues);
}

}  // namespace alba::algebra::Factorization
