#include "MultipleVariableSolutionSet.hpp"

#include <algorithm>
#include <sstream>

using namespace std;

namespace alba::algebra {

SolutionSet MultipleVariableSolutionSet::getSolutionSetForVariable(string const& variableName) const {
    SolutionSet result;
    auto it = m_variableNameToSolutionSetMap.find(variableName);
    if (it != m_variableNameToSolutionSetMap.cend()) {
        result = it->second;
    }
    return result;
}

MultipleVariableSolutionSet::VariableNameToSolutionSetMap const&
MultipleVariableSolutionSet::getVariableNameToSolutionSetMap() const {
    return m_variableNameToSolutionSetMap;
}

VariableNamesSet MultipleVariableSolutionSet::getVariableNames() const {
    VariableNamesSet result;
    for (auto const& [variableName, solutionSet] : m_variableNameToSolutionSetMap) {
        result.emplace(variableName);
    }
    return result;
}

int MultipleVariableSolutionSet::getNumberOfVariablesWithSolutions() const {
    return static_cast<int>(m_variableNameToSolutionSetMap.size());
}

bool MultipleVariableSolutionSet::isValueAcceptedForVariable(
    string const& variableName, AlbaNumber const& value) const {
    SolutionSet const solutionSet(getSolutionSetForVariable(variableName));
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    return find(acceptedValues.cbegin(), acceptedValues.cend(), value) != acceptedValues.cend();
}

void MultipleVariableSolutionSet::addSolutionSetForVariable(
    string const& variableName, SolutionSet const& solutionSet) {
    m_variableNameToSolutionSetMap[variableName] = solutionSet;
}

ostream& operator<<(ostream& out, MultipleVariableSolutionSet const& solutionSet) {
    for (auto const& pair : solutionSet.m_variableNameToSolutionSetMap) {
        out << "Variable:{" << pair.first << "} SolutionSet:{" << pair.second << "}\n";
    }
    return out;
}

}  // namespace alba::algebra
