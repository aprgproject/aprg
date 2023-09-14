#include "ExpressionAndFunctionsRetriever.hpp"

namespace alba::algebra {

void ExpressionAndFunctionsRetriever::retrieveFromPolynomial(Polynomial const&) {}

void ExpressionAndFunctionsRetriever::retrieveFromExpression(Expression const& expression) {
    m_expressionsAndFunctions.emplace(Term(expression));
    BaseRetriever::retrieveFromExpression(expression);
}

void ExpressionAndFunctionsRetriever::retrieveFromFunction(Function const& functionObject) {
    m_expressionsAndFunctions.emplace(Term(functionObject));
    BaseRetriever::retrieveFromFunction(functionObject);
}

TermSet const& ExpressionAndFunctionsRetriever::getExpressionsAndFunctions() const { return m_expressionsAndFunctions; }

}  // namespace alba::algebra
