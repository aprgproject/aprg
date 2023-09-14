#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba::algebra {

class ExpressionAndFunctionsRetriever final : public BaseRetriever {
public:
    void retrieveFromPolynomial(Polynomial const&) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
    [[nodiscard]] TermSet const& getExpressionsAndFunctions() const;

private:
    TermSet m_expressionsAndFunctions;
};

}  // namespace alba::algebra
