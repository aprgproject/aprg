#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(DisplayTableTest, TableCanBeConstructedWithNumberOfColumnsAndRows) {
    DisplayTable table(2U, 3U);

    table.setBorders("-", "|");
    table.getCellReferenceAt(0U, 0U).setText("(0,0)");
    table.getCellReferenceAt(0U, 1U).setText("(0,1)");
    table.getCellReferenceAt(0U, 2U).setText("(0,2)");
    table.getCellReferenceAt(1U, 0U).setText("(1,0)");
    table.getCellReferenceAt(1U, 1U).setText("(1,1)");
    table.getCellReferenceAt(1U, 2U).setText("(1,2)");

    EXPECT_EQ(
        "-------------\n|(0,0)|(1,0)|\n-------------\n|(0,1)|(1,1)|\n-------------\n|(0,2)|(1,2)|\n-------------\n",
        convertToString(table));
}

TEST(DisplayTableTest, TableWorksWithBorders) {
    DisplayTable table;

    table.setBorders("X", "X");
    table.addRow();
    table.getLastRow().addCell("Test");

    EXPECT_EQ("XXXXXX\nXTestX\nXXXXXX\n", convertToString(table));
}

TEST(DisplayTableTest, TableWorksFor3by3Table) {
    DisplayTable table;

    table.setBorders("-", "|");
    table.addRow();
    table.getLastRow().addCell("1000");
    table.getLastRow().addCell("2");
    table.getLastRow().addCell("3");
    table.addRow();
    table.getLastRow().addCell("4.1");
    table.getLastRow().addCell("5");
    table.getLastRow().addCell("6.55");
    table.addRow();
    table.getLastRow().addCell("7");
    table.getLastRow().addCell("8");
    table.getLastRow().addCell("9000000");

    EXPECT_EQ(
        "----------------\n|1000|2|   3   |\n----------------\n|4.1 |5| 6.55  |\n----------------\n| 7  "
        "|8|9000000|\n----------------\n",
        convertToString(table));
}

TEST(DisplayTableTest, TableWorksForMultilineCell) {
    DisplayTable table;

    table.setBorders("-", "|");
    table.addRow();
    table.getLastRow().addCell("10000000\n100");
    table.getLastRow().addCell("2\n20000000000\n200\n22");
    table.getLastRow().addCell("3\n300\n30000");
    table.addRow();
    table.getLastRow().addCell("4.1\n4\n4");
    table.getLastRow().addCell("5\n55\n555\n5555\n555555\n5555555");
    table.getLastRow().addCell("6.55\n6......");
    table.addRow();
    table.getLastRow().addCell("7\n7\n7\n7\n7\n7\n7\n7\n7\n7\n");
    table.getLastRow().addCell("8 8 8 8 8");
    table.getLastRow().addCell("9000000");

    EXPECT_EQ(
        "------------------------------\n|        |     2     |   3   |\n|10000000|20000000000|  300  |\n|  100   |    "
        "200    | 30000 |\n|        |    22     |       |\n------------------------------\n|        |     5     |      "
        " |\n|  4.1   |    55     |       |\n|   4    |    555    | 6.55  |\n|   4    |   5555    |6......|\n|        "
        "|  555555   |       |\n|        |  5555555  |       |\n------------------------------\n|   7    |           | "
        "      |\n|   7    |           |       |\n|   7    |           |       |\n|   7    |           |       |\n|   "
        "7    | 8 8 8 8 8 |9000000|\n|   7    |           |       |\n|   7    |           |       |\n|   7    |        "
        "   |       |\n|   7    |           |       |\n|   7    |           |       "
        "|\n------------------------------\n",
        convertToString(table));
}

TEST(DisplayTableTest, TableWorksForMultilineCellWithDifferentAlignments) {
    DisplayTable table;

    table.setBorders("-", "|");
    table.addRow();
    table.getLastRow().addCell("10000000\n100", HorizontalAlignment::Center, VerticalAlignment::Center);
    table.getLastRow().addCell("2\n20000000000\n200\n22", HorizontalAlignment::Justify, VerticalAlignment::Justify);
    table.getLastRow().addCell("3\n300\n30000", HorizontalAlignment::Left, VerticalAlignment::Top);
    table.addRow();
    table.getLastRow().addCell("4.1\n4\n4", HorizontalAlignment::Right, VerticalAlignment::Bottom);
    table.getLastRow().addCell(
        "5\n55\n555\n5555\n555555\n5555555", HorizontalAlignment::Justify, VerticalAlignment::Center);
    table.getLastRow().addCell("6.55\n6......", HorizontalAlignment::Justify, VerticalAlignment::Justify);
    table.addRow();
    table.getLastRow().addCell(
        "7\n7\n7\n7\n7\n7\n7\n7\n7\n7\n", HorizontalAlignment::Center, VerticalAlignment::Center);
    table.getLastRow().addCell("8 8 8 8 8", HorizontalAlignment::Justify, VerticalAlignment::Bottom);
    table.getLastRow().addCell("9000000", HorizontalAlignment::Center, VerticalAlignment::Bottom);

    EXPECT_EQ(
        "------------------------------\n|        |     2     |3      |\n|10000000|20000000000|300    |\n|  100   |  2 "
        " 0  0  |30000  |\n|        |   2   2   |       |\n------------------------------\n|        |     5     |      "
        " |\n|        |   5   5   |6 . 5 5|\n|        |  5  5  5  |       |\n|     4.1|  5 5 5 5  |6......|\n|       "
        "4|5 5 5 5 5 5|       |\n|       4|  5555555  |       |\n------------------------------\n|   7    |           "
        "|       |\n|   7    |           |       |\n|   7    |           |       |\n|   7    |           |       |\n|  "
        " 7    |           |       |\n|   7    |           |       |\n|   7    |           |       |\n|   7    |       "
        "    |       |\n|   7    |           |       |\n|   7    | 8 8 8 8 8 "
        "|9000000|\n------------------------------\n",
        convertToString(table));
}

TEST(DisplayTableTest, ConvertingToStringWorks) {
    DisplayTable table;

    table.addRow();
    table.getLastRow().addCell("Test");

    EXPECT_EQ("Test\n", convertToString(table));
}

TEST(DisplayTableTest, TableCellWithAlignmentCanBeAdded) {
    DisplayTable table;

    table.addRow();
    table.getLastRow().addCell("12345");
    table.addRow();
    table.getLastRow().addCell("C", HorizontalAlignment::Center);
    table.addRow();
    table.getLastRow().addCell("L", HorizontalAlignment::Left);
    table.addRow();
    table.getLastRow().addCell("R", HorizontalAlignment::Right);
    table.addRow();
    table.getLastRow().addCell("J", HorizontalAlignment::Justify);

    EXPECT_EQ("12345\n  C  \nL    \n    R\n  J  \n", convertToString(table));
}

}  // namespace alba
