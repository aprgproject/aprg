#include "TestUtilities.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilitiesTests/MtDirectoryConstants.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba::CodeUtilities {

void clearFile(path const& file) { ofstream const expectedFileStream(AlbaLocalPathHandler(file).getPath()); }

void copyFile(string const& source, string const& destination) {
    AlbaLocalPathHandler const sourcePathHandler(source);
    AlbaLocalPathHandler const destinationPathHandler(destination);
    sourcePathHandler.copyFileToAndIsSuccessful(destinationPathHandler.getPath());
}

void verifyFile(string const& expectedFile, string const& testFile) {
    AlbaLocalPathHandler const expectedFilePathHandler(expectedFile);
    AlbaLocalPathHandler const testFilePathHandler(testFile);
    ifstream expectedFileStream(expectedFilePathHandler.getPath());
    ifstream testFileStream(testFilePathHandler.getPath());
    AlbaFileReader expectedFileReader(expectedFileStream);
    AlbaFileReader testFileReader(testFileStream);
    bool isDifferenceFound(false);
    strings lines;
    string lineInExpectedFile;
    string lineInTestFile;
    while (expectedFileReader.isNotFinished() && testFileReader.isNotFinished()) {
        lineInExpectedFile = expectedFileReader.getLine();
        lineInTestFile = testFileReader.getLine();
        EXPECT_EQ(lineInExpectedFile, lineInTestFile);
        if (lineInExpectedFile != lineInTestFile) {
            constexpr int LINES_TO_DISPLAY = 6;
            int const numberOfLines = static_cast<int>(lines.size());
            int lineIndex = numberOfLines < LINES_TO_DISPLAY ? 0 : numberOfLines - LINES_TO_DISPLAY;
            cout << "Difference occured at:\n";
            for (; lineIndex < numberOfLines; ++lineIndex) {
                cout << lines[lineIndex] << "\n";
            }
            cout << "---> At line [" << lineIndex << "]:\n";
            cout << "---> EXPECTED: [" << lineInExpectedFile << "]\n";
            cout << "---> ACTUAL:   [" << lineInTestFile << "]\n\n";
            isDifferenceFound = true;
            break;
        }
        lines.emplace_back(lineInExpectedFile);
    }
    if (!isDifferenceFound) {
        if (expectedFileReader.isNotFinished() || testFileReader.isNotFinished()) {
            isDifferenceFound = true;
            EXPECT_FALSE(expectedFileReader.isNotFinished());
            EXPECT_FALSE(testFileReader.isNotFinished());
            cout << "---> EXPECTED LAST LINE: [" << lineInExpectedFile << "]\n";
            cout << "---> ACTUAL   LAST LINE: [" << lineInTestFile << "]\n\n";
            cout << "Remaining EXPECTED contents:\n";
            while (expectedFileReader.isNotFinished()) {
                cout << expectedFileReader.getLine();
                cout << "\n";
            }
            cout << "\nRemaining ACTUAL contents:\n";
            while (testFileReader.isNotFinished()) {
                cout << testFileReader.getLine();
                cout << "\n";
            }
            expectedFileReader.moveToTheBeginning();
            cout << "\nAll EXPECTED contents:\n";
            while (expectedFileReader.isNotFinished()) {
                cout << expectedFileReader.getLine();
                cout << "\n";
            }
            testFileReader.moveToTheBeginning();
            cout << "\nAll ACTUAL contents:\n";
            while (testFileReader.isNotFinished()) {
                cout << testFileReader.getLine();
                cout << "\n";
            }
            cout << "\n";
        }
    }
    if (isDifferenceFound) {
        runDiffForTwoFiles(expectedFilePathHandler.getPath(), testFilePathHandler.getPath());
    }
}

void runFormatter(path const& file) {
    string command(FORMATTER_APPLICATION_PATH);
    command += R"( -style=file -i ")";
    command += file.string();
    command += R"(")";
    runInConsole(command);
}

void runDiffForTwoFiles(path const& file1, path const& file2) {
    string command(DIFF_APPLICATION_PATH);
    command += R"( ")";
    command += file1.string();
    command += R"(" ")";
    command += file2.string();
    command += R"(")";
    runInConsole(command);
}

void runFormatterInDirectory(path const& directoryPath) {
    AlbaLocalPathHandler const directoryPathHandler(directoryPath);
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const filePathHandler(filePath);
            if (isCppFileExtension(filePathHandler.getExtension().string())) {
                runFormatter(filePathHandler.getPath());
            }
        });
}

void runInConsole(string const& command) {
    // NOLINTBEGIN(cert-env33-c)
    cout << "---> command [" << command << "]:\n";
    system(command.c_str());
    // NOLINTEND(cert-env33-c)
}

}  // namespace alba::CodeUtilities
