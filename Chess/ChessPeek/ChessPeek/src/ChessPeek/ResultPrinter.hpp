#pragma once

#include <ChessPeek/BoardWithContext.hpp>
#include <ChessPeek/Book.hpp>
#include <ChessPeek/CalculationDetails.hpp>
#include <ChessPeek/HumanScoreGenerator.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

namespace alba::chess::ChessPeek {

class ResultPrinter {
public:
    enum class MoveType { BookMove, CalculatedMove };

    struct NextMove {
        Move move;
        std::string moveString;
        int mateValue;
        int engineScore;
        HumanScoreGenerator::Score humanScore;
    };

    using NextMoves = std::vector<NextMove>;

    struct MovesSequence {
        int mateValue;
        int engineScore;
        HumanScoreGenerator::Score humanScore;
        std::vector<Move> halfMoves;
    };

    struct BookMove {
        Move move;
        std::string nameOfLineInBook;
        int winningPercentageInBook;
    };

    using BookMoves = std::vector<BookMove>;

    struct MovesToPrint {
        BookMoves bookMoves;
        NextMoves calculatedMoves;
        NextMoves mostHumanMoves;
        MovesSequence bestLine;
        MovesSequence mostHumanLine;
    };

    using ScorePair = std::pair<int, int>;
    ResultPrinter() = delete;
    ResultPrinter(CalculationDetails const& calculationDetails, BoardWithContext const& engineBoard, Book const& book);
    void print();

private:
    void printCalculationDetails(MovesToPrint const& movesToPrint) const;
    void printMovesGrids(MovesToPrint const& movesToPrint) const;

    template <typename GenericMoves>
    void printARowOfNextMoves(GenericMoves const& genericMoves, int const startIndex) const;

    template <typename GenericMoves>
    void setNextMovesOnGrid(
        DisplayTable& grid, GenericMoves const& genericMoves, int const startIndex, int const rowSize) const;

    [[nodiscard]] BookMove createBookMove(
        Move const& move, Book::LineDetail const& lineDetail, Book::MoveDetail const& bookMoveDetail) const;

    [[nodiscard]] BookMoves getMovesFromBook() const;
    [[nodiscard]] MovesSequence getMovesSequenceFromMoveString(std::string const& moveString) const;
    [[nodiscard]] NextMove createNextMove(Move const& move, Variation const& variation) const;
    [[nodiscard]] NextMoves getNextMovesFromCalculation() const;
    [[nodiscard]] std::string getNameOfBookMove(Move const& move, Book::LineDetail const& lineDetail) const;
    void printARowOfMovesSequence(MovesSequence const& movesSequence) const;
    void setMovesSequenceOnGrid(DisplayTable& grid, MovesSequence const& movesSequence, int const rowSize) const;

    void printHeadersForNextMoves(
        NextMoves const& nextMoves, int const startIndex, stringHelper::strings const& suffixHeaders) const;

    void printHeadersForBookMoves(BookMoves const& bookMoves) const;
    void printHeadersForBestLine(MovesSequence const& movesSequence, stringHelper::strings const& suffixHeaders) const;
    void printHorizontalBorder() const;
    void fillMovesFromBook(BookMoves& bookMoves) const;
    void fillNextMovesFromCalculation(NextMoves& nextMoves) const;
    void humanizeMoves(NextMoves& nextMoves) const;
    void removeTooManyPawnMoves(NextMoves& nextMoves) const;
    void fillMovesSequenceFromVariation(MovesSequence& result, Variation const& variation) const;
    [[nodiscard]] static ScorePair getBestAndWorstScores(Variations const& variations);

    [[nodiscard]] static std::optional<char> getFirstCharOfABoardCell(
        bool const isCertainPreMove, bool const isPossiblePreMove);

    [[nodiscard]] static std::string getDisplayableString(NextMove const& nextMove);
    [[nodiscard]] static std::string getDisplayableString(MovesSequence const& movesSequence);
    [[nodiscard]] static std::string getDisplayableString(BookMove const& bookMove);

    [[nodiscard]] static std::string getDisplayableString(
        int const mateValue, int const engineScore, HumanScoreGenerator::Score const humanScore);

    [[nodiscard]] static std::string getDisplayableString(int const mateValue, int const engineScore);
    [[nodiscard]] static std::string formatToHeaderString(std::string const& content);

    [[nodiscard]] static std::string getDisplayableStringForABoardCell(
        Piece const& piece, int const moveNumber, std::optional<char> const& firstChar);

    [[nodiscard]] static stringHelper::strings getNextMovesString(NextMoves const& nextMoves, int const startIndex);
    [[nodiscard]] static stringHelper::strings getBookMovesString(BookMoves const& bookMoves);
    [[nodiscard]] static int getNumberOfColumnsOfGrid(int const numberOfBoards);
    [[nodiscard]] static int getHorizontalBorderSize(int const numberOfBoards);
    [[nodiscard]] static int getRowSizeForHalfMoves(int const numberOfHalfMoves);
    [[nodiscard]] static int getRowSizeForFullMoves(int const numberOfFullMoves);

    static void printHeaders(
        stringHelper::strings const& prefixHeaders, stringHelper::strings const& suffixHeaders, int const rowSize);

    static void setBoardOnGrid(DisplayTable& grid, Board const& board, int const xOffset);

    static void setMoveOnGrid(
        DisplayTable& grid, Board const& board, Move const& move, int const xOffset, int const moveNumber,
        std::optional<char> const& firstChar);

    static void setSeparatorsOnGrid(DisplayTable& grid, int const xOffset);
    static void sortForMoreHumanMoves(NextMoves& nextMoves);
    CalculationDetails const& m_calculationDetails;
    BoardWithContext const& m_engineBoardWithContext;
    Book const& m_book;
    ScorePair m_worstAndBestScorePair;
    HumanScoreGenerator m_humanScoreGenerator;
    std::string m_horizontalBorder;
};

}  // namespace alba::chess::ChessPeek
