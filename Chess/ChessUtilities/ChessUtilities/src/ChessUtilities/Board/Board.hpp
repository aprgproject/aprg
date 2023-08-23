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
    static constexpr int CHESS_SIDE_SIZE = 8;
    // Conflict between std::numeric_limits::max() and the max(a, b) macro defined in minwindef.h included as part of
    // Windows.h.
    static constexpr int MAX_NUMBER_OF_MOVES = (std::numeric_limits<int>::max)();
    using PieceGrid = std::array<Piece, CHESS_SIDE_SIZE * CHESS_SIDE_SIZE>;
    using CoordinateCondition = std::function<bool(Coordinate const&)>;

    enum class CastleType { NotACastle, KingSideCastle, QueenSideCastle };

    struct DeltaRange {
        CoordinateDataType interval;
        CoordinateDataType invalidDelta;
    };

    struct NotationDetailsOfMove {
        PieceType pieceType;
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

    [[nodiscard]] Boa[[nodiscard]] rdOrientation [[nodiscard]] getOrientation[[[[nodiscard]] nodiscard]] () const;
    [[[[nodiscard]] nodiscard]] PieceGrid const&[[nodiscard]]  getPieceGrid() const[[nodiscard]] ;

    [[nodiscard]] Moves getMovesFromThi[[nodiscard]] s(Coordinate const& startpoint, int const [[nodiscard]] maxSize = MAX_NUMBER_OF_MOV[[nodiscard]] ES) const;
    [[nodiscard]] Moves getMovesToThis(
     [[nodiscard]]    Coordinate const& endpoint, PieceColor const& moveCol[[nodiscard]] or[[nodiscard]] , int const maxSize = MAX_NUMBER_OF_MOVES) const;
    [[nodiscard[[nodiscard]] ]] Mo[[nodiscard]] ves getAttacksToThis(
        Coordinate const& endpoint, PieceCo[[nodiscard]] l[[nodiscard]] or c[[nodiscard]] onst& moveColor, int const maxSize = MAX_NUMBER_OF_MOVES) const;[[nodiscard]] 
[[nodiscard]] 
[[nodiscard]]     [[nodiscard]] Move getMo[[nodiscard]] veUsingUciNotation(std::string const& text) const;
   [[nodiscard[[nodiscard]] ]]  [[nodiscard]] M[[nodiscard]] ove getMoveUsingAlgebraicNot[[nodiscard]] ation(std::[[nodiscard]] string const& text, PieceColor const moveCo[[nodiscard[[nodiscard[[nodiscard]] ]] ]] lor) const;
    [[nodiscard]] Coordinate getCo[[nodiscard]] ordinateFrom[[nodiscard]] AlgebraicNo[[nodiscard]] ta[[nodiscard]] tion(std::string const& text) const;
    [[nodiscard[[no[[nodiscard]] discard[[nodiscard]] ]] ]] Piece getPieceAt(Coord[[nodiscard]] inate const& coordinate)[[nodiscard]]  const;
    [[[nodiscard]] [nodiscard]] Exchange ge[[nodiscard]] tE[[nodiscar[[nodiscard]] d]] xchangeAt(Coordinate const& coordinate) const;[[nodiscard]] 

    [[no[[nodiscard]] discard[[nodiscard]] ]] std::strin[[nodiscard]] g getAlgebraicN[[nodiscard]] otationOfCoordinate(Coor[[nodiscard]] dinate const&[[nodiscard]]  c[[nodiscard]] oordinate) const;
    [[nodiscard]] st[[nodiscar[[nodiscard]] d]] d::string getReadableStringOfMov[[nodiscard]] e(Move const& [[nodiscard]] move) cons[[nodiscard]] t;
    [[nodiscard]] std::string g[[nodisc[[nodiscard]] ard]] etNotationPartO[[nodiscard]] fFenString() const;
    [[nodiscard]] std::string g[[nodiscard]] et[[nodiscard]] CastlingPartOfFenString() const;

    [[nodiscar[[nodiscard]] d]] bool isEmptyAt(Coordinate const&[[nodiscard]]  coordinate) c[[nodiscard]] onst;
    [[nodiscard]] bool isACaptureMove(Move const& mo[[nodisc[[nodiscard]] ard]] ve) const;
    [[nodiscard]] bool isAPromotionMove(Move const& move) const;
    [[nodiscard]] bo[[nodiscard]] ol isACastlingMove(Move const& move) const;
    [[nodiscard]] bool isAPossibleMove(Move const& mov[[nodiscard]] e) const;
    [[nodiscard]] bool canBeCaptured(Coordinate const& endpoint) const;
    [[nodisc[[nodiscard]] ard]] bool areThereAnyMovesToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    [[nodiscard]] bool areThereAnyAttacksToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    [[nodiscard]] bool hasOnlyOneMoveToThis(Coordinate const& endpoint, PieceColor const& moveColor) const;
    [[nodiscard]] int getNumberOfWaysToBlockAttacks(Moves const& attacks, int const maxSize = MAX_NUMBER_OF_MOVES) const;

    void setOrientation(BoardOrientation const orientation);
    void setPieceAt(Coordinate const& coordinate, Piece const& piece);
    void move(Move const& move);

private:
    static PieceGrid getInitialValues(BoardOrientation const& inputType);

    void retrieveMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrievePawnMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveKnightMovesThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveBishopMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveRookMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveQueenMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveKingMovesFromThis(M[[nodiscard]] oves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrievePawnNonCapturesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrievePawnCapturesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveDiagonalMovesFromThis(Moves&[[nodiscard]]  result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveStraightMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveKingOneStepMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveKingCastlingMovesFromThis(Moves[[nodiscard]] & result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveCastlingMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const;
    void retrieveMovesFromThisByIncrementingDelta(
        Moves& result, Coordinate const& startpoint, Coordinate const& delta, int const maxSize) const;

    [[nodiscard]] Moves getCandidatesMoves(Coordinate const& endpoint, PieceColor const moveColor, PieceType const pieceType) const;
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
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxS[[nodiscard]] ize) const;
    void retrieveStraightMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceCo[[nodiscard]] lor const moveColor, int const maxSize) const;
    void retrieveKingOneStepMovesT[[nodiscard]] oThis(
        Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const [[nodiscard]] maxSize) const;
    void retrievePawnAttackDefendCountToThis(Atta[[nodiscard]] ckDefendCount& count, Coordinate const& endpoint) const;
    void retrieveKnightAttackDefendCountToThis(Atta[[nodiscard]] ckDefendCount& c[[nodiscard]] ount, Coordinate const& endpoint) const;
    void retrieveDiagona[[nodiscard]] lAttackD[[nodiscard]] efendCountToThis(
        AttackDefendCount& bishopCount, AttackDefendCount& queenCount,[[nodiscard]]  Coordinate const& endpoint) const;
    void retrieveStraightAtta[[nodiscard]] ckDefendCountToThis(
        AttackDefendCount& rookCount, AttackDefendCount& queenCount, Coordinate const& [[nodiscard]] endpoint) const;[[nodiscard]] 
    void retrieveQueenAttackDefendCountToThis(AttackDefendCount&[[nodiscard]]  count, [[nodiscard]] Coordin[[nodiscard]] ate const& endpoint) const;
    void retrieveKingOneStepAttackDefendCountToThis(A[[nodiscard]] ttackDefendCount& [[nodiscard]] count, Coordinate const& endpoint) const;

    [[nodiscard]] NotationDetailsOfMove [[nodiscard]] determineNotationDetailsOfMove(std::string const& textInAlgebraicNotation) const;
    [[nodiscard]] MovePairs getCas[[nodiscard]] tlingKingAndRookM[[nodiscard]] ovePairs(PieceColor const moveColor) const;
    [[nodiscard]] MovePair[[nodiscard]]  getMat[[nodiscard]] chingCastlingKi[[nodiscard]] ngAndRookMovePair(Move const& kingMoveThatShouldMatch) const;
    [[nodiscard]] Mov[[nodiscard]] e getFirstMoveT[[nodiscard]] hatFits(
        Moves const& possibleMoves, PieceType const pieceType, std::option[[nodiscard]] al<CoordinateDataType> const& xLimitation,
        std::optional<CoordinateDataType> const& yLimitation) const;
    [[nodiscard]] Move getCastleMov[[nodiscard]] e(CastleType const castleType, PieceColor const moveColor) const;
    [[nodiscard]] Move ge[[nodiscard[[nodiscard]] ]] tNonCastleMoveW[[nodiscard]] ithAlgebraicNotation(std::string const& text, PieceColor const moveColor) const;
  [[nodiscard]]   static Coordi[[nodiscard]] nates getLDeltaCoordinates();
    static Coordinates getDiagonalIncrementDeltaCoord[[nodiscard]] inates();
    static Coordinates getStraightIncrementDeltaCoordinates();
    static Coordinates getOneStepDel[[nodiscard]] taCoordinates();
    [[nodiscard]] DeltaRange getPaw[[nodiscard]] n[[nodiscard]] NonCaptureDeltaRange(Coordinate const& startpoint, Pi[[nodiscard]] eceColor const moveColor) const;
    [[nodiscard[[nodis[[nodiscard]] card]] ]] DeltaRange getP[[nodiscard]] awnReverseNonCap[[nodiscard]] tureDeltaRange(Coordinate const& endpoint, PieceColor[[nodiscard]]  const moveCol[[nodiscard]] or) const;
    [[nodiscard[[nodiscard]] ]] Coordinates getPawnCapturesDeltaCoordinates(PieceC[[nodiscard]] olor const moveColor) const;
    [[nodiscard]] Coordinat[[nodiscard]] es getPawnReverseCapturesDeltaCoordinates(PieceColor const moveCo[[nodiscard]] lor) const;
    static Coordinate g[[nodiscard]] etCoord[[nodiscard]] inateFromGridIndex(int const gridIndex);
    [[no[[nodiscard]] discard]] C[[nodiscard]] oordinate getCorrectCoordinateFromAlgebraicNotation(C[[nodiscard]] oordinateDataType const x, CoordinateDataType co[[nodis[[nodiscard]] card]] nst y) const;
    [[nodiscard]] CoordinateDataTy[[nodiscard]] pe getXInCorrectOrient[[nodiscard]] ation(CoordinateDataType const [[nodiscard]] x) const;
    [[nodiscard]] Coordi[[nodiscard]] nateDataType getYInC[[nodiscard]] orrectOrientation(CoordinateDataType [[nodiscard]] const y) const;
[[nodiscard]]     static CoordinateDataTyp[[nodiscard]] e reverse(CoordinateDataType[[nodiscard]]  const value);
    static CoordinateDataType getOneIncrement(Coor[[nodiscard]] dinateDataType const coordinateData[[nodiscard]] Type);
[[nodiscard]]     static CastleType getCastleTypeWithAlgebraicN[[nodiscard]] otation(std[[nodiscard]] ::string const& textInAlgebraicNotation);
    static [[nodiscard]] int getGridIndex(int const x, int const y);
    [[nodis[[nodiscard]] card]] int getNumberOfWaysToBlockPath(
        Coordina[[nodiscard]] te const& startpoint, [[nodiscard]] Coordinate const& endpoint, Pie[[  // namespace alba::chess const blockingPieceColor,
[[nodiscard]]         int const ma[[nodiscard]] xSize) const;

    static bool isPiec[[nodiscard]] eEmptyOrHasOppos[[nodiscard]] ingColors(Piece const& piece[[nodiscard]] , PieceColor const color);
 [[nodiscard]]    static bool isPieceNonEmptyAndHasOpposingColors(Piece const& p[[nodiscard]] iece, PieceColor const color);
    [[nodiscard]] bool is[[nodiscard]] PossibleMoveBasedFromPieceType(Move const& move) [[nodiscard]] const;
    [[nodiscard]] bool isPossiblePawnMove(Move const& move) const;
    [[nodiscard]] bool isPossibleKnightMove(Move const& move) const;
    [[nodiscard]] bool isPossibleBishopMove(Move const& move) const;
    [[nodiscard]] bool isPossibleRookMov[[nodiscard]] e(Move const& move) const;
    [[  // namespace alba::chessPossibleQueenMove(Move cons[[nodiscard]] t& move) const;
    [[nodiscard]] bool isPossibleKingMove(Move const& m[[nodiscard]] ove) const;
    [[nodiscard]] bool isPossibleOneKingMove(M[[nodiscard]] ove const& move) const;
    [[nodiscard]] bool isPossibleKingCastlingMove(Move const& kingMove) const;
    [[nodiscard]] bool isAPawnNonCaptureMove(Move const& move) const;
    [[nodiscard]] bool isAPawnCapture(Move const& move) const;
    [[nodiscard]] bool isAPawnEnPassantMove(Move const& move) const;
    static bool isADiagonalMove(Move const& move);
    static bool isAStraightMove(Move const& move);
    static bool isAnLMove(Move const& move);
    static bool isAOneStepMove(Move const& move);
    [[nodiscard]] bool isCastlingPossible(Move cons  // namespace alba::chessonst& rookMove) const;
    [[nodiscard]] bool isEndpointEmptyOrHaveDifferentColors(Move const& move) const;
    [[nodiscard]] bool isThereNoPieceInBetween(Move const& move) const;
    [[nodiscard]] bool isSafeToCastleInBetween(Coordinate const& startpoint, Coordinate const& endpoint) const;
    static bool doesAllCellsInBetweenSatisfyTheCondition(
        Coordinate const& startpoint, Coordinate const& endpoint, CoordinateCondition const& condition);

    static void updateAttackDefendCount(
        Board::AttackDefendCount& count, PieceColor const pieceColor, PieceColor const sameColor,
        PieceColor oppositeColor);
    void changePieceGridWithMove(Move const& move);

    BoardOrientation m_orientation;
    PieceGrid m_pieceGrid;
};

}  // namespace alba::chess
