#include <BitmapManipulator/AnimeFilter.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(\AprgBitmapFilters\FilesForTests\SampleBitmaps\)"

namespace alba::AprgBitmap {

TEST(AnimeFilterTest, DISABLED_AnimizeMultipleFilesTest) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const inputDirectory(bitmapDirectory.getDirectory() + R"(AnimizeMultipleFilesTest\input2\)");
    ListOfPaths inputSubDirectories;
    ListOfPaths inputFiles;
    inputDirectory.findFilesAndDirectoriesOneDepth("*.*", inputFiles, inputSubDirectories);

    for (string const& inputFile : inputFiles) {
        AlbaLocalPathHandler const inputFilePathHandler(inputFile);
        AlbaLocalPathHandler const outputFilePathHandler(
            bitmapDirectory.getDirectory() + R"(AnimizeMultipleFilesTest\output2\Out_)" +
            inputFilePathHandler.getFile());
        animize(inputFilePathHandler.getFullPath(), outputFilePathHandler.getFullPath());
        cout << "Finished: " << outputFilePathHandler.getFullPath() << "\n";
    }
}

TEST(AnimeFilterTest, DISABLED_AnimizeSingleFileTest) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const inputFilePathHandler(
        bitmapDirectory.getDirectory() + R"(NonAnimeBitmaps\GilmoreGirls.bmp)");
    AlbaLocalPathHandler const outputFilePathHandler(
        bitmapDirectory.getDirectory() + R"(NonAnimeBitmaps\GilmoreGirls_Animized.bmp)");
    animize(inputFilePathHandler.getFullPath(), outputFilePathHandler.getFullPath());
}

}  // namespace alba::AprgBitmap
