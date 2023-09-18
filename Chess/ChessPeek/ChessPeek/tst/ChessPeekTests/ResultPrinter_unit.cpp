#include <ChessPeek/DatabaseDefinitions.hpp>
#include <ChessPeek/ResultPrinter.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::chess::ChessPeek {

TEST(ResultPrinterTest, PrintWorks) {
    AlbaLocalPathHandler const chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book const book;
    // book.loadDatabaseFrom(chessDotComBookDatabase.getPath());  // comment out if needed
    CalculationDetails calculationDetails{};
    BoardWithContext const boardWithContext(PieceColor::White, Board(BoardOrientation::BlackUpWhiteDown));
    Variation const variation1{0, 200, {"e2e4", "c7c5", "g1f3"}};
    Variation const variation2{0, 100, {"d2d4", "g8f6", "c2c4"}};
    Variation const variation3{0, 0, {"g1f3", "g8f6", "d2d4"}};
    Variation const variation4{0, -100, {"c2c4", "g8f6", "d2d4"}};
    Variation const variation5{0, -200, {"g2g3", "d7d5", "g1f3"}};
    Variations const variations{variation1, variation2, variation3, variation4, variation5};
    calculationDetails.depthInPlies = 21;
    calculationDetails.variations = variations;
    calculationDetails.bestMove = "e2e4";
    ResultPrinter printHelper(calculationDetails, boardWithContext, book);

    printHelper.print();
}

}  // namespace alba::chess::ChessPeek
