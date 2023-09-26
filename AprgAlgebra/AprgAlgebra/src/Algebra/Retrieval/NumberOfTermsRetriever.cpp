#include "NumberOfTermsRetriever.hpp"

namespace alba::algebra {

void NumberOfTermsRetriever::retrieveFromExpression(Expression const& expression) {
    ++m_numberOfTerms;
    BaseRetriever::retrieveFromExpression(expression);
}

void NumberOfTermsRetriever::retrieveFromFunction(Function const& functionObject) {
    ++m_numberOfTerms;
    BaseRetriever::retrieveFromFunction(functionObject);
}

int NumberOfTermsRetriever::getNumberOfTerms() const { return m_numberOfTerms; }
void NumberOfTermsRetriever::retrieveFromConstant(Constant const&) { ++m_numberOfTerms; }
void NumberOfTermsRetriever::retrieveFromVariable(Variable const&) { ++m_numberOfTerms; }
void NumberOfTermsRetriever::retrieveFromMonomial(Monomial const&) { ++m_numberOfTerms; }

}  // namespace alba::algebra
