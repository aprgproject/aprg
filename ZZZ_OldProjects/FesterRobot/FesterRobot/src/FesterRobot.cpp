#include "FesterRobot.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <iostream>
#include <sstream>
#define EXCEL_CELL_COORDINATES1 1256, 437
#define EXCEL_CELL_COORDINATES2 1256, 466
#define MATLAB_COMMAND_WINDOW_COORDINATES 190, 160
#define MATLAB_TITLE_BAR_COORDINATES 375, 14
#define ORIGIN 0, 0

using namespace alba::AlbaLocalUserAutomation;
using namespace std;

namespace {
constexpr int POLLING_DELAY_TO_WAIT_FOR_START = 1000;
} // namespace

namespace alba {

FesterRobot::FesterRobot(string const& outputPath) : m_outputStream(outputPath) {}

void FesterRobot::run() {
    cout << "Press the key 'ctrl' to start.\n";
    while (true) {
        exitIfSpecialKeyIsPressed();
        if (isLetterPressed(VK_CONTROL)) {
            cout << "Starting robot duties.\n";
            setupFesterEnvironmentInMatlab();

            for (int filterBitInteger = 63; filterBitInteger > 0;) {
                updateExcelFile(static_cast<unsigned int>(filterBitInteger));
                m_outputStream << "FREQUENCIES BIT: [" << std::hex << filterBitInteger << std::dec << "]\n";
                runFesterFunctionInMatlab();
                if (!m_retryCurrentFrequencies) {
                    --filterBitInteger;
                }
            }
            break;
        }
        sleep(POLLING_DELAY_TO_WAIT_FOR_START);
    }
    setMousePosition(MousePosition(ORIGIN));
}

string FesterRobot::getFrequenciesStringForExcel() const {
    stringstream frequencyStream;
    for (int const frequency : m_frequencies) {
        frequencyStream << frequency << " ";
    }
    string frequencyString(frequencyStream.str());
    if (!frequencyString.empty()) {
        frequencyString = frequencyString.substr(0, frequencyString.length() - 1);
    }
    return frequencyString;
}

bool FesterRobot::isRunningFinishedInClipboardData(string const& clipboardData) const {
    string const freqBandStringInLog(stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
        stringHelper::getStringWithoutRedundantWhiteSpace(stringHelper::getStringAfterThisString(
            stringHelper::getStringInBetweenTwoStrings(clipboardData, "freqBand", "filCoef"), "="))));
    string const frequenciesStringForExcel(getFrequenciesStringForExcel());
    cout << "freqBandStringInLog: [" << freqBandStringInLog << "]\n";
    cout << "frequenciesStringForExcel: [" << frequenciesStringForExcel << "]\n";
    return freqBandStringInLog == frequenciesStringForExcel;
}

void FesterRobot::updateExcelFile(unsigned int const freqUsageBits) {
    updateFrequenciesBasedFreqUsageBits(freqUsageBits);
    editCellInExcelWithNewFrequencies(MousePosition(EXCEL_CELL_COORDINATES1));
    editCellInExcelWithNewFrequencies(MousePosition(EXCEL_CELL_COORDINATES2));
    performKeyCombination({VK_CONTROL}, {'S'});
}

void FesterRobot::editCellInExcelWithNewFrequencies(MousePosition const& excelCellPosition) {
    doLeftClickAt(excelCellPosition);
    doLeftClickAt(excelCellPosition);
    typeCharacter(VK_DELETE);
    doDoubleLeftClickAt(excelCellPosition);
    setStringToClipboard(getFrequenciesStringForExcel());
    performKeyCombination({VK_CONTROL}, {'V'});
}

void FesterRobot::runFesterFunctionInMatlab() {
    doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    setStringToClipboard("clc");
    performKeyCombination({VK_CONTROL}, {'V'});
    typeCharacter(VK_RETURN);
    setStringToClipboard(R"(fester('perf_rake_ilpc_gsm:1M_FixedGsm','300a');)");
    performKeyCombination({VK_CONTROL}, {'V'});
    typeCharacter(VK_RETURN);
    bool isRunning(true);
    bool isRunningFinished(false);
    string clipboardData;
    while (isRunning && !isRunningFinished) {
        exitIfSpecialKeyIsPressed();
        sleep(2000);
        doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
        performKeyCombination({VK_CONTROL}, {'A'});
        performKeyCombination({VK_CONTROL}, {'C'});
        clipboardData = getClipboardFormattedData();
        isRunning = isRunningInClipboardData(clipboardData);
        isRunningFinished = isRunningFinishedInClipboardData(clipboardData);
        doLeftClickAt(MousePosition(MATLAB_TITLE_BAR_COORDINATES));
    }
    m_retryCurrentFrequencies = !isRunning;
    saveDataToOutputFile(clipboardData);
}

void FesterRobot::saveDataToOutputFile(string const& clipboardData) {
    m_outputStream << "FREQUENCIES: [" << getFrequenciesStringForExcel() << "]\n";
    m_outputStream << clipboardData << "\n";
}

void FesterRobot::updateFrequenciesBasedFreqUsageBits(unsigned int const freqUsageBits) {
    m_frequencies.clear();
    if ((freqUsageBits & 0x1) > 0) {
        m_frequencies.emplace_back(-1800);
    }
    if ((freqUsageBits & 0x2) > 0) {
        m_frequencies.emplace_back(-1600);
    }
    if ((freqUsageBits & 0x4) > 0) {
        m_frequencies.emplace_back(-1400);
    }
    if ((freqUsageBits & 0x8) > 0) {
        m_frequencies.emplace_back(1400);
    }
    if ((freqUsageBits & 0x16) > 0) {
        m_frequencies.emplace_back(1600);
    }
    if ((freqUsageBits & 0x32) > 0) {
        m_frequencies.emplace_back(1800);
    }
}

string FesterRobot::getClipboardFormattedData() {
    string clipboardData(getStringFromClipboard());
    stringHelper::replaceAllAndReturnIfFound(clipboardData, "\r", "");
    return clipboardData;
}

void FesterRobot::setupFesterEnvironmentInMatlab() {
    doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    setStringToClipboard("clc");
    performKeyCombination({VK_CONTROL}, {'V'});
    typeCharacter(VK_RETURN);
    setStringToClipboard(R"(run('C:\Users\malba\Desktop\DSS\Fester\Fester_scp.m'))");
    performKeyCombination({VK_CONTROL}, {'V'});
    typeCharacter(VK_RETURN);
    setStringToClipboard(R"(format long g)");
    performKeyCombination({VK_CONTROL}, {'V'});
    typeCharacter(VK_RETURN);
}

void FesterRobot::exitIfSpecialKeyIsPressed() {
    if (isLetterPressed(VK_MENU)) {
        setMousePosition(MousePosition(ORIGIN));
        // NOLINTNEXTLINE(concurrency-mt-unsafe)
        exit(0);
    }
}

bool FesterRobot::isRunningInClipboardData(string const& clipboardData) {
    return stringHelper::isStringFoundCaseSensitive(clipboardData, "running iteration");
}

}  // namespace alba
