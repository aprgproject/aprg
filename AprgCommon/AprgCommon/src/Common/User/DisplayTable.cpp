#include "DisplayTable.hpp"

#include <algorithm>
#include <numeric>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

DisplayTableCell::DisplayTableCell()
    : m_horizontalAlignment(HorizontalAlignment::Center), m_verticalAlignment(VerticalAlignment::Center) {}

DisplayTableCell::DisplayTableCell(string_view const displayText)
    : m_displayText(displayText),
      m_horizontalAlignment(HorizontalAlignment::Center),
      m_verticalAlignment(VerticalAlignment::Center) {}

DisplayTableCell::DisplayTableCell(string_view const displayText, HorizontalAlignment const horizontalAlignment)
    : m_displayText(displayText),
      m_horizontalAlignment(horizontalAlignment),
      m_verticalAlignment(VerticalAlignment::Center) {}

DisplayTableCell::DisplayTableCell(
    string_view const displayText, HorizontalAlignment const horizontalAlignment,
    VerticalAlignment const verticalAlignment)
    : m_displayText(displayText), m_horizontalAlignment(horizontalAlignment), m_verticalAlignment(verticalAlignment) {}

string DisplayTableCell::getText() const { return m_displayText; }

HorizontalAlignment DisplayTableCell::getHorizontalAlignment() const { return m_horizontalAlignment; }

VerticalAlignment DisplayTableCell::getVerticalAlignment() const { return m_verticalAlignment; }

string& DisplayTableCell::getTextReference() { return m_displayText; }

void DisplayTableCell::setText(string_view const text) { m_displayText = text; }

void DisplayTableCell::setHorizontalAlignment(HorizontalAlignment const horizontalAlignment) {
    m_horizontalAlignment = horizontalAlignment;
}

void DisplayTableCell::setVerticalAlignment(VerticalAlignment const verticalAlignment) {
    m_verticalAlignment = verticalAlignment;
}

DisplayTableRow::DisplayTableRow(int const numberOfCells) : m_cells(numberOfCells) {}

int DisplayTableRow::getNumberOfColumns() const { return static_cast<int>(m_cells.size()); }

DisplayTableCells const& DisplayTableRow::getCells() const { return m_cells; }

DisplayTableCell const& DisplayTableRow::getCellAt(int const columnIndex) const { return m_cells[columnIndex]; }

DisplayTableCells& DisplayTableRow::getCellsReference() { return m_cells; }

DisplayTableCell& DisplayTableRow::getCellReferenceAt(int const columnIndex) { return m_cells[columnIndex]; }

void DisplayTableRow::addCell(string_view const text) { m_cells.emplace_back(text); }

void DisplayTableRow::addCell(string_view const displayText, HorizontalAlignment const horizontalAlignment) {
    m_cells.emplace_back(displayText, horizontalAlignment);
}

void DisplayTableRow::addCell(
    string_view const displayText, HorizontalAlignment const horizontalAlignment,
    VerticalAlignment const verticalAlignment) {
    m_cells.emplace_back(displayText, horizontalAlignment, verticalAlignment);
}

DisplayTable::DisplayTable(int const numberOfColumns, int const numberOfRows)
    : m_rows(numberOfRows, DisplayTableRow(numberOfColumns)) {}

int DisplayTable::getNumberOfRows() const { return static_cast<int>(m_rows.size()); }

int DisplayTable::getMaxNumberOfColumns() const {
    int maxColumns = 0;
    for (DisplayTableRow const& row : m_rows) {
        maxColumns = max(maxColumns, row.getNumberOfColumns());
    }
    return maxColumns;
}

DisplayTableRows const& DisplayTable::getRows() const { return m_rows; }

DisplayTableRow const& DisplayTable::getRowAt(int const rowIndex) const { return m_rows[rowIndex]; }

DisplayTableCell const& DisplayTable::getCellAt(int const columnIndex, int const rowIndex) const {
    return m_rows[rowIndex].getCellAt(columnIndex);
}

std::string DisplayTable::getHorizontalBorder() const { return m_horizontalBorder; }

std::string DisplayTable::getVerticalBorder() const { return m_verticalBorder; }

DisplayTableRow& DisplayTable::getLastRow() { return m_rows.back(); }

DisplayTableRow& DisplayTable::getRowReferenceAt(int const rowIndex) { return m_rows[rowIndex]; }

DisplayTableCell& DisplayTable::getCellReferenceAt(int const columnIndex, int const rowIndex) {
    return m_rows[rowIndex].getCellReferenceAt(columnIndex);
}

void DisplayTable::addRow() { m_rows.emplace_back(); }

void DisplayTable::setBorders(string_view const horizontalBorder, string_view const verticalBorder) {
    m_horizontalBorder = horizontalBorder;
    m_verticalBorder = verticalBorder;
}

void DisplayTable::setHorizontalBorder(std::string_view const horizontalBorder) { m_horizontalBorder = horizontalBorder; }

void DisplayTable::setVerticalBorder(std::string_view const verticalBorder) { m_verticalBorder = verticalBorder; }

ostream& operator<<(ostream& out, DisplayTable const& displayTable) {
    DisplayTablePrinter printer(displayTable);
    printer.print(out);
    return out;
}

DisplayTablePrinter::DisplayTablePrinter(DisplayTable const& displayTable)
    : m_maxLengthAtColumn(displayTable.getMaxNumberOfColumns(), 0),
      m_maxWidthAtRow(displayTable.getNumberOfRows(), 0),
      m_horizontalBorder(displayTable.getHorizontalBorder()),
      m_verticalBorder(displayTable.getVerticalBorder()) {
    saveTableInformation(displayTable);
}

void DisplayTablePrinter::print(std::ostream& out) const {
    string const horizontalLine(getHorizontalBorderLine());
    string const verticalBorderPoint(getVerticalBorderPoint());
    out << horizontalLine;
    int rowIndex = 0;
    for (Row const& row : m_rows) {
        int numberOfLinesAtRow = m_maxWidthAtRow[rowIndex];
        for (int lineIndexAtRow = 0; lineIndexAtRow < numberOfLinesAtRow; ++lineIndexAtRow) {
            out << verticalBorderPoint;
            int columnIndex = 0;
            for (Cell const& cell : row.cells) {
                Lines const& lines(cell.lines);
                int targetLength = m_maxLengthAtColumn[columnIndex];
                string textOnVerticalAlignment =
                    getTextBasedOnVerticalAlignment(cell.verticalAlignment, lineIndexAtRow, numberOfLinesAtRow, lines);
                string cellTextLine =
                    textOnVerticalAlignment.empty()
                        ? string(targetLength, ' ')
                        : getStringWithAlignment(textOnVerticalAlignment, targetLength, cell.horizontalAlignment);
                out << cellTextLine;
                ++columnIndex;
                out << verticalBorderPoint;
            }
            out << "\n";
        }
        out << horizontalLine;
        ++rowIndex;
    }
}

void DisplayTablePrinter::saveTableInformation(DisplayTable const& displayTable) {
    int rowIndex = 0;
    for (DisplayTableRow const& displayTableRow : displayTable.getRows()) {
        m_rows.emplace_back();
        int columnIndex = 0;
        for (DisplayTableCell const& displayTableCell : displayTableRow.getCells()) {
            m_rows.back().cells.emplace_back(
                Cell{displayTableCell.getHorizontalAlignment(), displayTableCell.getVerticalAlignment(), {}});
            strings cellTextLines;
            splitToStrings<SplitStringType::WithoutDelimeters>(cellTextLines, displayTableCell.getText(), "\r\n");
            for (string const& cellTextLine : cellTextLines) {
                m_rows.back().cells.back().lines.emplace_back(cellTextLine);
                m_maxLengthAtColumn[columnIndex] =
                    max(m_maxLengthAtColumn[columnIndex], static_cast<int>(cellTextLine.size()));
            }
            m_maxWidthAtRow[rowIndex] = max(m_maxWidthAtRow[rowIndex], static_cast<int>(cellTextLines.size()));
            ++columnIndex;
        }
        ++rowIndex;
    }

    m_totalColumnLength = accumulate(
        m_maxLengthAtColumn.cbegin(), m_maxLengthAtColumn.cend(), 0,
        [](int const partialSum, int const lengthPerColumn) { return partialSum + lengthPerColumn; });
}

string DisplayTablePrinter::getTextBasedOnVerticalAlignment(
    VerticalAlignment const alignment, int const lineIndexAtRow, int const numberOfLinesAtRow,
    Lines const& linesAtCell) {
    int numberOfLinesAtCell = static_cast<int>(linesAtCell.size());
    switch (alignment) {
        case VerticalAlignment::Justify: {
            int numberOfEmptyLines = numberOfLinesAtRow - numberOfLinesAtCell;
            int numberOfGapLines = (numberOfLinesAtCell <= 1) ? 0
                                   : (numberOfEmptyLines >= numberOfLinesAtCell + 1)
                                       ? numberOfEmptyLines / (numberOfLinesAtCell + 1)
                                       : numberOfEmptyLines / (numberOfLinesAtCell - 1);
            int remainingWidthAtTheEnds = numberOfEmptyLines - (numberOfGapLines * (numberOfLinesAtCell - 1));
            int start = remainingWidthAtTheEnds / 2;
            if (lineIndexAtRow >= start) {
                int indexAtStart = lineIndexAtRow - start;
                int interval = numberOfGapLines + 1;
                if (indexAtStart % interval == 0) {
                    int indexAtLinesAtCell = indexAtStart / interval;
                    if (indexAtLinesAtCell < numberOfLinesAtCell) {
                        return linesAtCell[indexAtLinesAtCell];
                    }
                }
            }
            break;
        }
        case VerticalAlignment::Center: {
            int middleStart = (numberOfLinesAtRow - numberOfLinesAtCell) / 2;
            int middleEnd = middleStart + numberOfLinesAtCell;
            if (lineIndexAtRow >= middleStart && lineIndexAtRow < middleEnd) {
                return linesAtCell[lineIndexAtRow - middleStart];
            }
            break;
        }
        case VerticalAlignment::Top: {
            if (lineIndexAtRow < numberOfLinesAtCell) {
                return linesAtCell[lineIndexAtRow];
            }
            break;
        }
        case VerticalAlignment::Bottom: {
            int bottomStart = numberOfLinesAtRow - numberOfLinesAtCell;
            if (lineIndexAtRow >= bottomStart) {
                return linesAtCell[lineIndexAtRow - bottomStart];
            }
            break;
        }
    }
    return {};
}

string DisplayTablePrinter::getHorizontalBorderLine() const {
    string result;
    if (!m_horizontalBorder.empty()) {
        result = getStringByRepeatingUntilDesiredLength(m_horizontalBorder, getHorizontalBorderLength()) + "\n";
    }
    return result;
}

string DisplayTablePrinter::getVerticalBorderPoint() const { return m_verticalBorder; }

int DisplayTablePrinter::getVerticalBorderLength() const { return m_verticalBorder.length(); }

int DisplayTablePrinter::getHorizontalBorderLength() const {
    return ((m_maxLengthAtColumn.size() + 1) * getVerticalBorderLength()) + m_totalColumnLength;
}

}  // namespace alba
