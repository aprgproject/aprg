#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <FileExtractor/AprgFileExtractor.hpp>

#include <gtest/gtest.h>
#ifndef PATH_OF_7Z_TEMP_FILE
static_assert(false, "PATH_OF_7Z_TEMP_FILE is not set in cmake");
#endif
#define PATH_OF_SAMPLE_ZIP_1 APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest.zip)"
#define PATH_OF_SAMPLE_ZIP_2 APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest2.zip)"

using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {

void deleteAllFilesOnDirectory(path const& directoryPath) {
    AlbaLocalPathHandler const topDirectoryPathHandler(directoryPath);
    if (topDirectoryPathHandler.isExistingDirectory()) {
        topDirectoryPathHandler.findFilesAndDirectoriesUnlimitedDepth(
            [](AlbaLocalPathHandler::LocalPath const&) {},
            [&](AlbaLocalPathHandler::LocalPath const& filePath) {
                AlbaLocalPathHandler filePathHandler(filePath);
                EXPECT_TRUE(filePathHandler.deleteFileAndIsSuccessful());
                ASSERT_FALSE(filePathHandler.doesExist());
            });
    }
}

}  // namespace

namespace ProgressCounters {
int numberOfFilesToBeAnalyzedForExtraction;
int numberOfFilesAnalyzedForExtraction;
}  // namespace ProgressCounters

TEST(AprgFileExtractorTest, ListOfFilesFromZipFileAreCorrectlyRetrieved) {
    AprgFileExtractor const fileExtractor;
    AprgFileExtractor::SetOfPaths files;
    fileExtractor.copyRelativeFilePathsFromCompressedFile(PATH_OF_SAMPLE_ZIP_1, files);

    ASSERT_EQ(11U, files.size());
    auto fileIterator = files.begin();
#if defined(OS_LINUX)
    EXPECT_EQ(R"(DirectoryTest/DIR1/File1.log)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/DIR2/File2.txt)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/DIR3/File3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/DIR4/File4.mp3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/DIR5/File5.avi)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/DIR6/SUBDIR1/File6.jpg)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/File1.log)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/File2.txt)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/File3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/File4.mp3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest/File5.avi)", *fileIterator++);
#elif defined(OS_WINDOWS)
    EXPECT_EQ(R"(DirectoryTest\DIR1\File1.log)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR2\File2.txt)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR3\File3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR4\File4.mp3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR5\File5.avi)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR6\SUBDIR1\File6.jpg)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File1.log)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File2.txt)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File4.mp3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File5.avi)", *fileIterator++);
#endif
}

TEST(AprgFileExtractorTest, AllFilesAreExtractedSuccessfully) {
    AprgFileExtractor const fileExtractor;
    AlbaLocalPathHandler const directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\)");
    deleteAllFilesOnDirectory(directoryPathHandler.getPath());

    path const outputDirectoryPath = fileExtractor.extractOnceForAllFiles(PATH_OF_SAMPLE_ZIP_1);

    EXPECT_EQ(directoryPathHandler.getPath(), outputDirectoryPath);
    AlbaLocalPathHandler outputFilePathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_TRUE(outputFilePathHandler.doesExist());
    outputFilePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_TRUE(outputFilePathHandler.doesExist());
    outputFilePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File3)");
    EXPECT_TRUE(outputFilePathHandler.doesExist());
    outputFilePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_TRUE(outputFilePathHandler.doesExist());
    outputFilePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File5.avi)");
    EXPECT_TRUE(outputFilePathHandler.doesExist());
    deleteAllFilesOnDirectory(directoryPathHandler.getPath());
}

TEST(AprgFileExtractorTest, OneFileIsExtractedSuccessfully) {
    AprgFileExtractor const fileExtractor;
    AlbaLocalPathHandler const directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\)");
    AlbaLocalPathHandler const relativeFilePathHandler(R"(DirectoryTest\DIR1\File1.log)");
    AlbaLocalPathHandler filePathHandler(
        APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)");
    deleteAllFilesOnDirectory(directoryPathHandler.getPath());

    path const outputFilePath = fileExtractor.extractOneFile(PATH_OF_SAMPLE_ZIP_1, relativeFilePathHandler.getPath());
    EXPECT_EQ(filePathHandler.getPath(), outputFilePath);
    EXPECT_TRUE(filePathHandler.doesExist());
    // deleteAllFilesOnDirectory(directoryPathHandler.getPath());
}

TEST(AprgFileExtractorTest, DISABLED_ActualTest) {
    AprgFileExtractor fileExtractor(
        R"([LRM] || [alarm] || [UDP] || [CPU] || [syslog] || [ccns] || [tcom] || [startup] || [runtime] || [system] || [radparam] || ([bts]&&([.log]||[.zip]||[.tar])) || [snapshot] || ([tech]&&[report]) || [BTSLogFiles])");
    fileExtractor.extractAllRelevantFiles(R"(D:\W\ZZZ_Useless_Logs\PR103380\New folder\)");
}

TEST(AprgFileExtractorTest, FilesAreExtractedSuccessfullyWithACondition) {
    AprgFileExtractor fileExtractor("[.log]");
    AlbaLocalPathHandler const directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\)");
    deleteAllFilesOnDirectory(directoryPathHandler.getPath());

    fileExtractor.extractAllRelevantFiles(PATH_OF_SAMPLE_ZIP_1);

    AlbaLocalPathHandler filePathHandler(
        APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)");
    EXPECT_TRUE(filePathHandler.doesExist());
    filePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\DirectoryTest\File1.log)");
    EXPECT_TRUE(filePathHandler.doesExist());
    deleteAllFilesOnDirectory(directoryPathHandler.getPath());
}

TEST(AprgFileExtractorTest, FilesAreExtractedRecursivelyWithACondition) {
    AprgFileExtractor fileExtractor("[DirectoryTest]");
    AlbaLocalPathHandler const directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest2\)");
    deleteAllFilesOnDirectory(directoryPathHandler.getPath());

    fileExtractor.extractAllRelevantFiles(PATH_OF_SAMPLE_ZIP_2);

    AlbaLocalPathHandler const filePathHandler(
        APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest2\DirectoryTest2\DirectoryTest2\DirectoryTest2.txt)");
    EXPECT_TRUE(filePathHandler.doesExist());
    deleteAllFilesOnDirectory(directoryPathHandler.getPath());
}

}  // namespace alba
