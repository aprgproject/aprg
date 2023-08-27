#include "CPlusPlusVariable.hpp"

namespace codeReview {

CPlusPlusVariable::CPlusPlusVariable() {}

CPlusPlusVariable::CPlusPlusVariable(CPlusPlusType const& cPlusPlusType) : m_type(cPlusPlusType) {}

CPlusPlusType CPlusPlusVariable::getType() const { return m_type; }

}  // namespace codeReview
