#pragma once

#include <ChessPeek/CommonTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::chess::ChessPeek {

class Configuration {
public:
    enum class Type { ChessDotComVersus, ChessDotComPuzzle, ChessDotComExplorer, LichessVersus, LichessStream };

    Configuration() = delete;
    explicit Configuration(Type const type);
    [[nodiscard]] stringHelper::StringPairs const& getUciOptionNamesAndValuePairs() const;
    [[nodiscard]] Type getType() const;
    [[nodiscard]] XY getTopLeftOfBoard() const;
    [[nodiscard]] XY getBottomRightOfBoard() const;
    [[nodiscard]] std::string const& getChessEnginePath() const;
    [[nodiscard]] std::string const& getScreenShotPath() const;
    [[nodiscard]] double getWhiteColorLimit() const;
    [[nodiscard]] double getBlackColorLimit() const;

private:
    void initialize();
    void initializeCommonParameters();
    void initializeSpecificParameters();
    void initializeChessDotComVersus();
    void initializeChessDotComPuzzle();
    void initializeChessDotComExplorer();
    void initializeLichessVersus();
    void initializeLichessStream();
    Type m_type;
    std::string m_chessEnginePath;
    stringHelper::StringPairs m_uciOptionNamesAndValuePairs;
    XY m_boardTopLeft;
    XY m_boardBottomRight;
    double m_whiteColorLimit;
    double m_blackColorLimit;
};

}  // namespace alba::chess::ChessPeek
