#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba::algorithm {

template <typename Values>
class BinaryNearestValueSearchWithTwoIndices {
public:
    using Index = int;
    using Value = typename Values::value_type;

    explicit BinaryNearestValueSearchWithTwoIndices(Values const& sortedValues)
        : m_lowIndex(INVALID_INDEX), m_highIndex(INVALID_INDEX), m_sortedValues(sortedValues) {
        setInitialIndexes();
    }

    BinaryNearestValueSearchWithTwoIndices(Index const lowIndex, Index const highIndex, Values const& sortedValues)
        : m_lowIndex(INVALID_INDEX), m_highIndex(INVALID_INDEX), m_sortedValues(sortedValues) {
        setInitialIndexes(lowIndex, highIndex);
    }

    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();
    [[nodiscard]] inline Index getLowerIndex() const { return m_lowIndex; }
    [[nodiscard]] inline Index getHigherIndex() const { return m_highIndex; }

    [[nodiscard]] Value getLowerValue() const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues[m_lowIndex];
        }
        return result;
    }

    [[nodiscard]] Value getHigherValue() const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues[m_highIndex];
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& target) {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            moveCloserUsingIntervalsInsideTarget(target);
            result = getIndexOfNearestValueInBetweenTwoIndices(target);
        }
        return result;
    }

    Value getNearestValue(Value const& target) {
        Value result{};
        if (!m_sortedValues.empty()) {
            moveCloserUsingIntervalsInsideTarget(target);
            result = m_sortedValues[getIndexOfNearestValueInBetweenTwoIndices(target)];
        }
        return result;
    }

private:
    [[nodiscard]] Index getIndexOfNearestValueInBetweenTwoIndices(Value const& target) const {
        Value const deviationFromLower(mathHelper::getPositiveDelta(target, m_sortedValues[m_lowIndex]));
        Value const deviationFromHigher(mathHelper::getPositiveDelta(target, m_sortedValues[m_highIndex]));
        return (deviationFromLower <= deviationFromHigher) ? m_lowIndex : m_highIndex;
    }

    void setInitialIndexes() {
        if (!m_sortedValues.empty()) {
            m_lowIndex = 0;
            m_highIndex = m_sortedValues.size() - 1;  // fully closed interval
        }
    }

    void setInitialIndexes(Index const lowIndex, Index const highIndex) {
        if (!m_sortedValues.empty()) {
            Index const maxIndex = m_sortedValues.size() - 1;
            m_lowIndex = std::min(lowIndex, maxIndex);
            m_highIndex = std::min(highIndex, maxIndex);  // fully closed interval
            if (m_lowIndex > m_highIndex) {
                std::swap(m_lowIndex, m_highIndex);
            }
        }
    }

    void moveCloserUsingIntervalsInsideTarget(Value const& target) {
        if (!m_sortedValues.empty()) {
            while (m_lowIndex + 1 < m_highIndex) {
                Index const middleIndex(getMidpointOfIndexes(m_lowIndex, m_highIndex));
                if (m_sortedValues[middleIndex] <= target) {
                    m_lowIndex = middleIndex;
                } else {
                    m_highIndex = middleIndex;
                }
            }
            if (target <= m_sortedValues[m_lowIndex]) {
                m_highIndex = m_lowIndex;
            } else if (m_sortedValues[m_highIndex] <= target) {
                m_lowIndex = m_highIndex;
            }
        }
    }

    Index m_lowIndex;
    Index m_highIndex;
    Values const& m_sortedValues;
};

}  // namespace alba::algorithm
