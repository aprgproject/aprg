#pragma once

#include <Algorithm/Search/SingleValue/LinearSearch/LinearSearchWithTwoIndices.hpp>
#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class JumpSearch
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    JumpSearch(Values const& values) // values can be unsorted
        : m_blockSize(getOptimalSize(values))
        , m_values(values)
    {}

    Index getIndexOfValue(Value const& valueToCheck)
    {
        Index result(INVALID_INDEX);

        // find the block where value is included
        Index blockStartIndex(0U);
        Index blockEndIndex(0U);
        while(blockEndIndex<m_values.size() && m_values.at(blockEndIndex)<valueToCheck)
        {
            blockStartIndex = blockEndIndex;
            blockEndIndex += m_blockSize;
        }

        LinearSearchWithTwoIndices<Values> linearSearch(m_values); // perform linear search on that block
        result = linearSearch.getIndexOfValue(blockStartIndex, blockEndIndex, valueToCheck);
        return result;
    }

private:

    Index getOptimalSize(Values const& values) const
    {
        // optimal size is squareroot size
        return std::max(1U, mathHelper::getIntegerAfterFloorOfDoubleValue<Index>(sqrt(values.size())));
    }

    Index m_blockSize;
    Values const& m_values;
};

}

}

// Like Binary Search, Jump Search is a searching algorithm for sorted arrays.
// The basic idea is to check fewer elements (than linear search) by jumping ahead by fixed steps or skipping some elements in place of searching all elements.
// For example, suppose we have an array arr[] of size n and block (to be jumped) size m.
// Then we search at the indexes arr[0], arr[m], arr[2m]…..arr[km] and so on. Once we find the interval (arr[km] < x < arr[(k+1)m]),
// we perform a linear search operation from the index km to find the element x.

// Let’s consider the following array: (0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610).
// Length of the array is 16.
// Jump search will find the value of 55 with the following steps assuming that the block size to be jumped is 4.
// STEP 1: Jump from index 0 to index 4;
// STEP 2: Jump from index 4 to index 8;
// STEP 3: Jump from index 8 to index 12;
// STEP 4: Since the element at index 12 is greater than 55 we will jump back a step to come to index 8.
// STEP 5: Perform linear search from index 8 to get the element 55.

// What is the optimal block size to be skipped?
// In the worst case, we have to do n/m jumps and if the last checked value is greater than the element to be searched for,
// we perform m-1 comparisons more for linear search.
// Therefore the total number of comparisons in the worst case will be ((n/m) + m-1).
// The value of the function ((n/m) + m-1) will be minimum when m = √n.
// Therefore, the best step size is m = √n.