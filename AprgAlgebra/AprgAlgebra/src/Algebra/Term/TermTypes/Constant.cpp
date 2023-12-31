#include "Constant.hpp"

#include <sstream>

using namespace std;

namespace alba::algebra {

Constant::Constant(AlbaNumber const& constantValue) : m_constantValue(constantValue) {}
bool Constant::operator==(Constant const& second) const { return m_constantValue == second.m_constantValue; }
bool Constant::operator!=(Constant const& second) const { return m_constantValue != second.m_constantValue; }
bool Constant::operator<(Constant const& second) const { return m_constantValue < second.m_constantValue; }
AlbaNumber const& Constant::getNumber() const { return m_constantValue; }
void Constant::setNumber(AlbaNumber const& constantValue) { m_constantValue = constantValue; }

ostream& operator<<(ostream& out, Constant const& constant) {
    out << constant.m_constantValue;
    return out;
}

}  // namespace alba::algebra
