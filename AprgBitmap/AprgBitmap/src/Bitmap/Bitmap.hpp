#pragma once

#include <Bitmap/BitmapConfiguration.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <Bitmap/CommonTypes.hpp>

#include <string>

namespace alba::AprgBitmap {

class Bitmap {
public:
    explicit Bitmap(std::string const& path);

    BitmapConfiguration getConfiguration() const;
    BitmapSnippet createColorFilledSnippetWithSizeOfWholeBitmap(uint8_t const colorByte) const;  // implement UT
    BitmapSnippet getSnippetReadFromFileWholeBitmap() const;                                     // implement UT
    BitmapSnippet getSnippetReadFromFileWithOutOfRangeCoordinates(
        int outOfRangeLeft, int outOfRangeTop, int outOfRangeRight, int outOfRangeBottom) const;
    BitmapSnippet getSnippetReadFromFileWithNumberOfBytesToRead(
        BitmapXY const center, int const numberOfBytesToRead) const;
    BitmapSnippet getSnippetReadFromFile(BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const;
    void setSnippetWriteToFile(BitmapSnippet const& snippet) const;

private:
    void calculateNewCornersBasedOnCenterAndNumberOfBytes(
        BitmapXY& topLeftCorner, BitmapXY& bottomRightCorner, BitmapXY const center, int const numberOfBytes) const;
    static void adjustToTargetLength(int& low, int& high, int const targetLength, int const maxLength);
    BitmapConfiguration m_configuration;
};

}  // namespace alba
