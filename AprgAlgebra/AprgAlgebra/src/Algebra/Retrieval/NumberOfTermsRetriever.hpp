#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>

namespace alba::algebra {

class NumberOfTermsRetriever final : public BaseRetriever {
public:
    NumberOfTermsRetriever() = default;
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
    [[nodiscard]] int getNumberOfTerms() const;

private:
    int m_numberOfTerms{};
};

}  // namespace alba::algebra
