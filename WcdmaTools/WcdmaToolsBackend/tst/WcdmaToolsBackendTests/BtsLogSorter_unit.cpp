#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <WcdmaToolsBackend/BtsLogSorter.hpp>
#include <WcdmaToolsBackendTests/BtsLogSorterTest.hpp>

#include <gtest/gtest.h>

namespace alba::ProgressCounters {
double totalSizeToBeReadForCombine;
double totalSizeReadForCombine;
int writeProgressForCombine;
}  // namespace alba::ProgressCounters

using namespace alba;
using namespace std;

namespace wcdmaToolsBackend {

TEST_F(BtsLogSorterTest, DISABLED_PerformanceTest) {
    BtsLogSorter btsLogSorter(m_configuration);
    btsLogSorter.processDirectory(
        R"(D:\W\ZZZ_Useless_Logs\PR111534\PR(alarm 160 didn't cancel)\Test\PR(alarm 160 didn't cancel))");
    btsLogSorter.saveLogsToOutputFile(
        R"(D:\W\ZZZ_Useless_Logs\PR111534\PR(alarm 160 didn't cancel)\Test\sortednew.log)");
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotWorksWithPrintsAreMerged) {
    BtsLogSorter btsLogSorter(m_configuration);
    AlbaLocalPathHandler inputPathHandler(
        APRG_DIR
        R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\input.log)");
    AlbaLocalPathHandler outputPathHandler(
        APRG_DIR
        R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged\output.log)");
    btsLogSorter.processFile(inputPathHandler.getFullPath());
    btsLogSorter.saveLogsToOutputFile(outputPathHandler.getFullPath());

    int lines = 0;
    ifstream inputLogFileStream(outputPathHandler.getFullPath());
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        fileReader.getLineAndIgnoreWhiteSpaces();
        ++lines;
    }

    EXPECT_EQ(2, lines);
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotWorksWithPrintsAreMerged2) {
    BtsLogSorter btsLogSorter(m_configuration);
    AlbaLocalPathHandler inputPathHandler(
        APRG_DIR
        R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged2\input.log)");
    AlbaLocalPathHandler outputPathHandler(
        APRG_DIR
        R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreMerged2\output.log)");
    btsLogSorter.processFile(inputPathHandler.getFullPath());
    btsLogSorter.saveLogsToOutputFile(outputPathHandler.getFullPath());

    int lines = 0;
    ifstream inputLogFileStream(outputPathHandler.getFullPath());
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        fileReader.getLineAndIgnoreWhiteSpaces();
        ++lines;
    }

    EXPECT_EQ(59, lines);
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotWorksWithPrintsAreOrderedBasedOnBtsTime) {
    BtsLogSorter btsLogSorter(m_configuration);
    AlbaLocalPathHandler inputPathHandler(
        APRG_DIR
        R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\input.log)");
    AlbaLocalPathHandler outputPathHandler(
        APRG_DIR
        R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreOrderedBasedOnBtsTime\output.log)");
    btsLogSorter.processFile(inputPathHandler.getFullPath());
    btsLogSorter.saveLogsToOutputFile(outputPathHandler.getFullPath());

    int lines = 0;
    ifstream inputLogFileStream(outputPathHandler.getFullPath());
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        cout << fileReader.getLineAndIgnoreWhiteSpaces() << "\n";
        ++lines;
    }

    EXPECT_EQ(4, lines);
}

TEST_F(BtsLogSorterTest, SyslogsAndSnapshotWorksWithPrintsAreFiltered) {
    m_configuration.m_isFilterGrepOn = true;
    m_configuration.m_filterGrepCondition = "[TCOM/NC]";
    BtsLogSorter btsLogSorter(m_configuration);
    AlbaLocalPathHandler inputPathHandler(
        APRG_DIR
        R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreFiltered\input.log)");
    AlbaLocalPathHandler outputPathHandler(
        APRG_DIR
        R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\ImportantTestingFiles\SyslogsAndSnapshotTest_PrintsAreFiltered\output.log)");
    btsLogSorter.processFile(inputPathHandler.getFullPath());
    btsLogSorter.saveLogsToOutputFile(outputPathHandler.getFullPath());

    int lines = 0;
    ifstream inputLogFileStream(outputPathHandler.getFullPath());
    AlbaFileReader fileReader(inputLogFileStream);
    while (fileReader.isNotFinished()) {
        cout << fileReader.getLineAndIgnoreWhiteSpaces() << "\n";
        ++lines;
    }

    EXPECT_EQ(3, lines);
}

}  // namespace wcdmaToolsBackend
