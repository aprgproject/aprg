#include "FunctionUtilities.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra::Functions {

AlbaNumberPairs evaluateAndGetInputOutputPair(
    AlbaNumbers const& numbers, string const& variableName, Function const& functionObject) {
    AlbaNumberPairs result;
    SubstitutionOfVariablesToValues substitution;
    for (AlbaNumber const& number : numbers) {
        substitution.putVariableWithValue(variableName, number);
        Term const substituteTerm(substitution.performSubstitutionTo(functionObject));
        if (substituteTerm.isConstant()) {
            result.emplace_back(number, substituteTerm.getAsNumber());
        }
    }
    return result;
}

Term getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term const& term) { return ln(abs(term)); }

bool isFunctionContinuous(Function const& functionObject) {
    strings const continuousFunctionNames{"abs", "sin", "cos"};
    return isFunctionNameFoundOnAList(functionObject, continuousFunctionNames);
}

bool isTrigonometricFunction(Function const& functionObject) {
    strings const continuousFunctionNames{"sin", "cos", "tan", "csc", "sec", "cot"};
    return isFunctionNameFoundOnAList(functionObject, continuousFunctionNames);
}

bool isInverseTrigonometricFunction(Function const& functionObject) {
    strings const continuousFunctionNames{"arcsin", "arccos", "arctan", "arccsc", "arcsec", "arccot"};
    return isFunctionNameFoundOnAList(functionObject, continuousFunctionNames);
}

bool isLogarithmicFunction(Function const& functionObject) {
    strings const continuousFunctionNames{"ln", "log"};
    return isFunctionNameFoundOnAList(functionObject, continuousFunctionNames);
}

bool isFunctionNameFoundOnAList(Function const& functionObject, strings const& names) {
    return any_of(
        names.cbegin(), names.cend(), [&](string const& name) { return name == functionObject.getFunctionName(); });
}

}  // namespace alba::algebra::Functions
