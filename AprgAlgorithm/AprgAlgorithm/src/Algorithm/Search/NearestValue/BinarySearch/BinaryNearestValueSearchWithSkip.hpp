#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BinaryNearestValueSearchWithSkip
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithSkip(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}

    Value getNearestValue(Value const& value) const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            Index lowerIndex(getNearestLowerBoundIndex(value));
            result = getNearestValueFromLowerBoundIndex(value, lowerIndex);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            Index lowerIndex(getNearestLowerBoundIndex(value));
            result = getIndexOfNearestValueFromLowerIndex(value, lowerIndex);
        }
        return result;
    }

private:

    Index getNearestLowerBoundIndex(Value const& value) const
    {
        Index result(0);
        Index size(m_sortedValues.size());
        for(Index forwardSkip = size/2; forwardSkip>=1; forwardSkip/=2) // forward skip start from half of size, then quarter of size, then eighth of size and so on
        {
            while(result+forwardSkip < size && m_sortedValues.at(result+forwardSkip) <= value)
            {
                result += forwardSkip;
            }
        }
        return result;
    }

    Value getNearestValueFromLowerBoundIndex(Value const& value, Index const lowerIndex) const
    {
        Value lowerBoundValue(m_sortedValues.at(lowerIndex));
        Value higherBoundValue(m_sortedValues.at(getHigherIndex(lowerIndex)));
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherBoundValue));
        return (deviationFromLower <= deviationFromHigher) ? lowerBoundValue : higherBoundValue;
    }

    Index getIndexOfNearestValueFromLowerIndex(Value const& value, Index const lowerIndex) const
    {
        Value lowerBoundValue(m_sortedValues.at(lowerIndex));
        Value higherIndex(getHigherIndex(lowerIndex));
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues.at(higherIndex)));
        return (deviationFromLower <= deviationFromHigher) ? lowerIndex : higherIndex;
    }

    Index getHigherIndex(Index const lowerIndex) const
    {
        return std::min(lowerIndex+1, m_sortedValues.size()-1);
    }

    Values const& m_sortedValues;
};

}

}