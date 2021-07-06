#pragma once

#include <ChessPeek/ChessPeekConfigurationType.hpp>
#include <ChessUtilities/Board/BoardTypes.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Container/AlbaOptional.hpp>

#include <array>
#include <cstdint>
#include <fstream>
#include <map>

namespace alba
{

namespace chess
{

class ChessPieceConverter
{
public:
    using Count = unsigned int;
    using CountPerByte = std::array<Count, 8>;
    using PieceTypeToCountPerByteMap = std::map<PieceType, CountPerByte>;
    using PieceTypeToCountMap = std::map<PieceType, Count>;
    using CountToPieceTypeMultiMap = std::multimap<Count, PieceType>;
    using PieceTypeToBitValueMap = std::map<PieceType, uint64_t>;
    using BitManipulator = AlbaBitManipulation<uint64_t>;
    using BitValueUtilities = AlbaBitValueUtilities<uint64_t>;

    ChessPieceConverter() = delete;
    ChessPieceConverter(ChessPeekConfigurationType const type);

    Piece convertBitValueToPiece(PieceColor const pieceColor, uint64_t const bitValue);
    void setLogFile(std::string const& logFilePath);

private:
    void initialize(ChessPeekConfigurationType const type);
    void initializeConverterToChessDotCom();
    void initializeConverterToLichessDotOrg();

    PieceType getPieceTypeFromBitValue(
            PieceTypeToBitValueMap const& pieceTypeToBitValueMap,            uint64_t const bitValue);

    PieceTypeToBitValueMap getDifferenceMap(
            PieceTypeToBitValueMap const& pieceTypeToBitValueMap,
            uint64_t const bitValue) const;
    PieceTypeToCountPerByteMap getDifferenceOfEachByteMap(
            PieceTypeToBitValueMap const& differenceMap) const;
    PieceTypeToCountMap getPieceTypeToScoreMap(
            PieceTypeToCountPerByteMap const& pieceTypeToDifferenceOfEachByteMap) const;
    PieceTypes getBestFitTypes(PieceTypeToCountMap const& pieceTypeToScoreMap) const;

    PieceTypeToBitValueMap m_whitePiecesToBitValuesMap;
    PieceTypeToBitValueMap m_blackPiecesToBitValuesMap;
    AlbaOptional<std::ofstream> m_logFileStreamOptional;

};

}

}
