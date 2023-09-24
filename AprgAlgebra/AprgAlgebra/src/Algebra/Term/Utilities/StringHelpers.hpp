#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba::algebra {

void addValueTermIfNotEmpty(Terms& terms, std::string const& valueString);
Term buildTermIfPossible(std::string const& termString);
Terms tokenizeToTerms(std::string const& inputString);
std::string getOperatingString(OperatorLevel const operatorLevel, TermAssociationType const association);

std::string getFirstStringIfNegativeAssociation(
    OperatorLevel const operatorLevel, TermAssociationType const association);

std::string createVariableNameForSubstitution(Term const& term);
int getOperatorPriority(std::string const& operatorString);
bool isOperator(std::string const& stringObject);
bool isFunction(std::string const& stringObject);

}  // namespace alba::algebra
