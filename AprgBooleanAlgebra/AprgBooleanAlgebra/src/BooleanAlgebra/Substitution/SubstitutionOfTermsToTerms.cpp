#include "SubstitutionOfTermsToTerms.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>

using namespace std;

namespace alba::booleanAlgebra {

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms(TermToTermMap const& variablesWithValues) {
    putTermsToTermsMapping(variablesWithValues);
}

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms(initializer_list<TermTermPair> const& variablesWithValues) {
    putTermsToTermsMapping(variablesWithValues);
}

Expression SubstitutionOfTermsToTerms::performSubstitutionForExpression(Expression const& expression) const {
    Expression newExpression(expression);
    performSubstitutionForWrappedTerms(newExpression.getWrappedTermsReference());
    newExpression.simplify();
    return newExpression;
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

Term SubstitutionOfTermsToTerms::performSubstitutionTo(Term const& term) const {
    Term newTerm(term);
    if (isTermFound(term)) {
        newTerm = getTermForTerm(term);
    } else if (term.isExpression()) {
        newTerm = performSubstitutionTo(term.getExpressionConstReference());
    }
    return newTerm;
}

int SubstitutionOfTermsToTerms::getSize() const { return static_cast<int>(m_termsToTermsMap.size()); }
bool SubstitutionOfTermsToTerms::isEmpty() const { return m_termsToTermsMap.empty(); }

bool SubstitutionOfTermsToTerms::isTermFound(Term const& term) const {
    return m_termsToTermsMap.find(term) != m_termsToTermsMap.cend();
}

void SubstitutionOfTermsToTerms::putTermsToTermsMapping(initializer_list<TermTermPair> const& variablesWithValues) {
    for (auto const& [variableName, value] : variablesWithValues) {
        putTermToTermMapping(variableName, value);
    }
}

void SubstitutionOfTermsToTerms::putTermsToTermsMapping(TermToTermMap const& variablesWithValues) {
    for (auto const& [variableName, value] : variablesWithValues) {
        putTermToTermMapping(variableName, value);
    }
}

void SubstitutionOfTermsToTerms::putTermToTermMapping(Term const& term1, Term const& term2) {
    m_termsToTermsMap[term1] = term2;
}

void SubstitutionOfTermsToTerms::performSubstitutionForWrappedTerms(WrappedTerms& wrappedTerms) const {
    for (WrappedTerm& wrappedTerm : wrappedTerms) {
        Term& term(getTermReferenceFromUniquePointer(wrappedTerm.baseTermPointer));
        term = performSubstitutionTo(term);
    }
}

}  // namespace alba::booleanAlgebra
