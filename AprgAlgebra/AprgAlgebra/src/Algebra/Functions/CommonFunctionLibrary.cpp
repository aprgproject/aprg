#include "CommonFunctionLibrary.hpp"

#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra::Functions {

Function abs(Term const& term) {
    return {"abs", term, [](AlbaNumber const& number) -> AlbaNumber { return getAbsoluteValue(number); }};
}

Function greatestIntegerFunction(Term const& term) {
    return {"greatestIntegerFunction", term, [](AlbaNumber const& number) -> AlbaNumber {
                return {ceil(number.getDouble())};
            }};
}

Function sgn(Term const& term) {
    return {"sgn", term, [](AlbaNumber const& number) -> AlbaNumber {
                AlbaNumber result;
                if (number > 0) {
                    result = 1;
                } else if (number < 0) {
                    result = -1;
                }
                return result;
            }};
}

Function factorial(Term const& term) {
    return {"factorial", term, [](AlbaNumber const& number) -> AlbaNumber {
                AlbaNumber result;
                if (number.isIntegerType() && number >= 0) {
                    result = AlbaNumber(getFactorial(static_cast<int>(number.getInteger())));
                }
                return result;
            }};
}

Function ln(Term const& term) {
    return {"ln", term, [](AlbaNumber const& number) -> AlbaNumber { return ::log(number.getDouble()); }};
}

Function log(Term const& term) {
    return {"log", term, [](AlbaNumber const& number) -> AlbaNumber { return ::log10(number.getDouble()); }};
}

Function harmonicNumber(Term const& term) {
    return {"harmonicNumber", term, [](AlbaNumber const& number) -> AlbaNumber {
                AlbaNumber result;
                if ((number.getInteger() != 0) && number > 0) {
                    int const lastNumber = static_cast<int>(number.getInteger());
                    for (int i = 1; i <= lastNumber; ++i) {
                        result = result + AlbaNumber::createFraction(1, i);
                    }
                }
                return result;
            }};
}

Function sin(Term const& term) {
    return {"sin", term, [](AlbaNumber const& number) -> AlbaNumber { return ::sin(number.getDouble()); }};
}

Function cos(Term const& term) {
    return {"cos", term, [](AlbaNumber const& number) -> AlbaNumber { return ::cos(number.getDouble()); }};
}

Function tan(Term const& term) {
    return {"tan", term, [](AlbaNumber const& number) -> AlbaNumber { return ::tan(number.getDouble()); }};
}

Function csc(Term const& term) {
    return {"csc", term, [](AlbaNumber const& number) -> AlbaNumber { return 1 / ::sin(number.getDouble()); }};
}

Function sec(Term const& term) {
    return {"sec", term, [](AlbaNumber const& number) -> AlbaNumber { return 1 / ::cos(number.getDouble()); }};
}

Function cot(Term const& term) {
    return {"cot", term, [](AlbaNumber const& number) -> AlbaNumber { return 1 / ::tan(number.getDouble()); }};
}

Function arcsin(Term const& term) {
    return {"arcsin", term, [](AlbaNumber const& number) -> AlbaNumber { return ::asin(number.getDouble()); }};
}

Function arccos(Term const& term) {
    return {"arccos", term, [](AlbaNumber const& number) -> AlbaNumber { return ::acos(number.getDouble()); }};
}

Function arctan(Term const& term) {
    return {"arctan", term, [](AlbaNumber const& number) -> AlbaNumber { return ::atan(number.getDouble()); }};
}

Function arccsc(Term const& term) {
    return {"arccsc", term, [](AlbaNumber const& number) -> AlbaNumber { return ::asin(1 / number.getDouble()); }};
}

Function arcsec(Term const& term) {
    return {"arcsec", term, [](AlbaNumber const& number) -> AlbaNumber { return ::acos(1 / number.getDouble()); }};
}

Function arccot(Term const& term) {
    return {"arccot", term, [](AlbaNumber const& number) -> AlbaNumber { return ::atan(1 / number.getDouble()); }};
}

Function sinh(Term const& term) {
    return {"sinh", term, [](AlbaNumber const& number) -> AlbaNumber { return ::sinh(number.getDouble()); }};
}

Function cosh(Term const& term) {
    return {"cosh", term, [](AlbaNumber const& number) -> AlbaNumber { return ::cosh(number.getDouble()); }};
}

Function tanh(Term const& term) {
    return {"tanh", term, [](AlbaNumber const& number) -> AlbaNumber { return ::tanh(number.getDouble()); }};
}

Function csch(Term const& term) {
    return {"csch", term, [](AlbaNumber const& number) -> AlbaNumber { return 1 / ::sinh(number.getDouble()); }};
}

Function sech(Term const& term) {
    return {"sech", term, [](AlbaNumber const& number) -> AlbaNumber { return 1 / ::cosh(number.getDouble()); }};
}

Function coth(Term const& term) {
    return {"coth", term, [](AlbaNumber const& number) -> AlbaNumber {
                return ::cosh(number.getDouble()) / ::sinh(number.getDouble());
            }};
}

Function arcsinh(Term const& term) {
    return {"arcsinh", term, [](AlbaNumber const& number) -> AlbaNumber { return ::asinh(number.getDouble()); }};
}

Function arccosh(Term const& term) {
    return {"arccosh", term, [](AlbaNumber const& number) -> AlbaNumber { return ::acosh(number.getDouble()); }};
}

Function arctanh(Term const& term) {
    return {"arctanh", term, [](AlbaNumber const& number) -> AlbaNumber { return ::atanh(number.getDouble()); }};
}

Function arccsch(Term const& term) {
    return {"arccsch", term, [](AlbaNumber const& number) -> AlbaNumber { return ::asinh(1 / number.getDouble()); }};
}

Function arcsech(Term const& term) {
    return {"arcsech", term, [](AlbaNumber const& number) -> AlbaNumber { return ::acos(1 / number.getDouble()); }};
}

Function arccoth(Term const& term) {
    return {"arccoth", term, [](AlbaNumber const& number) -> AlbaNumber { return ::atanh(1 / number.getDouble()); }};
}

Function sinHarmonic(
    Term const& term, AlbaNumber const& amplitude, AlbaNumber const& period, AlbaNumber const& phaseDifference) {
    AlbaNumber const amplitudeCopy(amplitude);
    AlbaNumber const periodCopy(period);
    AlbaNumber const phaseDifferenceCopy(phaseDifference);
    return {"sinHarmonic", term, [=](AlbaNumber const& number) -> AlbaNumber {
                return amplitudeCopy * ::sin((periodCopy * number + phaseDifferenceCopy).getDouble());
            }};
}

}  // namespace alba::algebra::Functions
