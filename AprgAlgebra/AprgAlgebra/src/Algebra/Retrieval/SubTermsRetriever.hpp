#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba::algebra {

class SubTermsRetriever final : public BaseRetriever {
public:
    SubTermsRetriever() = default;
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromPolynomial(Polynomial const& polynomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
    [[nodiscard]] TermSet const& getSubTerms() const;

private:
    TermSet m_subTerms;
};

}  // namespace alba::algebra
