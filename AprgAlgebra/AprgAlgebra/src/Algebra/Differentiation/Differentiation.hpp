#pragma once

#include <Algebra/Differentiation/DerivativeVariableName.hpp>
#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba::algebra {

class Differentiation {
public:
    explicit Differentiation(std::string const& nameOfVariableToDifferentiate);
    explicit Differentiation(std::string&& nameOfVariableToDifferentiate);

    Differentiation(
        std::string const& nameOfVariableToDifferentiate, VariableNamesSet const& namesOfDependentVariables);

    Differentiation(std::string&& nameOfVariableToDifferentiate, VariableNamesSet&& namesOfDependentVariables);
    [[nodiscard]] Equation differentiate(Equation const& equation) const;
    [[nodiscard]] Equation differentiateMultipleTimes(Equation const& equation, int const numberOfTimes) const;
    [[nodiscard]] Equation differentiateEquation(Equation const& equation) const;
    [[nodiscard]] Monomial differentiateVariable(Variable const& variable) const;
    [[nodiscard]] Polynomial differentiateMonomial(Monomial const& monomial) const;
    [[nodiscard]] Polynomial differentiatePolynomial(Polynomial const& polynomial) const;
    [[nodiscard]] Term differentiate(Term const& term) const;
    [[nodiscard]] Term differentiate(Variable const& variable) const;
    [[nodiscard]] Term differentiate(Monomial const& monomial) const;
    [[nodiscard]] Term differentiate(Polynomial const& polynomial) const;
    [[nodiscard]] Term differentiate(Expression const& expression) const;
    [[nodiscard]] Term differentiate(Function const& functionObject) const;
    [[nodiscard]] Term differentiateWithDefiniteValue(Term const& term, AlbaNumber const& value) const;
    [[nodiscard]] Term differentiateMultipleTimes(Term const& term, int const numberOfTimes) const;
    [[nodiscard]] Term differentiateExpression(Expression const& expression) const;
    [[nodiscard]] Term differentiateFunction(Function const& functionObject) const;
    [[nodiscard]] Term differentiateTwoMultipliedTerms(Term const& term1, Term const& term2) const;
    [[nodiscard]] Term differentiateTwoDividedTerms(Term const& numerator, Term const& denominator) const;
    static AlbaNumber differentiateConstant(Constant const&);
    static Term differentiate(Constant const& constant);

private:
    [[nodiscard]] Polynomial differentiateMonomialWithChangingVariables(Monomial const& changingVariables) const;
    [[nodiscard]] Term differentiateAsTermOrExpressionIfNeeded(Expression const& expression) const;
    [[nodiscard]] Term differentiateSimplifiedExpressionOnly(Expression const& expression) const;
    [[nodiscard]] Term differentiateTermsInAdditionOrSubtraction(Expression const& expression) const;
    [[nodiscard]] Term differentiateTermsInMultiplicationOrDivision(Expression const& expression) const;
    [[nodiscard]] Term differentiateByProcessingAsPolynomialsOverPolynomials(Term const& term) const;

    [[nodiscard]] Term differentiateTermsInMultiplicationOrDivisionTermByTerm(
        TermsWithDetails const& termsWithDetails) const;

    [[nodiscard]] Term differentiateTermsInRaiseToPower(Expression const& expression) const;
    [[nodiscard]] Term differentiateNonChangingTermRaiseToChangingTerm(Term const& base, Term const& exponent) const;
    [[nodiscard]] Term differentiateChangingTermRaiseToNonChangingTerm(Term const& base, Term const& exponent) const;
    [[nodiscard]] bool isVariableToDifferentiate(std::string const& variableName) const;
    [[nodiscard]] bool isDependentVariable(std::string const& variableName) const;

    [[nodiscard]] bool isDerivativeVariableNameAndAffectedByThisDifferentiation(
        DerivativeVariableName const& derivativeVariable) const;

    [[nodiscard]] bool isChangingVariableName(std::string const& variableName) const;
    [[nodiscard]] bool isChangingTerm(Term const& term) const;

    void separateNonChangingAndChangingVariables(
        Monomial& nonChangingVariablesAndConstant, Monomial& changingVariables, Monomial const& monomial) const;

    static Term differentiateChangingTermRaiseToChangingTerm(Term const& firstTerm, Term const& secondTerm);
    static Term differentiateFunctionOnly(Function const& functionObject);
    std::string m_nameOfVariableToDifferentiate;
    VariableNamesSet m_namesOfDependentVariables;
};

}  // namespace alba::algebra
