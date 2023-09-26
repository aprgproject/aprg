#include <CodeUtilities/CPlusPlus/CPlusPlusFixer.hpp>
#include <CodeUtilitiesTests/MtDirectoryConstants.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <TestUtilities/TestUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace std::filesystem;

namespace alba::CodeUtilities {

namespace {

void processDirectory(path const& directoryPath) {
    CPlusPlusFixer fixer;
    fixer.processDirectory(directoryPath);
    runFormatterInDirectory(directoryPath);
}

void processAprgDirectory(string const& aprgPath) {
    CPlusPlusFixer fixer;
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

TEST(CPlusPlusFixerTest, DISABLED_ActualAprgDirectoryTest) {
    processAprgDirectory(R"(F:\Branches\aprg_project\aprg_semi_clean\aprg)");
}

TEST(CPlusPlusFixerTest, DISABLED_ActualDirectoryTest) {
    CPlusPlusFixer fixer;
    fixer.processDirectory(R"(F:\Branches\aprg_project\aprg\aprg\gsl\GslTest)");
}

TEST(CPlusPlusFixerTest, FixerWorksForGenericCode) {
    CPlusPlusFixer fixer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/FixerTests/Before/GenericCode.txt)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/FixerTests/After/GenericCode.txt)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/FixerTests/Expected/GenericCode.txt)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    fixer.processFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

TEST(CPlusPlusFixerTest, FixerWorksForHeaderCode) {
    CPlusPlusFixer fixer;
    string const beforeHeaderFilePath(TEST_DIRECTORY R"(/FixerTests/Before/HeaderCode.hpp)");
    string const afterHeaderFilePath(TEST_DIRECTORY R"(/FixerTests/After/HeaderCode.hpp)");
    string const expectedHeaderFilePath(TEST_DIRECTORY R"(/FixerTests/Expected/HeaderCode.hpp)");
    copyFile(beforeHeaderFilePath, afterHeaderFilePath);

    fixer.processFile(afterHeaderFilePath);

    verifyFile(expectedHeaderFilePath, afterHeaderFilePath);
}

}  // namespace alba::CodeUtilities
