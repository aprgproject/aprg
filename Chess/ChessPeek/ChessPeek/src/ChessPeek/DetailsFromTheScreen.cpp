#include "DetailsFromTheScreen.hpp"

#include <ChessPeek/Utilities.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba::chess::ChessPeek {

DetailsFromTheScreen::DetailsFromTheScreen(Configuration const& configuration)
    : m_configuration(configuration),
      m_screenMonitoring(),
      m_boardObserver(m_configuration, m_screenMonitoring),

      m_savedPlayerColor{},
      m_savedOrientation{},
      m_countOfPieces{} {}

BoardWithContext const& DetailsFromTheScreen::getBoardWithContext() const { return m_boardWithContext; }

bool DetailsFromTheScreen::canAnalyzeBoard() const {
    return areKingsValid() && !m_boardWithContext.isOpponentsKingOnCheck();
}

void DetailsFromTheScreen::saveDetailsFromTheScreen() {
    m_screenMonitoring.capturePixelsFromScreen();
    Board temporaryBoard(getBoardAndSaveDetails());

    savePlayerColorAndOrientation();
    temporaryBoard.setOrientation(m_savedOrientation);

    m_boardWithContext.save(m_savedPlayerColor, temporaryBoard);
}

bool DetailsFromTheScreen::areKingsValid() const {
    return m_countOfPieces.numberOfWhiteKings == 1 && m_countOfPieces.numberOfBlackKings == 1;
}

void DetailsFromTheScreen::saveBoardDetails(Coordinate const& coordinate, Piece const& piece) {
    m_countOfPieces.pieceCount++;
    saveBoardKingDetails(coordinate, piece);
    saveBoardUpperHalfAndLowerHalfDetails(coordinate, piece);
}

void DetailsFromTheScreen::saveBoardKingDetails(Coordinate const& coordinate, Piece const& piece) {
    if (PieceType::King == piece.getType()) {
        if (PieceColor::White == piece.getColor()) {
            m_countOfPieces.numberOfWhiteKings++;
            m_countOfPieces.whiteKingCoordinate = coordinate;
        } else if (PieceColor::Black == piece.getColor()) {
            m_countOfPieces.numberOfBlackKings++;
            m_countOfPieces.blackKingCoordinate = coordinate;
        }
    }
}

void DetailsFromTheScreen::saveBoardUpperHalfAndLowerHalfDetails(Coordinate const& coordinate, Piece const& piece) {
    if (coordinate.getY() <= 3) {
        if (PieceColor::White == piece.getColor()) {
            m_countOfPieces.whiteCountInUpperHalf++;
        } else if (PieceColor::Black == piece.getColor()) {
            m_countOfPieces.blackCountInUpperHalf++;
        }
    } else {
        if (PieceColor::White == piece.getColor()) {
            m_countOfPieces.whiteCountInLowerHalf++;
        } else if (PieceColor::Black == piece.getColor()) {
            m_countOfPieces.blackCountInLowerHalf++;
        }
    }
}

void DetailsFromTheScreen::savePlayerColorAndOrientation() {
    if (m_configuration.getType() == Configuration::Type::ChessDotComExplorer) {
        // its always from white POV
        savePlayerColor(PieceColor::White);
        saveOrientationOnLowerHalfColor(PieceColor::White);
    } else if (m_configuration.getType() == Configuration::Type::ChessDotComPuzzle) {
        savePlayerColorIfChessDotComPuzzle();
    } else if (m_configuration.getType() == Configuration::Type::LichessStream) {
        savePlayerColorIfLichessStream();
    } else {
        savePlayerColorAndOrientationFromBoardDetails();
    }
}

void DetailsFromTheScreen::savePlayerColorIfChessDotComPuzzle() {
    auto intensity = calculateColorIntensityDecimal(m_screenMonitoring.getColorAt(3337, 137));
    if (intensity < m_configuration.getBlackColorLimit()) {
        saveOrientationOnLowerHalfColor(PieceColor::Black);
        savePlayerColor(PieceColor::Black);
    } else if (intensity > m_configuration.getWhiteColorLimit()) {
        saveOrientationOnLowerHalfColor(PieceColor::White);
        savePlayerColor(PieceColor::White);
    }
}

void DetailsFromTheScreen::savePlayerColorIfLichessStream() {
    constexpr auto xForWhiteSection = 3387;
    constexpr auto xForBlackSection = 3553;
    constexpr auto lastMovePixelColor = 0x2A4053U;
    constexpr auto rgbMask = 0xFFFFFFU;
    for (auto yCoordinate = 897; yCoordinate >= 199; yCoordinate -= 1) {
        auto pixelColorInWhiteSection = m_screenMonitoring.getColorAt(xForWhiteSection, yCoordinate) & rgbMask;
        auto pixelColorInBlackSection = m_screenMonitoring.getColorAt(xForBlackSection, yCoordinate) & rgbMask;
        if (lastMovePixelColor == pixelColorInWhiteSection) {
            savePlayerColor(PieceColor::Black);
            break;
        }
        if (lastMovePixelColor == pixelColorInBlackSection) {
            savePlayerColor(PieceColor::White);
            break;
        }
    }
}

void DetailsFromTheScreen::savePlayerColorAndOrientationFromBoardDetails() {
    constexpr int MIN_PIECE_COUNT_TO_CONSIDER = 12;
    if (m_countOfPieces.pieceCount >= MIN_PIECE_COUNT_TO_CONSIDER) {
        PieceColor lowerHalfColor{};
        if (m_countOfPieces.whiteCountInLowerHalf > m_countOfPieces.blackCountInLowerHalf &&
            m_countOfPieces.blackCountInUpperHalf > m_countOfPieces.whiteCountInUpperHalf &&
            isInLowerHalf(m_countOfPieces.whiteKingCoordinate) && isInUpperHalf(m_countOfPieces.blackKingCoordinate)) {
            lowerHalfColor = PieceColor::White;
        } else if (
            m_countOfPieces.blackCountInLowerHalf > m_countOfPieces.whiteCountInLowerHalf &&
            m_countOfPieces.whiteCountInUpperHalf > m_countOfPieces.blackCountInUpperHalf &&
            isInLowerHalf(m_countOfPieces.blackKingCoordinate) && isInUpperHalf(m_countOfPieces.whiteKingCoordinate)) {
            lowerHalfColor = PieceColor::Black;
        }

        if (PieceColor::Unknown != lowerHalfColor) {
            saveOrientationOnLowerHalfColor(lowerHalfColor);
            savePlayerColor(lowerHalfColor);
        }
    }
}

void DetailsFromTheScreen::saveOrientationOnLowerHalfColor(PieceColor const lowerHalfColor) {
    if (PieceColor::White == lowerHalfColor) {
        saveOrientation(BoardOrientation::BlackUpWhiteDown);
    } else if (PieceColor::Black == lowerHalfColor) {
        saveOrientation(BoardOrientation::WhiteUpBlackDown);
    }
}

void DetailsFromTheScreen::savePlayerColor(PieceColor const playerColor) { m_savedPlayerColor = playerColor; }
void DetailsFromTheScreen::saveOrientation(BoardOrientation const orientation) { m_savedOrientation = orientation; }

Board DetailsFromTheScreen::getBoardAndSaveDetails() {
    Board board;
    m_countOfPieces = {};
    for (int j = 0; j < Board::CHESS_SIDE_SIZE; ++j) {
        for (int i = 0; i < Board::CHESS_SIDE_SIZE; ++i) {
            Coordinate const coordinate(i, j);
            Piece const piece(m_boardObserver.getPieceFromCell(i, j));
            board.setPieceAt(coordinate, piece);
            if (!piece.isEmpty()) {
                saveBoardDetails(coordinate, piece);
            }
        }
    }
    return board;
}

}  // namespace alba::chess::ChessPeek
