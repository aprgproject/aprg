#include "Piece.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace std;

namespace alba
{

namespace chess
{

PieceColor Piece::extractColor(uint16_t const value)
{
    return static_cast<PieceColor>(value>>3 & 0B1);
}

PieceType Piece::extractType(uint16_t const value)
{
    return static_cast<PieceType>(value & 0B111);
}

uint16_t Piece::getValueFromColorAndType(PieceColor const color, PieceType const type)
{
    return ((static_cast<uint16_t>(color) & 0B1) << 3) | (static_cast<uint16_t>(type) & 0B111);
}

char Piece::convertToCharacter(uint16_t const value)
{
    char result{};
    PieceType pieceType(extractType(value));
    switch(pieceType)
    {
    case PieceType::Empty:
    {
        result = ' ';
        break;
    }
    case PieceType::Pawn:
    {
        result = 'p';
        break;
    }
    case PieceType::Knight:
    {
        result = 'n';
        break;
    }
    case PieceType::Bishop:
    {
        result = 'b';
        break;
    }
    case PieceType::Rook:
    {
        result = 'r';
        break;
    }
    case PieceType::Queen:
    {
        result = 'q';
        break;
    }
    case PieceType::King:
    {
        result = 'k';
        break;
    }
    default :
    {
        break;
    }
    }
    result = (PieceColor::White == extractColor(value)) ? toupper(result) : result;
    return result;
}

Piece::Piece()
    : m_underlyingValue(0U)
{}

Piece::Piece(uint16_t const underlyingValue)
    : m_underlyingValue(underlyingValue)
{}

Piece::Piece(PieceColor const color, PieceType const type)
    : m_underlyingValue(getValueFromColorAndType(color, type))
{}

bool Piece::operator==(Piece const& piece) const
{
    return m_underlyingValue == piece.m_underlyingValue;
}

bool Piece::operator!=(Piece const& piece) const
{
    return !operator==(piece);
}

bool Piece::isEmpty() const
{
    return PieceType::Empty == getType();
}

PieceColor Piece::getColor() const
{
    return extractColor(m_underlyingValue);
}

PieceType Piece::getType() const
{
    return extractType(m_underlyingValue);
}

uint16_t Piece::getUnderlyingValue() const
{
    return m_underlyingValue;
}

char Piece::getCharacter() const
{
    return convertToCharacter(m_underlyingValue);
}

ostream & operator<<(ostream & out, Piece const& piece)
{
    out << piece.getCharacter();
    return out;
}

}

}
