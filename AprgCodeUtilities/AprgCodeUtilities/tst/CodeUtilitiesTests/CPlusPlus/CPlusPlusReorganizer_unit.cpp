#include <CodeUtilities/CPlusPlus/CPlusPlusReorganizer.hpp>
#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilitiesTests/MtDirectoryConstants.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

namespace {

void runFormatter(string const& file) {
    string command(FORMATTER_APPLICATION_PATH);
    command += R"( -style=file -i ")";
    command += file;
    command += R"(")";
    cout << "---> command [" << command << "]:\n";
    // system(command.c_str());
}

void runDiffForTwoFiles(string const& file1, string const& file2) {
    string command(DIFF_APPLICATION_PATH);
    command += R"( ")";
    command += file1;
    command += R"(" ")";
    command += file2;
    command += R"(")";
    cout << "---> command [" << command << "]:\n";
    // system(command.c_str());
}

void runFormatterInDirectory(string const& directoryPath) {
    CPlusPlusReorganizer const reorganizer;
    AlbaLocalPathHandler const directoryPathHandler(directoryPath);
    ListOfPaths directories;
    ListOfPaths files;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler const filePathHandler(file);
        if (isCppFileExtension(filePathHandler.getExtension())) {
            runFormatter(filePathHandler.getFullPath());
        }
    }
}

void copyFile(string const& source, string const& destination) {
    AlbaLocalPathHandler sourcePathHandler(source);
    AlbaLocalPathHandler const destinationPathHandler(destination);
    sourcePathHandler.copyToNewFile(destinationPathHandler.getFullPath());
}

void verifyFile(string const& expectedFile, string const& testFile) {
    AlbaLocalPathHandler const expectedFilePathHandler(expectedFile);
    AlbaLocalPathHandler const testFilePathHandler(testFile);
    ifstream expectedFileStream(expectedFilePathHandler.getFullPath());
    ifstream testFileStream(testFilePathHandler.getFullPath());
    AlbaFileReader expectedFileReader(expectedFileStream);
    AlbaFileReader testFileReader(testFileStream);
    bool isDifferenceFound(false);
    strings lines;
    while (expectedFileReader.isNotFinished() && testFileReader.isNotFinished()) {
        string const lineInExpectedFile(expectedFileReader.getLine());
        string const lineInTestFile(testFileReader.getLine());
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
            runDiffForTwoFiles(expectedFilePathHandler.getFullPath(), testFilePathHandler.getFullPath());
            break;
        }
        lines.emplace_back(lineInExpectedFile);
    }
    if (!isDifferenceFound) {
        EXPECT_FALSE(expectedFileReader.isNotFinished());
        EXPECT_FALSE(testFileReader.isNotFinished());
    }
}

void clearFile(string const& file) { ofstream const expectedFileStream(AlbaLocalPathHandler(file).getFullPath()); }

void processDirectory(string const& directoryPath) {
    CPlusPlusReorganizer reorganizer;
    reorganizer.processDirectory(directoryPath);
    runFormatterInDirectory(directoryPath);
}

void processAprgDirectory(string const& aprgPath) {
    CPlusPlusReorganizer const reorganizer;
    AlbaLocalPathHandler const aprgPathHandler(aprgPath);
    ListOfPaths directories;
    ListOfPaths files;
    aprgPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler const filePathHandler(file);
        if (filePathHandler.getFile() == "CppProjectIndicatorFile.txt") {
            processDirectory(filePathHandler.getDirectory());
        }
    }
}

}  // namespace

TEST(CPlusPlusReorganizerTest, DISABLED_ActualProcessAprgDirectoryTest) {
    processAprgDirectory(R"(F:\Branches\aprg_project\aprg_semi_clean\aprg)");
}

TEST(CPlusPlusReorganizerTest, DISABLED_ActualProcessDirectoryTest) {
    processDirectory(R"(F:\Branches\aprg_project\aprg\aprg\Chess\ChessPeek\ChessPeek)");
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaConfigurationHolderWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaConfigurationHolder.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaConfigurationHolder.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitManipulationClassDefinitionWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitManipulationClassDefinition.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitManipulationClassDefinition.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaDebugWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaDebug.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaDebug.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaOptionalWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaOptional.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaOptional.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitConstantsWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitConstants.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitConstants.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaLocalPathHandlerWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaLocalPathHandler.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaLocalPathHandler.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaValueRangeWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaValueRange.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaValueRange.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaMatrixWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMatrix.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMatrix.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitUtilitiesBuiltInWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitUtilitiesBuiltIn.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitUtilitiesBuiltIn.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaXYZWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaXYZ.hpp)", TEST_HEADER_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaXYZ.hpp)", TEST_HEADER_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaMacrosUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMacros.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMacros_unit.cpp)", TEST_UNIT_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMacros.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMacros_unit.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_UNIT_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaSingletonUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaSingleton.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaSingleton_unit.cpp)", TEST_UNIT_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaSingleton.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaSingleton_unit.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_UNIT_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaFundamentalOperationsCounterUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFundamentalOperationsCounter.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFundamentalOperationsCounter_unit.cpp)", TEST_UNIT_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFundamentalOperationsCounter.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFundamentalOperationsCounter_unit.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_UNIT_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaContainerHelperWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaContainerHelper.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaContainerHelper.cpp)", TEST_IMPLEMENTATION_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaContainerHelper.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaContainerHelper.cpp)", TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaNumberWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.cpp)", TEST_IMPLEMENTATION_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.cpp)", TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaUserInterfaceWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaUserInterface.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaUserInterface.cpp)", TEST_IMPLEMENTATION_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaUserInterface.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaUserInterface.cpp)", TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeCPlusPlusTokenizerWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/CPlusPlusTokenizer.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/CPlusPlusTokenizer.cpp)", TEST_IMPLEMENTATION_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/CPlusPlusTokenizer.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/CPlusPlusTokenizer.cpp)", TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeBtsLogPrintWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/BtsLogPrint.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/BtsLogPrint.cpp)", TEST_IMPLEMENTATION_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/BtsLogPrint.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/BtsLogPrint.cpp)", TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeTermRaiseToTermsWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/TermRaiseToTerms.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/TermRaiseToTerms.cpp)", TEST_IMPLEMENTATION_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/TermRaiseToTerms.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/TermRaiseToTerms.cpp)", TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaStringHelperUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper.cpp)", TEST_IMPLEMENTATION_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper_unit.cpp)", TEST_UNIT_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper.cpp)", TEST_IMPLEMENTATION_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper_unit.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_UNIT_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaFileReaderUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader.cpp)", TEST_IMPLEMENTATION_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader_unit.cpp)", TEST_UNIT_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader.cpp)", TEST_IMPLEMENTATION_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader_unit.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_UNIT_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaWindowsScreenMonitoringUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring.cpp)", TEST_IMPLEMENTATION_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring_unit.cpp)", TEST_UNIT_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring.cpp)", TEST_IMPLEMENTATION_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring_unit.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_UNIT_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeLimitsAtInfinityUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity.cpp)", TEST_IMPLEMENTATION_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity_unit.cpp)", TEST_UNIT_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity.cpp)", TEST_IMPLEMENTATION_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity_unit.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_UNIT_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeCommonFunctionLibraryUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary.cpp)", TEST_IMPLEMENTATION_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary_unit.cpp)", TEST_UNIT_FILE);

    reorganizer.processHeaderFile(TEST_HEADER_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);
    reorganizer.processImplementationFile(TEST_HEADER_FILE, TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary.cpp)", TEST_IMPLEMENTATION_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary_unit.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_UNIT_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeDownloadMovesFromChessDotComTestsWorks) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/DownloadMovesFromChessDotComTests.cpp)", TEST_UNIT_FILE);

    reorganizer.processImplementationFile("", TEST_UNIT_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/DownloadMovesFromChessDotComTests.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_HEADER_FILE);
}

TEST(CPlusPlusReorganizerTest, ReorganizeBenchmarkTestsWorks) {
    CPlusPlusReorganizer reorganizer;

    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumberPerformanceTests.cpp)", TEST_UNIT_FILE);
    reorganizer.processImplementationFile("", TEST_UNIT_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumberPerformanceTests.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_UNIT_FILE);

    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/BitBuiltInFunctionsPerformanceTests.cpp)", TEST_UNIT_FILE);
    reorganizer.processImplementationFile("", TEST_UNIT_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/BitBuiltInFunctionsPerformanceTests.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_UNIT_FILE);

    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/NumberOfOnesPerformanceTests.cpp)", TEST_UNIT_FILE);
    reorganizer.processImplementationFile("", TEST_UNIT_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/NumberOfOnesPerformanceTests.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_UNIT_FILE);

    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/RandomizerPerformanceTests.cpp)", TEST_UNIT_FILE);
    reorganizer.processImplementationFile("", TEST_UNIT_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/RandomizerPerformanceTests.cpp)", TEST_UNIT_FILE);
    clearFile(TEST_UNIT_FILE);
}

}  // namespace alba::CodeUtilities
