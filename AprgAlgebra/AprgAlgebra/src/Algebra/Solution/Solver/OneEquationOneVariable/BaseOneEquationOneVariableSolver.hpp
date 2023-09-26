#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba::algebra {

class BaseOneEquationOneVariableSolver : public BaseSolver {
public:
    BaseOneEquationOneVariableSolver() = default;
    // virtual destructor because of virtual functions (vtable exists)
    virtual ~BaseOneEquationOneVariableSolver() = default;
    BaseOneEquationOneVariableSolver(BaseOneEquationOneVariableSolver const&) = default;
    BaseOneEquationOneVariableSolver(BaseOneEquationOneVariableSolver&&) noexcept = default;
    BaseOneEquationOneVariableSolver& operator=(BaseOneEquationOneVariableSolver const&) = default;
    BaseOneEquationOneVariableSolver& operator=(BaseOneEquationOneVariableSolver&&) noexcept = default;
    SolutionSet calculateSolutionAndReturnSolutionSet(Equation const& equation);

protected:
    virtual void calculateSolution(SolutionSet& solutionSet, Equation const& equation) = 0;
    virtual void calculateForEquation(SolutionSet& solutionSet, Equation const& equation) = 0;
    virtual void calculateForTermAndVariable(Term const& term, std::string const& variableName) = 0;
    void processWhenEquationIsAlwaysSatisfied(SolutionSet& solutionSet);
    void calculateWhenEquationIsSometimesSatisfied(SolutionSet& solutionSet, Equation const& equation);
    void sortAndRemoveDuplicateCalculatedValues();

    void calculateForTermAndCheckAbsoluteValueFunctions(
        Term const& nonZeroLeftHandTerm, std::string const& variableName);

    void calculateAndSubstituteAbsoluteValueFunctions(
        FunctionsSet const& absFunctions, Term const& term, std::string const& variableName);

    AlbaNumbers m_calculatedValues;
};

}  // namespace alba::algebra
