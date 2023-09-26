#include "GameWithMaze.hpp"

#include <Math/GameTheory/Common/GameUtilities.hpp>

#include <sstream>

using namespace std;

namespace alba::math {

GameWithMaze::GameWithMaze(BooleanMatrix const& isBlockedMatrix)
    : m_isBlockedMatrix(isBlockedMatrix),
      m_grundyNumberMatrix(
          isBlockedMatrix.getNumberOfColumns(), isBlockedMatrix.getNumberOfRows(), INVALID_GRUNDY_NUMBER) {}

bool GameWithMaze::hasNoMoves(Coordinate const& coordinate) const {
    Coordinate const oneLeft(coordinate.first - 1, coordinate.second);
    Coordinate const oneUp(coordinate.first, coordinate.second - 1);
    bool const isLeftNotAllowed = !m_isBlockedMatrix.isInside(oneLeft.first, oneLeft.second) ||
                                  m_isBlockedMatrix.getEntry(oneLeft.first, oneLeft.second);
    bool const isUpAllowed =
        !m_isBlockedMatrix.isInside(oneUp.first, oneUp.second) || m_isBlockedMatrix.getEntry(oneUp.first, oneUp.second);
    return isLeftNotAllowed && isUpAllowed;
}

GameWithMaze::Coordinate GameWithMaze::getOptimalNextCoordinateAt(Coordinate const& coordinate) {
    Coordinate result{};
    GameState const gameState = getGameStateFromGrundyNumber(getGrundyNumberAt(coordinate));
    if (GameState::Losing == gameState) {
        Coordinate const oneLeft(coordinate.first - 1, coordinate.second);
        Coordinate const oneUp(coordinate.first, coordinate.second - 1);
        if (m_isBlockedMatrix.isInside(oneLeft.first, oneLeft.second) &&
            !m_isBlockedMatrix.getEntry(oneLeft.first, oneLeft.second)) {
            // move one left if possible to prolong the game
            result = oneLeft;
        } else if (
            m_isBlockedMatrix.isInside(oneUp.first, oneUp.second) &&
            !m_isBlockedMatrix.getEntry(oneUp.first, oneUp.second)) {
            // move one top if possible to prolong the game
            result = oneUp;
        }
    } else if (GameState::Winning == gameState) {
        for (Coordinate const& nextCoordinate : getNextCoordinates(coordinate)) {
            // cppcheck-suppress useStlAlgorithm
            if (0U == getGrundyNumberAt(nextCoordinate)) {
                // force your opponent to losing state
                result = nextCoordinate;
                break;
            }
        }
    }
    return result;
}

GameWithMaze::Coordinate GameWithMaze::getNextCoordinateWithGrundyNumber(
    Coordinate const& coordinate, UnsignedInteger const& targetGrundyNumber) {
    Coordinate result{};
    for (Coordinate const& nextCoordinate : getNextCoordinates(coordinate)) {
            // cppcheck-suppress useStlAlgorithm
        if (targetGrundyNumber == getGrundyNumberAt(nextCoordinate)) {
            result = nextCoordinate;
            break;
        }
    }
    return result;
}

GameState GameWithMaze::getGameStateAt(Coordinate const& coordinate) {
    return getGameStateFromGrundyNumber(getGrundyNumberAt(coordinate));
}

UnsignedInteger GameWithMaze::getGrundyNumberAt(Coordinate const& coordinate) {
    UnsignedInteger result{};
    if (!m_isBlockedMatrix.getEntry(coordinate.first, coordinate.second)) {
        GrundyNumberEntry const grundyNumberEntry = m_grundyNumberMatrix.getEntry(coordinate.first, coordinate.second);
        if (grundyNumberEntry != INVALID_GRUNDY_NUMBER) {
            result = static_cast<UnsignedInteger>(grundyNumberEntry);
        } else {
            result = getGrundyNumber(getNextGrundyNumbers(coordinate));
            m_grundyNumberMatrix.setEntry(coordinate.first, coordinate.second, static_cast<GrundyNumberEntry>(result));
        }
    }
    return result;
}

string GameWithMaze::getString() {
    DisplayTable table;
    table.setBorders("-", "|");
    for (int y = 0; y < static_cast<int>(m_isBlockedMatrix.getNumberOfRows()); ++y) {
        table.addRow();
        for (int x = 0; x < static_cast<int>(m_isBlockedMatrix.getNumberOfColumns()); ++x) {
            stringstream ss;
            if (m_isBlockedMatrix.getEntry(x, y)) {
                ss << "X";
            } else {
                ss << getGrundyNumberAt(Coordinate(x, y));
            }
            table.getLastRow().addCell(ss.str());
        }
    }
    stringstream ss;
    ss << "Matrix output:\n" << table;
    return ss.str();
}

GameWithMaze::Coordinates GameWithMaze::getNextCoordinates(Coordinate const& coordinate) const {
    Coordinates result;
    if (m_isBlockedMatrix.isInside(coordinate.first, coordinate.second)) {
        retrieveLeftCoordinates(result, coordinate);
        retrieveUpCoordinates(result, coordinate);
    }
    return result;
}

void GameWithMaze::retrieveLeftCoordinates(Coordinates& retrievedCoordinates, Coordinate const& coordinate) const {
    for (int x = coordinate.first - 1; x >= 0; --x) {
        Coordinate const xyToCheck(x, coordinate.second);
        if (!m_isBlockedMatrix.getEntry(xyToCheck.first, xyToCheck.second)) {
            retrievedCoordinates.emplace_back(xyToCheck);
        } else {
            break;
        }
    }
}

void GameWithMaze::retrieveUpCoordinates(Coordinates& retrievedCoordinates, Coordinate const& coordinate) const {
    for (int y = coordinate.second - 1; y >= 0; --y) {
        Coordinate const xyToCheck(coordinate.first, y);
        if (!m_isBlockedMatrix.getEntry(xyToCheck.first, xyToCheck.second)) {
            retrievedCoordinates.emplace_back(xyToCheck);
        } else {
            break;
        }
    }
}

SetOfUnsignedIntegers GameWithMaze::getNextGrundyNumbers(Coordinate const& coordinate) {
    SetOfUnsignedIntegers result;
    Coordinates const nextCoorindates(getNextCoordinates(coordinate));
    transform(
        nextCoorindates.cbegin(), nextCoorindates.cend(), inserter(result, result.begin()),
        [&](Coordinate const& nextCoordinate) { return getGrundyNumberAt(nextCoordinate); });
    return result;
}

}  // namespace alba::math
