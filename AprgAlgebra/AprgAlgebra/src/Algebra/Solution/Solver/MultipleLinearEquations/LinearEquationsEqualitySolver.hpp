#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/MultipleVariableSolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Algebra/Utilities/NumberMatrix.hpp>

namespace alba::algebra {

class LinearEquationsEqualitySolver : public BaseSolver {
public:
    LinearEquationsEqualitySolver();
    MultipleVariableSolutionSet calculateSolutionAndReturnSolutionSet(Equations const& equations);
    MultipleVariableSolutionSet calculateSolutionAndReturnSolutionSet(Polynomials const& polynomials);

private:
    static bool areExponentsEqualToOneAndZero(AlbaNumbersSet const& exponents);
    static void setMatrixCoefficients(
        NumberMatrix& coefficientsMatrix, VariableNamesSet const& variableNames, Polynomials const& polynomials);

    static void saveSolutionSetsFromTheCoefficientMatrix(
        MultipleVariableSolutionSet& solutionSet, NumberMatrix const& coefficientsMatrix,
        VariableNamesSet const& variables);

    void calculateSolution(MultipleVariableSolutionSet& solutionSet, Equations const& equations);
    void calculateSolution(MultipleVariableSolutionSet& solutionSet, Polynomials const& polynomials);
};

}  // namespace alba::algebra
