#include <BitmapManipulator/BitmapFilters.hpp>
#include <BitmapManipulator/PenCirclesDrawer.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(\AprgBitmapFilters\FilesForTests\SampleBitmaps\)"

namespace alba::AprgBitmap {

TEST(PenCirclesDrawerTest, DrawACircle) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(100, 100), 20, 0x123456);

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.draw();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "DrawACircle.bmp");
}

TEST(PenCirclesDrawerTest, DrawTwoConnectedCircles) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(200, 200), 20, 0x123456);
    penCircles.addAsPenCircle(BitmapXY(50, 50), 40, 0x123456);
    penCircles.connectCircles(BitmapXY(200, 200), BitmapXY(50, 50));

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.draw();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "DrawTwoConnectedCircles.bmp");
}

TEST(PenCirclesDrawerTest, DrawTwoConnectedCirclesWithDifferentColors) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(200, 200), 20, 0x1188FF);
    penCircles.addAsPenCircle(BitmapXY(50, 50), 40, 0x226644);
    penCircles.connectCircles(BitmapXY(200, 200), BitmapXY(50, 50));

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.draw();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(
        outputSnippet, "DrawTwoConnectedCirclesWithDifferentColors.bmp");
}

TEST(PenCirclesDrawerTest, DrawTwoCirclesThatCoincidesWithEachOther) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(200, 200), 20, 0x1188FF);
    penCircles.addAsPenCircle(BitmapXY(220, 220), 60, 0x226644);

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.draw();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "DrawTwoCirclesThatCoincidesWithEachOther.bmp");
}

TEST(PenCirclesDrawerTest, DrawTwoAlmostConcentricCircles) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(200, 200), 20, 0x1188FF);
    penCircles.addAsPenCircle(BitmapXY(201, 201), 60, 0x226644);

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.draw();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "DrawTwoAlmostConcentricCircles.bmp");
}

TEST(PenCirclesDrawerTest, DrawTwoCirclesWithIntersectionAndAreIntentionallyConnected) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(200, 200), 50, 0x1188FF);
    penCircles.addAsPenCircle(BitmapXY(250, 250), 60, 0x226644);
    penCircles.connectCircles(BitmapXY(200, 200), BitmapXY(250, 250));

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.draw();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(
        outputSnippet, "DrawTwoCirclesWithIntersection_IntentionallyConnected.bmp");
}

TEST(PenCirclesDrawerTest, DrawTwoCirclesWithIntersectionAndAreAutomaticallyConnected) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(200, 200), 50, 0x1188FD);
    penCircles.addAsPenCircle(BitmapXY(250, 250), 60, 0x138AFF);

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.draw();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(
        outputSnippet, "DrawTwoCirclesWithIntersection_AutomaticallyConnected.bmp");
}

TEST(PenCirclesDrawerTest, DrawMultipleCirclesWithACommonConnection) {
    AlbaLocalPathHandler const bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler const sampleFile(bitmapDirectory.getDirectory() / R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(200, 200), 50, 0x1188FF);
    penCircles.addAsPenCircle(BitmapXY(150, 150), 60, 0x991122);
    penCircles.addAsPenCircle(BitmapXY(150, 250), 70, 0x7777AA);
    penCircles.addAsPenCircle(BitmapXY(250, 150), 80, 0x449933);
    penCircles.addAsPenCircle(BitmapXY(250, 250), 90, 0x226644);
    penCircles.connectCircles(BitmapXY(200, 200), BitmapXY(150, 150));
    penCircles.connectCircles(BitmapXY(200, 200), BitmapXY(150, 250));
    penCircles.connectCircles(BitmapXY(200, 200), BitmapXY(250, 150));
    penCircles.connectCircles(BitmapXY(200, 200), BitmapXY(250, 250));

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.draw();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "DrawMultipleCirclesWithACommonConnection.bmp");
}

}  // namespace alba::AprgBitmap
