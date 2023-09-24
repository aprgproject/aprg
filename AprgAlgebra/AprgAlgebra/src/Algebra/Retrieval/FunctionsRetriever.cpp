#include "FunctionsRetriever.hpp"

namespace alba::algebra {

FunctionsRetriever::FunctionsRetriever(FunctionCondition const& isFunctionIncluded)
    : m_isFunctionIncluded(isFunctionIncluded) {}

FunctionsRetriever::FunctionsRetriever(FunctionCondition&& isFunctionIncluded)
    : m_isFunctionIncluded(isFunctionIncluded) {}

void FunctionsRetriever::retrieveFromPolynomial(Polynomial const&) {}

void FunctionsRetriever::retrieveFromFunction(Function const& functionObject) {
    if (m_isFunctionIncluded(functionObject)) {
        m_functions.emplace(functionObject);
    }
}

FunctionsSet const& FunctionsRetriever::getFunctions() const { return m_functions; }

}  // namespace alba::algebra
