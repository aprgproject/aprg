#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <vector>

namespace alba::algebra {

using VariablesToTermsMap = std::map<std::string, Term>;
using VariableTermPair = std::pair<std::string, Term>;

class SubstitutionOfVariablesToTerms {
public:
    SubstitutionOfVariablesToTerms() = default;
    explicit SubstitutionOfVariablesToTerms(VariablesToTermsMap const& variablesWithTerms);
    SubstitutionOfVariablesToTerms(std::initializer_list<VariableTermPair> const& variablesWithTerms);
    [[nodiscard]] Equation performSubstitutionTo(Equation const& equation) const;
    [[nodiscard]] Expression performSubstitutionForMonomial(Monomial const& monomial) const;
    [[nodiscard]] Expression performSubstitutionForPolynomial(Polynomial const& polynomial) const;
    [[nodiscard]] Expression performSubstitutionForExpression(Expression const& expression) const;
    [[nodiscard]] Function performSubstitutionForFunction(Function const& functionObject) const;
    [[nodiscard]] Term getTermForVariable(std::string const& variable) const;
    [[nodiscard]] Term performSubstitutionTo(Variable const& variable) const;
    [[nodiscard]] Term performSubstitutionTo(Monomial const& monomial) const;
    [[nodiscard]] Term performSubstitutionTo(Polynomial const& polynomial) const;
    [[nodiscard]] Term performSubstitutionTo(Expression const& expression) const;
    [[nodiscard]] Term performSubstitutionTo(Function const& functionObject) const;
    [[nodiscard]] Term performSubstitutionTo(Term const& term) const;
    [[nodiscard]] VariablesToTermsMap const& getVariablesToTermsMap() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isVariableFound(std::string const& variable) const;
    void putVariablesWithTerms(std::initializer_list<VariableTermPair> const& variablesWithTerms);
    void putVariablesWithTerms(VariablesToTermsMap const& variablesWithTerms);
    void putVariableWithTerm(std::string const& variable, Term const& term);

private:
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation& termsWithAssociation) const;
    VariablesToTermsMap m_variableToTermsMap;
};

using SubstitutionsOfVariablesToTerms = std::vector<SubstitutionOfVariablesToTerms>;

}  // namespace alba::algebra
