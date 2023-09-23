#include "MinimumInitialPointsToReachDestination.hpp"

using namespace std;

namespace alba {

MinimumInitialPointsToReachDestination::MinimumInitialPointsToReachDestination(Grid const& inputGrid)
    : m_inputGrid(inputGrid) {}

MinimumInitialPointsToReachDestination::MinimumInitialPointsToReachDestination(Grid&& inputGrid)
    : m_inputGrid(inputGrid) {}

MinimumInitialPointsToReachDestination::Value
MinimumInitialPointsToReachDestination::getMinimalInitialPointsUsingIterativeDP() const {
    // Time Complexity of the DP implementation is O(mn) which is much better than Naive Recursive implementation.
    Value result(0);
    if (!m_inputGrid.isEmpty()) {
        int const lastX = static_cast<int>(m_inputGrid.getNumberOfColumns()) - 1;
        int const lastY = static_cast<int>(m_inputGrid.getNumberOfRows()) - 1;
        Value const lastValue =
            m_inputGrid.getEntry(lastX, lastY) > 0 ? 1 : m_inputGrid.getEntry(lastX, lastY) * -1 + 1;

        Grid neededPointsGrid(m_inputGrid.getNumberOfColumns(), m_inputGrid.getNumberOfRows());
        neededPointsGrid.setEntry(lastX, lastY, lastValue);

        for (int x = lastX - 1; x >= 0; --x) {
            // last row has no bottom neighbors
            Value const neededPointsForThisCell =
                max(1, neededPointsGrid.getEntry(x + 1, lastY) - m_inputGrid.getEntry(x, lastY));
            neededPointsGrid.setEntry(x, lastY, neededPointsForThisCell);
        }
        for (int y = lastY - 1; y >= 0; --y) {
            // last column has no right neighbors
            Value const neededPointsForThisCell =
                max(1, neededPointsGrid.getEntry(lastX, y + 1) - m_inputGrid.getEntry(lastX, y));
            neededPointsGrid.setEntry(lastX, y, neededPointsForThisCell);
        }
        for (int y = lastY - 1; y >= 0; --y) {
            // the rest of the matrix
            for (int x = lastX - 1; x >= 0; --x) {
                Value const minFromRightOrDown =
                    min(neededPointsGrid.getEntry(x + 1, y), neededPointsGrid.getEntry(x, y + 1));
                Value const neededPointsForThisCell = max(1, minFromRightOrDown - m_inputGrid.getEntry(x, y));
                neededPointsGrid.setEntry(x, y, neededPointsForThisCell);
            }
        }
        result = neededPointsGrid.getEntry(0, 0);
    }
    return result;
}

}  // namespace alba
