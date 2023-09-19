#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ProcessFiles/FileDestructor/FileDestructor.hpp>
#include <ProcessFilesTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {

void createAFileInDirectory(path const& directory) {
    ofstream outputStream(directory / "SomeFile.txt");
    outputStream << "some string\n";
}

void retrieveNumberOfFilesAndDirectoriesFromPath(
    AlbaLocalPathHandler& pathHandler, unsigned int& numberOfFiles, unsigned int& numberOfDirectories) {
    numberOfFiles = 0;
    numberOfDirectories = 0;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [&](AlbaLocalPathHandler::LocalPath const&) { ++numberOfDirectories; },
        [&](AlbaLocalPathHandler::LocalPath const&) { ++numberOfFiles; });
}

}  // namespace

TEST(SampleTest, DestroyTest) {
    FileDestructor const fileDestructor;
    AlbaLocalPathHandler pathHandler(APRG_FILE_DESTRUCTION_TEST_DIRECTORY);
    pathHandler.createDirectoriesAndIsSuccessful();
    createAFileInDirectory(pathHandler.getPath());
    unsigned int numberOfFiles = 0;
    unsigned int numberOfDirectories = 0;
    retrieveNumberOfFilesAndDirectoriesFromPath(pathHandler, numberOfFiles, numberOfDirectories);
    EXPECT_EQ(1U, numberOfFiles);
    EXPECT_EQ(0U, numberOfDirectories);

    alba::FileDestructor::destroy(pathHandler.getPath());

    retrieveNumberOfFilesAndDirectoriesFromPath(pathHandler, numberOfFiles, numberOfDirectories);
    EXPECT_EQ(0U, numberOfFiles);
    EXPECT_EQ(0U, numberOfDirectories);
}

}  // namespace alba
