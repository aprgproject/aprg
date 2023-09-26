#include "Variable.hpp"

#include <ostream>

using namespace std;

namespace alba::algebra {

Variable::Variable(string const& variableName) : m_variableName(variableName) {}
Variable::Variable(string&& variableName) : m_variableName(variableName) {}
bool Variable::operator==(Variable const& second) const { return m_variableName == second.m_variableName; }
bool Variable::operator!=(Variable const& second) const { return m_variableName != second.m_variableName; }
bool Variable::operator<(Variable const& second) const { return m_variableName < second.m_variableName; }
string Variable::getVariableName() const { return m_variableName; }
void Variable::setVariableName(string const& variableName) { m_variableName = variableName; }

ostream& operator<<(ostream& out, Variable const& variable) {
    out << variable.m_variableName;
    return out;
}

}  // namespace alba::algebra
