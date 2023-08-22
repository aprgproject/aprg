#pragma once

#include <string>
#include <vector>

namespace alba {

enum class DisplayTableCellMode { justify, center, right, left };

enum class DisplayTableRowMode { align, justify };

class DisplayTableCell {
public:
    DisplayTableCell();
    explicit DisplayTableCell(std::string_view displayText);
    explicit DisplayTableCell(std::string_view displayText, DisplayTableCellMode const horizontalMode);

    // rule of zero

    [[nodiscard]] std::string getText() const;
    [[nodiscard]] DisplayTableCellMode getHorizontalMode() const;

    std::string& getTextReference();
    void setText(std::string_view text);
    void setHorizontalMode(DisplayTableCellMode const mode);

private:
    std::string m_displayText;
    DisplayTableCellMode m_horizontalMode;
};

using Cells = std::vector<DisplayTableCell>;

class DisplayTableRow {
public:
    DisplayTableRow() = default;
    explicit DisplayTableRow(size_t const numberOfCells);

    // rule of zero

    [[nodiscard]] size_t getNumberOfColumns() const;
    [[nodiscard]] size_t getCharacters() const;
    [[nodiscard]] Cells const& getCells() const;
    [[nodiscard]] DisplayTableCell const& getCellAt(size_t const columnIndex) const;

    Cells& getCellsReference();
    DisplayTableCell& getCellReferenceAt(size_t const columnIndex);
    void addCell(std::string_view text);
    void addCell(std::string_view text, DisplayTableCellMode const horizontalMode);

private:
    Cells m_cells;
};

class DisplayTable {
public:
    DisplayTable() = default;
    DisplayTable(size_t const numberOfColumns, size_t const numberOfRows);

    // rule of zero

    [[nodiscard]] size_t getTotalRows() const;
    [[nodiscard]] size_t getTotalColumns() const;
    [[nodiscard]] size_t getMaxCharactersInOneRow() const;
    [[nodiscard]] DisplayTableCell const& getCellAt(size_t const columnIndex, size_t const rowIndex) const;

    DisplayTableRow& getLastRow();
    DisplayTableRow& getRowReferenceAt(size_t const rowIndex);
    DisplayTableCell& getCellReferenceAt(size_t const columnIndex, size_t const rowIndex);
    void addRow();
    void setBorders(std::string_view horizontalBorder, std::string_view verticalBorder);
    void setHorizontalBorder(std::string_view horizontalBorder);
    void setVerticalBorder(std::string_view verticalBorder);

private:
    static std::string getCellTextWithDesiredLength(DisplayTableCell const& cell, size_t const desiredLength);
    [[nodiscard]] std::string getHorizontalBorderLine(size_t const length) const;
    [[nodiscard]] std::string getVerticalBorderPoint() const;
    [[nodiscard]] size_t getVerticalBorderLength() const;
    [[nodiscard]] size_t getHorizontalBorderLength(size_t const totalColumnLength) const;

    friend std::ostream& operator<<(std::ostream& out, DisplayTable const& displayTable);

    std::string m_horizontalBorder;
    std::string m_verticalBorder;
    std::vector<DisplayTableRow> m_rows;
};

}  // namespace alba
