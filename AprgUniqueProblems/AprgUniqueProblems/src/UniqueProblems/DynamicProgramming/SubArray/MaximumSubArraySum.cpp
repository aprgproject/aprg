#include "MaximumSubArraySum.hpp"

using namespace std;

namespace alba {

MaximumSubArraySum::MaximumSubArraySum(Values const& values) : m_values(values) {}
MaximumSubArraySum::MaximumSubArraySum(Values&& values) : m_values(values) {}

MaximumSubArraySum::SubArrayDetails MaximumSubArraySum::getMaximumSubArraySumWithDetails() const {
    SubArrayDetails currentSubArray{};
    SubArrayDetails bestSubArray{0, 0, MIN_VALUE};
    int index(0);
    for (Value const& value : m_values) {
        if (value > currentSubArray.sum + value) {
            // new sub array contains only value
            currentSubArray = {index, index, value};
        } else {
            // add value to current sub array
            currentSubArray.highIndex = index;
            currentSubArray.sum += value;
        }
        if (bestSubArray.sum < currentSubArray.sum) {
            bestSubArray = currentSubArray;
        }
        ++index;
    }
    return bestSubArray;
}

MaximumSubArraySum::Value MaximumSubArraySum::getMaximumSubArraySum() const {
    // Kadane’s algorithm
    // This linear-time algorithm is attributed to J. B. Kadane.
    // Time Complexity: O(n)
    // Auxiliary Space: O(1)
    Value currentSum(0);
    Value bestSum(MIN_VALUE);
    for (Value const& value : m_values) {
        currentSum = max(value, currentSum + value);
        bestSum = max(bestSum, currentSum);
    }
    return bestSum;
}

}  // namespace alba
