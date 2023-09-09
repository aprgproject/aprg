#pragma once

#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <fstream>
#include <string>
#include <vector>

using Frequencies = std::vector<int>;

namespace alba {

class FesterRobot {
public:
    explicit FesterRobot(std::string const& outputPath);
    void run();

private:
    static bool isRunningInClipboardData(std::string const& clipboardData);
    std::string getClipboardFormattedData() const;
    std::string getFrequenciesStringForExcel() const;
    bool isRunningFinishedInClipboardData(std::string const& clipboardData) const;
    void exitIfSpecialKeyIsPressed();
    void updateExcelFile(unsigned int const freqUsageBits);
    void setupFesterEnvironmentInMatlab();
    void editCellInExcelWithNewFrequencies(MousePosition const& excelCellPosition);
    void runFesterFunctionInMatlab();
    void saveDataToOutputFile(std::string const& clipboardData);
    void updateFrequenciesBasedFreqUsageBits(unsigned int const freqUsageBits);
    std::ofstream m_outputStream;
    Frequencies m_frequencies;
    AlbaWindowsUserAutomation m_userAutomation;
    bool m_retryCurrentFrequencies{false};
};

}  // namespace alba
