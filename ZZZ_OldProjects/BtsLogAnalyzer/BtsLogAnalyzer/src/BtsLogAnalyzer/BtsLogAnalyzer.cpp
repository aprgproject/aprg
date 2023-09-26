#include "BtsLogAnalyzer.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WcdmaToolsBackend/BtsLogPrint.hpp>

#include <iomanip>
#include <iostream>
#include <set>

using namespace std;
using namespace wcdmaToolsBackend;

namespace alba {

BtsLogAnalyzer::BtsLogAnalyzer() : m_totalDelay(0), m_count(0) {}

BtsLogAnalyzer::BtsLogAnalyzer(string const& pathOfOutputFile)
    : m_outputStream(pathOfOutputFile), m_totalDelay(0), m_count(0) {
    if (m_outputStream.is_open()) {
        cout << "OutputStream is opened. Saving to output files"
             << "\n";
    }
}

double BtsLogAnalyzer::getComputedAverageDelay() const {
    cout << "totalDelay: " << m_totalDelay << " count: " << m_count << "\n";
    return m_totalDelay / m_count;
}

void BtsLogAnalyzer::processDirectoryForWireSharkDelay(string const& directoryPath) {
    AlbaLocalPathHandler(directoryPath)
        .findFilesAndDirectoriesUnlimitedDepth(
            [](AlbaLocalPathHandler::LocalPath const&) {},
            [&](AlbaLocalPathHandler::LocalPath const& filePath) {
                processFileForWireSharkDelay(AlbaLocalPathHandler(filePath).getPath().string());
            });
}

void BtsLogAnalyzer::processFileForWireSharkDelay(string const& filePath) {
    m_wireSharkDelays.clear();
    cout << "processFile: " << AlbaLocalPathHandler(filePath).getFile() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    optional<double> startTimeFetchedOptional;
    optional<double> endTimeFetchedOptional;

    if (!inputLogFileStream.is_open()) {
        cout << "Cannot open file: " << filePath << "\n";
    }
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(
                lineInLogs, R"(id-radioLinkSetup , RadioLinkSetupRequestFDD)")) {
            startTimeFetchedOptional = getWireSharkTime(lineInLogs);
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(id-radioLinkSetup , RadioLinkSetupResponseFDD)")) {
            endTimeFetchedOptional = getWireSharkTime(lineInLogs);
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(CRNC-CommunicationContextID: )")) {
            int const crnccId = stringHelper::convertStringToNumber<int>(
                getNumberAfterThisString(lineInLogs, "CRNC-CommunicationContextID: "));
            WireSharkDelay& delayForCrnccId = m_wireSharkDelays[crnccId];
            if (startTimeFetchedOptional) {
                delayForCrnccId.startTimeOptional = startTimeFetchedOptional;
            }
            if (endTimeFetchedOptional) {
                delayForCrnccId.endTimeOptional = endTimeFetchedOptional;
            }
            startTimeFetchedOptional.reset();
            endTimeFetchedOptional.reset();

            if (delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional) {
                double const delay =
                    delayForCrnccId.endTimeOptional.value() - delayForCrnccId.startTimeOptional.value();
                m_totalDelay += delay;
                ++m_count;
                m_outputStream << crnccId << "," << setw(10) << delay << "\n";
                // cout<<"CrnccId: "<<crnccId<<" Delay: "<<delay<<" count: "<<m_count<<" totalDelay:
                // "<<m_totalDelay<<"\n";
                m_wireSharkDelays.erase(crnccId);
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(No.     Time)")) {
            startTimeFetchedOptional.reset();
            endTimeFetchedOptional.reset();
        }
    }
}

void BtsLogAnalyzer::processFileForMsgQueuingTime(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getPath() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    int totalMsgQueuingTime = 0;
    int highestMsgQueuingTime = 0;
    int numberOfPrints = 0;
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundCaseSensitive(lineInLogs, "MSG TIME, start queuing time")) {
            int const msgQueuingTime =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgQueuingTime: "));
            totalMsgQueuingTime += msgQueuingTime;
            if (msgQueuingTime > highestMsgQueuingTime) {
                highestMsgQueuingTime = msgQueuingTime;
            }
            m_outputStream << msgQueuingTime << "," << lineInLogs << "\n";
            ++numberOfPrints;
        }
    }
    cout << "TotalMsgQueuingTime: " << totalMsgQueuingTime << " highestMsgQueuingTime: " << highestMsgQueuingTime
         << " AverageMsgQueuingTime: " << (static_cast<double>(totalMsgQueuingTime)) / numberOfPrints
         << " numberOfPrints: " << numberOfPrints << "\n";
}

void BtsLogAnalyzer::processFileForBtsDelayForRlh(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    cout << "processFile: " << filePathHandler.getPath() << " isOpen: " << inputLogFileStream.is_open()
         << " fileReader: " << fileReader.isNotFinished() << "\n";

    m_outputStream << "crnccId,nbccId,transactionId,delay"
                   << "\n";
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            UniqueId uniqueKey;
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)")) {
            UniqueId uniqueKey;
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.endTimeOptional = logPrint.getBtsTime();
            }
            if (delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional &&
                delayForCrnccId.startTimeOptional->getTotalSeconds() <=
                    delayForCrnccId.endTimeOptional->getTotalSeconds()) {
                BtsLogTime const delayTime =
                    delayForCrnccId.endTimeOptional.value() - delayForCrnccId.startTimeOptional.value();
                int const delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                // if(uniqueKey.crnccId == 15167){cout<<"crnccId "<<uniqueKey.crnccId<<"nbccId
                // "<<uniqueKey.nbccId<<"delay "<<delay<<"startTimeOptional
                // "<<delayForCrnccId.startTimeOptional.getReference()<<"endTimeOptional
                // "<<delayForCrnccId.endTimeOptional.getReference()<<"\n";}
                m_totalDelay += delay;
                ++m_count;
                m_outputStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << "," << uniqueKey.transactionId << ","
                               << setw(10) << delay << "\n";
                m_btsLogDelays.erase(uniqueKey);
            }
        }
    }
}

void BtsLogAnalyzer::processFileForBtsDelayForRlDeletion(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getPath() << "\n";

    m_outputStream << "crnccId,nbccId,transactionId,delay"
                   << "\n";
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlDeletionReq3G)")) {
            UniqueId uniqueKey;
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlDeletionResp3G)")) {
            UniqueId uniqueKey;
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crncId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelays[uniqueKey];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.endTimeOptional = logPrint.getBtsTime();
            }
            if (delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional &&
                delayForCrnccId.startTimeOptional->getTotalSeconds() <=
                    delayForCrnccId.endTimeOptional->getTotalSeconds()) {
                BtsLogTime const delayTime =
                    delayForCrnccId.endTimeOptional.value() - delayForCrnccId.startTimeOptional.value();
                int const delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                // if(uniqueKey.crnccId == 15167){cout<<"crnccId "<<uniqueKey.crnccId<<"nbccId
                // "<<uniqueKey.nbccId<<"delay "<<delay<<"startTimeOptional
                // "<<delayForCrnccId.startTimeOptional.getReference()<<"endTimeOptional
                // "<<delayForCrnccId.endTimeOptional.getReference()<<"\n";}
                m_totalDelay += delay;
                ++m_count;
                m_outputStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << "," << uniqueKey.transactionId << ","
                               << setw(10) << delay << "\n";
                m_btsLogDelays.erase(uniqueKey);
            }
        }
    }
}

void BtsLogAnalyzer::processFileForBtsDelayForGrm(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getPath() << "\n";

    m_outputStream << "crnccId,nbccId,transactionId,delay"
                   << "\n";
    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(INF/TCOM/G, Received API_TCOM_RNC_MSG)")) {
            int const nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelaysGrm[nbccId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            int const crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            int const nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            int const transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& delayForCrnccId = m_btsLogDelaysGrm[nbccId];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                delayForCrnccId.endTimeOptional = logPrint.getBtsTime();
            }
            if (delayForCrnccId.startTimeOptional && delayForCrnccId.endTimeOptional &&
                delayForCrnccId.startTimeOptional->getTotalSeconds() <=
                    delayForCrnccId.endTimeOptional->getTotalSeconds()) {
                BtsLogTime const delayTime =
                    delayForCrnccId.endTimeOptional.value() - delayForCrnccId.startTimeOptional.value();
                int const delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                if (delay < 1000000) {
                    m_totalDelay += delay;
                    ++m_count;
                    m_outputStream << crnccId << "," << nbccId << "," << transactionId << "," << setw(10) << delay
                                   << "\n";
                }
                m_btsLogDelaysGrm.erase(nbccId);
            }
        }
        /*else if(stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(INF/TCOM/R,
        CTRL_RLH_)")
                || stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(INF/TCOM/R,
        RLH_CTRL_)")
                || stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(LRM_RL_)")
                || stringHelper::isStringFoundNotCaseSensitive(lineInLogs,
        R"(TC_2_RL_SETUP_IND_MSG)")
                || stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(BB_2_RL_)")
                )
        {
            int nbccId = stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            m_btsLogDelaysGrm.erase(nbccId);
        }*/
    }
}

void BtsLogAnalyzer::processFileForToCountUsersWithTracing(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getPath() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);
    set<int> usersWithTracing;
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundCaseSensitive(lineInLogs, "RLH sends BB_UE_TRACING_REPORT_IND_MSG (0x515D)")) {
            int const msgType =
                stringHelper::convertHexStringToNumber<int>(getNumberAfterThisString(lineInLogs, "msgType: 0x"));
            int const nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            if (msgType == 0x1200) {
                usersWithTracing.emplace(nbccId);
                cout << "msgType: " << msgType << " nbccId: " << nbccId
                     << " number of usersWithTracing: " << usersWithTracing.size() << "\n";
            } else if (msgType == 0x1300) {
                usersWithTracing.erase(nbccId);
                cout << "msgType: " << msgType << " nbccId: " << nbccId
                     << " number of usersWithTracing: " << usersWithTracing.size() << "\n";
            }
        }
    }
}

void BtsLogAnalyzer::processFileForBtsDelayForMikhailKnife(string const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    cout << "processFile: " << filePathHandler.getPath() << "\n";

    ifstream inputLogFileStream(filePath);
    AlbaFileReader fileReader(inputLogFileStream);

    ofstream grmFetchFileStream(filePathHandler.getDirectory() / R"(grmFetchFileStream.csv)");
    ofstream grmProcessFileStream(filePathHandler.getDirectory() / R"(grmProcessFileStream.csv)");
    ofstream messageDeliveryFileStream(filePathHandler.getDirectory() / R"(messageDeliveryFileStream.csv)");
    ofstream rlSetupFileStream(filePathHandler.getDirectory() / R"(rlSetupFileStream.csv)");
    grmFetchFileStream << "crnccId,"
                       << "nbccId,"
                       << "transactionId,"
                       << "difference"
                       << "\n";
    grmProcessFileStream << "crnccId,"
                         << "nbccId,"
                         << "transactionId,"
                         << "delay"
                         << "\n";
    messageDeliveryFileStream << "crnccId,"
                              << "nbccId,"
                              << "transactionId,"
                              << "delay"
                              << "\n";
    rlSetupFileStream << "crnccId,"
                      << "nbccId,"
                      << "transactionId,"
                      << "delay"
                      << "\n";

    std::map<UniqueId, BtsLogDelay> grmProcessMap;
    std::map<UniqueId, BtsLogDelay> messageDeliveryMap;
    std::map<UniqueId, BtsLogDelay> rlSetupMap;

    double grmFetchTotal = 0;
    int grmFetchCount = 0;
    double grmProcessTotal = 0;
    int grmProcessCount = 0;
    double messageDeliveryTotal = 0;
    int messageDeliveryCount = 0;
    double rlSetupTotal = 0;
    int rlSetupCount = 0;

    while (fileReader.isNotFinished()) {
        UniqueId uniqueKey;
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(
                lineInLogs, R"(INF/TCOM/G, decodeRadioLinkRequest API_TCOM_RNC_MSG)")) {
            int const crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            int const nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            int const transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            unsigned int const difference =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "diff in ms: "));
            if (difference != 0x80000000) {
                grmFetchTotal += difference * 1000;
                ++grmFetchCount;
                grmFetchFileStream << crnccId << "," << nbccId << "," << transactionId << "," << setw(10) << difference
                                   << "\n";
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(
                       lineInLogs, R"(INF/TCOM/G, Received API_TCOM_RNC_MSG)")) {
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& processMapInstance = grmProcessMap[uniqueKey];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                processMapInstance.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(INF/TCOM/G, Sending API_TCOM_RNC_MSG)")) {
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& processMapInstance = grmProcessMap[uniqueKey];
            BtsLogDelay& messageDeliveryInstance = messageDeliveryMap[uniqueKey];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                processMapInstance.endTimeOptional = logPrint.getBtsTime();
                messageDeliveryInstance.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(CTRL_RLH_RlSetupReq3G)")) {
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& messageDeliveryInstance = messageDeliveryMap[uniqueKey];
            BtsLogDelay& rlSetupMapInstance = rlSetupMap[uniqueKey];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                messageDeliveryInstance.endTimeOptional = logPrint.getBtsTime();
                rlSetupMapInstance.startTimeOptional = logPrint.getBtsTime();
            }
        } else if (stringHelper::isStringFoundNotCaseSensitive(lineInLogs, R"(RLH_CTRL_RlSetupResp3G)")) {
            uniqueKey.crnccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "crnccId: "));
            uniqueKey.nbccId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "nbccId: "));
            uniqueKey.transactionId =
                stringHelper::convertStringToNumber<int>(getNumberAfterThisString(lineInLogs, "transactionId: "));
            BtsLogDelay& rlSetupMapInstance = rlSetupMap[uniqueKey];
            BtsLogPrint const logPrint(lineInLogs);
            if (!logPrint.getBtsTime().isStartup()) {
                rlSetupMapInstance.endTimeOptional = logPrint.getBtsTime();
            }
        }

        BtsLogDelay& processMapInstance = grmProcessMap[uniqueKey];
        if (processMapInstance.startTimeOptional && processMapInstance.endTimeOptional) {
            if (processMapInstance.startTimeOptional.value() < processMapInstance.endTimeOptional.value()) {
                BtsLogTime const delayTime =
                    processMapInstance.endTimeOptional.value() - processMapInstance.startTimeOptional.value();
                int const delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                grmProcessTotal += delay;
                ++grmProcessCount;
                grmProcessFileStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << "," << uniqueKey.transactionId
                                     << "," << setw(10) << delay << "\n";
            }
            grmProcessMap.erase(uniqueKey);
        }

        BtsLogDelay& messageDeliveryInstance = messageDeliveryMap[uniqueKey];
        if (messageDeliveryInstance.startTimeOptional && messageDeliveryInstance.endTimeOptional) {
            if (messageDeliveryInstance.startTimeOptional.value() < messageDeliveryInstance.endTimeOptional.value()) {
                BtsLogTime const delayTime =
                    messageDeliveryInstance.endTimeOptional.value() - messageDeliveryInstance.startTimeOptional.value();
                int const delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                messageDeliveryTotal += delay;
                ++messageDeliveryCount;
                messageDeliveryFileStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << ","
                                          << uniqueKey.transactionId << "," << setw(10) << delay << "\n";
            }
            messageDeliveryMap.erase(uniqueKey);
        }

        BtsLogDelay& rlSetupMapInstance = rlSetupMap[uniqueKey];
        if (rlSetupMapInstance.startTimeOptional && rlSetupMapInstance.endTimeOptional) {
            if (rlSetupMapInstance.startTimeOptional.value() < rlSetupMapInstance.endTimeOptional.value()) {
                BtsLogTime const delayTime =
                    rlSetupMapInstance.endTimeOptional.value() - rlSetupMapInstance.startTimeOptional.value();
                int const delay = static_cast<int>(delayTime.getMicroSeconds() + delayTime.getSeconds() * 1000000);
                rlSetupTotal += delay;
                ++rlSetupCount;
                rlSetupFileStream << uniqueKey.crnccId << "," << uniqueKey.nbccId << "," << uniqueKey.transactionId
                                  << "," << setw(10) << delay << "\n";
            }
            rlSetupMap.erase(uniqueKey);
        }
    }
    cout << "grmFetchTotal: " << grmFetchTotal << " count: " << grmFetchCount
         << " average:" << grmFetchTotal / grmFetchCount << "\n";
    cout << "grmProcessTotal: " << grmProcessTotal << " count: " << grmProcessCount
         << " average:" << grmProcessTotal / grmProcessCount << "\n";
    cout << "messageDeliveryTotal: " << messageDeliveryTotal << " count: " << messageDeliveryCount
         << " average:" << messageDeliveryTotal / messageDeliveryCount << "\n";
    cout << "rlSetupTotal: " << rlSetupTotal << " count: " << rlSetupCount << " average:" << rlSetupTotal / rlSetupCount
         << "\n";
}

string BtsLogAnalyzer::getNumberAfterThisString(string const& mainString, string const& stringToSearch) {
    string result;
    int const firstIndexOfFirstString = static_cast<int>(mainString.find(stringToSearch));
    if (stringHelper::isNotNpos(firstIndexOfFirstString)) {
        int const lastIndexOfFirstString = static_cast<int>(firstIndexOfFirstString + stringToSearch.length());
        int lastIndexOfNumber = 0;
        for (lastIndexOfNumber = lastIndexOfFirstString; stringHelper::isNumber(mainString[lastIndexOfNumber]);
             ++lastIndexOfNumber) {
            ;
        }
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber - lastIndexOfFirstString);
    }
    return result;
}

double BtsLogAnalyzer::getWireSharkTime(string const& lineInLogs) {
    int const length(static_cast<int>(lineInLogs.length()));
    int startIndexOfTime = 0;
    int endIndexOfTime = 0;
    int i = 0;
    for (; i < length && stringHelper::isWhiteSpace(lineInLogs[i]); ++i) {
    }
    for (; i < length && stringHelper::isNumber(lineInLogs[i]); ++i) {
    }
    startIndexOfTime = i;
    for (; i < length && stringHelper::isWhiteSpace(lineInLogs[i]); ++i) {
    }
    for (; i < length && !stringHelper::isWhiteSpace(lineInLogs[i]); ++i) {
    }
    endIndexOfTime = i;
    return stringHelper::convertStringToNumber<double>(
        lineInLogs.substr(startIndexOfTime, endIndexOfTime - startIndexOfTime));
}

}  // namespace alba
