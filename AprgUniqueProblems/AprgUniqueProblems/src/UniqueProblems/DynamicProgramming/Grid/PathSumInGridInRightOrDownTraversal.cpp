#include "PathSumInGridInRightOrDownTraversal.hpp"

using namespace std;

namespace alba {

PathSumInGridInRightOrDownTraversal::PathSumInGridInRightOrDownTraversal(Type const type, Grid const& inputGrid)
    : m_inputGrid(inputGrid) {
    initialize(type);
}

PathSumInGridInRightOrDownTraversal::PathSumInGridInRightOrDownTraversal(Type const type, Grid&& inputGrid)
    : m_inputGrid(inputGrid) {
    initialize(type);
}

PathSumInGridInRightOrDownTraversal::Path PathSumInGridInRightOrDownTraversal::getBestPathUsingIterativeDP() const {
    Path path;
    if (!m_inputGrid.isEmpty()) {
        Grid const partialSumGrid(getPartialSumGridUsingIterativeDP());
        Index x = static_cast<Index>(partialSumGrid.getNumberOfColumns()) - 1;
        Index y = static_cast<Index>(partialSumGrid.getNumberOfRows()) - 1;
        path = {m_inputGrid.getEntry(x, y)};
        while (true) {
            if (x == 0 && y == 0) {
                break;
            }
            // NOLINTBEGIN(bugprone-branch-clone)
            if (x == 0) {
                path.emplace_back(m_inputGrid.getEntry(x, --y));
            } else if (y == 0) {
                path.emplace_back(m_inputGrid.getEntry(--x, y));
            } else if (m_compareFunction(partialSumGrid.getEntry(x - 1, y), partialSumGrid.getEntry(x, y - 1))) {
                path.emplace_back(m_inputGrid.getEntry(--x, y));
            } else {
                path.emplace_back(m_inputGrid.getEntry(x, --y));
            }
            // NOLINTEND(bugprone-branch-clone)
        }
        reverse(path.begin(), path.end());
    }
    return path;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingNaiveRecursion()
    const {
    Value pathSum(0);
    if (!m_inputGrid.isEmpty()) {
        pathSum = getBestPathSumUsingNaiveRecursion(
            static_cast<Index>(m_inputGrid.getNumberOfColumns()) - 1,
            static_cast<Index>(m_inputGrid.getNumberOfRows()) - 1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingMemoizationDP()
    const {
    Value pathSum(0);
    if (!m_inputGrid.isEmpty()) {
        Grid partialSumGrid(m_inputGrid.getNumberOfColumns(), m_inputGrid.getNumberOfRows(), UNUSED_VALUE);
        pathSum = getBestPathSumUsingMemoizationDP(
            partialSumGrid, static_cast<Index>(m_inputGrid.getNumberOfColumns()) - 1,
            static_cast<Index>(m_inputGrid.getNumberOfRows()) - 1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingIterativeDP() const {
    // Time Complexity of the DP implementation is O(mn) which is much better than Naive Recursive implementation.
    Value pathSum(0);
    if (!m_inputGrid.isEmpty()) {
        Grid const partialSumGrid(getPartialSumGridUsingIterativeDP());
        pathSum =
            partialSumGrid.getEntry(partialSumGrid.getNumberOfColumns() - 1, partialSumGrid.getNumberOfRows() - 1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Grid PathSumInGridInRightOrDownTraversal::getPartialSumGridUsingIterativeDP()
    const {
    Grid result(m_inputGrid);
    // first row has only left neighbor
    for (Index x = 1; x < static_cast<Index>(result.getNumberOfColumns()); ++x) {
        result.getEntryReference(x, 0) += result.getEntry(x - 1, 0);
    }
    // first column has only up neighbors
    for (Index y = 1; y < static_cast<Index>(result.getNumberOfRows()); ++y) {
        result.getEntryReference(0, y) += result.getEntry(0, y - 1);
    }
    // the rest of the matrix
    for (Index x = 1; x < static_cast<Index>(result.getNumberOfColumns()); ++x) {
        for (Index y = 1; y < static_cast<Index>(result.getNumberOfRows()); ++y) {
            result.getEntryReference(x, y) += m_minMaxFunction(result.getEntry(x - 1, y), result.getEntry(x, y - 1));
        }
    }
    return result;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingNaiveRecursion(
    Index const x, Index const y) const {
    // Naive recursion approach
    Value result(m_inputGrid.getEntry(x, y));
    if (!(x == 0 && y == 0)) {
        if (x == 0) {
            result += getBestPathSumUsingNaiveRecursion(x, y - 1);
        } else if (y == 0) {
            result += getBestPathSumUsingNaiveRecursion(x - 1, y);
        } else {
            result += m_minMaxFunction(
                getBestPathSumUsingNaiveRecursion(x - 1, y), getBestPathSumUsingNaiveRecursion(x, y - 1));
        }
    }
    return result;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingMemoizationDP(
    Grid& partialSumGrid, Index const x, Index const y) const {
    Value result(partialSumGrid.getEntry(x, y));
    if (UNUSED_VALUE == result) {
        result = m_inputGrid.getEntry(x, y);
        if (!(x == 0 && y == 0)) {
            if (x == 0) {
                result += getBestPathSumUsingMemoizationDP(partialSumGrid, x, y - 1);
            } else if (y == 0) {
                result += getBestPathSumUsingMemoizationDP(partialSumGrid, x - 1, y);
            } else {
                result += m_minMaxFunction(
                    getBestPathSumUsingMemoizationDP(partialSumGrid, x - 1, y),
                    getBestPathSumUsingMemoizationDP(partialSumGrid, x, y - 1));
            }
        }
        partialSumGrid.setEntry(x, y, result);
    }
    return result;
}

void PathSumInGridInRightOrDownTraversal::initialize(Type const type) {
    if (Type::MinimumSum == type) {
        m_compareFunction = less_equal<>();
        m_minMaxFunction = [](Value const& value1, Value const& value2) { return min(value1, value2); };
    } else if (Type::MaximumSum == type) {
        m_compareFunction = greater_equal<>();
        m_minMaxFunction = [](Value const& value1, Value const& value2) { return max(value1, value2); };
    }
}

}  // namespace alba
