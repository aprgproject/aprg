#pragma once

#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaDateTime.hpp>
#include <Statistics/DataCollection.hpp>

#include <map>
#include <string>
#include <vector>

namespace alba {

enum class TopLogAnalyzerState { BeforeColumnHeaders, AfterColumnHeaders };

class TopLogAnalyzer {
public:
    struct CpuMemLoad {
        double cpuLoad;
        double memLoad;
    };

    struct DataEntry {
        using ProcessToCpuMemMap = std::map<std::string, CpuMemLoad>;
        using ProcessToCpuMemPair = std::pair<std::string, CpuMemLoad>;
        [[nodiscard]] bool isEmpty() const;
        void clear();
        AlbaDateTime timeInTop;
        double totalCpuFromTop{};
        ProcessToCpuMemMap processToCpuMemMap;
    };

    struct ColumnHeaders {
        void clear();
        void set(unsigned int const sizeFromTop, double const cpuIndexFromTop, double const memIndexFromTop);
        unsigned int size;
        unsigned int cpuIndex;
        unsigned int memIndex;
    };

    struct CpuMemCollection {
        DataCollection<double> mem;
        DataCollection<double> cpu;
    };

    TopLogAnalyzer();
    void clear();
    void processTopLog(std::string const& pathOfTopLog);

private:
    void putEntriesInCpuReport(
        stringHelper::strings const& processNamesInReport, std::ofstream& cpuReportFileStream) const;

    void putEntriesInMemReport(
        stringHelper::strings const& processNamesInReport, std::ofstream& memReportFileStream) const;

    void readTopLogsAndSaveToDatabase(std::string const& pathOfTopLog);
    void generateCpuReport(std::string const& pathOfTopLog);
    void generateMemReport(std::string const& pathOfTopLog);
    void saveAndClearCurrentEntry(DataEntry& currentEntry);
    void saveDataFromHeaders(std::string const& lineInLogs);
    void saveCpuAndMem(std::string const& lineInLogs, DataEntry& currentEntry);
    stringHelper::strings getProcessNamesForCpuReport();
    stringHelper::strings getProcessNamesForMemReport();

    static void putHeadersInCpuReport(
        stringHelper::strings const& processNamesInReport, std::ofstream& cpuReportFileStream);

    static void putHeadersInMemReport(
        stringHelper::strings const& processNamesInReport, std::ofstream& memReportFileStream);

    static void saveTimeFromTop(std::string const& lineInLogs, DataEntry& currentEntry);
    static void saveOverallCpuData(std::string const& lineInLogs, DataEntry& currentEntry);
    static bool isTopCommandFirstLine(std::string const& lineInLogs);
    static bool isTopCommandHeaderLine(std::string const& lineInLogs);
    TopLogAnalyzerState m_state;
    ColumnHeaders m_columnHeaders{};
    std::vector<DataEntry> m_dataEntries;
    std::map<std::string, CpuMemCollection> m_processToCpuMemCollectionMap;
};

}  // namespace alba
