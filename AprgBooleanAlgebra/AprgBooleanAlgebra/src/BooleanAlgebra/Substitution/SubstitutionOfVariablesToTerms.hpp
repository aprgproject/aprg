#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <map>
#include <vector>

namespace alba::booleanAlgebra {

using VariablesToTermsMap = std::map<std::string, Term>;
using VariableTermPair = std::pair<std::string, Term>;

class SubstitutionOfVariablesToTerms {
public:
    SubstitutionOfVariablesToTerms() = default;
    explicit SubstitutionOfVariablesToTerms(VariablesToTermsMap const& variablesWithTerms);
    SubstitutionOfVariablesToTerms(std::initializer_list<VariableTermPair> const& variablesWithTerms);
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isVariableFound(std::string const& variable) const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] Term getTermForVariable(std::string const& variable) const;
    [[nodiscard]] VariablesToTermsMap const& getVariablesToTermsMap() const;
    [[nodiscard]] Term performSubstitutionTo(VariableTerm const& variableTerm) const;
    [[nodiscard]] Term performSubstitutionTo(Expression const& expression) const;
    [[nodiscard]] Term performSubstitutionTo(Term const& term) const;
    [[nodiscard]] Expression performSubstitutionForExpression(Expression const& expression) const;
    void putVariablesWithTerms(std::initializer_list<VariableTermPair> const& variablesWithTerms);
    void putVariablesWithTerms(VariablesToTermsMap const& variablesWithTerms);
    void putVariableWithTerm(std::string const& variable, Term const& term);

private:
    void performSubstitutionForWrappedTerms(WrappedTerms& wrappedTerms) const;
    VariablesToTermsMap m_variableToTermsMap;
};

using SubstitutionsOfVariablesToTerms = std::vector<SubstitutionOfVariablesToTerms>;

}  // namespace alba::booleanAlgebra
