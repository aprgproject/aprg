#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>

namespace alba::algorithm {

template <typename Values>  // this should be a non set container to be efficient because std::lower_bound and
// std::upper_bound are used
class BinaryNearestValueSearchWithCppFunctions {
public:
    using Index = int;
    using Value = typename Values::value_type;
    explicit BinaryNearestValueSearchWithCppFunctions(Values const& sortedValues) : m_sortedValues(sortedValues) {}
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    [[nodiscard]] Index getIndexOfNearestValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueUsingEqualRange(target);
        }
        return result;
    }

    [[nodiscard]] Value getNearestValue(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = getNearestValueUsingEqualRange(target);
        }
        return result;
    }

    [[nodiscard]] Value getLowerBound(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            auto lowerBoundIt = std::lower_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), target);
            result = *lowerBoundIt;
        }
        return result;
    }

    [[nodiscard]] Value getHigherBound(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            auto upperBoundIt = std::upper_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), target);
            result = *upperBoundIt;
        }
        return result;
    }

private:
    [[nodiscard]] Index getIndexOfNearestValueUsingEqualRange(Value const& target) const {
        // assumption is non set
        auto&& [lowerIt, upperIt] = containerHelper::getLowerAndUpperConstIteratorsForNonSet(m_sortedValues, target);
        Value const lowerBoundValue(*lowerIt);
        Value const higherBoundValue(*upperIt);
        Value const deviationFromLower(mathHelper::getPositiveDelta(target, lowerBoundValue));
        Value const deviationFromHigher(mathHelper::getPositiveDelta(target, higherBoundValue));
        return (deviationFromLower <= deviationFromHigher) ? std::distance(m_sortedValues.cbegin(), lowerIt)
                                                           : std::distance(m_sortedValues.cbegin(), upperIt);
    }

    [[nodiscard]] Value getNearestValueUsingEqualRange(Value const& target) const {
        // assumption is non set
        auto&& [lowerBoundValue, higherBoundValue] =
            containerHelper::getLowerAndUpperValuesForNonSet(m_sortedValues, target);
        Value const deviationFromLower(mathHelper::getPositiveDelta(target, lowerBoundValue));
        Value const deviationFromHigher(mathHelper::getPositiveDelta(target, higherBoundValue));
        return (deviationFromLower <= deviationFromHigher) ? lowerBoundValue : higherBoundValue;
    }

    Values const& m_sortedValues;
};

}  // namespace alba::algorithm
