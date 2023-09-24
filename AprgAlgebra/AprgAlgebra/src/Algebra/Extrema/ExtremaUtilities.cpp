#include "ExtremaUtilities.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Solution/Solver/SolverUsingSubstitution/SolverUsingSubstitution.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Number/Interval/AlbaNumberInterval.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace alba::algebra::DomainAndRange;
using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

// functions for this file only
namespace {

void putArbitiaryValuesFromInterval(AlbaNumbers& arbitiaryValues, AlbaNumberInterval const& interval);
void putArbitiaryValuesBasedFromDomainOfTerm(AlbaNumbers& arbitiaryValues, Term const& term);
void retrieveSecondDerivatives(Terms& secondDerivatives, Term const& term, strings const& variableNames);

void retrieveSubstitutionsFromCriticalNumbers(
    SubstitutionsOfVariablesToValues& substitutions,
    VariableNameToCriticalNumbersMap const& variableNameToCriticalNumbersMap);

void determineExtrema(
    ExtremaWithMultipleVariables& extrema, Terms const& secondDerivatives,
    SubstitutionsOfVariablesToValues const& substitutions);

}  // namespace

AlbaNumbers getInputValuesInIntervalWithSameAsMeanOfInterval(
    Term const& term, string const& variableName, AlbaNumber const& a, AlbaNumber const& b) {
    // Mean-Value theorem:
    // Let f be a function such that:
    // (i) it is continuous on the closed interval [a, b]
    // (ii) it is differentiable on the open interval (a, b)
    // (iii) f(a) = 0 and f(b) = 0
    // Then there is a number c in the open interval (a, b) such that f'(c) = (f(b)-f(a))/(b-a)
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, a);
    Term const fa(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, b);
    Term const fb(substitution.performSubstitutionTo(term));
    AlbaNumbers result;
    if (fa.isConstant() && fb.isConstant()) {
        AlbaNumber const mean = (fb.getAsNumber() - fa.getAsNumber()) / (b - a);
        Differentiation const differentiation(variableName);
        Term const fPrime(differentiation.differentiate(term));
        Equation const derivativeEqualsMeanEquation(fPrime, "=", mean);
        OneEquationOneVariableEqualitySolver solver;
        SolutionSet const solutionSet(solver.calculateSolutionAndReturnSolutionSet(derivativeEqualsMeanEquation));
        AlbaNumberInterval const abOpenInterval(createOpenEndpoint(a), createOpenEndpoint(b));
        result = getNumbersInsideTheInterval(solutionSet.getAcceptedValues(), abOpenInterval);
    }
    return result;
}

AlbaNumbers getInputValuesForCauchyMeanValueTheorem(
    Term const& term, string const& variableName, AlbaNumber const& a, AlbaNumber const& b) {
    // Cauchy Mean-Value Theorem
    TermsOverTerms const termsOverTerms(createTermsOverTermsFromTerm(term));
    Term const numerator(termsOverTerms.getCombinedNumerator());
    Term const denominator(termsOverTerms.getCombinedDenominator());
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, a);
    Term const fa(substitution.performSubstitutionTo(numerator));
    Term const ga(substitution.performSubstitutionTo(denominator));
    substitution.putVariableWithValue(variableName, b);
    Term const fb(substitution.performSubstitutionTo(numerator));
    Term const gb(substitution.performSubstitutionTo(denominator));
    AlbaNumbers result;
    if (fa.isConstant() && fb.isConstant()) {
        AlbaNumber const cauchyValue = (fb.getAsNumber() - fa.getAsNumber()) / (gb.getAsNumber() - ga.getAsNumber());
        Differentiation const differentiation(variableName);
        Term const fPrime(differentiation.differentiate(numerator));
        Term const gPrime(differentiation.differentiate(denominator));
        Term const cauchyExpression(fPrime / gPrime);
        Equation const cauchyEquation(cauchyExpression, "=", cauchyValue);
        OneEquationOneVariableEqualitySolver solver;
        SolutionSet const solutionSet(solver.calculateSolutionAndReturnSolutionSet(cauchyEquation));
        AlbaNumberInterval const abOpenInterval(createOpenEndpoint(a), createOpenEndpoint(b));
        result = getNumbersInsideTheInterval(solutionSet.getAcceptedValues(), abOpenInterval);
    }
    return result;
}

AlbaNumbers getCriticalNumbers(Term const& term, string const& variableName) {
    // If c is a number in the domain of the function f, and if either f'(c) = 0 of f'(c) does not exist,
    // then c is called a critical number of f.
    Differentiation const differentiation(variableName);
    Term const firstDerivative(differentiation.differentiate(term));
    Equation const derivativeEqualsZeroEquation(firstDerivative, "=", 0);
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet const solutionSet(solver.calculateSolutionAndReturnSolutionSet(derivativeEqualsZeroEquation));
    AlbaNumbers result;
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    AlbaNumbers const& rejectedValues(solutionSet.getRejectedValues());
    result.reserve(acceptedValues.size() + rejectedValues.size());
    copy(acceptedValues.cbegin(), acceptedValues.cend(), back_inserter(result));
    copy(rejectedValues.cbegin(), rejectedValues.cend(), back_inserter(result));
    return result;
}

AlbaNumbers getInputValuesAtPointsOfInflection(Term const& term, string const& variableName) {
    Differentiation const differentiation(variableName);
    Term const secondDerivative(differentiation.differentiateMultipleTimes(term, 2));
    AlbaNumbers result;
    if (!secondDerivative.isConstant()) {
        Equation const derivativeEqualsZeroEquation(secondDerivative, "=", 0);
        OneEquationOneVariableEqualitySolver solver;
        SolutionSet const solutionSet(solver.calculateSolutionAndReturnSolutionSet(derivativeEqualsZeroEquation));
        AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
        AlbaNumbers const& rejectedValues(solutionSet.getRejectedValues());
        result.reserve(acceptedValues.size() + rejectedValues.size());
        copy(acceptedValues.cbegin(), acceptedValues.cend(), back_inserter(result));
        copy(rejectedValues.cbegin(), rejectedValues.cend(), back_inserter(result));
    }
    return result;
}

Extrema getRelativeExtrema(Term const& term, string const& variableName) {
    // Let c be a critical number of a function f at which f'(c) = 0, and let f exist for all values of x in some open
    // interval containing c.
    // If f''(c) exists and :
    // (i) if f''(c) < 0, then f has a relative maximum value at c.
    // (ii) if f''(c) > 0, then f has a relative minimum value at c.
    Differentiation const differentiation(variableName);
    Term const firstDerivative(differentiation.differentiate(term));
    Term const secondDerivative(differentiation.differentiateMultipleTimes(term, 2));
    Equation const firstDerivativeEqualsZeroEquation(firstDerivative, "=", 0);
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet const solutionSet(solver.calculateSolutionAndReturnSolutionSet(firstDerivativeEqualsZeroEquation));
    AlbaNumbers const& valuesWhenFirstDerivativeIsZero(solutionSet.getAcceptedValues());
    Extrema result;
    for (AlbaNumber const& valueWhenFirstDerivativeIsZero : valuesWhenFirstDerivativeIsZero) {
        SubstitutionOfVariablesToValues const substitution({{variableName, valueWhenFirstDerivativeIsZero}});
        Term const secondDerivativeTermAtCriticalValue(substitution.performSubstitutionTo(secondDerivative));
        Term const evaluatedTerm(substitution.performSubstitutionTo(term));
        if (secondDerivativeTermAtCriticalValue.isConstant() && evaluatedTerm.isConstant()) {
            AlbaNumber const secondDerivativeValueAtCriticalValue(secondDerivativeTermAtCriticalValue.getAsNumber());
            if (secondDerivativeValueAtCriticalValue.isAFiniteValue()) {
                if (secondDerivativeValueAtCriticalValue < 0) {
                    result.emplace_back(
                        Extremum{ExtremumType::Maximum, {valueWhenFirstDerivativeIsZero, evaluatedTerm.getAsNumber()}});
                } else if (secondDerivativeValueAtCriticalValue > 0) {
                    result.emplace_back(
                        Extremum{ExtremumType::Minimum, {valueWhenFirstDerivativeIsZero, evaluatedTerm.getAsNumber()}});
                }
            }
        }
    }
    return result;
}

ExtremaWithMultipleVariables getRelativeExtremaWithMultipleVariables(Term const& term, strings const& coordinateNames) {
    ExtremaWithMultipleVariables result;
    VariableNameToCriticalNumbersMap const variableNameToCriticalNumbersMap(
        getCriticalNumbersWithMultipleVariables(term, coordinateNames));
    Terms secondDerivatives;
    retrieveSecondDerivatives(secondDerivatives, term, coordinateNames);
    SubstitutionsOfVariablesToValues substitutions;
    retrieveSubstitutionsFromCriticalNumbers(substitutions, variableNameToCriticalNumbersMap);
    determineExtrema(result, secondDerivatives, substitutions);
    return result;
}

Extremum getAbsoluteExtremumBasedOnRelativeExtremaOnInterval(
    Extrema const& relativeExtrema, AlbaNumberInterval const& interval) {
    // Let the function f be continuous on the interval I containing the number c.
    // If f(c) is a relative extremum of f on I and c is the ONLY in I for which f has a relative extermum,
    // then f(c) is an absolute extremum of f on I. Furthermore,
    // (i) if f(c) is relative maximum value of f on I, then f(c) is an absolute maximum value of f on I.
    // (ii) if f(c) is relative minimum value of f on I, then f(c) is an absolute minimum value of f on I.
    int numberOfExtremaFoundInInterval(0);
    Extremum result;
    Extremum extremumInInterval;
    for (Extremum const& extremum : relativeExtrema) {
        auto const& [inputValue, outputValue] = extremum.inputOutputValues;
        if (interval.isValueInsideTheInterval(inputValue)) {
            extremumInInterval = extremum;
            ++numberOfExtremaFoundInInterval;
            if (numberOfExtremaFoundInInterval > 1) {
                break;
            }
        }
    }
    if (numberOfExtremaFoundInInterval == 1) {
        // if its the only extrema in interval then its absolute
        result = extremumInInterval;
    }
    return result;
}

MinimumAndMaximum getMinimumAndMaximumAtClosedInterval(
    Term const& term, string const& variableName, AlbaNumberInterval const& closedInterval) {
    // Extreme value theorem
    // If the function f is continuous on the closed interval [a, b],
    // then f has an absolute maximum value and an absolute minimum value on [a, b].
    // Procedure:
    // 1. Find the function values at the critical numbers on f on (a, b).
    // 2. Find the values of f(a) and f(b)
    // 3. The largest of the values from steps 1 and 2 is the absolute maximum value,
    // and the smallest of the values is the absolute minimum value.
    MinimumAndMaximum result;
    if (closedInterval.getLowerEndpoint().isClose() && closedInterval.getHigherEndpoint().isClose()) {
        AlbaNumbers valuesToCheck(getCriticalNumbers(term, variableName));
        valuesToCheck.emplace_back(closedInterval.getLowerEndpoint().getValue());
        valuesToCheck.emplace_back(closedInterval.getHigherEndpoint().getValue());
        SubstitutionOfVariablesToValues substitution;
        bool isFirst(true);
        for (AlbaNumber const& valueToCheck : valuesToCheck) {
            substitution.putVariableWithValue(variableName, valueToCheck);
            Term const evaluatedTerm(substitution.performSubstitutionTo(term));
            if (evaluatedTerm.isConstant()) {
                AlbaNumber const evaluatedValue(evaluatedTerm.getAsNumber());
                if (isFirst) {
                    result.minimumInputOutputValues.first = valueToCheck;
                    result.minimumInputOutputValues.second = evaluatedValue;
                    result.maximumInputOutputValues.first = valueToCheck;
                    result.maximumInputOutputValues.second = evaluatedValue;
                    isFirst = false;
                } else if (result.minimumInputOutputValues.second > evaluatedValue) {
                    result.minimumInputOutputValues.first = valueToCheck;
                    result.minimumInputOutputValues.second = evaluatedValue;
                } else if (result.maximumInputOutputValues.second < evaluatedValue) {
                    result.maximumInputOutputValues.first = valueToCheck;
                    result.maximumInputOutputValues.second = evaluatedValue;
                }
            }
        }
    }
    return result;
}

VariableNameToCriticalNumbersMap getCriticalNumbersWithMultipleVariables(
    Term const& term, strings const& coordinateNames) {
    VariableNameToCriticalNumbersMap result;
    Equations equationsWithPartialDerivatives;
    equationsWithPartialDerivatives.reserve(coordinateNames.size());
    transform(
        coordinateNames.cbegin(), coordinateNames.cend(), back_inserter(equationsWithPartialDerivatives),
        [&](string const& variableName) { return Equation(getPartialDerivative(term, variableName), "=", 0); });
    SolverUsingSubstitution solver;
    MultipleVariableSolutionSets const solutionSets(
        solver.calculateSolutionAndReturnSolutionSet(equationsWithPartialDerivatives));
    for (MultipleVariableSolutionSet const& solutionSet : solutionSets) {
        for (auto const& [variableName, solutionSetInMap] : solutionSet.getVariableNameToSolutionSetMap()) {
            AlbaNumbers& criticalNumbers(result[variableName]);
            AlbaNumbers const& acceptedValues(solutionSetInMap.getAcceptedValues());
            AlbaNumbers const& rejectedValues(solutionSetInMap.getRejectedValues());
            criticalNumbers.reserve(acceptedValues.size() + rejectedValues.size());
            copy(acceptedValues.cbegin(), acceptedValues.cend(), back_inserter(criticalNumbers));
            copy(rejectedValues.cbegin(), rejectedValues.cend(), back_inserter(criticalNumbers));
        }
    }
    return result;
}

bool willYieldToAbsoluteMinimumValue(
    Term const& term, string const& variableName, AlbaNumber const& valueForEvaluation) {
    // f(c) is said to be the absolute minimum value of the f if c is in the domain of f and if f(c) <= f(x) for all
    // values of x in the domain of f.
    AlbaNumbers valuesUsedForChecking;
    putArbitiaryValuesBasedFromDomainOfTerm(valuesUsedForChecking, term);
    return willYieldToExtremumValue(
        ExtremumType::Minimum, term, variableName, valueForEvaluation, valuesUsedForChecking);
}

bool willYieldToAbsoluteMaximumValue(
    Term const& term, string const& variableName, AlbaNumber const& valueForEvaluation) {
    // f(c) is said to be the absolute maximum value of the f if c is in the domain of f and if f(c) >= f(x) for all
    // values of x in the domain of f.
    AlbaNumbers valuesUsedForChecking;
    putArbitiaryValuesBasedFromDomainOfTerm(valuesUsedForChecking, term);
    return willYieldToExtremumValue(
        ExtremumType::Maximum, term, variableName, valueForEvaluation, valuesUsedForChecking);
}

bool willYieldToRelativeMinimumValue(
    Term const& term, string const& variableName, AlbaNumber const& valueForEvaluation,
    AlbaNumberInterval const& openInterval) {
    // The function f is aid to have a relative minimum value at c if there exists an open interval containing c,
    // on which f is defined such that f(c) <= f(x) for all x in this interval
    if (openInterval.getLowerEndpoint().isOpen() && openInterval.getHigherEndpoint().isOpen()) {
        AlbaNumbers valuesUsedForChecking;
        putArbitiaryValuesFromInterval(valuesUsedForChecking, openInterval);
        return willYieldToExtremumValue(
            ExtremumType::Minimum, term, variableName, valueForEvaluation, valuesUsedForChecking);
    }
    return false;
}

bool willYieldToRelativeMaximumValue(
    Term const& term, string const& variableName, AlbaNumber const& valueForEvaluation,
    AlbaNumberInterval const& openInterval) {
    // The function f is aid to have a relative maximum value at c if there exists an open interval containing c,
    // on which f is defined such that f(c) >= f(x) for all x in this interval
    bool result(false);
    if (openInterval.getLowerEndpoint().isOpen() && openInterval.getHigherEndpoint().isOpen()) {
        AlbaNumbers valuesUsedForChecking;
        putArbitiaryValuesFromInterval(valuesUsedForChecking, openInterval);
        result = willYieldToExtremumValue(
            ExtremumType::Maximum, term, variableName, valueForEvaluation, valuesUsedForChecking);
    }
    return result;
}

bool willYieldToExtremumValue(
    ExtremumType const extremumType, Term const& term, string const& variableName, AlbaNumber const& valueForEvaluation,
    AlbaNumbers const& valuesUsedForChecking) {
    bool result(false);
    SubstitutionOfVariablesToValues const substitutionOfC({{variableName, valueForEvaluation}});
    Term const fOfC(substitutionOfC.performSubstitutionTo(term));
    if (fOfC.isConstant()) {
        for (AlbaNumber const& valueUsedForChecking : valuesUsedForChecking) {
            SubstitutionOfVariablesToValues const substitutionOfX({{variableName, valueUsedForChecking}});
            Term const fOfX(substitutionOfX.performSubstitutionTo(term));
            if (fOfX.isConstant()) {
                bool const isMaximum(fOfC.getAsNumber() >= fOfX.getAsNumber());
                bool const isMinimum(fOfC.getAsNumber() <= fOfX.getAsNumber());
                if ((isMaximum && ExtremumType::Maximum == extremumType) ||
                    (isMinimum && ExtremumType::Minimum == extremumType)) {
                    result = true;
                } else {
                    result = false;
                    break;
                }
            }
        }
    }
    return result;
}

bool isDerivativeZeroOnPossibleExtremum(
    Term const& term, string const& variableName, AlbaNumber const& valueAtPossibleExtremum,
    AlbaNumberInterval const& interval) {
    // If f(x) exists for all values of x in the open interval (a, b),
    // and if f has a relative extremum at c, where a<c<b and if f'(c) exists, then f'(c) = 0.
    Term const derivative(
        getDerivativeAtUsingLimit(term, variableName, valueAtPossibleExtremum, LimitAtAValueApproachType::BothSides));
    bool const hasRelativeExtremum =
        willYieldToRelativeMaximumValue(term, variableName, valueAtPossibleExtremum, interval) ||
        willYieldToRelativeMinimumValue(term, variableName, valueAtPossibleExtremum, interval);
    return hasRelativeExtremum && derivative.isConstant() && derivative.getAsNumber() == 0;
}

bool isDecreasingAt(Term const& term, string const& variableName, AlbaNumber const& value) {
    Differentiation const differentiation(variableName);
    Term const firstDerivativeTerm(differentiation.differentiate(term));
    SubstitutionOfVariablesToValues const substitution({{variableName, value}});
    Term const firstDerivativeValue(substitution.performSubstitutionTo(firstDerivativeTerm));
    bool result(false);
    if (firstDerivativeValue.isConstant()) {
        result = firstDerivativeValue.getAsNumber() < 0;
    }
    return result;
}

bool isIncreasingAt(Term const& term, string const& variableName, AlbaNumber const& value) {
    Differentiation const differentiation(variableName);
    Term const firstDerivativeTerm(differentiation.differentiate(term));
    SubstitutionOfVariablesToValues const substitution({{variableName, value}});
    Term const firstDerivativeValue(substitution.performSubstitutionTo(firstDerivativeTerm));
    bool result(false);
    if (firstDerivativeValue.isConstant()) {
        result = firstDerivativeValue.getAsNumber() > 0;
    }
    return result;
}

bool isConcaveDownwardAt(Term const& term, string const& variableName, AlbaNumber const& value) {
    Differentiation const differentiation(variableName);
    Term const secondDerivativeTerm(differentiation.differentiateMultipleTimes(term, 2));
    SubstitutionOfVariablesToValues const substitution({{variableName, value}});
    Term const secondDerivativeValue(substitution.performSubstitutionTo(secondDerivativeTerm));
    bool result(false);
    if (secondDerivativeValue.isConstant()) {
        result = secondDerivativeValue.getAsNumber() < 0;
    }
    return result;
}

bool isConcaveUpwardAt(Term const& term, string const& variableName, AlbaNumber const& value) {
    Differentiation const differentiation(variableName);
    Term const firstDerivativeTerm(differentiation.differentiateMultipleTimes(term, 2));
    SubstitutionOfVariablesToValues const substitution({{variableName, value}});
    Term const secondDerivativeValue(substitution.performSubstitutionTo(firstDerivativeTerm));
    bool result(false);
    if (secondDerivativeValue.isConstant()) {
        result = secondDerivativeValue.getAsNumber() > 0;
    }
    return result;
}

bool hasPointOfInflectionAt(Term const& term, string const& variableName, AlbaNumber const& value) {
    // The point (c, f(c)) is a point of inflection of the graph of the function f if the graph has a tangent line
    // there, and if there exists an open interval I containing c such that if x is in I, the either: (i) f''(x) < 0 if
    // x < c, and f''(x) > 0 if x > c, or (ii) f''(x) > 0 if x < c, and f''(x) < 0 if x > c
    Differentiation const differentiation(variableName);
    Term const secondDerivativeTerm(differentiation.differentiateMultipleTimes(term, 2));
    bool result(false);
    if (!secondDerivativeTerm.isConstant()) {
        SubstitutionOfVariablesToValues const substitution({{variableName, value}});
        Term const secondDerivativeValue(substitution.performSubstitutionTo(secondDerivativeTerm));
        if (secondDerivativeValue.isConstant()) {
            result = secondDerivativeValue.getAsNumber() == 0;
        }
    }
    return result;
}

bool isRolleTheoremSatisfied(
    Term const& term, string const& variableName, AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c) {
    // Rolle's theorem:
    // Let f be a function such that:
    // (i) it is continuous on the closed interval [a, b]
    // (ii) it is differentiable on the open interval (a, b)
    // (iii) f(a) = 0 and f(b) = 0
    // Then there is a number c in the open interval (a, b) such that f'(c) = 0
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, a);
    Term const fa(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, b);
    Term const fb(substitution.performSubstitutionTo(term));

    bool result(false);
    if (fa.isConstant() && fb.isConstant() && AlbaNumber(0) == fa.getAsNumber() && AlbaNumber(0) == fb.getAsNumber()) {
        AlbaNumberIntervals const continuityDomainIntervals(getContinuityDomain(term).getAcceptedIntervals());
        AlbaNumberIntervals const differentiabilityDomainIntervals(
            getDifferentiabilityDomain(term, variableName).getAcceptedIntervals());
        AlbaNumberInterval const abCloseInterval(createCloseEndpoint(a), createCloseEndpoint(b));
        AlbaNumberInterval const abOpenInterval(createOpenEndpoint(a), createOpenEndpoint(b));

        if (isIntervalInsideTheIntervals(abCloseInterval, continuityDomainIntervals) &&
            isIntervalInsideTheIntervals(abOpenInterval, differentiabilityDomainIntervals)) {
            Differentiation const differentiation(variableName);
            Term const firstDerivativeTerm(differentiation.differentiate(term));
            substitution.putVariableWithValue(variableName, c);
            Term const fPrimeC(substitution.performSubstitutionTo(firstDerivativeTerm));
            result = fPrimeC.isConstant() && AlbaNumber(0) == fPrimeC.getAsNumber();
        }
    }
    return result;
}

namespace {

void putArbitiaryValuesFromInterval(AlbaNumbers& arbitiaryValues, AlbaNumberInterval const& interval) {
    AlbaNumberIntervalEndpoint const lowEndpoint(interval.getLowerEndpoint());
    AlbaNumberIntervalEndpoint const highEndpoint(interval.getHigherEndpoint());
    AlbaNumber lowValue(convertIfInfinityToNearestFiniteValue(lowEndpoint.getValue()));
    AlbaNumber highValue(convertIfInfinityToNearestFiniteValue(highEndpoint.getValue()));
    if (lowEndpoint.isClose()) {
        arbitiaryValues.emplace_back(lowValue);
    }
    if (highEndpoint.isClose()) {
        arbitiaryValues.emplace_back(highValue);
    }
    for (int level = 0; level < 5; ++level) {
        AlbaNumber const midpoint = (lowValue + highValue) / 2;
        lowValue = (lowValue + midpoint) / 2;
        highValue = (highValue + midpoint) / 2;
        arbitiaryValues.emplace_back(lowValue);
        arbitiaryValues.emplace_back(midpoint);
        arbitiaryValues.emplace_back(highValue);
    }
}

void putArbitiaryValuesBasedFromDomainOfTerm(AlbaNumbers& arbitiaryValues, Term const& term) {
    SolutionSet const domainSolutionSet = calculateDomainForTermWithOneVariable(term);
    AlbaNumberIntervals const& domains(domainSolutionSet.getAcceptedIntervals());
    for (AlbaNumberInterval const domain : domains) {
        putArbitiaryValuesFromInterval(arbitiaryValues, domain);
    }
}

void retrieveSecondDerivatives(Terms& secondDerivatives, Term const& term, strings const& variableNames) {
    secondDerivatives.reserve(variableNames.size());
    transform(
        variableNames.cbegin(), variableNames.cend(), back_inserter(secondDerivatives),
        [&](string const& variableName) {
            return getPartialDerivative(getPartialDerivative(term, variableName), variableName);
        });
}

void retrieveSubstitutionsFromCriticalNumbers(
    SubstitutionsOfVariablesToValues& substitutions,
    VariableNameToCriticalNumbersMap const& variableNameToCriticalNumbersMap) {
    for (auto const& [variableName, criticalNumbers] : variableNameToCriticalNumbersMap) {
        int i = 0;
        for (AlbaNumber const& criticalNumber : criticalNumbers) {
            if (static_cast<int>(substitutions.size()) <= i) {
                substitutions.emplace_back();
            }
            substitutions[i++].putVariableWithValue(variableName, criticalNumber);
        }
    }
}

void determineExtrema(
    ExtremaWithMultipleVariables& extrema, Terms const& secondDerivatives,
    SubstitutionsOfVariablesToValues const& substitutions) {
    for (SubstitutionOfVariablesToValues const& substitution : substitutions) {
        ExtremumWithMultipleVariables extremum;
        ExtremumType extremumType(ExtremumType::Unknown);
        for (Term const& secondDerivative : secondDerivatives) {
            Term const secondDerivativeSubstituted(substitution.performSubstitutionTo(secondDerivative));
            if (secondDerivativeSubstituted.isConstant()) {
                AlbaNumber const& secondDerivativeValue(secondDerivativeSubstituted.getAsNumber());
                if (ExtremumType::Maximum == extremumType) {
                    if (secondDerivativeValue > 0) {
                        extremumType = ExtremumType::SaddlePoint;
                        break;
                    }
                } else if (ExtremumType::Minimum == extremumType) {
                    if (secondDerivativeValue < 0) {
                        extremumType = ExtremumType::SaddlePoint;
                        break;
                    }
                } else {
                    if (secondDerivativeValue < 0) {
                        extremumType = ExtremumType::Maximum;
                    } else if (secondDerivativeValue > 0) {
                        extremumType = ExtremumType::Minimum;
                    }
                }
            }
        }
        extremum.extremumType = extremumType;
        for (auto const& [variableName, value] : substitution.getVariableToValuesMap()) {
            extremum.variableNamesToValues[variableName] = value;
        }
        extrema.emplace_back(extremum);
    }
}

}  // namespace

}  // namespace alba::algebra
