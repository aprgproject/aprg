#pragma once

#include <ChessPeek/BoardWithContext.hpp>

namespace alba::chess::ChessPeek {

class HumanScoreGenerator {
public:
    using Score = uint64_t;

    struct MoveDetail {
        Move move;
        int mate;
        int score;
    };

    struct DataFromExchanges {
        Score hangingValue;
        Score complicatedScore;
    };

    //    // competitive but not too human
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_WINNING = 90;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_BETTER = 190;  // needs blunders to be human
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_EQUAL = 190;            // needs blunders to be human
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_WORSE = 40;    // try to equalize
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_LOSING = 90;            // just accept that your losing
    //    // good until 2200
    //    static constexpr int SCORE_LEVEL_DISTANCE = 90;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_WINNING = 90;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_BETTER = 190;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_EQUAL = 290;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_WORSE = 140;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_LOSING = 40;
    HumanScoreGenerator(BoardWithContext const& boardWithContext, int const worstScore, int const bestScore);
    [[nodiscard]] Score getHumanScore(MoveDetail const& moveDetail) const;
    static constexpr int LOWER_LIMIT_FOR_WINNING = 200;          // x > 200
    static constexpr int LOWER_LIMIT_FOR_SLIGHTLY_BETTER = 100;  // 200 > x > 100
    static constexpr int LOWER_LIMIT_FOR_EQUAL = -100;           // 100 > x > -100
    static constexpr int LOWER_LIMIT_FOR_SLIGHTLY_WORSE = -200;  // -100 > x > -200
    // just lose please
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_WINNING = 190;
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_BETTER = 290;
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_EQUAL = 190;
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_WORSE = 90;
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_LOSING = 90;

private:
    [[nodiscard]] DataFromExchanges getDataFromExchanges(Move const& move) const;
    [[nodiscard]] Score getScoreLevelPart(MoveDetail const& moveDetail) const;
    [[nodiscard]] Score getMoveTypePart(Move const& move) const;
    [[nodiscard]] Score getDistanceToKingPart(Move const& move) const;
    [[nodiscard]] Score getPiecePart(Move const& move) const;
    [[nodiscard]] int getDistanceToKing(Coordinate const& coordinate) const;
    [[nodiscard]] int getScoreLevelDistance() const;
    [[nodiscard]] bool isSameValueExchange(Piece const pieceAtStart, Piece const pieceAtEnd) const;
    [[nodiscard]] bool isDevelopingMove(Piece const pieceAtStart, Move const& move) const;
    [[nodiscard]] static Score getHumanScoreOfPiece(PieceType const pieceType);
    [[nodiscard]] static bool isACaptureMove(Piece const pieceAtStart, Piece const pieceAtEnd);
    [[nodiscard]] static bool isCastlingMove(Piece const pieceAtStart, Move const& move);
    [[nodiscard]] static bool isCheck(Piece const pieceAtEnd);
    BoardWithContext const& m_boardWithContext;
    int m_worstScore;
    int m_bestScore;
    int m_highestScoreLevel;
};

}  // namespace alba::chess::ChessPeek
