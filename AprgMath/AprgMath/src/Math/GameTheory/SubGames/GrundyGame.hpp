#pragma once

#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

#include <deque>
#include <map>
#include <tuple>

namespace alba::math {

class GrundyGame {
public:
    // An example of such a game is Grundy’s game.
    // Initially, there is a single heap that contains n sticks.
    // On each turn, the player chooses a heap and divides it into two nonempty heaps such that the heaps are of
    // DIFFERENT size. The player who makes the last move wins the game. Let f(n) be the Grundy number of a heap that
    // contains n sticks. The Grundy number can be calculated by going through all ways to divide the heap into two
    // heaps.
    using StickHeaps = std::deque<UnsignedInteger>;
    using SticksToGrundyNumberMap = std::map<UnsignedInteger, UnsignedInteger>;
    using HeapIndexAndFirstPileAndSecondPile = std::tuple<UnsignedInteger, UnsignedInteger, UnsignedInteger>;
    explicit GrundyGame(UnsignedInteger const totalNumberOfSticks);
    [[nodiscard]] StickHeaps const& getStickHeaps() const;
    [[nodiscard]] bool hasNoMoves() const;
    void split(HeapIndexAndFirstPileAndSecondPile const& heapIndexAndFirstPileAndSecondPile);
    GameState getGameState();
    HeapIndexAndFirstPileAndSecondPile getOptimalWayToSplit();
    UnsignedInteger getOverallGrundyNumber();

private:
    SetOfUnsignedIntegers getNextGrundyNumbersWithNumberOfSticks(UnsignedInteger const numberOfSticks);
    UnsignedInteger getGrundyNumberWithNumberOfSticks(UnsignedInteger const numberOfSticks);
    StickHeaps m_stickHeaps;
    SticksToGrundyNumberMap m_sticksToGrundyNumberMap;  // dynamic programming
};

}  // namespace alba::math
