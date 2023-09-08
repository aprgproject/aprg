#pragma once

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <vector>

namespace alba::algorithm {

template <typename Values>
class MedianOfSmallerSizes {
public:
    // nth_element might be on larger sizes
    // but this is almost constant on smaller size
    using Index = int;
    using Value = typename Values::value_type;
    using MedianValues = std::vector<Value>;  // you need to make it small because vector is used
    using ConstIterator = typename Values::const_iterator;

    explicit MedianOfSmallerSizes(Values const& values) : m_size(values.size()), m_medianSize(getMedianSize(m_size)) {
        m_sortedValuesInHalf.reserve(getMedianSizeWithOverFlow(m_medianSize));
        for (Value const& value : values) {
            addValueToMedianValues(value);
            // Confirm that capacity is constant (so no reallocation) and were not "thrashing":
            // assert(getMedianSizeWithOverFlow(m_medianSize) == m_sortedValuesInHalf.capacity());
        }
    }

    MedianOfSmallerSizes(
        ConstIterator const startIt,
        ConstIterator const endIt)  // half open interval
        : m_size(std::distance(startIt, endIt)), m_medianSize(getMedianSize(m_size)) {
        m_sortedValuesInHalf.reserve(getMedianSizeWithOverFlow(m_medianSize));
        for (auto it = startIt; it != endIt; ++it) {
            addValueToMedianValues(*it);
        }
    }

    [[nodiscard]] Value getSmallerMedian() const {
        return m_sortedValuesInHalf.empty() ? Value{} : getSmallerMedianWithoutCheck();
    }

    [[nodiscard]] Value getLargerMedian() const {
        return m_sortedValuesInHalf.empty() ? Value{} : getLargerMedianWithoutCheck();
    }

    Value getMedian() { return m_sortedValuesInHalf.empty() ? Value{} : getMedianWithoutCheck(); }

private:
    [[nodiscard]] Index getMedianSize(Index const size) const { return (size + 2) / 2; }
    [[nodiscard]] Index getMedianSizeWithOverFlow(Index const medianSize) const { return medianSize + 1; }

    [[nodiscard]] Value getMedianWithoutCheck() const {
        return (getSmallerMedianWithoutCheck() + getLargerMedianWithoutCheck()) / 2;
    }

    [[nodiscard]] Value getSmallerMedianWithoutCheck() const {
        auto it = std::prev(m_sortedValuesInHalf.end());
        if (mathHelper::isEven(m_size)) {
            --it;
        }
        return *it;
    }

    [[nodiscard]] Value getLargerMedianWithoutCheck() const { return m_sortedValuesInHalf.back(); }

    void addValueToMedianValues(Value const& value) {
        // this is similar to insertion sort for link list
        bool isInserted(false);
        for (auto it = m_sortedValuesInHalf.cbegin(); it != m_sortedValuesInHalf.cend(); ++it) {
            if (value < *it) {
                m_sortedValuesInHalf.emplace(it, value);
                isInserted = true;
                break;
            }
        }
        if (static_cast<Index>(m_sortedValuesInHalf.size()) < m_medianSize && !isInserted) {
            m_sortedValuesInHalf.emplace_back(value);
        } else if (static_cast<Index>(m_sortedValuesInHalf.size()) > m_medianSize && isInserted) {
            m_sortedValuesInHalf.pop_back();
        }
    }

    Index m_size;
    Index m_medianSize;
    MedianValues m_sortedValuesInHalf;
};

}  // namespace alba::algorithm
