#include "IsolationOfOneVariableOnEqualityEquation.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba::algebra {

IsolationOfOneVariableOnEqualityEquation::IsolationOfOneVariableOnEqualityEquation(Equation const& equation) {
    setEquation(equation);
}

AlbaNumber IsolationOfOneVariableOnEqualityEquation::getIdenticalExponentForVariableIfPossible(
    string const& variableName) const {
    AlbaNumber exponent(0);
    if (canBeConvertedToPolynomial(m_simplifiedLeftSideTerm)) {
        Polynomial polynomial(createPolynomialIfPossible(m_simplifiedLeftSideTerm));
        exponent = getIdenticalExponentForVariableIfPossible(variableName, polynomial);
    }
    return exponent;
}

Equation IsolationOfOneVariableOnEqualityEquation::isolateTermWithVariableOnLeftSideOfEquation(
    string const& variableName) const {
    Term termWithVariable;
    Term termWithWithoutVariable;
    isolateTermWithVariable(variableName, termWithVariable, termWithWithoutVariable);
    return {termWithVariable, "=", termWithWithoutVariable};
}

Equation IsolationOfOneVariableOnEqualityEquation::isolateTermWithVariableOnRightSideOfEquation(
    string const& variableName) const {
    Term termWithVariable;
    Term termWithWithoutVariable;
    isolateTermWithVariable(variableName, termWithVariable, termWithWithoutVariable);
    return {termWithWithoutVariable, "=", termWithVariable};
}

Term IsolationOfOneVariableOnEqualityEquation::getEquivalentTermByIsolatingAVariable(string const& variableName) const {
    Term termWithVariable;
    Term termWithWithoutVariable;
    isolateTermWithVariable(variableName, termWithVariable, termWithWithoutVariable);
    return getEquivalentTermByReducingItToAVariable(variableName, termWithVariable, termWithWithoutVariable);
}

bool IsolationOfOneVariableOnEqualityEquation::canBeIsolated(string const& variableName) const {
    bool result(false);
    if (canBeConvertedToPolynomial(m_simplifiedLeftSideTerm)) {
        Polynomial polynomial(createPolynomialIfPossible(m_simplifiedLeftSideTerm));
        result = canBeIsolatedBasedOnExponent(getIdenticalExponentForVariableIfPossible(variableName, polynomial));
    }
    return result;
}

void IsolationOfOneVariableOnEqualityEquation::isolateTermWithVariable(
    string const& variableName, Term& termWithVariable, Term& termWithWithoutVariable) const {
    if (canBeConvertedToPolynomial(m_simplifiedLeftSideTerm)) {
        Polynomial polynomial(createPolynomialIfPossible(m_simplifiedLeftSideTerm));
        isolateTermWithVariable(variableName, polynomial, termWithVariable, termWithWithoutVariable);
    } else if (m_simplifiedLeftSideTerm.isExpression()) {
        Expression const& expression(m_simplifiedLeftSideTerm.getAsExpression());
        isolateTermWithVariable(variableName, expression, termWithVariable, termWithWithoutVariable);
    }
}

void IsolationOfOneVariableOnEqualityEquation::setEquation(Equation const& equation) {
    if (equation.getEquationOperator().isEqual()) {
        Equation simplifiedEquation(equation);
        simplifiedEquation.simplify();
        m_simplifiedLeftSideTerm = simplifiedEquation.getLeftHandTerm();
    }
}

void IsolationOfOneVariableOnEqualityEquation::isolateTermWithVariable(
    string const& variableName, Polynomial const& polynomial, Term& termWithVariable, Term& termWithWithoutVariable) {
    AlbaNumber identicalExponentForVariable(getIdenticalExponentForVariableIfPossible(variableName, polynomial));
    if (canBeIsolatedBasedOnExponent(identicalExponentForVariable)) {
        Monomials monomialsWithVariable;
        Monomials monomialsWithoutVariable;
        segregateMonomialsWithAndWithoutVariable(
            polynomial.getMonomials(), variableName, monomialsWithVariable, monomialsWithoutVariable);
        Polynomial numerator(monomialsWithoutVariable);
        Polynomial denominator(monomialsWithVariable);
        numerator.multiplyNumber(-1);
        Monomial monomialWithIsolatedVariable(1, {{variableName, identicalExponentForVariable}});
        denominator.divideMonomial(monomialWithIsolatedVariable);
        termWithVariable = monomialWithIsolatedVariable;
        termWithWithoutVariable = Term(numerator) / Term(denominator);
        termWithVariable.simplify();
        termWithWithoutVariable.simplify();
    }
}

void IsolationOfOneVariableOnEqualityEquation::isolateTermWithVariable(
    string const& variableName, Expression const& expression, Term& termWithVariable, Term& termWithWithoutVariable) {
    Expression simplifiedExpression(expression);
    simplifyForIsolation(simplifiedExpression);
    if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
        TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
        TermsWithDetails termsWithDetailsWithVariable;
        TermsWithDetails termsWithDetailsWithoutVariable;
        segregateTermsWithAndWithoutVariable(
            termsWithDetails, variableName, termsWithDetailsWithVariable, termsWithDetailsWithoutVariable);

        Term termFromExpressionWithVariable(
            createTermWithAdditionAndSubtractionTermsWithDetails(termsWithDetailsWithVariable));
        Term termFromExpressionWithoutVariable(
            createTermWithAdditionAndSubtractionTermsWithDetails(termsWithDetailsWithoutVariable));

        termFromExpressionWithVariable.simplify();
        if (canBeConvertedToPolynomial(termFromExpressionWithVariable)) {
            Polynomial polynomialWithVariable(createPolynomialIfPossible(termFromExpressionWithVariable));
            AlbaNumber identicalExponentForVariable(
                getIdenticalExponentForVariableIfPossible(variableName, polynomialWithVariable));
            Term termWithIsolatedVariable(Monomial(1, {{variableName, identicalExponentForVariable}}));
            Term numerator(negateTerm(termFromExpressionWithoutVariable));
            Term denominator(termFromExpressionWithVariable / termWithIsolatedVariable);
            termWithVariable = termWithIsolatedVariable;
            termWithWithoutVariable = numerator / denominator;
            termWithVariable.simplify();
            termWithWithoutVariable.simplify();
        }
    }
}

void IsolationOfOneVariableOnEqualityEquation::simplifyForIsolation(Term& term) {
    term.simplify();
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyToFactors = true;
        configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
        configurationDetails.shouldSimplifyToACommonDenominator = true;

        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        term.simplify();
    }
}

void IsolationOfOneVariableOnEqualityEquation::simplifyForIsolation(Expression& expression) {
    expression.simplify();
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyToFactors = false;
        configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
        configurationDetails.shouldSimplifyToACommonDenominator = true;

        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        expression.simplify();
    }
}

AlbaNumber IsolationOfOneVariableOnEqualityEquation::getIdenticalExponentForVariableIfPossible(
    string const& variableName, Polynomial const& polynomial) {
    AlbaNumber exponent;
    for (Monomial const& monomial : polynomial.getMonomials()) {
        AlbaNumber currentExponent = monomial.getExponentForVariable(variableName);
        if (currentExponent != 0) {
            if (exponent == 0) {
                exponent = currentExponent;
            } else if (exponent != currentExponent) {
                exponent = 0;
                break;
            }
        }
    }
    return exponent;
}

bool IsolationOfOneVariableOnEqualityEquation::canBeIsolatedBasedOnExponent(
    AlbaNumber const& identicalExponentForVariable) {
    return identicalExponentForVariable != 0;
}

}  // namespace alba::algebra
