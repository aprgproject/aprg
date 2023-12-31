#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <string>

namespace alba::algebra::Functions {

AlbaNumberPairs evaluateAndGetInputOutputPair(
    AlbaNumbers const& numbers, std::string const& variableName, Function const& functionObject);

Term getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term const& term);
bool isFunctionContinuous(Function const& functionObject);
bool isTrigonometricFunction(Function const& functionObject);
bool isInverseTrigonometricFunction(Function const& functionObject);
bool isLogarithmicFunction(Function const& functionObject);
bool isFunctionNameFoundOnAList(Function const& functionObject, stringHelper::strings const& names);

}  // namespace alba::algebra::Functions
