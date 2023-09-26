#pragma once

#include <ChessUtilities/Board/BoardTypes.hpp>
#include <ChessUtilities/Board/Exchange.hpp>
#include <ChessUtilities/Board/Piece.hpp>

#include <array>
#include <cstdint>
#include <functional>
#include <limits>
#include <optional>
#include <vector>

namespace alba::chess {

struct Board {
public:
    // Conflict between std::numeric_limits::max() and the max(a, b) macro defined in minwindef.h included as part of
    // Windows.h.
    static constexpr int MAX_NUMBER_OF_MOVES = (std::numeric_limits<int>::max)();
    static constexpr int CHESS_SIDE_SIZE = 8;

    using PieceGrid =
        std::array<Piece, static_cast<std::size_t>(CHESS_SIDE_SIZE) * static_cast<std::size_t>(CHESS_SIDE_SIZE)>;

    using CoordinateCondition = std::function<bool(Coordinate const&)>;

    enum class CastleType { NotACastle, KingSideCastle, QueenSideCastle };

    struct DeltaRange {
        CoordinateDataType interval;
        CoordinateDataType invalidDelta;
    };

    struct NotationDetailsOfMove {
        PieceType pieceType{PieceType::Empty};
        std::optional<CoordinateDataType> firstX, firstY, lastX, lastY;
    };

    struct AttackDefendCount {
        int attack;
        int defend;
    };

    using AttackDefendCounts = std::vector<AttackDefendCount>;
    Board();
    explicit Board(BoardOrientation const& orientation);
    Board(BoardOrientation const& orientation, PieceGrid const& pieceGrid);
    bool operator==(Board const& other) const;
    bool operator!=(Board const& other) const;
    [[nodiscard]] BoardOrientation getOrientation() const;
    [[nodiscard]] Coordinate getCoordinateFromAlgebraicNotation(std::string const& text) const;
    [[nodiscard]] Exchange getExchangeAt(Coordinate const& coordinate) const;
    [[nodiscard]] Move getMoveUsingUciNotation(std::string const& text) const;
    [[nodiscard]] Move getMoveUsingAlgebraicNotation(std::string const& text, PieceColor const moveColor) const;
    [[nodiscard]] Moves getMovesFromThis(Coordinate const& startpoint, int const maxSize = MAX_NUMBER_OF_MOVES) const;

    [[nodiscard]] Moves getMovesToThis(
        Coordinate const& endpoint, PieceColor const& moveColor, int const maxSize = MAX_NUMBER_OF_MOVES) const;

    [[nodiscard]] Moves getAttacksToThis(
        Coordinate const& endpoint, PieceColor const& moveColor, int const maxSize = MAX_NUMBER_OF_MOVES) const;

    [[nodiscard]] Piece getPieceAt(Coordinate const& coordinate) const;
    [[nodiscard]] PieceGrid const& getPieceGrid() const;
    [[nodiscard]] std::string getAlgebraicNotationOfCoordinate(Coordinate const& coordinate) const;
    [[nodiscard]] std::string getReadableStringOfMove(Move const& move) const;
    [[nodiscard]] std::string getNotationPartOfFenString() const;
    [[nodiscard]] std::string getCastlingPartOfFenString() const;

    [[nodiscard]] int getNumberOfWaysToBlockAttacks(
        Moves const& attacks, int const maxSize = MAX_NUMBER_OF_MOVES) const;

    [[nodiscard]] bool isEmptyAt(Coordinate const& coordinate) const;
    [[nodiscard]] bool isACaptureMove(Move const& move) const;
    [[nodiscard]] bool isAPromotionMove(Move const& move) const;
    [[nodiscard]] bool isACastlingMove(Move const& move) const;
    [[nodiscard]] bool isAPossibleMove(Move const& move) const;
    [[nodiscard]] bool canBeCaptured(Coordinate const& endpoint) const;
    [[nodiscard]] bool areThereAnyMovesToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    [[nodiscard]] bool areThereAnyAttacksToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    [[nodiscard]] bool hasOnlyOneMoveToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    void setOrientation(BoardOrientation const orientation);
    void setPieceAt(Coordinate const& coordinate, Piece const& piece);
    void move(Move const& move);

private:
    [[nodiscard]] Coordinate getCorrectCoordinateFromAlgebraicNotation(
        CoordinateDataType const x, CoordinateDataType const y) const;

    [[nodiscard]] CoordinateDataType getXInCorrectOrientation(CoordinateDataType const x) const;
    [[nodiscard]] CoordinateDataType getYInCorrectOrientation(CoordinateDataType const y) const;
    [[nodiscard]] Coordinates getPawnCapturesDeltaCoordinates(PieceColor const moveColor) const;
    [[nodiscard]] Coordinates getPawnReverseCapturesDeltaCoordinates(PieceColor const moveColor) const;

    [[nodiscard]] DeltaRange getPawnNonCaptureDeltaRange(
        Coordinate const& startpoint, PieceColor const moveColor) const;

    [[nodiscard]] DeltaRange getPawnReverseNonCaptureDeltaRange(
        Coordinate const& endpoint, PieceColor const moveColor) const;

    [[nodiscard]] Move getFirstMoveThatFits(
        Moves const& possibleMoves, PieceType const pieceType, std::optional<CoordinateDataType> const& xLimitation,
        std::optional<CoordinateDataType> const& yLimitation) const;

    [[nodiscard]] Move getCastleMove(CastleType const castleType, PieceColor const moveColor) const;
    [[nodiscard]] Move getNonCastleMoveWithAlgebraicNotation(std::string const& text, PieceColor const moveColor) const;
    [[nodiscard]] MovePair getMatchingCastlingKingAndRookMovePair(Move const& kingMoveThatShouldMatch) const;
    [[nodiscard]] MovePairs getCastlingKingAndRookMovePairs(PieceColor const moveColor) const;

    [[nodiscard]] Moves getCandidatesMoves(
        Coordinate const& endpoint, PieceColor const moveColor, PieceType const pieceType) const;

    [[nodiscard]] NotationDetailsOfMove determineNotationDetailsOfMove(
        std::string const& textInAlgebraicNotation) const;

    [[nodiscard]] int getNumberOfWaysToBlockPath(
        Coordinate const& startpoint, Coordinate const& endpoint, PieceColor const blockingPieceColor,
        int const maxSize) const;

    [[nodiscard]] bool isPossibleMoveBasedFromPieceType(Move const& move) const;
    [[nodiscard]] bool isPossiblePawnMove(Move const& move) const;
    [[nodiscard]] bool isPossibleKnightMove(Move const& move) const;
    [[nodiscard]] bool isPossibleBishopMove(Move const& move) const;
    [[nodiscard]] bool isPossibleRookMove(Move const& move) const;
    [[nodiscard]] bool isPossibleQueenMove(Move const& move) const;
    [[nodiscard]] bool isPossibleKingMove(Move const& move) const;
    [[nodiscard]] bool isPossibleOneKingMove(Move const& move) const;
    [[nodiscard]] bool isPossibleKingCastlingMove(Move const& kingMove) const;
    [[nodiscard]] bool isAPawnNonCaptureMove(Move const& move) const;
    [[nodiscard]] bool isAPawnCapture(Move const& move) const;
    [[nodiscard]] bool isAPawnEnPassantMove(Move const& move) const;
    [[nodiscard]] bool isCastlingPossible(Move const& kingMove, Move const& rookMove) const;
    [[nodiscard]] bool isEndpointEmptyOrHaveDifferentColors(Move const& move) const;
    [[nodiscard]] bool isThereNoPieceInBetween(Move const& move) const;
    [[nodiscard]] bool isSafeToCastleInBetween(Coordinate const& startpoint, Coordinate const& endpoint) const;
    void retrieveMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrievePawnMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveKnightMovesThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveBishopMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveRookMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveQueenMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveKingMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrievePawnNonCapturesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrievePawnCapturesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveDiagonalMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveStraightMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveKingOneStepMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveKingCastlingMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveCastlingMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;

    void retrieveMovesFromThisByIncrementingDelta(
        Moves& result, Coordinate const& startpoint, Coordinate const& delta, int const maxSize) const;

    void retrieveMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrieveAttacksToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrieveAttacksToThisWithNoKingMoves(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrievePawnReverseNonCapturesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrievePawnReverseCapturesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrievePawnEnPassantReverseToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrieveAllNonPawnMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrieveKnightMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrieveDiagonalMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrieveStraightMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrieveKingOneStepMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    void retrievePawnAttackDefendCountToThis(AttackDefendCount& count, Coordinate const& endpoint) const;
    void retrieveKnightAttackDefendCountToThis(AttackDefendCount& count, Coordinate const& endpoint) const;

    void retrieveDiagonalAttackDefendCountToThis(
        AttackDefendCount& bishopCount, AttackDefendCount& queenCount, Coordinate const& endpoint) const;

    void retrieveStraightAttackDefendCountToThis(
        AttackDefendCount& rookCount, AttackDefendCount& queenCount, Coordinate const& endpoint) const;

    void retrieveQueenAttackDefendCountToThis(AttackDefendCount& count, Coordinate const& endpoint) const;
    void retrieveKingOneStepAttackDefendCountToThis(AttackDefendCount& count, Coordinate const& endpoint) const;
    void changePieceGridWithMove(Move const& move);

    static void updateAttackDefendCount(
        Board::AttackDefendCount& count, PieceColor const pieceColor, PieceColor const sameColor,
        PieceColor const oppositeColor);

    static CastleType getCastleTypeWithAlgebraicNotation(std::string const& textInAlgebraicNotation);
    static Coordinate getCoordinateFromGridIndex(int const gridIndex);
    static CoordinateDataType reverse(CoordinateDataType const value);
    static CoordinateDataType getOneIncrement(CoordinateDataType const coordinateDataType);
    static Coordinates getLDeltaCoordinates();
    static Coordinates getDiagonalIncrementDeltaCoordinates();
    static Coordinates getStraightIncrementDeltaCoordinates();
    static Coordinates getOneStepDeltaCoordinates();
    static PieceGrid getInitialValues(BoardOrientation const& inputType);
    static int getGridIndex(int const x, int const y);
    static bool isPieceEmptyOrHasOpposingColors(Piece const& piece, PieceColor const color);
    static bool isPieceNonEmptyAndHasOpposingColors(Piece const& piece, PieceColor const color);
    static bool isADiagonalMove(Move const& move);
    static bool isAStraightMove(Move const& move);
    static bool isAnLMove(Move const& move);
    static bool isAOneStepMove(Move const& move);

    static bool doesAllCellsInBetweenSatisfyTheCondition(
        Coordinate const& startpoint, Coordinate const& endpoint, CoordinateCondition const& condition);

    BoardOrientation m_orientation;
    PieceGrid m_pieceGrid;
};

}  // namespace alba::chess
