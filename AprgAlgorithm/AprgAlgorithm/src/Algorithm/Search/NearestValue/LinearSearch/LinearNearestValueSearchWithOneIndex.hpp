#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <limits>

namespace alba::algorithm {

template <typename Values>
class LinearNearestValueSearchWithOneIndex {
public:
    using Index = int;
    using Value = typename Values::value_type;

    explicit LinearNearestValueSearchWithOneIndex(Values const& values)  // values can be unsorted
        : m_startIndex(INVALID_INDEX), m_endIndex(INVALID_INDEX), m_values(values) {
        setInitialIndexes();
    }

    LinearNearestValueSearchWithOneIndex(Index const startIndex, Index const endIndex, Values const& values)
        : m_startIndex(INVALID_INDEX), m_endIndex(INVALID_INDEX), m_values(values) {
        setInitialIndexes(startIndex, endIndex);
    }

    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    Index getIndexOfNearestValue(Value const& target) {
        Index result(INVALID_INDEX);
        if (!m_values.empty()) {
            Value minimumDeviation(std::numeric_limits<Value>::max());
            for (auto it = m_values.cbegin() + m_startIndex; it != m_values.cbegin() + m_endIndex; ++it) {
                Value const value(*it);
                if (value == target) {
                    result = std::distance(m_values.cbegin(), it);
                    break;
                }
                Value const currentDeviation(mathHelper::getPositiveDelta(value, target));
                if (minimumDeviation > currentDeviation) {
                    minimumDeviation = currentDeviation;
                    result = std::distance(m_values.cbegin(), it);
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
            m_endIndex = m_values.size();  // half open interval
        }
    }

    void setInitialIndexes(Index const lowIndex, Index const highIndex) {
        if (!m_values.empty()) {
            m_startIndex = std::min(lowIndex, static_cast<Index>(m_values.size()) - 1);
            m_endIndex = std::min(highIndex + 1, static_cast<Index>(m_values.size()));  // half open interval
        }
    }

    Index m_startIndex;
    Index m_endIndex;
    Values const& m_values;
};

}  // namespace alba::algorithm
