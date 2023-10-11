#include "ReduceEquationsBySubstitution.hpp"

#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Retrieval/SingleVariableNameRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>

#include <algorithm>

using namespace std;

namespace alba::algebra {

void reduceEquationsBySubstitution(Equations& substitutedEquations, VariableNamesSet const& variableNamesToIgnore) {
    VariableNamesRetriever unknownsRetriever;
    unknownsRetriever.retrieveFromEquations(substitutedEquations);
    bool areVariableAndEquationSelected(true);
    while (areVariableAndEquationSelected && unknownsRetriever.getVariableNames().size() > 1) {
        areVariableAndEquationSelected = false;
        string selectedVariableName;
        int selectedEquationIndex(0);
        selectVariableNameAndEquationNumber(
            areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex, substitutedEquations,
            variableNamesToIgnore);
        substituteEquationForSelectedEquationIndex(
            substitutedEquations, areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex);
        removeEquationsWithoutUnknowns(substitutedEquations);
        unknownsRetriever.getVariableNamesReference().clear();
        unknownsRetriever.retrieveFromEquations(substitutedEquations);
    }
}

void selectVariableNameAndEquationNumber(
    bool& areVariableAndEquationSelected, string& selectedVariableName, int& selectedEquationIndex,
    Equations const& equations, VariableNamesSet const& variableNamesToIgnore) {
    areVariableAndEquationSelected = false;
    selectedVariableName.clear();
    selectedEquationIndex = 0;
    VariableNamesSet const variableNamesToCheck(getVariablesNamesToCheck(equations, variableNamesToIgnore));
    int equationIndex = 0;
    for (Equation const& equation : equations) {
        IsolationOfOneVariableOnEqualityEquation const isolation(equation);
        auto it = find_if(variableNamesToCheck.cbegin(), variableNamesToCheck.cend(), [&](string const& variableName) {
            return isolation.canBeIsolated(variableName) &&
                   isolation.getIdenticalExponentForVariableIfPossible(variableName) == 1;
        });
        bool const canBePutOnOneSide = it != variableNamesToCheck.cend();
        if (canBePutOnOneSide) {
            areVariableAndEquationSelected = true;
            selectedVariableName = *it;
            selectedEquationIndex = equationIndex;
        }
        ++equationIndex;
    }
}

void substituteEquationForSelectedEquationIndex(
    Equations& substitutedEquations, bool const areVariableAndEquationSelected, string const& selectedVariableName,
    int const selectedEquationIndex) {
    if (areVariableAndEquationSelected) {
        IsolationOfOneVariableOnEqualityEquation const isolation(substitutedEquations[selectedEquationIndex]);
        substitutedEquations.erase(substitutedEquations.begin() + selectedEquationIndex);
        SubstitutionOfVariablesToTerms substitution;
        substitution.putVariableWithTerm(
            selectedVariableName, isolation.getEquivalentTermByIsolatingAVariable(selectedVariableName));
        for_each(substitutedEquations.begin(), substitutedEquations.end(), [&](Equation& substitutedEquation) {
            substitutedEquation = substitution.performSubstitutionTo(substitutedEquation);
        });
    }
}

void removeEquationsWithoutUnknowns(Equations& substitutedEquations) {
    substitutedEquations.erase(
        remove_if(
            substitutedEquations.begin(), substitutedEquations.end(),
            [](Equation const& equation) { return hasNoVariables(equation); }),
        substitutedEquations.end());
}

VariableNamesSet getVariablesNamesToCheck(Equations const& equations, VariableNamesSet const& variableNamesToIgnore) {
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromEquations(equations);
    VariableNamesSet variableNamesToCheck(variableNamesRetriever.getVariableNames());
    for (string const& variableNameToIgnore : variableNamesToIgnore) {
        variableNamesToCheck.erase(variableNameToIgnore);
    }
    return variableNamesToCheck;
}

}  // namespace alba::algebra
