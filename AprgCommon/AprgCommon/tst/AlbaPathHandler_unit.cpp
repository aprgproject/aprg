#include <fstream>
#include <gtest/gtest.h>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>

using namespace std;
using namespace alba;

#define SIZE_TEST_FILE R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\FileReaderTest\Test2_SizeTest.txt)"
TEST(PathTest, FullPathWithDirectoryAndFileGiven)
{
    AlbaPathHandler pathHandler(R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", R"(\)");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)");
    EXPECT_EQ(pathHandler.getFile(), "76543.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "76543");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_EQ(pathHandler.getImmediateDirectoryName(), "tst");
}

TEST(PathTest, FileOnly)
{
    AlbaPathHandler pathHandler("src", R"(\)");
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_EQ(pathHandler.getFile(), "src");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "src");
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_TRUE(pathHandler.getImmediateDirectoryName().empty());
}

TEST(PathTest, ReInputFile)
{
    AlbaPathHandler pathHandler("src", R"(\)");
    pathHandler.reInput();
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_EQ(pathHandler.getFile(), "src");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "src");
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_TRUE(pathHandler.getImmediateDirectoryName().empty());
}

TEST(PathTest, GoUpUntilLastFolder)
{
    AlbaPathHandler pathHandler(R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", R"(\)");
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\APRG12345\Aprg!@#$%Common\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\APRG12345\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_WindowsStyleInput)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_JumbledSlashes)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG////AprgCommon\\\\/AprgCommon/tst\FilesForTests\)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WebPathTest, DirectoryWithColonAndFileGivenAndNoProtocol)
{
    AlbaWebPathHandler pathHandler(R"(\\::://directory!@#$%12345\\\\/\\\\/file.txt)");
    EXPECT_FALSE(pathHandler.hasProtocol());
    EXPECT_TRUE(pathHandler.getProtocol().empty());
    EXPECT_EQ(pathHandler.getDirectory(), R"(\\::://directory!@#$%12345/)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WebPathTest, FullPathWithOnlyDirectoryGiven_HttpStyleInput)
{
    AlbaWebPathHandler pathHandler(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///)");
    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ(pathHandler.getProtocol(), "http");
    EXPECT_EQ(pathHandler.getDirectory(), "hTTp://www.google.com/!@#$%12345/");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WebPathTest, FullPathWithQuestionMark)
{
    AlbaWebPathHandler pathHandler("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg?v=1354256522");
    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ(pathHandler.getProtocol(), "http");
    EXPECT_EQ(pathHandler.getDirectory(), "http://a.mhcdn.net/store/manga/12114/001.0/compressed/");
    EXPECT_EQ(pathHandler.getFile(), "r049.jpg");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "r049");
    EXPECT_EQ(pathHandler.getExtension(), "jpg");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WebPathTest, GotoLinkWhenNoProtocolIsGiven)
{
    AlbaWebPathHandler pathHandler(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///NewFile1.txt)");
    pathHandler.gotoLink(R"(NewDirectory1\NewFile2.ext)");

    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ(pathHandler.getProtocol(), "http");
    EXPECT_EQ(pathHandler.getDirectory(), "hTTp://www.google.com/!@#$%12345/NewDirectory1/");
    EXPECT_EQ(pathHandler.getFile(), "NewFile2.ext");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "NewFile2");
    EXPECT_EQ(pathHandler.getExtension(), "ext");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WebPathTest, GotoLinkWhenWithProtocolIsGiven)
{
    AlbaWebPathHandler pathHandler(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///)");
    pathHandler.gotoLink(R"(ftP://www.yahoo.com\NewDirectory1\\NewFile2.ext)");

    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ(pathHandler.getProtocol(), "ftp");
    EXPECT_EQ(pathHandler.getDirectory(), "ftP://www.yahoo.com/NewDirectory1/");
    EXPECT_EQ(pathHandler.getFile(), "NewFile2.ext");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "NewFile2");
    EXPECT_EQ(pathHandler.getExtension(), "ext");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getFile(), "zxcvbnm12345.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "zxcvbnm12345");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getFile(), "zxcvbnm12345.");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "zxcvbnm12345");
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileExtensionOnlyGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getFile(), ".zxcvbnm12345");
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ(pathHandler.getExtension(), "zxcvbnm12345");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharactersTwoTimes)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)");
    EXPECT_EQ(pathHandler.getFile(), "76543.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "76543");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);

    pathHandler.input(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(pathHandler.getDrive(), "E");
    EXPECT_EQ(pathHandler.getDirectory(), R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getFile(), ".zxcvbnm12345");
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ(pathHandler.getExtension(), "zxcvbnm12345");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFile_DoublePeriodInPath)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\..\dir\file.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\dir\)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);

    pathHandler.input(R"(C:\APRG\dir\..\..\file.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);

    pathHandler.input(R"(C:\APRG\dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\dir2\)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFile_ActualLocalDirectory)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(pathHandler.getFile(), "File1.log");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "File1");
    EXPECT_EQ(pathHandler.getExtension(), "log");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(), true);

    pathHandler.input(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\thisFileDoesNotExist.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ(pathHandler.getFile(), "thisFileDoesNotExist.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "thisFileDoesNotExist");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(), false);

    pathHandler.input(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(),true);

    pathHandler.input(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(),true);
}

TEST(WindowsPathTest, ReInputFileThatIsToBeDeleted_ActualLocalDirectory)
{
    string const pathOfFileToBeDeleted(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\FileToBeDeleted.log)");
    std::ofstream fileToBeDeleted(pathOfFileToBeDeleted);
    fileToBeDeleted.close();

    AlbaWindowsPathHandler pathHandler(pathOfFileToBeDeleted);
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(pathHandler.getFile(), "FileToBeDeleted.log");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "FileToBeDeleted");
    EXPECT_EQ(pathHandler.getExtension(), "log");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(), true);

    pathHandler.deleteFile();
    pathHandler.reInput();

    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(pathHandler.getFile(), "FileToBeDeleted.log");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "FileToBeDeleted");
    EXPECT_EQ(pathHandler.getExtension(), "log");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(), false);
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryOneDepth)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(listOfFiles.size(), 5);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)");
    ASSERT_EQ(listOfDirectory.size(), 6);
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)");
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryMultipleDepthTwo)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectory, 2);
    ASSERT_EQ(listOfFiles.size(), 10);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)");
    ASSERT_EQ(listOfDirectory.size(), 7);
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)");
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepth)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(listOfFiles.size(), 11);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\File6.jpg)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)");
    ASSERT_EQ(listOfDirectory.size(), 7);
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)");
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepthWithWildCard)
{
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.log", listOfFiles, listOfDirectory);
    ASSERT_EQ(listOfFiles.size(), 1);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    ASSERT_EQ(listOfDirectory.size(), 0);
}

TEST(WindowsPathTest, FileSizeTest)
{
    AlbaWindowsPathHandler pathHandler(SIZE_TEST_FILE);

    ASSERT_EQ(pathHandler.getPathType(), PathType::File);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);
    EXPECT_DOUBLE_EQ(pathHandler.getFileSizeEstimate(), 5000);
}
