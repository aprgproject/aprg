#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Statistics/DataCollection.hpp>
#include <UserIdentifiers.hpp>
#include <WcdmaToolsBackend/BtsLogPrint.hpp>
#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <fstream>
#include <map>
#include <optional>
#include <string>

namespace alba {

class BtsLogAnalyzer {
public:
    enum class LogType { RlSetup, RlDeletion };

    struct PrintsAvailable {
        PrintsAvailable() = default;
        bool hasBB_2_RL_SETUP_REQ_MSG{false};
        bool hasBB_2_RL_SETUP_ACK_MSG{false};
        bool hasTC_TRANSPORT_BEARER_REGISTER_MSG{false};
        bool hasTC_TRANSPORT_BEARER_REGISTER_RESP_MSG{false};
    };

    struct DspData {
        DspData() = default;

        unsigned int boardId{0};
        unsigned int cpuId{0};
        unsigned int lcgId{0};
        unsigned int availableUlCEs{0};
        unsigned int availableDlCEs{0};
        unsigned int rakeState{0};
        unsigned int rachHand{0};
        unsigned int rakeLoad{0};
        unsigned int hsupaCFs{0};
        unsigned int hsRachCFs{0};
        unsigned int hsupaUsers{0};
        unsigned int nbrOfEnhHsupaUsers{0};
        unsigned int dchUsers{0};
    };

    using LogTime = std::optional<wcdmaToolsBackend::BtsLogTime>;
    using LogTimePair = std::pair<LogTime, LogTime>;
    using LogTimePairs = std::map<alba::UserIdentifiers, LogTimePair>;
    using UserIdentifierToPrintsAvailablePair = std::pair<alba::UserIdentifiers, PrintsAvailable>;
    using PrintsAvailableMap = std::map<alba::UserIdentifiers, PrintsAvailable>;
    using DspDataPair = std::pair<unsigned int, DspData>;
    using DspDataMap = std::map<unsigned int, DspData>;
    BtsLogAnalyzer();
    void printAllCollectedData() const;
    void clear();
    void processFileWithSortedPrints(std::string const& pathOfBtsSortedLog);

private:
    void initializeMessageQueueingTimeFileStream();
    void initializeRlSetupTimeFileStream();
    void initializeRlDeletionTimeFileStream();
    void initializeRlSetupPerSecondFileStream();
    void saveDspCapacityInformationInGrm(std::string const& lineInLogs);

    void saveDspCapacityInformationInGrmOfOneDsp(
        std::string const& dspCapacityOfOneDsp, unsigned int const boardId,
        wcdmaToolsBackend::BtsLogPrint const& logPrint);

    void saveDspCapacityInformationInLrmForR3(std::string const& lineInLogs);

    void saveDspCapacityInformationInLrmOfOneDspForR3(
        std::string const& dspCapacityOfOneDsp, unsigned int const boardId,
        wcdmaToolsBackend::BtsLogPrint const& logPrint);

    void saveDspCapacityInformationInLrmForR2(std::string const& lineInLogs);

    void saveDspCapacityInformationInLrmOfOneDspForR2(
        std::string const& dspCapacityOfOneDsp, unsigned int const boardId,
        wcdmaToolsBackend::BtsLogPrint const& logPrint);

    void initializeDataDumpOfAllDspsForR3();
    void initializeDataDumpOfAllDspsForR2();
    void initializeDataDumpOfOneDsp(std::string const& fileName);
    void initializeTotalUsersAndCfsDump();
    void initializeSaveAllUsersAndCfsDump();

    void saveDataDumpOfOneDsp(
        std::string const& fileName, DspData const& dspData, wcdmaToolsBackend::BtsLogPrint const& logPrint);

    void saveTotalUsersAndCfs(wcdmaToolsBackend::BtsLogPrint const& logPrint);
    void saveAllUsersAndCfs(wcdmaToolsBackend::BtsLogPrint const& logPrint);
    void saveDspInformation(unsigned int const dspAddress, DspData const& dspData);
    void saveMaxDspInformation(DspData const& dspData);
    void saveQueueingTime(std::string const& lineInLogs);
    void saveRlSetupPerSecond(std::string const& lineInLogs);
    void saveRlhSetupTime(std::string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs);
    void saveRlhDeletionTime(std::string const& lineInLogs, LogTimePairs& rlDeletionLogTimePairs);
    void saveAdditionalPrintsRlSetup(std::string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs);

    void computeRlSetupLatencyAndUpdateIfLogTimePairIsValid(
        UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs);

    void computeRLDeletionLatencyAndUpdateIfLogTimePairIsValid(
        UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs);

    void saveMessageQueueingTimeToCsvFile(std::string const& lineInLogs, unsigned int const messageQueueingTime);
    void savePrintsAvailableToCsvFile(UserIdentifiers const& userIdentifiers, std::ofstream& csvFileStream);

    static void setFirstLogTimeInPair(
        std::string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs);

    static void setSecondLogTimeInPair(
        std::string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs);

    static void saveUserIndentifierAndLatencyToCsvFile(
        UserIdentifiers const& userIdentifiers, double const latencyInMicroseconds, std::ofstream& csvFileStream);

    static void setLogTimeIfNeeded(std::string const& lineInLogs, LogTime& logTime);
    static double getTotalMicroseconds(LogTimePair const& logTimePairOfTheUser);
    static double getTotalMicroseconds(wcdmaToolsBackend::BtsLogTime const& btsLogTime);
    DataCollection<double> m_messageQueueingTime;
    DataCollection<double> m_rlhRlSetupLatency;
    DataCollection<double> m_rlhRlDeletionLatency;
    AlbaLocalPathHandler m_btsLogPathHandler;
    DspData m_maxDspData;
    DspDataMap m_dspDataMap;
    PrintsAvailableMap m_rlSetupPrintsAvailableMap;
    std::optional<std::ofstream> messageQueueingTimeFileStreamOptional;
    std::optional<std::ofstream> rlSetupTimeFileStreamOptional;
    std::optional<std::ofstream> rlDeletionTimeFileStreamOptional;
    std::optional<std::ofstream> rlSetupPerSecondFileStreamOptional;
};

}  // namespace alba
