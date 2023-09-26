#include "MisereGame.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Math/GameTheory/NimGame.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba::math {

GameState MisereGame::getGameState(NimState const& nimState) {
    GameState result(GameState::Losing);
    if (getMaxHeapSize(nimState) == 1) {
        if (isEven(countNonEmptyHeaps(nimState))) {
            result = GameState::Winning;
        }
    } else {
        NimHeapSize const nimSum(NimGame::getNimSum(nimState));
        if (nimSum > 0) {
            result = GameState::Winning;
        }
    }
    return result;
}

NimState MisereGame::getOptimalNextState(NimState const& inputNimState) {
    NimState result(inputNimState);
    GameState const gameState(getGameState(inputNimState));
    if (GameState::Losing == gameState) {
        for (NimHeapSize& nimHeapSize : result) {
            // cppcheck-suppress useStlAlgorithm
            if (nimHeapSize > 0) {
                // just take one to prolong the game
                --nimHeapSize;
                break;
            }
        }
    } else if (GameState::Winning == gameState) {
        // state is only winning when size is odd (checked on getGameState)
        NimHeapSize const nimSum(NimGame::getNimSum(inputNimState));
        UnsignedInteger i = 0;
        for (; i < result.size(); ++i) {
            NimHeapSize const hammingDistanceFromNimSum = result[i] ^ nimSum;
            if (hammingDistanceFromNimSum < result[i]) {
                result[i] = hammingDistanceFromNimSum;
                break;
            }
        }
        // When it result to maxHeapSize is 1 and its non empty heaps is even, try to make it odd.
        UnsignedInteger const nonEmptyHeapsInResult = countNonEmptyHeaps(result);
        UnsignedInteger const nonEmptyHeapsInInput = countNonEmptyHeaps(inputNimState);
        if (getMaxHeapSize(result) == 1 && isEven(nonEmptyHeapsInResult) &&
            nonEmptyHeapsInResult == nonEmptyHeapsInInput) {
            result[i] = 0;
        }
    }
    return result;
}

NimHeapSize MisereGame::getMaxHeapSize(NimState const& nimState) {
    // cppcheck-suppress unusedVariable
    auto&& [_, maxIt] = minmax_element(nimState.cbegin(), nimState.cend());
    return *maxIt;
}

UnsignedInteger MisereGame::countNonEmptyHeaps(NimState const& nimState) {
    return count_if(nimState.cbegin(), nimState.cend(), [](NimHeapSize const nimHeapSize) { return nimHeapSize > 0; });
}

}  // namespace alba::math
