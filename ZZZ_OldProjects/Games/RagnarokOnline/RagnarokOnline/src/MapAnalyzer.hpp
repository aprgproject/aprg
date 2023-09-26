#pragma once

#include <RagnarokOnline.hpp>

#include <string>
#include <vector>

namespace alba {

struct MapAnalyzerData {
    std::string mapName;
    double zenyPotential;
    double baseExperiencePotential;
    double jobExperiencePotential;
    double annoyanceHp;
    unsigned int mobCount;
};

using MapsAnalyzerData = std::vector<MapAnalyzerData>;

class MapAnalyzer {
public:
    MapAnalyzer() = default;
    [[nodiscard]] double getPotentialZenyFromMonster(Monster const& monster) const;
    void printResult() const;
    void printPotentialZenyFromMonster(std::string const& monsterName) const;
    void analyze();
    static double getMultiplierForExperience(std::string const& mapName);

private:
    [[nodiscard]] double getBestPrice(Item const& item) const;
    void gatherData();
    void selectMaps();
    void sortMaps();
    static double getTalonRoDropRate(double const dropRate);
    static bool isDropRateAcceptable(double const dropRate);
    RagnarokOnline m_ragnarokOnline;
    MapsAnalyzerData m_mapsAnalyzerData;
};

}  // namespace alba
