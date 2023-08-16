#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <FileDestructor.hpp>

#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>

using namespace std;

namespace alba {

namespace {

void createAFileInDirectory(string const& directory) {
    ofstream outputStream(directory + "SomeFile.txt");
    outputStream << "some string\n";
}

void retrieveNumberOfFilesAndDirectoriesFromPath(
    AlbaLocalPathHandler& pathHandler, unsigned int& numberOfFiles, unsigned int& numberOfDirectories) {
    pathHandler.reInput();
    ListOfPaths files;
    ListOfPaths directories;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    numberOfFiles = files.size();
    numberOfDirectories = directories.size();
}

}  // namespace

TEST(SampleTest, DestroyOneFileTest) {
    FileDestructor fileDestructor;
    AlbaLocalPathHandler pathHandler(APRG_DIR R"(\FileDestructor\FilesForTests\TestFolderForDestruction)");
    unsigned int numberOfFiles;
    unsigned int numberOfDirectories;
    pathHandler.createDirectoriesForNonExisitingDirectories();
    createAFileInDirectory(pathHandler.getFullPath());
    string systemCommand1 = string("echo \" PATH:") + pathHandler.getFullPath() + "\"";
    string systemCommand2 = string("cd ") + pathHandler.getFullPath() + " && dir";
    system(systemCommand1.c_str());
    system(systemCommand2.c_str());
    retrieveNumberOfFilesAndDirectoriesFromPath(pathHandler, numberOfFiles, numberOfDirectories);
    EXPECT_EQ(1U, numberOfFiles);
    EXPECT_EQ(0U, numberOfDirectories);

    fileDestructor.destroy(pathHandler.getFullPath());

    retrieveNumberOfFilesAndDirectoriesFromPath(pathHandler, numberOfFiles, numberOfDirectories);
    EXPECT_EQ(0U, numberOfFiles);
    EXPECT_EQ(0U, numberOfDirectories);
}

}  // namespace alba
