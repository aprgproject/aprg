#pragma once

#include <ChessUtilities/Board/Board.hpp>

namespace alba::chess::ChessPeek {

class BoardWithContext {
public:
    struct BoardDetails {
        Coordinate whiteKingCoordinate;
        Coordinate blackKingCoordinate;
    };

    BoardWithContext();
    BoardWithContext(PieceColor const& playerColor, Board const& board);
    [[nodiscard]] Board const& getBoard() const;
    [[nodiscard]] Coordinate getPlayerKingCoordinate() const;
    [[nodiscard]] Coordinate getOpponentsKingCoordinate() const;
    [[nodiscard]] PieceColor getPlayerColor() const;
    [[nodiscard]] std::string getFenString() const;
    [[nodiscard]] bool isPlayersKingOnCheck() const;
    [[nodiscard]] bool isOpponentsKingOnCheck() const;
    void save(PieceColor const& playerColor, Board const& board);
    void setPlayerColor(PieceColor const& playerColor);
    void move(Move const& move);

private:
    void updateBoardDetails();
    PieceColor m_playerColor;
    Board m_board;
    BoardDetails m_boardDetails;
};

}  // namespace alba::chess::ChessPeek
