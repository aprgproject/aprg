#pragma once

#include <cstdint>

namespace alba {

class AddTwoNumbersWithoutUsingArithmeticOperators {
public:
    using Value = uint64_t;
    AddTwoNumbersWithoutUsingArithmeticOperators() = default;
    static Value getSum(Value const value1, Value const value2);
};

}  // namespace alba

// Write a function Add() that returns sum of two integers.
// The function should not use any of the arithmetic operators (+, ++, –, -, .. etc).
