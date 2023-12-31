#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <algorithm>

namespace alba::algorithm {

template <typename Values>  // this should be a non set container to be efficient because std::lower_bound and
// std::upper_bound are used
class BinarySearchWithCppFunctions {
public:
    using Index = int;
    using Value = typename Values::value_type;
    explicit BinarySearchWithCppFunctions(Values const& sortedValues) : m_sortedValues(sortedValues) {}
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    [[nodiscard]] Index getIndexOfValue(Value const& target) const {
        Index result(INVALID_INDEX);
        auto lowerBoundIt =
            std::lower_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), target);  // assumption is non set
        if (lowerBoundIt != m_sortedValues.cend()) {
            if (*lowerBoundIt == target) {
                result = std::distance(m_sortedValues.cbegin(), lowerBoundIt);
            }
        }
        return result;
    }

private:
    Values const& m_sortedValues;
};

}  // namespace alba::algorithm

// The C++ standard library contains the following functions that are based on binary search and work in logarithmic
// time: • lower_bound returns a pointer to the first array element whose target is at least x. • upper_bound returns a
// pointer to the first array element whose target is larger than x. • equal_range returns both above pointers.
// The functions assume that the array is sorted.
// If there is no such element, the pointer points to the element after the last array element.
