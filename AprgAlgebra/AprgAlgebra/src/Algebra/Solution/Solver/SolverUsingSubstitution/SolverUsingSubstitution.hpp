#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/MultipleVariableSolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

namespace alba::algebra {

class SolverUsingSubstitution : public BaseSolver {
public:
    SolverUsingSubstitution();
    MultipleVariableSolutionSets calculateSolutionAndReturnSolutionSet(Equations const& equations);

private:
    [[nodiscard]] bool isTheValueAlreadyExisting(std::string const& variableName, AlbaNumber const& value) const;
    void clear();
    void calculateSolutions(Equations const& equations);

    void calculateASolutionForAllVariables(
        MultipleVariableSolutionSet& multipleVariableSolutionSet, Equations const& equations);

    void addIfSolutionIsCompleteAndCorrect(MultipleVariableSolutionSet const& solutionSet, Equations const& equations);

    void calculateASolutionForOneVariable(
        MultipleVariableSolutionSet& multipleVariableSolutionSet, Equations const& equations);

    void solveForTheFirstOneVariableEquationAndUpdate(
        MultipleVariableSolutionSet& multipleVariableSolutionSet, Equations const& substitutedEquations);

    void solveAndUpdate(
        MultipleVariableSolutionSet& solutionSet, Equation const& equationToSolve,
        std::string const& variableNameToSolve);

    static void substituteSolutionSetValuesToEquations(
        Equations& substitutedEquations, MultipleVariableSolutionSet const& multipleVariableSolutionSet);

    static SubstitutionOfVariablesToValues getSubstitutionFromSolutionSet(
        MultipleVariableSolutionSet const& solutionSet);

    static bool isSolutionCorrect(MultipleVariableSolutionSet const& solutionSet, Equations const& equations);
    MultipleVariableSolutionSets m_solutionsWithAllVariables;
    MultipleVariableSolutionSets m_solutionsWithSomeVariables;
    VariableNamesSet m_variablesNames;
};

}  // namespace alba::algebra
