#include <BitmapManipulator/AnimeFilter.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(\AprgBitmapFilters\FilesForTests\SampleBitmaps\)"

namespace alba::AprgBitmap {

TEST(AnimeFilterTest, DISABLED_AnimizeMultipleFilesTest) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const inputDirectory(bitmapDirectory.getDirectory() / R"(AnimizeMultipleFilesTest\input2\)");
    inputDirectory.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const inputFilePathHandler(filePath);
            AlbaLocalPathHandler const outputFilePathHandler(
                bitmapDirectory.getDirectory() / R"(AnimizeMultipleFilesTest\output2\Out_)" /
                inputFilePathHandler.getFile());
            animize(inputFilePathHandler.getPath(), outputFilePathHandler.getPath());
            cout << "Finished: " << outputFilePathHandler.getPath() << "\n";
        });
}

TEST(AnimeFilterTest, DISABLED_AnimizeSingleFileTest) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const inputFilePathHandler(
        bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\GilmoreGirls.bmp)");
    AlbaLocalPathHandler const outputFilePathHandler(
        bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\GilmoreGirls_Animized.bmp)");
    animize(inputFilePathHandler.getPath(), outputFilePathHandler.getPath());
}

}  // namespace alba::AprgBitmap
