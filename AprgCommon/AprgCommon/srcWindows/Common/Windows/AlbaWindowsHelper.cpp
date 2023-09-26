#include "AlbaWindowsHelper.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <windows.h>

#include <sstream>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba::AlbaWindowsHelper {

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
string getLastFormattedErrorMessage() {
    stringstream lastErrorStream;
    auto errorCode = GetLastError();
    lastErrorStream << "No message from windows. Error code: " << errorCode;
    if (errorCode != 0U) {
        LPVOID lpMessageBuffer = nullptr;
        DWORD const bufferLength = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
            errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPTSTR>(&lpMessageBuffer), 0,
            nullptr);
        if (bufferLength != 0U) {
            auto lpMessageString = static_cast<LPCSTR>(lpMessageBuffer);
            string const errorMessageFromWindows(
                getStringWithoutRedundantWhiteSpace(string(lpMessageString, lpMessageString + bufferLength)));
            LocalFree(lpMessageBuffer);
            lastErrorStream.str(string());
            lastErrorStream << "Error from windows: [" << errorMessageFromWindows << "] ErrorCode:[" << errorCode
                            << "]\n";
        }
    }
    return lastErrorStream.str();
}

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

}  // namespace alba::AlbaWindowsHelper
