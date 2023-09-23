#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <functional>

namespace alba::algebra {

class FunctionsRetriever final : public BaseRetriever {
public:
    using FunctionCondition = std::function<bool(Function const&)>;
    explicit FunctionsRetriever(FunctionCondition const& isFunctionIncluded);
    explicit FunctionsRetriever(FunctionCondition&& isFunctionIncluded);
    void retrieveFromPolynomial(Polynomial const&) override;
    void retrieveFromFunction(Function const& functionObject) override;
    [[nodiscard]] FunctionsSet const& getFunctions() const;

private:
    FunctionCondition m_isFunctionIncluded;
    FunctionsSet m_functions;
};

}  // namespace alba::algebra
