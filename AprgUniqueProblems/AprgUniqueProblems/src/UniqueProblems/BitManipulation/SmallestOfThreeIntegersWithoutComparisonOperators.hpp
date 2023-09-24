#pragma once

#include <cstdint>

namespace alba {

class SmallestOfThreeIntegersWithoutComparisonOperators {
public:
    using UnsignedValue = uint64_t;  // The comparison works only on unsigned values.
    SmallestOfThreeIntegersWithoutComparisonOperators();

    [[nodiscard]] static UnsignedValue getSmallest(
        UnsignedValue const value1, UnsignedValue const value2, UnsignedValue const value3);

    static bool isLessThan(UnsignedValue const value1, UnsignedValue const value2);
};

}  // namespace alba

// Write a program to find the smallest of three integers, without using any of the comparison operators.
// Let 3 input numbers be x, y and z.
