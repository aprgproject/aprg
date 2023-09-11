#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/BoardObserver.hpp>
#include <ChessPeek/Utilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba::chess::ChessPeek {

namespace {

void verifyGetChessCellPieceForBlackUpWhiteDown(BoardObserver const& retriever) {
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getPieceFromCell(0U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getPieceFromCell(1U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getPieceFromCell(2U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getPieceFromCell(3U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getPieceFromCell(4U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getPieceFromCell(5U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getPieceFromCell(6U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), retriever.getPieceFromCell(7U, 6U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteRook), retriever.getPieceFromCell(0U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteRook), retriever.getPieceFromCell(7U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKnight), retriever.getPieceFromCell(1U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKnight), retriever.getPieceFromCell(6U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteBishop), retriever.getPieceFromCell(2U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteBishop), retriever.getPieceFromCell(5U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteQueen), retriever.getPieceFromCell(3U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::WhiteKing), retriever.getPieceFromCell(4U, 7U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getPieceFromCell(0U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getPieceFromCell(1U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getPieceFromCell(2U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getPieceFromCell(3U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getPieceFromCell(4U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getPieceFromCell(5U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getPieceFromCell(6U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackPawn), retriever.getPieceFromCell(7U, 1U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackRook), retriever.getPieceFromCell(0U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackRook), retriever.getPieceFromCell(7U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKnight), retriever.getPieceFromCell(1U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKnight), retriever.getPieceFromCell(6U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackBishop), retriever.getPieceFromCell(2U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackBishop), retriever.getPieceFromCell(5U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackQueen), retriever.getPieceFromCell(3U, 0U));
    EXPECT_EQ(Piece(PieceColorAndType::BlackKing), retriever.getPieceFromCell(4U, 0U));
}

}  // namespace
TEST(BoardObserverTest, DISABLED_GetChessCellPieceWorksForChessDotComVersus) {
    AlbaLocalPathHandler const inputFile(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\ChessDotComVersus.bmp)");

    Configuration const configuration(Configuration::Type::ChessDotComVersus);
    Bitmap const inputBitmap(inputFile.getFullPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BoardObserver const retriever(configuration, inputSnippet);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever);
}

TEST(BoardObserverTest, DISABLED_GetChessCellPieceWorksForChessDotComPuzzle) {
    AlbaLocalPathHandler const inputFile(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\ChessDotComPuzzle.bmp)");

    Configuration const configuration(Configuration::Type::ChessDotComPuzzle);
    Bitmap const inputBitmap(inputFile.getFullPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BoardObserver const retriever(configuration, inputSnippet);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever);
}

TEST(BoardObserverTest, DISABLED_GetChessCellPieceWorksForLichessVersus) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\LichessVersus.bmp)");

    Configuration const configuration(Configuration::Type::LichessVersus);
    Bitmap const inputBitmap(inputFile.getFullPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BoardObserver const retriever(configuration, inputSnippet);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever);
}

TEST(BoardObserverTest, DISABLED_GetChessCellPieceWorksForLichessStream) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\LichessStream.bmp)");

    Configuration const configuration(Configuration::Type::LichessStream);
    Bitmap const inputBitmap(inputFile.getFullPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BoardObserver const retriever(configuration, inputSnippet);

    verifyGetChessCellPieceForBlackUpWhiteDown(retriever);
}

}  // namespace alba::chess::ChessPeek
