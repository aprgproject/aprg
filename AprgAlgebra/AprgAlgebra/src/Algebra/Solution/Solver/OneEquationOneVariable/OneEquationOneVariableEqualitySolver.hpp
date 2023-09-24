#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Solution/Solver/NewtonMethod.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/BaseOneEquationOneVariableSolver.hpp>

namespace alba::algebra {

class OneEquationOneVariableEqualitySolver : public BaseOneEquationOneVariableSolver {
public:
    OneEquationOneVariableEqualitySolver();

private:
    void calculateSolution(SolutionSet& solutionSet, Equation const& equation) override;
    void calculateForEquation(SolutionSet& solutionSet, Equation const& equation) override;
    void calculateForTermAndVariable(Term const& term, std::string const& variableName) override;
    void addValuesToSolutionSetIfNeeded(SolutionSet& solutionSet, Term const& term, std::string const& variableName);
    void performNewtonMethodToFindSolution(Term const& termToCheck, std::string const& variableNameForSubstitution);

    static AlbaNumber getMoreAccurateValueFromNewtonMethod(
        Term const& termToCheck, std::string const& variableNameForSubstitution, AlbaNumber const& value);

    static NewtonMethod::Function getFunctionToIterate(
        Term const& termToCheck, std::string const& variableNameForSubstitution);
};

}  // namespace alba::algebra
