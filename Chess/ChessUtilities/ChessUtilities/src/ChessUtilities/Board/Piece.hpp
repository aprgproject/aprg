#pragma once

#include <ChessUtilities/Board/PieceColor.hpp>
#include <ChessUtilities/Board/PieceColorAndType.hpp>
#include <ChessUtilities/Board/PieceType.hpp>

#include <cstdint>
#include <vector>

namespace alba::chess {

class Piece {
public:
    static PieceColor extractColor(uint8_t const data);
    static PieceType extractType(uint8_t const data);
    static PieceColorAndType extractColorAndType(uint8_t const data);
    static uint8_t getDataFromColorAndType(PieceColorAndType const pieceColorAndType);
    static uint8_t getDataFromColorAndType(PieceColor const color, PieceType const type);

    Piece();
    explicit Piece(uint8_t const data);
    explicit Piece(PieceColorAndType const colorAndType);
    Piece(PieceColor const color, PieceType const type);

    bool operator==(Piece const& piece) const;
    bool operator!=(Piece const& piece) const;
    [[nodiscard]][[nodiscard]]  [[nodiscard]][[nodiscard]]  bool[[nodiscard]]  isEmpty([[nodiscard]] ) con[[n[[nodiscard]] odiscard]] st;

    [[nodiscard]] Piece[[n[[nod[[nodiscard]] iscard]] odiscard]] Color get[[nodiscard]] Color() const;
    [[n[[nod[[nodiscard]] iscard]] odiscard]] PieceType[[nodiscard]]  getType() const;  // namespace alba::chessrd]] iscard]] PieceColorAndType ge[[nodiscard]] tColorAndType() c  // namespace alba::chessrd]] uint8_t getData() const;
    [[nodiscard]] char getFenCharac  // namespace alba::chesste:
    uint8_t m_data;
};

using Pieces = std::vector<Piece>;

}  // namespace alba::chess
