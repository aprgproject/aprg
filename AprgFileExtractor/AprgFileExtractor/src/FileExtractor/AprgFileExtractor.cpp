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
#ifndef PATH_OF_7Z_TEMP_FILE
static_assert(false, "PATH_OF_7Z_TEMP_FILE is not set in cmake");
#endif

using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {
#if defined(OS_LINUX)
constexpr auto NULL_DEVICE = "/dev/null";
#elif defined(OS_WINDOWS)
constexpr auto NULL_DEVICE = "nul";
#endif
}  // namespace

namespace ProgressCounters {
extern int numberOfFilesToBeAnalyzedForExtraction;
extern int numberOfFilesAnalyzedForExtraction;
}  // namespace ProgressCounters

AprgFileExtractor::AprgFileExtractor(string const& condition)
    : m_grepEvaluator(condition),
      m_pathOf7zExecutable(AlbaLocalPathHandler(PATH_OF_7Z_EXECUTABLE).getPath()),
      m_pathOf7zTempFile(AlbaLocalPathHandler(PATH_OF_7Z_TEMP_FILE).getPath()),
      m_nullDevice(NULL_DEVICE) {}

AprgFileExtractor::AprgFileExtractor()
    : m_grepEvaluator(""),
      m_pathOf7zExecutable(AlbaLocalPathHandler(PATH_OF_7Z_EXECUTABLE).getPath()),
      m_pathOf7zTempFile(AlbaLocalPathHandler(PATH_OF_7Z_TEMP_FILE).getPath()),
      m_nullDevice(NULL_DEVICE) {}

AprgFileExtractor::AprgFileExtractor(
    string const& condition, path const& pathOf7zExecutable, path const& pathOf7zTempFile)
    : m_grepEvaluator(condition), m_pathOf7zExecutable(pathOf7zExecutable), m_pathOf7zTempFile(pathOf7zTempFile) {}

AprgFileExtractor::AprgFileExtractor(string&& condition, path&& pathOf7zExecutable, path&& pathOf7zTempFile)
    : m_grepEvaluator(condition), m_pathOf7zExecutable(pathOf7zExecutable), m_pathOf7zTempFile(pathOf7zTempFile) {}

void AprgFileExtractor::copyRelativeFilePathsFromCompressedFile(
    path const& filePathOfCompressedFile, SetOfPaths& files) const {
    AlbaLocalPathHandler const filePathHandler(filePathOfCompressedFile);
    string const command = string(R"(")") + m_pathOf7zExecutable.string() + R"(" l -slt ")" +
                           filePathHandler.getPath().string() + R"(" > ")" + m_pathOf7zTempFile.string() + R"(")";
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

path AprgFileExtractor::extractOnceForAllFiles(path const& filePathOfCompressedFile) const {
    AlbaLocalPathHandler const compressedFilePathHandler(filePathOfCompressedFile);
    AlbaLocalPathHandler const outputPathHandler(
        compressedFilePathHandler.getDirectory() / compressedFilePathHandler.getFilenameOnly() / "");
    string const command = string(R"(")") + m_pathOf7zExecutable.string() + R"(" e -y -o")" +
                           outputPathHandler.getDirectory().string() + R"(" ")" +
                           compressedFilePathHandler.getPath().string() + R"(" > )" + m_nullDevice;
    cout << "extractAll: " << outputPathHandler.getDirectoryName() << R"(\)"
         << "\n";
    runInConsole(command);
    return outputPathHandler.getPath();
}

path AprgFileExtractor::extractOneFile(path const& filePathOfCompressedFile, path const& relativePathOfFile) const {
    AlbaLocalPathHandler const compressedFilePathHandler(filePathOfCompressedFile);
    AlbaLocalPathHandler const outputPathHandler(
        compressedFilePathHandler.getDirectory() / compressedFilePathHandler.getFilenameOnly() / relativePathOfFile);
    string const command = string(R"(")") + m_pathOf7zExecutable.string() + R"(" e -y -o")" +
                           outputPathHandler.getDirectory().string() + R"(" ")" +
                           compressedFilePathHandler.getPath().string() + R"(" ")" + relativePathOfFile.string() +
                           R"(" > )" + m_nullDevice;
    cout << "extractOneFile: " << outputPathHandler.getFile() << "\n";
    runInConsole(command);
    return outputPathHandler.getPath();
}

void AprgFileExtractor::extractAllRelevantFiles(path const& pathOfFileOrDirectory) {
    AlbaLocalPathHandler const fileOrDirectoryPathHandler(pathOfFileOrDirectory);
    if (!fileOrDirectoryPathHandler.doesExist()) {
        cout << "extractAllRelevantFiles: File or directory not found in local system.\n";
    }
    if (fileOrDirectoryPathHandler.isExistingDirectory()) {
        extractAllRelevantFilesInThisDirectory(fileOrDirectoryPathHandler.getPath());
    } else {
        extractAllRelevantFilesInThisCompressedFile(fileOrDirectoryPathHandler.getPath());
    }
}

bool AprgFileExtractor::isRecognizedCompressedFile(string const& extensionString) {
    return stringHelper::isEqualNotCaseSensitive("zip", extensionString) ||
           stringHelper::isEqualNotCaseSensitive("tar", extensionString) ||
           stringHelper::isEqualNotCaseSensitive("7z", extensionString) ||
           stringHelper::isEqualNotCaseSensitive("xz", extensionString) ||
           stringHelper::isEqualNotCaseSensitive("gz", extensionString);
}

void AprgFileExtractor::extractAllRelevantFilesInThisDirectory(path const& directoryPath) {
    AlbaLocalPathHandler const directoryPathHandler(directoryPath);
    set<AlbaLocalPathHandler::LocalPath> listOfFilePaths;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) { listOfFilePaths.emplace(filePath); });
    ProgressCounters::numberOfFilesToBeAnalyzedForExtraction += static_cast<int>(listOfFilePaths.size());
    for (auto const& filePath : listOfFilePaths) {
        AlbaLocalPathHandler const extractedPathHandler(filePath);
        if (isRecognizedCompressedFile(extractedPathHandler.getExtension().string())) {
            extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getPath());
        }
        ProgressCounters::numberOfFilesAnalyzedForExtraction++;
    }
}

void AprgFileExtractor::extractAllRelevantFilesInThisCompressedFile(path const& filePathOfCompressedFile) {
    AlbaLocalPathHandler const compressedFilePathHandler(filePathOfCompressedFile);
    if (isTheExtensionXzOrGzOrTar(compressedFilePathHandler.getExtension().string())) {
        if (m_grepEvaluator.evaluate(compressedFilePathHandler.getFile().string())) {
            extractAllFilesRecursively(filePathOfCompressedFile);
        }
    } else {
        extractAllRelevantFilesRecursively(filePathOfCompressedFile);
    }
}

void AprgFileExtractor::extractAllFilesRecursively(path const& filePathOfCompressedFile) {
    AlbaLocalPathHandler const extractedPathHandler(extractOnceForAllFiles(filePathOfCompressedFile));
    extractAllRelevantFilesInThisDirectory(extractedPathHandler.getPath());
}

void AprgFileExtractor::extractAllRelevantFilesRecursively(path const& filePathOfCompressedFile) {
    SetOfPaths filePaths;
    copyRelativeFilePathsFromCompressedFile(filePathOfCompressedFile, filePaths);
    ProgressCounters::numberOfFilesToBeAnalyzedForExtraction += static_cast<int>(filePaths.size());
    for (auto const& filePath : filePaths) {
        AlbaLocalPathHandler const filePathHandler(filePath);
        if (m_grepEvaluator.evaluate(filePathHandler.getFile().string())) {
            AlbaLocalPathHandler const extractedPathHandler(extractOneFile(filePathOfCompressedFile, filePath));
            if (isRecognizedCompressedFile(extractedPathHandler.getExtension().string())) {
                extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getPath());
                if (!extractedPathHandler.deleteFileAndIsSuccessful()) {
                    cout << "extractAllRelevantFilesRecursively: Deletion is not successful: ["
                         << extractedPathHandler.getPath() << "].\n";
                }
            }
        }
        ProgressCounters::numberOfFilesAnalyzedForExtraction++;
    }
}

void AprgFileExtractor::runInConsole(string const& command) {
#if defined(OS_LINUX)
    // ALBA_INF_PRINT1(cout, command);
    system(command.c_str());
#elif defined(OS_WINDOWS)
    string const revisedCommand = string(R"(cmd /S /C ")") + command + string(R"(")");
    // ALBA_INF_PRINT1(cout, revisedCommand);
    system(revisedCommand.c_str());
#endif
}

bool AprgFileExtractor::isTheExtensionXzOrGzOrTar(string const& extensionString) {
    return stringHelper::isEqualNotCaseSensitive("xz", extensionString) ||
           stringHelper::isEqualNotCaseSensitive("gz", extensionString) ||
           stringHelper::isEqualNotCaseSensitive("tar", extensionString);
}

}  // namespace alba
