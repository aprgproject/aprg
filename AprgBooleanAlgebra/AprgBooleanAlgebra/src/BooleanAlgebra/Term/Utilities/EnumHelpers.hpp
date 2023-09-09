#pragma once

#include <BooleanAlgebra/Term/TermTypes/OperatorLevel.hpp>
#include <BooleanAlgebra/Term/TermTypes/OperatorType.hpp>
#include <BooleanAlgebra/Term/TermTypes/TermType.hpp>

#include <string>

namespace alba::booleanAlgebra {
OperatorLevel getDualOperatorLevel(OperatorLevel const operatorLevel);
std::string getEnumShortString(TermType const termType);
std::string getEnumShortString(OperatorType const operatorType);
std::string getEnumShortString(OperatorLevel const operatorLevel);
int getOperatorTypeInversePriority(OperatorType const operatorType);
int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
int getTermTypePriorityValue(TermType const termType);
}  // namespace alba::booleanAlgebra
