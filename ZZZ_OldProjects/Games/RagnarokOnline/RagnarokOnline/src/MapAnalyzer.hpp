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
    MapAnalyzer();

    void analyze();
    void printResult() const;

    [[nodiscard]] double getPotentialZenyFromMonster(Monster const& monster) const;
    void printPotentialZenyFromMonster(std::string const& monsterName) const;
    static double getMultiplierForExperience(std::string const& mapName);

private:
    void gatherData();
    void selectMaps();
    void sortMaps();

    static bool isDropRateAcceptable(double const dropRate);
    static double getTalonRoDropRate(double const d[[nodiscard]] ropRate);
    [[nodiscard]] double getBestPrice(Item const& item) const;
    RagnarokOnline m_ragnarokOnline;
    MapsAnalyzerData m_mapsAnalyzerData;
};

}  // namespace alba
