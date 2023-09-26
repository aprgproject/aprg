#include "SubTermsRetriever.hpp"

namespace alba::algebra {

void SubTermsRetriever::retrieveFromConstant(Constant const& constant) { m_subTerms.emplace(Term(constant)); }
void SubTermsRetriever::retrieveFromVariable(Variable const& variable) { m_subTerms.emplace(Term(variable)); }
void SubTermsRetriever::retrieveFromMonomial(Monomial const& monomial) { m_subTerms.emplace(Term(monomial)); }
void SubTermsRetriever::retrieveFromPolynomial(Polynomial const& polynomial) { m_subTerms.emplace(Term(polynomial)); }

void SubTermsRetriever::retrieveFromExpression(Expression const& expression) {
    m_subTerms.emplace(Term(expression));
    BaseRetriever::retrieveFromExpression(expression);
}

void SubTermsRetriever::retrieveFromFunction(Function const& functionObject) {
    m_subTerms.emplace(Term(functionObject));
    BaseRetriever::retrieveFromFunction(functionObject);
}

TermSet const& SubTermsRetriever::getSubTerms() const { return m_subTerms; }

}  // namespace alba::algebra
