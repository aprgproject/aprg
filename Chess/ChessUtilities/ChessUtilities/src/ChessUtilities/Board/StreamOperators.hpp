#pragma once

#include <ChessUtilities/Board/BoardValue.hpp>
#include <ChessUtilities/Board/Piece.hpp>

namespace alba::chess {
std::istream& operator>>(std::istream& in, Move& move);
std::istream& operator>>(std::istream& in, BoardValue& boardValue);
std::ostream& operator<<(std::ostream& out, PieceColor const pieceColor);
std::ostream& operator<<(std::ostream& out, PieceType const pieceType);
std::ostream& operator<<(std::ostream& out, PieceColorAndType const pieceType);
std::ostream& operator<<(std::ostream& out, Piece const& piece);
std::ostream& operator<<(std::ostream& out, Exchange const& exchange);
std::ostream& operator<<(std::ostream& out, Move const& move);
std::ostream& operator<<(std::ostream& out, Board const& board);
std::ostream& operator<<(std::ostream& out, BoardValue const& boardValue);
void printHexValuesInBoard(std::ostream& out, Board const& board);
}  // namespace alba::chess
