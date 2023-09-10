#include "AlbaWindowsPathHandler.hpp"

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaWindowsTimeHelper.hpp>
#include <Common/Windows/AlbaWindowsHelper.hpp>

#include <winbase.h>
#include <windows.h>

#include <functional>
#include <iostream>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaWindowsPathHandler::AlbaWindowsPathHandler(string_view const path) : AlbaPathHandler(R"(\)") { setPath(path); }
AlbaWindowsPathHandler AlbaWindowsPathHandler::createPathHandlerForDetectedPath() {
    return AlbaWindowsPathHandler{getCurrentDetectedPath()};
}

void AlbaWindowsPathHandler::createDirectoriesForNonExisitingDirectories() const {
    string const fullPath(getFullPath());
    int index = 0;
    int const length = fullPath.length();
    while (index < length) {
        int const indexWithSlashCharacter = fullPath.find_first_of(m_slashCharacterString, index);
        if (isNpos(indexWithSlashCharacter)) {
            break;
        }
        string const partialDirectory(fullPath.substr(0, indexWithSlashCharacter + 1));
        AlbaWindowsPathHandler const partialDirectoryPathHandler(partialDirectory);
        if (!partialDirectoryPathHandler.isFoundInLocalSystem()) {
            if (CreateDirectoryW(
                    convertToAnotherBasicStringVariant<string, wstring>(partialDirectoryPathHandler.getFullPath())
                        .c_str(),
                    nullptr) == 0) {
                cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
                cout << "Path: [" << partialDirectoryPathHandler.getFullPath() << "]\n";
                cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
            }
        }
        index = indexWithSlashCharacter + 1;
    }
}

string AlbaWindowsPathHandler::getDriveOrRoot() const { return m_driveOrRoot; }
bool AlbaWindowsPathHandler::isFoundInLocalSystem() const { return m_foundInLocalSystem; }
bool AlbaWindowsPathHandler::isRelativePath() const { return m_relativePath; }

void AlbaWindowsPathHandler::deleteFilesInDirectory() {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (auto&& file : listOfFiles) {
        AlbaWindowsPathHandler(file).deleteFile();
    }
    reInput();
}

void AlbaWindowsPathHandler::deleteInnerFilesAndDirectories() {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (auto&& file : listOfFiles) {
        AlbaWindowsPathHandler(file).deleteFile();
    }
    set<string>::reverse_iterator reverseIterator;
    for (reverseIterator = listOfDirectories.rbegin(); reverseIterator != listOfDirectories.rend(); ++reverseIterator) {
        AlbaWindowsPathHandler(*reverseIterator).deleteDirectoryWithoutFilesAndDirectories();
    }
    reInput();
}

void AlbaWindowsPathHandler::deleteDirectoryWithFilesAndDirectories() {
    deleteInnerFilesAndDirectories();
    deleteDirectoryWithoutFilesAndDirectories();
    reInput();
}

AlbaDateTime AlbaWindowsPathHandler::getFileCreationTime() {
    AlbaDateTime fileCreationTime;
    WIN32_FILE_ATTRIBUTE_DATA attributeData;
    if (GetFileAttributesExW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(), GetFileExInfoStandard,
            &attributeData) != 0) {
        SYSTEMTIME fileCreationTimeInSystemTime;
        FileTimeToSystemTime(&(attributeData.ftCreationTime), &fileCreationTimeInSystemTime);
        fileCreationTime = convertSystemTimeToAlbaDateTime(fileCreationTimeInSystemTime);
    } else {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << "Path:" << getFullPath() << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }
    return fileCreationTime;
}

double AlbaWindowsPathHandler::getFileSizeEstimate() {
    double fileSizeEstimate(0);
    WIN32_FILE_ATTRIBUTE_DATA attributeData;
    if (GetFileAttributesExW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(), GetFileExInfoStandard,
            &attributeData) != 0) {
        fileSizeEstimate =
            static_cast<double>(attributeData.nFileSizeHigh) * 0x100'000'000 + attributeData.nFileSizeLow;
    } else {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << "Path:" << getFullPath() << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }
    return fileSizeEstimate;
}

bool AlbaWindowsPathHandler::deleteFile() {
    bool isSuccessful(false);
    if (isFile()) {
        isSuccessful =
            static_cast<bool>(DeleteFileW(convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str()));
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::deleteDirectoryWithoutFilesAndDirectories() {
    bool isSuccessful(false);
    if (isDirectory()) {
        isSuccessful = static_cast<bool>(
            RemoveDirectoryW(convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str()));
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::copyToNewFile(string_view const newFilePath) {
    bool isSuccessful(false);
    if (isFile()) {
        isSuccessful = static_cast<bool>(CopyFileW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(),
            convertToAnotherBasicStringVariant<string_view, wstring>(newFilePath).c_str(), 0));
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << "newFilePath: [" << newFilePath << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::renameFile(string_view const newFileName) {
    bool isSuccessful(false);
    if (isFile()) {
        string const newPath(m_directory + string(newFileName));
        isSuccessful = static_cast<bool>(MoveFileW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(),
            convertToAnotherBasicStringVariant<string, wstring>(newPath).c_str()));
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << "newFileName: [" << newFileName << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            input(newPath);
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::renameImmediateDirectory(string_view const newDirectoryName) {
    bool isSuccessful(false);
    if (isDirectory()) {
        AlbaWindowsPathHandler newPathHandler(getFullPath());
        newPathHandler.goUp();
        newPathHandler.input(newPathHandler.getDirectory() + m_slashCharacterString + string(newDirectoryName));
        isSuccessful = static_cast<bool>(MoveFileW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(),
            convertToAnotherBasicStringVariant<string, wstring>(newPathHandler.getFullPath()).c_str()));
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << "newDirectoryName: [" << newDirectoryName << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            input(newPathHandler.getFullPath());
        }
    }
    return isSuccessful;
}

string AlbaWindowsPathHandler::getCurrentDetectedPath() {
    string result;
    constexpr size_t MAXIMUM_CHARACTERS_PATH = 1000;
    WCHAR currentPathFromWindowsWideCharArray[MAXIMUM_CHARACTERS_PATH];
    if (GetModuleFileNameW(nullptr, currentPathFromWindowsWideCharArray, MAX_PATH) != 0U) {
        result = convertToAnotherBasicStringVariant<wstring, string>(wstring(currentPathFromWindowsWideCharArray));
    } else {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }
    return result;
}

bool AlbaWindowsPathHandler::canBeLocated(string_view const fullPath) {
    DWORD const attributes =
        GetFileAttributesW(convertToAnotherBasicStringVariant<string_view, wstring>(fullPath).c_str());
    return INVALID_FILE_ATTRIBUTES != attributes;
}

bool AlbaWindowsPathHandler::isSlashNeededAtTheEnd(
    string_view const correctedPath, string_view const originalPath) const {
    bool result(false);
    if (!correctedPath.empty()) {
        bool const isCorrectPathLastCharacterNotASlash(
            correctedPath[correctedPath.length() - 1] != m_slashCharacterString[0]);
        if (isCorrectPathLastCharacterNotASlash) {
            DWORD const attributes =
                GetFileAttributesW(convertToAnotherBasicStringVariant<string_view, wstring>(correctedPath).c_str());
            bool const isFoundInWindows(INVALID_FILE_ATTRIBUTES != attributes);
            if (isFoundInWindows) {
                bool const isDirectoryInWindows((attributes & FILE_ATTRIBUTE_DIRECTORY) != 0U);
                if (isDirectoryInWindows) {
                    result = true;
                }
            } else {
                bool const isOriginalPathLastCharacterASlash(
                    originalPath[originalPath.length() - 1] == m_slashCharacterString[0]);
                if (isOriginalPathLastCharacterASlash) {
                    result = true;
                }
            }
        }
    }
    return result;
}

void AlbaWindowsPathHandler::save(string_view const path) { setPath(path); }

void AlbaWindowsPathHandler::setPath(string_view const path) {
    string correctPath(getCorrectPathWithoutDoublePeriod(
        getCorrectPathWithReplacedSlashCharacters(path, m_slashCharacterString), m_slashCharacterString));
    if (isSlashNeededAtTheEnd(correctPath, path)) {
        correctPath = getCorrectPathWithoutDoublePeriod(correctPath + m_slashCharacterString, m_slashCharacterString);
    }

    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setDriveOrRoot();
    setFileType();
    m_foundInLocalSystem = canBeLocated(correctPath);
}

void AlbaWindowsPathHandler::setDriveOrRoot() {
    int const index = m_directory.find_first_of(m_slashCharacterString + ":");
    if (isNotNpos(index) && m_directory[index] == ':') {
        m_driveOrRoot = getStringWithCapitalLetters(m_directory.substr(0, index));
    }
    m_relativePath = m_driveOrRoot.empty();
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesOneDepth(
    string_view const wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, 1);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesMultipleDepth(
    string_view const wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories, int const depth) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, depth);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesUnlimitedDepth(
    string_view const wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, -1);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesWithDepth(
    string_view const currentDirectory, string_view const wildCardSearch, set<string>& listOfFiles,
    set<string>& listOfDirectories, int const depth) const {
    HANDLE hFind{};
    WIN32_FIND_DATAW data;

    if (depth == 0) {
        return;
    }
    int const correctedDepth = (depth > 0) ? depth - 1 : depth;

    string const currentDirectoryString(currentDirectory);
    string const searchString = currentDirectoryString + string(wildCardSearch);
    hFind = FindFirstFileW(convertToAnotherBasicStringVariant<string, wstring>(searchString).c_str(), &data);
    bool bContinue(hFind != INVALID_HANDLE_VALUE);
    while (bContinue) {
        string const fileOrDirectoryName(convertToAnotherBasicStringVariant<wstring, string>(wstring(data.cFileName)));
        if (!isPeriodOrDoublePeriod(fileOrDirectoryName)) {
            if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0U) {
                string const newDirectory(currentDirectoryString + fileOrDirectoryName + '\\');
                listOfDirectories.emplace(newDirectory);
                findFilesAndDirectoriesWithDepth(
                    newDirectory, wildCardSearch, listOfFiles, listOfDirectories, correctedDepth);
            } else {
                listOfFiles.emplace(currentDirectoryString + fileOrDirectoryName);
            }
        }
        bContinue = (FindNextFileW(hFind, &data) != 0);
    }
}

void AlbaWindowsPathHandler::clear() {
    AlbaPathHandler::clear();
    m_driveOrRoot.clear();
    m_foundInLocalSystem = false;
    m_relativePath = false;
}

}  // namespace alba
