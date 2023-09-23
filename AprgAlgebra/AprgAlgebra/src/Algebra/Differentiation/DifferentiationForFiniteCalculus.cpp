#include "DifferentiationForFiniteCalculus.hpp"

#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba::algebra {

DifferentiationForFiniteCalculus::DifferentiationForFiniteCalculus(string const& nameOfVariableToDifferentiate)
    : m_nameOfVariableToDifferentiate(nameOfVariableToDifferentiate) {}

DifferentiationForFiniteCalculus::DifferentiationForFiniteCalculus(string&& nameOfVariableToDifferentiate)
    : m_nameOfVariableToDifferentiate(nameOfVariableToDifferentiate) {}

Equation DifferentiationForFiniteCalculus::differentiate(Equation const& equation) const {
    return differentiateEquation(equation);
}

Equation DifferentiationForFiniteCalculus::differentiateMultipleTimes(
    Equation const& equation, int const numberOfTimes) const {
    Equation currentResult(equation);
    for (int i = 0; i < numberOfTimes; ++i) {
        currentResult = differentiate(currentResult);
    }
    return currentResult;
}

Equation DifferentiationForFiniteCalculus::differentiateEquation(Equation const& equation) const {
    Equation result(
        differentiate(equation.getLeftHandTerm()), equation.getEquationOperator().getOperatorString(),
        differentiate(equation.getRightHandTerm()));
    result.simplify();
    return result;
}

Polynomial DifferentiationForFiniteCalculus::differentiateVariable(Variable const& variable) const {
    Polynomial result(createPolynomialFromNumber(0));
    if (isVariableToDifferentiate(variable.getVariableName())) {
        result = Polynomial{Monomial(1, {{m_nameOfVariableToDifferentiate, 1}}), Monomial(1, {})};
    }
    return result;
}

Term DifferentiationForFiniteCalculus::differentiate(Term const& term) const { return differentiateTerm(term); }

Term DifferentiationForFiniteCalculus::differentiate(Variable const& variable) const {
    Term result(differentiateVariable(variable));
    result.simplify();
    return result;
}

Term DifferentiationForFiniteCalculus::differentiate(Monomial const& monomial) const {
    Term result(differentiateMonomial(monomial));
    result.simplify();
    return result;
}

Term DifferentiationForFiniteCalculus::differentiate(Polynomial const& polynomial) const {
    Term result(differentiatePolynomial(polynomial));
    result.simplify();
    return result;
}

Term DifferentiationForFiniteCalculus::differentiate(Expression const& expression) const {
    return differentiateExpression(expression);
}

Term DifferentiationForFiniteCalculus::differentiate(Function const& functionObject) const {
    return differentiateFunction(functionObject);
}

Term DifferentiationForFiniteCalculus::differentiateMultipleTimes(Term const& term, int const numberOfTimes) const {
    Term currentResult(term);
    for (int i = 0; i < numberOfTimes; ++i) {
        currentResult = differentiate(currentResult);
    }
    return currentResult;
}

Term DifferentiationForFiniteCalculus::differentiateTerm(Term const& term) const {
    Term result;
    if (term.isConstant()) {
        result = differentiate(term.getAsConstant());
    } else if (term.isVariable()) {
        result = differentiate(term.getAsVariable());
    } else if (term.isMonomial()) {
        result = differentiate(term.getAsMonomial());
    } else if (term.isPolynomial()) {
        result = differentiate(term.getAsPolynomial());
    } else if (term.isExpression()) {
        result = differentiate(term.getAsExpression());
    } else if (term.isFunction()) {
        result = differentiate(term.getAsFunction());
    }
    return result;
}

Term DifferentiationForFiniteCalculus::differentiateMonomial(Monomial const& monomial) const {
    return {getDerivativeDefinitionForFiniteCalculus(Term(monomial), m_nameOfVariableToDifferentiate)};
}

Term DifferentiationForFiniteCalculus::differentiatePolynomial(Polynomial const& polynomial) const {
    return {getDerivativeDefinitionForFiniteCalculus(Term(polynomial), m_nameOfVariableToDifferentiate)};
}

Term DifferentiationForFiniteCalculus::differentiateExpression(Expression const& expression) const {
    return {getDerivativeDefinitionForFiniteCalculus(Term(expression), m_nameOfVariableToDifferentiate)};
}

Term DifferentiationForFiniteCalculus::differentiateFunction(Function const& functionObject) const {
    return {getDerivativeDefinitionForFiniteCalculus(Term(functionObject), m_nameOfVariableToDifferentiate)};
}

AlbaNumber DifferentiationForFiniteCalculus::differentiateConstant(Constant const&) { return 0; }

Term DifferentiationForFiniteCalculus::differentiate(Constant const& constant) {
    return {differentiateConstant(constant)};
}

bool DifferentiationForFiniteCalculus::isVariableToDifferentiate(string const& variableName) const {
    return variableName == m_nameOfVariableToDifferentiate;
}

}  // namespace alba::algebra
