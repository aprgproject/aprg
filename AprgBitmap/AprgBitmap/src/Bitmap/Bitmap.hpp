#pragma once

#include <Bitmap/BitmapConfiguration.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <Bitmap/CommonTypes.hpp>

#include <filesystem>
#include <string>

namespace alba::AprgBitmap {

class Bitmap {
public:
    explicit Bitmap(std::filesystem::path const& filePath);
    [[nodiscard]] BitmapConfiguration getConfiguration() const;

    [[nodiscard]] BitmapSnippet createColorFilledSnippetWithSizeOfWholeBitmap(
        uint8_t const colorByte) const;  // implement UT

    [[nodiscard]] BitmapSnippet getSnippetReadFromFileWholeBitmap() const;  // implement UT

    [[nodiscard]] BitmapSnippet getSnippetReadFromFileWithOutOfRangeCoordinates(
        int const outOfRangeLeft, int const outOfRangeTop, int const outOfRangeRight, int const outOfRangeBottom) const;

    [[nodiscard]] BitmapSnippet getSnippetReadFromFileWithNumberOfBytesToRead(
        BitmapXY const center, int const numberOfBytesToRead) const;

    [[nodiscard]] BitmapSnippet getSnippetReadFromFile(
        BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const;

    void setSnippetWriteToFile(BitmapSnippet const& snippet) const;

private:
    void calculateNewCornersBasedOnCenterAndNumberOfBytes(
        BitmapXY& topLeftCorner, BitmapXY& bottomRightCorner, BitmapXY const center, int const numberOfBytes) const;

    static void adjustToTargetLength(int& low, int& high, int const targetLength, int const maxLength);
    BitmapConfiguration m_configuration;
};

}  // namespace alba::AprgBitmap
