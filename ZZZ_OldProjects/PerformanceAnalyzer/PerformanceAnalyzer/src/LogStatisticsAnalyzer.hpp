#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WcdmaToolsBackend/BtsLogPrint.hpp>
#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace alba {

struct LogDetails {
    bool operator<(LogDetails const& logDetails) const;
    bool operator>(LogDetails const& logDetails) const;
    bool operator==(LogDetails const& logDetails) const;
    stringHelper::strings logStrings;
    unsigned int count{};
};

class LogStatisticsAnalyzer {
public:
    LogStatisticsAnalyzer();
    void saveDataToCsv(std::string const& csvPath);
    void saveLogDetailsToCsv(std::ofstream& outputCsvFileStream);
    void processFileWithSortedPrints(std::string const& pathOfBtsSortedLog);

private:
    void analyzeLog(std::string const& lineInLogs);
    void addLogDetailsToCheckInInitialization(stringHelper::strings const& logStrings);
    void addLogDetailsToCheckInInitialization(std::string const& firstLogString, std::string const& secondLogString);
    void initializeLogDetailsToCheck();
    AlbaLocalPathHandler m_btsLogPathHandler;
    std::vector<LogDetails> m_logDetailsToCheck;
    unsigned int m_totalLinesFound{0};
    unsigned int m_totalLines{0};
};

}  // namespace alba
