#include "BuildingBridges.hpp"

#include <UniqueProblems/DynamicProgramming/Subsequence/Increasing/LongestIncreasingSubsequenceLinearithmic.hpp>

#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

namespace alba {

BuildingBridges::BuildingBridges(Bridges const& bridges) : m_bridges(bridges) {}
BuildingBridges::BuildingBridges(Bridges&& bridges) : m_bridges(bridges) {}

BuildingBridges::Bridges BuildingBridges::getPossibleBridges() const {
    // Time Complexity – O(NlogN)
    // Space Complexity – O(N)
    Bridges result;
    if (!m_bridges.empty()) {
        Bridges sortedBridges(m_bridges);
        sort(sortedBridges.begin(), sortedBridges.end());

        LongestIncreasingSubsequenceLinearithmic::Values secondPoints;
        secondPoints.reserve(sortedBridges.size());
        transform(sortedBridges.cbegin(), sortedBridges.cend(), back_inserter(secondPoints), [](auto const& bridge) {
            return bridge.second;
        });

        Index longestLength(1);
        IndexToValue lengthMinus1ToEndValue(secondPoints.size(), 0);  // length minus one because its index
        IndexToIndex lengthMinus1ToEndIndex(secondPoints.size(), 0);
        IndexToIndex indexToPreviousIndex(secondPoints.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);
        lengthMinus1ToEndValue[0] = secondPoints.front();
        for (Index i = 1; i < static_cast<Index>(secondPoints.size()); ++i) {
            Value const& value(secondPoints[i]);
            auto beginIt = lengthMinus1ToEndValue.begin();
            auto endIt = lengthMinus1ToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, value);

            if (lowerBoundItForEndValue == endIt) {
                // if current value is the highest
                indexToPreviousIndex[i] = lengthMinus1ToEndIndex[longestLength - 1];
                lengthMinus1ToEndIndex[longestLength] = i;
                lengthMinus1ToEndValue[longestLength++] = value;  // extend
            } else {
                auto const currentLength =
                    static_cast<Index>(distance(lengthMinus1ToEndValue.begin(), lowerBoundItForEndValue));
                if (currentLength > 0) {
                    indexToPreviousIndex[i] = lengthMinus1ToEndIndex[currentLength - 1];
                }
                lengthMinus1ToEndIndex[currentLength] = i;
                *lowerBoundItForEndValue = value;  // replace
            }
        }

        // construct longest sequence
        Index traverseIndex = lengthMinus1ToEndIndex[longestLength - 1];
        for (; traverseIndex != indexToPreviousIndex[traverseIndex];
             traverseIndex = indexToPreviousIndex[traverseIndex]) {
            result.emplace_back(sortedBridges[traverseIndex]);
        }
        result.emplace_back(sortedBridges[traverseIndex]);
        // reverse(result.begin(), result.end()); // no need for reverse
    }
    return result;
}

BuildingBridges::Index BuildingBridges::getNumberOfPossibleBridges() const {
    // Time Complexity – O(NlogN)
    // Space Complexity – O(N)
    Bridges sortedBridges(m_bridges);
    sort(sortedBridges.begin(), sortedBridges.end());

    LongestIncreasingSubsequenceLinearithmic::Values secondPoints;
    secondPoints.reserve(sortedBridges.size());
    transform(sortedBridges.cbegin(), sortedBridges.cend(), back_inserter(secondPoints), [](auto const& bridge) {
        return bridge.second;
    });

    LongestIncreasingSubsequenceLinearithmic const lis(secondPoints);
    return lis.getLongestLength();
}

}  // namespace alba
