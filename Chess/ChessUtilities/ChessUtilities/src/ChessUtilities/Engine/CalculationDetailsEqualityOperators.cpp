#include "CalculationDetailsEqualityOperators.hpp"

namespace alba::chess {

bool operator==(Variation const& variation1, Variation const& variation2) {
    return variation1.scoreInCentipawns == variation2.scoreInCentipawns &&
           variation1.mateValue == variation2.mateValue && variation1.halfMoves == variation2.halfMoves;
}

}  // namespace alba::chess
