#include <CodeUtilities/CPlusPlus/CPlusPlusFixer.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

namespace {
void processAprgDirectory(string const& aprgPath) {
    CPlusPlusFixer fixer;
    AlbaLocalPathHandler const aprgPathHandler(aprgPath);
    aprgPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const filePathHandler(filePath);
            if (filePathHandler.getFile() == "CppProjectIndicatorFile.txt") {
                fixer.processDirectory(filePathHandler.getDirectory());
            }
        });
}
}  // namespace

TEST(CPlusPlusFixerTest, DISABLED_AprgDirectoryTest) {
    processAprgDirectory(R"(F:\Branches\aprg_project\aprg_semi_clean\aprg)");
}

TEST(CPlusPlusFixerTest, DISABLED_PathTest) {
    CPlusPlusFixer fixer;
    fixer.processPath(
        R"(F:\Branches\aprg_project\aprg_semi_clean\aprg\AprgAlgebra\AprgAlgebra\src\Algebra\Solution\Solver\MultipleLinearEquations\LinearEquationsEqualitySolver.cpp)");
}

}  // namespace alba::CodeUtilities
