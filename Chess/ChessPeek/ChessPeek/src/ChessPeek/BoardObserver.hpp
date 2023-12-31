#pragma once

#include <Bitmap/BitmapSnippet.hpp>
#include <ChessPeek/CommonTypes.hpp>
#include <ChessPeek/Configuration.hpp>
#include <ChessUtilities/Board/BoardTypes.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <ScreenMonitoring/AlbaLocalScreenMonitoring.hpp>

#include <bitset>
#include <cstdint>
#include <functional>
#include <map>

namespace alba::chess::ChessPeek {

class BoardObserver {
public:
    enum class WhiteOrBlack { White, Black };

    struct CheckDetail {
        XY pointOffset;
        WhiteOrBlack condition;
    };

    using BitSet64 = std::bitset<64>;
    using Count = int;
    using PieceToChessCellBitValueMap = std::map<PieceColorAndType, uint64_t>;
    using BitValueUtilities = AlbaBitValueUtilities<uint64_t>;
    using PieceColorAndTypes = std::vector<PieceColorAndType>;
    using CheckDetails = std::vector<CheckDetail>;
    using BoolFunction = std::function<bool(double const)>;
    BoardObserver() = delete;
    BoardObserver(Configuration const& configuration, AlbaLocalScreenMonitoring const& screenMonitoring);
    BoardObserver(Configuration const& configuration, AprgBitmap::BitmapSnippet const& bitmapSnippet);
    [[nodiscard]] BitSet64 getBitValueFromCell(int const xIndex, int const yIndex) const;
    [[nodiscard]] Piece getPieceFromCell(int const xIndex, int const yIndex) const;
    void retrieveWhiteOffsetPoints(XYs& coordinates, int const xIndex, int const yIndex) const;
    void retrieveBlackOffsetPoints(XYs& coordinates, int const xIndex, int const yIndex) const;

private:
    [[nodiscard]] PieceColorAndType getBestPieceFromChessCellBitValue(uint64_t const chessCellBitValue) const;
    [[nodiscard]] PieceColorAndTypes getBestFitPiecesFromChessCellBitValue(uint64_t const chessCellBitValue) const;
    [[nodiscard]] uint32_t getColorAt(int const x, int const y) const;

    [[nodiscard]] bool isBitValueAsserted(
        CheckDetail const& checkDetail, XY const& chessCellTopLeft, XY const& chessCellBottomRight) const;

    void retrieveChessCellTopLeftAndBottomRight(
        XY& chessCellTopLeft, XY& chessCellBottomRight, int const xIndex, int const yIndex) const;

    void retrieveOffsetPointsWithCondition(
        XYs& coordinates, int const xIndex, int const yIndex, BoolFunction const& condition) const;

    void initialize(Configuration::Type const type);
    void initializeConverterToChessDotCom();
    void initializeConverterToLichessVersus();
    Configuration const& m_configuration;
    AlbaLocalScreenMonitoring const* const m_screenMonitoringPtr;
    AprgBitmap::BitmapSnippet const* const m_bitmapSnippetPtr;
    XY m_checkMaxPoint;
    CheckDetails m_checkDetails;
    PieceToChessCellBitValueMap m_piecesToChessCellBitValuesMap;
};

}  // namespace alba::chess::ChessPeek
