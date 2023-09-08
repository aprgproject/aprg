#include "FesterRobot.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <iostream>
#include <sstream>

#define POLLING_DELAY_TO_WAIT_FOR_START 1000
#define EXCEL_CELL_COORDINATES1 1256, 437
#define EXCEL_CELL_COORDINATES2 1256, 466
#define MATLAB_COMMAND_WINDOW_COORDINATES 190, 160
#define MATLAB_TITLE_BAR_COORDINATES 375, 14
#define ORIGIN 0, 0

using namespace std;

namespace alba {

FesterRobot::FesterRobot(string const& outputPath) : m_outputStream(outputPath) {}

void FesterRobot::run() {
    cout << "Press the key 'ctrl' to start.\n";
    while (true) {
        exitIfSpecialKeyIsPressed();
        if (m_userAutomation.isLetterPressed(VK_CONTROL)) {
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
        m_userAutomation.sleep(POLLING_DELAY_TO_WAIT_FOR_START);
    }
    m_userAutomation.setMousePosition(MousePosition(ORIGIN));
}

bool FesterRobot::isRunningInClipboardData(string const& clipboardData) {
    return stringHelper::isStringFoundCaseSensitive(clipboardData, "running iteration");
}

bool FesterRobot::isRunningFinishedInClipboardData(string const& clipboardData) const {
    string freqBandStringInLog(stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
        stringHelper::getStringWithoutRedundantWhiteSpace(stringHelper::getStringAfterThisString(
            stringHelper::getStringInBetweenTwoStrings(clipboardData, "freqBand", "filCoef"), "="))));
    string frequenciesStringForExcel(getFrequenciesStringForExcel());
    cout << "freqBandStringInLog: [" << freqBandStringInLog << "]\n";
    cout << "frequenciesStringForExcel: [" << frequenciesStringForExcel << "]\n";
    return freqBandStringInLog == frequenciesStringForExcel;
}

string FesterRobot::getClipboardFormattedData() const {
    string clipboardData(m_userAutomation.getStringFromClipboard());
    stringHelper::replaceAllAndReturnIfFound(clipboardData, "\r", "");
    return clipboardData;
}

string FesterRobot::getFrequenciesStringForExcel() const {
    stringstream frequencyStream;
    for (int frequency : m_frequencies) {
        frequencyStream << frequency << " ";
    }
    string frequencyString(frequencyStream.str());
    if (!frequencyString.empty()) {
        frequencyString = frequencyString.substr(0, frequencyString.length() - 1);
    }
    return frequencyString;
}

void FesterRobot::exitIfSpecialKeyIsPressed() {
    if (m_userAutomation.isLetterPressed(VK_MENU)) {
        m_userAutomation.setMousePosition(MousePosition(ORIGIN));
        exit(0);
    }
}

void FesterRobot::updateExcelFile(unsigned int const freqUsageBits) {
    updateFrequenciesBasedFreqUsageBits(freqUsageBits);
    editCellInExcelWithNewFrequencies(MousePosition(EXCEL_CELL_COORDINATES1));
    editCellInExcelWithNewFrequencies(MousePosition(EXCEL_CELL_COORDINATES2));
    m_userAutomation.performKeyCombination({VK_CONTROL}, {'S'});
}

void FesterRobot::setupFesterEnvironmentInMatlab() {
    m_userAutomation.doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    m_userAutomation.doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    m_userAutomation.setStringToClipboard("clc");
    m_userAutomation.performKeyCombination({VK_CONTROL}, {'V'});
    m_userAutomation.typeCharacter(VK_RETURN);
    m_userAutomation.setStringToClipboard(R"(run('C:\Users\malba\Desktop\DSS\Fester\Fester_scp.m'))");
    m_userAutomation.performKeyCombination({VK_CONTROL}, {'V'});
    m_userAutomation.typeCharacter(VK_RETURN);
    m_userAutomation.setStringToClipboard(R"(format long g)");
    m_userAutomation.performKeyCombination({VK_CONTROL}, {'V'});
    m_userAutomation.typeCharacter(VK_RETURN);
}

void FesterRobot::editCellInExcelWithNewFrequencies(MousePosition const& excelCellPosition) {
    m_userAutomation.doLeftClickAt(excelCellPosition);
    m_userAutomation.doLeftClickAt(excelCellPosition);
    m_userAutomation.typeCharacter(VK_DELETE);
    m_userAutomation.doDoubleLeftClickAt(excelCellPosition);
    m_userAutomation.setStringToClipboard(getFrequenciesStringForExcel());
    m_userAutomation.performKeyCombination({VK_CONTROL}, {'V'});
}

void FesterRobot::runFesterFunctionInMatlab() {
    m_userAutomation.doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    m_userAutomation.setStringToClipboard("clc");
    m_userAutomation.performKeyCombination({VK_CONTROL}, {'V'});
    m_userAutomation.typeCharacter(VK_RETURN);
    m_userAutomation.setStringToClipboard(R"(fester('perf_rake_ilpc_gsm:1M_FixedGsm','300a');)");
    m_userAutomation.performKeyCombination({VK_CONTROL}, {'V'});
    m_userAutomation.typeCharacter(VK_RETURN);
    bool isRunning(true);
    bool isRunningFinished(false);
    string clipboardData;
    while (isRunning && !isRunningFinished) {
        exitIfSpecialKeyIsPressed();
        m_userAutomation.sleep(2000);
        m_userAutomation.doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
        m_userAutomation.performKeyCombination({VK_CONTROL}, {'A'});
        m_userAutomation.performKeyCombination({VK_CONTROL}, {'C'});
        clipboardData = getClipboardFormattedData();
        isRunning = isRunningInClipboardData(clipboardData);
        isRunningFinished = isRunningFinishedInClipboardData(clipboardData);
        m_userAutomation.doLeftClickAt(MousePosition(MATLAB_TITLE_BAR_COORDINATES));
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

}  // namespace alba
