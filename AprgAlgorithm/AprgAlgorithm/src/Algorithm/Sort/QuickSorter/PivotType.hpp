#pragma once

#include <utility>

namespace alba::algorithm {

enum class PivotType {
    LowestIndex,
    HighestIndex,
    RandomIndex,
    MedianOfLowMidHighIndexes,
    MedianNinther,
    MedianOfMedians
};

}  // namespace alba::algorithm
