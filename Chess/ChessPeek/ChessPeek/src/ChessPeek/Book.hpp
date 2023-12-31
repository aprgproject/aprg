#pragma once

#include <ChessUtilities/Board/BoardValue.hpp>

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace alba::chess::ChessPeek {

class Book {
public:
    struct MoveDetail {
        std::string move;
        int winPercentage;
    };

    using MoveDetails = std::vector<MoveDetail>;

    struct LineDetail {
        std::string nameOfLine;
        PieceColor colorToMove;
        int totalNumberOfGames;
        MoveDetails nextMoves;
    };

    using LineDetailOptional = std::optional<LineDetail>;
    [[nodiscard]] LineDetailOptional getLine(Board const& board) const;
    [[nodiscard]] size_t getSize() const;
    void saveDatabaseTo(std::string const& path) const;
    void clear();
    void addLine(Board const& board, LineDetail const& lineDetail);
    void loadDatabaseFrom(std::string const& path);

private:
    std::map<BoardValue, LineDetail> m_boardToLineDetail;
};

}  // namespace alba::chess::ChessPeek
