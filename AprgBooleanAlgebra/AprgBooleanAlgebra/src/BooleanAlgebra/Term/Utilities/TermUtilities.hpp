#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>
#include <BooleanAlgebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba::booleanAlgebra {
Term getTermFromVariableAndPrimeValue(std::string const& variableName, char const primeValue);
VariableNamesSet getVariableNames(Term const& term);
bool isNonEmptyOrNonOperatorType(Term const& term);
bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term);
bool getNoEffectValueInOperation(OperatorLevel const operatorLevel);
bool getShortCircuitValueEffectInOperation(OperatorLevel const operatorLevel);
}  // namespace alba::booleanAlgebra
