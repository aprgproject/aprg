#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ProcessFiles/GrepFile/AlbaGrepFile.hpp>
#include <ProcessFilesTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba {

TEST(AlbaGrepFileTest, NoOutputIsWrittenWhenInputIsNonExisting) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    AlbaGrepFile grepFile("[.]");
    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(APRG_PROCESS_FILES_TEST_NON_EXISTING_FILE, file1ToReadPathHandler.getPath());
    EXPECT_FALSE(grepFile.isOutputFileWritten());
}

TEST(AlbaGrepFileTest, GrepUpdatesWorks) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    AlbaLocalPathHandler const file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    for (int i = 0; i < 100; ++i) {
        testFile << i << "\n";
    }
    testFile.close();

    double capturedPercentage = 0;
    AlbaGrepFile grepFile("[0]", [&](double const percentage) -> void { capturedPercentage = percentage; });
    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(file1ToReadPathHandler.getPath(), file2ToReadPathHandler.getPath());
    EXPECT_TRUE(grepFile.isOutputFileWritten());
    EXPECT_DOUBLE_EQ(100, capturedPercentage);
}

TEST(AlbaGrepFileTest, GrepWorks) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    AlbaLocalPathHandler const file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(As a person, I think that Mark is so cool)"
             << "\n";
    testFile << R"(As a designer, I know that Mark Earvin is so cool)"
             << "\n";
    testFile << R"(As a programmer, I know that Earvin is so cool)"
             << "\n";
    testFile << R"(As a coder, I know that MARKalba is so cool)"
             << "\n";
    testFile.close();

    AlbaGrepFile grepFile("[mark]");
    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(file1ToReadPathHandler.getPath(), file2ToReadPathHandler.getPath());
    EXPECT_TRUE(grepFile.isOutputFileWritten());

    ifstream outputTestFile(file2ToReadPathHandler.getPath());
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(As a person, I think that Mark is so cool)", fileReader.getLine());
    EXPECT_EQ(R"(As a designer, I know that Mark Earvin is so cool)", fileReader.getLine());
    EXPECT_EQ(R"(As a coder, I know that MARKalba is so cool)", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

}  // namespace alba
