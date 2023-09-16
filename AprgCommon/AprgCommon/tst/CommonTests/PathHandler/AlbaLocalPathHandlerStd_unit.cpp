#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/PathHandler/AlbaLocalPathHandlerStd.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimeHelper.hpp>
#include <CommonTests/DirectoryConstants.hpp>
#include <CommonTestsUtilities/File/FileUtilities.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {
using PathHandler = AlbaLocalPathHandlerStd;
using LocalPath = PathHandler::LocalPath;
using SetOfLocalPaths = std::set<LocalPath>;
constexpr char SLASH_CHARACTER = static_cast<char>(path::preferred_separator);
string getAprgPath() { return APRG_DIR R"(\)"; }
string getAprgTestDirectory() { return APRG_DIR R"(\AprgCommon\FilesForTests\)"; }
LocalPath getAprgRootPath() {
    string aprgPath(getAprgPath());
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

TEST(AlbaLocalPathHandlerStd, GetLastModifiedDateTimeWorks) {
#if !defined(_MSC_VER)
    PathHandler const pathHandler(APRG_COMMON_TEST_FILE_TO_WRITE);
    createEmptyFile(pathHandler.getPath().string());

    AlbaDateTime lastModifiedTime(pathHandler.getLastModifiedDateTime());

    AlbaDateTime currentTime(getCurrentDateTime());
    AlbaDateTime difference(currentTime - lastModifiedTime);
    AlbaDateTime allowableDifference(0, 0, 0, 0, 1, 0, 0);  // 1 minute
    EXPECT_LT(difference, allowableDifference);
#endif
}

TEST(AlbaLocalPathHandlerStd, EmptyPathWorks) {
    PathHandler const pathHandler("");
    EXPECT_TRUE(pathHandler.getPath().empty());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStd, ClearWorks) {
    PathHandler pathHandler(getAprgTestDirectory());

    pathHandler.clear();

    EXPECT_TRUE(pathHandler.getPath().empty());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithOnlyDirectoryGivenWindowsStyleInput) {
    PathHandler pathHandler(getAprgTestDirectory());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithOnlyDirectoryGivenJumbledSlashes) {
    PathHandler const pathHandler(getAprgPath() + R"(////AprgCommon\\\\\FilesForTests\)");
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithOnlyDirectoryGivenJumbledSlashesWithDirectoryDoesNotExists) {
    PathHandler const pathHandler(APRG_DIR R"(\////AprgCommon\\\\/AprgCommon/tst\DirectoryDoesNotExists\)");
    EXPECT_EQ(fixPath(getAprgPath() + R"(AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(
        fixPath(getAprgPath() + R"(AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithOnlyDirectoryGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryAndFileGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ(
        fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.txt", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryAndFileExtensionOnlyGivenWithNumbersAndSpecialCharacters) {
    PathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryAndFileActualLocalDirectory) {
    PathHandler pathHandler(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)");
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\File1.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("File1.log", pathHandler.getFile());
    EXPECT_EQ("File1", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    pathHandler.input(getAprgTestDirectory() + R"(\thisFileDoesNotExist.txt)");
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\thisFileDoesNotExist.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_EQ("thisFileDoesNotExist.txt", pathHandler.getFile());
    EXPECT_EQ("thisFileDoesNotExist", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_FALSE(pathHandler.doesExist());

    pathHandler.input(getAprgPath() + R"(AprgCommon\FilesForTests)");
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    pathHandler.input(getAprgPath() + R"(AprgCommon\FilesForTests\)");
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory()), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerStd, ReInputFileThatIsToBeDeletedActualLocalDirectory) {
    LocalPath const pathOfFileToBeDeleted(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeDeleted.log)"));
    createEmptyFile(fixPath(pathOfFileToBeDeleted).string());

    PathHandler pathHandler(pathOfFileToBeDeleted);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeDeleted.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeDeleted.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_FALSE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerStd, FileIsCopiedToNewFileActualLocalDirectory) {
    LocalPath const pathOfFileToBeCopied(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeCopied.log)");
    string const pathOfCopiedFile("CopiedFile.log");
    createEmptyFile(fixPath(pathOfFileToBeCopied).string());

    PathHandler pathHandler(pathOfFileToBeCopied);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeCopied.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeCopied.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeCopied", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.copyFileToAndIsSuccessful(pathHandler.getDirectory() / pathOfCopiedFile));

    PathHandler pathHandlerOfCopiedFile(pathHandler.getDirectory() / pathOfCopiedFile);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\CopiedFile.log)"), pathHandlerOfCopiedFile.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandlerOfCopiedFile.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandlerOfCopiedFile.getDirectory());
    EXPECT_EQ("CopiedFile.log", pathHandlerOfCopiedFile.getFile());
    EXPECT_EQ("CopiedFile", pathHandlerOfCopiedFile.getFilenameOnly());
    EXPECT_EQ("log", pathHandlerOfCopiedFile.getExtension());
    EXPECT_TRUE(pathHandlerOfCopiedFile.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());
    EXPECT_TRUE(pathHandlerOfCopiedFile.deleteFileAndIsSuccessful());
}

TEST(AlbaLocalPathHandlerStd, ReInputFileThatIsToBeRenamedActualLocalDirectory) {
    LocalPath const pathOfFileToBeRenamed(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeRenamed.log)");
    createEmptyFile(fixPath(pathOfFileToBeRenamed).string());

    PathHandler pathHandler(pathOfFileToBeRenamed);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\FileToBeRenamed.log)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeRenamed.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeRenamed", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameFileAndIsSuccessful("RenamedFile.txt"));

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\RenamedFile.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("RenamedFile.txt", pathHandler.getFile());
    EXPECT_EQ("RenamedFile", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.deleteFileAndIsSuccessful());
}

TEST(AlbaLocalPathHandlerStd, ReInputDirectoryThatIsToBeRenamedActualLocalDirectory) {
    LocalPath const pathOfDirectoryToBeRenamed(getAprgTestDirectory() + R"(\DirectoryTest\DIR1)");

    PathHandler pathHandler(pathOfDirectoryToBeRenamed);
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameDirectoryAndIsSuccessful("RenamedDirectory"));

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\RenamedDirectory\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\RenamedDirectory\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());

    EXPECT_TRUE(pathHandler.renameDirectoryAndIsSuccessful("DIR1"));

    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgTestDirectory() + R"(\DirectoryTest\DIR1\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryAndFileNoFileExtensionGivenWithNumbersAndSpecialCharactersTwoTimes) {
    PathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(R"(e\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(fixPath(R"(e\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)"), pathHandler.getPath());
    EXPECT_TRUE(pathHandler.getRoot().empty());
    EXPECT_EQ(fixPath(R"(e\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)"), pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryAndFileDoublePeriodInPath) {
    PathHandler pathHandler(getAprgPath() + R"(..\dir\file.txt)");
    EXPECT_EQ(fixPath(getAprgPath() + R"(..\dir\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(..\dir\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(getAprgPath() + R"(dir\..\..\file.txt)");
    EXPECT_EQ(fixPath(getAprgPath() + R"(..\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir\..\..\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());

    pathHandler.input(getAprgPath() + R"(dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir2\file.txt)"), pathHandler.getPath());
    EXPECT_EQ(getAprgRootPath(), pathHandler.getRoot());
    EXPECT_EQ(fixPath(getAprgPath() + R"(dir2\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
}

TEST(AlbaLocalPathHandlerStd, FileSizeTestFileIsNotExisting) {
    PathHandler pathHandler("This path does not exist");

    EXPECT_EQ("This path does not exist", pathHandler.getPath());
    ASSERT_FALSE(pathHandler.doesExist());
    EXPECT_EQ(0U, pathHandler.getFileSize());
}

TEST(AlbaLocalPathHandlerStd, FileSizeTestFileIsExisting) {
    PathHandler pathHandler(ALBA_COMMON_SIZE_TEST_FILE);

    EXPECT_EQ(fixPath(ALBA_COMMON_SIZE_TEST_FILE), pathHandler.getPath());
    ASSERT_TRUE(pathHandler.doesExist());
    EXPECT_EQ(5000U, pathHandler.getFileSize());
}

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryFindFileAndDirectoryOneDepth) {
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

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryFindFileAndDirectoryMultipleDepthTwo) {
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

TEST(AlbaLocalPathHandlerStd, FullPathWithDirectoryFindFileAndDirectoryUnlimitedDepth) {
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

TEST(AlbaLocalPathHandlerStd, CreatePathHandlerForDetectedPathWorks) {
    PathHandler const pathHandler(PathHandler::createPathHandlerForDetectedPath());

    EXPECT_FALSE(pathHandler.getPath().empty());
    EXPECT_TRUE(pathHandler.doesExist());
}

TEST(AlbaLocalPathHandlerStd, CreateDirectoriesAndIsSuccessfulWorks) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\DIR2\DIR3\)");
    ASSERT_FALSE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").isExistingDirectory());

    EXPECT_TRUE(pathHandler.createDirectoriesAndIsSuccessful());

    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\DIR2\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\DIR1\DIR2\DIR3\)").isExistingDirectory());

    ASSERT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").deleteDirectoryAndIsSuccessful());
    EXPECT_FALSE(PathHandler(getAprgTestDirectory() + R"(\CreateDirectory\)").isExistingDirectory());
}

TEST(AlbaLocalPathHandlerStd, DeleteDirectoryAndIsSuccessfulWorks) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DeleteDirectory\)");
    EXPECT_TRUE(
        PathHandler(getAprgTestDirectory() + R"(\DeleteDirectory\DIR1\DIR2\DIR3\)").createDirectoriesAndIsSuccessful());
    createEmptyFile(getAprgTestDirectory() + R"(\DeleteDirectory\FILE0.txt)");
    createEmptyFile(getAprgTestDirectory() + R"(\DeleteDirectory\DIR1\FILE1.txt)");
    createEmptyFile(getAprgTestDirectory() + R"(\DeleteDirectory\DIR1\DIR2\FILE2.txt)");
    ASSERT_TRUE(PathHandler(getAprgTestDirectory() + R"(\DeleteDirectory\)").isExistingDirectory());

    EXPECT_TRUE(pathHandler.deleteDirectoryAndIsSuccessful());

    EXPECT_FALSE(PathHandler(getAprgTestDirectory() + R"(\DeleteDirectory\)").isExistingDirectory());
}

TEST(AlbaLocalPathHandlerStd, DeleteAllDirectoryContentsAndIsSuccessfulWorks) {
    PathHandler const pathHandler(getAprgTestDirectory() + R"(\DeleteContents\)");
    EXPECT_TRUE(
        PathHandler(getAprgTestDirectory() + R"(\DeleteContents\DIR1\DIR2\DIR3\)").createDirectoriesAndIsSuccessful());
    createEmptyFile(getAprgTestDirectory() + R"(\DeleteContents\FILE0.txt)");
    createEmptyFile(getAprgTestDirectory() + R"(\DeleteContents\DIR1\FILE1.txt)");
    createEmptyFile(getAprgTestDirectory() + R"(\DeleteContents\DIR1\DIR2\FILE2.txt)");
    ASSERT_TRUE(PathHandler(getAprgTestDirectory() + R"(\DeleteContents\)").isExistingDirectory());

    EXPECT_TRUE(pathHandler.deleteAllDirectoryContentsAndIsSuccessful());

    EXPECT_TRUE(PathHandler(getAprgTestDirectory() + R"(\DeleteContents\)").isExistingDirectory());
    int numberOfItems = 0;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [&](LocalPath const&) { ++numberOfItems; }, [&](LocalPath const&) { ++numberOfItems; });
    EXPECT_EQ(0, numberOfItems);
}

TEST(AlbaLocalPathHandlerStd, DoesExistWorks) {
    EXPECT_FALSE(PathHandler("").doesExist());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory()).doesExist());
    EXPECT_TRUE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).doesExist());
}

TEST(AlbaLocalPathHandlerStd, IsExistingDirectoryWorks) {
    EXPECT_FALSE(PathHandler("").isExistingDirectory());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory()).isExistingDirectory());
    EXPECT_FALSE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).isExistingDirectory());
}

TEST(AlbaLocalPathHandlerStd, IsExistingFileWorks) {
    EXPECT_FALSE(PathHandler("").isExistingFile());
    EXPECT_FALSE(PathHandler(getAprgTestDirectory()).isExistingFile());
    EXPECT_TRUE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).isExistingFile());
}

TEST(AlbaLocalPathHandlerStd, IsRelativePathWorks) {
    EXPECT_TRUE(PathHandler("").isRelativePath());
    EXPECT_FALSE(PathHandler(getAprgTestDirectory()).isRelativePath());
    EXPECT_FALSE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).isRelativePath());
    EXPECT_TRUE(PathHandler("a/b").isRelativePath());
}

TEST(AlbaLocalPathHandlerStd, IsAbsolutePathWorks) {
    EXPECT_FALSE(PathHandler("").isAbsolutePath());
    EXPECT_TRUE(PathHandler(getAprgTestDirectory()).isAbsolutePath());
    EXPECT_TRUE(PathHandler(APRG_COMMON_EMPTY_TEST_FILE).isAbsolutePath());
    EXPECT_FALSE(PathHandler("a/b").isAbsolutePath());
}

}  // namespace alba
