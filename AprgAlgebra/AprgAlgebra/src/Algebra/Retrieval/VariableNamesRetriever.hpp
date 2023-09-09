#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba::algebra {

class VariableNamesRetriever final : public BaseRetriever {
public:
    [[nodiscard]] VariableNamesSet const& getVariableNames() const;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    VariableNamesSet& getVariableNamesReference();

private:
    VariableNamesSet m_variableNames;
};

}  // namespace alba::algebra
