#include "FileDirectoryDatabase.hpp"

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace codeReview;
using namespace std;

void FileDirectoryDatabase::printFilesAndDirectories(ostream& outputStream) const {
    for (auto& directory : m_directories) {
        outputStream << "FileDirectoryDatabase | Directory: [" << directory << "]\n";
    }
    for (auto& file : m_files) {
        outputStream << "FileDirectoryDatabase | File: [" << file << "]\n";
    }
}

bool FileDirectoryDatabase::isFileIncluded(string const& baseDirectory, string const& fileName) const {
    string whereItShouldBePath(AlbaLocalPathHandler(baseDirectory + fileName).getPath());
    for (auto fullPathOfFileFromDatabase : m_files) {
        if (whereItShouldBePath == fullPathOfFileFromDatabase) {
            return true;
        }
        if (isFileInFullPath(fullPathOfFileFromDatabase, fileName)) {
            return true;
        }
    }
    return false;
}

bool FileDirectoryDatabase::isFileInFullPath(string const& fullPathFromDatabase, string const& fileName) {
    string correctFileName(AlbaLocalPathHandler(string("\\") + fileName).getPath());
    int correctFileNameLength = correctFileName.length();
    int fullPathFromDatabaseLength = fullPathFromDatabase.length();
    if (correctFileNameLength < fullPathFromDatabaseLength) {
        string lastCharacters = fullPathFromDatabase.substr(fullPathFromDatabaseLength - correctFileNameLength);
        if (lastCharacters == correctFileName) {
            return true;
        }
    }
    return false;
}

string FileDirectoryDatabase::getPathOfFile(string const& baseDirectory, string const& fileName) const {
    int count = 0;
    unsigned int levenshteinDistance = 0;
    int score = 0;
    string fullPathOfFirstFileFound;
    string whereItShouldBePath(AlbaLocalPathHandler(baseDirectory + fileName).getPath());
    for (string fullPathOfFileFromDatabase : m_files) {
        if (whereItShouldBePath == fullPathOfFileFromDatabase) {
            return whereItShouldBePath;
        }
        if (isFileInFullPath(fullPathOfFileFromDatabase, fileName)) {
            unsigned int currentLevenshteinDistance =
                getLevenshteinDistance(whereItShouldBePath, fullPathOfFileFromDatabase);
            int lengthDifference =
                abs(static_cast<int>(whereItShouldBePath.length() - fullPathOfFileFromDatabase.length()));
            int currentScore = currentLevenshteinDistance - lengthDifference;
            if (fullPathOfFirstFileFound.empty() || score > currentScore ||
                (score == currentScore && levenshteinDistance > currentLevenshteinDistance)) {
                fullPathOfFirstFileFound = fullPathOfFileFromDatabase;
                levenshteinDistance = currentLevenshteinDistance;
                score = currentLevenshteinDistance - lengthDifference;
            }
            count++;
        }
    }
    if (count > 1) {
        cout << "FileDirectoryDatabase::getPathOfFile| Warning: multiple files found for file: " << fileName
             << "\n";
        cout << "WhereItShouldBe:" << whereItShouldBePath << "\n";
        cout << "WhereItIs: " << fullPathOfFirstFileFound << "\n";
    }
    return fullPathOfFirstFileFound;
}

SetOfFiles& FileDirectoryDatabase::getSetOfFilesReference() { return m_files; }

SetOfDirectories& FileDirectoryDatabase::getSetOfDirectoriesReference() { return m_directories; }

void FileDirectoryDatabase::allowNonExistentDirectories() { m_isNonExistentDirectoriesAllowed = true; }

void FileDirectoryDatabase::addFileOrDirectory(string const& fileOrDirectory) {
    AlbaLocalPathHandler pathHandler(fileOrDirectory);
    if (m_isNonExistentDirectoriesAllowed || pathHandler.doesExist()) {
        if (pathHandler.isFile()) {
            m_files.emplace(pathHandler.getPath());
        } else if (pathHandler.isDirectory()) {
            m_directories.emplace(pathHandler.getPath());
            pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", m_files, m_directories);
        }
    } else {
        cout << "FileDirectoryDatabase::addFileOrDirectory| InvalidFileAndDirectory: [" << fileOrDirectory << "]\n";
    }
}
