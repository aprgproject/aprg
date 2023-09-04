#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <optional>
#include <string>
#include <vector>

namespace alba {

using HorizontalAlignment = stringHelper::AlignmentType;
enum class VerticalAlignment { Justify, Center, Top, Bottom };

class DisplayTableCell {
public:
    DisplayTableCell();
    explicit DisplayTableCell(std::string_view const displayText);
    DisplayTableCell(std::string_view const displayText, HorizontalAlignment const horizontalAlignment);
    DisplayTableCell(
        std::string_view const displayText, HorizontalAlignment const horizontalAlignment,
        VerticalAlignment const verticalAlignment);

    // rule of zero

    [[nodiscard]] std::string getText() const;
    [[nodiscard]] HorizontalAlignment getHorizontalAlignment() const;
    [[nodiscard]] VerticalAlignment getVerticalAlignment() const;

    std::string& getTextReference();
    void setText(std::string_view const text);
    void setHorizontalAlignment(HorizontalAlignment const horizontalAlignment);
    void setVerticalAlignment(VerticalAlignment const verticalAlignment);

private:
    std::string m_displayText;
    HorizontalAlignment m_horizontalAlignment;
    VerticalAlignment m_verticalAlignment;
};

using DisplayTableCells = std::vector<DisplayTableCell>;

class DisplayTableRow {
public:
    DisplayTableRow() = default;
    explicit DisplayTableRow(int const numberOfCells);

    // rule of zero

    [[nodiscard]] int getNumberOfColumns() const;
    [[nodiscard]] DisplayTableCells const& getCells() const;
    [[nodiscard]] DisplayTableCell const& getCellAt(int const columnIndex) const;

    DisplayTableCells& getCellsReference();
    DisplayTableCell& getCellReferenceAt(int const columnIndex);
    void addCell(std::string_view const text);
    void addCell(std::string_view const displayText, HorizontalAlignment const horizontalAlignment);
    void addCell(
        std::string_view const displayText, HorizontalAlignment const horizontalAlignment,
        VerticalAlignment const verticalAlignment);

private:
    DisplayTableCells m_cells;
};

using DisplayTableRows = std::vector<DisplayTableRow>;

class DisplayTable {
public:
    DisplayTable() = default;
    DisplayTable(int const numberOfColumns, int const numberOfRows);

    // rule of zero

    [[nodiscard]] int getNumberOfRows() const;
    [[nodiscard]] int getMaxNumberOfColumns() const;
    [[nodiscard]] DisplayTableRows const& getRows() const;
    [[nodiscard]] DisplayTableRow const& getRowAt(int const rowIndex) const;
    [[nodiscard]] DisplayTableCell const& getCellAt(int const columnIndex, int const rowIndex) const;
    [[nodiscard]] std::string getHorizontalBorder() const;
    [[nodiscard]] std::string getVerticalBorder() const;

    DisplayTableRow& getLastRow();
    DisplayTableRow& getRowReferenceAt(int const rowIndex);
    DisplayTableCell& getCellReferenceAt(int const columnIndex, int const rowIndex);
    void addRow();
    void setBorders(std::string_view const horizontalBorder, std::string_view const verticalBorder);
    void setHorizontalBorder(std::string_view const horizontalBorder);
    void setVerticalBorder(std::string_view const verticalBorder);

private:
    friend std::ostream& operator<<(std::ostream& out, DisplayTable const& displayTable);

    std::string m_horizontalBorder;
    std::string m_verticalBorder;
    DisplayTableRows m_rows;
};

class DisplayTablePrinter {
public:
    using Line = std::string;
    using Lines = std::vector<Line>;
    struct Cell {
        HorizontalAlignment horizontalAlignment;
        VerticalAlignment verticalAlignment;
        Lines lines;
    };
    using Cells = std::vector<Cell>;
    struct Row {
        Cells cells;
    };
    using Rows = std::vector<Row>;

    explicit DisplayTablePrinter(DisplayTable const& displayTable);
    void print(std::ostream& out) const;

private:
    void saveTableInformation(DisplayTable const& displayTable);
    [[nodiscard]] static std::string getTextBasedOnVerticalAlignment(
        VerticalAlignment const alignment, int const lineIndexAtRow, int const numberOfLinesAtRow,
        Lines const& linesAtCell);
    [[nodiscard]] bool shouldBePrintedAtThisRow() const;
    [[nodiscard]] std::string getHorizontalBorderLine() const;
    [[nodiscard]] std::string getVerticalBorderPoint() const;
    [[nodiscard]] int getVerticalBorderLength() const;
    [[nodiscard]] int getHorizontalBorderLength() const;
    Rows m_rows{};
    std::vector<int> m_maxLengthAtColumn;
    std::vector<int> m_maxWidthAtRow;
    int m_totalColumnLength{};
    std::string m_horizontalBorder;
    std::string m_verticalBorder;
};

}  // namespace alba
