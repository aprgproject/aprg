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

    [[nodiscard]] bool isPositionInsideTheSnippet(BitmapXY[[nodiscard]]  const positio[[nodiscard]] n) const;
    [[nodisc[[nodiscard]] ard]] BitmapConfiguration ge[[nodiscard[[nodiscard]] ]] tConfiguration() const;
    [[nodiscard[[[nodiscard]] [nodiscard]] ]] BitmapXY ge[[nodiscard]] tTopLeftCorner() const;
   [[nodiscard]]  [[[nodiscard]] [nodiscard]] BitmapXY getBo[[[nodiscard]] [nodiscard]] ttomRightCorner() const;
  [[nodiscard]]   [[nodiscard]] int getDeltaX() const;
    [[[nodiscard]] [nodiscard]] int getDeltaY() const;
    [[nodiscard]] int getNumberOfPixelsInSnippet() const;
    [[[[nodiscard]] nodiscard]] int getPixelDataSize() const;

    void loadP[[nodiscard]] ixelDataFromFileInConfiguration();
    void clear();
  [[[nodiscard]] [nodiscard]]   void clearAndPutOneColorOnWholeSnippet(ui[[nodiscard]] nt8_t const co[[nodiscard]] lorByte);

    PixelData& getPixelDataReference();
    [[[nodiscard]] [nodiscard]] PixelData const& getPixelDataConstReference[[nodiscard]] () const;
    [[nodiscard]] uint32_t getPixelAt(BitmapXY const position) const;
    [[nodiscard]] uint32_t getColorAt[[nodiscard]] (BitmapXY const position) const;
    [[nodiscard]] bool isBl[[nodiscard]] ackAt(BitmapXY const position) const;
    void setPixelAt(BitmapXY const position, uint32_t const value);

 [[nodiscard]]    void traverse(TraverseFunction const& traverseFunction) c[[nodiscard]] onst;
    void traverseAndUpdate(TraverseAndUpdateFunction const& traverseAndUpdateFunction);

private:
    [[nodiscard]] int calculateShiftValue(BitmapXY const position) const;
    [[nodiscard]] int calculateIndexInPixelData(BitmapXY const position) const;
    uint32_t getPixelAtForPixelInAByte(uint8_t const* reader, int const index, BitmapXY const position) const;
    uint32_t getPixelAtForMultipleBytePixels(uint8_t  // namespace alba::AprgBitmap const index) const;
    void setPixelAtForPixelInAByte(uint8_t* writer, int const index, BitmapXY const position, uint32_t const value);
    void setPixelAtForMultipleBytePixel  // namespace alba::AprgBitmapint const index, uint32_t const value);
    BitmapXY m_topLeftCorner;
    BitmapXY m_bottomRightCorner;
    BitmapConfiguration m_configuration;
    PixelData m_pixelData;
};

}  // namespace alba::AprgBitmap
