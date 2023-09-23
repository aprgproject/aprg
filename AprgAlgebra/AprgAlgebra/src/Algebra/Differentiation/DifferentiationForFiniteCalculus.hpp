#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class DifferentiationForFiniteCalculus {
public:
    explicit DifferentiationForFiniteCalculus(std::string const& nameOfVariableToDifferentiate);
    explicit DifferentiationForFiniteCalculus(std::string&& nameOfVariableToDifferentiate);
    [[nodiscard]] Equation differentiate(Equation const& equation) const;
    [[nodiscard]] Equation differentiateMultipleTimes(Equation const& equation, int const numberOfTimes) const;
    [[nodiscard]] Equation differentiateEquation(Equation const& equation) const;
    [[nodiscard]] Polynomial differentiateVariable(Variable const& variable) const;
    [[nodiscard]] Term differentiate(Term const& term) const;
    [[nodiscard]] Term differentiate(Variable const& variable) const;
    [[nodiscard]] Term differentiate(Monomial const& monomial) const;
    [[nodiscard]] Term differentiate(Polynomial const& polynomial) const;
    [[nodiscard]] Term differentiate(Expression const& expression) const;
    [[nodiscard]] Term differentiate(Function const& functionObject) const;
    [[nodiscard]] Term differentiateMultipleTimes(Term const& term, int const numberOfTimes) const;
    [[nodiscard]] Term differentiateTerm(Term const& term) const;
    [[nodiscard]] Term differentiateMonomial(Monomial const& monomial) const;
    [[nodiscard]] Term differentiatePolynomial(Polynomial const& polynomial) const;
    [[nodiscard]] Term differentiateExpression(Expression const& expression) const;
    [[nodiscard]] Term differentiateFunction(Function const& functionObject) const;
    static AlbaNumber differentiateConstant(Constant const&);
    static Term differentiate(Constant const& constant);

private:
    [[nodiscard]] bool isVariableToDifferentiate(std::string const& variableName) const;
    std::string m_nameOfVariableToDifferentiate;
};

}  // namespace alba::algebra
