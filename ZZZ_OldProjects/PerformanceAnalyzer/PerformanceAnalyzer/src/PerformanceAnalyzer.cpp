#include "PerformanceAnalyzer.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <FileExtractor/AprgFileExtractor.hpp>
#include <WcdmaToolsBackend/BtsLogSorter.hpp>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace alba::stringHelper;
using namespace std;
using wcdmaToolsBackend::BtsLogPrint;
using wcdmaToolsBackend::BtsLogTime;

namespace alba {

namespace ProgressCounters {
int numberOfFilesToBeAnalyzedForExtraction;
int numberOfFilesAnalyzedForExtraction;
double totalSizeToBeReadForCombine;
double totalSizeReadForCombine;
int writeProgressForCombine;
}  // namespace ProgressCounters

PerformanceAnalyzer::UniqueUserId::UniqueUserId(std::string const& lineInLogs)
    : nbccId(getNbccId(lineInLogs)), crnccId(getCrnccId(lineInLogs)), transactionId(getTransactionId(lineInLogs)) {}

PerformanceAnalyzer::UniqueUserId::UniqueUserId() : nbccId(0), crnccId(0), transactionId(0) {}

bool PerformanceAnalyzer::UniqueUserId::operator<(UniqueUserId const& uniqueUserId) const {
    if (nbccId != uniqueUserId.nbccId) {
        return nbccId < uniqueUserId.nbccId;
    }
    if (crnccId != uniqueUserId.crnccId) {
        return crnccId < uniqueUserId.crnccId;
    }
    return transactionId < uniqueUserId.transactionId;
}

void PerformanceAnalyzer::UniqueUserId::saveNbccId(std::string const& lineInLogs) { nbccId = getNbccId(lineInLogs); }
void PerformanceAnalyzer::UniqueUserId::saveCrnccId(std::string const& lineInLogs) { crnccId = getCrnccId(lineInLogs); }

void PerformanceAnalyzer::UniqueUserId::saveTransactionId(std::string const& lineInLogs) {
    transactionId = getTransactionId(lineInLogs);
}

int PerformanceAnalyzer::UniqueUserId::getNbccId(std::string const& lineInLogs) {
    int properNbccId = 0;
    int const nbccid = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccid: "));
    int const nbccId = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
    if (nbccid > 0) {
        properNbccId = nbccid;
    }
    if (nbccId > 0) {
        properNbccId = nbccId;
    }
    return properNbccId;
}

int PerformanceAnalyzer::UniqueUserId::getCrnccId(std::string const& lineInLogs) {
    int properCrnccId = 0;
    int const logCrnccId = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
    int const logCrncId = convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crncId: "));
    if (logCrncId > 0) {
        properCrnccId = logCrncId;
    }
    if (logCrnccId > 0) {
        properCrnccId = logCrnccId;
    }
    return properCrnccId;
}

int PerformanceAnalyzer::UniqueUserId::getTransactionId(std::string const& lineInLogs) {
    return convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
}

PerformanceAnalyzer::PerformanceAnalyzer() {
    // defautlvalues
    AlbaLocalPathHandler const pathHandler(R"(C:\temp\BtsSorter\)");
    pathHandler.createDirectoriesAndIsSuccessful();
    m_sorterConfiguration.m_acceptedFilesGrepCondition =
        R"( ([syslog]&&[.log]) || [ccns.log] || [tcom.log] || (([startup]||[runtime]||[system])&&[.log]) || ([UDP]&&([.log]||[.txt])) )";
    m_sorterConfiguration.m_pathOfTempFiles = pathHandler.getPath().string();
    pathHandler.createDirectoriesAndIsSuccessful();
    m_sorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks =
        pathHandler.getPath().string() + R"(WithPcTimeBlocks\)";
    AlbaLocalPathHandler(m_sorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks)
        .createDirectoriesAndIsSuccessful();
    m_sorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_sorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams = 50;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks =
        pathHandler.getPath().string() + R"(WithoutPcTimeBlocks\)";
    AlbaLocalPathHandler(m_sorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks)
        .createDirectoriesAndIsSuccessful();
    m_sorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = 1000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_sorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams = 70;
}

string PerformanceAnalyzer::extract(string const& inputPath) const {
    cout << " (Extract) start | Input path: " << inputPath << "\n";
    AprgFileExtractor fileExtractor(m_extractGrepCondition);
    AlbaLocalPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    if (pathHandler.isExistingDirectory()) {
        fileExtractor.extractAllRelevantFiles(pathHandler.getPath());
    } else if (alba::AprgFileExtractor::isRecognizedCompressedFile(pathHandler.getExtension().string())) {
        fileExtractor.extractAllRelevantFiles(pathHandler.getPath());
        pathHandler.input(pathHandler.getDirectory() / pathHandler.getFilenameOnly());
        outputPath = pathHandler.getPath().string();
    } else {
        cout << "Extraction step did not proceed. Current path: " << pathHandler.getPath() << "\n";
    }
    cout << " (Extract) done | Output path: " << outputPath << "\n";
    return outputPath;
}

string PerformanceAnalyzer::combineAndSort(string const& inputPath) const {
    cout << " (CombineAndSort) start | Input path: " << inputPath << "\n";
    AlbaLocalPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    if (pathHandler.isExistingDirectory()) {
        wcdmaToolsBackend::BtsLogSorter btsLogSorter(m_sorterConfiguration);
        btsLogSorter.processDirectory(pathHandler.getDirectory().string());
        pathHandler.moveUpADirectory();
        pathHandler.input(pathHandler.getDirectory().string() + R"(\sorted.log)");
        outputPath = pathHandler.getPath().string();
        btsLogSorter.saveLogsToOutputFile(outputPath);
    } else {
        cout << "Combine and sort step did not proceed. Current path: " << pathHandler.getPath() << "\n";
    }
    cout << " (CombineAndSort) done | Output path: " << inputPath << "\n";
    return outputPath;
}

void PerformanceAnalyzer::setFileForRawDataDump(string const& rawDataPath) {
    if (m_RawDataFileOptional) {
        m_RawDataFileOptional.reset();
    }
    m_RawDataFileOptional.emplace();
    m_RawDataFileOptional->open(rawDataPath.c_str());
    if (!m_RawDataFileOptional->is_open()) {
        m_RawDataFileOptional.reset();
    }
}

void PerformanceAnalyzer::logLineInRawDataFile(string const& line) {
    if (m_RawDataFileOptional) {
        m_RawDataFileOptional.value() << line << "\n";
    }
}

void PerformanceAnalyzer::logStringInRawDataFile(string const& line) {
    if (m_RawDataFileOptional) {
        m_RawDataFileOptional.value() << line;
    }
}

void PerformanceAnalyzer::processFileForMsgQueueingTime(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getPath() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    int totalMsgQueueingTime = 0;
    int highestMsgQueueingTime = 0;
    int numberOfInstances = 0;

    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundCaseSensitive(lineInLogs, "MSG TIME, start queuing time")) {
            int const msgQueueingTime =
                convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgQueuingTime: "));
            totalMsgQueueingTime += msgQueueingTime;
            highestMsgQueueingTime = std::max(msgQueueingTime, highestMsgQueueingTime);
            logLineInRawDataFile(lineInLogs);
            ++numberOfInstances;
        }
    }
    cout << "TotalMsgQueueingTime: " << totalMsgQueueingTime << "\n";
    cout << "highestMsgQueueingTime: " << highestMsgQueueingTime << "\n";
    cout << "AverageMsgQueueingTime: " << (static_cast<double>(totalMsgQueueingTime)) / numberOfInstances << "\n";
    cout << "numberOfPrints: " << numberOfInstances << "\n";
}

void PerformanceAnalyzer::processFileForRlSetupDelayInRlh(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";
    logLineInRawDataFile("crnccId,nbccId,transactionId,isSuccessful,delay");

    UniqueUserId userIdForMaxDelay;
    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;
    int countFail = 0;
    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    BtsLogTime startTest;
    BtsLogTime endTest;
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            BtsLogDelay& btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.startTimeOptional = logPrint.getBtsTime();
                if (!logPrint.getPcTime().isEmpty()) {
                    endTest = logPrint.getBtsTime();
                    if (startTest.isEmpty()) {
                        startTest = logPrint.getBtsTime();
                    }
                }
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            BtsLogDelay& btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.endTimeOptional = logPrint.getBtsTime();
            }
            if (btsLogDelay.startTimeOptional && btsLogDelay.endTimeOptional &&
                btsLogDelay.startTimeOptional->getTotalSeconds() <= btsLogDelay.endTimeOptional->getTotalSeconds()) {
                int const delay =
                    getDelayTimeInUs(btsLogDelay.endTimeOptional.value(), btsLogDelay.startTimeOptional.value());
                if (maxDelay < delay) {
                    maxDelay = delay;
                    userIdForMaxDelay = uniqueUserId;
                }
                totalDelay += delay;
                ++count;
                stringstream ss;
                ss << uniqueUserId.crnccId << "," << uniqueUserId.nbccId << "," << uniqueUserId.transactionId
                   << ",successful," << setw(10) << delay;
                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupFail3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            BtsLogDelay& btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.endTimeOptional = logPrint.getBtsTime();
            }
            if (btsLogDelay.startTimeOptional && btsLogDelay.endTimeOptional &&
                btsLogDelay.startTimeOptional->getTotalSeconds() <= btsLogDelay.endTimeOptional->getTotalSeconds()) {
                int const delay =
                    getDelayTimeInUs(btsLogDelay.endTimeOptional.value(), btsLogDelay.startTimeOptional.value());
                ++countFail;
                stringstream ss;
                ss << uniqueUserId.crnccId << "," << uniqueUserId.nbccId << "," << uniqueUserId.transactionId
                   << ",fail," << setw(10) << delay;
                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
        }
    }
    cout.precision(10);
    cout << "Average Delay(ms): " << totalDelay / count / 1000 << "\n";
    cout << "Max Delay(ms): " << maxDelay / 1000 << "\n";
    cout << "User with max delay -> nbccId: " << userIdForMaxDelay.nbccId << " crnccId: " << userIdForMaxDelay.crnccId
         << " transactionId: " << userIdForMaxDelay.transactionId << "\n";
    cout << "RL setup success count: " << count << "\n";
    cout << "RL setup failures count: " << countFail << "\n";
    BtsLogTime const delayTime = endTest - startTest;
    cout << "Test Duration: " << delayTime.getEquivalentStringBtsTimeFormat() << "\n";
}

void PerformanceAnalyzer::processFileForRlDeletionDelayInRlh(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << "\n";
    logLineInRawDataFile("crnccId,nbccId,transactionId,delay");

    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;
    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            BtsLogDelay& btsLogDelay(btsLogDelays[uniqueUserId]);
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            BtsLogDelay& btsLogDelay(btsLogDelays[uniqueUserId]);
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.endTimeOptional = logPrint.getBtsTime();
            }
            if (btsLogDelay.startTimeOptional && btsLogDelay.endTimeOptional &&
                btsLogDelay.startTimeOptional->getTotalSeconds() <= btsLogDelay.endTimeOptional->getTotalSeconds()) {
                int const delay =
                    getDelayTimeInUs(btsLogDelay.endTimeOptional.value(), btsLogDelay.startTimeOptional.value());
                maxDelay = std::max(maxDelay, static_cast<double>(delay));
                totalDelay += delay;
                ++count;
                stringstream ss;
                ss << uniqueUserId.crnccId << "," << uniqueUserId.nbccId << "," << uniqueUserId.transactionId << ","
                   << setw(10) << delay;
                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
        }
    }
    cout.precision(10);
    cout << "Average Delay(ms): " << totalDelay / count / 1000 << "\n";
    cout << "Max Delay(ms): " << maxDelay / 1000 << "\n";
}

void PerformanceAnalyzer::processFileForPeriodicCpuLogging(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << "\n";
    logLineInRawDataFile("subsystem,inProcess,inSystem,threadCpuTimeSpent");

    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundNotCaseSensitive(lineInLogs, R"(Periodic CPU Usage Report)") ||
            isStringFoundNotCaseSensitive(lineInLogs, R"(printCpuDataCollection)")) {
            string subsystem("Unknown");
            if (isStringFoundNotCaseSensitive(lineInLogs, R"(TCOM/CM)")) {
                subsystem = "CMEAS";
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(TCOM/DM)")) {
                subsystem = "DMEAS";
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(TCOM/G)")) {
                subsystem = "GRM";
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(TCOM/LRM)")) {
                subsystem = "LRM";
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(TCOM/R)")) {
                subsystem = "RLH";
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(TCOM/WRC)")) {
                subsystem = "WRC";
            }
            auto inProcess = convertStringToNumber<double>(getStringInBetweenTwoStrings(lineInLogs, "inProcess:", "%"));
            auto inSystem = convertStringToNumber<double>(getStringInBetweenTwoStrings(lineInLogs, "inSystem:", "%"));
            string const threadCpuTimeSpent(getStringInBetweenTwoStrings(lineInLogs, "threadCpuTimeSpent:", " ("));
            stringstream ss;
            ss << subsystem << "," << inProcess << "," << inSystem << "," << threadCpuTimeSpent;
            logLineInRawDataFile(ss.str());
        }
    }
}

void PerformanceAnalyzer::processFileForRlSetupDelayInTupcWithSymonKnife(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";
    logStringInRawDataFile("crnccId,nbccId,transactionId,totalDelayInRlh,");

    logStringInRawDataFile("rlhRlSetupRequest,");
    logStringInRawDataFile("rlhTbRegisterTime,");
    logStringInRawDataFile("tupcTbRegisterTime,");
    logStringInRawDataFile("tupcFirstErqSent,");
    logStringInRawDataFile("tupcLastEcfReceived,");
    logStringInRawDataFile("tupcFirstTransportConnectionSetup,");
    logStringInRawDataFile("tupcLastTransportConnectionSetupResponse,");
    logStringInRawDataFile("tupcTbRegisterResponseTime,");
    logStringInRawDataFile("rlhTbRegisterResponseTime,");
    logStringInRawDataFile("rlhRlSetupResponse,");

    logStringInRawDataFile("delayInRlSetupToTbRegisterInRlh,");
    logStringInRawDataFile("delayInTbRegisterFromRlhToTupc,");
    // logStringInRawDataFile("delayInCommunicationWithFtm,");
    logStringInRawDataFile("delayInTbRegisterToErqInTupc,");
    logStringInRawDataFile("delayInErqToEcfInFtm,");
    logStringInRawDataFile("delayInEcfToTransportConnectionInTupc,");
    logStringInRawDataFile("delayInTransportConnectionRequestResponseInDsp,");
    logStringInRawDataFile("delayInTransportConnectionResponseToTbRegisterResponseInTupc,");
    logStringInRawDataFile(
        "delayInTbRegisterResponseFromTupcToRlh"
        ",");
    logLineInRawDataFile("delayInTbRegisterResponseToRlSetupResponseInRlh");

    UniqueUserId userIdForMaxDelay;
    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;

    struct TupcDelaysData {
        [[nodiscard]] bool isComplete(int) const {
            return rlhRlSetupRequestOptional && rlhTbRegisterTimeOptional && tupcTbRegisterTimeOptional &&
                   tupcFirstErqSentOptional && tupcLastEcfReceivedOptional &&
                   tupcFirstTransportConnectionSetupOptional && tupcLastTransportConnectionSetupResponseOptional &&
                   tupcTbRegisterResponseTimeOptional && rlhTbRegisterResponseTimeOptional &&
                   rlhRlSetupResponseOptional;
        }

        [[nodiscard]] bool isCorrect(int const nbccId) const {
            if (!isComplete(nbccId)) {
                return false;
            }
            bool const isCorrect =
                (rlhRlSetupRequestOptional.value() < rlhTbRegisterTimeOptional.value()) &&
                (rlhTbRegisterTimeOptional.value() < tupcTbRegisterTimeOptional.value()) &&
                //(tupcTbRegisterTimeOptional.value()<tupcFirstTransportConnectionSetupOptional.value()) &&
                (tupcTbRegisterTimeOptional.value() < tupcFirstErqSentOptional.value()) &&
                (tupcFirstErqSentOptional.value() < tupcLastEcfReceivedOptional.value()) &&
                (tupcLastEcfReceivedOptional.value() < tupcFirstTransportConnectionSetupOptional.value()) &&
                (tupcFirstTransportConnectionSetupOptional.value() <
                 tupcLastTransportConnectionSetupResponseOptional.value()) &&
                (tupcLastTransportConnectionSetupResponseOptional.value() <
                 tupcTbRegisterResponseTimeOptional.value()) &&
                (tupcTbRegisterResponseTimeOptional.value() < rlhTbRegisterResponseTimeOptional.value()) &&
                (rlhTbRegisterResponseTimeOptional.value() < rlhRlSetupResponseOptional.value());

            return isCorrect;
        }

        optional<BtsLogTime> rlhRlSetupRequestOptional;
        optional<BtsLogTime> rlhTbRegisterTimeOptional;
        optional<BtsLogTime> tupcTbRegisterTimeOptional;
        optional<BtsLogTime> tupcFirstErqSentOptional;
        optional<BtsLogTime> tupcLastEcfReceivedOptional;
        optional<BtsLogTime> tupcFirstTransportConnectionSetupOptional;
        optional<BtsLogTime> tupcLastTransportConnectionSetupResponseOptional;
        optional<BtsLogTime> tupcTbRegisterResponseTimeOptional;
        optional<BtsLogTime> rlhTbRegisterResponseTimeOptional;
        optional<BtsLogTime> rlhRlSetupResponseOptional;
    };

    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    std::map<UniqueUserId, TupcDelaysData> tupcLogDelays;
    UniqueUserId tupcRegisterRequestTupcUserId;
    BtsLogPrint ecfLogPrint;

    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);

            BtsLogDelay& btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.startTimeOptional = logPrint.getBtsTime();
                UniqueUserId tupcUserIdInStartup;
                tupcUserIdInStartup.saveNbccId(lineInLogs);
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserIdInStartup];
                tupcLogDelay.rlhRlSetupRequestOptional = logPrint.getBtsTime();
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(RLH send TC_TRANSPORT_BEARER_REGISTER_MSG)")) {
            BtsLogPrint const logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if (tupcLogDelays.contains(tupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.rlhTbRegisterTimeOptional = logPrint.getBtsTime();
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"([Rcvd:TC_TRANSPORT_BEARER_REGISTER_MSG])")) {
            BtsLogPrint const logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if (tupcLogDelays.contains(tupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.tupcTbRegisterTimeOptional = logPrint.getBtsTime();
                tupcRegisterRequestTupcUserId = tupcUserId;
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"([Sent:M_IP_ERQ])")) {
            BtsLogPrint const logPrint(lineInLogs);
            if (tupcLogDelays.contains(tupcRegisterRequestTupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcRegisterRequestTupcUserId];
                if (!tupcLogDelay.tupcFirstErqSentOptional) {
                    tupcLogDelay.tupcFirstErqSentOptional = logPrint.getBtsTime();
                }
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(Rcvd[M_IP_ECF])")) {
            BtsLogPrint const logPrint(lineInLogs);
            ecfLogPrint = logPrint;
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"([Sent:TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG])")) {
            BtsLogPrint const logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if (tupcLogDelays.contains(tupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
                if (!tupcLogDelay.tupcFirstTransportConnectionSetupOptional) {
                    tupcLogDelay.tupcLastEcfReceivedOptional = ecfLogPrint.getBtsTime();
                    tupcLogDelay.tupcFirstTransportConnectionSetupOptional = logPrint.getBtsTime();
                }
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"([TUP_TRANSPORT_CONNECTION_SETUP_RESP])")) {
            BtsLogPrint const logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if (tupcLogDelays.contains(tupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.tupcLastTransportConnectionSetupResponseOptional = logPrint.getBtsTime();
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"([Sent:TC_TRANSPORT_BEARER_REGISTER_RESP_MSG])")) {
            BtsLogPrint const logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if (tupcLogDelays.contains(tupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.tupcTbRegisterResponseTimeOptional = logPrint.getBtsTime();
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(RLH receive TC_TRANSPORT_BEARER_REGISTER_RESP_MSG)")) {
            BtsLogPrint const logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if (tupcLogDelays.contains(tupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.rlhTbRegisterResponseTimeOptional = logPrint.getBtsTime();
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);

            BtsLogDelay& btsLogDelay = btsLogDelays[uniqueUserId];
            TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.endTimeOptional = logPrint.getBtsTime();
                tupcLogDelay.rlhRlSetupResponseOptional = logPrint.getBtsTime();
            }
            if (tupcLogDelay.isCorrect(tupcUserId.nbccId) && btsLogDelay.startTimeOptional &&
                btsLogDelay.endTimeOptional &&
                btsLogDelay.startTimeOptional->getTotalSeconds() <= btsLogDelay.endTimeOptional->getTotalSeconds()) {
                int const delay =
                    getDelayTimeInUs(btsLogDelay.endTimeOptional.value(), btsLogDelay.startTimeOptional.value());
                if (maxDelay < delay) {
                    maxDelay = delay;
                    userIdForMaxDelay = uniqueUserId;
                }
                totalDelay += delay;
                ++count;
                stringstream ss;

                ss << uniqueUserId.crnccId << "," << uniqueUserId.nbccId << "," << uniqueUserId.transactionId << ","
                   << setw(10) << delay;

                ss << "," << setw(10) << tupcLogDelay.rlhRlSetupRequestOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.rlhTbRegisterTimeOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.tupcTbRegisterTimeOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.tupcFirstErqSentOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.tupcLastEcfReceivedOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10)
                   << tupcLogDelay.tupcFirstTransportConnectionSetupOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10)
                   << tupcLogDelay.tupcLastTransportConnectionSetupResponseOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10)
                   << tupcLogDelay.tupcTbRegisterResponseTimeOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10)
                   << tupcLogDelay.rlhTbRegisterResponseTimeOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.rlhRlSetupResponseOptional->getEquivalentStringBtsTimeFormat();

                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.rlhTbRegisterTimeOptional.value(),
                          tupcLogDelay.rlhRlSetupRequestOptional.value());
                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.tupcTbRegisterTimeOptional.value(),
                          tupcLogDelay.rlhTbRegisterTimeOptional.value());
                // ss<<","<<setw(10)<<getDelayTimeInUs(tupcLogDelay.tupcFirstTransportConnectionSetupOptional.value(),
                // tupcLogDelay.tupcTbRegisterTimeOptional.value());
                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.tupcFirstErqSentOptional.value(),
                          tupcLogDelay.tupcTbRegisterTimeOptional.value());
                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.tupcLastEcfReceivedOptional.value(),
                          tupcLogDelay.tupcFirstErqSentOptional.value());
                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.tupcFirstTransportConnectionSetupOptional.value(),
                          tupcLogDelay.tupcLastEcfReceivedOptional.value());
                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.tupcLastTransportConnectionSetupResponseOptional.value(),
                          tupcLogDelay.tupcFirstTransportConnectionSetupOptional.value());
                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.tupcTbRegisterResponseTimeOptional.value(),
                          tupcLogDelay.tupcLastTransportConnectionSetupResponseOptional.value());
                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.rlhTbRegisterResponseTimeOptional.value(),
                          tupcLogDelay.tupcTbRegisterResponseTimeOptional.value());
                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.rlhRlSetupResponseOptional.value(),
                          tupcLogDelay.rlhTbRegisterResponseTimeOptional.value());

                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
            tupcLogDelays.erase(tupcUserId);
        }
    }
    cout << "Average Delay:" << totalDelay / count << " Max Delay:" << maxDelay << "\n";
    cout << "User with max delay -> nbccId: " << userIdForMaxDelay.nbccId << " crnccId: " << userIdForMaxDelay.crnccId
         << " transactionId: " << userIdForMaxDelay.transactionId << "\n";
}

void PerformanceAnalyzer::processFileForRlSetupDelayInTupcWithSymonKnifeForFtm(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";
    logStringInRawDataFile("crnccId,nbccId,transactionId,totalDelayInRlh,");

    logStringInRawDataFile("rlhRlSetupRequest,");
    logStringInRawDataFile("tupcTbRegisterTime,");
    logStringInRawDataFile("tupcFirstErqSent,");
    logStringInRawDataFile("tupcLastEcfReceived,");
    logStringInRawDataFile("tupcFirstTransportConnectionSetup,");
    logStringInRawDataFile("rlhRlSetupResponse,");

    logLineInRawDataFile("delayInErqToEcfInFtm,");

    UniqueUserId userIdForMaxDelay;
    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;

    struct TupcDelaysData {
        [[nodiscard]] bool isComplete(int) const {
            return rlhRlSetupRequestOptional && tupcTbRegisterTimeOptional && tupcFirstErqSentOptional &&
                   tupcLastEcfReceivedOptional && tupcFirstTransportConnectionSetupOptional &&
                   rlhRlSetupResponseOptional;
        }

        [[nodiscard]] bool isCorrect(int const nbccId) const {
            if (!isComplete(nbccId)) {
                return false;
            }
            bool const isCorrect =
                (rlhRlSetupRequestOptional.value() < tupcTbRegisterTimeOptional.value()) &&
                (tupcTbRegisterTimeOptional.value() < tupcFirstErqSentOptional.value()) &&
                (tupcFirstErqSentOptional.value() < tupcLastEcfReceivedOptional.value()) &&
                (tupcLastEcfReceivedOptional.value() < tupcFirstTransportConnectionSetupOptional.value()) &&
                (tupcFirstTransportConnectionSetupOptional.value() < rlhRlSetupResponseOptional.value());

            return isCorrect;
        }

        optional<BtsLogTime> rlhRlSetupRequestOptional;
        optional<BtsLogTime> tupcTbRegisterTimeOptional;
        optional<BtsLogTime> tupcFirstErqSentOptional;
        optional<BtsLogTime> tupcLastEcfReceivedOptional;
        optional<BtsLogTime> tupcFirstTransportConnectionSetupOptional;
        optional<BtsLogTime> rlhRlSetupResponseOptional;
    };

    std::map<UniqueUserId, BtsLogDelay> btsLogDelays;
    std::map<UniqueUserId, TupcDelaysData> tupcLogDelays;
    UniqueUserId tupcRegisterRequestTupcUserId;
    BtsLogPrint ecfLogPrint;

    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);

            BtsLogDelay& btsLogDelay = btsLogDelays[uniqueUserId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.startTimeOptional = logPrint.getBtsTime();
                UniqueUserId tupcUserIdInStartup;
                tupcUserIdInStartup.saveNbccId(lineInLogs);
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserIdInStartup];
                tupcLogDelay.rlhRlSetupRequestOptional = logPrint.getBtsTime();
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"([Rcvd:TC_TRANSPORT_BEARER_REGISTER_MSG])")) {
            BtsLogPrint const logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if (tupcLogDelays.contains(tupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
                tupcLogDelay.tupcTbRegisterTimeOptional = logPrint.getBtsTime();
                tupcRegisterRequestTupcUserId = tupcUserId;
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"([Sent:M_IP_ERQ])")) {
            BtsLogPrint const logPrint(lineInLogs);
            if (tupcLogDelays.contains(tupcRegisterRequestTupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcRegisterRequestTupcUserId];
                if (!tupcLogDelay.tupcFirstErqSentOptional) {
                    tupcLogDelay.tupcFirstErqSentOptional = logPrint.getBtsTime();
                }
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(Rcvd[M_IP_ECF])")) {
            BtsLogPrint const logPrint(lineInLogs);
            ecfLogPrint = logPrint;
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"([Sent:TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG])")) {
            BtsLogPrint const logPrint(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);
            if (tupcLogDelays.contains(tupcUserId)) {
                TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
                if (!tupcLogDelay.tupcFirstTransportConnectionSetupOptional) {
                    tupcLogDelay.tupcLastEcfReceivedOptional = ecfLogPrint.getBtsTime();
                    tupcLogDelay.tupcFirstTransportConnectionSetupOptional = logPrint.getBtsTime();
                }
            }
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)")) {
            UniqueUserId const uniqueUserId(lineInLogs);
            UniqueUserId tupcUserId;
            tupcUserId.saveNbccId(lineInLogs);

            BtsLogDelay& btsLogDelay = btsLogDelays[uniqueUserId];
            TupcDelaysData& tupcLogDelay = tupcLogDelays[tupcUserId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                btsLogDelay.endTimeOptional = logPrint.getBtsTime();
                tupcLogDelay.rlhRlSetupResponseOptional = logPrint.getBtsTime();
            }
            if (tupcLogDelay.isCorrect(tupcUserId.nbccId) && btsLogDelay.startTimeOptional &&
                btsLogDelay.endTimeOptional &&
                btsLogDelay.startTimeOptional->getTotalSeconds() <= btsLogDelay.endTimeOptional->getTotalSeconds()) {
                int const delay =
                    getDelayTimeInUs(btsLogDelay.endTimeOptional.value(), btsLogDelay.startTimeOptional.value());
                if (maxDelay < delay) {
                    maxDelay = delay;
                    userIdForMaxDelay = uniqueUserId;
                }
                totalDelay += delay;
                ++count;
                stringstream ss;

                ss << uniqueUserId.crnccId << "," << uniqueUserId.nbccId << "," << uniqueUserId.transactionId << ","
                   << setw(10) << delay;

                ss << "," << setw(10) << tupcLogDelay.rlhRlSetupRequestOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.tupcTbRegisterTimeOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.tupcFirstErqSentOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.tupcLastEcfReceivedOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10)
                   << tupcLogDelay.tupcFirstTransportConnectionSetupOptional->getEquivalentStringBtsTimeFormat();
                ss << "," << setw(10) << tupcLogDelay.rlhRlSetupResponseOptional->getEquivalentStringBtsTimeFormat();

                ss << "," << setw(10)
                   << getDelayTimeInUs(
                          tupcLogDelay.tupcLastEcfReceivedOptional.value(),
                          tupcLogDelay.tupcFirstErqSentOptional.value());

                logLineInRawDataFile(ss.str());
            }
            btsLogDelays.erase(uniqueUserId);
            tupcLogDelays.erase(tupcUserId);
        }
    }
    cout << "Average Delay:" << totalDelay / count << " Max Delay:" << maxDelay << "\n";
    cout << "User with max delay -> nbccId: " << userIdForMaxDelay.nbccId << " crnccId: " << userIdForMaxDelay.crnccId
         << " transactionId: " << userIdForMaxDelay.transactionId << "\n";
}

void PerformanceAnalyzer::processFileForFtmFcmWireshark(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";
    logLineInRawDataFile("saidKey(hex),erqTime,ecfTime,numberInWiresharkOfStart,numberInWiresharkOfEnd,delay");

    double maxDelay = 0;
    double totalDelay = 0;
    int count = 0;
    double endWiresharkTime = NAN;
    struct WiresharkLogKey {
        bool operator<(WiresharkLogKey const& key) const {
            if (said == key.said) {
                return operation < key.operation;
            }
            return said < key.said;
        }

        unsigned int operation;
        unsigned int said;
    };
    struct WiresharkLogDelay {
        optional<double> startTimeOptional;
        optional<double> endTimeOptional;
        unsigned int numberInWiresharkOfStart{};
        unsigned int numberInWiresharkOfEnd{};
    };
    std::map<WiresharkLogKey, WiresharkLogDelay> wiresharkLogDelays;
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundNotCaseSensitive(lineInLogs, R"(No.     Time        Source                Destination)")) {
            string const nextLine(fileReader.getLineAndIgnoreWhiteSpaces());
            string const timeString(getStringInBetweenTwoStrings(nextLine, " ", " "));
            auto wiresharkTime = convertStringToNumber<double>(timeString);
            endWiresharkTime = wiresharkTime;
            auto numberInWireshark = convertStringToNumber<unsigned int>(getStringBeforeThisString(nextLine, " "));
            WiresharkLogKey key{};
            while (fileReader.isNotFinished()) {
                string const followingLine(fileReader.getLineAndIgnoreWhiteSpaces());
                if (isStringFoundNotCaseSensitive(followingLine, R"(0000)")) {
                    auto msgId = convertHexStringToNumber<unsigned int>(followingLine.substr(18, 2));
                    if (msgId == 0x75 || msgId == 0x77 || msgId == 0x7E) {
                        string const followingLine2(fileReader.getLineAndIgnoreWhiteSpaces());
                        if (isStringFoundNotCaseSensitive(followingLine2, R"(0010)")) {
                            key.said = 0;  // convertHexStringToNumber<unsigned int>(followingLine2.substr(6,11));
                            if (msgId == 0x75) {
                                key.operation = 1;
                            } else if (msgId == 0x77) {
                                key.operation = 2;
                            } else if (msgId == 0x7E) {
                                key.operation = 3;
                            } else {
                                key.operation = 4;
                            }
                            WiresharkLogDelay& wiresharkLogDelay = wiresharkLogDelays[key];

                            wiresharkLogDelay.startTimeOptional = wiresharkTime;
                            wiresharkLogDelay.numberInWiresharkOfStart = numberInWireshark;
                        }
                    } else if (msgId == 0x74 || msgId == 0x76 || msgId == 0x7C) {
                        string const followingLine2(fileReader.getLineAndIgnoreWhiteSpaces());
                        if (isStringFoundNotCaseSensitive(followingLine2, R"(0010)")) {
                            key.said = 0;
                            if (msgId == 0x74) {
                                key.operation = 1;
                            } else if (msgId == 0x76) {
                                key.operation = 2;
                            } else if (msgId == 0x7C) {
                                key.operation = 3;
                            } else {
                                key.operation = 4;
                            }
                            WiresharkLogDelay& wiresharkLogDelay = wiresharkLogDelays[key];
                            wiresharkLogDelay.endTimeOptional = wiresharkTime;
                            wiresharkLogDelay.numberInWiresharkOfEnd = numberInWireshark;
                        }
                    }
                    break;
                }
            }
            WiresharkLogDelay& checkWiresharkLogDelay = wiresharkLogDelays[key];
            if (checkWiresharkLogDelay.startTimeOptional && checkWiresharkLogDelay.endTimeOptional &&
                checkWiresharkLogDelay.startTimeOptional.value() <= checkWiresharkLogDelay.endTimeOptional.value()) {
                double const delay =
                    checkWiresharkLogDelay.endTimeOptional.value() - checkWiresharkLogDelay.startTimeOptional.value();
                maxDelay = std::max(maxDelay, delay);
                totalDelay += delay;
                ++count;
                stringstream ss;
                ss << "0x" << std::hex << key.said << ",";
                ss.precision(17);
                ss << std::dec << checkWiresharkLogDelay.startTimeOptional.value() << ","
                   << checkWiresharkLogDelay.endTimeOptional.value() << ","
                   << checkWiresharkLogDelay.numberInWiresharkOfStart << ","
                   << checkWiresharkLogDelay.numberInWiresharkOfEnd << "," << setw(17) << delay;
                logLineInRawDataFile(ss.str());
                wiresharkLogDelays.erase(key);
            }
        }
    }
    cout << "Average Delay:" << totalDelay / count << " Max Delay:" << maxDelay << "\n";
    cout << "endWiresharkTime:" << endWiresharkTime << "\n";
}

void PerformanceAnalyzer::processFileForTopLogs(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";

    double maxCpuTcomLrm = 0;
    double maxCpuTcomGrm = 0;
    double maxCpuTcomRlh = 0;
    double maxCpuTupcConman = 0;
    double maxCpuTcomAalman = 0;
    double maxTotalCpu = 0;
    double maxTotalCpuFromTop = NAN;
    vector<string> processNames;
    vector<double> cpuConsumptions;
    unsigned int state = 0;
    int cpuIndexInLine = 0;
    int commmandIndexInLine = 0;
    stringstream masterStringStream;
    double totalCpuFromTop(0);
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());

        if (isStringFoundNotCaseSensitive(lineInLogs, "=~=~=~=~=~=~=~=~=~=~=~=") ||
            isStringFoundNotCaseSensitive(lineInLogs, "top - ")) {
            state = 1;
        } else if (
            isStringFoundNotCaseSensitive(lineInLogs, "PID") && isStringFoundNotCaseSensitive(lineInLogs, "%CPU") &&
            isStringFoundNotCaseSensitive(lineInLogs, "COMMAND")) {
            state = 2;
            cpuIndexInLine = static_cast<int>(lineInLogs.find("%CPU"));
            commmandIndexInLine = static_cast<int>(lineInLogs.find("COMMAND"));

            double totalCpu(0);
            stringstream ss;
            for (auto const& consumption : cpuConsumptions) {
                totalCpu += consumption;
                ss << consumption << ", ";
            }
            masterStringStream << totalCpuFromTop << ", " << totalCpu << ", " << ss.str() << "\n";
            maxTotalCpu = std::max(maxTotalCpu, totalCpu);
            totalCpuFromTop = 0;
        } else if (state == 1 && isStringFoundNotCaseSensitive(lineInLogs, "%Cpu0  :")) {
            unsigned int const bracketCpuIndexInLine(lineInLogs.find('['));
            totalCpuFromTop = convertStringToNumber<double>(lineInLogs.substr(bracketCpuIndexInLine - 3, 3));
            maxTotalCpuFromTop = std::max(maxTotalCpuFromTop, totalCpuFromTop);
        }
        if (state == 2 && isNotNpos(commmandIndexInLine) && isNotNpos(cpuIndexInLine) &&
            commmandIndexInLine < lineInLogs.length() && cpuIndexInLine + 5 < lineInLogs.length()) {
            string const processName(
                getStringWithoutStartingAndTrailingWhiteSpace(lineInLogs.substr(commmandIndexInLine)));
            auto cpuLoad = convertStringToNumber<double>(lineInLogs.substr(cpuIndexInLine, 5));
            if (cpuLoad > 0 && processName != "`- top") {
                int i = 0;
                bool isFound(false);
                for (; i < processNames.size(); ++i) {
                    if (processNames[i] == processName) {
                        isFound = true;
                        break;
                    }
                }
                if (isFound) {
                    cpuConsumptions[i] = cpuLoad;
                } else {
                    processNames.emplace_back(processName);
                    cpuConsumptions.emplace_back(cpuLoad);
                }
            }

            if (isStringFoundNotCaseSensitive(lineInLogs, R"(_LRM_)")) {
                maxCpuTcomLrm = std::max(maxCpuTcomLrm, cpuLoad);
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(_GRM_)")) {
                maxCpuTcomGrm = std::max(maxCpuTcomGrm, cpuLoad);
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(_RLH_)")) {
                maxCpuTcomRlh = std::max(maxCpuTcomRlh, cpuLoad);
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(Conman_EU)")) {
                maxCpuTupcConman = std::max(maxCpuTupcConman, cpuLoad);
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(Aalman_EU)")) {
                maxCpuTcomAalman = std::max(maxCpuTcomAalman, cpuLoad);
            }
        }
    }
    cout << "Max Total CPU from TOP:" << maxTotalCpuFromTop << "\n";
    cout << "Max Total CPU:" << maxTotalCpu << "\n";
    cout << "Max CPU GRM TCOM:" << maxCpuTcomGrm << "\n";
    cout << "Max CPU LRM TCOM:" << maxCpuTcomLrm << "\n";
    cout << "Max CPU RLH TCOM:" << maxCpuTcomRlh << "\n";
    cout << "Max CPU TUP Conman:" << maxCpuTupcConman << "\n";
    cout << "Max CPU TUP Aalman:" << maxCpuTcomAalman << "\n";

    stringstream ss;
    ss << "totalCpuFromTop, totalCpu, ";
    for (auto const& processName : processNames) {
        ss << processName << ", ";
    }
    logLineInRawDataFile(ss.str());
    logLineInRawDataFile(masterStringStream.str());
}

void PerformanceAnalyzer::processFileForTopLogsMem(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";

    double maxMemTcomLrm = 0;
    double maxMemTcomGrm = 0;
    double maxMemTupcConman = 0;
    double maxMemTcomAalman = 0;
    vector<string> processNames;
    vector<double> memConsumptions;
    unsigned int state = 0;
    int memIndexInLine = 0;
    int commmandIndexInLine = 0;
    stringstream masterStringStream;
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());

        if (isStringFoundNotCaseSensitive(lineInLogs, "=~=~=~=~=~=~=~=~=~=~=~=") ||
            isStringFoundNotCaseSensitive(lineInLogs, "top - ")) {
            state = 1;
        } else if (
            isStringFoundNotCaseSensitive(lineInLogs, "PID") && isStringFoundNotCaseSensitive(lineInLogs, "MEM") &&
            isStringFoundNotCaseSensitive(lineInLogs, "COMMAND")) {
            state = 2;
            memIndexInLine = static_cast<int>(lineInLogs.find("MEM"));
            commmandIndexInLine = static_cast<int>(lineInLogs.find("COMMAND"));

            double totalMem(0);
            stringstream ss;
            for (auto const& consumption : memConsumptions) {
                totalMem += consumption;
                ss << consumption << ", ";
            }
            masterStringStream << totalMem << ", " << ss.str() << "\n";
        }
        if (state == 2 && isNotNpos(commmandIndexInLine) && isNotNpos(memIndexInLine) &&
            commmandIndexInLine < lineInLogs.length() && memIndexInLine + 5 < lineInLogs.length()) {
            string const processName(
                getStringWithoutStartingAndTrailingWhiteSpace(lineInLogs.substr(commmandIndexInLine)));
            auto memLoad = convertStringToNumber<double>(lineInLogs.substr(memIndexInLine - 1, 4));
            if (memLoad > 0 && processName != "`- top") {
                int i = 0;
                bool isFound(false);
                for (; i < processNames.size(); ++i) {
                    if (processNames[i] == processName) {
                        isFound = true;
                        break;
                    }
                }
                if (isFound) {
                    memConsumptions[i] = memLoad;
                } else {
                    processNames.emplace_back(processName);
                    memConsumptions.emplace_back(memLoad);
                }
            }

            if (isStringFoundNotCaseSensitive(lineInLogs, R"(_LRM_)")) {
                maxMemTcomLrm = std::max(maxMemTcomLrm, memLoad);
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(TCOM_GRM_TASK)")) {
                maxMemTcomGrm = std::max(maxMemTcomGrm, memLoad);
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(Conman_EU)")) {
                maxMemTupcConman = std::max(maxMemTupcConman, memLoad);
            } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(Aalman_EU)")) {
                maxMemTcomAalman = std::max(maxMemTcomAalman, memLoad);
            }
        }
    }
    cout << "Max MEM GRM TCOM:" << maxMemTcomGrm << "\n";
    cout << "Max MEM LRM TCOM:" << maxMemTcomLrm << "\n";
    cout << "Max MEM TUP Conman:" << maxMemTupcConman << "\n";
    cout << "Max MEM TUP Aalman:" << maxMemTcomAalman << "\n";

    stringstream ss;
    ss << "totalMEM, ";
    for (auto const& processName : processNames) {
        ss << processName << ", ";
    }
    logLineInRawDataFile(ss.str());
    logLineInRawDataFile(masterStringStream.str());
}

void PerformanceAnalyzer::processFileForRlSetupPerSecond(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";
    logLineInRawDataFile("BtsTime,instances");

    int hour = 0;
    int min = 0;
    int sec = 0;
    int instances = 0;
    BtsLogTime const firstLogTime;
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        BtsLogPrint const logPrint(lineInLogs);
        BtsLogTime const logTime(logPrint.getBtsTime());

        // int hourOffsetForDay = 0;
        // cout<<"hourOffsetForDay"<<hourOffsetForDay<<"D1:"<<firstLogTime.getDays()<<"D1:"<<logTime.getDays()<<"\n";
        if (!logTime.isStartup()) {
            if ((hour == logTime.getHours()) && (min == logTime.getMinutes()) && (sec == logTime.getSeconds())) {
                ++instances;
            } else {
                stringstream ss;
                ss << hour << ":" << min << ":" << sec << "," << instances;
                logLineInRawDataFile(ss.str());
                hour = static_cast<int>(logTime.getHours());
                min = static_cast<int>(logTime.getMinutes());
                sec = static_cast<int>(logTime.getSeconds());
                instances = 1;
            }
        }
    }
    stringstream ss;
    ss << hour << ":" << min << ":" << sec << "," << instances;
    logLineInRawDataFile(ss.str());
}

void PerformanceAnalyzer::processFileForTraceLog(string const& traceLogPath) {
    AlbaLocalPathHandler const filePathHandler(traceLogPath);
    ifstream inputLogFileStream(traceLogPath);
    AlbaFileReader fileReader(inputLogFileStream);

    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";

    stringstream ss;
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (isStringFoundNotCaseSensitive(lineInLogs, R"(START time=)")) {
            int const hour = convertStringToNumber<int>(lineInLogs.substr(22, 2));
            int const min = convertStringToNumber<int>(lineInLogs.substr(25, 2));
            int const sec = convertStringToNumber<int>(lineInLogs.substr(28, 2));
            ss << hour << ":" << min << ":" << sec << ",";
        } else if (isStringFoundNotCaseSensitive(lineInLogs, R"(STOP  time=)")) {
            int const hour = convertStringToNumber<int>(lineInLogs.substr(22, 2));
            int const min = convertStringToNumber<int>(lineInLogs.substr(25, 2));
            int const sec = convertStringToNumber<int>(lineInLogs.substr(28, 2));
            ss << hour << ":" << min << ":" << sec;
        }
    }
    logLineInRawDataFile(ss.str());
}

void PerformanceAnalyzer::processDirectoryForTraceLog(string const& traceLogPath) {
    logLineInRawDataFile("StartTime,EndTime");
    AlbaLocalPathHandler(traceLogPath)
        .findFilesAndDirectoriesUnlimitedDepth(
            [](AlbaLocalPathHandler::LocalPath const&) {},
            [&](AlbaLocalPathHandler::LocalPath const& filePath) {
                if (isStringFoundNotCaseSensitive(filePath.string(), "trace")) {
                    processFileForTraceLog(AlbaLocalPathHandler(filePath).getPath().string());
                }
            });
}

int PerformanceAnalyzer::getDelayTimeInUs(BtsLogTime const& endTime, BtsLogTime const& startTime) {
    BtsLogTime const delayTime = endTime - startTime;
    return static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
}

int PerformanceAnalyzer::getDelayTimeInMinutes(BtsLogTime const& endTime, BtsLogTime const& startTime) {
    BtsLogTime const delayTime = endTime - startTime;
    return static_cast<int>(delayTime.getMinutes());
}

}  // namespace alba
