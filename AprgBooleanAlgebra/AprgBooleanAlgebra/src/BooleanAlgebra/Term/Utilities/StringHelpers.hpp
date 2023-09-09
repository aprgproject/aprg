#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba::booleanAlgebra {
void addValueTermIfNotEmpty(Terms& terms, std::string const& valueString);
Term buildTermIfPossible(std::string const& termString);
Terms tokenizeToTerms(std::string const& inputString);
std::string getString(OperatorType const operatorType);
std::string getString(OperatorLevel const operatorLevel);
std::string getString(WrappedTerms const& wrappedTerms);
std::string createVariableTermNameForSubstitution(Term const& term);
int getOperatorPriority(std::string const& operatorString);
bool isConstant(std::string const& stringObject);
bool isOperator(std::string const& stringObject);
bool isPrime(char const character);
}  // namespace alba::booleanAlgebra
