#include <Bitmap/Bitmap.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ScreenMonitoring/AlbaLocalScreenMonitoring.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba::chess::ChessPeek {

TEST(ScreenMonitoringTest, DISABLED_ScreenCaptureCanBeSavedAsBitmap) {
    AlbaLocalScreenMonitoring screenMonitoring;
    screenMonitoring.capturePixelsFromScreen();

    AlbaLocalPathHandler const outputFileForWhite(APRG_DIR R"(\Chess\ChessPeek\Files\ScreeMonitoringTest.bmp)");
    Bitmap const outputBitmap(outputFileForWhite.getFullPath());
    BitmapSnippet outputSnippet(outputBitmap.getSnippetReadFromFileWholeBitmap());

    BitmapXY const topLeftCorner = outputSnippet.getTopLeftCorner();
    BitmapXY const bottomRightCorner = outputSnippet.getBottomRightCorner();
    for (int y = topLeftCorner.getY(); y <= bottomRightCorner.getY(); ++y) {
        for (int x = topLeftCorner.getX(); x <= bottomRightCorner.getX(); ++x) {
            outputSnippet.setPixelAt(BitmapXY(x, y), screenMonitoring.getColorAt(x, y));
        }
    }

    outputBitmap.setSnippetWriteToFile(outputSnippet);
}

}  // namespace alba::chess::ChessPeek
