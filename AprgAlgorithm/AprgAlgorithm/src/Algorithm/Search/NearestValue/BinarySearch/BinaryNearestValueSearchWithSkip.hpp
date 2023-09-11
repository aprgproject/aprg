#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba::algorithm {

template <typename Values>
class BinaryNearestValueSearchWithSkip {
public:
    using Index = int;
    using Value = typename Values::value_type;
    explicit BinaryNearestValueSearchWithSkip(Values const& sortedValues) : m_sortedValues(sortedValues) {}
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    [[nodiscard]] Index getIndexOfNearestValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueWithoutCheck(target);
        }
        return result;
    }

    [[nodiscard]] Value getNearestValue(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues[getIndexOfNearestValueWithoutCheck(target)];
        }
        return result;
    }

private:
    [[nodiscard]] Index getIndexOfNearestValueWithoutCheck(Value const& target) const {
        Index const lowIndex(getNearestLowerBoundIndex(target));
        return getIndexOfNearestValueFromLowerIndex(target, lowIndex);
    }

    [[nodiscard]] Index getNearestLowerBoundIndex(Value const& target) const {
        Index result(0);
        Index const size(m_sortedValues.size());
        // forward skip start from half of size, then quarter of size, then eighth of size and so on
        for (Index forwardSkip = size / 2; forwardSkip >= 1; forwardSkip /= 2) {
            result += forwardSkip;  // move to next position
            while (result < size && m_sortedValues[result] <= target) {
                result += forwardSkip;
            }
            result -= forwardSkip;  // return to valid position
        }
        return result;
    }

    [[nodiscard]] Index getIndexOfNearestValueFromLowerIndex(Value const& target, Index const lowIndex) const {
        Value const lowerBoundValue(m_sortedValues[lowIndex]);
        Value const highIndex(getHigherIndex(lowIndex));
        Value const deviationFromLower(mathHelper::getPositiveDelta(target, lowerBoundValue));
        Value const deviationFromHigher(mathHelper::getPositiveDelta(target, m_sortedValues[highIndex]));
        return (deviationFromLower <= deviationFromHigher) ? lowIndex : highIndex;
    }

    [[nodiscard]] Index getHigherIndex(Index const lowIndex) const {
        return std::min(lowIndex + 1, static_cast<Index>(m_sortedValues.size()) - 1);
    }

    Values const& m_sortedValues;
};

}  // namespace alba::algorithm
