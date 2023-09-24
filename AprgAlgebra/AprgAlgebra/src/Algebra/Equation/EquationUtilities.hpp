#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Equation/EquationOperator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::algebra {

void segregateEquationsWithAndWithoutVariable(
    Equations const& equationsToSegregate, std::string const& variableName, Equations& equationsWithVariable,
    Equations& equationsWithoutVariable);

AlbaNumber getDegree(Equation const& equation);
Equation buildEquationIfPossible(std::string const& equationString);

Term getEquivalentTermByReducingItToAVariable(
    std::string const& variableName, Term const& termWithVariable, Term const& termWithWithoutVariable);

std::string getEquationOperatorCharacters();
std::string getReverseEquationOperatorString(std::string const& equationOperatorString);
bool isEquationOperatorString(std::string const& stringToCheck);
bool isEquationOperatorCharacterString(std::string const& stringToCheck);

bool doesNegativeVariableSubstitutionYieldsToTheSameEquation(
    Equation const& equation, stringHelper::strings const& variableNames);

bool isSymmetricAlongXAxis(Equation const& equation);
bool isSymmetricAlongYAxis(Equation const& equation);
bool isSymmetricOnOrigin(Equation const& equation);
bool isEqual(Term const& leftTerm, Term const& rightTerm);
bool isNotEqual(Term const& leftTerm, Term const& rightTerm);
bool isLessThan(Term const& leftTerm, Term const& rightTerm);
bool isGreaterThan(Term const& leftTerm, Term const& rightTerm);
bool isLessThanOrEqual(Term const& leftTerm, Term const& rightTerm);
bool isGreaterThanOrEqual(Term const& leftTerm, Term const& rightTerm);
bool isEquationOperationSatisfied(EquationOperator const& operatorObject, Term const& leftTerm, Term const& rightTerm);
bool doesAllEquationsHaveEqualityOperator(Equations const& equations);

}  // namespace alba::algebra
