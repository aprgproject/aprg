#include <Common/PathHandler/AlbaPathHandler.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba {

TEST(AlbaPathHandlerTest, GoUpUntilLastFolder) {
    AlbaPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", R"(\)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", pathHandler.getPath());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\)", pathHandler.getPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\)", pathHandler.getPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\)", pathHandler.getPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\)", pathHandler.getPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\)", pathHandler.getPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(AlbaPathHandlerTest, FullPathWithDirectoryAndFileGiven) {
    AlbaPathHandler const pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", R"(\)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_EQ("tst", pathHandler.getImmediateDirectoryName());
}

TEST(AlbaPathHandlerTest, FileOnly) {
    AlbaPathHandler const pathHandler("src", R"(\)");
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_EQ("src", pathHandler.getFile());
    EXPECT_EQ("src", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.getImmediateDirectoryName().empty());
}

TEST(AlbaPathHandlerTest, ReInputFile) {
    AlbaPathHandler pathHandler("src", R"(\)");
    pathHandler.reInput();
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_EQ("src", pathHandler.getFile());
    EXPECT_EQ("src", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.getImmediateDirectoryName().empty());
}

TEST(AlbaPathHandlerTest, EmptyPathWorks) {
    AlbaPathHandler const pathHandler("");
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Empty, pathHandler.getPathType());
}

}  // namespace alba
