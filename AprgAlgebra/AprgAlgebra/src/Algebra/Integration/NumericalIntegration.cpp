#include "NumericalIntegration.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

Term getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(
        Term const& term,
        DetailsForDefiniteIntegralWithValues const& integralDetails,
        unsigned int const numberOfSamples)
{
    // The Trapozoidal Rule
    AlbaNumber lengthOfInterval(integralDetails.higherEnd-integralDetails.lowerEnd);
    AlbaNumber incrementInX(lengthOfInterval/numberOfSamples);
    SubstitutionOfVariablesToValues substitution;
    Term sum(0);
    for(unsigned int i=0; i<=numberOfSamples; i++)
    {
        AlbaNumber currentX(integralDetails.lowerEnd + incrementInX*i);
        substitution.putVariableWithValue(integralDetails.variableName, currentX);
        Term currentY(substitution.performSubstitutionTo(term));
        if(i==0 || i==numberOfSamples)
        {
            sum = sum + currentY;
        }
        else
        {
            sum = sum + (currentY * 2);
        }
    }
    return lengthOfInterval / 2 / numberOfSamples * sum;
}

Term getAnApproximateOfDefiniteIntegralUsingSimpsonRule(
        Term const& term,
        DetailsForDefiniteIntegralWithValues const& integralDetails,
        unsigned int const numberOfSamples)
{
    // The Simpson Rule
    AlbaNumber lengthOfInterval(integralDetails.higherEnd-integralDetails.lowerEnd);
    AlbaNumber incrementInX(lengthOfInterval/numberOfSamples);
    SubstitutionOfVariablesToValues substitution;
    Term sum(0);
    for(unsigned int i=0; i<=numberOfSamples; i++)
    {
        AlbaNumber currentX(integralDetails.lowerEnd + incrementInX*i);
        substitution.putVariableWithValue(integralDetails.variableName, currentX);
        Term currentY(substitution.performSubstitutionTo(term));
        if(i==0 || i==numberOfSamples)
        {
            sum = sum + currentY;
        }
        else if(isOdd(i))
        {
            sum = sum + (currentY * 4);
        }
        else
        {
            sum = sum + (currentY * 2);
        }
    }
    return lengthOfInterval / 3 / numberOfSamples * sum;
}

Term getActualTruncationErrorInTrapezoidalRule(
        Term const& term,
        DetailsForDefiniteIntegralWithValues const& integralDetails,
        unsigned int const numberOfSamples)
{
    Integration integration(integralDetails.variableName);
    return integration.integrateAtDefiniteValues(term, integralDetails.lowerEnd, integralDetails.higherEnd)
            - getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(term, integralDetails, numberOfSamples);
}

Term getActualTruncationErrorInSimpsonRule(
        Term const& term,
        DetailsForDefiniteIntegralWithValues const& integralDetails,
        unsigned int const numberOfSamples)
{
    Integration integration(integralDetails.variableName);
    return integration.integrateAtDefiniteValues(term, integralDetails.lowerEnd, integralDetails.higherEnd)
            - getAnApproximateOfDefiniteIntegralUsingSimpsonRule(term, integralDetails, numberOfSamples);
}

Term getAnApproximateOfTruncationErrorInTrapezoidalRuleAt(
        Term const& term,
        DetailsForDefiniteIntegralWithValues const& integralDetails,
        AlbaNumber const& valueToCheckAt,
        AlbaNumber const& deltaX)
{
    Differentiation differentiation(integralDetails.variableName);
    Term termDoublePrime(differentiation.differentiateMultipleTimes(term, 2));
    SubstitutionOfVariablesToValues substitution{{integralDetails.variableName, valueToCheckAt}};
    Term termDoublePrimeValue(substitution.performSubstitutionTo(termDoublePrime));
    AlbaNumber lengthOfInterval(integralDetails.higherEnd-integralDetails.lowerEnd);
    return lengthOfInterval / -12 * (deltaX ^ 2) * termDoublePrimeValue;
}

Term getAnApproximateOfTruncationErrorInSimpsonRuleAt(
        Term const& term,
        DetailsForDefiniteIntegralWithValues const& integralDetails,
        AlbaNumber const& valueToCheckAt,
        AlbaNumber const& deltaX)
{
    Differentiation differentiation(integralDetails.variableName);
    Term termDoublePrime(differentiation.differentiateMultipleTimes(term, 4));
    SubstitutionOfVariablesToValues substitution{{integralDetails.variableName, valueToCheckAt}};
    Term termDoublePrimeValue(substitution.performSubstitutionTo(termDoublePrime));
    AlbaNumber lengthOfInterval(integralDetails.higherEnd-integralDetails.lowerEnd);
    return lengthOfInterval / -180 * (deltaX ^ 2) * termDoublePrimeValue;
}

AlbaNumber getAnApproximateOfNaturalLogarithmUsingTrapezoidRule(
        AlbaNumber const& input,
        unsigned int const numberOfSamples)
{
    AlbaNumber result;
    if(input > 0)
    {
        Term oneOverX(Term(1)/Term("x"));
        Term approximateValue(getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(oneOverX, {"x", AlbaNumber(1), input}, numberOfSamples));
        if(approximateValue.isConstant())
        {
            result = approximateValue.getConstantValueConstReference();
        }
    }
    return result;
}

AlbaNumber getAnApproximateOfNaturalLogarithmUsingSimpsonRule(
        AlbaNumber const& input,
        unsigned int const numberOfSamples)
{
    AlbaNumber result;
    if(input > 0)
    {
        Term oneOverX(Term(1)/Term("x"));
        Term approximateValue(getAnApproximateOfDefiniteIntegralUsingSimpsonRule(oneOverX, {"x", AlbaNumber(1), input}, numberOfSamples));
        if(approximateValue.isConstant())
        {
            result = approximateValue.getConstantValueConstReference();
        }
    }
    return result;
}

}

}
