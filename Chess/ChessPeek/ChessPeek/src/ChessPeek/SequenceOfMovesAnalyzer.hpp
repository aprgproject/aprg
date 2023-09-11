#pragma once

#include <ChessPeek/BoardWithContext.hpp>

namespace alba::chess::ChessPeek {

class SequenceOfMovesAnalyzer {
public:
    enum class State { NoMove, AnalyzingMove, Moved };

    struct StepDetails {
        BoardWithContext boardWithContext;
        Move move;
    };

    explicit SequenceOfMovesAnalyzer(BoardWithContext const& boardWithContext);
    [[nodiscard]] Board const& getCurrentBoard() const;
    [[nodiscard]] PieceColor getCurrentMoveColor() const;
    [[nodiscard]] State getState() const;
    [[nodiscard]] bool canPreMove() const;
    void analyzeMove(Move const& halfMove);
    void commitMove();

private:
    [[nodiscard]] bool isPreviousColorOpposite() const;
    [[nodiscard]] bool canPreMoveBecauseOfRecapture() const;
    [[nodiscard]] bool canPreMoveBecauseOfCheck() const;
    [[nodiscard]] bool didPreviousMoveHadOnlyOneWayToCapture() const;
    [[nodiscard]] bool isARecapture() const;
    State m_state;
    StepDetails m_current;
    StepDetails m_previous;
};

}  // namespace alba::chess::ChessPeek
