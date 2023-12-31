#include "MapAnalyzer.hpp"

#include <Common/Print/AlbaLogPrints.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

double MapAnalyzer::getPotentialZenyFromMonster(Monster const& monster) const {
    double potentialZeny = 0;
    for (NameAndRate const& dropWithRate : monster.dropsWithRates) {
        if (isDropRateAcceptable(dropWithRate.rate)) {
            Item const item(m_ragnarokOnline.getItem(dropWithRate.name));
            double const bestPrice(getBestPrice(item));
            potentialZeny += bestPrice * getTalonRoDropRate(dropWithRate.rate) / 100;
        }
    }
    return potentialZeny;
}

void MapAnalyzer::printResult() const {
    cout.precision(10);
    for (MapAnalyzerData const& mapData : m_mapsAnalyzerData) {
        cout << "Map:[" << mapData.mapName << "] Zeny:[" << mapData.zenyPotential << "] BaseExp:["
             << mapData.baseExperiencePotential << "] JobExp:[" << mapData.jobExperiencePotential << "] AnnoyanceHp:["
             << mapData.annoyanceHp << "] MobCount:[" << mapData.mobCount << "]\n";
    }
}

void MapAnalyzer::printPotentialZenyFromMonster(string const& monsterName) const {
    cout.precision(10);
    cout << "\n";
    cout << "Monster name: [" << monsterName << "]\n";
    Monster const monster(m_ragnarokOnline.getMonster(monsterName));
    for (NameAndRate const& dropWithRate : monster.dropsWithRates) {
        if (isDropRateAcceptable(dropWithRate.rate)) {
            Item const item(m_ragnarokOnline.getItem(dropWithRate.name));
            string const fixedItemName(alba::RagnarokOnline::getFixedItemName(item));
            double const bestPrice(getBestPrice(item));
            double const itemPotentialZeny = bestPrice * getTalonRoDropRate(dropWithRate.rate) / 100;
            cout << "Item name: [" << fixedItemName << "] Item potential zeny: [" << itemPotentialZeny
                 << "] Talon RO drop rate: [" << getTalonRoDropRate(dropWithRate.rate) << "] Best price: [" << bestPrice
                 << "] NPC price: [" << item.sellingPrice << "] TalonRo buying price: ["
                 << m_ragnarokOnline.getTalonRoBuyingPrice(fixedItemName) << "] TalonRo selling price: ["
                 << m_ragnarokOnline.getTalonRoSellingPrice(fixedItemName) << "]\n";
        }
    }
    cout << "\n";
}

void MapAnalyzer::analyze() {
    gatherData();
    selectMaps();
    sortMaps();
}

double MapAnalyzer::getMultiplierForExperience(string const& mapName) {
    double multiplier(1);
    if (isStringFoundCaseSensitive(mapName, "xmas_") || isStringFoundCaseSensitive(mapName, "man_") ||
        isStringFoundCaseSensitive(mapName, "dic_")) {
        multiplier = 2;
    }
    return multiplier;
}

double MapAnalyzer::getBestPrice(Item const& item) const {
    double result = NAN;
    string const fixedItemName(alba::RagnarokOnline::getFixedItemName(item));
    double const npcPrice = item.sellingPrice;
    double const talonRoBuyingPrice = m_ragnarokOnline.getTalonRoBuyingPrice(fixedItemName);
    double const talonRoSellingPrice = m_ragnarokOnline.getTalonRoSellingPrice(fixedItemName);
    result = npcPrice;
    if (result < talonRoBuyingPrice) {
        result = talonRoBuyingPrice;  // remove this if buying shops are ignored
    }
    if (result < talonRoSellingPrice) {
        // result = talonRoSellingPrice; //remove this if selling shops are ignored
    }
    return result;
}

void MapAnalyzer::gatherData() {
    m_ragnarokOnline.readItemIdToItemMapFromFile(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\ItemIdToItemMap.txt)");
    m_ragnarokOnline.readMonsterIdToMonsterMapFromFile(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\MonsterIdToMonsterMap.txt)");
    m_ragnarokOnline.readMapNameToRoMapFromFile(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\MapNameToRoMap.txt)");
    // m_ragnarokOnline.readBuyingShopItems(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\BuyingShopItemsCurrentData.txt)");
    // m_ragnarokOnline.readSellingShopItems(R"(C:\Users\detec\OneDrive\Desktop\Games\RO\SellingShopItemsCurrentData.txt)");
    m_ragnarokOnline.readBuyingShopItems(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\BuyingShopItemsCumulativeData.txt)");
    m_ragnarokOnline.readSellingShopItems(
        R"(C:\Users\detec\OneDrive\Desktop\Games\RO\SellingShopItemsCumulativeData.txt)");
    m_ragnarokOnline.buildItemNameToItemId();
    m_ragnarokOnline.buildMonsterNameToMonsterId();
}

void MapAnalyzer::selectMaps() {
    cout.precision(10);
    for (auto const& mapNameToRoMap : m_ragnarokOnline.getMapNameToRoMap()) {
        MapAnalyzerData mapAnalyzerData{};
        mapAnalyzerData.mapName = mapNameToRoMap.first;
        struct MonsterData {
            unsigned int spawnCount;
            double potentialZeny;
            double potentialBaseExperience;
            double potentialJobExperience;
            bool isAnnoyance;
        };
        RoMap const& roMap(mapNameToRoMap.second);

        bool hasAcceptableSmall(false);
        bool hasAcceptableMedium(false);
        bool hasAcceptableLarge(false);
        map<string, MonsterData> monstersNameToDataMap;
        for (MonsterDetailsOnRoMap const& monsterDetailsOnMap : roMap.monstersDetailsOnMap) {
            Monster const monster(m_ragnarokOnline.getMonster(monsterDetailsOnMap.monsterName));
            if (!monster.isMvp()) {
                // default case:
                // if (false) {
                // for sniper:
                // if(monster.hp > 30000) {
                // for merchant:
                // if(monster.fleeRequiredFor95Percent > 220 || monster.hitRequiredFor100Percent > 135 || monster.hp
                // > 10000 || monster.vitality > 50 || monster.defense > 40) {
                // for wizard:
                // if(monster.hp > 30000 || monster.attackRange > 3 ) {
                // for rogue:
                // if(monster.fleeRequiredFor95Percent > 297 || monster.hitRequiredFor100Percent > 161) {
                // for assassin
                // if(monster.fleeRequiredFor95Percent > 310 || monster.hitRequiredFor100Percent > 170) {
                // for knight
                // if(monster.hitRequiredFor100Percent > 154 || monster.hitRequiredFor100Percent > 254) {
                // for sage:
                // if (monster.walkSpeed == "Very Fast" || monster.walkSpeed == "Fast") {
                //     isMapAcceptable = false;
                //     break;
                // }
                if (monster.size == "Small" && monster.hp > 100) {  // remove plants
                    hasAcceptableSmall = true;
                }
                if (monster.size == "Medium" && monster.hp > 6000) {
                    hasAcceptableMedium = true;
                }
                if (monster.size == "Large" && monster.hp > 20000) {
                    hasAcceptableLarge = true;
                }
                if (monstersNameToDataMap.find(monsterDetailsOnMap.monsterName) == monstersNameToDataMap.cend()) {
                    monstersNameToDataMap[monsterDetailsOnMap.monsterName].spawnCount = 0;
                }
                monstersNameToDataMap[monsterDetailsOnMap.monsterName].spawnCount += monsterDetailsOnMap.spawnCount;
            }
        }
        int countAcceptable(0);
        if (hasAcceptableSmall) {
            ++countAcceptable;
        }
        if (hasAcceptableMedium) {
            ++countAcceptable;
        }
        if (hasAcceptableLarge) {
            ++countAcceptable;
        }
        bool const isMapAcceptable = countAcceptable >= 3;
        if (isMapAcceptable && !monstersNameToDataMap.empty()) {
            double totalPotentialZeny = 0;
            double totalPotentialBaseExperience = 0;
            double totalPotentialJobExperience = 0;
            for (auto& monsterNameToDataPair : monstersNameToDataMap) {
                Monster const monster(m_ragnarokOnline.getMonster(monsterNameToDataPair.first));
                MonsterData& monsterData(monsterNameToDataPair.second);
                monsterData.potentialZeny = getPotentialZenyFromMonster(monster) * monsterData.spawnCount;
                monsterData.potentialBaseExperience =
                    getMultiplierForExperience(roMap.name) * monster.baseExperience * monsterData.spawnCount;
                monsterData.potentialJobExperience =
                    getMultiplierForExperience(roMap.name) * monster.jobExperience * monsterData.spawnCount;

                // print a specific map
                if (mapAnalyzerData.mapName == "mag_dun02") {
                    // ALBA_INF_PRINT1(cout, mapAnalyzerData.mapName);
                    // ALBA_INF_PRINT4(cout,
                    //     monster.name, monsterData.potentialZeny, getPotentialZenyFromMonster(monster),
                    //     monsterData.spawnCount);
                    // ALBA_INF_PRINT6(cout,
                    //     monster.name, monster.monsterId, monster.baseExperience, monsterData.spawnCount,
                    //     monster.hitRequiredFor100Percent, monster.fleeRequiredFor95Percent);
                    // ALBA_INF_PRINT5(cout,
                    //     mapAnalyzerData.mapName, monster.name, monsterData.potentialJobExperience,
                    //     monster.jobExperience, monsterData.spawnCount);
                    // for (auto const& dropWithRates : monster.dropsWithRates) {
                    //     ALBA_INF_PRINT2(cout, dropWithRates.name, dropWithRates.rate);
                    // }
                }
                // if (monster.fleeRequiredFor95Percent <= 200) {} // for homunculus lvling
                // if (monster.size == "Small") {  // for homunculus star glad farming
                //     ALBA_INF_PRINT3(cout, monster.name, monster.size, totalPotentialZeny);
                // }
                totalPotentialZeny += monsterData.potentialZeny;
                totalPotentialBaseExperience += monsterData.potentialBaseExperience;
                totalPotentialJobExperience += monsterData.potentialJobExperience;
            }
            mapAnalyzerData.zenyPotential = totalPotentialZeny;
            mapAnalyzerData.baseExperiencePotential = totalPotentialBaseExperience;
            mapAnalyzerData.jobExperiencePotential = totalPotentialJobExperience;
            // double averageZeny = totalPotentialZeny / monstersNameToDataMap.size();
            double const averageJobExperience =
                totalPotentialJobExperience / static_cast<double>(monstersNameToDataMap.size());
            for (auto& monsterNameToDataPair : monstersNameToDataMap) {
                Monster const monster(m_ragnarokOnline.getMonster(monsterNameToDataPair.first));
                MonsterData& monsterData(monsterNameToDataPair.second);
                // job annoyance
                monsterData.isAnnoyance = monsterData.potentialJobExperience / averageJobExperience < 0.5;
                // zeny annoyance
                // monsterData.isAnnoyance = monsterData.potentialZeny / averageZeny < 0.5;
                if (monsterData.isAnnoyance) {
                    mapAnalyzerData.annoyanceHp += monster.hp;
                }
                // if (!monsterData.isAnnoyance && monster.isAggressive()) {  // annoying mobs
                // if (monster.isAggressive()) { // aggressive mobs
                if (monster.walkSpeed != "Immovable") {  // moving mobs
                    mapAnalyzerData.mobCount += monsterData.spawnCount;
                }
            }
            m_mapsAnalyzerData.emplace_back(mapAnalyzerData);
        }
    }

    // printPotentialZenyFromMonster("Demon Pungus");
    // printPotentialZenyFromMonster("Sleeper");
    // printPotentialZenyFromMonster("Incubus");
    // printPotentialZenyFromMonster("Succubus");
    // printPotentialZenyFromMonster("Violy");
    // printPotentialZenyFromMonster("Anolian");
    // printPotentialZenyFromMonster("Drainliar");
    // printPotentialZenyFromMonster("Gargoyle");
    // printPotentialZenyFromMonster("Kraben");
    // printPotentialZenyFromMonster("Tamruan");
    // printPotentialZenyFromMonster("Whisper");
    // printPotentialZenyFromMonster("Evil Cloud Hermit / Taoist Hermit");
    // printPotentialZenyFromMonster("Wicked Nymph / Evil Nymph");
    // printPotentialZenyFromMonster("Wild Ginseng / Hermit Plant");
    // printPotentialZenyFromMonster("Ghoul");
    // printPotentialZenyFromMonster("Zombie Slaughter");
    // printPotentialZenyFromMonster("Ragged Zombie");
    // printPotentialZenyFromMonster("Hell Poodle");
    // printPotentialZenyFromMonster("Banshee");
    // printPotentialZenyFromMonster("Flame Skull");
    // printPotentialZenyFromMonster("Zombie Prisoner");
    // printPotentialZenyFromMonster("Injustice");
    // printPotentialZenyFromMonster("Cenere (Re-Stats)");
    // printPotentialZenyFromMonster("Antique Book (Re-Stats)");
    // printPotentialZenyFromMonster("Blue Lichtern / Lichtern (Re-Stats)");
    // printPotentialZenyFromMonster("Yellow Lichtern / Lichtern (Re-Stats)");
    // printPotentialZenyFromMonster("Blazer");
    // printPotentialZenyFromMonster("Deleter");
    // printPotentialZenyFromMonster("Diabolic");
    // printPotentialZenyFromMonster("Gig");
    // printPotentialZenyFromMonster("Nightmare Terror");
}

void MapAnalyzer::sortMaps() {
    sort(
        m_mapsAnalyzerData.begin(), m_mapsAnalyzerData.end(),
        [](MapAnalyzerData const& first, MapAnalyzerData const& second) {
            // the first one is always tweaked depending on goal
            if (first.zenyPotential == second.zenyPotential) {
                if (first.baseExperiencePotential == second.baseExperiencePotential) {
                    if (first.jobExperiencePotential == second.jobExperiencePotential) {
                        if (first.annoyanceHp == second.annoyanceHp) {
                            return first.mobCount > second.mobCount;
                        }
                        return first.annoyanceHp < second.annoyanceHp;
                    }
                    return first.jobExperiencePotential > second.jobExperiencePotential;
                }
                return first.baseExperiencePotential > second.baseExperiencePotential;
            }
            return first.zenyPotential > second.zenyPotential;
        });
}

double MapAnalyzer::getTalonRoDropRate(double const dropRate) {
    double talonRoDropRate(dropRate * 3);
    if (talonRoDropRate > 100) {
        talonRoDropRate = 100;
    }
    return talonRoDropRate;
}

bool MapAnalyzer::isDropRateAcceptable(double const /*dropRate*/) {
    return true;
    // return dropRate >= 1; // This removes hard farming
}

}  // namespace alba
