#include <Common/PathHandler/AlbaLinuxPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace {
using PathHandler = AlbaLinuxPathHandler;
constexpr char SLASH_CHARACTER = static_cast<char>('\\');
string getAprgPath() { return APRG_DIR R"(\)"; }
string getAprgTestDirectory() { return APRG_DIR R"(\AprgCommon\FilesForTests\)"; }
string getAprgRootPath() { return getStringBeforeThisString(getAprgPath(), ":"); }

string fixPath(string_view const& path) {
    return getCorrectPathWithoutDoublePeriod<SLASH_CHARACTER>(
        getCorrectPathWithReplacedSlashCharacters<SLASH_CHARACTER>(path));
}
}  // namespace

TEST(AlbaLinuxPathHandlerTest, EmptyPathWorks) {
    PathHandler pathHandler("");
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Empty, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithOnlyDirectoryGivenWindowsStyleInput) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests\)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithOnlyDirectoryGivenJumbledSlashes) {
    PathHandler pathHandler(APRG_DIR R"(\////AprgCommon\\\\/FilesForTests\)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithOnlyDirectoryGivenJumbledSlashesWithDirectoryDoesNotExists) {
    PathHandler pathHandler(APRG_DIR R"(\////AprgCommon\\\\/AprgCommon/tst\DirectoryDoesNotExists\)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithOnlyDirectoryGivenWithNumbersAndSpecialCharacters) {
    PathHandler pathHandler(R"(/APRG12345/Aprg!@#$%Common/AprgCommon/tst/)");
    EXPECT_EQ(R"(/APRG12345/Aprg!@#$%Common/AprgCommon/tst/)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryAndFileGivenWithNumbersAndSpecialCharacters) {
    PathHandler pathHandler(R"(/APRG12345/Aprg!@#$%Common/AprgCommon/tst/zxcvbnm12345.txt)");
    EXPECT_EQ(R"(/APRG12345/Aprg!@#$%Common/AprgCommon/tst/)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.txt", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharacters) {
    PathHandler pathHandler(R"(/APRG12345/Aprg!@#$%Common/AprgCommon/tst/zxcvbnm12345.)");
    EXPECT_EQ(R"(/APRG12345/Aprg!@#$%Common/AprgCommon/tst/)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryAndFileExtensionOnlyGivenWithNumbersAndSpecialCharacters) {
    PathHandler pathHandler(R"(/APRG12345/Aprg!@#$%Common/AprgCommon/tst/.zxcvbnm12345)");
    EXPECT_EQ(R"(/APRG12345/Aprg!@#$%Common/AprgCommon/tst/)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(PathHandlerTest, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharactersTwoTimes) {
    PathHandler pathHandler(R"(/APRG12345/Aprg!@#$%Common/Aprg1111Common/tst/76543.txt)");
    EXPECT_EQ(R"(/APRG12345/Aprg!@#$%Common/Aprg1111Common/tst/)", pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(R"(e:/APRG12345/Aprg!@#$%Common/AprgCommon/tst/.zxcvbnm12345)");
    EXPECT_EQ(R"(e:/APRG12345/Aprg!@#$%Common/AprgCommon/tst/)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryAndFileDoublePeriodInPath) {
    PathHandler pathHandler(APRG_DIR R"(\../dir/file.txt)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\../dir/)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(APRG_DIR R"(\dir/../../file.txt)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\dir/../../)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(APRG_DIR R"(\dir/../dir2/dir3/../file.txt)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\dir2/)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(AlbaLinuxPathHandlerTest, FileSizeTestFileIsNotExisting) {
    PathHandler pathHandler("This path does not exist");

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_FALSE(pathHandler.isFoundInLocalSystem());
    EXPECT_DOUBLE_EQ(0, pathHandler.getFileSizeEstimate());
}

TEST(AlbaLinuxPathHandlerTest, FileSizeTestFileIsExisting) {
    PathHandler pathHandler(ALBA_COMMON_SIZE_TEST_FILE);

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());
    EXPECT_DOUBLE_EQ(5000, pathHandler.getFileSizeEstimate());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryAndFileActualLocalDirectory) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File1.log)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)"), pathHandler.getDirectory());
    EXPECT_EQ("File1.log", pathHandler.getFile());
    EXPECT_EQ("File1", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(APRG_DIR R"(\AprgCommon/FilesForTests/thisFileDoesNotExist.txt)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/)"), pathHandler.getDirectory());
    EXPECT_EQ("thisFileDoesNotExist.txt", pathHandler.getFile());
    EXPECT_EQ("thisFileDoesNotExist", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(APRG_DIR R"(\AprgCommon/FilesForTests)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(APRG_DIR R"(\AprgCommon/FilesForTests/)");
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryFindFileAndDirectoryOneDepth) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(5U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File5.avi)"), *(itFiles++));
    ASSERT_EQ(6U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR1/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR2/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR3/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR4/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR5/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR6/)"), *(itDirectories++));
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryFindFileAndDirectoryMultipleDepthTwo) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectory, 2);
    ASSERT_EQ(10U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR1/File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR2/File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR3/File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR4/File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR5/File5.avi)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File5.avi)"), *(itFiles++));
    ASSERT_EQ(7U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR1/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR2/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR3/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR4/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR5/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR6/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR6/SUBDIR1/)"), *(itDirectories++));
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryFindFileAndDirectoryUnlimitedDepth) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(11U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR1/File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR2/File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR3/File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR4/File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR5/File5.avi)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR6/SUBDIR1/File6.jpg)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File1.log)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File2.txt)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File4.mp3)"), *(itFiles++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File5.avi)"), *(itFiles++));
    ASSERT_EQ(7U, listOfDirectory.size());
    auto itDirectories = begin(listOfDirectory);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR1/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR2/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR3/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR4/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR5/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR6/)"), *(itDirectories++));
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR6/SUBDIR1/)"), *(itDirectories++));
}

TEST(AlbaLinuxPathHandlerTest, FullPathWithDirectoryFindFileAndDirectoryUnlimitedDepthWithWildCard) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.log", listOfFiles, listOfDirectory);
    ASSERT_EQ(1U, listOfFiles.size());
    auto itFiles = begin(listOfFiles);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/File1.log)"), *(itFiles++));
    ASSERT_EQ(0U, listOfDirectory.size());
}

TEST(AlbaLinuxPathHandlerTest, ReInputFileThatIsToBeDeletedActualLocalDirectory) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/FileToBeDeleted.log)");
    ofstream fileToBeDeleted(pathHandler.getFullPath());
    fileToBeDeleted.close();
    pathHandler.reInput();
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());

    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());
}

TEST(AlbaLinuxPathHandlerTest, FileIsCopiedToNewFileActualLocalDirectory) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/FileToBeCopied.log)");
    string const pathOfCopiedFile("CopiedFile.log");
    ofstream fileToBeDeleted(pathHandler.getFullPath());
    fileToBeDeleted.close();
    pathHandler.reInput();
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeCopied.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeCopied", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.copyToNewFile(pathHandler.getDirectory() + pathOfCopiedFile));

    PathHandler pathHandlerOfCopiedFile(pathHandler.getDirectory() + pathOfCopiedFile);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)"), pathHandlerOfCopiedFile.getDirectory());
    EXPECT_EQ("CopiedFile.log", pathHandlerOfCopiedFile.getFile());
    EXPECT_EQ("CopiedFile", pathHandlerOfCopiedFile.getFilenameOnly());
    EXPECT_EQ("log", pathHandlerOfCopiedFile.getExtension());
    EXPECT_EQ(PathType::File, pathHandlerOfCopiedFile.getPathType());
    EXPECT_TRUE(pathHandlerOfCopiedFile.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());
    EXPECT_TRUE(pathHandlerOfCopiedFile.deleteFile());
}

TEST(AlbaLinuxPathHandlerTest, ReInputFileThatIsToBeRenamedActualLocalDirectory) {
    PathHandler pathHandler(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/FileToBeRenamed.log)");
    ofstream fileToBeRenamed(pathHandler.getFullPath());
    fileToBeRenamed.close();
    pathHandler.reInput();
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeRenamed.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeRenamed", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameFile("RenamedFile.txt"));

    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/)"), pathHandler.getDirectory());
    EXPECT_EQ("RenamedFile.txt", pathHandler.getFile());
    EXPECT_EQ("RenamedFile", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());
}

TEST(AlbaLinuxPathHandlerTest, ReInputDirectoryThatIsToBeRenamedActualLocalDirectory) {
    string const pathOfDirectoryToBeRenamed(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR1)");

    PathHandler pathHandler(pathOfDirectoryToBeRenamed);
    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR1/)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("RenamedDirectory"));

    EXPECT_EQ(
        fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/RenamedDirectory/)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("DIR1"));

    EXPECT_EQ(fixPath(APRG_DIR R"(\AprgCommon/FilesForTests/DirectoryTest/DIR1/)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}

TEST(AlbaLinuxPathHandlerTest, SetCurrentDirectoryFromDetectedLocalPath) {
    PathHandler pathHandler(PathHandler::createPathHandlerForDetectedPath());

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());
}

}  // namespace alba
