#pragma once

#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <fstream>
#include <map>
#include <optional>
#include <string>

namespace alba {

struct BtsLogDelay {
    std::optional<wcdmaToolsBackend::BtsLogTime> startTimeOptional;
    std::optional<wcdmaToolsBackend::BtsLogTime> endTimeOptional;
};

struct UniqueId {
    UniqueId() = default;

    bool operator<(UniqueId const& uniqueId) const {
        if (crnccId != uniqueId.crnccId) {
            return crnccId < uniqueId.crnccId;
        }
        if (nbccId != uniqueId.nbccId) {
            return nbccId < uniqueId.nbccId;
        }
        return transactionId < uniqueId.transactionId;
    }

    int crnccId{0};
    int nbccId{0};
    int transactionId{0};
};

struct WireSharkDelay {
    std::optional<double> startTimeOptional;
    std::optional<double> endTimeOptional;
};

class BtsLogAnalyzer {
public:
    explicit BtsLogAnalyzer(std::string const& pathOfOutputFile);
    BtsLogAnalyzer();
    [[nodiscard]] double getComputedAverageDelay() const;
    void processDirectoryForWireSharkDelay(std::string const& directoryPath);
    void processFileForWireSharkDelay(std::string const& filePath);
    void processFileForMsgQueuingTime(std::string const& filePath);
    void processFileForBtsDelayForRlh(std::string const& filePath);
    void processFileForBtsDelayForRlDeletion(std::string const& filePath);
    void processFileForBtsDelayForGrm(std::string const& filePath);
    static void processFileForToCountUsersWithTracing(std::string const& filePath);
    static void processFileForBtsDelayForMikhailKnife(std::string const& filePath);
    static std::string getNumberAfterThisString(std::string const& mainString, std::string const& stringToSearch);
    static double getWireSharkTime(std::string const& lineInLogs);

private:
    std::ofstream m_outputStream;
    double m_totalDelay;
    int m_count;
    std::map<int, WireSharkDelay> m_wireSharkDelays;
    std::map<UniqueId, BtsLogDelay> m_btsLogDelays;
    std::map<int, BtsLogDelay> m_btsLogDelaysGrm;
};

}  // namespace alba
