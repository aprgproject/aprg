#include "AprgFileExtractor.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaLogPrints.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#ifndef PATH_OF_7Z_EXECUTABLE
static_assert(false, "PATH_OF_7Z_EXECUTABLE is not set in cmake");
#endif
#ifndef NULL_DEVICE
static_assert(false, "NULL_DEVICE is not set in cmake");
#endif
#ifndef PATH_OF_7Z_TEMP_FILE
static_assert(false, "PATH_OF_7Z_TEMP_FILE is not set in cmake");
#endif

using namespace std;

namespace alba {

namespace ProgressCounters {
extern int numberOfFilesToBeAnalyzedForExtraction;
extern int numberOfFilesAnalyzedForExtraction;
}  // namespace ProgressCounters

AprgFileExtractor::AprgFileExtractor(string const& condition)
    : m_grepEvaluator(condition),
      m_pathOf7zExecutable(AlbaLocalPathHandler(PATH_OF_7Z_EXECUTABLE).getPath()),
      m_pathOf7zTempFile(AlbaLocalPathHandler(PATH_OF_7Z_TEMP_FILE).getPath()),
      m_nullDevice(AlbaLocalPathHandler(NULL_DEVICE).getPath()) {}

AprgFileExtractor::AprgFileExtractor()
    : m_grepEvaluator(""),
      m_pathOf7zExecutable(AlbaLocalPathHandler(PATH_OF_7Z_EXECUTABLE).getPath()),
      m_pathOf7zTempFile(AlbaLocalPathHandler(PATH_OF_7Z_TEMP_FILE).getPath()),
      m_nullDevice(AlbaLocalPathHandler(NULL_DEVICE).getPath()) {}

AprgFileExtractor::AprgFileExtractor(
    string const& condition, string const& pathOf7zExecutable, string const& pathOf7zTempFile)
    : m_grepEvaluator(condition), m_pathOf7zExecutable(pathOf7zExecutable), m_pathOf7zTempFile(pathOf7zTempFile) {}

void AprgFileExtractor::copyRelativeFilePathsFromCompressedFile(
    string const& filePathOfCompressedFile, SetOfFilePaths& files) const {
    AlbaLocalPathHandler const filePathHandler(filePathOfCompressedFile);
    string const command = string(R"(")") + m_pathOf7zExecutable + R"(" l -slt ")" + filePathHandler.getPath() +
                           R"(" > ")" + m_pathOf7zTempFile + R"(")";
    runInConsole(command);

    ifstream tempFile(m_pathOf7zTempFile);
    string path;
    AlbaFileReader fileReader(tempFile);
    while (fileReader.isNotFinished()) {
        string const lineInFile(fileReader.getLine());
        if (stringHelper::isStringFoundCaseSensitive(lineInFile, "Path = ")) {
            path = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
                stringHelper::getStringAfterThisString(lineInFile, "Path = "));
        } else if (stringHelper::isStringFoundCaseSensitive(lineInFile, "Attributes = ")) {
            if (!stringHelper::isStringFoundCaseSensitive(
                    stringHelper::getStringAfterThisString(lineInFile, "Attributes = "), "D")) {
                files.emplace(path);
            }
        }
    }
}

string AprgFileExtractor::extractOnceForAllFiles(string const& filePathOfCompressedFile) const {
    AlbaLocalPathHandler const compressedFilePathHandler(filePathOfCompressedFile);
    AlbaLocalPathHandler const outputPathHandler(
        compressedFilePathHandler.getDirectory() + R"(\)" + compressedFilePathHandler.getFilenameOnly() + R"(\)");
    string const command = string(R"(")") + m_pathOf7zExecutable + R"(" e -y -o")" + outputPathHandler.getDirectory() +
                           R"(" ")" + compressedFilePathHandler.getPath() + R"(" > )" + m_nullDevice;
    runInConsole(command);
    cout << "extractAll: " << outputPathHandler.getImmediateDirectoryName() << R"(\)"
         << "\n";
    return outputPathHandler.getPath();
}

string AprgFileExtractor::extractOneFile(
    string const& filePathOfCompressedFile, string const& relativePathOfFile) const {
    AlbaLocalPathHandler const compressedFilePathHandler(filePathOfCompressedFile);
    AlbaLocalPathHandler const outputPathHandler(
        compressedFilePathHandler.getDirectory() + R"(\)" + compressedFilePathHandler.getFilenameOnly() + R"(\)" +
        relativePathOfFile);
    string const command = string(R"(")") + m_pathOf7zExecutable + R"(" e -y -o")" + outputPathHandler.getDirectory() +
                           R"(" ")" + compressedFilePathHandler.getPath() + R"(" ")" + relativePathOfFile +
                           R"(" > )" + m_nullDevice;
    runInConsole(command);
    cout << "extractOneFile: " << outputPathHandler.getFile() << "\n";
    return outputPathHandler.getPath();
}

void AprgFileExtractor::extractAllRelevantFiles(string const& pathOfFileOrDirectory) {
    AlbaLocalPathHandler const fileOrDirectoryPathHandler(pathOfFileOrDirectory);
    if (!fileOrDirectoryPathHandler.doesExist()) {
        cout << "extractAllRelevantFiles: File or directory not found in local system.\n";
    }
    if (fileOrDirectoryPathHandler.isDirectory()) {
        extractAllRelevantFilesInThisDirectory(fileOrDirectoryPathHandler.getPath());
    } else {
        extractAllRelevantFilesInThisCompressedFile(fileOrDirectoryPathHandler.getPath());
    }
}

bool AprgFileExtractor::isRecognizedCompressedFile(string const& extension) {
    return stringHelper::isEqualNotCaseSensitive("zip", extension) ||
           stringHelper::isEqualNotCaseSensitive("tar", extension) ||
           stringHelper::isEqualNotCaseSensitive("7z", extension) ||
           stringHelper::isEqualNotCaseSensitive("xz", extension) ||
           stringHelper::isEqualNotCaseSensitive("gz", extension);
}

void AprgFileExtractor::extractAllRelevantFilesInThisDirectory(string const& directoryPath) {
    AlbaLocalPathHandler const directoryPathHandler(directoryPath);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    ProgressCounters::numberOfFilesToBeAnalyzedForExtraction += listOfFiles.size();
    for (string const& filePath : listOfFiles) {
        AlbaLocalPathHandler const extractedPathHandler(filePath);
        if (isRecognizedCompressedFile(extractedPathHandler.getExtension())) {
            extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getPath());
        }
        ProgressCounters::numberOfFilesAnalyzedForExtraction++;
    }
}

void AprgFileExtractor::extractAllRelevantFilesInThisCompressedFile(string const& filePathOfCompressedFile) {
    AlbaLocalPathHandler const compressedFilePathHandler(filePathOfCompressedFile);
    if (isTheExtensionXzOrGzOrTar(compressedFilePathHandler.getExtension())) {
        if (m_grepEvaluator.evaluate(compressedFilePathHandler.getFile())) {
            extractAllFilesRecursively(filePathOfCompressedFile);
        }
    } else {
        extractAllRelevantFilesRecursively(filePathOfCompressedFile);
    }
}

void AprgFileExtractor::extractAllFilesRecursively(string const& filePathOfCompressedFile) {
    AlbaLocalPathHandler const extractedPathHandler(extractOnceForAllFiles(filePathOfCompressedFile));
    extractAllRelevantFilesInThisDirectory(extractedPathHandler.getPath());
}

void AprgFileExtractor::extractAllRelevantFilesRecursively(string const& filePathOfCompressedFile) {
    set<string> filePaths;
    copyRelativeFilePathsFromCompressedFile(filePathOfCompressedFile, filePaths);
    ProgressCounters::numberOfFilesToBeAnalyzedForExtraction += filePaths.size();
    for (string const& filePath : filePaths) {
        AlbaLocalPathHandler const filePathHandler(filePath);
        if (m_grepEvaluator.evaluate(filePathHandler.getFile())) {
            AlbaLocalPathHandler extractedPathHandler(extractOneFile(filePathOfCompressedFile, filePath));
            if (isRecognizedCompressedFile(extractedPathHandler.getExtension())) {
                extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getPath());
                extractedPathHandler.deleteFile();
            }
        }
        ProgressCounters::numberOfFilesAnalyzedForExtraction++;
    }
}

void AprgFileExtractor::runInConsole(string const& command) {
#if defined(OS_LINUX)
    ALBA_INF_PRINT1(cout, command);
    system(command.c_str());
#elif defined(OS_WINDOWS)
    string const revisedCommand = string(R"(cmd /S /C ")") + command + string(R"(")");
    ALBA_INF_PRINT1(cout, revisedCommand);
    system(revisedCommand.c_str());
#endif
}

bool AprgFileExtractor::isTheExtensionXzOrGzOrTar(string const& extension) {
    return stringHelper::isEqualNotCaseSensitive("xz", extension) ||
           stringHelper::isEqualNotCaseSensitive("gz", extension) ||
           stringHelper::isEqualNotCaseSensitive("tar", extension);
}

}  // namespace alba
