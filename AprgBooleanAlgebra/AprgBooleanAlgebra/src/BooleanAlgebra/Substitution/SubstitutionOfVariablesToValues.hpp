#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <map>

namespace alba::booleanAlgebra {

using VariablesToValuesMap = std::map<std::string, bool>;
using VariableValuePair = std::pair<std::string, bool>;

class SubstitutionOfVariablesToValues {
public:
    SubstitutionOfVariablesToValues() = default;
    explicit SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues);
    SubstitutionOfVariablesToValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    [[nodiscard]] Expression performSubstitutionForExpression(Expression const& expression) const;
    [[nodiscard]] Term performSubstitutionTo(VariableTerm const& variableTerm) const;
    [[nodiscard]] Term performSubstitutionTo(Expression const& expression) const;
    [[nodiscard]] Term performSubstitutionTo(Term const& term) const;
    [[nodiscard]] VariablesToValuesMap const& getVariableToValuesMap() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isVariableFound(std::string const& variable) const;
    [[nodiscard]] bool getValueForVariable(std::string const& variable) const;
    void putVariablesWithValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    void putVariablesWithValues(VariablesToValuesMap const& variablesWithValues);
    void putVariableWithValue(std::string const& variable, bool const value);

private:
    void performSubstitutionForWrappedTerms(WrappedTerms& wrappedTerms) const;
    VariablesToValuesMap m_variableToValuesMap;
};

using SubstitutionsOfVariablesToValues = std::vector<SubstitutionOfVariablesToValues>;

}  // namespace alba::booleanAlgebra
