#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

using VariablesToValuesMap = std::map<std::string, AlbaNumber>;
using VariableValuePair = std::pair<std::string, AlbaNumber>;

class SubstitutionOfVariablesToValues {
public:
    SubstitutionOfVariablesToValues();
    explicit SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues);
    SubstitutionOfVariablesToValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    [[nodiscard]] AlbaNumber getValueForVariable(std::string const& variable) const;
    [[nodiscard]] Equation performSubstitutionTo(Equation const& equation) const;
    [[nodiscard]] Expression performSubstitutionForExpression(Expression const& expression) const;
    [[nodiscard]] Function performSubstitutionForFunction(Function const& functionObject) const;
    [[nodiscard]] Monomial performSubstitutionForMonomial(Monomial const& monomial) const;
    [[nodiscard]] Polynomial performSubstitutionForPolynomial(Polynomial const& polynomial) const;
    [[nodiscard]] Term performSubstitutionTo(Variable const& variable) const;
    [[nodiscard]] Term performSubstitutionTo(Monomial const& monomial) const;
    [[nodiscard]] Term performSubstitutionTo(Polynomial const& polynomial) const;
    [[nodiscard]] Term performSubstitutionTo(Expression const& expression) const;
    [[nodiscard]] Term performSubstitutionTo(Function const& functionObject) const;
    [[nodiscard]] Term performSubstitutionTo(Term const& term) const;
    [[nodiscard]] VariablesToValuesMap const& getVariableToValuesMap() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isVariableFound(std::string const& variable) const;
    void putVariablesWithValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    void putVariablesWithValues(VariablesToValuesMap const& variablesWithValues);
    void putVariableWithValue(std::string const& variable, AlbaNumber const& value);

private:
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation& termsWithAssociation) const;
    VariablesToValuesMap m_variableToValuesMap;
};

using SubstitutionsOfVariablesToValues = std::vector<SubstitutionOfVariablesToValues>;

}  // namespace alba::algebra
