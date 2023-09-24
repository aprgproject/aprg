#pragma once

#include <WcdmaToolsBackend/BtsLogSorterConfiguration.hpp>
#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <optional>
#include <string>

namespace alba {

class PerformanceAnalyzer {
private:
    struct UniqueUserId {
        explicit UniqueUserId(std::string const& lineInLogs);
        UniqueUserId();
        bool operator<(UniqueUserId const& uniqueUserId) const;
        void saveNbccId(std::string const& lineInLogs);
        void saveCrnccId(std::string const& lineInLogs);
        void saveTransactionId(std::string const& lineInLogs);
        static int getNbccId(std::string const& lineInLogs);
        static int getCrnccId(std::string const& lineInLogs);
        static int getTransactionId(std::string const& lineInLogs);
        int nbccId;
        int crnccId;
        int transactionId;
    };

    struct BtsLogDelay {
        std::optional<wcdmaToolsBackend::BtsLogTime> startTimeOptional;
        std::optional<wcdmaToolsBackend::BtsLogTime> endTimeOptional;
    };

public:
    PerformanceAnalyzer();
    [[nodiscard]] std::string extract(std::string const& inputPath) const;
    [[nodiscard]] std::string combineAndSort(std::string const& inputPath) const;
    void setFileForRawDataDump(std::string const& rawDataPath);
    void logLineInRawDataFile(std::string const& line);
    void logStringInRawDataFile(std::string const& line);
    void processFileForMsgQueueingTime(std::string const& filePath);
    void processFileForRlSetupDelayInRlh(std::string const& filePath);
    void processFileForRlDeletionDelayInRlh(std::string const& filePath);
    void processFileForPeriodicCpuLogging(std::string const& filePath);
    void processFileForRlSetupDelayInTupcWithSymonKnife(std::string const& filePath);
    void processFileForRlSetupDelayInTupcWithSymonKnifeForFtm(std::string const& filePath);
    void processFileForFtmFcmWireshark(std::string const& filePath);
    void processFileForTopLogs(std::string const& filePath);
    void processFileForTopLogsMem(std::string const& filePath);
    void processFileForRlSetupPerSecond(std::string const& filePath);
    void processFileForTraceLog(std::string const& traceLogPath);
    void processDirectoryForTraceLog(std::string const& traceLogPath);

    static int getDelayTimeInUs(
        wcdmaToolsBackend::BtsLogTime const& endTime, wcdmaToolsBackend::BtsLogTime const& startTime);

    static int getDelayTimeInMinutes(
        wcdmaToolsBackend::BtsLogTime const& endTime, wcdmaToolsBackend::BtsLogTime const& startTime);

private:
    std::string m_extractGrepCondition{
        R"([LRM] || [alarm] || [UDP] || [CPU] || [syslog] || [ccns] || [tcom] || [startup] || [runtime] || [system] || [radparam] || ([bts]&&([.log]||[.zip]||[.tar])) || [snapshot] || ([tech]&&[report]) || [BTSLogFiles])"};

    wcdmaToolsBackend::BtsLogSorterConfiguration m_sorterConfiguration;
    std::optional<std::ofstream> m_RawDataFileOptional;
};

}  // namespace alba
