#include <Common/Debug/AlbaDebug.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/PathHandler/AlbaLocalPathHandlerStd.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {

using LocalPath = AlbaLocalPathHandlerStd::LocalPath;
using SetOfLocalPaths = std::set<LocalPath>;
constexpr char SLASH_CHARACTER = static_cast<char>(path::preferred_separator);
string getAprgDirectory() { return APRG_DIR R"(\)"; }
LocalPath getAprgRootPath() { return getStringBeforeThisString(getAprgDirectory(), ":") + ":"; }

LocalPath convertToPath(LocalPath const path) {
    return getCorrectPathWithoutDoublePeriod<SLASH_CHARACTER>(
        getCorrectPathWithReplacedSlashCharacters<SLASH_CHARACTER>(path.string()));
}

}  // namespace

TEST(AlbaLocalPathHandlerStdTest, EmptyPathWorks) {
    AlbaLocalPathHandlerStd const pathHandler("");
    EXPECT_TRUE(pathHandler.getPath().empty());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithOnlyDirectoryGivenWindowsStyleInput) {
    AlbaLocalPathHandlerStd const pathHandler(getAprgDirectory() + R"(AprgCommon\FilesForTests\)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithOnlyDirectoryGivenJumbledSlashes) {
    AlbaLocalPathHandlerStd const pathHandler(getAprgDirectory() + R"(////AprgCommon\\\\\FilesForTests\)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithOnlyDirectoryGivenJumbledSlashesWithDirectoryDoesNotExists) {
    AlbaLocalPathHandlerStd const pathHandler(APRG_DIR R"(\////AprgCommon\\\\/AprgCommon/tst\DirectoryDoesNotExists\)");
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"),
        pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithOnlyDirectoryGivenWithNumbersAndSpecialCharacters) {
    AlbaLocalPathHandlerStd const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithDirectoryAndFileGivenWithNumbersAndSpecialCharacters) {
    AlbaLocalPathHandlerStd const pathHandler(
        R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)", pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.txt", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharacters) {
    AlbaLocalPathHandlerStd const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)", pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithDirectoryAndFileExtensionOnlyGivenWithNumbersAndSpecialCharacters) {
    AlbaLocalPathHandlerStd const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)", pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithDirectoryAndFileActualLocalDirectory) {
    AlbaLocalPathHandlerStd pathHandler(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("File1.log", pathHandler.getFile());
    EXPECT_EQ("File1", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    pathHandler.input(getAprgDirectory() + R"(AprgCommon\FilesForTests\thisFileDoesNotExist.txt)");
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\thisFileDoesNotExist.txt)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_EQ("thisFileDoesNotExist.txt", pathHandler.getFile());
    EXPECT_EQ("thisFileDoesNotExist", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_FALSE(pathHandler.doesExist());

    pathHandler.input(getAprgDirectory() + R"(AprgCommon\FilesForTests)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    pathHandler.input(getAprgDirectory() + R"(AprgCommon\FilesForTests\)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerStdTest, ReInputFileThatIsToBeDeletedActualLocalDirectory) {
    LocalPath const pathOfFileToBeDeleted(
        getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeDeleted.log)");
    ofstream fileToBeDeleted(pathOfFileToBeDeleted);
    fileToBeDeleted.close();

    AlbaLocalPathHandlerStd pathHandler(pathOfFileToBeDeleted);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeDeleted.log)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());

    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeDeleted.log)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_FALSE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerStdTest, FileIsCopiedToNewFileActualLocalDirectory) {
    LocalPath const pathOfFileToBeCopied(
        getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeCopied.log)");
    string const pathOfCopiedFile("CopiedFile.log");
    ofstream fileToBeCopied(pathOfFileToBeCopied);
    fileToBeCopied.close();

    AlbaLocalPathHandlerStd pathHandler(pathOfFileToBeCopied);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeCopied.log)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeCopied.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeCopied", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.copyFileToAndIsSuccessful(pathHandler.getDirectory() / pathOfCopiedFile));

    AlbaLocalPathHandlerStd pathHandlerOfCopiedFile(pathHandler.getDirectory() / pathOfCopiedFile);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\CopiedFile.log)"),
        pathHandlerOfCopiedFile.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandlerOfCopiedFile.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"),
        pathHandlerOfCopiedFile.getDirectory());
    EXPECT_EQ("CopiedFile.log", pathHandlerOfCopiedFile.getFile());
    EXPECT_EQ("CopiedFile", pathHandlerOfCopiedFile.getFilenameOnly());
    EXPECT_EQ("log", pathHandlerOfCopiedFile.getExtension());
    EXPECT_TRUE(pathHandlerOfCopiedFile.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());
    EXPECT_TRUE(pathHandlerOfCopiedFile.deleteFileAndIsSuccessful());
}

TEST(AlbaLocalPathHandlerStdTest, ReInputFileThatIsToBeRenamedActualLocalDirectory) {
    LocalPath const pathOfFileToBeRenamed(
        getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeRenamed.log)");
    ofstream fileToBeDeleted(pathOfFileToBeRenamed);
    fileToBeDeleted.close();

    AlbaLocalPathHandlerStd pathHandler(pathOfFileToBeRenamed);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeRenamed.log)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeRenamed.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeRenamed", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameFileAndIsSuccessful("RenamedFile.txt"));

    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\RenamedFile.txt)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("RenamedFile.txt", pathHandler.getFile());
    EXPECT_EQ("RenamedFile", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());
}

TEST(AlbaLocalPathHandlerStdTest, ReInputDirectoryThatIsToBeRenamedActualLocalDirectory) {
    LocalPath const pathOfDirectoryToBeRenamed(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1)");

    AlbaLocalPathHandlerStd pathHandler(pathOfDirectoryToBeRenamed);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"),
        pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameDirectoryAndIsSuccessful("RenamedDirectory"));

    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\RenamedDirectory\)"),
        pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\RenamedDirectory\)"),
        pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameDirectoryAndIsSuccessful("DIR1"));

    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"),
        pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

TEST(
    AlbaLocalPathHandlerStdTest,
    FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharactersTwoTimes) {
    AlbaLocalPathHandlerStd pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)", pathHandler.getPath());
    EXPECT_EQ("e:", pathHandler.getRoot());
    EXPECT_EQ(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithDirectoryAndFileDoublePeriodInPath) {
    AlbaLocalPathHandlerStd pathHandler(getAprgDirectory() + R"(..\dir\file.txt)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(..\dir\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(..\dir\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(getAprgDirectory() + R"(dir\..\..\file.txt)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(..\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(dir\..\..\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(getAprgDirectory() + R"(dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(dir2\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(dir2\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerStdTest, FileSizeTestFileIsNotExisting) {
    AlbaLocalPathHandlerStd pathHandler("This path does not exist");

    EXPECT_EQ("This path does not exist", pathHandler.getPath());
    ASSERT_FALSE(pathHandler.doesExist());
    EXPECT_EQ(0U, pathHandler.getFileSize());
}

TEST(AlbaLocalPathHandlerStdTest, FileSizeTestFileIsExisting) {
    AlbaLocalPathHandlerStd pathHandler(ALBA_COMMON_SIZE_TEST_FILE);

    EXPECT_EQ(ALBA_COMMON_SIZE_TEST_FILE, pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());
    EXPECT_EQ(5000U, pathHandler.getFileSize());
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithDirectoryFindFileAndDirectoryOneDepth) {
    AlbaLocalPathHandlerStd const pathHandler(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());

    SetOfLocalPaths listOfDirectory;
    SetOfLocalPaths listOfFiles;
    pathHandler.findFilesAndDirectoriesOneDepth(
        [&listOfDirectory](LocalPath const& directoryPath) { listOfDirectory.emplace(directoryPath); },
        [&listOfFiles](LocalPath const& filePath) { listOfFiles.emplace(filePath); });
    ASSERT_EQ(5U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(6U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\)"), *(itDirectories++));
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithDirectoryFindFileAndDirectoryMultipleDepthTwo) {
    AlbaLocalPathHandlerStd const pathHandler(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());

    SetOfLocalPaths listOfDirectory;
    SetOfLocalPaths listOfFiles;
    pathHandler.findFilesAndDirectoriesMultipleDepth(
        2, [&listOfDirectory](LocalPath const& directoryPath) { listOfDirectory.emplace(directoryPath); },
        [&listOfFiles](LocalPath const& filePath) { listOfFiles.emplace(filePath); });
    ASSERT_EQ(10U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\File1.log)"), *(itFiles++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\File3)"), *(itFiles++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\File5.avi)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(7U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)"),
        *(itDirectories++));
}

TEST(AlbaLocalPathHandlerStdTest, FullPathWithDirectoryFindFileAndDirectoryUnlimitedDepth) {
    AlbaLocalPathHandlerStd const pathHandler(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());

    SetOfLocalPaths listOfDirectory;
    SetOfLocalPaths listOfFiles;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [&listOfDirectory](LocalPath const& directoryPath) { listOfDirectory.emplace(directoryPath); },
        [&listOfFiles](LocalPath const& filePath) { listOfFiles.emplace(filePath); });
    ASSERT_EQ(11U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\File1.log)"), *(itFiles++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\File3)"), *(itFiles++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\File5.avi)"), *(itFiles++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\SUBDIR1\File6.jpg)"),
        *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(7U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\)"), *(itDirectories++));
    EXPECT_EQ(
        convertToPath(getAprgDirectory() + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)"),
        *(itDirectories++));
}

TEST(AlbaLocalPathHandlerStdTest, SetCurrentDirectoryFromDetectedLocalPath) {
    AlbaLocalPathHandlerStd const pathHandler(AlbaLocalPathHandlerStd::createPathHandlerForDetectedPath());

    EXPECT_FALSE(pathHandler.getPath().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

}  // namespace alba
