#pragma once

#include <ChessUtilities/Board/PieceColor.hpp>
#include <ChessUtilities/Board/PieceColorAndType.hpp>
#include <ChessUtilities/Board/PieceType.hpp>

#include <cstdint>
#include <vector>

namespace alba::chess {

class Piece {
public:
    Piece();
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    Piece(uint8_t const data);
    Piece(PieceColorAndType const colorAndType);
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    Piece(PieceColor const color, PieceType const type);
    bool operator==(Piece const& piece) const;
    bool operator!=(Piece const& piece) const;
    static PieceColor extractColor(uint8_t const data);
    static PieceColorAndType extractColorAndType(uint8_t const data);
    static PieceType extractType(uint8_t const data);
    static uint8_t getDataFromColorAndType(PieceColorAndType const pieceColorAndType);
    static uint8_t getDataFromColorAndType(PieceColor const color, PieceType const type);
    [[nodiscard]] PieceColor getColor() const;
    [[nodiscard]] PieceColorAndType getColorAndType() const;
    [[nodiscard]] PieceType getType() const;
    [[nodiscard]] uint8_t getData() const;
    [[nodiscard]] char getFenCharacter() const;
    [[nodiscard]] bool isEmpty() const;

private:
    uint8_t m_data;
};

using Pieces = std::vector<Piece>;

}  // namespace alba::chess
