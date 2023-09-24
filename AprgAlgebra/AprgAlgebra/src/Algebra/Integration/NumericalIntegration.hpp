#pragma once

#include <Algebra/Integration/DetailsForDefiniteIntegralWithValues.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba::algebra {

AlbaNumber getAnApproximateOfNaturalLogarithmUsingTrapezoidRule(AlbaNumber const& input, int const numberOfSamples);
AlbaNumber getAnApproximateOfNaturalLogarithmUsingSimpsonRule(AlbaNumber const& input, int const numberOfSamples);

Term getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, int const numberOfSamples);

Term getAnApproximateOfDefiniteIntegralUsingSimpsonRule(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, int const numberOfSamples);

Term getActualTruncationErrorInTrapezoidalRule(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, int const numberOfSamples);

Term getActualTruncationErrorInSimpsonRule(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, int const numberOfSamples);

Term getAnApproximateOfTruncationErrorInTrapezoidalRuleAt(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, AlbaNumber const& valueToCheckAt,
    AlbaNumber const& deltaX);

Term getAnApproximateOfTruncationErrorInSimpsonRuleAt(
    Term const& term, DetailsForDefiniteIntegralWithValues const& integralDetails, AlbaNumber const& valueToCheckAt,
    AlbaNumber const& deltaX);

}  // namespace alba::algebra
