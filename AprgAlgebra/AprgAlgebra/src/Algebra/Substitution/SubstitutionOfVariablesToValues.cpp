#include "SubstitutionOfVariablesToValues.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba::algebra {

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues) {
    putVariablesWithValues(variablesWithValues);
}

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues(
    initializer_list<VariableValuePair> const& variablesWithValues) {
    putVariablesWithValues(variablesWithValues);
}

AlbaNumber SubstitutionOfVariablesToValues::getValueForVariable(string const& variable) const {
    AlbaNumber result;
    if (isVariableFound(variable)) {
        result = m_variableToValuesMap.at(variable);
    }
    return result;
}

Equation SubstitutionOfVariablesToValues::performSubstitutionTo(Equation const& equation) const {
    Equation simplifiedEquation(
        performSubstitutionTo(equation.getLeftHandTerm()), equation.getEquationOperator().getOperatorString(),
        performSubstitutionTo(equation.getRightHandTerm()));
    simplifiedEquation.simplify();
    return simplifiedEquation;
}

Expression SubstitutionOfVariablesToValues::performSubstitutionForExpression(Expression const& expression) const {
    Expression newExpression(expression);
    performSubstitutionForTermsWithAssociation(newExpression.getTermsWithAssociationReference());
    newExpression.simplify();
    return newExpression;
}

Function SubstitutionOfVariablesToValues::performSubstitutionForFunction(Function const& functionObject) const {
    Function newFunction(functionObject);
    getTermReferenceFromBaseTerm(newFunction.getInputTermReference()) =
        performSubstitutionTo(getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
    newFunction.simplify();
    return newFunction;
}

Monomial SubstitutionOfVariablesToValues::performSubstitutionForMonomial(Monomial const& monomial) const {
    Monomial newMonomial(createMonomialFromNumber(monomial.getCoefficient()));
    Monomial::VariablesToExponentsMap const& previousVariableExponentMap(monomial.getVariablesToExponentsMap());
    for (auto const& [variableName, exponent] : previousVariableExponentMap) {
        if (isVariableFound(variableName)) {
            newMonomial.setConstant(newMonomial.getCoefficient() * (getValueForVariable(variableName) ^ exponent));
        } else {
            newMonomial.putVariableWithExponent(variableName, exponent);
        }
    }
    newMonomial.simplify();
    return newMonomial;
}

Polynomial SubstitutionOfVariablesToValues::performSubstitutionForPolynomial(Polynomial const& polynomial) const {
    Polynomial newPolynomial;
    for (Monomial const& monomial : polynomial.getMonomials()) {
        newPolynomial.addMonomial(performSubstitutionForMonomial(monomial));
    }
    newPolynomial.simplify();
    return newPolynomial;
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Variable const& variable) const {
    Term result;
    string const variableName(variable.getVariableName());
    if (isVariableFound(variableName)) {
        result = Term(getValueForVariable(variableName));
    } else {
        result = Term(variable);
    }
    return result;
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Monomial const& monomial) const {
    return simplifyAndConvertMonomialToSimplestTerm(performSubstitutionForMonomial(monomial));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Polynomial const& polynomial) const {
    return simplifyAndConvertPolynomialToSimplestTerm(performSubstitutionForPolynomial(polynomial));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Expression const& expression) const {
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Function const& functionObject) const {
    return simplifyAndConvertFunctionToSimplestTerm(performSubstitutionForFunction(functionObject));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Term const& term) const {
    Term newTerm(term);
    if (term.isVariable()) {
        newTerm = performSubstitutionTo(term.getAsVariable());
    } else if (term.isMonomial()) {
        newTerm = performSubstitutionTo(term.getAsMonomial());
    } else if (term.isPolynomial()) {
        newTerm = performSubstitutionTo(term.getAsPolynomial());
    } else if (term.isExpression()) {
        newTerm = performSubstitutionTo(term.getAsExpression());
    } else if (term.isFunction()) {
        newTerm = performSubstitutionTo(term.getAsFunction());
    }
    return newTerm;
}

VariablesToValuesMap const& SubstitutionOfVariablesToValues::getVariableToValuesMap() const {
    return m_variableToValuesMap;
}

int SubstitutionOfVariablesToValues::getSize() const { return static_cast<int>(m_variableToValuesMap.size()); }
bool SubstitutionOfVariablesToValues::isEmpty() const { return m_variableToValuesMap.empty(); }

bool SubstitutionOfVariablesToValues::isVariableFound(string const& variable) const {
    return m_variableToValuesMap.find(variable) != m_variableToValuesMap.cend();
}

void SubstitutionOfVariablesToValues::putVariablesWithValues(
    initializer_list<VariableValuePair> const& variablesWithValues) {
    for (auto const& [variable, value] : variablesWithValues) {
        putVariableWithValue(variable, value);
    }
}

void SubstitutionOfVariablesToValues::putVariablesWithValues(VariablesToValuesMap const& variablesWithValues) {
    for (auto const& [variable, value] : variablesWithValues) {
        putVariableWithValue(variable, value);
    }
}

void SubstitutionOfVariablesToValues::putVariableWithValue(string const& variable, AlbaNumber const& value) {
    m_variableToValuesMap[variable] = value;
}

void SubstitutionOfVariablesToValues::performSubstitutionForTermsWithAssociation(
    TermsWithAssociation& termsWithAssociation) const {
    for (TermWithDetails& termWithDetails : termsWithAssociation.getTermsWithDetailsReference()) {
        Term& term(getTermReferenceFromUniquePointer(termWithDetails.baseTermPointer));
        term = performSubstitutionTo(term);
    }
}

}  // namespace alba::algebra
