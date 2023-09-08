#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

struct CalculationDetails {
    bool operator==(CalculationDetails const& other) const;
    bool operator!=(CalculationDetails const& other) const;
    int depthInPlies;
    Variations variations;
    std::string bestMove;
    std::string responseMoveToPonder;
};

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba
