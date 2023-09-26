#pragma once

#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <map>
#include <vector>

namespace alba::algebra {

class MultipleVariableSolutionSet {
public:
    using VariableNameToSolutionSetMap = std::map<std::string, SolutionSet>;
    using VariableNameToSolutionSetPair = std::pair<std::string, SolutionSet>;
    MultipleVariableSolutionSet() = default;
    [[nodiscard]] SolutionSet getSolutionSetForVariable(std::string const& variableName) const;
    [[nodiscard]] VariableNameToSolutionSetMap const& getVariableNameToSolutionSetMap() const;
    [[nodiscard]] VariableNamesSet getVariableNames() const;
    [[nodiscard]] int getNumberOfVariablesWithSolutions() const;
    [[nodiscard]] bool isValueAcceptedForVariable(std::string const& variableName, AlbaNumber const& value) const;
    void addSolutionSetForVariable(std::string const& variableName, SolutionSet const& solutionSet);

private:
    friend std::ostream& operator<<(std::ostream& out, MultipleVariableSolutionSet const& solutionSet);
    VariableNameToSolutionSetMap m_variableNameToSolutionSetMap;
};

using MultipleVariableSolutionSets = std::vector<MultipleVariableSolutionSet>;

}  // namespace alba::algebra
