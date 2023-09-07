#include <CodeUtilities/CPlusPlus/CPlusPlusReorganizer.hpp>
#include <CodeUtilitiesTests/MtDirectoryConstants.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>

using namespace std;
using namespace alba::stringHelper;

namespace alba::CodeUtilities {

namespace {
void processAprgDirectory(string const& aprgPath) {
    CPlusPlusReorganizer reorganizer;
    AlbaLocalPathHandler aprgPathHandler(aprgPath);
    ListOfPaths directories;
    ListOfPaths files;
    aprgPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        if (filePathHandler.getFile() == "CppProjectIndicatorFile.txt") {
            reorganizer.processDirectory(filePathHandler.getDirectory());
        }
    }
}
void runFormatterInDirectory(string const& aprgPath) {
    CPlusPlusReorganizer reorganizer;
    AlbaLocalPathHandler aprgPathHandler(aprgPath);
    ListOfPaths directories;
    ListOfPaths files;
    aprgPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        string command(R"(")");
        command += FORMATTER_APPLICATION_PATH;
        command += R"(" -style=file -i ")";
        command += filePathHandler.getFullPath();
        command += R"(")";
        cout << "---> command [" << command << "]:\n";
        system(command.c_str());
    }
}
void copyFile(string const& source, string const& destination) {
    AlbaLocalPathHandler sourcePathHandler(source);
    AlbaLocalPathHandler destinationPathHandler(destination);
    sourcePathHandler.copyToNewFile(destinationPathHandler.getFullPath());
}
void verifyFile(string const& expectedFile, string const& testFile) {
    AlbaLocalPathHandler expectedFilePathHandler(expectedFile);
    AlbaLocalPathHandler testFilePathHandler(testFile);
    ifstream expectedFileStream(expectedFilePathHandler.getFullPath());
    ifstream testFileStream(testFilePathHandler.getFullPath());
    AlbaFileReader expectedFileReader(expectedFileStream);
    AlbaFileReader testFileReader(testFileStream);
    bool isDifferenceFound(false);
    strings lines;
    while (expectedFileReader.isNotFinished() && testFileReader.isNotFinished()) {
        string lineInExpectedFile(expectedFileReader.getLine());
        string lineInTestFile(testFileReader.getLine());
        EXPECT_EQ(lineInExpectedFile, lineInTestFile);
        if (lineInExpectedFile != lineInTestFile) {
            constexpr int LINES_TO_DISPLAY = 6;
            int numberOfLines = static_cast<int>(lines.size());
            int lineIndex = numberOfLines < LINES_TO_DISPLAY ? 0 : numberOfLines - LINES_TO_DISPLAY;
            cout << "Difference occured at:\n";
            for (; lineIndex < numberOfLines; ++lineIndex) {
                cout << lines[lineIndex] << "\n";
            }
            cout << "---> At line [" << lineIndex << "]:\n";
            cout << "---> EXPECTED: [" << lineInExpectedFile << "]\n";
            cout << "---> ACTUAL:   [" << lineInTestFile << "]\n\n";
            isDifferenceFound = true;
            string command(R"(")");
            command += FORMATTER_APPLICATION_PATH;
            command += R"(" ")";
            command += expectedFilePathHandler.getFullPath();
            command += R"(" ")";
            command += testFilePathHandler.getFullPath();
            command += R"(")";
            cout << "---> command [" << command << "]:\n";
            system(command.c_str());
            break;
        }
        lines.emplace_back(lineInExpectedFile);
    }
    if (!isDifferenceFound) {
        EXPECT_FALSE(expectedFileReader.isNotFinished());
        EXPECT_FALSE(testFileReader.isNotFinished());
    }
}
void clearFile(string const& file) { ofstream expectedFileStream(AlbaLocalPathHandler(file).getFullPath()); }
}  // namespace

TEST(CPlusPlusReorganizerTest, ActualTest) {
    CPlusPlusReorganizer reorganizer;
    reorganizer.processDirectory(R"(F:\Branches\aprg_project\aprg_temp\aprg\AprgCommon\AprgCommon)");
    runFormatterInDirectory(R"(F:\Branches\aprg_project\aprg_temp\aprg\AprgCommon\AprgCommon)");
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaNumberWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.cpp)", TEST_IMPLEMENTATION_FILE);

    reorganizer.processHeaderAndImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.cpp)", TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaConfigurationHolderWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaConfigurationHolder.hpp)", TEST_HEADER_FILE);

    reorganizer.reorganizeFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaConfigurationHolder.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitManipulationClassDefinitionWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitManipulationClassDefinition.hpp)", TEST_HEADER_FILE);

    reorganizer.reorganizeFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitManipulationClassDefinition.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaOptionalWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaOptional.hpp)", TEST_HEADER_FILE);

    reorganizer.reorganizeFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaOptional.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitConstantsWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitConstants.hpp)", TEST_HEADER_FILE);

    reorganizer.reorganizeFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitConstants.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaLocalPathHandlerWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaLocalPathHandler.hpp)", TEST_HEADER_FILE);

    reorganizer.reorganizeFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaLocalPathHandler.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaValueRangeWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaValueRange.hpp)", TEST_HEADER_FILE);

    reorganizer.reorganizeFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaValueRange.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaMatrixWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMatrix.hpp)", TEST_HEADER_FILE);

    reorganizer.reorganizeFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMatrix.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

}  // namespace alba::CodeUtilities
