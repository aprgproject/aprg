#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/BoardObserver.hpp>
#include <ChessPeek/Utilities.hpp>
#include <Common/Math/Helpers/DigitRelatedHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace alba::mathHelper;
using namespace std;

namespace alba::chess::ChessPeek {

namespace {

using SetOfPieces = std::set<PieceColorAndType>;
using PointToSetOfPiecesMap = std::map<XY, SetOfPieces>;

void writeBottomRightBorder(BitmapSnippet& outputSnippet, XY const& deltaChessBoard) {
    XY const cellBottomRightCorner(deltaChessBoard / 8U);
    for (int x = 0; x < cellBottomRightCorner.getX(); ++x) {
        outputSnippet.setPixelAt(convertToBitmapXY({x, cellBottomRightCorner.getY()}), 0U);
    }
    for (int y = 0; y < cellBottomRightCorner.getY(); ++y) {
        outputSnippet.setPixelAt(convertToBitmapXY({cellBottomRightCorner.getY(), y}), 0U);
    }
}

void checkChessCellForWhiteAndBlackPoints(
    PointToSetOfPiecesMap& whitePointsToUniquePiecesMap, PointToSetOfPiecesMap& blackPointsToUniquePiecesMap,
    BoardObserver const& retriever, PieceColorAndType const piece, int const xIndex, int const yIndex) {
    XYs whitePoints;
    XYs blackPoints;
    retriever.retrieveWhiteOffsetPoints(whitePoints, xIndex, yIndex);
    retriever.retrieveBlackOffsetPoints(blackPoints, xIndex, yIndex);

    for (XY const& whitePoint : whitePoints) {
        whitePointsToUniquePiecesMap[whitePoint].emplace(piece);
    }
    for (XY const& blackPoint : blackPoints) {
        blackPointsToUniquePiecesMap[blackPoint].emplace(piece);
    }
}

void checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
    PointToSetOfPiecesMap& whitePointsToUniquePiecesMap, PointToSetOfPiecesMap& blackPointsToUniquePiecesMap,
    BoardObserver const& retriever) {
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackKnight, 1U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackBishop, 2U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackQueen, 3U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackKing, 4U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackBishop, 5U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackKnight, 6U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackRook, 7U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 0U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 1U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 2U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 3U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 4U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 5U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 6U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 7U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteRook, 7U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 0U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 1U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 2U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 3U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 4U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 5U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 6U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 7U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackRook, 0U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteRook, 0U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteKnight, 1U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteBishop, 2U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteQueen, 3U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteKing, 4U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteBishop, 5U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteKnight, 6U, 7U);
}

void printChessBitValuesWithBlackUpWhiteDown(BoardObserver const& retriever) {
    cout << "White pawn:   [" << retriever.getBitValueFromCell(0U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getBitValueFromCell(1U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getBitValueFromCell(2U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getBitValueFromCell(3U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getBitValueFromCell(4U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getBitValueFromCell(5U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getBitValueFromCell(6U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getBitValueFromCell(7U, 6U).to_string() << "]\n";
    cout << "White rook:   [" << retriever.getBitValueFromCell(0U, 7U).to_string() << "]\n";
    cout << "White rook:   [" << retriever.getBitValueFromCell(7U, 7U).to_string() << "]\n";
    cout << "White knight: [" << retriever.getBitValueFromCell(1U, 7U).to_string() << "]\n";
    cout << "White knight: [" << retriever.getBitValueFromCell(6U, 7U).to_string() << "]\n";
    cout << "White bishop: [" << retriever.getBitValueFromCell(2U, 7U).to_string() << "]\n";
    cout << "White bishop: [" << retriever.getBitValueFromCell(5U, 7U).to_string() << "]\n";
    cout << "White queen:  [" << retriever.getBitValueFromCell(3U, 7U).to_string() << "]\n";
    cout << "White king:   [" << retriever.getBitValueFromCell(4U, 7U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getBitValueFromCell(0U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getBitValueFromCell(1U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getBitValueFromCell(2U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getBitValueFromCell(3U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getBitValueFromCell(4U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getBitValueFromCell(5U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getBitValueFromCell(6U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getBitValueFromCell(7U, 1U).to_string() << "]\n";
    cout << "Black rook:   [" << retriever.getBitValueFromCell(0U, 0U).to_string() << "]\n";
    cout << "Black rook:   [" << retriever.getBitValueFromCell(7U, 0U).to_string() << "]\n";
    cout << "Black knight: [" << retriever.getBitValueFromCell(1U, 0U).to_string() << "]\n";
    cout << "Black knight: [" << retriever.getBitValueFromCell(6U, 0U).to_string() << "]\n";
    cout << "Black bishop: [" << retriever.getBitValueFromCell(2U, 0U).to_string() << "]\n";
    cout << "Black bishop: [" << retriever.getBitValueFromCell(5U, 0U).to_string() << "]\n";
    cout << "Black queen:  [" << retriever.getBitValueFromCell(3U, 0U).to_string() << "]\n";
    cout << "Black king:   [" << retriever.getBitValueFromCell(4U, 0U).to_string() << "]\n";
}

int getLabelBasedOnSetOfPieces(SetOfPieces const& setOfPieces) {
    int result(0U);
    for (PieceColorAndType const piece : setOfPieces) {
        result += static_cast<int>(piece) * 13U;
    }
    return result;
}

uint32_t getLabelColor(int const label) {
    int const digits = getNumberOfBase10Digits(label);
    double const newValue = (static_cast<double>(1) / label) * pow(10, digits + 8);
    return static_cast<uint32_t>(newValue) % 0xFFFFFF;
}

uint32_t getLabelColor(SetOfPieces const& setOfPieces) {
    return getLabelColor(getLabelBasedOnSetOfPieces(setOfPieces));
}

}  // namespace

TEST(BoardObserverPreparationTest, DISABLED_CheckChessBitValueForChessDotComVersus) {
    AlbaLocalPathHandler const inputFile(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\ChessDotComVersus.bmp)");

    Configuration const configuration(Configuration::Type::ChessDotComVersus);
    Bitmap const inputBitmap(inputFile.getPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BoardObserver const retriever(configuration, inputSnippet);

    printChessBitValuesWithBlackUpWhiteDown(retriever);
}

TEST(BoardObserverPreparationTest, DISABLED_CheckChessBitValueForChessDotComPuzzle) {
    AlbaLocalPathHandler const inputFile(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\ChessDotComPuzzle.bmp)");

    Configuration const configuration(Configuration::Type::ChessDotComPuzzle);
    Bitmap const inputBitmap(inputFile.getPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BoardObserver const retriever(configuration, inputSnippet);

    printChessBitValuesWithBlackUpWhiteDown(retriever);
}

TEST(BoardObserverPreparationTest, DISABLED_CheckChessBitValueForLichessVersus) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\LichessVersus.bmp)");

    Configuration const configuration(Configuration::Type::LichessVersus);
    Bitmap const inputBitmap(inputFile.getPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BoardObserver const retriever(configuration, inputSnippet);

    printChessBitValuesWithBlackUpWhiteDown(retriever);
}

TEST(BoardObserverPreparationTest, DISABLED_CheckChessBitValueLichessStream) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\LichessStream.bmp)");

    Configuration const configuration(Configuration::Type::LichessStream);
    Bitmap const inputBitmap(inputFile.getPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BoardObserver const retriever(configuration, inputSnippet);

    printChessBitValuesWithBlackUpWhiteDown(retriever);
}

TEST(BoardObserverPreparationTest, DISABLED_FindImportantPointsForChessDotComVersus) {
    AlbaLocalPathHandler const inputFile(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\ChessDotComVersus.bmp)");
    AlbaLocalPathHandler const outputFileForWhite(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\White.bmp)");
    AlbaLocalPathHandler const outputFileForBlack(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\Black.bmp)");
    AlbaLocalPathHandler const blankFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blankFile.copyFileToAndIsSuccessful(outputFileForWhite.getPath());
    blankFile.copyFileToAndIsSuccessful(outputFileForBlack.getPath());

    Configuration const configuration(Configuration::Type::ChessDotComVersus);
    Bitmap const inputBitmap(inputFile.getPath());
    Bitmap const outputBitmapForWhite(outputFileForWhite.getPath());
    Bitmap const outputBitmapForBlack(outputFileForBlack.getPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    BoardObserver const retriever(configuration, inputSnippet);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    XY const deltaChessBoard = configuration.getBottomRightOfBoard() - configuration.getTopLeftOfBoard();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for (auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap) {
        outputSnippetForWhite.setPixelAt(
            convertToBitmapXY(whitePointsAndUniquePiecesPair.first),
            getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for (auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap) {
        outputSnippetForBlack.setPixelAt(
            convertToBitmapXY(blackPointsAndUniquePiecesPair.first),
            getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

TEST(BoardObserverPreparationTest, DISABLED_FindImportantPointsForChessDotComPuzzle) {
    AlbaLocalPathHandler const inputFile(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\ChessDotComPuzzle.bmp)");
    AlbaLocalPathHandler const outputFileForWhite(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\White.bmp)");
    AlbaLocalPathHandler const outputFileForBlack(
        APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\Black.bmp)");
    AlbaLocalPathHandler const blankFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blankFile.copyFileToAndIsSuccessful(outputFileForWhite.getPath());
    blankFile.copyFileToAndIsSuccessful(outputFileForBlack.getPath());

    Configuration const configuration(Configuration::Type::ChessDotComPuzzle);
    Bitmap const inputBitmap(inputFile.getPath());
    Bitmap const outputBitmapForWhite(outputFileForWhite.getPath());
    Bitmap const outputBitmapForBlack(outputFileForBlack.getPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    BoardObserver const retriever(configuration, inputSnippet);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    XY const deltaChessBoard = configuration.getBottomRightOfBoard() - configuration.getTopLeftOfBoard();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for (auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap) {
        outputSnippetForWhite.setPixelAt(
            convertToBitmapXY(whitePointsAndUniquePiecesPair.first),
            getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for (auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap) {
        outputSnippetForBlack.setPixelAt(
            convertToBitmapXY(blackPointsAndUniquePiecesPair.first),
            getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

TEST(BoardObserverPreparationTest, DISABLED_FindImportantPointsForLichessVersus) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\LichessVersus.bmp)");
    AlbaLocalPathHandler const outputFileForWhite(APRG_DIR
                                                  R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\White.bmp)");
    AlbaLocalPathHandler const outputFileForBlack(APRG_DIR
                                                  R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\Black.bmp)");
    AlbaLocalPathHandler const blankFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blankFile.copyFileToAndIsSuccessful(outputFileForWhite.getPath());
    blankFile.copyFileToAndIsSuccessful(outputFileForBlack.getPath());

    Configuration const configuration(Configuration::Type::LichessVersus);
    Bitmap const inputBitmap(inputFile.getPath());
    Bitmap const outputBitmapForWhite(outputFileForWhite.getPath());
    Bitmap const outputBitmapForBlack(outputFileForBlack.getPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    BoardObserver const retriever(configuration, inputSnippet);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    XY const deltaChessBoard = configuration.getBottomRightOfBoard() - configuration.getTopLeftOfBoard();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for (auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap) {
        outputSnippetForWhite.setPixelAt(
            convertToBitmapXY(whitePointsAndUniquePiecesPair.first),
            getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for (auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap) {
        outputSnippetForBlack.setPixelAt(
            convertToBitmapXY(blackPointsAndUniquePiecesPair.first),
            getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

TEST(BoardObserverPreparationTest, DISABLED_FindImportantPointsForLichessStream) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\LichessStream.bmp)");
    AlbaLocalPathHandler const outputFileForWhite(APRG_DIR
                                                  R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\White.bmp)");
    AlbaLocalPathHandler const outputFileForBlack(APRG_DIR
                                                  R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\Black.bmp)");
    AlbaLocalPathHandler const blankFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blankFile.copyFileToAndIsSuccessful(outputFileForWhite.getPath());
    blankFile.copyFileToAndIsSuccessful(outputFileForBlack.getPath());

    Configuration const configuration(Configuration::Type::LichessVersus);
    Bitmap const inputBitmap(inputFile.getPath());
    Bitmap const outputBitmapForWhite(outputFileForWhite.getPath());
    Bitmap const outputBitmapForBlack(outputFileForBlack.getPath());
    BitmapSnippet const inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    BoardObserver const retriever(configuration, inputSnippet);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    XY const deltaChessBoard = configuration.getBottomRightOfBoard() - configuration.getTopLeftOfBoard();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for (auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap) {
        outputSnippetForWhite.setPixelAt(
            convertToBitmapXY(whitePointsAndUniquePiecesPair.first),
            getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for (auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap) {
        outputSnippetForBlack.setPixelAt(
            convertToBitmapXY(blackPointsAndUniquePiecesPair.first),
            getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

}  // namespace alba::chess::ChessPeek
