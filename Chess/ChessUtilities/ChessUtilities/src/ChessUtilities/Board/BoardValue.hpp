#pragma once

#include <ChessUtilities/Board/Board.hpp>

#include <array>
#include <cstdint>

namespace alba::chess {

class BoardValue {
public:
    static constexpr int SIZE_OF_DATA = 4;
    using Data = std::array<uint64_t, SIZE_OF_DATA>;
    BoardValue();
    explicit BoardValue(Board const& board);
    explicit BoardValue(Data const& data);
    [[nodiscard]] Data const& getData() const;
    [[nodiscard]] bool isZero() const;
    friend std::istream& operator>>(std::istream& in, BoardValue& boardValue);
    friend std::ostream& operator<<(std::ostream& out, BoardValue const& boardValue);
    friend bool operator<(BoardValue const& bv1, BoardValue const& bv2);
    friend bool operator==(BoardValue const& bv1, BoardValue const& bv2);

private:
    void saveBoardToData(Board const& board);
    static Coordinate getCorrectCoordinate(Board const& board, CoordinateDataType const x, CoordinateDataType const y);
    Data m_data;
};

bool operator<(BoardValue const& bv1, BoardValue const& bv2);
bool operator==(BoardValue const& bv1, BoardValue const& bv2);

}  // namespace alba::chess
