#include "VariableNamesRetriever.hpp"

namespace alba::booleanAlgebra {

void VariableNamesRetriever::retrieveFromVariableTerm(VariableTerm const& variableTerm) {
    m_savedData.emplace(variableTerm.getVariableTermName());
}

}  // namespace alba
