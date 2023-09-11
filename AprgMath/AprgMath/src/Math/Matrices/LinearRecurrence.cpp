#include "LinearRecurrence.hpp"

using namespace alba::matrix;
using namespace std;

namespace alba::math {

UnsignedIntegerPair getNextFibonacciNumbersUsingLinearRecurrence(UnsignedIntegerPair const integerPair) {
    // Linear recurrence: f(n) = f(n-1) + f(n-2)
    // Matrix representation:
    // |f(n-1)|f(n)  |
    // |f(n)  |f(n+1)|
    UnsignedIntegerMatrix const formulaicTransform(2U, 2U, {0U, 1U, 1U, 1U});

    UnsignedIntegerMatrix const input(1U, 2U, {integerPair.first, integerPair.second});

    UnsignedIntegerMatrix const output = formulaicTransform * input;

    return UnsignedIntegerPair{output.getEntry(0U, 0U), output.getEntry(0U, 1U)};
}

UnsignedIntegerPair getNextNumberOfDerangementsUsingLinearRecurrence(
    UnsignedInteger const nthValue, UnsignedIntegerPair const integerPair) {
    // Linear recurrence: f(n) = (n-1)*(f(n-1)+f(n-2))
    UnsignedIntegerMatrix output(2U, 2U);

    if (nthValue > 0) {
        UnsignedIntegerMatrix const formulaicTransform(2U, 2U, {0U, 1, nthValue - 1, nthValue - 1});

        UnsignedIntegerMatrix const input(1U, 2U, {integerPair.first, integerPair.second});

        output = formulaicTransform * input;
    }
    return UnsignedIntegerPair{output.getEntry(0U, 0U), output.getEntry(0U, 1U)};
}

}  // namespace alba::math
