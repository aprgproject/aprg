#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba::algorithm {

template <typename Values>
class BinaryNearestValueSearchWithRecursion {
public:
    using Index = int;
    using Value = typename Values::value_type;
    explicit BinaryNearestValueSearchWithRecursion(Values const& sortedValues) : m_sortedValues(sortedValues) {}
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    [[nodiscard]] Value getNearestValue(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues[getIndexUsingIntervalsInsideTarget(0, m_sortedValues.size() - 1, target)];
        }
        return result;
    }

    [[nodiscard]] Index getIndexOfNearestValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexUsingIntervalsInsideTarget(0, m_sortedValues.size() - 1, target);
        }
        return result;
    }

    [[nodiscard]] Index getIndexOfNearestValue(Index const lowIndex, Index const highIndex, Value const& target) const {
        Index result(INVALID_INDEX);
        if (lowIndex < static_cast<Index>(m_sortedValues.size()) &&
            highIndex < static_cast<Index>(m_sortedValues.size()) && lowIndex <= highIndex) {
            result = getIndexUsingIntervalsInsideTarget(lowIndex, highIndex, target);
        }
        return result;
    }

private:
    [[nodiscard]] Index getIndexUsingIntervalsInsideTarget(
        Index const lowIndex, Index const highIndex, Value const& target) const {
        if (lowIndex + 1 < highIndex) {
            // Binary search with one comparison per iteration
            Index middleIndex = getMidpointOfIndexes(lowIndex, highIndex);
            if (m_sortedValues[middleIndex] <= target) {
                return getIndexUsingIntervalsInsideTarget(middleIndex, highIndex, target);
            }
            return getIndexUsingIntervalsInsideTarget(lowIndex, middleIndex, target);
        }
        return getIndexOfNearestValueInBetweenTwoIndices(lowIndex, highIndex, target);
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
