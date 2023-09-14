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
    system(command.c_str());
}

void runDiffForTwoFiles(string const& file1, string const& file2) {
    string command(DIFF_APPLICATION_PATH);
    command += R"( ")";
    command += file1;
    command += R"(" ")";
    command += file2;
    command += R"(")";
    cout << "---> command [" << command << "]:\n";
    system(command.c_str());
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

void clearFile(string const& file) { ofstream const expectedFileStream(AlbaLocalPathHandler(file).getFullPath()); }

void copyFile(string const& source, string const& destination) {
    AlbaLocalPathHandler sourcePathHandler(source);
    AlbaLocalPathHandler const destinationPathHandler(destination);
    clearFile(destinationPathHandler.getFullPath());
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
            runDiffForTwoFiles(expectedFilePathHandler.getFullPath(), testFilePathHandler.getFullPath());
            break;
        }
        lines.emplace_back(lineInExpectedFile);
    }
    if (!isDifferenceFound) {
        if (expectedFileReader.isNotFinished() || testFileReader.isNotFinished()) {
            cout << "---> EXPECTED LAST LINE: [" << lineInExpectedFile << "]\n";
            cout << "---> ACTUAL   LAST LINE: [" << lineInTestFile << "]\n\n";
            cout << "Remaining EXPECTED contents:\n";
            while (expectedFileReader.isNotFinished()) {
                cout << expectedFileReader.getLine();
            }
            cout << "Remaining ACTUAL contents:\n";
            while (testFileReader.isNotFinished()) {
                cout << testFileReader.getLine();
            }
        }
        EXPECT_FALSE(expectedFileReader.isNotFinished());
        EXPECT_FALSE(testFileReader.isNotFinished());
    }
}

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
    processDirectory(R"(F:\Branches\aprg_project\aprg\aprg\AprgCodeUtilities\AprgCodeUtilities)");
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaConfigurationHolderWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaConfigurationHolder.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaConfigurationHolder.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaConfigurationHolder.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitManipulationClassDefinitionWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitManipulationClassDefinition.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitManipulationClassDefinition.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY
                                  R"(/ReorganizerTests/Expected/AlbaBitManipulationClassDefinition.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaDebugWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaDebug.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaDebug.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaDebug.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaOptionalWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaOptional.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaOptional.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaOptional.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitConstantsWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitConstants.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitConstants.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaBitConstants.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaLocalPathHandlerWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaLocalPathHandler.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaLocalPathHandler.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaLocalPathHandler.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaValueRangeWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaValueRange.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaValueRange.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaValueRange.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaMatrixWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMatrix.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMatrix.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaMatrix.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitUtilitiesBuiltInWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitUtilitiesBuiltIn.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitUtilitiesBuiltIn.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaBitUtilitiesBuiltIn.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaXYZWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaXYZ.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaXYZ.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaXYZ.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaMacrosUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMacros.hpp)");
    string beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMacros_unit.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMacros.hpp)");
    string afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMacros_unit.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaMacros.hpp)");
    string expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaMacros_unit.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaSingletonUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaSingleton.hpp)");
    string beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaSingleton_unit.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaSingleton.hpp)");
    string afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaSingleton_unit.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaSingleton.hpp)");
    string expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaSingleton_unit.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaFundamentalOperationsCounterUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFundamentalOperationsCounter.hpp)");
    string beforeUnitTestFilePath(TEST_DIRECTORY
                                  R"(/ReorganizerTests/Before/AlbaFundamentalOperationsCounter_unit.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFundamentalOperationsCounter.hpp)");
    string afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFundamentalOperationsCounter_unit.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaFundamentalOperationsCounter.hpp)");
    string expectedUnitTestFilePath(TEST_DIRECTORY
                                    R"(/ReorganizerTests/Expected/AlbaFundamentalOperationsCounter_unit.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaContainerHelperWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaContainerHelper.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaContainerHelper.cpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaContainerHelper.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaContainerHelper.cpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaContainerHelper.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaContainerHelper.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaNumberWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.cpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.cpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaNumber.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaNumber.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaUserInterfaceWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaUserInterface.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaUserInterface.cpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaUserInterface.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaUserInterface.cpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaUserInterface.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaUserInterface.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeCPlusPlusTokenizerWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CPlusPlusTokenizer.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CPlusPlusTokenizer.cpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CPlusPlusTokenizer.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CPlusPlusTokenizer.cpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/CPlusPlusTokenizer.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/CPlusPlusTokenizer.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeBtsLogPrintWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/BtsLogPrint.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/BtsLogPrint.cpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/BtsLogPrint.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/BtsLogPrint.cpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/BtsLogPrint.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/BtsLogPrint.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeTermRaiseToTermsWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/TermRaiseToTerms.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/TermRaiseToTerms.cpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/TermRaiseToTerms.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/TermRaiseToTerms.cpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/TermRaiseToTerms.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/TermRaiseToTerms.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaStringHelperUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper.cpp)");
    string beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper_unit.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper.cpp)");
    string afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper_unit.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaStringHelper.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaStringHelper.cpp)");
    string expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaStringHelper_unit.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaFileReaderUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader.cpp)");
    string beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader_unit.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader.cpp)");
    string afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader_unit.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaFileReader.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaFileReader.cpp)");
    string expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaFileReader_unit.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaWindowsScreenMonitoringUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring.cpp)");
    string beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring_unit.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring.cpp)");
    string afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring_unit.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaWindowsScreenMonitoring.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY
                                          R"(/ReorganizerTests/Expected/AlbaWindowsScreenMonitoring.cpp)");
    string expectedUnitTestFilePath(TEST_DIRECTORY
                                    R"(/ReorganizerTests/Expected/AlbaWindowsScreenMonitoring_unit.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeLimitsAtInfinityUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity.cpp)");
    string beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity_unit.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity.cpp)");
    string afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity_unit.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/LimitsAtInfinity.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/LimitsAtInfinity.cpp)");
    string expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/LimitsAtInfinity_unit.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeCommonFunctionLibraryUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary.hpp)");
    string beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary.cpp)");
    string beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary_unit.hpp)");
    string afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary.hpp)");
    string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary.cpp)");
    string afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary_unit.hpp)");
    string expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/CommonFunctionLibrary.hpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/CommonFunctionLibrary.cpp)");
    string expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/CommonFunctionLibrary_unit.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeDownloadMovesFromChessDotComTestsWorks) {
    CPlusPlusReorganizer reorganizer;
    string beforeImplementationFilePath(TEST_DIRECTORY
                                        R"(/ReorganizerTests/Before/DownloadMovesFromChessDotComTests.cpp)");
    string afterImplementationFilePath(TEST_DIRECTORY
                                       R"(/ReorganizerTests/After/DownloadMovesFromChessDotComTests.cpp)");
    string expectedImplementationFilePath(TEST_DIRECTORY
                                          R"(/ReorganizerTests/Expected/DownloadMovesFromChessDotComTests.cpp)");
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processImplementationFile("", afterImplementationFilePath);

    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeBenchmarkTestsWorks) {
    CPlusPlusReorganizer reorganizer;

    {
        string beforeImplementationFilePath(TEST_DIRECTORY
                                            R"(/ReorganizerTests/Before/AlbaNumberPerformanceTests.cpp)");
        string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumberPerformanceTests.cpp)");
        string expectedImplementationFilePath(TEST_DIRECTORY
                                              R"(/ReorganizerTests/Expected/AlbaNumberPerformanceTests.cpp)");
        copyFile(beforeImplementationFilePath, afterImplementationFilePath);

        reorganizer.processImplementationFile("", afterImplementationFilePath);

        verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    }

    {
        string beforeImplementationFilePath(TEST_DIRECTORY
                                            R"(/ReorganizerTests/Before/BitBuiltInFunctionsPerformanceTests.cpp)");
        string afterImplementationFilePath(TEST_DIRECTORY
                                           R"(/ReorganizerTests/After/BitBuiltInFunctionsPerformanceTests.cpp)");
        string expectedImplementationFilePath(TEST_DIRECTORY
                                              R"(/ReorganizerTests/Expected/BitBuiltInFunctionsPerformanceTests.cpp)");
        copyFile(beforeImplementationFilePath, afterImplementationFilePath);

        reorganizer.processImplementationFile("", afterImplementationFilePath);

        verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    }

    {
        string beforeImplementationFilePath(TEST_DIRECTORY
                                            R"(/ReorganizerTests/Before/NumberOfOnesPerformanceTests.cpp)");
        string afterImplementationFilePath(TEST_DIRECTORY
                                           R"(/ReorganizerTests/After/NumberOfOnesPerformanceTests.cpp)");
        string expectedImplementationFilePath(TEST_DIRECTORY
                                              R"(/ReorganizerTests/Expected/NumberOfOnesPerformanceTests.cpp)");
        copyFile(beforeImplementationFilePath, afterImplementationFilePath);

        reorganizer.processImplementationFile("", afterImplementationFilePath);

        verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    }

    {
        string beforeImplementationFilePath(TEST_DIRECTORY
                                            R"(/ReorganizerTests/Before/RandomizerPerformanceTests.cpp)");
        string afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/RandomizerPerformanceTests.cpp)");
        string expectedImplementationFilePath(TEST_DIRECTORY
                                              R"(/ReorganizerTests/Expected/RandomizerPerformanceTests.cpp)");
        copyFile(beforeImplementationFilePath, afterImplementationFilePath);

        reorganizer.processImplementationFile("", afterImplementationFilePath);

        verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    }
}

}  // namespace alba::CodeUtilities
