#include "CPlusPlusFileFixer.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/PathHandler/AlbaPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>

using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {

set<string> const listOfCPlusPlusHeaders{"algorithm",     "any",
                                         "array",         "atomic",
                                         "bitset",        "cassert",
                                         "cctype",        "cerrno",
                                         "cfenv",         "cfloat",
                                         "chrono",        "cinttypes",
                                         "climits",       "clocale",
                                         "cmath",         "codecvt",
                                         "complex",       "condition_variable",
                                         "csetjmp",       "csignal",
                                         "cstdarg",       "cstddef",
                                         "cstdint",       "cstdio",
                                         "cstdlib",       "ctgmath",
                                         "cstring",       "ctime",
                                         "cuchar",        "cwchar",
                                         "cwctype",       "deque",
                                         "exception",     "execution",
                                         "filesystem",    "forward_list",
                                         "fstream",       "functional",
                                         "future",        "initializer_list",
                                         "iomanip",       "ios",
                                         "iosfwd",        "iostream",
                                         "istream",       "iterator",
                                         "limits",        "list",
                                         "locale",        "map",
                                         "memory",        "memory_resource",
                                         "mutex",         "new",
                                         "numeric",       "optional",
                                         "ostream",       "queue",
                                         "random",        "ratio",
                                         "regex",         "scoped_allocator",
                                         "set",           "shared_mutex",
                                         "sstream",       "stack",
                                         "stdexcept",     "streambuf",
                                         "string",        "string_view",
                                         "strstream",     "system_error",
                                         "thread",        "tuple",
                                         "typeindex",     "typeinfo",
                                         "type_traits",   "unordered_map",
                                         "unordered_set", "utility",
                                         "valarray",      "variant",
                                         "vector"};

set<string> const listOfLinuxHeaders{
    "assert.h",       "conio.h",      "crtdbg.h",      "ctype.h",        "curses.h",       "dirent.h",
    "env.h",          "errno.h",      "eti.h",         "fcntl.h",        "float.h",        "fnmatch.h",
    "form.h",         "graph.h",      "grp.h",         "i86.h",          "limits.h",       "locale.h",
    "malloc.h",       "math.h",       "mbctype.h",     "mbstring.h",     "mem.h",          "menu.h",
    "mig.h",          "mqueue.h",     "panel.h",       "pgchart.h",      "process.h",      "pwd.h",
    "queue.h",        "regex.h",      "search.h",      "semaphore.h",    "setjmp.h",       "share.h",
    "signal.h",       "stdarg.h",     "stddef.h",      "stdio.h",        "stdlib.h",       "string.h",
    "sys/audio.h",    "sys/cdrom.h",  "sys/console.h", "sys/con_msg.h",  "sys/debug.h",    "sys/dev.h",
    "sys/dev_msg.h",  "sys/disk.h",   "sys/dumper.h",  "sys/fd.h",       "sys/fsys.h",     "sys/fsysinfo.h",
    "sys/fsys_msg.h", "sys/inline.h", "sys/io_msg.h",  "sys/irqinfo.h",  "sys/kernel.h",   "sys/lmf.h",
    "sys/locking.h",  "sys/magic.h",  "sys/mman.h",    "sys/mouse.h",    "sys/mous_msg.h", "sys/name.h",
    "sys/osinfo.h",   "sys/osstat.h", "sys/pci.h",     "sys/prfx.h",     "sys/proc_msg.h", "sys/proxy.h",
    "sys/psinfo.h",   "sys/qioctl.h", "sys/qnxterm.h", "sys/qnx_glob.h", "sys/sched.h",    "sys/seginfo.h",
    "sys/select.h",   "sys/sendmx.h", "sys/ser_msg.h", "sys/sidinfo.h",  "sys/stat.h",     "sys/sys_msg.h",
    "sys/term.h",     "sys/timeb.h",  "sys/timers.h",  "sys/times.h",    "sys/trace.h",    "sys/tracecod.h",
    "sys/types.h",    "sys/uio.h",    "sys/uscsi.h",   "sys/utsname.h",  "sys/vc.h",       "sys/wait.h",
    "syslog.h",       "tar.h",        "tchar.h",       "term.h",         "termios.h",      "time.h",
    "unctrl.h",       "unicode.h",    "unistd.h",      "unix.h",         "utime.h",        "varargs.h",
    "_comdef.h"};

set<string> const listOfWindowsHeaders{
    "basetsd.h",  "cderr.h",  "commdlg.h",  "ctype.h",    "dde.h",      "ddeml.h",    "dlgs.h",    "excpt.h",
    "guiddef.h",  "imm.h",    "lzexpand.h", "mmsystem.h", "nb30.h",     "objbase.h",  "ole2.h",    "oleauto.h",
    "olectlid.h", "rpc.h",    "shellapi.h", "stdarg.h",   "string.h",   "winbase.h",  "winbgim.h", "wincon.h",
    "wincrypt.h", "windef.h", "windows.h",  "winerror.h", "wingdi.h",   "winnetwk.h", "winnls.h",  "winnt.h",
    "winperf.h",  "winreg.h", "winresrc.h", "winsock.h",  "winspool.h", "winsvc.h",   "winuser.h", "winver.h",
};

}  // namespace

void CPlusPlusFileFixer::processFile(path const& path) {
    // cout<<"ProcessFile: "<<path<<"\n";
    clear();
    checkFile(path.string());
    fix(path.string());
    writeFile(path.string());
}

void CPlusPlusFileFixer::notifyIfAlbaDebugHeaderExistInProductionCode(string const& path) const {
    bool const isAlbaDebugHeaderFound =
        (find(
             m_headerListFromAngleBrackets.cbegin(), m_headerListFromAngleBrackets.cend(),
             string("Debug/AlbaDebug.hpp")) != m_headerListFromAngleBrackets.end());
    if (isAlbaDebugHeaderFound) {
        // !isUnitTest)
        cout << "CHECK THIS: AlbaDebug found in:[" << path << "].\n";
    }
}

void CPlusPlusFileFixer::notifyIfIostreamHeaderExistInProductionCode(string const& path) const {
    AlbaLocalPathHandler const filePathHandler(path);
    bool const isIostreamFound =
        (find(m_headerListFromAngleBrackets.cbegin(), m_headerListFromAngleBrackets.cend(), string("iostream")) !=
         m_headerListFromAngleBrackets.end());
    // bool isCpp = filePathHandler.getExtension() == "cpp";
    bool const isUnitTest = isStringFoundCaseSensitive(filePathHandler.getFile().string(), "_unit.cpp");
    if (isIostreamFound && !isUnitTest) {
        // && !isCpp) // !isUnitTest)
        cout << "CHECK THIS: iostream found in:[" << path << "].\n";
    }
}

void CPlusPlusFileFixer::notifyIfCAssertHeaderExistInProductionCode(string const& path) const {
    bool const isCAssertFound =
        (find(m_headerListFromAngleBrackets.cbegin(), m_headerListFromAngleBrackets.cend(), string("cassert")) !=
         m_headerListFromAngleBrackets.end());
    if (isCAssertFound) {
        cout << "CHECK THIS: cassert found in:[" << path << "].\n";
    }
}

void CPlusPlusFileFixer::notifyIfMoreThanLoopsAreCascaded(string const& path) const {
    set<int> indentionsOfLoops;
    for (string const& line : m_linesAfterTheHeader) {
        if (isLineWithALoopStart(line)) {
            indentionsOfLoops.emplace(getStringThatContainsWhiteSpaceIndention(line).size());
            if (indentionsOfLoops.size() >= 2) {
                cout << "CHECK THIS: More than 2 loops found in:[" << path << "] in line:[" << line << "].\n";
            }
        } else if (isLineWithALoopEnd(line)) {
            auto it = indentionsOfLoops.find(static_cast<int>(getStringThatContainsWhiteSpaceIndention(line).size()));
            if (it != indentionsOfLoops.end()) {
                indentionsOfLoops.erase(it);
            }
        }
    }
}

void CPlusPlusFileFixer::writeHeadersWithQuotations(ofstream& outputLogFileStream) const {
    for (string const& header : m_headerListFromQuotations) {
        if (!header.empty()) {
            outputLogFileStream << R"(#include ")" << header << R"(")"
                                << "\n";
        } else {
            outputLogFileStream << "\n";
        }
    }
    outputLogFileStream << "\n";
}

void CPlusPlusFileFixer::writeHeadersWithAngleBrackets(ofstream& outputLogFileStream) const {
    for (string const& header : m_headerListFromAngleBrackets) {
        if (!header.empty()) {
            outputLogFileStream << R"(#include <)" << header << R"(>)"
                                << "\n";
        } else {
            outputLogFileStream << "\n";
        }
    }
}

void CPlusPlusFileFixer::clear() {
    m_linesAfterTheHeader.clear();
    m_headerListFromAngleBrackets.clear();
    m_headerListFromQuotations.clear();
    m_isPragmaOnceFound = false;
}

void CPlusPlusFileFixer::checkFile(string const& path) {
    readContentsFromFile(path);
    notifyIfAlbaDebugHeaderExistInProductionCode(path);
    // notifyIfCAssertHeaderExistInProductionCode(path);
    // notifyIfIostreamHeaderExistInProductionCode(path);
    // notifyIfMoreThanLoopsAreCascaded(path);
}

void CPlusPlusFileFixer::readContentsFromFile(string const& path) {
    AlbaLocalPathHandler const filePathHandler(path);
    ifstream inputLogFileStream(filePathHandler.getPath());
    AlbaFileReader fileReader(inputLogFileStream);
    bool isOnHeaderPart(true);
    while (fileReader.isNotFinished()) {
        string const line(fileReader.getLine());
        if (isOnHeaderPart) {
            if (isStringFoundCaseSensitive(line, "#include")) {
                notifyIfThereAreCommentsInHeader(path, line);
                readLineWithSharpInclude(line, path);
            } else if (isStringFoundCaseSensitive(line, "#pragma") && isStringFoundCaseSensitive(line, "once")) {
                m_isPragmaOnceFound = true;
            } else if (!isWhiteSpace(line)) {
                m_linesAfterTheHeader.emplace_back(line);
                isOnHeaderPart = false;
            }
        } else {
            m_linesAfterTheHeader.emplace_back(line);
        }
    }
}

void CPlusPlusFileFixer::readLineWithSharpInclude(string const& line, string const& path) {
    string const headerFromAngleBrackets(getStringInBetweenTwoStrings(line, R"(<)", R"(>)"));
    string const headerFromQuotations(getStringInBetweenTwoStrings(line, R"(")", R"(")"));
    if (!headerFromAngleBrackets.empty()) {
        AlbaLocalPathHandler const filePathHandler(path);
        AlbaPathHandler const headerFromAngleBracketsPathHandler(headerFromAngleBrackets, "/");
        if (headerFromAngleBracketsPathHandler.getFilenameOnly() == filePathHandler.getFilenameOnly() &&
            isStringFoundCaseSensitive(filePathHandler.getPath().string(), headerFromAngleBrackets)) {
            addHeaderFileFromQuotations(filePathHandler.getFile().string());
        } else {
            addHeaderFileFromAngleBrackets(headerFromAngleBrackets);
        }
    }
    if (!headerFromQuotations.empty()) {
        addHeaderFileFromQuotations(headerFromQuotations);
    }
}

void CPlusPlusFileFixer::fix(string const& path) {
    fixHeaders(path);
    removeTrailingLinesInCode();
    fixNamespaces();
    fixSmallUToCapitalUInNumbers();
}

void CPlusPlusFileFixer::fixHeaders(string const&) {
    set<string> cPlusPlusHeaders;
    set<string> otherLibraryHeaders;
    set<string> aprgFiles;
    for (string const& header : m_headerListFromAngleBrackets) {
        if (isCPlusPlusHeader(header)) {
            cPlusPlusHeaders.emplace(header);
        } else if (isOtherLibraryHeaders(header)) {
            otherLibraryHeaders.emplace(header);
        } else {
            aprgFiles.emplace(header);
        }
    }
    m_headerListFromAngleBrackets.clear();
    if (!aprgFiles.empty()) {
        for (string const& header : aprgFiles) {
            addHeaderFileFromAngleBrackets(header);
        }
        addHeaderFileFromAngleBrackets(string());
    }
    if (!otherLibraryHeaders.empty()) {
        for (string const& header : otherLibraryHeaders) {
            addHeaderFileFromAngleBrackets(header);
        }
        addHeaderFileFromAngleBrackets(string());
    }
    if (!cPlusPlusHeaders.empty()) {
        for (string const& header : cPlusPlusHeaders) {
            addHeaderFileFromAngleBrackets(header);
        }
        addHeaderFileFromAngleBrackets(string());
    }
}

void CPlusPlusFileFixer::removeTrailingLinesInCode() {
    auto nonWhiteSpaceLineIterator = m_linesAfterTheHeader.rbegin();
    for (; nonWhiteSpaceLineIterator != m_linesAfterTheHeader.rend(); ++nonWhiteSpaceLineIterator) {
        if (!isWhiteSpace(*nonWhiteSpaceLineIterator)) {
            break;
        }
    }
    m_linesAfterTheHeader.erase(nonWhiteSpaceLineIterator.base(), m_linesAfterTheHeader.end());
}

void CPlusPlusFileFixer::fixNamespaces() {
    for (string& line : m_linesAfterTheHeader) {
        string const firstWord(getStringBeforeThisString(getStringWithoutStartingAndTrailingWhiteSpace(line), " "));
        if ("namespace" == firstWord) {
            replaceAllAndReturnIfFound(line, "{", "\n{");
        }
    }
}

void CPlusPlusFileFixer::fixSmallUToCapitalUInNumbers() {
    for (string& line : m_linesAfterTheHeader) {
        int indexOfU = static_cast<int>(line.find('u'));
        while (isNotNpos(indexOfU)) {
            bool isCharacterBeforeUANumber(false);
            bool isCharacterAfterUNotALetterOrNumberOrUnderscore(false);
            if (indexOfU > 0) {
                isCharacterBeforeUANumber = isNumber(line[indexOfU - 1]);
            }
            if (indexOfU + 1 < static_cast<int>(line.length())) {
                isCharacterAfterUNotALetterOrNumberOrUnderscore = !isLetterOrNumberOrUnderscore(line[indexOfU + 1]);
            } else {
                isCharacterAfterUNotALetterOrNumberOrUnderscore = true;
            }
            if (isCharacterBeforeUANumber && isCharacterAfterUNotALetterOrNumberOrUnderscore) {
                line[indexOfU] = 'U';
            }
            indexOfU = static_cast<int>(line.find('u', indexOfU + 1));
        }
    }
}

void CPlusPlusFileFixer::addHeaderFileFromAngleBrackets(string const& header) {
    AlbaPathHandler const headerPathHandler(header, "/");
    m_headerListFromAngleBrackets.emplace_back(headerPathHandler.getPath());
}

void CPlusPlusFileFixer::addHeaderFileFromQuotations(string const& header) {
    AlbaPathHandler const headerPathHandler(header, "/");
    m_headerListFromQuotations.emplace(headerPathHandler.getPath());
}

void CPlusPlusFileFixer::writeFile(string const& path) {
    AlbaLocalPathHandler const filePathHandler(path);
    ofstream outputLogFileStream(filePathHandler.getPath());
    if (m_isPragmaOnceFound) {
        outputLogFileStream << "#pragma once\n";
        outputLogFileStream << "\n";
    }
    if (!m_headerListFromQuotations.empty()) {
        writeHeadersWithQuotations(outputLogFileStream);
    }
    if (!m_headerListFromAngleBrackets.empty()) {
        writeHeadersWithAngleBrackets(outputLogFileStream);
    }
    for (string const& line : m_linesAfterTheHeader) {
        outputLogFileStream << line << "\n";
    }
}

bool CPlusPlusFileFixer::isOtherLibraryHeaders(string const& header) {
    bool result(false);
    if (isLinuxHeader(header) || isWindowsHeader(header) || isGtestHeader(header) || isQtHeader(header)) {
        result = true;
    }
    return result;
}

void CPlusPlusFileFixer::notifyIfThereAreCommentsInHeader(string const& path, string const& line) {
    if (isStringFoundCaseSensitive(line, "//")) {
        cout << "CHECK THIS: Header comments on:[" << path << "] in line:[" << line << "]\n";
    }
}

bool CPlusPlusFileFixer::isLineWithALoopStart(string const& line) {
    bool result(false);
    if (isStringFoundCaseSensitive(line, "for(") || isStringFoundCaseSensitive(line, "while(")) {
        result = true;
    }
    return result;
}

bool CPlusPlusFileFixer::isLineWithALoopEnd(string const& line) {
    bool result(false);
    if (isStringFoundCaseSensitive(line, "}") && !isStringFoundCaseSensitive(line, "{")) {
        result = true;
    }
    return result;
}

bool CPlusPlusFileFixer::isPathIgnored(string const& path) {
    bool result(false);
    if (isStringFoundCaseSensitive(path, "ACodeReview") || isStringFoundCaseSensitive(path, "AllCommonCMakeFiles") ||
        isStringFoundCaseSensitive(path, "CImg") || isStringFoundCaseSensitive(path, "curl-7.38.0") ||
        isStringFoundCaseSensitive(path, "CurlCpp") || isStringFoundCaseSensitive(path, "gsl1.8") ||
        isStringFoundCaseSensitive(path, "gtest-1.7.0") || isStringFoundCaseSensitive(path, "plantumlqeditor") ||
        isStringFoundCaseSensitive(path, "zlib128")) {
        result = true;
    }
    return result;
}

bool CPlusPlusFileFixer::isCPlusPlusHeader(string const& header) {
    return listOfCPlusPlusHeaders.find(header) != listOfCPlusPlusHeaders.cend();
}

bool CPlusPlusFileFixer::isLinuxHeader(string const& header) {
    return listOfLinuxHeaders.find(header) != listOfLinuxHeaders.cend() || isStringFoundCaseSensitive(header, "sys/");
}

bool CPlusPlusFileFixer::isWindowsHeader(string const& header) {
    return listOfWindowsHeaders.find(header) != listOfWindowsHeaders.cend();
}

bool CPlusPlusFileFixer::isGtestHeader(string const& header) { return isStringFoundCaseSensitive(header, "gtest"); }

bool CPlusPlusFileFixer::isQtHeader(string const& header) {
    bool result(false);
    AlbaLocalPathHandler const headerFileHandler(header);
    if (header.length() >= 2) {
        if ('Q' == header[0] && ('t' == header[1] || isCapitalLetter(header[1])) &&
            headerFileHandler.getExtension().empty()) {
            result = true;
        }
    }
    return result;
}

void CPlusPlusFileFixer::processDirectory(path const& path) {
    set<string> const listOfFiles;
    set<string> const listOfDirectories;
    AlbaLocalPathHandler(path).findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const filePathHandler(filePath);
            if (!isPathIgnored(filePathHandler.getPath().string())) {
                if ("cpp" == filePathHandler.getExtension() || "hpp" == filePathHandler.getExtension()) {
                    processFile(filePathHandler.getPath());
                }
            }
        });
}

}  // namespace alba
