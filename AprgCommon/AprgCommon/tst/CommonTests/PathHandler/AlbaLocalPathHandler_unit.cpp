#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimeHelper.hpp>
#include <CommonTests/DirectoryConstants.hpp>
#include <CommonTestsUtilities/File/FileUtilities.hpp>
#include <CommonTestsUtilities/Time/DateTimeUtilities.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {

using PathHandler = AlbaLocalPathHandler;
using LocalPath = PathHandler::LocalPath;
using SetOfLocalPaths = std::set<LocalPath>;
constexpr char SLASH_CHARACTER = static_cast<char>(path::preferred_separator);
string getAprgPath() { return APRG_DIR R"(\)"; }
string getAprgTestDirectory() { return APRG_DIR R"(\AprgCommon\FilesForTests\)"; }

LocalPath getAprgRootPath() {
    string const aprgPath(getAprgPath());
    auto colonIndex = aprgPath.find_first_of(':', 0);
    if (colonIndex != string::npos) {
        return aprgPath.substr(0, colonIndex + 1);
    }
    return {};
}

LocalPath fixPath(LocalPath const& path) {
    return getCorrectPathWithoutDoublePeriod<SLASH_CHARACTER>(
        getCorrectPathWithReplacedSlashCharacters<SLASH_CHARACTER>(path.string()));
}

}  // namespace

TEST(AlbaLocalPathHandlerTest, GetLastModifiedDateTimeWorks) {
    PathHandler const pathHandler(APRG_COMMON_TEST_FILE_TO_WRITE);
    createEmptyFile(pathHandler.getPath());

    AlbaDateTime const lastModifiedTime(pathHandler.getLastModifiedDateTime());
    sleepFor(1);
    AlbaDateTime const currentTime(getCurrentDateTime());

    EXPECT_TRUE(isDifferenceAcceptable(lastModifiedTime, currentTime));
}

TEST(AlbaLocalPathHandlerTest, EmptyPathWorks) {
    PathHandler const pathHandler("");
    EXPECT_TRUE(pathHandler.getPath().empty());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_TRUE(pathHandler.getDirectoryName().empty());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerTest, FileIsCopiedToNewFileActualLocalDirectory) {
    LocalPath const pathOfFileToBeCopied(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeCopied.log)");
    string const pathOfCopiedFile("CopiedFile.log");
    createEmptyFile(fixPath(pathOfFileToBeCopied));

    PathHandler const pathHandler(pathOfFileToBeCopied);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeCopied.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DirectoryTest)"), pathHandler.getDirectoryName());
    EXPECT_EQ("FileToBeCopied.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeCopied", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.copyFileToAndIsSuccessful(pathHandler.getDirectory() / pathOfCopiedFile));

    PathHandler const pathHandlerOfCopiedFile(pathHandler.getDirectory() / pathOfCopiedFile);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\CopiedFile.log)"), pathHandlerOfCopiedFile.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandlerOfCopiedFile.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandlerOfCopiedFile.getDirectory());
    EXPECT_EQ((R"(DirectoryTest)"), pathHandlerOfCopiedFile.getDirectoryName());
    EXPECT_EQ("CopiedFile.log", pathHandlerOfCopiedFile.getFile());
    EXPECT_EQ("CopiedFile", pathHandlerOfCopiedFile.getFilenameOnly());
    EXPECT_EQ("log", pathHandlerOfCopiedFile.getExtension());
    EXPECT_TRUE(pathHandlerOfCopiedFile.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());
    EXPECT_TRUE(pathHandlerOfCopiedFile.deleteFileAndIsSuccessful());
}

TEST(AlbaLocalPathHandlerTest, ReInputFileThatIsToBeRenamedActualLocalDirectory) {
    LocalPath const pathOfFileToBeRenamed(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeRenamed.log)");
    createEmptyFile(fixPath(pathOfFileToBeRenamed));

    PathHandler pathHandler(pathOfFileToBeRenamed);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeRenamed.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DirectoryTest)"), pathHandler.getDirectoryName());
    EXPECT_EQ("FileToBeRenamed.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeRenamed", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameFileAndIsSuccessful("RenamedFile.txt"));

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\RenamedFile.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DirectoryTest)"), pathHandler.getDirectoryName());
    EXPECT_EQ("RenamedFile.txt", pathHandler.getFile());
    EXPECT_EQ("RenamedFile", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());
}

TEST(AlbaLocalPathHandlerTest, ReInputFileThatIsToBeDeletedActualLocalDirectory) {
    LocalPath const pathOfFileToBeDeleted(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeDeleted.log)"));
    createEmptyFile(fixPath(pathOfFileToBeDeleted));

    PathHandler const pathHandler(pathOfFileToBeDeleted);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeDeleted.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DirectoryTest)"), pathHandler.getDirectoryName());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeDeleted.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DirectoryTest)"), pathHandler.getDirectoryName());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_FALSE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithDirectoryAndFileActualLocalDirectory) {
    PathHandler pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)");
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DirectoryTest)"), pathHandler.getDirectoryName());
    EXPECT_EQ("File1.log", pathHandler.getFile());
    EXPECT_EQ("File1", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    pathHandler.input(getAprgTestDirectory() + R"(\thisFileDoesNotExist.txt)");
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\thisFileDoesNotExist.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_EQ((R"(FilesForTests)"), pathHandler.getDirectoryName());
    EXPECT_EQ("thisFileDoesNotExist.txt", pathHandler.getFile());
    EXPECT_EQ("thisFileDoesNotExist", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_FALSE(pathHandler.doesExist());

    pathHandler.input(getAprgPath() + R"(AprgCommon\FilesForTests)");
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_EQ((R"(FilesForTests)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    pathHandler.input(getAprgPath() + R"(AprgCommon\FilesForTests\)");
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_EQ((R"(FilesForTests)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerTest, ReInputDirectoryThatIsToBeRenamedActualLocalDirectory) {
    LocalPath const pathOfDirectoryToBeRenamed(getAprgTestDirectory() + R"(\DirectoryTest\DIR1)");

    PathHandler pathHandler(pathOfDirectoryToBeRenamed);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DIR1)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameDirectoryAndIsSuccessful("RenamedDirectory"));

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\RenamedDirectory\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\RenamedDirectory\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(RenamedDirectory)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameDirectoryAndIsSuccessful("DIR1"));

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DIR1)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

TEST(
    AlbaLocalPathHandlerTest, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharactersTwoTimes) {
    PathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(tst)"), pathHandler.getDirectoryName());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(R"(e\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(fixPath(R"(e\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(e\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(tst)"), pathHandler.getDirectoryName());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithDirectoryAndFileDoublePeriodInPath) {
    PathHandler pathHandler(getAprgPath() + R"(..\dir\file.txt)");
    EXPECT_EQ(fixPath(getAprgPath() + R"(..\dir\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(..\dir\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(dir)"), pathHandler.getDirectoryName());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(getAprgPath() + R"(dir1\dir2\dir3\..\..\file.txt)");
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir1\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir1\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(dir1)"), pathHandler.getDirectoryName());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(getAprgPath() + R"(dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir2\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir2\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(dir2)"), pathHandler.getDirectoryName());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithOnlyDirectoryGivenWindowsStyleInput) {
    PathHandler const pathHandler(getAprgTestDirectory());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_EQ((R"(FilesForTests)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithOnlyDirectoryGivenJumbledSlashes) {
    PathHandler const pathHandler(getAprgPath() + R"(////AprgCommon\\\\\FilesForTests\)");
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_EQ((R"(FilesForTests)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithOnlyDirectoryGivenJumbledSlashesWithDirectoryDoesNotExists) {
    PathHandler const pathHandler(APRG_DIR R"(\////AprgCommon\\\\/AprgCommon/tst\DirectoryDoesNotExists\)");
    EXPECT_EQ(fixPath(getAprgPath() + R"(AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        fixPath(getAprgPath() + R"(AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(DirectoryDoesNotExists)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithOnlyDirectoryGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(tst)"), pathHandler.getDirectoryName());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithDirectoryAndFileGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ(
        fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(tst)"), pathHandler.getDirectoryName());
    EXPECT_EQ("zxcvbnm12345.txt", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(tst)"), pathHandler.getDirectoryName());
    EXPECT_EQ("zxcvbnm12345.", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithDirectoryAndFileExtensionOnlyGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ((R"(tst)"), pathHandler.getDirectoryName());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerTest, ClearWorks) {
    PathHandler pathHandler(getAprgTestDirectory());

    pathHandler.clear();

    EXPECT_TRUE(pathHandler.getPath().empty());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerTest, FileSizeTestFileIsNotExisting) {
    PathHandler const pathHandler("This path does not exist");

    EXPECT_EQ("This path does not exist", pathHandler.getPath());
    ASSERT_FALSE(pathHandler.doesExist());
    EXPECT_EQ(0U, pathHandler.getFileSize());
}

TEST(AlbaLocalPathHandlerTest, FileSizeTestFileIsExisting) {
    PathHandler const pathHandler(ALBA_COMMON_SIZE_TEST_FILE);

    EXPECT_EQ(fixPath(ALBA_COMMON_SIZE_TEST_FILE), pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());
    EXPECT_EQ(5000U, pathHandler.getFileSize());
}

TEST(AlbaLocalPathHandlerTest, FullPathWithDirectoryFindFileAndDirectoryOneDepth) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\)");
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());

    SetOfLocalPaths listOfDirectory;
    SetOfLocalPaths listOfFiles;
    pathHandler.findFilesAndDirectoriesOneDepth(
        [&listOfDirectory](LocalPath const& directoryPath) { listOfDirectory.emplace(directoryPath); },
        [&listOfFiles](LocalPath const& filePath) { listOfFiles.emplace(filePath); });
    ASSERT_EQ(5U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(6U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR6\)"), *(itDirectories++));
}

TEST(AlbaLocalPathHandlerTest, FullPathWithDirectoryFindFileAndDirectoryMultipleDepthTwo) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\)");
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());

    SetOfLocalPaths listOfDirectory;
    SetOfLocalPaths listOfFiles;
    pathHandler.findFilesAndDirectoriesMultipleDepth(
        2, [&listOfDirectory](LocalPath const& directoryPath) { listOfDirectory.emplace(directoryPath); },
        [&listOfFiles](LocalPath const& filePath) { listOfFiles.emplace(filePath); });
    ASSERT_EQ(10U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR2\File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR3\File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR4\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR5\File5.avi)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(7U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR6\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR6\SUBDIR1\)"), *(itDirectories++));
}

TEST(AlbaLocalPathHandlerTest, FullPathWithDirectoryFindFileAndDirectoryUnlimitedDepth) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\)");
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());

    SetOfLocalPaths listOfDirectory;
    SetOfLocalPaths listOfFiles;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [&listOfDirectory](LocalPath const& directoryPath) { listOfDirectory.emplace(directoryPath); },
        [&listOfFiles](LocalPath const& filePath) { listOfFiles.emplace(filePath); });
    ASSERT_EQ(11U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR2\File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR3\File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR4\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR5\File5.avi)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR6\SUBDIR1\File6.jpg)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(7U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR6\)"), *(itDirectories++));
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR6\SUBDIR1\)"), *(itDirectories++));
}

TEST(AlbaLocalPathHandlerTest, CreatePathHandlerForDetectedPathWorks) {
    PathHandler const pathHandler(PathHandler::createPathHandlerForDetectedPath());

    EXPECT_FALSE(pathHandler.getPath().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerTest, CopyDirectoryAndIsSuccessfulWorks) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\CopyDirectory\)");
    EXPECT_TRUE(
        PathHandler(getAprgTestDirectory() + R"(\CopyDirectory\DIR1\DIR2\DIR3\)").createDirectoriesAndIsSuccessful());
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\CopyDirectory\FILE0.txt)"));
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\CopyDirectory\DIR1\FILE1.txt)"));
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\CopyDirectory\DIR1\DIR2\FILE2.txt)"));
    ASSERT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CopyDirectory\)").isExistingDirectory());
    PathHandler const destinationHandler(getAprgTestDirectory() + R"(\CopiedDirectory\)");

    EXPECT_TRUE(pathHandler.copyDirectoryToAndIsSuccessful(destinationHandler.getPath()));

    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CopiedDirectory\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CopiedDirectory\DIR1\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CopiedDirectory\DIR1\DIR2\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CopiedDirectory\DIR1\DIR2\DIR3\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CopiedDirectory\FILE0.txt)").isExistingFile());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CopiedDirectory\DIR1\FILE1.txt)").isExistingFile());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CopiedDirectory\DIR1\DIR2\FILE2.txt)").isExistingFile());

    EXPECT_TRUE(pathHandler.deleteDirectoryAndIsSuccessful());
    EXPECT_TRUE(destinationHandler.deleteDirectoryAndIsSuccessful());
}

TEST(AlbaLocalPathHandlerTest, MoveUpADirectoryWorks) {
    PathHandler pathHandler(getAprgTestDirectory() + R"(DIR1\DIR2\DIR3\)");

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DIR1\DIR2\DIR3\)"), pathHandler.getPath());
    pathHandler.moveUpADirectory();
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DIR1\DIR2\)"), pathHandler.getPath());
    pathHandler.moveUpADirectory();
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DIR1\)"), pathHandler.getPath());
    pathHandler.moveUpADirectory();
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
}

TEST(AlbaLocalPathHandlerTest, GetRelativePathFromWorks) {
    PathHandler const pathHandler(getAprgTestDirectory());

    EXPECT_EQ(fixPath(""), pathHandler.getRelativePathFrom(""));
    EXPECT_EQ(fixPath(R"(AprgCommon\FilesForTests)"), pathHandler.getRelativePathFrom(fixPath(getAprgPath())));
    EXPECT_EQ(fixPath(R"(.)"), pathHandler.getRelativePathFrom(fixPath(getAprgTestDirectory())));
    EXPECT_EQ(fixPath(R"(..\..)"), pathHandler.getRelativePathFrom(fixPath(APRG_COMMON_EMPTY_TEST_FILE)));
    EXPECT_EQ(fixPath(""), pathHandler.getRelativePathFrom(fixPath("a/b")));
}

TEST(AlbaLocalPathHandlerTest, GetRelativePathToWorks) {
    PathHandler const pathHandler(getAprgTestDirectory());

    EXPECT_EQ(fixPath(""), pathHandler.getRelativePathTo(""));
    EXPECT_EQ(fixPath(R"(..\..)"), pathHandler.getRelativePathTo(fixPath(getAprgPath())));
    EXPECT_EQ(fixPath(R"(.)"), pathHandler.getRelativePathTo(fixPath(getAprgTestDirectory())));
    EXPECT_EQ(
        fixPath(R"(FileReaderTest\EmptyFile.txt)"),
        pathHandler.getRelativePathTo(fixPath(APRG_COMMON_EMPTY_TEST_FILE)));
    EXPECT_EQ(fixPath(""), pathHandler.getRelativePathTo(fixPath("a/b")));
}

TEST(AlbaLocalPathHandlerTest, GetProximatePathFromWorks) {
    PathHandler const pathHandler(getAprgTestDirectory());

    EXPECT_EQ(fixPath(getAprgPath() + R"(AprgCommon\FilesForTests)"), pathHandler.getProximatePathFrom(""));
    EXPECT_EQ(fixPath(R"(AprgCommon\FilesForTests)"), pathHandler.getProximatePathFrom(fixPath(getAprgPath())));
    EXPECT_EQ(fixPath(R"(.)"), pathHandler.getProximatePathFrom(fixPath(getAprgTestDirectory())));
    EXPECT_EQ(fixPath(R"(..\..)"), pathHandler.getProximatePathFrom(fixPath(APRG_COMMON_EMPTY_TEST_FILE)));
    // EXPECT_EQ(fixPath(getAprgPath() + R"(AprgCommon\FilesForTests)"),
    // pathHandler.getProximatePathFrom(fixPath("a/b")));
}

TEST(AlbaLocalPathHandlerTest, GetProximatePathToWorks) {
    PathHandler const pathHandler(getAprgTestDirectory());

    EXPECT_EQ(fixPath(""), pathHandler.getProximatePathTo(""));
    EXPECT_EQ(fixPath(R"(..\..)"), pathHandler.getProximatePathTo(fixPath(getAprgPath())));
    EXPECT_EQ(fixPath(R"(.)"), pathHandler.getProximatePathTo(fixPath(getAprgTestDirectory())));
    EXPECT_EQ(
        fixPath(R"(FileReaderTest\EmptyFile.txt)"),
        pathHandler.getProximatePathTo(fixPath(APRG_COMMON_EMPTY_TEST_FILE)));
    EXPECT_EQ(fixPath(R"(a\b)"), pathHandler.getProximatePathTo(fixPath("a/b")));
}

TEST(AlbaLocalPathHandlerTest, DoesExistWorks) {
    EXPECT_FALSE(PathHandler("").doesExist());
    EXPECT_TRUE(PathHandler(getAprgPath()).doesExist());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory()).doesExist());
    EXPECT_TRUE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).doesExist());
}

TEST(AlbaLocalPathHandlerTest, CreateDirectoriesAndIsSuccessfulWorks) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\DIR2\DIR3\File)");
    ASSERT_FALSE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").isExistingDirectory());

    EXPECT_TRUE(pathHandler.createDirectoriesAndIsSuccessful());

    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\DIR2\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\DIR2\DIR3\)").isExistingDirectory());
    EXPECT_FALSE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\DIR2\DIR3\File)").doesExist());

    ASSERT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").deleteDirectoryAndIsSuccessful());
    EXPECT_FALSE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").isExistingDirectory());
}

TEST(AlbaLocalPathHandlerTest, IsExistingDirectoryWorks) {
    EXPECT_FALSE(PathHandler("").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgPath()).isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory()).isExistingDirectory());
    EXPECT_FALSE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).isExistingDirectory());
}

TEST(AlbaLocalPathHandlerTest, DeleteAllDirectoryContentsAndIsSuccessfulWorks) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DeleteContents\)");
    EXPECT_TRUE(
        PathHandler(getAprgTestDirectory() + R"(\DeleteContents\DIR1\DIR2\DIR3\)").createDirectoriesAndIsSuccessful());
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\DeleteContents\FILE0.txt)").string());
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\DeleteContents\DIR1\FILE1.txt)").string());
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\DeleteContents\DIR1\DIR2\FILE2.txt)").string());
    ASSERT_TRUE(PathHandler(getAprgTestDirectory() + R"(\DeleteContents\)").isExistingDirectory());

    EXPECT_TRUE(pathHandler.deleteAllDirectoryContentsAndIsSuccessful());

    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\DeleteContents\)").isExistingDirectory());
    int numberOfItems = 0;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [&](LocalPath const&) { ++numberOfItems; }, [&](LocalPath const&) { ++numberOfItems; });
    EXPECT_EQ(0, numberOfItems);

    EXPECT_TRUE(pathHandler.deleteDirectoryAndIsSuccessful());
}

TEST(AlbaLocalPathHandlerTest, DeleteDirectoryAndIsSuccessfulWorks) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DeleteDirectory\)");
    EXPECT_TRUE(
        PathHandler(getAprgTestDirectory() + R"(\DeleteDirectory\DIR1\DIR2\DIR3\)").createDirectoriesAndIsSuccessful());
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\DeleteDirectory\FILE0.txt)"));
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\DeleteDirectory\DIR1\FILE1.txt)"));
    createEmptyFile(fixPath(getAprgTestDirectory() + R"(\DeleteDirectory\DIR1\DIR2\FILE2.txt)"));
    ASSERT_TRUE(PathHandler(getAprgTestDirectory() + R"(\DeleteDirectory\)").isExistingDirectory());

    EXPECT_TRUE(pathHandler.deleteDirectoryAndIsSuccessful());

    EXPECT_FALSE(PathHandler(getAprgTestDirectory() + R"(\DeleteDirectory\)").isExistingDirectory());
}

TEST(AlbaLocalPathHandlerTest, IsExistingFileWorks) {
    EXPECT_FALSE(PathHandler("").isExistingFile());
    EXPECT_FALSE(PathHandler(getAprgPath()).isExistingFile());
    EXPECT_FALSE(PathHandler(getAprgTestDirectory()).isExistingFile());
    EXPECT_TRUE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).isExistingFile());
}

TEST(AlbaLocalPathHandlerTest, IsRelativePathWorks) {
    EXPECT_TRUE(PathHandler("").isRelativePath());
    EXPECT_FALSE(PathHandler(getAprgPath()).isRelativePath());
    EXPECT_FALSE(PathHandler(getAprgTestDirectory()).isRelativePath());
    EXPECT_FALSE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).isRelativePath());
    EXPECT_TRUE(PathHandler("a/b").isRelativePath());
}

TEST(AlbaLocalPathHandlerTest, IsAbsolutePathWorks) {
    EXPECT_FALSE(PathHandler("").isAbsolutePath());
    EXPECT_TRUE(PathHandler(getAprgPath()).isAbsolutePath());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory()).isAbsolutePath());
    EXPECT_TRUE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).isAbsolutePath());
    EXPECT_FALSE(PathHandler("a/b").isAbsolutePath());
}

}  // namespace alba
