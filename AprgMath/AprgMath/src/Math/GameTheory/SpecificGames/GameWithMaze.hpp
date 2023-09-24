#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

#include <map>

namespace alba::math {

class GameWithMaze {
public:
    // As an example, consider a game where the players move a figure in a maze.
    // Each square in the maze is either floor or wall.
    // On each turn, the player has to move the figure some number of steps left or up.
    // The winner of the game is the player who makes the last move.
    using GrundyNumberEntry = int;
    using GrundyNumberMatrix = matrix::AlbaMatrix<GrundyNumberEntry>;
    using BooleanMatrix = matrix::AlbaMatrix<bool>;
    using Coordinate = std::pair<int, int>;
    using Coordinates = std::vector<Coordinate>;
    explicit GameWithMaze(BooleanMatrix const& isBlockedMatrix);
    [[nodiscard]] bool hasNoMoves(Coordinate const& coordinate) const;
    Coordinate getOptimalNextCoordinateAt(Coordinate const& coordinate);

    Coordinate getNextCoordinateWithGrundyNumber(
        Coordinate const& coordinate, UnsignedInteger const& targetGrundyNumber);

    GameState getGameStateAt(Coordinate const& coordinate);
    UnsignedInteger getGrundyNumberAt(Coordinate const& coordinate);
    std::string getString();
    static constexpr GrundyNumberEntry INVALID_GRUNDY_NUMBER = -1;

private:
    [[nodiscard]] Coordinates getNextCoordinates(Coordinate const& coordinate) const;
    void retrieveLeftCoordinates(Coordinates& retrievedCoordinates, Coordinate const& coordinate) const;
    void retrieveUpCoordinates(Coordinates& retrievedCoordinates, Coordinate const& coordinate) const;
    SetOfUnsignedIntegers getNextGrundyNumbers(Coordinate const& coordinate);
    BooleanMatrix const& m_isBlockedMatrix;
    GrundyNumberMatrix m_grundyNumberMatrix;  // dynamic programming
};

}  // namespace alba::math
