#pragma once

#include <Algorithm/Search/NearestValue/LinearSearch/LinearNearestValueSearchWithOneIndex.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba::algorithm {

template <typename Values>
class JumpNearestValueSearch {
public:
    using Index = int;
    using Value = typename Values::value_type;
    explicit JumpNearestValueSearch(Values const& values)  // values can be unsorted
        : m_blockSize(getOptimalSize(values)), m_sortedValues(values) {}
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    Index getIndexOfNearestValue(Value const& target) {
        Index previousSearchIndex(0);
        Index searchIndex(0);
        while (searchIndex < static_cast<Index>(m_sortedValues.size()) && m_sortedValues[searchIndex] < target) {
            previousSearchIndex = searchIndex;
            searchIndex += m_blockSize;
        }

        // perform linear search on that block
        LinearNearestValueSearchWithOneIndex<Values> linearSearch(
            previousSearchIndex, std::min(searchIndex, static_cast<int>(m_sortedValues.size()) - 1), m_sortedValues);
        return linearSearch.getIndexOfNearestValue(target);
    }

    Value getNearestValue(Value const& target) {
        Value result{};
        Index const selectedIndex(getIndexOfNearestValue(target));
        if (selectedIndex != INVALID_INDEX) {
            result = m_sortedValues[selectedIndex];
        }
        return result;
    }

private:
    [[nodiscard]] Index getOptimalSize(Values const& values) const {
        // optimal size is squareroot size
        return std::max(1, mathHelper::getIntegerAfterFloorOfDoubleValue<Index>(sqrt(values.size())));
    }

    Index m_blockSize;
    Values const& m_sortedValues;
};

}  // namespace alba::algorithm
