#include "SegregateTermsByConditionInAdditionAndSubtractionRetriever.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace std;

namespace alba::algebra {

SegregateTermsByConditionInAdditionAndSubtractionRetriever::SegregateTermsByConditionInAdditionAndSubtractionRetriever(
    ConditionFunction const& condition)
    : m_condition(condition) {}

SegregateTermsByConditionInAdditionAndSubtractionRetriever::SegregateTermsByConditionInAdditionAndSubtractionRetriever(
    ConditionFunction&& condition)
    : m_condition(condition) {}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromConstant(Constant const& constant) {
    saveTerm(Term(constant));
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromVariable(Variable const& variable) {
    saveTerm(Term(variable));
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromMonomial(Monomial const& monomial) {
    saveTerm(Term(monomial));
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromExpression(Expression const& expression) {
    if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
        for (TermWithDetails const& termWithDetails : expression.getTermsWithAssociation().getTermsWithDetails()) {
            if (termWithDetails.hasPositiveAssociation()) {
                retrieveFromTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
            } else {
                retrieveFromTerm(negateTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer)));
            }
        }
    } else {
        saveTerm(Term(expression));
    }
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromFunction(Function const& functionObject) {
    saveTerm(Term(functionObject));
}

Term const& SegregateTermsByConditionInAdditionAndSubtractionRetriever::getTermWithCondition() const {
    return m_termWithCondition;
}

Term const& SegregateTermsByConditionInAdditionAndSubtractionRetriever::getTermWithoutCondition() const {
    return m_termWithoutCondition;
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::saveTerm(Term const& term) {
    if (m_condition(term)) {
        m_termWithCondition += term;
    } else {
        m_termWithoutCondition += term;
    }
}

}  // namespace alba::algebra
