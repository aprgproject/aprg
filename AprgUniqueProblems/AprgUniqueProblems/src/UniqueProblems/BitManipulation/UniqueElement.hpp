#pragma once

#include <cstdint>
#include <vector>

namespace alba {

class UniqueElement {
public:
    using Value = uint64_t;
    using ValuePairs = std::pair<Value, Value>;
    using Values = std::vector<Value>;

    UniqueElement();
    static [[nodiscard]] Value getAUniqueElementOnTwoDuplicatedValues(Values const& values) ;
    static [[nodiscard]] ValuePairs getTwoUniqueElementsOnTwoDuplicatedValues(Values const& values) ;
    static Value getAUniqueElementOnThreeDuplicatedValues(Values const& values);
    static [[nodiscard]] Value getAnElementOccuringOddNumberOfTimes(Values const& values) ;

private:
    static Value getXorResult(Values const& values);

    Values m_values;
};

}  // namespace alba
