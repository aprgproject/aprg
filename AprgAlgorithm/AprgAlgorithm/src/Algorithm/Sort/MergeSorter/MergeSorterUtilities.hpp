#pragma once

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>
void mergeTheTwoSortedParts(
    Values& valuesToSort, Values& auxiliary, unsigned int const lowest, unsigned int const middle,
    unsigned int const highest) {
    std::copy(valuesToSort.cbegin() + lowest, valuesToSort.cbegin() + highest + 1, auxiliary.begin() + lowest);
    unsigned int mainIndex = lowest, lowPartIndex = lowest, highPartIndex = middle + 1;
    for (; mainIndex <= highest && lowPartIndex <= middle && highPartIndex <= highest; mainIndex++) {
        if (auxiliary.at(highPartIndex) < auxiliary.at(lowPartIndex)) {  // high part has lower value
            valuesToSort[mainIndex] = auxiliary.at(highPartIndex++);     // copy and move high index
        } else {
            valuesToSort[mainIndex] = auxiliary.at(lowPartIndex++);  // copy and move low index
        }
    }
    if (lowPartIndex <= middle) {
        std::copy(auxiliary.cbegin() + lowPartIndex, auxiliary.cbegin() + middle + 1, valuesToSort.begin() + mainIndex);
    }
    if (highPartIndex <= highest) {
        // copy all remaining from high part
        std::copy(
            auxiliary.cbegin() + highPartIndex, auxiliary.cbegin() + highest + 1, valuesToSort.begin() + mainIndex);
    }
}

template <typename Values>
Values mergeTwoSortedSequences(Values const& sortedValues1, Values const& sortedValues2) {
    Values result;
    result.reserve(sortedValues1.size() + sortedValues2.size());
    unsigned int i = 0, j = 0;
    while (i < sortedValues1.size() && j < sortedValues2.size()) {
        if (sortedValues2.at(j) < sortedValues1.at(i)) {  // second has lower value
            result.emplace_back(sortedValues2.at(j++));   // copy and move second index
        } else {                                          // first has lower value
            result.emplace_back(sortedValues1.at(i++));   // copy and move first index
        }
    }
    if (i < sortedValues1.size()) {
        // copy remaining from the other array
        std::copy(sortedValues1.cbegin() + i, sortedValues1.cend(), std::back_inserter(result));
    }
    if (j < sortedValues2.size()) {
        // copy remaining from the other array
        std::copy(sortedValues2.cbegin() + j, sortedValues2.cend(), std::back_inserter(result));
    }
    return result;
}
}  // namespace algorithm

}  // namespace alba
