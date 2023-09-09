#pragma once

#include <ChessUtilities/Board/Board.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class BoardWithContext {
public:
    struct BoardDetails {
        Coordinate whiteKingCoordinate;
        Coordinate blackKingCoordinate;
    };

    BoardWithContext();
    BoardWithContext(PieceColor const& playerColor, Board const& board);
    Board const& getBoard() const;
    Coordinate getPlayerKingCoordinate() const;
    Coordinate getOpponentsKingCoordinate() const;
    PieceColor getPlayerColor() const;
    std::string getFenString() const;
    bool isPlayersKingOnCheck() const;
    bool isOpponentsKingOnCheck() const;
    void save(PieceColor const& playerColor, Board const& board);
    void setPlayerColor(PieceColor const& playerColor);
    void move(Move const& move);

private:
    void updateBoardDetails();
    PieceColor m_playerColor;
    Board m_board;
    BoardDetails m_boardDetails;
};

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba
