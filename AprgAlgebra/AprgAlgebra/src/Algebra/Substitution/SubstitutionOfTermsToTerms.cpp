#include "SubstitutionOfTermsToTerms.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>

using namespace std;

namespace alba::algebra {

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms(TermToTermMap const& variablesWithValues) {
    putTermsToTermsMapping(variablesWithValues);
}

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms(initializer_list<TermTermPair> const& variablesWithValues) {
    putTermsToTermsMapping(variablesWithValues);
}

Equation SubstitutionOfTermsToTerms::performSubstitutionTo(Equation const& equation) const {
    Equation simplifiedEquation(
        performSubstitutionTo(equation.getLeftHandTerm()), equation.getEquationOperator().getOperatorString(),
        performSubstitutionTo(equation.getRightHandTerm()));
    simplifiedEquation.simplify();
    return simplifiedEquation;
}

Expression SubstitutionOfTermsToTerms::performSubstitutionForExpression(Expression const& expression) const {
    Expression newExpression(expression);
    performSubstitutionForTermsWithAssociation(newExpression.getTermsWithAssociationReference());
    newExpression.simplify();
    return newExpression;
}

Function SubstitutionOfTermsToTerms::performSubstitutionForFunction(Function const& functionObject) const {
    Function newFunction(functionObject);
    getTermReferenceFromBaseTerm(newFunction.getInputTermReference()) =
        performSubstitutionTo(getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
    newFunction.simplify();
    return newFunction;
}

Term SubstitutionOfTermsToTerms::getTermForTerm(Term const& term) const {
    Term result;
    if (isTermFound(term)) {
        result = m_termsToTermsMap.at(term);
    }
    return result;
}

Term SubstitutionOfTermsToTerms::performSubstitutionTo(Expression const& expression) const {
    Term result;
    Term const expressionTerm(expression);
    if (isTermFound(expressionTerm)) {
        result = getTermForTerm(expressionTerm);
    } else {
        result = simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
    }
    return result;
}

Term SubstitutionOfTermsToTerms::performSubstitutionTo(Function const& functionObject) const {
    Term result;
    Term const functionTerm(functionObject);
    if (isTermFound(functionTerm)) {
        result = getTermForTerm(functionTerm);
    } else {
        result = simplifyAndConvertFunctionToSimplestTerm(performSubstitutionForFunction(functionObject));
    }
    return result;
}

Term SubstitutionOfTermsToTerms::performSubstitutionTo(Term const& term) const {
    Term newTerm(term);
    if (isTermFound(term)) {
        newTerm = getTermForTerm(term);
    } else if (term.isExpression()) {
        newTerm = performSubstitutionTo(term.getAsExpression());
    } else if (term.isFunction()) {
        newTerm = performSubstitutionTo(term.getAsFunction());
    }
    return newTerm;
}

int SubstitutionOfTermsToTerms::getSize() const { return static_cast<int>(m_termsToTermsMap.size()); }
bool SubstitutionOfTermsToTerms::isEmpty() const { return m_termsToTermsMap.empty(); }

bool SubstitutionOfTermsToTerms::isTermFound(Term const& term) const {
    return m_termsToTermsMap.find(term) != m_termsToTermsMap.cend();
}

void SubstitutionOfTermsToTerms::putTermsToTermsMapping(initializer_list<TermTermPair> const& variablesWithValues) {
    for (auto const& [variable, value] : variablesWithValues) {
        putTermToTermMapping(variable, value);
    }
}

void SubstitutionOfTermsToTerms::putTermsToTermsMapping(TermToTermMap const& variablesWithValues) {
    for (auto const& [variable, value] : variablesWithValues) {
        putTermToTermMapping(variable, value);
    }
}

void SubstitutionOfTermsToTerms::putTermToTermMapping(Term const& term1, Term const& term2) {
    m_termsToTermsMap[term1] = term2;
}

void SubstitutionOfTermsToTerms::performSubstitutionForTermsWithAssociation(
    TermsWithAssociation& termsWithAssociation) const {
    for (TermWithDetails& termWithDetails : termsWithAssociation.getTermsWithDetailsReference()) {
        Term& term(getTermReferenceFromUniquePointer(termWithDetails.baseTermPointer));
        term = performSubstitutionTo(term);
    }
}

}  // namespace alba::algebra
