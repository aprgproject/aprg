#include <CodeUtilities/CPlusPlus/CPlusPlusReorganizer.hpp>
#include <CodeUtilitiesTests/MtDirectoryConstants.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <fstream>

using namespace std;
using namespace alba::stringHelper;

namespace alba::CodeUtilities {

namespace {
void copyFile(string const& source, string const& destination) {
    AlbaLocalPathHandler sourcePathHandler(source);
    AlbaLocalPathHandler destinationPathHandler(destination);
    sourcePathHandler.copyToNewFile(destinationPathHandler.getFullPath());
}
void verifyFile(string const& expectedFile, string const& testFile) {
    ifstream expectedFileStream(AlbaLocalPathHandler(expectedFile).getFullPath());
    ifstream testFileStream(AlbaLocalPathHandler(testFile).getFullPath());
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
            int numberOfLines = lines.size();
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
        EXPECT_FALSE(expectedFileReader.isNotFinished());
        EXPECT_FALSE(testFileReader.isNotFinished());
    }
}
void clearFile(string const& file) { ofstream expectedFileStream(AlbaLocalPathHandler(file).getFullPath()); }
}  // namespace

TEST(CPlusPlusReorganizerTest, DISABLED_ActualTest) {
    CPlusPlusReorganizer reorganizer;
    reorganizer.processHeaderAndImplementationFile(
        R"(F:\Branches\aprg_project\aprg_semi_clean\aprg\AprgCommon\AprgCommon\src\Common\Math\Number\AlbaNumber.hpp)",
        R"(F:\Branches\aprg_project\aprg_semi_clean\aprg\AprgCommon\AprgCommon\src\Common\Math\Number\AlbaNumber.cpp)");
}

TEST(CPlusPlusReorganizerTest, AlbaNumberTest) {
    CPlusPlusReorganizer reorganizer;
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.hpp)", TEST_HEADER_FILE);
    copyFile(TEST_DIRECTORY R"(/ReorganizerTests/Before/AlbaNumber.cpp)", TEST_IMPLEMENTATION_FILE);

    reorganizer.processHeaderAndImplementationFile(TEST_HEADER_FILE, TEST_IMPLEMENTATION_FILE);

    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.hpp)", TEST_HEADER_FILE);
    verifyFile(TEST_DIRECTORY R"(/ReorganizerTests/After/AlbaNumber.cpp)", TEST_IMPLEMENTATION_FILE);
    clearFile(TEST_HEADER_FILE);
    clearFile(TEST_IMPLEMENTATION_FILE);
}

}  // namespace alba::CodeUtilities
