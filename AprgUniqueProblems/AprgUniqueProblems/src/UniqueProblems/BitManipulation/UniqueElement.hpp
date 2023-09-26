#pragma once

#include <cstdint>
#include <vector>

namespace alba {

class UniqueElement {
public:
    using Value = uint64_t;
    using ValuePairs = std::pair<Value, Value>;
    using Values = std::vector<Value>;
    UniqueElement() = default;
    [[nodiscard]] static Value getAUniqueElementOnTwoDuplicatedValues(Values const& values);
    [[nodiscard]] static Value getAnElementOccuringOddNumberOfTimes(Values const& values);
    [[nodiscard]] static ValuePairs getTwoUniqueElementsOnTwoDuplicatedValues(Values const& values);
    static Value getAUniqueElementOnThreeDuplicatedValues(Values const& values);

private:
    static Value getXorResult(Values const& values);
    Values m_values;
};

}  // namespace alba
