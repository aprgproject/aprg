#pragma once

#include <vector>

namespace alba {

class TwoSum {
public:
    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.
    using Index = int;
    using Value = int;
    using Values = std::vector<Value>;
    using ValuesPair = std::pair<Value, Value>;
    explicit TwoSum(Values const& valuesToCheck);
    explicit TwoSum(Values&& valuesToCheck);
    [[nodiscard]] ValuesPair getTwoValuesWithSum(Value const targetSum) const;

private:
    Values m_sortedValues;
};

}  // namespace alba
