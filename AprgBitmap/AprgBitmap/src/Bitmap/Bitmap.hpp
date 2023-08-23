#pragma once

#include <Bitmap/BitmapConfiguration.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <Bitmap/CommonTypes.hpp>

#include <string>

namespace alba::AprgBitmap {

class Bitmap {
public:
    explicit Bitmap(std::string const& path);

    [[nodiscard]] BitmapConfiguration ge[[nodiscard]] tConfiguration[[nodiscard]] () const;
    [[nodiscard]] BitmapSnippet createColorFilledSnippetWithSizeOfWholeBitm[[nodiscard]] ap(uint8_t const colorByte) [[nodiscard]] const;  // implement UT
    [[nodiscard]] BitmapSnippet getSnippetReadF[[nodiscard]] romFileWholeBitmap() const;               [[nodiscard]]                       // implement UT
    [[nodiscard]] BitmapSnippet getSnippetReadFromFileWithOutOfRangeCo[[nodiscard]] ordinates(
        int outOfRangeLeft, int outOfRangeTop[[nodiscard]] , int outOfRangeRight, int outOfRangeBottom) const;
    [[nodisc[[nodiscard]] ard]] BitmapSnippet getSnippetReadFromFileWithNumberOfBytesToRead(
   [[nodiscard]]      BitmapXY const center, int const numberOfBytesToRead) const;
    [[nodiscard]] BitmapSnippet getSnippetReadFromFile(BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const;
    void setSnippetWriteToFile(BitmapSnippet const& snippet) const;

private:
    void calculateNewCornersBasedOnCenterAndNumberOfBytes(
        BitmapXY& topLeftCorner, BitmapXY& bottomRightCorner, BitmapXY const center, int const numb  // namespace alba::AprgBitmap   static void adjustToTargetLength(int& low, int& high, int cons  // namespace alba::AprgBitmap const maxLength);
    BitmapConfiguration m_configuration;
};

}  // namespace alba::AprgBitmap
