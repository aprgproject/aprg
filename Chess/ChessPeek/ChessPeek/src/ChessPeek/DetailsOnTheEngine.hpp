#pragma once

#include <ChessPeek/BoardWithContext.hpp>

namespace alba::chess::ChessPeek {

class DetailsOnTheEngine {
public:
    DetailsOnTheEngine();
    [[nodiscard]] BoardWithContext const& getBoardWithContext() const;
    void save(BoardWithContext const& boardWithContext);

private:
    BoardWithContext m_boardWithContext;
};

}  // namespace alba::chess::ChessPeek
