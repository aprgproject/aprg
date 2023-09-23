#include <Bitmap/Bitmap.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

#define APRG_BITMAP_WRITE_TEST_FILE APRG_DIR R"(\AprgBitmap\FilesForTests\SampleBitmaps\WriteTestFile.bmp)"

namespace alba::AprgBitmap {

TEST(BitmapWriteTest, TestForWritingBitmap) {
    Bitmap const bitmap(APRG_BITMAP_WRITE_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(10, 10), BitmapXY(90, 90)));

    for (unsigned i = 10; i <= 90; ++i) {
        snippet.setPixelAt(
            BitmapXY(
                static_cast<int>(i),
                static_cast<int>(round(static_cast<double>(50) + 40 * (sin(static_cast<double>(i) / 5))))),
            0x00FF0000);
    }
    bitmap.setSnippetWriteToFile(snippet);
}

TEST(BitmapWriteTest, TestForWritingMissingBitmapFile) {
    Bitmap const bitmap("FileThatDoesNotExist");
    ASSERT_FALSE(bitmap.getConfiguration().isValid());

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(50, 50), BitmapXY(150, 150)));
    for (unsigned i = 50; i <= 150; ++i) {
        snippet.setPixelAt(
            BitmapXY(
                static_cast<int>(i),
                static_cast<int>(round(static_cast<double>(100) + 40 * (sin(static_cast<double>(i) / 10))))),
            0x00FF0000);
    }
    bitmap.setSnippetWriteToFile(snippet);
}

}  // namespace alba::AprgBitmap
