#pragma once

#include <Bitmap/BitmapConfiguration.hpp>
#include <Bitmap/CommonTypes.hpp>

#include <functional>

namespace alba::AprgBitmap {

class BitmapSnippet {
public:
    using TraverseFunction = std::function<void(BitmapXY const&, uint32_t const)>;
    using TraverseAndUpdateFunction = std::function<void(BitmapXY const&, uint32_t&)>;
    BitmapSnippet();

    BitmapSnippet(
        BitmapXY const topLeftCornerPosition, BitmapXY const bottomRightCornerPosition,
        BitmapConfiguration const& configuration);

    BitmapSnippet(
        BitmapXY const topLeftCornerPosition, BitmapXY const bottomRightCornerPosition,
        BitmapConfiguration&& configuration);

    [[nodiscard]] BitmapConfiguration getConfiguration() const;
    [[nodiscard]] BitmapXY getTopLeftCorner() const;
    [[nodiscard]] BitmapXY getBottomRightCorner() const;
    [[nodiscard]] PixelData const& getPixelDataConstReference() const;
    [[nodiscard]] int getDeltaX() const;
    [[nodiscard]] int getDeltaY() const;
    [[nodiscard]] int getNumberOfPixelsInSnippet() const;
    [[nodiscard]] int getPixelDataSize() const;
    [[nodiscard]] uint32_t getPixelAt(BitmapXY const position) const;
    [[nodiscard]] uint32_t getColorAt(BitmapXY const position) const;
    [[nodiscard]] bool isPositionInsideTheSnippet(BitmapXY const position) const;
    [[nodiscard]] bool isBlackAt(BitmapXY const position) const;
    void traverse(TraverseFunction const& traverseFunction) const;
    void loadPixelDataFromFileInConfiguration();
    void clear();
    void clearAndPutOneColorOnWholeSnippet(uint8_t const colorByte);
    void setPixelAt(BitmapXY const position, uint32_t const value);
    void traverseAndUpdate(TraverseAndUpdateFunction const& traverseAndUpdateFunction);
    PixelData& getPixelDataReference();

private:
    [[nodiscard]] int calculateShiftValue(BitmapXY const position) const;
    [[nodiscard]] int calculateIndexInPixelData(BitmapXY const position) const;
    uint32_t getPixelAtForPixelInAByte(uint8_t const* reader, int const index, BitmapXY const position) const;
    uint32_t getPixelAtForMultipleBytePixels(uint8_t const* reader, int const index) const;
    void setPixelAtForPixelInAByte(uint8_t* writer, int const index, BitmapXY const position, uint32_t const value);
    void setPixelAtForMultipleBytePixels(uint8_t* writer, int const index, uint32_t const value);
    BitmapXY m_topLeftCorner;
    BitmapXY m_bottomRightCorner;
    BitmapConfiguration m_configuration;
    PixelData m_pixelData;
};

}  // namespace alba::AprgBitmap
