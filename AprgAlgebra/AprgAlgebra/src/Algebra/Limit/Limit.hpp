#pragma once

#include <Algebra/Limit/LimitAtAValueApproachType.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba::algebra {

void calculateTermAndLimitUsingLhopitalsRule(
    Term& newTerm, Term& limitValue, Term const& term, std::string const& variableName,
    AlbaNumber const& valueToApproach);

AlbaNumber getLimitAtAValueByApproachType(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach,
    LimitAtAValueApproachType const limitApproachType);

AlbaNumber getLimitAtAValueInBothSides(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);

AlbaNumber getLimitAtAValueInThePositiveSide(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);

AlbaNumber getLimitAtAValueInTheNegativeSide(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);

AlbaNumber getLimitAtAValueByIterationAndLinearInterpolation(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach,
    AlbaNumber const& initialValueForIteration, int const maxNumberOfIterations);

AlbaNumber getLimitAtAValueUsingTrendOfValues(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach,
    AlbaNumber const& previousAcceptedInput, AlbaNumber const& previousOfPreviousAcceptedInput);

AlbaNumber getValueUsingLinearInterpolation(
    AlbaNumber const& input1, AlbaNumber const& input2, AlbaNumber const& inputValue, AlbaNumber const& output1,
    AlbaNumber const& output2);

Term getLimit(Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);

Term getLimitWithMultipleVariablesWithDifferentApproaches(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach,
    SubstitutionsOfVariablesToTerms const& substitutionsForApproaches);

Term getLimitUsingLhopitalsRule(Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);
Term getTermUsingLhopitalsRule(Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);
Term getLimitAtAValueOrInfinity(Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);

Term getLimitAtAValue(
    Term const& term, std::string const& variableName, AlbaNumber const& value,
    LimitAtAValueApproachType const limitApproachType);

Term simplifyAndGetLimitAtAValue(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach,
    LimitAtAValueApproachType const limitApproachType);

Term getLimitAtInfinity(Term const& term, std::string const& variableName, AlbaNumber const infinityValue);
Term getObliqueAsymptote(Term const& term);
bool isAlmostEqualForLimitIteration(AlbaNumber const& value1, AlbaNumber const& value2);
bool isAlmostEqualForLimitChecking(AlbaNumber const& value1, AlbaNumber const& value2);
bool hasVerticalAsymptoteAtValue(Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);

bool hasHorizontalAsymptoteAtValue(
    Term const& term, std::string const& variableName, AlbaNumber const& valueToApproach);

bool isSqueezeTheoremSatisfied(
    Term const& alwaysLowerTermAtInterval, Term const& termInBetweenAtInterval, Term const& alwaysHigherTermAtInterval,
    std::string const& variableName, AlbaNumber const& valueToApproach);

bool continueToDifferentiateForLhopitalsRule(
    Term const& numerator, Term const& denominator, Term const& numeratorValue, Term const& denominatorValue);

}  // namespace alba::algebra
