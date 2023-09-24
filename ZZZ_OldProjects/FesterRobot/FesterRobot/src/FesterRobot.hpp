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
    [[nodiscard]] std::string getFrequenciesStringForExcel() const;
    [[nodiscard]] bool isRunningFinishedInClipboardData(std::string const& clipboardData) const;
    void updateExcelFile(unsigned int const freqUsageBits);
    void editCellInExcelWithNewFrequencies(AlbaLocalUserAutomation::MousePosition const& excelCellPosition);
    void runFesterFunctionInMatlab();
    void saveDataToOutputFile(std::string const& clipboardData);
    void updateFrequenciesBasedFreqUsageBits(unsigned int const freqUsageBits);
    [[nodiscard]] static std::string getClipboardFormattedData();
    static void setupFesterEnvironmentInMatlab();
    static void exitIfSpecialKeyIsPressed();
    static bool isRunningInClipboardData(std::string const& clipboardData);
    std::ofstream m_outputStream;
    Frequencies m_frequencies;
    bool m_retryCurrentFrequencies{false};
};

}  // namespace alba
