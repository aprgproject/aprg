#include "SubstitutionOfVariablesToTerms.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba::booleanAlgebra {

SubstitutionOfVariablesToTerms::SubstitutionOfVariablesToTerms(VariablesToTermsMap const& variablesWithTerms) {
    putVariablesWithTerms(variablesWithTerms);
}

SubstitutionOfVariablesToTerms::SubstitutionOfVariablesToTerms(
    initializer_list<VariableTermPair> const& variablesWithTerms) {
    putVariablesWithTerms(variablesWithTerms);
}

Expression SubstitutionOfVariablesToTerms::performSubstitutionForExpression(Expression const& expression) const {
    Expression newExpression(expression);
    performSubstitutionForWrappedTerms(newExpression.getWrappedTermsReference());
    return newExpression;
}

Term SubstitutionOfVariablesToTerms::getTermForVariable(string const& variable) const {
    Term result;
    if (isVariableFound(variable)) {
        result = m_variableToTermsMap.at(variable);
    }
    return result;
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(VariableTerm const& variableTerm) const {
    Term result;
    string const variableName(variableTerm.getVariableTermName());
    if (isVariableFound(variableName)) {
        result = getTermForVariable(variableName);
    } else {
        result = Term(variableTerm);
    }
    if (variableTerm.isNegated()) {
        result.negate();
    }
    result.simplify();
    return result;
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Expression const& expression) const {
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Term const& term) const {
    Term newTerm(term);
    if (term.isVariableTerm()) {
        newTerm = performSubstitutionTo(term.getVariableTermConstReference());
    } else if (term.isExpression()) {
        newTerm = performSubstitutionTo(term.getExpressionConstReference());
    }
    return newTerm;
}

VariablesToTermsMap const& SubstitutionOfVariablesToTerms::getVariablesToTermsMap() const {
    return m_variableToTermsMap;
}

int SubstitutionOfVariablesToTerms::getSize() const { return static_cast<int>(m_variableToTermsMap.size()); }
bool SubstitutionOfVariablesToTerms::isEmpty() const { return m_variableToTermsMap.empty(); }

bool SubstitutionOfVariablesToTerms::isVariableFound(string const& variable) const {
    return m_variableToTermsMap.find(variable) != m_variableToTermsMap.cend();
}

void SubstitutionOfVariablesToTerms::putVariablesWithTerms(
    initializer_list<VariableTermPair> const& variablesWithTerms) {
    for (auto const& [variableName, value] : variablesWithTerms) {
        putVariableWithTerm(variableName, value);
    }
}

void SubstitutionOfVariablesToTerms::putVariablesWithTerms(VariablesToTermsMap const& variablesWithTerms) {
    for (auto const& [variableName, value] : variablesWithTerms) {
        putVariableWithTerm(variableName, value);
    }
}

void SubstitutionOfVariablesToTerms::putVariableWithTerm(string const& variable, Term const& term) {
    m_variableToTermsMap[variable] = term;
    m_variableToTermsMap[variable].simplify();
}

void SubstitutionOfVariablesToTerms::performSubstitutionForWrappedTerms(WrappedTerms& wrappedTerms) const {
    for (WrappedTerm& wrappedTerm : wrappedTerms) {
        Term& term(getTermReferenceFromUniquePointer(wrappedTerm.baseTermPointer));
        term = performSubstitutionTo(term);
    }
}

}  // namespace alba::booleanAlgebra
