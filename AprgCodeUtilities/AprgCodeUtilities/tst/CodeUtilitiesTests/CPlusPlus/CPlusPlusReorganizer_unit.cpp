#include <CodeUtilities/CPlusPlus/CPlusPlusReorganizer.hpp>
#include <CodeUtilitiesTests/MtDirectoryConstants.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <TestUtilities/TestUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace std::filesystem;

namespace alba::CodeUtilities {

namespace {

void processDirectory(path const& directoryPath) {
    CPlusPlusReorganizer reorganizer;
    reorganizer.processDirectory(directoryPath);
    runFormatterInDirectory(directoryPath);
}

void processAprgDirectory(string const& aprgPath) {
    CPlusPlusReorganizer const reorganizer;
    AlbaLocalPathHandler const aprgPathHandler(aprgPath);
    aprgPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const filePathHandler(filePath);
            if (filePathHandler.getFile() == "CppProjectIndicatorFile.txt") {
                processDirectory(filePathHandler.getDirectory());
            }
        });
}

}  // namespace

TEST(CPlusPlusReorganizerTest, DISABLED_ActualAprgDirectoryTest) {
    processAprgDirectory(R"(F:\Branches\aprg_project\aprg_semi_clean\aprg)");
}

TEST(CPlusPlusReorganizerTest, DISABLED_ActualDirectoryTest) {
    processDirectory(R"(F:\Branches\aprg_project\aprg\aprg\AprgAlgebra\AprgAlgebra)");
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaConfigurationHolderWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaConfigurationHolder.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaConfigurationHolder.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaConfigurationHolder.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitManipulationClassDefinitionWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY
                                      R"(/ReorganizerTests/Before/AlbaBitManipulationClassDefinition.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY
                                     R"(/ReorganizerTests/After/AlbaBitManipulationClassDefinition.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY
                                        R"(/ReorganizerTests/Expected/AlbaBitManipulationClassDefinition.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaDebugWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaDebug.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaDebug.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaDebug.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaOptionalWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaOptional.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaOptional.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaOptional.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitConstantsWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitConstants.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitConstants.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaBitConstants.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaLocalPathHandlerWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaLocalPathHandler.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaLocalPathHandler.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaLocalPathHandler.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaValueRangeWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaValueRange.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaValueRange.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaValueRange.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaMatrixWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMatrix.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMatrix.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaMatrix.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaBitUtilitiesBuiltInWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaBitUtilitiesBuiltIn.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaBitUtilitiesBuiltIn.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaBitUtilitiesBuiltIn.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaXYZWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaXYZ.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaXYZ.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaXYZ.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaMacrosUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMacros.hpp)");
    string const beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaMacros_unit.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMacros.hpp)");
    string const afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaMacros_unit.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaMacros.hpp)");
    string const expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaMacros_unit.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaSingletonUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaSingleton.hpp)");
    string const beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaSingleton_unit.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaSingleton.hpp)");
    string const afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaSingleton_unit.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaSingleton.hpp)");
    string const expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaSingleton_unit.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaFundamentalOperationsCounterUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY
                                      R"(/ReorganizerTests/Before/AlbaFundamentalOperationsCounter.hpp)");
    string const beforeUnitTestFilePath(TEST_DIRECTORY
                                        R"(/ReorganizerTests/Before/AlbaFundamentalOperationsCounter_unit.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFundamentalOperationsCounter.hpp)");
    string const afterUnitTestFilePath(TEST_DIRECTORY
                                       R"(/ReorganizerTests/After/AlbaFundamentalOperationsCounter_unit.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY
                                        R"(/ReorganizerTests/Expected/AlbaFundamentalOperationsCounter.hpp)");
    string const expectedUnitTestFilePath(TEST_DIRECTORY
                                          R"(/ReorganizerTests/Expected/AlbaFundamentalOperationsCounter_unit.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeUnitTestFilePath, afterUnitTestFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterUnitTestFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedUnitTestFilePath, afterUnitTestFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaCombineAndGrepFilesWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaCombineAndGrepFiles.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaCombineAndGrepFiles.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaCombineAndGrepFiles.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaCombineAndGrepFiles.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaCombineAndGrepFiles.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY
                                                R"(/ReorganizerTests/Expected/AlbaCombineAndGrepFiles.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaContainerHelperWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaContainerHelper.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaContainerHelper.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaContainerHelper.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaContainerHelper.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaContainerHelper.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaContainerHelper.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaNumberWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaNumber.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaNumber.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaUserInterfaceWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaUserInterface.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaUserInterface.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaUserInterface.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaUserInterface.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaUserInterface.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaUserInterface.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeCPlusPlusTokenizerWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CPlusPlusTokenizer.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CPlusPlusTokenizer.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CPlusPlusTokenizer.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CPlusPlusTokenizer.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/CPlusPlusTokenizer.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/CPlusPlusTokenizer.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeBtsLogPrintWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/BtsLogPrint.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/BtsLogPrint.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/BtsLogPrint.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/BtsLogPrint.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/BtsLogPrint.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/BtsLogPrint.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeTermRaiseToTermsWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/TermRaiseToTerms.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/TermRaiseToTerms.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/TermRaiseToTerms.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/TermRaiseToTerms.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/TermRaiseToTerms.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/TermRaiseToTerms.cpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processHeaderFile(afterHeaderFilePath);
    reorganizer.processImplementationFile(afterHeaderFilePath, afterImplementationFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeAlbaStringHelperUnitTestWorks) {
    CPlusPlusReorganizer reorganizer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper.cpp)");
    string const beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaStringHelper_unit.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper.cpp)");
    string const afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaStringHelper_unit.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaStringHelper.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaStringHelper.cpp)");
    string const expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaStringHelper_unit.cpp)");
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
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader.cpp)");
    string const beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaFileReader_unit.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader.cpp)");
    string const afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaFileReader_unit.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaFileReader.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaFileReader.cpp)");
    string const expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaFileReader_unit.cpp)");
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
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY
                                              R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring.cpp)");
    string const beforeUnitTestFilePath(TEST_DIRECTORY
                                        R"(/ReorganizerTests/Before/AlbaWindowsScreenMonitoring_unit.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY
                                             R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring.cpp)");
    string const afterUnitTestFilePath(TEST_DIRECTORY
                                       R"(/ReorganizerTests/After/AlbaWindowsScreenMonitoring_unit.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/AlbaWindowsScreenMonitoring.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY
                                                R"(/ReorganizerTests/Expected/AlbaWindowsScreenMonitoring.cpp)");
    string const expectedUnitTestFilePath(TEST_DIRECTORY
                                          R"(/ReorganizerTests/Expected/AlbaWindowsScreenMonitoring_unit.cpp)");
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
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity.cpp)");
    string const beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/LimitsAtInfinity_unit.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity.cpp)");
    string const afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/LimitsAtInfinity_unit.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/LimitsAtInfinity.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/LimitsAtInfinity.cpp)");
    string const expectedUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/LimitsAtInfinity_unit.cpp)");
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
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary.hpp)");
    string const beforeImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary.cpp)");
    string const beforeUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Before/CommonFunctionLibrary_unit.cpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary.hpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary.cpp)");
    string const afterUnitTestFilePath(TEST_DIRECTORY R"(/ReorganizerTests/After/CommonFunctionLibrary_unit.cpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/ReorganizerTests/Expected/CommonFunctionLibrary.hpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY
                                                R"(/ReorganizerTests/Expected/CommonFunctionLibrary.cpp)");
    string const expectedUnitTestFilePath(TEST_DIRECTORY
                                          R"(/ReorganizerTests/Expected/CommonFunctionLibrary_unit.cpp)");
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
    string const beforeImplementationFilePath(TEST_DIRECTORY
                                              R"(/ReorganizerTests/Before/DownloadMovesFromChessDotComTests.cpp)");
    string const afterImplementationFilePath(TEST_DIRECTORY
                                             R"(/ReorganizerTests/After/DownloadMovesFromChessDotComTests.cpp)");
    string const expectedImplementationFilePath(TEST_DIRECTORY
                                                R"(/ReorganizerTests/Expected/DownloadMovesFromChessDotComTests.cpp)");
    copyFile(beforeImplementationFilePath, afterImplementationFilePath);

    reorganizer.processImplementationFile("", afterImplementationFilePath);

    verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
}

TEST(CPlusPlusReorganizerTest, ReorganizeBenchmarkTestsWorks) {
    CPlusPlusReorganizer reorganizer;

    {
        string const beforeImplementationFilePath(TEST_DIRECTORY
                                                  R"(/ReorganizerTests/Before/AlbaNumberPerformanceTests.cpp)");
        string const afterImplementationFilePath(TEST_DIRECTORY
                                                 R"(/ReorganizerTests/After/AlbaNumberPerformanceTests.cpp)");
        string const expectedImplementationFilePath(TEST_DIRECTORY
                                                    R"(/ReorganizerTests/Expected/AlbaNumberPerformanceTests.cpp)");
        copyFile(beforeImplementationFilePath, afterImplementationFilePath);

        reorganizer.processImplementationFile("", afterImplementationFilePath);

        verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    }

    {
        string const beforeImplementationFilePath(
            TEST_DIRECTORY R"(/ReorganizerTests/Before/BitBuiltInFunctionsPerformanceTests.cpp)");
        string const afterImplementationFilePath(TEST_DIRECTORY
                                                 R"(/ReorganizerTests/After/BitBuiltInFunctionsPerformanceTests.cpp)");
        string const expectedImplementationFilePath(
            TEST_DIRECTORY R"(/ReorganizerTests/Expected/BitBuiltInFunctionsPerformanceTests.cpp)");
        copyFile(beforeImplementationFilePath, afterImplementationFilePath);

        reorganizer.processImplementationFile("", afterImplementationFilePath);

        verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    }

    {
        string const beforeImplementationFilePath(TEST_DIRECTORY
                                                  R"(/ReorganizerTests/Before/NumberOfOnesPerformanceTests.cpp)");
        string const afterImplementationFilePath(TEST_DIRECTORY
                                                 R"(/ReorganizerTests/After/NumberOfOnesPerformanceTests.cpp)");
        string const expectedImplementationFilePath(TEST_DIRECTORY
                                                    R"(/ReorganizerTests/Expected/NumberOfOnesPerformanceTests.cpp)");
        copyFile(beforeImplementationFilePath, afterImplementationFilePath);

        reorganizer.processImplementationFile("", afterImplementationFilePath);

        verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    }

    {
        string const beforeImplementationFilePath(TEST_DIRECTORY
                                                  R"(/ReorganizerTests/Before/RandomizerPerformanceTests.cpp)");
        string const afterImplementationFilePath(TEST_DIRECTORY
                                                 R"(/ReorganizerTests/After/RandomizerPerformanceTests.cpp)");
        string const expectedImplementationFilePath(TEST_DIRECTORY
                                                    R"(/ReorganizerTests/Expected/RandomizerPerformanceTests.cpp)");
        copyFile(beforeImplementationFilePath, afterImplementationFilePath);

        reorganizer.processImplementationFile("", afterImplementationFilePath);

        verifyFile(expectedImplementationFilePath, afterImplementationFilePath);
    }
}

}  // namespace alba::CodeUtilities
