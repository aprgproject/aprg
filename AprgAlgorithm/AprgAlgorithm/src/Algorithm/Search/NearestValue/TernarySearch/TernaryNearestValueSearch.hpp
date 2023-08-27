#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba::algorithm {

template <typename Values>
class TernaryNearestValueSearch {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    explicit TernaryNearestValueSearch(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    [[nodiscard]] Value getNearestValue(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            Index selectedIndex(getIndexOfNearestValueWithoutCheck(0, m_sortedValues.size() - 1, target));
            if (selectedIndex != INVALID_INDEX) {
                result = m_sortedValues[selectedIndex];
            }
        }
        return result;
    }

    [[nodiscard]] Index getIndexOfNearestValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueWithoutCheck(0, m_sortedValues.size() - 1, target);
        }
        return result;
    }

    [[nodiscard]] Index getIndexOfNearestValue(Index const lowIndex, Index const highIndex, Value const& target) const {
        Index result(INVALID_INDEX);
        if (lowIndex < static_cast<Index>(m_sortedValues.size()) &&
            highIndex < static_cast<Index>(m_sortedValues.size()) && lowIndex <= highIndex) {
            result = getIndexOfNearestValueWithoutCheck(lowIndex, highIndex, target);
        }
        return result;
    }

private:
    [[nodiscard]] Index getIndexOfNearestValueWithoutCheck(
        Index const lowIndex, Index const highIndex, Value const& target) const {
        Index result(INVALID_INDEX);
        if (target < m_sortedValues[lowIndex]) {
            result = (lowIndex == 0) ? 0 : getIndexOfNearestValueInBetweenTwoIndices(lowIndex - 1, lowIndex, target);
        } else if (m_sortedValues[highIndex] < target) {
            Index lastIndex = static_cast<Index>(m_sortedValues.size()) - 1;
            result = (highIndex == lastIndex)
                         ? lastIndex
                         : getIndexOfNearestValueInBetweenTwoIndices(highIndex, highIndex + 1, target);
        } else {
            Index firstMiddleIndex = getFirstOneThirdIndex(lowIndex, highIndex);
            Index secondMiddleIndex = getSecondOneThirdIndex(lowIndex, highIndex);
            if (target < m_sortedValues[firstMiddleIndex]) {
                result = getIndexOfNearestValueWithoutCheck(lowIndex, firstMiddleIndex - 1, target);
            } else if (m_sortedValues[secondMiddleIndex] < target) {
                result = getIndexOfNearestValueWithoutCheck(secondMiddleIndex + 1, highIndex, target);
            } else {
                result = getIndexOfNearestValueWithoutCheck(firstMiddleIndex + 1, secondMiddleIndex - 1, target);
            }
        }
        return result;
    }

    [[nodiscard]] Index getIndexOfNearestValueInBetweenTwoIndices(
        Index const lowIndex, Index const highIndex, Value const& target) const {
        Value deviationFromLower(mathHelper::getPositiveDelta(target, m_sortedValues[lowIndex]));
        Value deviationFromHigher(mathHelper::getPositiveDelta(target, m_sortedValues[highIndex]));
        return (deviationFromLower <= deviationFromHigher) ? lowIndex : highIndex;
    }

    Values const& m_sortedValues;
};

}  // namespace alba::algorithm
