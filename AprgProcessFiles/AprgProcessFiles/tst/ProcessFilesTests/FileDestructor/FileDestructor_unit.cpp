#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ProcessFiles/FileDestructor/FileDestructor.hpp>
#include <ProcessFilesTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

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
    FileDestructor const fileDestructor;
    AlbaLocalPathHandler pathHandler(APRG_FILE_DESTRUCTION_TEST_DIRECTORY);
    unsigned int numberOfFiles = 0;
    unsigned int numberOfDirectories = 0;
    createAFileInDirectory(pathHandler.getPath());
    retrieveNumberOfFilesAndDirectoriesFromPath(pathHandler, numberOfFiles, numberOfDirectories);
    EXPECT_EQ(1U, numberOfFiles);
    EXPECT_EQ(0U, numberOfDirectories);

    fileDestructor.destroy(pathHandler.getPath());

    retrieveNumberOfFilesAndDirectoriesFromPath(pathHandler, numberOfFiles, numberOfDirectories);
    EXPECT_EQ(0U, numberOfFiles);
    EXPECT_EQ(0U, numberOfDirectories);
}

}  // namespace alba
