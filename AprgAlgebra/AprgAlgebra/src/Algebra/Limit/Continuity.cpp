#include "Continuity.hpp"

#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace alba::algebra::DomainAndRange;
using namespace std;

namespace alba::algebra {

ContinuityType getContinuityTypeAt(Term const& term, string const& variableName, AlbaNumber const& value) {
    ContinuityType result(ContinuityType::Unknown);
    SubstitutionOfVariablesToValues const substitution{{variableName, value}};
    Term const substitutedResult(substitution.performSubstitutionTo(term));
    if (substitutedResult.isConstant()) {
        AlbaNumber const limitAtValueInPositiveSide(getLimitAtAValueInThePositiveSide(term, variableName, value));
        AlbaNumber const limitAtValueInNegativeSide(getLimitAtAValueInTheNegativeSide(term, variableName, value));
        if (isAlmostEqualForLimitChecking(limitAtValueInPositiveSide, limitAtValueInNegativeSide)) {
            AlbaNumber const& substitutedResultValue(substitutedResult.getAsNumber());
            if (isAlmostEqualForLimitChecking(limitAtValueInPositiveSide, substitutedResultValue)) {
                result = ContinuityType::ContinuousAtBothSides;
            } else {
                result = ContinuityType::DiscontinuousWithRemovableDiscontinuity;
            }
        } else {
            result = ContinuityType::DiscontinuousWithEssentialDiscontinuity;
        }
    }
    return result;
}

SolutionSet getContinuityDomain(Term const& term) {
    // Calculus Theorem:  A polynomial function is continuous at every number.
    // Calculus Theorem:  A rational function (polynomial over polynomial) is continuous at every number in its domain.
    // Calculus Observation:  A radical function is continuous at every number in its domain.
    // Calculus Theorem:  A sine function is continuous at every number.
    // Calculus Theorem:  A cosine function is continuous at every number.
    // This code is not accurate. How about piecewise function?
    return calculateDomainForTermWithOneVariable(term);
}

bool isContinuousAtWithMultipleVariablesWithDifferentApproaches(
    Term const& term, string const& variableName, AlbaNumber const& valueToApproach,
    SubstitutionsOfVariablesToTerms const& substitutionsForApproaches) {
    SubstitutionOfVariablesToValues const substitution{{variableName, valueToApproach}};
    Term substitutedResult;
    if (!substitutionsForApproaches.empty()) {
        substitutedResult =
            substitution.performSubstitutionTo(substitutionsForApproaches[0].performSubstitutionTo(term));
    }
    Term const limitAtValue(getLimitWithMultipleVariablesWithDifferentApproaches(
        term, variableName, valueToApproach, substitutionsForApproaches));
    return substitutedResult == limitAtValue && isARealFiniteConstant(substitutedResult);
}

bool isIntermediateValueTheoremSatisfied(
    Term const& term, string const& variableName, AlbaNumber const& firstValue, AlbaNumber const& secondValue,
    AlbaNumber const& valueToTest) {
    // Theorem: If the function f is continuous on the closed interval [v1, v2] and if f(v1) != f(v2),
    // then for any number k between f(v1) and f(v2) there exists a number v3 between v1 and v2 such that f(v3) = k
    bool result(false);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, firstValue);
    Term const outputOfFirst(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, secondValue);
    Term const outputOfSecond(substitution.performSubstitutionTo(term));
    if (outputOfFirst.isConstant() && outputOfSecond.isConstant()) {
        AlbaNumber const outputValueOfFirst(outputOfFirst.getAsNumber());
        AlbaNumber const outputValueOfSecond(outputOfSecond.getAsNumber());
        SolutionSet const continuityDomain(getContinuityDomain(term));
        AlbaNumberIntervals const& continuityDomainIntervals(continuityDomain.getAcceptedIntervals());
        AlbaNumberInterval const firstAndSecondInterval(
            createCloseEndpoint(firstValue), createCloseEndpoint(secondValue));
        bool const areOutputValuesNotEqual = outputValueOfFirst != outputValueOfSecond;
        bool const areFirstAndSecondIntervalInContinuousDomain =
            isIntervalInsideTheIntervals(firstAndSecondInterval, continuityDomainIntervals);
        bool const isValueToTestBetweenFirstAndSecond = firstAndSecondInterval.isValueInsideTheInterval(valueToTest);
        result = areFirstAndSecondIntervalInContinuousDomain && areOutputValuesNotEqual &&
                 isValueToTestBetweenFirstAndSecond;
    }
    return result;
}

bool isContinuousAt(Term const& term, string const& variableName, AlbaNumber const& valueToApproach) {
    SubstitutionOfVariablesToValues const substitution{{variableName, valueToApproach}};
    Term const substitutedResult(substitution.performSubstitutionTo(term));
    Term const limitAtValue(getLimit(term, variableName, valueToApproach));
    return substitutedResult == limitAtValue && isARealFiniteConstant(substitutedResult);
}

bool isContinuousAt(
    Term const& term, string const& variableName, AlbaNumber const& valueToApproach,
    LimitAtAValueApproachType const limitApproachType) {
    bool result(false);
    SubstitutionOfVariablesToValues const substitution{{variableName, valueToApproach}};
    Term const substitutedResult(substitution.performSubstitutionTo(term));
    if (substitutedResult.isConstant()) {
        AlbaNumber const limitAtValue(
            getLimitAtAValueByApproachType(term, variableName, valueToApproach, limitApproachType));
        AlbaNumber const& substitutedResultValue(substitutedResult.getAsNumber());
        result = isAlmostEqualForLimitChecking(substitutedResultValue, limitAtValue);
    }
    return result;
}

bool isContinuousAt(
    Term const& term, string const& variableName, AlbaNumber const& valueToApproach,
    LimitAtAValueApproachType const limitApproachType, bool const isDifferentiableAtValue) {
    // If a function is differentiable at X, then f is continuous at X.
    bool result(true);
    if (!isDifferentiableAtValue) {
        result = isContinuousAt(term, variableName, valueToApproach, limitApproachType);
    }
    return result;
}

}  // namespace alba::algebra
