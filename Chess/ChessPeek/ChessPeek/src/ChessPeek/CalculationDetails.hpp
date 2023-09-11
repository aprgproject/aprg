#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba::chess::ChessPeek {

struct CalculationDetails {
    bool operator==(CalculationDetails const& other) const;
    bool operator!=(CalculationDetails const& other) const;
    int depthInPlies{};
    Variations variations;
    std::string bestMove;
    std::string responseMoveToPonder;
};

}  // namespace alba::chess::ChessPeek
