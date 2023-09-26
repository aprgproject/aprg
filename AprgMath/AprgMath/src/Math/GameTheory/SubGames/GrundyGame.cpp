#include "GrundyGame.hpp"

#include <Math/GameTheory/Common/GameUtilities.hpp>

using namespace std;

namespace alba::math {

GrundyGame::GrundyGame(UnsignedInteger const totalNumberOfSticks) : m_stickHeaps{totalNumberOfSticks} {}
GrundyGame::StickHeaps const& GrundyGame::getStickHeaps() const { return m_stickHeaps; }

bool GrundyGame::hasNoMoves() const {
    return all_of(m_stickHeaps.cbegin(), m_stickHeaps.cend(), [](UnsignedInteger const stickHeap) {
        return stickHeap <= 2;  // sizes 1 and 2 cannot be split with different sizes
    });
}

void GrundyGame::split(HeapIndexAndFirstPileAndSecondPile const& heapIndexAndFirstPileAndSecondPile) {
    UnsignedInteger const index = get<0>(heapIndexAndFirstPileAndSecondPile);
    if (index < m_stickHeaps.size()) {
        UnsignedInteger const firstPile = get<1>(heapIndexAndFirstPileAndSecondPile);
        UnsignedInteger const secondPile = get<2>(heapIndexAndFirstPileAndSecondPile);
        if (m_stickHeaps[index] == firstPile + secondPile) {
            m_stickHeaps.erase(m_stickHeaps.begin() + static_cast<int>(index));
            m_stickHeaps.emplace(m_stickHeaps.begin() + static_cast<int>(index), secondPile);
            m_stickHeaps.emplace(m_stickHeaps.begin() + static_cast<int>(index), firstPile);
        }
    }
}

GameState GrundyGame::getGameState() { return getGameStateFromGrundyNumber(getOverallGrundyNumber()); }

GrundyGame::HeapIndexAndFirstPileAndSecondPile GrundyGame::getOptimalWayToSplit() {
    HeapIndexAndFirstPileAndSecondPile result{};
    UnsignedInteger const overallGrundyNumber = getOverallGrundyNumber();
    GameState const gameState = getGameStateFromGrundyNumber(overallGrundyNumber);
    if (GameState::Losing == gameState) {
        for (UnsignedInteger heapIndex = 0; heapIndex < m_stickHeaps.size(); ++heapIndex) {
            UnsignedInteger const& stickHeap(m_stickHeaps[heapIndex]);
            if (stickHeap >= 3) {
                // sizes 1 and 2 cannot be split with different sizes
                result = make_tuple(heapIndex, 1ULL, stickHeap - 1ULL);
                break;
            }
        }
    } else if (GameState::Winning == gameState) {
        bool isFound(false);
        for (UnsignedInteger heapIndex = 0; !isFound && heapIndex < m_stickHeaps.size(); ++heapIndex) {
            UnsignedInteger const& stickHeap(m_stickHeaps[heapIndex]);
            UnsignedInteger const grundyNumberAtIndex = getGrundyNumberWithNumberOfSticks(stickHeap);
            UnsignedInteger const hammingDistance = grundyNumberAtIndex ^ overallGrundyNumber;
            for (int a = (static_cast<int>(stickHeap) - 1) / 2; !isFound && a > 0; --a) {
                int const b = static_cast<int>(stickHeap) - a;
                if (hammingDistance ==
                    getCombinedGrundyNumber(
                        getGrundyNumberWithNumberOfSticks(a), getGrundyNumberWithNumberOfSticks(b))) {
                    result = make_tuple(heapIndex, static_cast<UnsignedInteger>(a), static_cast<UnsignedInteger>(b));
                    isFound = true;
                }
            }
        }
    }
    return result;
}

UnsignedInteger GrundyGame::getOverallGrundyNumber() {
    UnsignedInteger result(0U);
    for (UnsignedInteger const& stickHeap : m_stickHeaps) {
        // cppcheck-suppress useStlAlgorithm
        result = getCombinedGrundyNumber(result, getGrundyNumberWithNumberOfSticks(stickHeap));
    }
    return result;
}

SetOfUnsignedIntegers GrundyGame::getNextGrundyNumbersWithNumberOfSticks(UnsignedInteger const numberOfSticks) {
    SetOfUnsignedIntegers result;

    UnsignedInteger const limit = (numberOfSticks + 1) / 2;
    for (int a = 1; a < static_cast<int>(limit); ++a) {
        int const b = static_cast<int>(numberOfSticks) - a;
        result.emplace(
            getCombinedGrundyNumber(getGrundyNumberWithNumberOfSticks(a), getGrundyNumberWithNumberOfSticks(b)));
    }
    return result;
}

UnsignedInteger GrundyGame::getGrundyNumberWithNumberOfSticks(UnsignedInteger const numberOfSticks) {
    UnsignedInteger result{};
    auto it = m_sticksToGrundyNumberMap.find(numberOfSticks);
    if (it != m_sticksToGrundyNumberMap.cend()) {
        result = it->second;
    } else {
        // possible infinite recursion for cycles
        result = getGrundyNumber(getNextGrundyNumbersWithNumberOfSticks(numberOfSticks));
        m_sticksToGrundyNumberMap[numberOfSticks] = result;
    }
    return result;
}

}  // namespace alba::math
