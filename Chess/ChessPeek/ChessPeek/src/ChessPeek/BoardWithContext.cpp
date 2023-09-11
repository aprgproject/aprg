#include "BoardWithContext.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba::chess::ChessPeek {

BoardWithContext::BoardWithContext() : m_playerColor{}, m_boardDetails{} {}

BoardWithContext::BoardWithContext(PieceColor const& playerColor, Board const& board)
    : m_playerColor(playerColor), m_board(board), m_boardDetails{} {
    updateBoardDetails();
}

Board const& BoardWithContext::getBoard() const { return m_board; }

Coordinate BoardWithContext::getPlayerKingCoordinate() const {
    Coordinate result = {};
    if (m_playerColor == PieceColor::White) {
        result = m_boardDetails.whiteKingCoordinate;
    } else if (m_playerColor == PieceColor::Black) {
        result = m_boardDetails.blackKingCoordinate;
    }
    return result;
}

Coordinate BoardWithContext::getOpponentsKingCoordinate() const {
    Coordinate result = {};
    if (m_playerColor == PieceColor::White) {
        result = m_boardDetails.blackKingCoordinate;
    } else if (m_playerColor == PieceColor::Black) {
        result = m_boardDetails.whiteKingCoordinate;
    }
    return result;
}

PieceColor BoardWithContext::getPlayerColor() const { return m_playerColor; }

string BoardWithContext::getFenString() const {
    return constructFenString(m_board, m_playerColor, m_board.getCastlingPartOfFenString(), "-", 0, 1);
}

bool BoardWithContext::isPlayersKingOnCheck() const { return m_board.canBeCaptured(getPlayerKingCoordinate()); }
bool BoardWithContext::isOpponentsKingOnCheck() const { return m_board.canBeCaptured(getOpponentsKingCoordinate()); }

void BoardWithContext::save(PieceColor const& playerColor, Board const& board) {
    m_playerColor = playerColor;
    m_board = board;
    updateBoardDetails();
}

void BoardWithContext::setPlayerColor(PieceColor const& playerColor) { m_playerColor = playerColor; }

void BoardWithContext::move(Move const& move) {
    if (move.first == m_boardDetails.whiteKingCoordinate) {
        m_boardDetails.whiteKingCoordinate = move.second;
    }
    if (move.first == m_boardDetails.blackKingCoordinate) {
        m_boardDetails.blackKingCoordinate = move.second;
    }
    m_board.move(move);
}

void BoardWithContext::updateBoardDetails() {
    m_boardDetails = {};
    for (int j = 0; j < 8; ++j) {
        for (int i = 0; i < 8; ++i) {
            Coordinate const coordinate(i, j);
            Piece const piece(m_board.getPieceAt(coordinate));
            if (piece.getType() == PieceType::King) {
                if (piece.getColor() == PieceColor::White) {
                    m_boardDetails.whiteKingCoordinate = coordinate;
                } else if (piece.getColor() == PieceColor::Black) {
                    m_boardDetails.blackKingCoordinate = coordinate;
                }
            }
        }
    }
}

}  // namespace alba::chess::ChessPeek
