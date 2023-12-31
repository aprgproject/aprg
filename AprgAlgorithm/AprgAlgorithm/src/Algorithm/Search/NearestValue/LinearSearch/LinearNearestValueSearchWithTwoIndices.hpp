#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba::algorithm {

template <typename Values>
class LinearNearestValueSearchWithTwoIndices {
public:
    using Index = int;
    using Value = typename Values::value_type;

    explicit LinearNearestValueSearchWithTwoIndices(Values const& values)  // values can be unsorted
        : m_startIndex(INVALID_INDEX), m_endIndex(INVALID_INDEX), m_values(values) {
        setInitialIndexes();
    }

    LinearNearestValueSearchWithTwoIndices(Index const lowIndex, Index const highIndex, Values const& sortedValues)
        : m_startIndex(INVALID_INDEX), m_endIndex(INVALID_INDEX), m_values(sortedValues) {
        setInitialIndexes(lowIndex, highIndex);
    }

    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    Index getIndexOfNearestValue(Value const& target) {
        Index result(INVALID_INDEX);
        if (!m_values.empty()) {
            Value minimumDeviation(std::numeric_limits<Value>::max());
            for (auto itLower = m_values.cbegin() + m_startIndex, itHigher = m_values.cbegin() + m_endIndex;
                 itLower <= itHigher; ++itLower, --itHigher) {
                Value const valueAtLower = *itLower;
                Value const valueAtHigher = *itHigher;
                if (valueAtLower == target) {
                    result = std::distance(m_values.cbegin(), itLower);
                    break;
                }
                if (valueAtHigher == target) {
                    result = std::distance(m_values.cbegin(), itHigher);
                    break;
                }
                Value const deviationAtLower(mathHelper::getPositiveDelta(valueAtLower, target));
                Value const deviationAtHigher(mathHelper::getPositiveDelta(valueAtHigher, target));
                if (deviationAtLower <= deviationAtHigher && minimumDeviation > deviationAtLower) {
                    minimumDeviation = deviationAtLower;
                    result = std::distance(m_values.cbegin(), itLower);
                } else if (deviationAtLower > deviationAtHigher && minimumDeviation > deviationAtHigher) {
                    minimumDeviation = deviationAtHigher;
                    result = std::distance(m_values.cbegin(), itHigher);
                }
                if (itLower == itHigher) {
                    break;
                }
            }
        }
        return result;
    }

    Value getNearestValue(Value const& target) {
        Value result{};
        Index const selectedIndex(getIndexOfNearestValue(target));
        if (selectedIndex != INVALID_INDEX) {
            result = m_values[selectedIndex];
        }
        return result;
    }

private:
    void setInitialIndexes() {
        if (!m_values.empty()) {
            m_startIndex = 0;
            m_endIndex = m_values.size() - 1;  // fully closed interval
        }
    }

    void setInitialIndexes(Index const lowIndex, Index const highIndex) {
        if (!m_values.empty()) {
            m_startIndex = std::min(lowIndex, static_cast<Index>(m_values.size()) - 1);
            m_endIndex = std::min(highIndex, static_cast<Index>(m_values.size()) - 1);  // fully closed interval
            if (m_startIndex > m_endIndex) {
                std::swap(m_startIndex, m_endIndex);
            }
        }
    }

    Index m_startIndex;
    Index m_endIndex;
    Values const& m_values;
};

}  // namespace alba::algorithm
