#include "DomainAndRange.hpp"

#include <Algebra/Retrieval/SingleVariableNameRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Solution/SolutionUtilities.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace alba::AlbaNumberConstants;
using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra::DomainAndRange {

void collectAndUniqueValuesAndSort(AlbaNumbersSet& sortedValues, AlbaNumbers const& valuesToCheck) {
    for (AlbaNumber const& valueToCheck : valuesToCheck) {
        sortedValues.emplace(valueToCheck);
    }
}

void collectMinAndMaxValues(AlbaNumbersSet& collectedValues, AlbaNumbersSet const& sortedValues) {
    int const valuesSize = static_cast<int>(sortedValues.size());
    if (valuesSize == 1) {
        auto itFront = sortedValues.cbegin();
        collectedValues.emplace(*itFront);
    } else if (sortedValues.size() >= 2) {
        auto itFront = sortedValues.cbegin();
        auto itBack = sortedValues.cend();
        --itBack;
        collectedValues.emplace(*itFront);
        collectedValues.emplace(*itBack);
    }
}

void appendTransitionValues(
    AlbaNumbersSet& transitionValues, AlbaNumbersSet const& sortedValues, FunctionToCheck const& functionToCheck) {
    AlbaNumber previousInputValue;
    AlbaNumber previousOutputValue;
    if (!sortedValues.empty()) {
        auto it = sortedValues.cbegin();
        previousInputValue = *it;
        previousOutputValue = functionToCheck(previousInputValue);
        ++it;
        for (; it != sortedValues.cend(); ++it) {
            AlbaNumber const& inputValue(*it);
            AlbaNumber const outputValue(functionToCheck(inputValue));
            if (previousOutputValue.isARealFiniteValue() && !outputValue.isARealFiniteValue()) {
                transitionValues.emplace(getTransitionValue(previousInputValue, inputValue, functionToCheck));
            } else if (!previousOutputValue.isARealFiniteValue() && outputValue.isARealFiniteValue()) {
                transitionValues.emplace(getTransitionValue(inputValue, previousInputValue, functionToCheck));
            }
            previousInputValue = inputValue;
            previousOutputValue = outputValue;
        }
    }
}

void retrieveTwoVariableNames(
    string& nameThatMatch, string& nameThatDoesNotMatch, VariableNamesSet const& variableNames,
    string const& variableNameToCheck) {
    if (variableNames.size() == 2) {
        auto it = variableNames.cbegin();
        string const variableName1 = *(it++);
        string const variableName2 = *(it++);
        if (variableName1 == variableNameToCheck) {
            nameThatMatch = variableName1;
            nameThatDoesNotMatch = variableName2;
        } else if (variableName2 == variableNameToCheck) {
            nameThatMatch = variableName2;
            nameThatDoesNotMatch = variableName1;
        }
    }
}

AlbaNumber getTransitionValue(
    AlbaNumber const& inputValueYieldsToFiniteValue, AlbaNumber const& inputValueYieldsToNonFiniteValue,
    FunctionToCheck const& functionToCheck) {
    AlbaNumber currentValueToRealFiniteValue(inputValueYieldsToFiniteValue);
    AlbaNumber currentValueToNonRealFiniteValue(inputValueYieldsToNonFiniteValue);
    AlbaNumber newInputValue(inputValueYieldsToFiniteValue);
    AlbaNumber previousInputValue(inputValueYieldsToNonFiniteValue);
    while (previousInputValue != newInputValue) {
        previousInputValue = newInputValue;
        newInputValue = getAverage(currentValueToRealFiniteValue, currentValueToNonRealFiniteValue);
        AlbaNumber const newOutputValue(functionToCheck(newInputValue));
        if (newOutputValue.isARealFiniteValue()) {
            currentValueToRealFiniteValue = newInputValue;
        } else {
            currentValueToNonRealFiniteValue = newInputValue;
        }
    }
    return newInputValue;
}

AlbaNumbers getNumbers(AlbaNumbersSet const& collectedValues) {
    return {collectedValues.cbegin(), collectedValues.cend()};
}

SolutionSet calculateDomainUsingTransitionValues(
    AlbaNumbers const& domainValuesToCheck, FunctionToCheck const& functionToCheck) {
    // This would be better if we have differentiation.
    SolutionSet domain;

    AlbaNumbersSet sortedValues;
    AlbaNumbersSet collectedValues;
    collectAndUniqueValuesAndSort(sortedValues, domainValuesToCheck);
    collectMinAndMaxValues(collectedValues, sortedValues);
    appendTransitionValues(collectedValues, sortedValues, functionToCheck);
    AlbaNumbers const transitionValues(getNumbers(collectedValues));

    domain.determineAndAddAcceptedIntervals(transitionValues, [&](AlbaNumber const& value) {
        AlbaNumber const computedValue(functionToCheck(value));
        return computedValue.isARealFiniteValue();
    });
    return domain;
}

SolutionSet calculateDomainForTermWithOneVariable(AlbaNumbers const& valuesToCheck, Term const& term) {
    SolutionSet domain;
    SingleVariableNameRetriever retriever;
    retriever.retrieveFromTerm(term);
    if (retriever.hasNoVariables()) {
        domain.addAcceptedInterval(createAllRealValuesInterval());
    } else if (retriever.hasOnlyASingleVariable()) {
        string variableName(retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty());
        SubstitutionOfVariablesToValues substitution;
        domain = calculateDomainUsingTransitionValues(valuesToCheck, [&](AlbaNumber const& value) {
            substitution.putVariableWithValue(variableName, value);
            Term const computedTerm(substitution.performSubstitutionTo(term));
            AlbaNumber computedValue;
            if (computedTerm.isConstant()) {
                computedValue = computedTerm.getAsNumber();
            }
            return computedValue;
        });
    }
    return domain;
}

SolutionSet calculateDomainForTermWithOneVariable(Term const& term) {
    return calculateDomainForTermWithOneVariable(getInitialValuesForIteratingMethods(term), term);
}

SolutionSet calculateDomainForEquation(
    string const& variableNameToCheck, AlbaNumbers const& valuesToCheck, Equation const& equation) {
    SolutionSet domain;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromEquation(equation);
    VariableNamesSet const& variableNames(variableNamesRetriever.getVariableNames());
    string inputName;
    string outputName;
    retrieveTwoVariableNames(inputName, outputName, variableNames, variableNameToCheck);
    if (!inputName.empty() && !outputName.empty()) {
        domain = calculateDomainForEquationWithVariableToSubstitute(inputName, valuesToCheck, equation);
    }
    return domain;
}

SolutionSet calculateDomainForEquation(string const& variableNameToCheck, Equation const& equation) {
    return calculateDomainForEquation(variableNameToCheck, getInitialValuesForIteratingMethods(equation), equation);
}

SolutionSet calculateRangeForEquation(
    string const& variableNameToCheck, AlbaNumbers const& valuesToCheck, Equation const& equation) {
    SolutionSet domain;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromEquation(equation);
    VariableNamesSet const& variableNames(variableNamesRetriever.getVariableNames());
    string inputName;
    string outputName;
    retrieveTwoVariableNames(inputName, outputName, variableNames, variableNameToCheck);
    if (!inputName.empty() && !outputName.empty()) {
        domain = calculateDomainForEquationWithVariableToSubstitute(outputName, valuesToCheck, equation);
    }
    return domain;
}

SolutionSet calculateRangeForEquation(string const& variableNameToCheck, Equation const& equation) {
    return calculateRangeForEquation(variableNameToCheck, getInitialValuesForIteratingMethods(equation), equation);
}

SolutionSet calculateDomainForEquationWithVariableToSubstitute(
    string const& variableNameToSubstitute, AlbaNumbers const& valuesToCheck, Equation const& equation) {
    SolutionSet domain;
    SubstitutionOfVariablesToValues substitution;
    OneEquationOneVariableEqualitySolver solver;
    domain = calculateDomainUsingTransitionValues(valuesToCheck, [&](AlbaNumber const& value) {
        substitution.putVariableWithValue(variableNameToSubstitute, value);
        Equation const simplifiedEquation(substitution.performSubstitutionTo(equation));
        Equation const equationToSolve(simplifiedEquation.getLeftHandTerm(), "=", 0);
        SolutionSet const solutionSet(solver.calculateSolutionAndReturnSolutionSet(equationToSolve));
        AlbaNumber computedValue(ALBA_NUMBER_NOT_A_NUMBER);
        AlbaNumbers acceptedValues(solutionSet.getAcceptedValues());
        if (!acceptedValues.empty()) {
            computedValue = acceptedValues.back();
        }
        return computedValue;
    });
    return domain;
}

bool isOneToOne(string const& variableNameToCheck, Equation const& equation) {
    bool result(false);
    SolutionSet const domain(calculateDomainForEquation(variableNameToCheck, equation));
    SolutionSet const range(calculateRangeForEquation(variableNameToCheck, equation));
    AlbaNumberIntervals const& domainIntervals(domain.getAcceptedIntervals());
    AlbaNumberIntervals const& rangeIntervals(range.getAcceptedIntervals());
    if (domainIntervals.size() == 1 && rangeIntervals.size() == 1) {
        result = domainIntervals.front() == createAllRealValuesInterval() &&
                 rangeIntervals.front() == createAllRealValuesInterval();
    }
    return result;
}

}  // namespace alba::algebra::DomainAndRange
