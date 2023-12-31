#include "AlbaLinuxPathHandler.hpp"

#include <Common/Linux/AlbaLinuxHelper.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLinuxTimeHelper.hpp>

#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>

using namespace alba::AlbaLinuxHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaLinuxPathHandler::AlbaLinuxPathHandler(string_view const path) : AlbaPathHandler(R"(/)") { setPath(path); }

AlbaDateTime AlbaLinuxPathHandler::getFileCreationTime() const {
    struct stat fileStatus {};
    AlbaDateTime fileCreationTime;
    if (0 == stat(getPath().c_str(), &fileStatus)) {
        timespec timeSpec{};
        clock_gettime(CLOCK_REALTIME, &timeSpec);
        fileCreationTime = convertSystemTimeToAlbaDateTime(timeSpec);
    } else if (errno != 0) {
        cerr << "Error in AlbaLinuxPathHandler::getFileCreationTime() path:[" << getPath() << "] 'stat' errno value:["
             << errno << "] error message:[" << getErrorMessage(errno) << "]\n";
    }
    return fileCreationTime;
}

double AlbaLinuxPathHandler::getFileSizeEstimate() const {
    struct stat fileStatus {};
    double fileSize(0);
    if (0 == stat(getPath().c_str(), &fileStatus)) {
        fileSize = static_cast<double>(fileStatus.st_size);
    } else if (errno != 0) {
        cerr << "Error in AlbaLinuxPathHandler::getFileSizeEstimate() path:[" << getPath() << "] 'stat' errno value:["
             << errno << "] error message:[" << getErrorMessage(errno) << "]\n";
    }
    return fileSize;
}

bool AlbaLinuxPathHandler::doesExist() const { return m_foundInLocalSystem; }
bool AlbaLinuxPathHandler::isRelativePath() const { return m_relativePath; }

void AlbaLinuxPathHandler::createDirectoriesForNonExisitingDirectories() const {
    string fullPath(getPath());
    size_t index = 0;
    auto length = static_cast<size_t>(fullPath.length());
    while (index < length) {
        auto indexWithSlashCharacter = static_cast<size_t>(fullPath.find_first_of(m_slashCharacterString, index));
        if (isNpos(static_cast<int>(indexWithSlashCharacter))) {
            break;
        }
        string partialDirectory(fullPath.substr(0, indexWithSlashCharacter + 1));
        AlbaLinuxPathHandler partialDirectoryPathHandler(partialDirectory);
        if (!partialDirectoryPathHandler.doesExist()) {
            mkdir(partialDirectoryPathHandler.getPath().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        index = indexWithSlashCharacter + 1;
    }
}

void AlbaLinuxPathHandler::deleteFilesInDirectory() {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (auto&& file : listOfFiles) {
        AlbaLinuxPathHandler(file).deleteFile();
    }
    reInput();
}

void AlbaLinuxPathHandler::deleteInnerFilesAndDirectories() {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (auto&& file : listOfFiles) {
        AlbaLinuxPathHandler(file).deleteFile();
    }
    set<string>::reverse_iterator reverseIterator;
    for (reverseIterator = listOfDirectories.rbegin(); reverseIterator != listOfDirectories.rend(); ++reverseIterator) {
        AlbaLinuxPathHandler(*reverseIterator).deleteDirectoryWithoutFilesAndDirectories();
    }
    reInput();
}

void AlbaLinuxPathHandler::deleteDirectoryWithFilesAndDirectories() {
    deleteInnerFilesAndDirectories();
    deleteDirectoryWithoutFilesAndDirectories();
    reInput();
}

bool AlbaLinuxPathHandler::deleteFile() {
    bool isSuccessful(false);
    if (isFile()) {
        int errorReturnValue = unlink(getPath().c_str());
        isSuccessful = errorReturnValue == 0;
        if (!isSuccessful) {
            cerr << "Error in AlbaLinuxPathHandler::deleteFile() path:[" << getPath() << "] 'unlink' error value:["
                 << errorReturnValue << "]\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaLinuxPathHandler::deleteDirectoryWithoutFilesAndDirectories() {
    bool isSuccessful(false);
    if (isDirectory()) {
        int errorReturnValue = rmdir(getPath().c_str());
        isSuccessful = errorReturnValue == 0;
        if (!isSuccessful) {
            cerr << "Error in AlbaLinuxPathHandler::deleteDirectoryWithoutFilesAndDirectories() path:[" << getPath()
                 << "] 'rmdir' error value:[" << errorReturnValue << "]\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaLinuxPathHandler::copyToNewFile(string_view const newFilePath) {
    int readFileDescriptor{};
    struct stat statBuffer {};
    off_t offset = 0;
    bool isSuccessful(false);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
    readFileDescriptor = open(getPath().c_str(), O_RDONLY);
    if (0 == stat(getPath().c_str(), &statBuffer)) {
        int writeFileDescriptor{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
        writeFileDescriptor = open(newFilePath.data(), O_WRONLY | O_CREAT, statBuffer.st_mode);
        if (isFile()) {
            int errorReturnValue = static_cast<int>(
                sendfile(writeFileDescriptor, readFileDescriptor, &offset, static_cast<size_t>(statBuffer.st_size)));
            isSuccessful = errorReturnValue != -1;
            if (!isSuccessful) {
                cerr << "Error in AlbaLinuxPathHandler::copyToNewFile() path:[" << getPath() << "] newFilePath:["
                     << newFilePath << "] 'sendfile' error value:[" << errorReturnValue << "]\n";
            } else {
                reInput();
            }
        }
        close(writeFileDescriptor);
    } else if (errno != 0) {
        cerr << "Error in AlbaLinuxPathHandler::copyToNewFile() path:[" << getPath() << "] 'stat' errno value:["
             << errno << "] error message:[" << getErrorMessage(errno) << "]\n";
    }
    close(readFileDescriptor);
    return isSuccessful;
}

bool AlbaLinuxPathHandler::renameFile(string_view const newFileName) {
    bool isSuccessful(false);
    if (isFile()) {
        string newPath(m_directory + string(newFileName));
        int errorReturnValue = rename(getPath().c_str(), newPath.c_str());
        isSuccessful = errorReturnValue == 0;
        if (!isSuccessful) {
            cerr << "Error in AlbaLinuxPathHandler::renameFile() path:[" << getPath() << "] newFileName:["
                 << newFileName << "] 'rename' error value:[" << errorReturnValue << "]\n";
        } else {
            input(newPath);
        }
    }
    return isSuccessful;
}

bool AlbaLinuxPathHandler::renameImmediateDirectory(string_view const newDirectoryName) {
    bool isSuccessful(false);
    if (isDirectory()) {
        AlbaLinuxPathHandler newPathHandler(getPath());
        newPathHandler.goUp();
        newPathHandler.input(newPathHandler.getDirectory() + m_slashCharacterString + string(newDirectoryName));
        int errorReturnValue = rename(getPath().c_str(), newPathHandler.getPath().c_str());
        isSuccessful = errorReturnValue == 0;
        if (!isSuccessful) {
            cerr << "Error in AlbaLinuxPathHandler::renameImmediateDirectory() path:[" << getPath()
                 << "] newDirectoryName:[" << newDirectoryName << "] 'rename' error value:[" << errorReturnValue
                 << "]\n";
        } else {
            input(newPathHandler.getPath());
        }
    }
    return isSuccessful;
}

AlbaLinuxPathHandler AlbaLinuxPathHandler::createPathHandlerForDetectedPath() {
    return AlbaLinuxPathHandler(getCurrentDetectedPath());
}

bool AlbaLinuxPathHandler::isPathADirectory(string_view const fileOrDirectoryName) const {
    bool result(false);
    if (canBeLocated(fileOrDirectoryName)) {
        struct stat statBuffer {};
        if (0 == stat(fileOrDirectoryName.data(), &statBuffer)) {
            result = S_ISDIR(statBuffer.st_mode);
        } else if (errno != 0) {
            cerr << "Error in AlbaLinuxPathHandler::isPathADirectory() path:[" << getPath() << "] 'stat' errno value:["
                 << errno << "] error message:[" << getErrorMessage(errno) << "]\n";
        }
    }
    return result;
}

bool AlbaLinuxPathHandler::isSlashNeededAtTheEnd(
    string_view const correctedPath, string_view const originalPath) const {
    bool result = false;
    if (!correctedPath.empty()) {
        bool isCorrectPathLastCharacterNotASlash(
            correctedPath[correctedPath.length() - 1] != m_slashCharacterString[0]);
        if (isCorrectPathLastCharacterNotASlash) {
            if (canBeLocated(correctedPath)) {
                if (isPathADirectory(correctedPath)) {
                    result = true;
                }
            } else {
                bool isOriginalPathLastCharacterASlash(
                    originalPath[originalPath.length() - 1] == m_slashCharacterString[0]);
                if (isOriginalPathLastCharacterASlash) {
                    result = true;
                }
            }
        }
    }
    return result;
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth(
    string_view const currentDirectory, string_view const wildCardSearch, ListOfPaths& listOfFiles,
    ListOfPaths& listOfDirectories, int const depth) const {
    if (depth == 0) {
        return;
    }
    int correctedDepth = (depth > 0) ? depth - 1 : depth;

    DIR* directoryStream(nullptr);

    directoryStream = opendir(currentDirectory.data());
    if (directoryStream != nullptr) {
        loopAllFilesAndDirectoriesInDirectoryStream(
            directoryStream, currentDirectory, wildCardSearch, listOfFiles, listOfDirectories, correctedDepth);
    } else if (errno != 0) {
        cerr << "Error in AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth() currentDirectory:["
             << currentDirectory << "] 'opendir' errno value:[" << errno << "] error message:["
             << getErrorMessage(errno) << "]\n";
    }
    if (directoryStream != nullptr) {
        closedir(directoryStream);
    }
}

void AlbaLinuxPathHandler::loopAllFilesAndDirectoriesInDirectoryStream(
    DIR* directoryStream, string_view const currentDirectory, string_view const wildCardSearch,
    set<string>& listOfFiles, set<string>& listOfDirectories, int const depth) const {
    struct dirent* directoryPointer = nullptr;
    do {
        // NOLINTNEXTLINE(concurrency-mt-unsafe)
        directoryPointer = readdir(directoryStream);
        if (directoryPointer != nullptr) {
            string immediateFileOrDirectoryName(static_cast<const char*>(directoryPointer->d_name));
            bool canProceedBasedOnWildcard = wildCardSearch.empty() || "*.*" == wildCardSearch ||
                                             isWildcardMatch(immediateFileOrDirectoryName, wildCardSearch);
            bool isTheNameNotComposedOfPeriods =
                "." != immediateFileOrDirectoryName && ".." != immediateFileOrDirectoryName;
            if (isTheNameNotComposedOfPeriods && canProceedBasedOnWildcard) {
                string fullFileOrDirectoryName(string(currentDirectory) + immediateFileOrDirectoryName);
                if (isPathADirectory(fullFileOrDirectoryName)) {
                    string fullFileOrDirectoryNameWithSlash(fullFileOrDirectoryName + "/");
                    listOfDirectories.emplace(fullFileOrDirectoryNameWithSlash);
                    findFilesAndDirectoriesWithDepth(
                        fullFileOrDirectoryNameWithSlash, wildCardSearch, listOfFiles, listOfDirectories, depth);
                } else {
                    listOfFiles.emplace(fullFileOrDirectoryName);
                }
            }
        } else if (errno != 0) {
            cerr << "Error in AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth() currentDirectory:["
                 << currentDirectory << "] 'readdir' errno value:[" << errno << "] error message:["
                 << getErrorMessage(errno) << "]\n";
        }
    } while (directoryPointer != nullptr);
}

void AlbaLinuxPathHandler::save(string_view const path) { setPath(path); }

void AlbaLinuxPathHandler::setPath(string_view const path) {
    string correctPath(getCorrectPathWithoutDoublePeriod(
        // getStringWithoutCharAtTheEnd(
        getCorrectPathWithReplacedSlashCharacters(path, m_slashCharacterString)
        //   , m_slashCharacterString[0])
        ,
        m_slashCharacterString));
    if (isSlashNeededAtTheEnd(correctPath, path)) {
        correctPath = getCorrectPathWithoutDoublePeriod(correctPath + m_slashCharacterString, m_slashCharacterString);
    }
    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setFileType();
    m_foundInLocalSystem = canBeLocated(correctPath);
}

string AlbaLinuxPathHandler::getCurrentDetectedPath() {
    constexpr size_t MAX_ARGUMENT_LENGTH = 50;
    constexpr size_t MAX_PATH = 1000;
    array<char, MAX_ARGUMENT_LENGTH> argument{};
    array<char, MAX_PATH> detectedLocalPath{};

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg,hicpp-vararg,cert-err33-c)
    snprintf(argument.data(), MAX_ARGUMENT_LENGTH, "/proc/%d/exe", getpid());
    auto length = static_cast<size_t>(readlink(argument.data(), detectedLocalPath.data(), MAX_PATH));
    length = (length == 0) ? 1 : length;
    detectedLocalPath[length] = '\0';
    return {detectedLocalPath.cbegin(), detectedLocalPath.cend()};
}

bool AlbaLinuxPathHandler::canBeLocated(string_view const fullPath) {
    struct stat statBuffer {};
    return stat(fullPath.data(), &statBuffer) == 0;
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesOneDepth(
    string_view const wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, 1);
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesMultipleDepth(
    string_view const wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories, int const depth) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, depth);
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesUnlimitedDepth(
    string_view const wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, -1);
}

void AlbaLinuxPathHandler::clear() {
    AlbaPathHandler::clear();
    m_foundInLocalSystem = false;
    m_relativePath = false;
}

}  // namespace alba
