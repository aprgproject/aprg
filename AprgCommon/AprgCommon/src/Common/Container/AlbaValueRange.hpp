#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <functional>
#include <ostream>
#include <string>

namespace alba {

enum class AlbaValueRangeType { Unknown, Once, Forward, Backward };

template <typename DataType>
class AlbaValueRange {
public:
    using TerminationCondition = std::function<bool(DataType, DataType)>;
    using TraverseOperation = std::function<void(DataType)>;
    AlbaValueRange() : m_startValue(0), m_endValue(0), m_intervalMagnitude(0) {}

    AlbaValueRange(DataType const startValue, DataType const endValue, DataType const intervalMagnitude)
        : m_startValue(startValue),
          m_endValue(endValue),
          m_intervalMagnitude(mathHelper::getAbsoluteValue(intervalMagnitude)) {}

    [[nodiscard]] AlbaValueRangeType getRangeType() const {
        return getRangeTypeFromStartAndEnd(m_startValue, m_endValue);
    }

    [[nodiscard]] DataType getStartValue() const { return m_startValue; }
    [[nodiscard]] DataType getEndValue() const { return m_endValue; }
    [[nodiscard]] DataType getMinimum() const { return std::min(m_startValue, m_endValue); }
    [[nodiscard]] DataType getMaximum() const { return std::max(m_startValue, m_endValue); }
    [[nodiscard]] DataType getInterval() const { return getIntervalWithSign(m_intervalMagnitude, getRangeType()); }
    [[nodiscard]] DataType getIntervalMagnitude() const { return m_intervalMagnitude; }

    [[nodiscard]] DataType getDelta() const {
        DataType delta(m_endValue - m_startValue);
        // cppcheck-suppress [unsignedLessThanZero,signConversion]
        return (delta < 0) ? delta * -1 : delta;
    }

    [[nodiscard]] DataType getMidpointValue() const { return (m_startValue + m_endValue) / 2; }

    [[nodiscard]] TerminationCondition getTerminationCondition() const {
        return getTerminationCondition(getRangeType());
    }

    // rule of zero
    [[nodiscard]] bool isEmpty() const { return m_startValue == 0 && m_endValue == 0 && m_intervalMagnitude == 0; }

    [[nodiscard]] bool isValueInsideInclusive(DataType const value) const {
        return getMinimum() <= value && getMaximum() >= value;
    }

    [[nodiscard]] bool isValueInsideExclusive(DataType const value) const {
        return getMinimum() < value && getMaximum() > value;
    }

    void traverse(TraverseOperation const& traverseOperation) const {
        if (!isEmpty()) {
            if (AlbaValueRangeType::Once == getRangeType()) {
                traverseOperation(m_startValue);
            } else {
                TerminationCondition const terminationCondition(getTerminationCondition());
                DataType interval(getInterval());
                DataType traverseValue = m_startValue;
                for (; terminationCondition(traverseValue, m_endValue); traverseValue += interval) {
                    traverseOperation(traverseValue);
                }
                if (traverseValue - interval != m_endValue) {
                    traverseOperation(m_endValue);
                }
            }
        }
    }

    void set(DataType const startValue, DataType const endValue, DataType const intervalMagnitude) {
        m_startValue = startValue;
        m_endValue = endValue;
        m_intervalMagnitude = mathHelper::getAbsoluteValue(intervalMagnitude);
    }

    void setStartValue(DataType const startValue) { m_startValue = startValue; }
    void setEndValue(DataType const endValue) { m_endValue = endValue; }

    void setIntervalMagnitude(DataType const intervalMagnitude) {
        m_intervalMagnitude = getAbsoluteValue(intervalMagnitude);
    }

    void clear() {
        m_startValue = 0;
        m_endValue == 0;
        m_intervalMagnitude == 0;
    }

private:
    [[nodiscard]] AlbaValueRangeType getRangeTypeFromStartAndEnd(
        DataType const startValue, DataType const endValue) const {
        AlbaValueRangeType rangeType(AlbaValueRangeType::Unknown);
        if (startValue == endValue) {
            rangeType = AlbaValueRangeType::Once;
        } else if (startValue < endValue) {
            rangeType = AlbaValueRangeType::Forward;
        } else {
            rangeType = AlbaValueRangeType::Backward;
        }
        return rangeType;
    }

    [[nodiscard]] DataType getIntervalWithSign(DataType const interval, AlbaValueRangeType const rangeType) const {
        DataType intervalWithSign(0);
        // cppcheck-suppress [unsignedLessThanZero,signConversion]
        DataType intervalMagnitude((interval < 0) ? interval * -1 : interval);
        switch (rangeType) {
            case AlbaValueRangeType::Forward:
                intervalWithSign = intervalMagnitude;
                break;
            case AlbaValueRangeType::Backward:
                // cppcheck-suppress signConversion
                intervalWithSign = intervalMagnitude * -1;
                break;
            default:
                break;
        }
        return intervalWithSign;
    }

    [[nodiscard]] TerminationCondition getTerminationCondition(AlbaValueRangeType const rangeType) const {
        TerminationCondition terminationCondition;
        switch (rangeType) {
            case AlbaValueRangeType::Forward:
                terminationCondition = std::less_equal<DataType>();
                break;
            case AlbaValueRangeType::Backward:
                terminationCondition = std::greater_equal<DataType>();
                break;
            default:
                terminationCondition = [](DataType, DataType) -> bool { return false; };
                break;
        }
        return terminationCondition;
    }

    friend std::ostream& operator<<(std::ostream& out, AlbaValueRange const& valueRange) {
        out << "[" << valueRange.m_startValue << " <- " << valueRange.getInterval() << " -> " << valueRange.m_endValue
            << "]";
        return out;
    }

    DataType m_startValue;
    DataType m_endValue;
    DataType m_intervalMagnitude;
};

}  // namespace alba
