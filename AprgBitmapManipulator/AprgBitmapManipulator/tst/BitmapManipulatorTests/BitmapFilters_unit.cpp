#include <BitmapManipulator/AnimizeColor.hpp>
#include <BitmapManipulator/BitmapFilters.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace std::filesystem;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(\AprgBitmapFilters\FilesForTests\SampleBitmaps\)"

namespace alba::AprgBitmap {

TEST(BitmapFiltersTest, DISABLED_FindPenAndNonPenAndFillNonPenGaps) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenPointsExperiments\sample.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet const tempSnippet(bitmapFilters.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilters.getBlankSnippetWithBackground());
    PenPoints penPoints;

    alba::AprgBitmap::BitmapFilters::determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    alba::AprgBitmap::BitmapFilters::drawPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapPenPoints.bmp");

    outputSnippet = bitmapFilters.getBlankSnippetWithBackground();
    alba::AprgBitmap::BitmapFilters::drawNonPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPoints.bmp");

    outputSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawBlurredNonPenPoints(penPoints, tempSnippet, outputSnippet, 3, 0x40);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapBlurredNonPenPoints.bmp");

    bitmapFilters.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPointsFilled.bmp");
}

TEST(BitmapFiltersTest, DISABLED_DeterminePenCircles) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(
        bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\JohnMayerVideoBlurredAnimizedColor.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet const tempSnippet(bitmapFilters.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilters.getBlankSnippetWithBackground());
    PenPoints penPoints;
    PenCircles penCircles;

    alba::AprgBitmap::BitmapFilters::determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    alba::AprgBitmap::BitmapFilters::drawPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(
        outputSnippet, "JohnMayerVideoBlurredAnimizedColor_1PenPoints.bmp");

    outputSnippet = bitmapFilters.getBlankSnippetWithBackground();
    alba::AprgBitmap::BitmapFilters::determinePenCirclesFromPenPoints(penCircles, penPoints, tempSnippet, 0x08, 0.80);
    alba::AprgBitmap::BitmapFilters::drawPenCircles(penCircles, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(
        outputSnippet, "JohnMayerVideoBlurredAnimizedColor_2PenCircles.bmp");
}

TEST(BitmapFiltersTest, DISABLED_DeterminePenAndNonPen) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\VeronicaMars.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet const tempSnippet(bitmapFilters.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilters.getBlankSnippetWithBackground());
    PenPoints penPoints;

    alba::AprgBitmap::BitmapFilters::determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    alba::AprgBitmap::BitmapFilters::drawPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_Pen.bmp");

    outputSnippet = bitmapFilters.getBlankSnippetWithBackground();
    alba::AprgBitmap::BitmapFilters::drawNonPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_NonPen.bmp");
}

TEST(BitmapFiltersTest, DISABLED_CclTestOneComponentAtATime) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(CCL\CclTest.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.determineConnectedComponentsByOneComponentAtATime(outputSnippet);
    bitmapFilters.drawNewColorForLabels(outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "Ccl_OneComponentAtATime.bmp");
}

TEST(BitmapFiltersTest, DISABLED_CclTestTwoPass) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(CCL\CclTest.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.determineConnectedComponentsUsingTwoPass(outputSnippet);
    bitmapFilters.drawNewColorForLabels(outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "Ccl_TwoPass.bmp");
}

TEST(BitmapFiltersTest, DISABLED_BlurredColors) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.drawBlurredColorsUsingCircles(outputSnippet, 8, 0x20);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_FillGaps) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\White.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "White_FilledGaps.bmp");
}

TEST(BitmapFiltersTest, DISABLED_BlurringDisimilarColors) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    alba::AprgBitmap::BitmapFilters::drawWithBlurringDisimilarColors(outputSnippet, 5, 0x02);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_BlurUsingSnakeLikeTraversal) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    alba::AprgBitmap::BitmapFilters::drawWithBlurUsingSnakeLikeTraversal(outputSnippet, 0x08);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_ConvertToAnimeColorWorks) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    path const inputBitmapFile = bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\santana_NonPenFilledGaps.bmp)";
    BitmapFilters bitmapFilters(inputBitmapFile);
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());
    AnimizeColor animizeColor;
    animizeColor.gatherStatistics(inputBitmapFile);
    animizeColor.calculateNewValues();

    alba::AprgBitmap::BitmapFilters::drawAnimeColor(outputSnippet, animizeColor);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santana_NonPenFilledGaps_AnimeColor.bmp");
}

TEST(BitmapFiltersTest, DISABLED_GatherAndSaveStatisticsWorks) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    BitmapFilters bitmapFilters(bitmapDirectory.getDirectory() / R"(NonAnimeBitmaps\Foals.bmp)");

    bitmapFilters.gatherAndSaveColorDataAndStatistics();
}

}  // namespace alba::AprgBitmap
