#include "Limit.hpp"

#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba{

namespace algebra
{

namespace
{

constexpr double POSITIVE_DELTA_FOR_INITIAL_VALUE=1;
constexpr unsigned int MAX_NUMBER_OF_ITERATIONS=100;

}

bool isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber const& value)
{
    return !value.isARealFiniteValue() || value.getDouble() == 0;
}

AlbaNumber getLimitValueByApproachType(        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitApproachType const limitApproachType)
{
    AlbaNumber result;
    if(LimitApproachType::BothSides == limitApproachType)
    {
        result = getLimitInBothSides(term, variableName, valueToApproach);
    }
    else if(LimitApproachType::PositiveSide == limitApproachType)
    {
        result = getLimitInPositiveSide(term, variableName, valueToApproach);
    }
    else if(LimitApproachType::NegativeSide == limitApproachType)
    {
        result = getLimitInNegativeSide(term, variableName, valueToApproach);
    }    return result;
}

AlbaNumber getLimitInBothSides(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    AlbaNumber result(AlbaNumber::Value::NotANumber);
    AlbaNumber limitPositiveSide(getLimitInPositiveSide(term, variableName, valueToApproach));
    AlbaNumber limitNegativeSide(getLimitInNegativeSide(term, variableName, valueToApproach));
    if(limitPositiveSide == limitNegativeSide) //limit only exists if both sides are equal  (Calculus Theorem)
    {
        result = getAverageForAlbaNumber(limitPositiveSide, limitNegativeSide);
    }
    return result;
}

AlbaNumber getLimitInPositiveSide(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    return getLimitByIterationAndLinearInterpolation(
                term,
                variableName,
                valueToApproach,
                valueToApproach + POSITIVE_DELTA_FOR_INITIAL_VALUE,
                MAX_NUMBER_OF_ITERATIONS);
}

AlbaNumber getLimitInNegativeSide(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    return getLimitByIterationAndLinearInterpolation(
                term,
                variableName,
                valueToApproach,
                valueToApproach - POSITIVE_DELTA_FOR_INITIAL_VALUE,
                MAX_NUMBER_OF_ITERATIONS);
}

AlbaNumber getLimitByIterationAndLinearInterpolation(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach,
        AlbaNumber const& initialValueForIteration,
        unsigned int maxNumberOfIterations)
{
    SubstitutionOfVariablesToValues substitution;
    AlbaNumber currentInput(initialValueForIteration);
    AlbaNumber previousAcceptedInput(currentInput);
    AlbaNumber previousPreviousAcceptedInput(currentInput);
    AlbaNumber previousRejectedInput(valueToApproach);
    for(unsigned int i=0; i<maxNumberOfIterations && currentInput != previousRejectedInput; i++)
    {
        substitution.putVariableWithValue(variableName, currentInput);
        Term currentOutputTerm = substitution.performSubstitutionTo(term);        if(currentOutputTerm.isConstant())
        {
            AlbaNumber currentOutputNumber(currentOutputTerm.getConstantConstReference().getNumberConstReference());
            if(isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(currentOutputNumber))
            {
                previousRejectedInput = currentInput;
            }            else
            {
                previousPreviousAcceptedInput = previousAcceptedInput;
                previousAcceptedInput = currentInput;
            }
            AlbaNumber newInput(getAverageForAlbaNumber(previousAcceptedInput, previousRejectedInput));
            if(newInput == valueToApproach) { break; }
            currentInput = newInput;
        }
        else
        {
            break;
        }
    }

    return getLimitValue(term, variableName, valueToApproach, previousAcceptedInput, previousPreviousAcceptedInput);
}

AlbaNumber getLimitValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach,
        AlbaNumber const& previousAcceptedInput,
        AlbaNumber const& previousPreviousAcceptedInput)
{
    AlbaNumber result;
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, valueToApproach);
    Term outputTermAtValueToApproach(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, previousAcceptedInput);
    Term previousAcceptedOutputTerm(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, previousPreviousAcceptedInput);
    Term previousPreviousAcceptedOutputTerm(substitution.performSubstitutionTo(term));
    if(outputTermAtValueToApproach.isConstant()
            && previousAcceptedOutputTerm.isConstant()
            && previousPreviousAcceptedOutputTerm.isConstant())
    {
        AlbaNumber outputAtValueToApproach(outputTermAtValueToApproach.getConstantConstReference().getNumberConstReference());
        AlbaNumber previousAcceptedOutput(previousAcceptedOutputTerm.getConstantConstReference().getNumberConstReference());
        AlbaNumber previousPreviousAcceptedOutput(previousPreviousAcceptedOutputTerm.getConstantConstReference().getNumberConstReference());
        if(outputAtValueToApproach.isNegativeInfinity() || outputAtValueToApproach.isPositiveInfinity())
        {
            if(previousAcceptedOutput<0)
            {
                result = AlbaNumber(AlbaNumber::Value::NegativeInfinity);
            }
            else
            {
                result = AlbaNumber(AlbaNumber::Value::PositiveInfinity);
            }
        }
        else
        {
            result = getValueUsingLinearInterpolation(
                        previousPreviousAcceptedInput,
                        previousAcceptedInput,
                        valueToApproach,
                        previousPreviousAcceptedOutput,
                        previousAcceptedOutput);
        }
    }
    return result;
}
AlbaNumber getValueUsingLinearInterpolation(
        AlbaNumber const& input1,
        AlbaNumber const& input2,
        AlbaNumber const& inputValue,
        AlbaNumber const& output1,
        AlbaNumber const& output2)
{
    AlbaNumber deltaInput = input2-input1;
    AlbaNumber deltaOutput = output2-output1;
    AlbaNumber deltaInputToUse = inputValue-input2;
    AlbaNumber result;
    if(deltaInput == 0)
    {
        result = AlbaNumber(AlbaNumber::Value::NotANumber);
    }
    else
    {
        result = output2 + (deltaOutput / deltaInput * deltaInputToUse);
    }
    return result;
}

Term getLimitAsItApproachesAValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitApproachType const limitApproachType)
{
    SubstitutionOfVariablesToValues substitution{{variableName, valueToApproach}};
    Term limitResult(substitution.performSubstitutionTo(term));
    if(limitResult.isConstant())
    {
        AlbaNumber limitResultNumber(limitResult.getConstantConstReference().getNumberConstReference());
        if(isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(limitResultNumber))
        {
            limitResult = Term(getLimitValueByApproachType(term, variableName, valueToApproach, limitApproachType));
        }
    }
    return limitResult;}

}

}