#include <CodeUtilities/CPlusPlus/CPlusPlusFinder.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

namespace {

void processAprgDirectory(string const& aprgPath) {
    CPlusPlusFinder finder;
    AlbaLocalPathHandler const aprgPathHandler(aprgPath);
    aprgPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const filePathHandler(filePath);
            if (filePathHandler.getFile() == "CppProjectIndicatorFile.txt") {
                finder.processDirectory(filePathHandler.getDirectory());
            }
        });
}

}  // namespace

TEST(CPlusPlusFinderTest, DISABLED_AprgDirectoryTest) { processAprgDirectory(R"(F:\Branches\aprg_project\aprg\aprg)"); }

TEST(CPlusPlusFinderTest, DISABLED_DirectoryTest) {
    CPlusPlusFinder finder;
    finder.processDirectory(R"(F:\Branches\aprg_project\aprg\aprg\AprgAlgebra\AprgAlgebra\)");
}

}  // namespace alba::CodeUtilities
