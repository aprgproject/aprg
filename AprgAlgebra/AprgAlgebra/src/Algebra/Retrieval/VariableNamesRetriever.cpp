#include "VariableNamesRetriever.hpp"

namespace alba::algebra {

void VariableNamesRetriever::retrieveFromVariable(Variable const& variable) {
    m_variableNames.emplace(variable.getVariableName());
}

void VariableNamesRetriever::retrieveFromMonomial(Monomial const& monomial) {
    for (auto const& [variableName, exponent] : monomial.getVariablesToExponentsMap()) {
        m_variableNames.emplace(variableName);
    }
}

VariableNamesSet const& VariableNamesRetriever::getVariableNames() const { return m_variableNames; }
VariableNamesSet& VariableNamesRetriever::getVariableNamesReference() { return m_variableNames; }

}  // namespace alba::algebra
