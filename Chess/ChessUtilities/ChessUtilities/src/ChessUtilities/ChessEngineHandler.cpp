#include "ChessEngineHandler.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Windows/AlbaWindowsHelper.hpp>

#include <array>
#include <iostream>

using namespace alba::stringHelper;
using namespace std;

#define MAX_BUFFER_SIZE 2000

namespace alba::chess {

namespace {

using CallBackData = struct _mydata {
    ChessEngineHandler* epointer;
};

using PointerToCallBackData = CallBackData*;

DWORD WINAPI engineMonitoringCallbackFunction(LPVOID const lpParam) {
    auto pointerToCallBackData = static_cast<PointerToCallBackData>(lpParam);
    auto* chessEngineHandlerPointer = reinterpret_cast<ChessEngineHandler*>(pointerToCallBackData->epointer);
    chessEngineHandlerPointer->startMonitoringEngineOutput();
    return 0;
}

int IsWinNT() {
    OSVERSIONINFO osv{};
    osv.dwOSVersionInfoSize = sizeof(osv);
    GetVersionEx(&osv);
    return static_cast<int>(osv.dwPlatformId == VER_PLATFORM_WIN32_NT);
}

}  // namespace

ChessEngineHandler::ChessEngineHandler(string const& enginePath)
    : m_enginePath(enginePath),

      m_startupInfo{},
      m_processInfo{},
      m_engineMonitoringThread{},
      m_threadId{},
      m_inputStreamOnEngineThread{},
      m_outputStreamOnEngineThread{},
      m_inputStreamOnHandler{},
      m_outputStreamOnHandler{} {
    initializeEngine();
}

ChessEngineHandler::~ChessEngineHandler() { shutdownEngine(); }

void ChessEngineHandler::reset() {
    log(LogType::HandlerStatus, "Resetting engine");
    shutdownEngine();
    initializeEngine();
}

void ChessEngineHandler::sendStringToEngine(string const& stringToEngine) {
    DWORD bytesWritten{};
    string stringToWrite(stringToEngine);
    stringToWrite += "\n";
    long remainingLength = stringToWrite.length();
    bool isSuccessful(true);
    // NOLINTBEGIN(bugprone-infinite-loop)
    while (isSuccessful && remainingLength > 0) {
        isSuccessful =
            (WriteFile(m_inputStreamOnHandler, stringToWrite.c_str(), remainingLength, &bytesWritten, nullptr) != 0);
        if (isSuccessful) {
            remainingLength = remainingLength - bytesWritten;
            if (remainingLength > 0) {
                stringToWrite = stringToWrite.substr(bytesWritten, remainingLength);
            }
        } else {
            cout << "Error on sendStringToEngine: " << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        }
    }
    // NOLINTEND(bugprone-infinite-loop)
    log(LogType::ToEngine, stringToEngine);
}

void ChessEngineHandler::processStringFromEngine(string const& stringFromEngine) {
    log(LogType::FromEngine, stringFromEngine);
    if (m_additionalStepsInProcessingAStringFromEngine) {
        m_additionalStepsInProcessingAStringFromEngine.value()(stringFromEngine);
    }
}

void ChessEngineHandler::startMonitoringEngineOutput() {
    lock_guard<mutex> const lockGuard(m_readMutex);
    DWORD bytesRead{};       // bytes read
    DWORD bytesAvailable{};  // bytes available
    array<char, MAX_BUFFER_SIZE> buffer{};
    string stringBuffer;
    while (true) {
        PeekNamedPipe(m_outputStreamOnHandler, buffer.data(), MAX_BUFFER_SIZE, nullptr, &bytesAvailable, nullptr);
        if (bytesAvailable > 0) {
            ReadFile(m_outputStreamOnHandler, buffer.data(), MAX_BUFFER_SIZE, &bytesRead, nullptr);
            stringBuffer.reserve(stringBuffer.size() + bytesRead);
            copy(buffer.begin(), buffer.begin() + bytesRead, back_inserter(stringBuffer));

            int currentIndex(0U);
            bool shouldContinue(true);
            while (shouldContinue) {
                int const startIndex = currentIndex;
                int const newLineIndex = stringBuffer.find_first_of("\r\n", startIndex);
                if (isNotNpos(static_cast<int>(newLineIndex))) {
                    string const oneLine(stringBuffer.substr(startIndex, newLineIndex - startIndex));
                    if (!oneLine.empty()) {
                        processStringFromEngine(oneLine);
                    }
                    currentIndex = newLineIndex + 1;
                } else {
                    if (currentIndex > 0) {
                        stringBuffer = stringBuffer.substr(currentIndex);
                    }
                    shouldContinue = false;
                }
            }
        } else if (!stringBuffer.empty()) {
            processStringFromEngine(stringBuffer);
            stringBuffer.clear();
        }
        Sleep(1);
    }
}

void ChessEngineHandler::setLogFile(string const& logFilePath) {
    m_logFileStreamOptional.emplace();
    m_logFileStreamOptional->open(logFilePath);

    if (!m_logFileStreamOptional->is_open()) {
        log(LogType::HandlerStatus, string("Cannot open log file") + logFilePath);
    }
}

void ChessEngineHandler::setAdditionalStepsInProcessingAStringFromEngine(
    ProcessAStringFunction const& additionalSteps) {
    m_additionalStepsInProcessingAStringFromEngine = additionalSteps;
}

void ChessEngineHandler::initializeEngine() {
    SECURITY_DESCRIPTOR securityDescriptor{};  // security information for pipes
    SECURITY_ATTRIBUTES securityAttributes;

    if (IsWinNT() != 0) {
        InitializeSecurityDescriptor(&securityDescriptor, SECURITY_DESCRIPTOR_REVISION);
        SetSecurityDescriptorDacl(&securityDescriptor, 1, nullptr, 0);
        securityAttributes.lpSecurityDescriptor = &securityDescriptor;
    } else {
        securityAttributes.lpSecurityDescriptor = nullptr;
    }

    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = 1;  // allow inheritable handles
    if (CreatePipe(&(m_inputStreamOnEngineThread), &(m_inputStreamOnHandler), &securityAttributes, 0) == 0) {
        log(LogType::HandlerStatus, "Cannot Create Pipe");
    }

    if (CreatePipe(&(m_outputStreamOnHandler), &(m_outputStreamOnEngineThread), &securityAttributes, 0) == 0) {
        log(LogType::HandlerStatus, "Cannot Create Pipe");
    }
    GetStartupInfo(&m_startupInfo);  // set startupinfo for the spawned process
    m_startupInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    m_startupInfo.wShowWindow = SW_HIDE;  // SW_SHOWDEFAULT;//
    m_startupInfo.hStdOutput = m_outputStreamOnEngineThread;
    m_startupInfo.hStdError = m_outputStreamOnEngineThread;
    m_startupInfo.hStdInput = m_inputStreamOnEngineThread;

    // spawn the child process
    if (!CreateProcess(
            m_enginePath.c_str(), nullptr, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, nullptr, nullptr, &m_startupInfo,
            &m_processInfo)) {
        log(LogType::HandlerStatus, "Cannot Create Process");
    }
    auto pData = new CallBackData();
    pData->epointer = this;
    m_engineMonitoringThread = CreateThread(nullptr, 0, engineMonitoringCallbackFunction, pData, 0, &(m_threadId));
}

void ChessEngineHandler::shutdownEngine() {
    sendStringToEngine("quit\n");
    // WaitForSingleObject(m_engineMonitoringThread, INFINITE); // not needed
    CloseHandle(m_engineMonitoringThread);
    TerminateProcess(m_processInfo.hProcess, 0);
    CloseHandle(m_outputStreamOnEngineThread);
    CloseHandle(m_outputStreamOnHandler);
    CloseHandle(m_inputStreamOnEngineThread);
    CloseHandle(m_inputStreamOnHandler);
}

void ChessEngineHandler::log(LogType const logtype, string const& logString) {
    if (m_logFileStreamOptional) {
        m_logFileStreamOptional.value() << getLogHeader(logtype) << logString << "\n";
        m_logFileStreamOptional.value().flush();
    }
}

string ChessEngineHandler::getLogHeader(LogType const logtype) {
    string result;
    switch (logtype) {
        case LogType::FromEngine: {
            result = "From engine: ";
            break;
        }
        case LogType::ToEngine: {
            result = "To engine: ";
            break;
        }
        case LogType::HandlerStatus: {
            result = "HandlerStatus: ";
            break;
        }
    }
    return result;
}

}  // namespace alba::chess
