#pragma once

#include <ChessPeek/BoardObserver.hpp>
#include <ChessPeek/BoardWithContext.hpp>
#include <ScreenMonitoring/AlbaLocalScreenMonitoring.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class DetailsFromTheScreen {
public:
    struct CountOfPieces {
        int pieceCount;
        int whiteCountInUpperHalf;
        int blackCountInUpperHalf;
        int whiteCountInLowerHalf;
        int blackCountInLowerHalf;
        int numberOfWhiteKings;
        int numberOfBlackKings;
        Coordinate whiteKingCoordinate;
        Coordinate blackKingCoordinate;
    };

    DetailsFromTheScreen(Configuration const& configuration);
    BoardWithContext const& getBoardWithContext() const;
    bool canAnalyzeBoard() const;
    void saveDetailsFromTheScreen();

private:
    bool areKingsValid() const;
    void saveBoardDetails(Coordinate const& coordinate, Piece const& piece);
    void saveBoardKingDetails(Coordinate const& coordinate, Piece const& piece);
    void saveBoardUpperHalfAndLowerHalfDetails(Coordinate const& coordinate, Piece const& piece);
    void savePlayerColorAndOrientation();
    void savePlayerColorIfChessDotComPuzzle();
    void savePlayerColorIfLichessStream();
    void savePlayerColorAndOrientationFromBoardDetails();
    void saveOrientationOnLowerHalfColor(PieceColor const lowerHalfColor);
    void savePlayerColor(PieceColor const newColor);
    void saveOrientation(BoardOrientation const orientation);
    Board getBoardAndSaveDetails();
    Configuration const& m_configuration;
    AlbaLocalScreenMonitoring m_screenMonitoring;
    BoardObserver m_boardObserver;
    BoardWithContext m_boardWithContext;
    PieceColor m_savedPlayerColor;
    BoardOrientation m_savedOrientation;
    CountOfPieces m_countOfPieces;
};

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba
