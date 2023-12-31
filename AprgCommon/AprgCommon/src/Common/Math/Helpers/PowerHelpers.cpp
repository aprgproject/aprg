#include "PowerHelpers.hpp"

using namespace std;

namespace alba::mathHelper {

bool isPerfectSquare(AlbaNumber const& value) { return isPerfectNthPower(value, 2); }
bool isPerfectCube(AlbaNumber const& value) { return isPerfectNthPower(value, 3); }

bool isPerfectNthPower(AlbaNumber const& number, size_t const nthPower) {
    bool result(false);

    if (number.isIntegerType()) {
        auto integerValue(static_cast<int64_t>(number.getInteger()));
        result = integerValue >= 0 && isPerfectNthPower(static_cast<size_t>(integerValue), nthPower);
    } else if (number.isFractionType()) {
        AlbaNumber::FractionData const fractionData(number.getFractionData());
        result = fractionData.numerator >= 0 &&
                 isPerfectNthPower(static_cast<size_t>(fractionData.numerator), nthPower) &&
                 isPerfectNthPower(fractionData.denominator, nthPower);
    }
    return result;
}

}  // namespace alba::mathHelper
