#include "CountingSubGrids.hpp"

#include <bitset>

using namespace std;

namespace alba {

CountingSubGrids::CountingSubGrids(BitGrid const& bitGrid) { initialize(bitGrid); }

int CountingSubGrids::countSubGridsWithAllBlackCorners() const {
    int result = 0;
    for (int row = 0; row < static_cast<int>(m_bitValueGrid.getNumberOfRows()); ++row) {
        for (int nextRow = row + 1; nextRow < static_cast<int>(m_bitValueGrid.getNumberOfRows()); ++nextRow) {
            int commonBlackColumns(0);
            for (int i = 0; i < static_cast<int>(m_bitValueGrid.getNumberOfColumns()); ++i) {
                commonBlackColumns += static_cast<int>(BitValueUtilities::getNumberOfOnes(
                    m_bitValueGrid.getEntry(i, row) & m_bitValueGrid.getEntry(i, nextRow)));
            }
            result += commonBlackColumns * (commonBlackColumns - 1) /
                      2;  // combinations of subgrids based on common black columns
        }
    }
    return result;
}

void CountingSubGrids::initialize(BitGrid const& bitGrid) {
    if (bitGrid.getNumberOfRows() <= bitGrid.getNumberOfColumns()) {
        int const newColumns((static_cast<int>(bitGrid.getNumberOfColumns()) + NUMBER_OF_BITS - 1) / NUMBER_OF_BITS);
        int const newRows(static_cast<int>(bitGrid.getNumberOfRows()));
        m_bitValueGrid.clearAndResize(newColumns, newRows);
        bitset<NUMBER_OF_BITS> bitsetValue;
        for (int y = 0; y < static_cast<int>(bitGrid.getNumberOfRows()); ++y) {
            for (int x = 0; x < static_cast<int>(bitGrid.getNumberOfColumns()); ++x) {
                if (x % NUMBER_OF_BITS == 0) {
                    bitsetValue.reset();
                }
                int const bitPosition = NUMBER_OF_BITS - 1 - x % NUMBER_OF_BITS;
                bitsetValue[bitPosition] = bitGrid.getEntry(x, y);
                if (bitPosition == NUMBER_OF_BITS - 1 || x == static_cast<int>(bitGrid.getNumberOfColumns()) - 1) {
                    m_bitValueGrid.setEntry(x / NUMBER_OF_BITS, y, static_cast<BitValue>(bitsetValue.to_ullong()));
                }
            }
        }
    } else {
        int const newColumns((static_cast<int>(bitGrid.getNumberOfRows()) + NUMBER_OF_BITS - 1) / NUMBER_OF_BITS);
        int const newRows(static_cast<int>(bitGrid.getNumberOfColumns()));
        m_bitValueGrid.clearAndResize(newColumns, newRows);
        bitset<NUMBER_OF_BITS> bitsetValue;
        for (int y = 0; y < static_cast<int>(bitGrid.getNumberOfColumns()); ++y) {
            for (int x = 0; x < static_cast<int>(bitGrid.getNumberOfRows()); ++x) {
                int const bitPosition = x % NUMBER_OF_BITS;
                if (bitPosition == 0) {
                    bitsetValue.reset();
                }
                bitsetValue[bitPosition] = bitGrid.getEntry(y, x);
                if (bitPosition == NUMBER_OF_BITS - 1 || x == static_cast<int>(bitGrid.getNumberOfColumns()) - 1) {
                    m_bitValueGrid.setEntry(x / NUMBER_OF_BITS, y, static_cast<BitValue>(bitsetValue.to_ullong()));
                }
            }
        }
    }
}

}  // namespace alba
