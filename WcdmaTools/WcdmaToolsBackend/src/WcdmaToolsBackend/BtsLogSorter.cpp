#include "BtsLogSorter.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaDateTime.hpp>
#include <Common/Time/AlbaLocalTimeHelper.hpp>

#include <iostream>
#include <map>

using namespace alba;
using namespace alba::algorithm;
using namespace std;

namespace alba::ProgressCounters {
extern double totalSizeToBeReadForCombine;
extern double totalSizeReadForCombine;
extern int writeProgressForCombine;
}  // namespace alba::ProgressCounters

namespace wcdmaToolsBackend {

BtsLogSorter::BtsLogSorter(BtsLogSorterConfiguration const& configuration)
    : m_isFilterOn(configuration.m_isFilterGrepOn),
      m_acceptedFilesGrepEvaluator(configuration.m_acceptedFilesGrepCondition),
      m_filterGrepEvaluator(configuration.m_filterGrepCondition),
      m_pathOfAllTempFiles(configuration.m_pathOfTempFiles),
      m_pathOfCurrentTempFiles(
          AlbaLocalPathHandler(configuration.m_pathOfTempFiles + R"(\)" + stringHelper::getRandomAlphaNumericString(30))
              .getPath()
              .string()),
      m_sorterWithPcTime(configuration.m_configurationWithPcTime.getConfigurationWithDifferentDirectory(
          AlbaLocalPathHandler(m_pathOfCurrentTempFiles + R"(\BlocksWithPcTime\)").getPath().string())),
      m_sorterWithoutPcTime(configuration.m_configurationWithoutPcTime.getConfigurationWithDifferentDirectory(
          AlbaLocalPathHandler(m_pathOfCurrentTempFiles + R"(\BlocksWithoutPcTime\)").getPath().string())),
      m_directoryOfLogsWithoutPcTime(
          AlbaLocalPathHandler(m_pathOfCurrentTempFiles + R"(\LogsWithoutPcTime\)").getPath().string()),
      m_pathOfStartupLog(
          AlbaLocalPathHandler(m_pathOfCurrentTempFiles + R"(\StartupLog\Startup.log)").getPath().string()) {
    deleteTempFilesAndDirectoriesOfOneDayOld();
    createTempDirectories();
}

void BtsLogSorter::processDirectory(string const& directoryPath) {
    cout << "processDirectory: " << directoryPath << "\n";
    AlbaLocalPathHandler(directoryPath)
        .findFilesAndDirectoriesUnlimitedDepth(
            [](AlbaLocalPathHandler::LocalPath const&) {},
            [&](AlbaLocalPathHandler::LocalPath const& filePath) {
                AlbaLocalPathHandler const filePathHandler(filePath);
                if (m_acceptedFilesGrepEvaluator.evaluate(filePathHandler.getFile().string())) {
                    processFile(filePathHandler.getPath().string());
                }
            });
}

void BtsLogSorter::processFile(string const& filePath) {
    openStartupLogsIfNeeded();
    AlbaLocalPathHandler const filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getFile() << "\n";

    double const previousTotalSize(ProgressCounters::totalSizeReadForCombine);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        string const lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        if (!m_isFilterOn || m_filterGrepEvaluator.evaluate(lineInFile)) {
            processLineInFile(filePathHandler.getFile().string(), lineInFile);
        }
        ProgressCounters::totalSizeReadForCombine =
            previousTotalSize + static_cast<double>(fileReader.getCurrentLocation());
    }
    ProgressCounters::totalSizeReadForCombine = previousTotalSize + static_cast<double>(filePathHandler.getFileSize());
}

void BtsLogSorter::processLineInFile(string const& filename, string const& lineInFile) {
    BtsLogPrint const logPrint(filename, lineInFile);
    m_foundHardwareAddresses.emplace(logPrint.getHardwareAddress());
    if (logPrint.getPcTime().isEmpty()) {
        m_sorterWithoutPcTime.add(logPrint);
    } else if (logPrint.getBtsTime().isStartup()) {
        m_startupLogStreamOptional.value() << logPrint << "\n";
    } else {
        m_sorterWithPcTime.add(logPrint);
    }
}

void BtsLogSorter::saveLogsToOutputFile(string const& outputPath) {
    addStartupLogsOnSorterWithPcTime();
    if (m_sorterWithPcTime.isEmpty()) {
        saveLogToOutputFileIfAllHavePcTime(outputPath);
    } else {
        saveLogToOutputFileIfNotAllHavePcTime(outputPath);
    }
    deleteStartupLog();
}

double BtsLogSorter::getTotalSizeToBeRead(set<string> const& listOfFiles) {
    double totalFileSize(0);
    for (string const& filePath : listOfFiles) {
        AlbaLocalPathHandler const filePathHandler(filePath);
        if (m_acceptedFilesGrepEvaluator.evaluate(filePathHandler.getFile().string())) {
            totalFileSize += static_cast<double>(filePathHandler.getFileSize());
        }
    }
    return totalFileSize;
}

void BtsLogSorter::createTempDirectories() const {
    AlbaLocalPathHandler(m_directoryOfLogsWithoutPcTime).createDirectoriesAndIsSuccessful();
    AlbaLocalPathHandler(m_pathOfStartupLog).createDirectoriesAndIsSuccessful();
}

void BtsLogSorter::deleteTempFilesAndDirectoriesOfOneDayOld() const {
    AlbaLocalPathHandler const tempFileAndDirectoryPathHandler(m_pathOfAllTempFiles);
    AlbaDateTime const currentTime(getCurrentDateTime());
    AlbaDateTime const oneDay(0, 0, 1, 0, 0, 0, 0);
    tempFileAndDirectoryPathHandler.findFilesAndDirectoriesOneDepth(
        [&](AlbaLocalPathHandler::LocalPath const& directoryPath) {
            AlbaLocalPathHandler const temporaryDirectoryPathHandler(directoryPath);
            AlbaDateTime const fileCreationTime(temporaryDirectoryPathHandler.getLastModifiedDateTime());
            AlbaDateTime const difference = currentTime - fileCreationTime;
            if (difference > oneDay) {
                cout << "Difference: [" << difference << "] deleted temporaryPath:" << directoryPath << "\n";
                temporaryDirectoryPathHandler.deleteDirectoryAndIsSuccessful();
            }
        },
        [](AlbaLocalPathHandler::LocalPath const&) {});
}

void BtsLogSorter::deleteStartupLog() const { deleteFilesInDirectory(m_pathOfStartupLog); }
void BtsLogSorter::deleteLogsWithoutPcTime() const { deleteFilesInDirectory(m_directoryOfLogsWithoutPcTime); }

void BtsLogSorter::saveLogToOutputFileIfAllHavePcTime(string const& outputPath) {
    cout << "Save log to output file if all have pc time.\n";
    ofstream outputLogFileStream(outputPath);
    writeLogsWithoutPcTimeToOutputFile(outputLogFileStream);
}

void BtsLogSorter::saveLogToOutputFileIfNotAllHavePcTime(string const& outputPath) {
    cout << "Save log to output file if not all have pc time.\n";
    ofstream outputLogFileStream(outputPath);
    separateLogsWithoutPcTimeIntoDifferentAddresses();
    writeLogsWithPcTimeToOutputFile(outputLogFileStream);
    writeLogsWithoutPcTimeToOutputFile(outputLogFileStream);
    deleteLogsWithoutPcTime();
}

void BtsLogSorter::openStartupLogsIfNeeded() {
    if (!m_startupLogStreamOptional) {
        m_startupLogStreamOptional.emplace();
        m_startupLogStreamOptional->open(m_pathOfStartupLog, std::ios::ate | std::ios::app);
    }
}

void BtsLogSorter::addStartupLogsOnSorterWithPcTime() {
    cout << "Add startup logs on sorter with PC time.\n";
    m_startupLogStreamOptional.reset();
    BtsPrintReaderWithRollback printReader;
    printReader.openIfNeeded(m_pathOfStartupLog);
    double const fileSize(static_cast<double>(AlbaLocalPathHandler(m_pathOfStartupLog).getFileSize()));
    while (printReader.isGood()) {
        BtsLogPrint const startupLogPrint(printReader.getPrint());
        if (!startupLogPrint.isEmpty()) {
            m_sorterWithPcTime.add(startupLogPrint);
        }
        ProgressCounters::writeProgressForCombine = static_cast<int>(25 * printReader.getCurrentLocation() / fileSize);
    }
}

void BtsLogSorter::writeLogsWithoutPcTimeToOutputFile(ofstream& outputLogFileStream) {
    cout << "Save sorted logs without PC time.\n";
    uint64_t printCount(0);
    uint64_t size(m_sorterWithoutPcTime.getSize());
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint) {
        updateOrWriteCurrentPrint(logPrint, outputLogFileStream);
        ProgressCounters::writeProgressForCombine = static_cast<int>(75 + (printCount++ * 25 / size));
    });
    writeLastPrint(outputLogFileStream);
}

void BtsLogSorter::separateLogsWithoutPcTimeIntoDifferentAddresses() {
    cout << "Save sorted logs without PC time into different addresses.\n";
    map<string, ofstream> hardwareAddressToOutputSteamMap;

    for (string const& hardwareAddress : m_foundHardwareAddresses) {
        hardwareAddressToOutputSteamMap[hardwareAddress].open(
            getPathOfLogWithoutPcTimeBasedFromHardwareAddress(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }
    uint64_t printCount(0);
    uint64_t size(m_sorterWithoutPcTime.getSize());
    m_sorterWithoutPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint) {
        hardwareAddressToOutputSteamMap[logPrint.getHardwareAddress()] << logPrint << "\n";

        ProgressCounters::writeProgressForCombine = static_cast<int>(25 + (printCount++ * 25 / size));
    });
}

void BtsLogSorter::writeLogsWithPcTimeToOutputFile(ofstream& outputLogFileStream) {
    cout << "Merge logs with and without PC time and save to output file.\n";
    map<string, BtsPrintReaderWithRollback> hardwareAddressToReaderMap;
    for (string const& hardwareAddress : m_foundHardwareAddresses) {
        hardwareAddressToReaderMap[hardwareAddress].openIfNeeded(
            getPathOfLogWithoutPcTimeBasedFromHardwareAddress(m_directoryOfLogsWithoutPcTime, hardwareAddress));
    }
    uint64_t printCount(0);
    uint64_t size(m_sorterWithPcTime.getSize());
    m_sorterWithPcTime.sortThenDoFunctionThenReleaseAllObjects([&](BtsLogPrint const& logPrint) {
        writePrintsFromFileReaderBeforeThisPrint(
            hardwareAddressToReaderMap[logPrint.getHardwareAddress()], logPrint, outputLogFileStream);
        updateOrWriteCurrentPrint(logPrint, outputLogFileStream);
        ProgressCounters::writeProgressForCombine = static_cast<int>(50 + (printCount++ * 25 / size));
    });
    for (auto& hardwareAddressToReaderPair : hardwareAddressToReaderMap) {
        addPrintsFromReaderToSorterWithoutPcTime(hardwareAddressToReaderPair.second);
    }
}

void BtsLogSorter::addPrintsFromReaderToSorterWithoutPcTime(BtsPrintReaderWithRollback& printReader) {
    while (printReader.isGood()) {
        BtsLogPrint const logPrintWithoutPcTime(printReader.getPrint());
        if (!logPrintWithoutPcTime.isEmpty()) {
            m_sorterWithoutPcTime.add(logPrintWithoutPcTime);
        }
    }
}

void BtsLogSorter::writePrintsFromFileReaderBeforeThisPrint(
    BtsPrintReaderWithRollback& printReader, BtsLogPrint const& logPrint, ofstream& outputLogFileStream) {
    while (printReader.isGood()) {
        BtsLogPrint const logPrintWithoutPcTime(printReader.getPrint());
        if (logPrintWithoutPcTime.getBtsTime() < logPrint.getBtsTime() ||
            logPrintWithoutPcTime.getBtsTime() == logPrint.getBtsTime()) {
            if (!logPrintWithoutPcTime.isEmpty()) {
                updateOrWriteCurrentPrint(logPrintWithoutPcTime, outputLogFileStream);
            }
        } else {
            printReader.rollBackPrint();
            break;
        }
    }
}

void BtsLogSorter::updateOrWriteCurrentPrint(BtsLogPrint const& logPrint, ofstream& outputLogFileStream) {
    if (m_currentPrintToWrite == logPrint) {
        m_currentPrintToWrite.updatePcTimeAndFileNameDetails(logPrint);
    } else {
        if (!m_currentPrintToWrite.getPrint().empty()) {
            outputLogFileStream << m_currentPrintToWrite.getPrintWithAllDetails() << "\n";
        }
        m_currentPrintToWrite = logPrint;
    }
}

void BtsLogSorter::writeLastPrint(ofstream& outputLogFileStream) {
    outputLogFileStream << m_currentPrintToWrite.getPrintWithAllDetails() << "\n";
    m_currentPrintToWrite = BtsLogPrint{};
}

void BtsLogSorter::deleteFilesInDirectory(string const& directoryOfLogs) {
    AlbaLocalPathHandler(directoryOfLogs).deleteAllDirectoryContentsAndIsSuccessful();
}

string BtsLogSorter::getPathOfLogWithoutPcTimeBasedFromHardwareAddress(
    string const& directory, string const& hardwareAddress) {
    string const filename = hardwareAddress.empty() ? "NoHardwareAddress" : hardwareAddress;
    return AlbaLocalPathHandler(directory + R"(\)" + filename + R"(.log)").getPath().string();
}

}  // namespace wcdmaToolsBackend
