#include "IntegrationUtilities.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Extrema/ExtremaUtilities.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba::algebra {

AlbaNumbers getInputForAverageValueInBetweenTwoValues(
    Term const& term, string const& variableName, AlbaNumber const& lowerEndInInterval,
    AlbaNumber const& higherEndInInterval) {
    // Mean-Value theorem for integrals:
    // If the function f is continuous on the closed interval [a, b],
    // there exists a number "average" in [a, b] such that:
    // The definite integral in [a, b] = f("average") * (b-a)
    Equation const meanValueTheoremEquation(
        term, "=", getAverageValueInBetweenTwoValues(term, {variableName, lowerEndInInterval, higherEndInInterval}));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet const solutionSet(solver.calculateSolutionAndReturnSolutionSet(meanValueTheoremEquation));
    AlbaNumberInterval const openInterval(
        createOpenEndpoint(lowerEndInInterval), createOpenEndpoint(higherEndInInterval));
    return getNumbersInsideTheInterval(solutionSet.getAcceptedValues(), openInterval);
}

LowerAndHigherValues getApproximateValuesForDefiniteIntegral(
    Term const& term, string const& variableName, AlbaNumber const& lowerEndInInterval,
    AlbaNumber const& higherEndInInterval) {
    AlbaNumberInterval const closedInterval(
        createCloseEndpoint(lowerEndInInterval), createCloseEndpoint(higherEndInInterval));
    MinimumAndMaximum const minMaxValues(getMinimumAndMaximumAtClosedInterval(term, variableName, closedInterval));
    AlbaNumber const delta(higherEndInInterval - lowerEndInInterval);
    LowerAndHigherValues result;
    result.higherValue = minMaxValues.maximumInputOutputValues.second * delta;
    result.lowerValue = minMaxValues.minimumInputOutputValues.second * delta;
    return result;
}

Term getAverageValueInBetweenTwoValues(Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails) {
    Integration integration(integralDetails.variableName);
    return integration.integrateAtDefiniteValues(term, integralDetails.lowerEnd, integralDetails.higherEnd) /
           (integralDetails.higherEnd - integralDetails.lowerEnd);
}

Term evaluateValuesAndGetDifference(
    Term const& term, string const& variableName, AlbaNumber const& lowerEnd, AlbaNumber const& higherEnd) {
    Term result(evaluate(term, variableName, higherEnd) - evaluate(term, variableName, lowerEnd));
    result.simplify();
    return result;
}

Term evaluateTermsAndGetDifference(
    Term const& term, string const& variableName, Term const& lowerEnd, Term const& higherEnd) {
    Term result(evaluate(term, variableName, higherEnd) - evaluate(term, variableName, lowerEnd));
    result.simplify();
    return result;
}

Term evaluate(Term const& term, string const& variableName, Term const& value) {
    Term result;
    if (isTheValue(value, ALBA_NUMBER_POSITIVE_INFINITY)) {
        result = getLimit(term, variableName, ALBA_NUMBER_POSITIVE_INFINITY);
    } else if (isTheValue(value, ALBA_NUMBER_NEGATIVE_INFINITY)) {
        result = getLimit(term, variableName, ALBA_NUMBER_NEGATIVE_INFINITY);
    } else {
        SubstitutionOfVariablesToTerms const substitution({{variableName, value}});
        result = substitution.performSubstitutionTo(term);
    }
    return result;
}

Term getAreaUnderACurveUsingReimannSums(
    Term const& term, string const& variableName, AlbaNumber const& lowerEndInInterval,
    AlbaNumber const& higherEndInInterval) {
    AlbaNumber const deltaOfValues(higherEndInInterval - lowerEndInInterval);
    Term inputForHeight(
        Polynomial{Monomial(lowerEndInInterval, {}), Monomial(deltaOfValues, {{"n", -1}, {variableName, 1}})});
    SubstitutionOfVariablesToTerms const substitution({{variableName, inputForHeight}});
    Term const heightOfARectangle(substitution.performSubstitutionTo(term));
    Term const widthOfARectangle(Monomial(deltaOfValues, {{"n", -1}}));
    Term const areaOfARectangle(heightOfARectangle * widthOfARectangle);
    Summation const summation(areaOfARectangle, variableName);
    Term const sumOfAreaOfAllRectangles(summation.getSum(1, "n"));
    LimitsAtInfinity const limits(sumOfAreaOfAllRectangles, "n");
    return limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY);  // Let number of rectangles approach infinity
}

bool isTheSecondFundamentalTheoremOfCalculusTrue(
    Term const& term, string const& variableName, AlbaNumber const& a, AlbaNumber const& b) {
    // The second fundamental theorem of calculus
    // Let the function f be continuous on the closed interval [a, b] and let the derivative of g be equal to f for all
    // x in [a, b]. Then the definite integral of f from a to b is equal of g(b)- g(a)
    Differentiation const differentiation(variableName);
    Integration integration(variableName);
    Term const g(integration.integrate(term));
    Term const gPrime(differentiation.differentiate(g));
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();
    bool const isGPrimeEqualToF = gPrime == simplifiedTerm;
    bool const isDefiniteIntegralEqualToDifference =
        integration.integrateAtDefiniteValues(term, a, b) == evaluateValuesAndGetDifference(g, variableName, a, b);
    return isGPrimeEqualToF && isDefiniteIntegralEqualToDifference;
}

bool isTheIntegralDefinitionForFiniteCalculusIsTrue(
    Term const& term, string const& variableName, AlbaNumber const& a, AlbaNumber const& b) {
    // The fundamental theorem of finite calculus:
    // The discrete definite integral from a to b is equal to
    // The summation of terms from a to b-1.
    IntegrationForFiniteCalculus const integration(variableName);
    Summation const summation(term, variableName);
    return integration.integrateAtDefiniteValues(term, a, b) == summation.getSum(a, b - 1);
}

bool isAreaUnderTheCurveEqualToDefiniteIntegral(
    Term const& term, string const& variableName, AlbaNumber const& a, AlbaNumber const& b) {
    Integration integration(variableName);
    return integration.integrateAtDefiniteValues(term, a, b) ==
           getAreaUnderACurveUsingReimannSums(term, variableName, a, b);
}

}  // namespace alba::algebra
