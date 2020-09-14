#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>
#include <string>

namespace alba
{
namespace algebra
{

using VariablesToExpressionsMap = std::map<std::string, Expression>;
using VariableExpressionPair = std::pair<std::string, Expression>;

class SubstitutionOfVariablesToExpressions
{
public:
    SubstitutionOfVariablesToExpressions();
    SubstitutionOfVariablesToExpressions(std::initializer_list<VariableExpressionPair> const& variablesWithExpressions);
    SubstitutionOfVariablesToExpressions(VariablesToExpressionsMap const& variablesWithExpressions);

    bool isEmpty() const;
    bool isVariableFound(std::string const& variable) const;
    unsigned int getSize() const;
    Expression getExpressionForVariable(std::string const& variable) const;
    Term performSubstitutionTo(Variable const& variable) const;    Term performSubstitutionTo(Monomial const& monomial) const;
    Term performSubstitutionTo(Polynomial const& polynomial) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Function const& functionAsParameter) const;
    Term performSubstitutionTo(Term const& term) const;
    Equation performSubstitutionTo(Equation const& equation) const;

    void putVariablesWithExpressions(std::initializer_list<VariableExpressionPair> const& variablesWithExpressions);
    void putVariablesWithExpressions(VariablesToExpressionsMap const& variablesWithExpressions);    void putVariableWithExpression(std::string const& variable, Expression const& expression);

private:
    Expression performSubstitutionForMonomial(Monomial const& monomial) const;
    Expression performSubstitutionForPolynomial(Polynomial const& polynomial) const;
    Expression performSubstitutionForExpression(Expression const& expression) const;
    Function performSubstitutionForFunction(Function const& functionAsParameter) const;
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const;
    VariablesToExpressionsMap m_variableToExpressionsMap;
};

}

}
