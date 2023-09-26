#include "CountNumberOfBinaryStringsWithoutConsecutiveOnes.hpp"

#include <Math/NumberTheory/OtherUtilities.hpp>

using namespace alba::math;
using namespace std;

namespace alba {

CountNumberOfBinaryStringsWithoutConsecutiveOnes::CountNumberOfBinaryStringsWithoutConsecutiveOnes(Count const length)
    : m_length(length) {}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count
CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingNaiveRecursion() const {
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(2^n)
    // Auxiliary Space: Constant
    return getCountUsingNaiveRecursion(false, m_length);
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count
CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingIterativeDP() const {
    // Time Complexity: O(n)
    // Auxiliary Space: O(n)
    Count result(0);
    if (m_length > 0) {
        CountMatrix valueMatrix(2, m_length, 0);
        valueMatrix.setEntry(0, 0, 1);
        valueMatrix.setEntry(1, 0, 1);
        for (Count index = 1; index < m_length; ++index) {
            Count const previousZeroCount = valueMatrix.getEntry(0, index - 1);
            Count const previousOneCount = valueMatrix.getEntry(1, index - 1);
            valueMatrix.setEntry(0, index, previousZeroCount + previousOneCount);
            valueMatrix.setEntry(1, index, previousZeroCount);
        }
        result = valueMatrix.getEntry(0, valueMatrix.getNumberOfRows() - 1) +
                 valueMatrix.getEntry(1, valueMatrix.getNumberOfRows() - 1);  // add last zero and one
    }
    return result;
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count
CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingIterativeDPAndSpaceEfficient() const {
    // Time Complexity: O(n)
    // Auxiliary Space: O(1)
    Count result(0);
    if (m_length > 0) {
        Count zeroCount = 1;
        Count oneCount = 1;
        for (Count subLength = 1; subLength < m_length; ++subLength) {
            Count const nextZeroCount = zeroCount + oneCount;
            oneCount = zeroCount;
            zeroCount = nextZeroCount;
        }
        result = zeroCount + oneCount;  // add last zero and one
    }
    return result;
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count
CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingFibonacci() const {
    // Time Complexity: O(1) (depends on how fibonacci number is computed)
    // Auxiliary Space: O(1)
    Count result(0);
    if (m_length > 0) {
        result = static_cast<Count>(getNthFibonacciNumberUsingBinetsFormula(static_cast<UnsignedInteger>(m_length) + 2));
    }
    return result;
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count
CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingNaiveRecursion(
    bool const previousValue, Count const length) const {
    if (length > 0) {
        if (previousValue) {
            return getCountUsingNaiveRecursion(false, length - 1);
        }
        return getCountUsingNaiveRecursion(false, length - 1) + getCountUsingNaiveRecursion(true, length - 1);
    }
    return 1;
}

}  // namespace alba
