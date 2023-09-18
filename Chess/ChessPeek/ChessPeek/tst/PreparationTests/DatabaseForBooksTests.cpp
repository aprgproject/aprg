#include <ChessPeek/Book.hpp>
#include <ChessPeek/DatabaseDefinitions.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/StreamOperators.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba::chess::ChessPeek {

TEST(DatabaseForBooksTest, DISABLED_SavingChessDotComDatabaseWorks) {
    constexpr int MIN_NUMBER_OF_GAMES = 0;  // put a restriction if the database gets too large
    AlbaLocalPathHandler const chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    AlbaLocalPathHandler const chessDotComDataFromSite(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_DATA_FROM_SITE);
    ifstream inStream(chessDotComDataFromSite.getPath());
    AlbaFileReader fileReader(inStream);

    Book book;
    while (fileReader.isNotFinished()) {
        string const line = getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "Line: [", "]");
        strings initialMoveStrings;
        splitToStrings<SplitStringType::WithoutDelimeters>(initialMoveStrings, line, ",");
        string nameOfLine =
            getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NameOfLine: [", "]");
        replaceAllAndReturnIfFound(nameOfLine, "é", "e");  // for Reti
        int const numberOfNextMoves = convertStringToNumber<int>(
            getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NumberOfNextMoves: [", "]"));

        Board board(BoardOrientation::BlackUpWhiteDown);
        PieceColor playerColor(PieceColor::White);
        for (string const& initialMoveString : initialMoveStrings) {
            board.move(board.getMoveUsingAlgebraicNotation(initialMoveString, playerColor));
            playerColor = getOppositeColor(playerColor);
        }

        int totalNumberOfGames{};
        Book::LineDetail lineDetail{nameOfLine, playerColor, {}, {}};
        for (int i = 0; i < numberOfNextMoves; ++i) {
            string const nextMove =
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NextMove: [", "]");
            int const numberOfGames = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NumberOfGames: [", "]"));
            int const whiteWinPercentage = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "WhiteWinPercentage: [", "]"));
            fileReader.skipLine();  // DrawPercentage;
            int const blackWinPercentage = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "BlackWinPercentage: [", "]"));
            int const winPercentageForColor = (PieceColor::White == playerColor)   ? whiteWinPercentage
                                              : (PieceColor::Black == playerColor) ? blackWinPercentage
                                                                                   : 0;
            Book::MoveDetail const moveDetail{nextMove, winPercentageForColor};
            if (nextMove.empty()) {
                cout << "The numberOfNextMoves is in correct on site details. Please check." << endl;
                cout << "line: " << line << endl;
                cout << "nameOfLine: " << nameOfLine << endl;
                cout << "numberOfNextMoves: " << numberOfNextMoves << endl;
            }
            lineDetail.nextMoves.emplace_back(moveDetail);
            totalNumberOfGames += numberOfGames;
        }
        lineDetail.totalNumberOfGames = totalNumberOfGames;
        if (!nameOfLine.empty() && numberOfNextMoves != 0 && totalNumberOfGames > MIN_NUMBER_OF_GAMES) {
            book.addLine(board, lineDetail);
        }
    }

    // NOTE: Adjust MIN_NUMBER_OF_GAMES to keep the book size (under 10000 maybe?)
    // Also, the LoadingDatabaseWorks tests below needs to be under 100 ms.
    ASSERT_EQ(6169U, book.getSize());  // update this before writing to database
    book.saveDatabaseTo(chessDotComBookDatabase.getPath().string());
}

TEST(DatabaseForBooksTest, DISABLED_LoadingDatabaseWorksWithStartingPosition) {
    AlbaLocalPathHandler const chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board const boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board const boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    book.loadDatabaseFrom(chessDotComBookDatabase.getPath().string());

    auto resultWithBUWD(book.getLine(boardWithBUWD));
    auto resultWithWUBD(book.getLine(boardWithWUBD));

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("Starting Position", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::White, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("Starting Position", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::White, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithWUBD.nextMoves.size());
}

TEST(DatabaseForBooksTest, DISABLED_LoadingDatabaseWorksWithE4) {
    AlbaLocalPathHandler const chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("e4", PieceColor::White));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("e4", PieceColor::White));
    book.loadDatabaseFrom(chessDotComBookDatabase.getPath().string());
    AlbaLocalTimer timer;

    timer.resetTimer();
    auto resultWithBUWD(book.getLine(boardWithBUWD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    timer.resetTimer();
    auto resultWithWUBD(book.getLine(boardWithWUBD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("King's Pawn Opening", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("King's Pawn Opening", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithWUBD.nextMoves.size());
}

TEST(DatabaseForBooksTest, DISABLED_LoadingDatabaseWorksWithD4) {
    AlbaLocalPathHandler const chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("d4", PieceColor::White));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("d4", PieceColor::White));
    book.loadDatabaseFrom(chessDotComBookDatabase.getPath().string());
    AlbaLocalTimer timer;

    timer.resetTimer();
    auto resultWithBUWD(book.getLine(boardWithBUWD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    timer.resetTimer();
    auto resultWithWUBD(book.getLine(boardWithWUBD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("Queen's Pawn Opening", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("Queen's Pawn Opening", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithWUBD.nextMoves.size());
}

TEST(DatabaseForBooksTest, DISABLED_LoadingDatabaseWorksWithC4) {
    AlbaLocalPathHandler const chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("c4", PieceColor::White));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("c4", PieceColor::White));
    book.loadDatabaseFrom(chessDotComBookDatabase.getPath().string());
    AlbaLocalTimer timer;

    timer.resetTimer();
    auto resultWithBUWD(book.getLine(boardWithBUWD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    timer.resetTimer();
    auto resultWithWUBD(book.getLine(boardWithWUBD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("English Opening", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("English Opening", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithWUBD.nextMoves.size());
}

TEST(DatabaseForBooksTest, DISABLED_LoadingDatabaseWorksWithSicilianDefense) {
    AlbaLocalPathHandler const chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("e4", PieceColor::White));
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("c5", PieceColor::Black));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("e4", PieceColor::White));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("c5", PieceColor::Black));
    book.loadDatabaseFrom(chessDotComBookDatabase.getPath().string());
    AlbaLocalTimer timer;

    timer.resetTimer();
    auto resultWithBUWD(book.getLine(boardWithBUWD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    timer.resetTimer();
    auto resultWithWUBD(book.getLine(boardWithWUBD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("Sicilian Defense", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::White, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(27U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("Sicilian Defense", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::White, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(27U, lineDetailsWithWUBD.nextMoves.size());
}

}  // namespace alba::chess::ChessPeek
