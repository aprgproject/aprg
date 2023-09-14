#pragma once

#include <limits>
#include <vector>

namespace alba {

class ComputeSumOfDigitsInAllNumbersFrom1ToN {
public:
    using Value = int;
    using Values = std::vector<Value>;
    explicit ComputeSumOfDigitsInAllNumbersFrom1ToN(Value const lastNumber);
    static constexpr Value UNUSED_COUNT = std::numeric_limits<Value>::max();
    [[nodiscard]] Value getValueUsingNaiveSolution() const;
    [[nodiscard]] Value getValueUsingMemoizationDP() const;
    [[nodiscard]] Value getValueUsingSummationValues() const;

private:
    [[nodiscard]] Value getValueUsingMemoizationDP(Value const number) const;
    static Value getSummationFrom1ToN(Value const number);
    Value const m_lastNumber;
};

}  // namespace alba

// Compute sum of digits in all numbers from 1 to n

// Given a number n, find the sum of digits in all numbers from 1 to n.
// Examples:
// Input: n = 5
// -> Output: Sum of digits in numbers from 1 to 5 = 15
// Input: n = 12
// -> Output: Sum of digits in numbers from 1 to 12 = 51
// Input: n = 328
// -> Output: Sum of digits in numbers from 1 to 328 = 3241
