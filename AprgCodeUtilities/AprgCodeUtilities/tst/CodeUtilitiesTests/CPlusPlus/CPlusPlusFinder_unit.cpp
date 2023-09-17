#include <CodeUtilities/CPlusPlus/CPlusPlusFinder.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

namespace {
void processAprgDirectory(string const& aprgPath) {
    CPlusPlusFinder finder;
    AlbaLocalPathHandler const aprgPathHandler(aprgPath);
    ListOfPaths directories;
    ListOfPaths files;
    aprgPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler const filePathHandler(file);
        if (filePathHandler.getFile() == "CppProjectIndicatorFile.txt") {
            finder.processDirectory(filePathHandler.getDirectory());
        }
    }
}
}  // namespace

TEST(CPlusPlusFinderTest, DISABLED_AprgDirectoryTest) { processAprgDirectory(R"(F:\Branches\aprg_project\aprg\aprg)"); }

TEST(CPlusPlusFinderTest, PathTest) {
    CPlusPlusFinder finder;
    finder.processPath(R"(F:\Branches\aprg_project\aprg\aprg\AprgAlgebra\AprgAlgebra\)");
}

}  // namespace alba::CodeUtilities
