#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba::algebra {

void reduceEquationsBySubstitution(Equations& substitutedEquations, VariableNamesSet const& variableNamesToIgnore);

void selectVariableNameAndEquationNumber(
    bool& areVariableAndEquationSelected, std::string& selectedVariableName, int& selectedEquationIndex,
    Equations const& equations, VariableNamesSet const& variableNamesToIgnore);

void substituteEquationForSelectedEquationIndex(
    Equations& substitutedEquations, bool const areVariableAndEquationSelected, std::string const& selectedVariableName,
    int const selectedEquationIndex);

void removeEquationsWithoutUnknowns(Equations& substitutedEquations);
VariableNamesSet getVariablesNamesToCheck(Equations const& equations, VariableNamesSet const& variableNamesToIgnore);

}  // namespace alba::algebra
