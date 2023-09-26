#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/BaseOneEquationOneVariableSolver.hpp>

namespace alba::algebra {

class OneEquationOneVariableNonEqualitySolver : public BaseOneEquationOneVariableSolver {
public:
    OneEquationOneVariableNonEqualitySolver() = default;

private:
    void calculateSolution(SolutionSet& solutionSet, Equation const& equation) override;
    void calculateForEquation(SolutionSet& solutionSet, Equation const& equation) override;
    void calculateForTermAndVariable(Term const& term, std::string const&) override;

    void addIntervalsToSolutionSetIfNeeded(
        SolutionSet& solutionSet, Equation const& equation, std::string const& variableName);
};

}  // namespace alba::algebra
