#include <Common/PathHandler/AlbaWindowsPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace {
using PathHandler = AlbaWindowsPathHandler;
constexpr char SLASH_CHARACTER = static_cast<char>('\\');
string getAprgPath() { return APRG_DIR R"(\)"; }
string getAprgTestDirectory() { return APRG_DIR R"(\AprgCommon\FilesForTests\)"; }
string getAprgRootPath() { return getStringBeforeThisString(getAprgPath(), ":"); }

string fixPath(string_view const& path) {
    return getCorrectPathWithoutDoublePeriod<SLASH_CHARACTER>(
        getCorrectPathWithReplacedSlashCharacters<SLASH_CHARACTER>(path));
}
}  // namespace

TEST(AlbaWindowsPathHandler, EmptyPathWorks) {
    PathHandler const pathHandler("");
    EXPECT_TRUE(pathHandler.getDriveOrRoot().empty());
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Empty, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithOnlyDirectoryGivenWindowsStyleInput) {
    PathHandler const pathHandler(getAprgTestDirectory());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithOnlyDirectoryGivenJumbledSlashes) {
    PathHandler const pathHandler(getAprgPath() + R"(////AprgCommon\\\\\FilesForTests\)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithOnlyDirectoryGivenJumbledSlashesWithDirectoryDoesNotExists) {
    PathHandler const pathHandler(APRG_DIR R"(\////AprgCommon\\\\/AprgCommon/tst\DirectoryDoesNotExists\)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(
        fixPath(getAprgPath() + R"(AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithOnlyDirectoryGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryAndFileGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.txt", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryAndFileExtensionOnlyGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(PathHandler, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharactersTwoTimes) {
    PathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ("E", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryAndFileDoublePeriodInPath) {
    PathHandler pathHandler(getAprgPath() + R"(..\dir\file.txt)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(..\dir\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(getAprgPath() + R"(dir\..\..\file.txt)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir\..\..\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(getAprgPath() + R"(dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir2\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryAndFileActualLocalDirectory) {
    PathHandler pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("File1.log", pathHandler.getFile());
    EXPECT_EQ("File1", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(getAprgTestDirectory() + R"(\thisFileDoesNotExist.txt)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_EQ("thisFileDoesNotExist.txt", pathHandler.getFile());
    EXPECT_EQ("thisFileDoesNotExist", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(getAprgPath() + R"(AprgCommon\FilesForTests)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(getAprgPath() + R"(AprgCommon\FilesForTests\)");
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}

TEST(AlbaWindowsPathHandler, ReInputFileThatIsToBeDeletedActualLocalDirectory) {
    string const pathOfFileToBeDeleted(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeDeleted.log)");
    ofstream fileToBeDeleted(pathOfFileToBeDeleted);
    fileToBeDeleted.close();

    PathHandler pathHandler(pathOfFileToBeDeleted);
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());

    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());
}

TEST(AlbaWindowsPathHandler, FileIsCopiedToNewFileActualLocalDirectory) {
    string const pathOfFileToBeCopied(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeCopied.log)");
    string const pathOfCopiedFile("CopiedFile.log");
    ofstream fileToBeCopied(pathOfFileToBeCopied);
    fileToBeCopied.close();

    PathHandler pathHandler(pathOfFileToBeCopied);
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeCopied.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeCopied", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.copyToNewFile(pathHandler.getDirectory() + pathOfCopiedFile));

    PathHandler pathHandlerOfCopiedFile(pathHandler.getDirectory() + pathOfCopiedFile);
    EXPECT_EQ(getAprgRootPath(), pathHandlerOfCopiedFile.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandlerOfCopiedFile.getDirectory());
    EXPECT_EQ("CopiedFile.log", pathHandlerOfCopiedFile.getFile());
    EXPECT_EQ("CopiedFile", pathHandlerOfCopiedFile.getFilenameOnly());
    EXPECT_EQ("log", pathHandlerOfCopiedFile.getExtension());
    EXPECT_EQ(PathType::File, pathHandlerOfCopiedFile.getPathType());
    EXPECT_TRUE(pathHandlerOfCopiedFile.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());
    EXPECT_TRUE(pathHandlerOfCopiedFile.deleteFile());
}

TEST(AlbaWindowsPathHandler, ReInputFileThatIsToBeRenamedActualLocalDirectory) {
    string const pathOfFileToBeRenamed(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeRenamed.log)");
    ofstream fileToBeDeleted(pathOfFileToBeRenamed);
    fileToBeDeleted.close();

    PathHandler pathHandler(pathOfFileToBeRenamed);
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeRenamed.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeRenamed", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameFile("RenamedFile.txt"));

    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("RenamedFile.txt", pathHandler.getFile());
    EXPECT_EQ("RenamedFile", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());
}

TEST(AlbaWindowsPathHandler, ReInputDirectoryThatIsToBeRenamedActualLocalDirectory) {
    string const pathOfDirectoryToBeRenamed(getAprgTestDirectory() + R"(\DirectoryTest\DIR1)");

    PathHandler pathHandler(pathOfDirectoryToBeRenamed);
    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("RenamedDirectory"));

    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\RenamedDirectory\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("DIR1"));

    EXPECT_EQ(getAprgRootPath(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryFindFileAndDirectoryOneDepth) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectory);
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

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryFindFileAndDirectoryMultipleDepthTwo) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectory, 2);
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

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryFindFileAndDirectoryUnlimitedDepth) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectory);
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

TEST(AlbaWindowsPathHandler, FullPathWithDirectoryFindFileAndDirectoryUnlimitedDepthWithWildCard) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.log", listOfFiles, listOfDirectory);
    ASSERT_EQ(1U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)"), *(itFiles++));
    ASSERT_EQ(0U, listOfDirectory.size());
}

TEST(AlbaWindowsPathHandler, FileSizeTestFileIsNotExisting) {
    PathHandler pathHandler("This path does not exist");

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_FALSE(pathHandler.isFoundInLocalSystem());
    EXPECT_DOUBLE_EQ(0, pathHandler.getFileSizeEstimate());
}

TEST(AlbaWindowsPathHandler, FileSizeTestFileIsExisting) {
    PathHandler pathHandler(ALBA_COMMON_SIZE_TEST_FILE);

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());
    EXPECT_DOUBLE_EQ(5000, pathHandler.getFileSizeEstimate());
}

TEST(AlbaWindowsPathHandler, SetCurrentDirectoryFromDetectedLocalPath) {
    PathHandler const pathHandler(PathHandler::createPathHandlerForDetectedPath());

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());
}

}  // namespace alba
