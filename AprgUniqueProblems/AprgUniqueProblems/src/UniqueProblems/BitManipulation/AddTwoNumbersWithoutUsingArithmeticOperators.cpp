#include "AddTwoNumbersWithoutUsingArithmeticOperators.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>

using namespace std;

namespace alba {

AddTwoNumbersWithoutUsingArithmeticOperators::Value AddTwoNumbersWithoutUsingArithmeticOperators::getSum(
    Value const value1, Value const value2) {
    Value carry = value1 & value2;
    Value sum = value1 ^ value2;
    while (carry > 0) {
        carry <<= 1;
        int const newCarry = static_cast<int>(sum & carry);
        sum = sum ^ carry;
        carry = newCarry;
    }
    return sum;
}

}  // namespace alba
