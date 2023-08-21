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
    Value getAUniqueElementOnTwoDuplicatedValues(Values const& values) const;
    ValuePairs getTwoUniqueElementsOnTwoDuplicatedValues(Values const& values) const;
    static Value getAUniqueElementOnThreeDuplicatedValues(Values const& values) ;
    Value getAnElementOccuringOddNumberOfTimes(Values const& values) const;

private:
    static Value getXorResult(Values const& values) ;

    Values m_values;
};

}  // namespace alba
