#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba {

namespace chess {

class UciInterpreter {
public:
    struct InfoDetails {
        stringHelper::StringPairs commonParameterNameAndValue;
        int multipv;
        stringHelper::strings pvHalfMoves;
        int scoreInCentipawns;
        int mateValue;  // number of mate moves, can be negative if player is about to be mated
    };

    explicit UciInterpreter(CalculationDetails& calculationDetails);
    void updateCalculationDetails(std::string const& stringFromEngine);

private:
    bool shouldSkipTheEntireInfo(std::string const& token);
    bool isACommonParameter(std::string const& token);
    InfoDetails createInfoDetailsFromInfoTokens(stringHelper::strings const& tokens);
    void processInfoTokens(stringHelper::strings const& infoTokens);
    void processBestMoveTokens(stringHelper::strings const& tokens);
    void saveCommonParametersOfBestLine(InfoDetails const& infoDetails);
    void saveVariation(InfoDetails const& infoDetails);
    CalculationDetails& m_calculationDetails;
};

}  // namespace chess

}  // namespace alba
