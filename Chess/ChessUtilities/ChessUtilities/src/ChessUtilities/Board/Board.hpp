#pragma once

#include <ChessUtilities/Board/BoardTypes.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <cstdint>
#include <functional>
#include <optional>

namespace alba {
namespace matrix {
template <>
bool isEqualForMathMatrixDataType(chess::Piece const& value1, chess::Piece const& value2);
}

namespace chess {

struct Board {
public:
    using PieceValue = uint16_t;
    using InitializerList = std::initializer_list<Piece>;
    using PieceMatrix = matrix::AlbaMatrix<Piece>;
    using CoordinateCondition = std::function<bool(Coordinate const&)>;

    enum class CastleType { NotACastle, KingSideCastle, QueenSideCastle };

    struct DeltaRange {
        CoordinateDataType interval;
        CoordinateDataType invalidDelta;
    };

    struct NotationDetailsOfMove {
        PieceType pieceType;
        std::optional<CoordinateDataType> firstX, firstY, secondX, secondY;
    };

    static constexpr int MAX_NUMBER_OF_MOVES = std::numeric_limits<int>::max();

    Board();
    Board(BoardOrientation const& orientation);
    Board(BoardOrientation const& orientation, InitializerList const& initializerList);

    bool operator==(Board const& other) const;
    bool operator!=(Board const& other) const;

    BoardOrientation getOrientation() const;
    PieceMatrix const& getPieceMatrix() const;

    Moves getMovesFromThis(Coordinate const& startpoint, int const maxSize = MAX_NUMBER_OF_MOVES) const;    Moves getMovesToThis(
        Coordinate const& endpoint, PieceColor const& moveColor, int const maxSize = MAX_NUMBER_OF_MOVES) const;
    Moves getAttacksToThis(
        Coordinate const& endpoint, PieceColor const& moveColor, int const maxSize = MAX_NUMBER_OF_MOVES) const;

    Move getMoveUsingUciNotation(std::string const& text) const;
    Move getMoveUsingAlgebraicNotation(std::string const& text, PieceColor const moveColor) const;
    Coordinate getCoordinateFromAlgebraicNotation(std::string const& text) const;
    Piece getPieceAt(Coordinate const& coordinate) const;

    std::string getAlgebraicNotationOfCoordinate(Coordinate const& coordinate) const;
    std::string getReadableStringOfMove(Move const& move) const;
    std::string getNotationPartOfFenString() const;
    std::string getCastlingPartOfFenString() const;
    bool isEmptyAt(Coordinate const& coordinate) const;
    bool isACaptureMove(Move const& move) const;
    bool isAPromotionMove(Move const& move) const;
    bool isACastlingMove(Move const& move) const;
    bool isAPossibleMove(Move const& move) const;
    bool canBeCaptured(Coordinate const& endpoint) const;
    bool areThereAnyMovesToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    bool areThereAnyAttacksToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    bool hasOnlyOneMoveToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    int getNumberOfWaysToBlockAttacks(Moves const& attacks, int const maxSize = MAX_NUMBER_OF_MOVES) const;

    void setOrientation(BoardOrientation const orientation);
    void setPieceAt(Coordinate const& coordinate, Piece const& piece);
    void move(Move const& move);

private:
    PieceMatrix::MatrixData getInitialValues(BoardOrientation const& inputType) const;

    void retrieveMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrievePawnMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;    void retrieveKnightMovesThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
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

    Moves getPossibleMovesForNotation(
        Coordinate const& endpoint, PieceColor const moveColor, PieceType const pieceType) const;
    void retrieveMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrieveAttacksToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrieveAttacksToThisWithNoKingMoves(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrievePawnReverseMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrievePawnReverseNonCapturesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrievePawnReverseCapturesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrieveAllNonPawnMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrieveKnightMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrieveDiagonalMovesToThis(        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrieveStraightMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;
    void retrieveKingOneStepMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const;

    NotationDetailsOfMove determineNotationDetailsOfMove(std::string const& text) const;

    MovePairs getCastlingKingAndRookMovePairs(PieceColor const moveColor) const;
    MovePair getMatchingCastlingKingAndRookMovePair(Move const& kingMoveThatShouldMatch) const;
    Move getFirstMoveThatFits(
        Moves const& possibleMoves, PieceType const pieceType, std::optional<CoordinateDataType> const& xLimitation,
        std::optional<CoordinateDataType> const& yLimitation) const;
    Move getCastleMoveUsingAlgebraicNotation(CastleType const castleType, PieceColor const moveColor) const;
    Move getNonCastleMoveUsingAlgebraicNotation(std::string const& text, PieceColor const moveColor) const;
    Coordinates getLDeltaCoordinates() const;
    Coordinates getDiagonalIncrementDeltaCoordinates() const;
    Coordinates getStraightIncrementDeltaCoordinates() const;    Coordinates getOneStepDeltaCoordinates() const;
    DeltaRange getPawnNonCaptureDeltaRange(Coordinate const& startpoint, PieceColor const moveColor) const;
    DeltaRange getPawnReverseNonCaptureDeltaRange(Coordinate const& endpoint, PieceColor const moveColor) const;
    Coordinates getPawnCapturesDeltaCoordinates(PieceColor const moveColor) const;
    Coordinates getPawnReverseCapturesDeltaCoordinates(PieceColor const moveColor) const;
    Coordinate getCoordinateInCorrectOrientation(CoordinateDataType const x, CoordinateDataType const y) const;
    CoordinateDataType getXInCorrectOrientation(CoordinateDataType const x) const;
    CoordinateDataType getYInCorrectOrientation(CoordinateDataType const y) const;
    CoordinateDataType reverse(CoordinateDataType const value) const;
    CoordinateDataType getOneIncrement(CoordinateDataType const coordinateDataType) const;
    CastleType getCastleTypeUsingAlgebraicNotation(std::string const& text) const;

    int getNumberOfWaysToBlockPath(
        Coordinate const& startpoint, Coordinate const& endpoint, PieceColor const blockingPieceColor,
        int const maxSize) const;
    bool isPossibleMoveBasedFromPieceType(Move const& move) const;
    bool isPossiblePawnMove(Move const& move) const;
    bool isPossibleKnightMove(Move const& move) const;
    bool isPossibleBishopMove(Move const& move) const;
    bool isPossibleRookMove(Move const& move) const;
    bool isPossibleQueenMove(Move const& move) const;
    bool isPossibleKingMove(Move const& move) const;
    bool isPossibleOneKingMove(Move const& move) const;
    bool isPossibleKingCastlingMove(Move const& kingMove) const;
    bool isAPawnNonCaptureMove(Move const& move) const;
    bool isAPawnCapture(Move const& move) const;
    bool isADiagonalMove(Move const& move) const;
    bool isAStraightMove(Move const& move) const;
    bool isAnLMove(Move const& move) const;
    bool isAOneStepMove(Move const& move) const;
    bool isCastlingPossible(Move const& kingMove, Move const& rookMove) const;
    bool isEndpointEmptyOrHaveDifferentColors(Move const& move) const;
    bool isThereNoPieceInBetween(Move const& move) const;
    bool isSafeToCastleInBetween(Coordinate const& startpoint, Coordinate const& endpoint) const;
    bool doesAllCellsInBetweenSatisfyTheCondition(
        Coordinate const& startpoint, Coordinate const& endpoint, CoordinateCondition const& condition) const;

    void changePieceMatrixWithMove(Move const& move);

    BoardOrientation m_orientation;
    PieceMatrix m_pieceMatrix;
};
}  // namespace chess

}  // namespace alba
