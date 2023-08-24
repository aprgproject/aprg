#pragma once

#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <fstream>
#include <map>
#include <optional>
#include <string>

using wcdmaToolsBackend::BtsLogTime;

namespace alba {

struct BtsLogDelay {
    std::optional<BtsLogTime> startTimeOptional;
    std::optional<BtsLogTime> endTimeOptional;
};

struct UniqueId {
    UniqueId()  {}
    int crnccId{0};
    int nbccId{0};
    int transactionId{0};
    bool operator<(UniqueId const& uniqueId) const {
        if (crnccId != uniqueId.crnccId) {
            return crnccId < uniqueId.crnccId;
        }
        if (nbccId != uniqueId.nbccId) {
            return nbccId < uniqueId.nbccId;
        }
        return transactionId < uniqueId.transactionId;
    }
};

struct WireSharkDelay {
    std::optional<double> startTimeOptional;
    std::optional<double> endTimeOptional;
};

class BtsLogAnalyzer {
public:
    BtsLogAnalyzer();
    explicit BtsLogAnalyzer(std::string const& pathOfOutputFile);
    static void processFileForToCountUsersWithTracing(std::string const& filePath);
    void processDirectoryForWireSharkDelay(std::string const& directoryPath);
    void processFileForWireSharkDelay(std::string const& filePath);
    void processFileForMsgQueuingTime(std::string const& filePath);
    void processFileForBtsDelayForRlh(std::string const& filePath);
    void processFileForBtsDelayForRlDeletion(std::string const& filePath);
    static void processFileForBtsDelayForMikhailKnife(std::string const& filePath);
    void processFileForBtsDelayForGrm(std::string const& filePath);
    static double getWireSharkTime(std::string const& lineInLogs);
    static std::string getNumberAfterThisString(std::string const& mainString, std::string const& stringToSearch);
    double getComputedAverageDelay() const;

private:
    std::ofstream m_outputStream;
    double m_totalDelay;
    int m_count;
    std::map<int, WireSharkDelay> m_wireSharkDelays;
    std::map<UniqueId, BtsLogDelay> m_btsLogDelays;
    std::map<int, BtsLogDelay> m_btsLogDelaysGrm;
};

}  // namespace alba
