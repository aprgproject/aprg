#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <Common/File/AlbaFileReader.hpp>

#include <cstdint>
#include <string>

namespace alba::AprgBitmap {

enum class CompressedMethodType {
    RGB,
    RLE8,
    RLE4,
    BITFIELDS,
    JPEG,
    PNG,
    ALPHABITFIELDS,
    CMYK,
    CMYKRLE8,
    CMYKRLE4,
    Unknown
};

class BitmapConfiguration {
public:
    BitmapConfiguration();
    [[nodiscard]] bool isValid() const;
    [[nodiscard]] bool isSignatureValid() const;
    [[nodiscard]] bool isHeaderValid() const;
    [[nodiscard]] bool isNumberOfColorPlanesValid() const;
    [[nodiscard]] bool isNumberOfBitsPerPixelValid() const;
    [[nodiscard]] bool isCompressedMethodSupported() const;
    [[nodiscard]] bool isPositionWithinTheBitmap(BitmapXY const position) const;
    [[nodiscard]] bool isPositionWithinTheBitmap(int x, int y) const;

    [[nodiscard]] CompressedMethodType getCompressedMethodType() const;
    [[nodiscard]] std::string getPath() const;
    [[nodiscard]] uint32_t getPixelArrayAddress() const;
    [[nodiscard]] uint32_t getBitmapWidth() const;
    [[nodiscard]] uint32_t getBitmapHeight() const;
    [[nodiscard]] uint16_t getNumberOfBitsPerPixel() const;
    [[nodiscard]] uint32_t getNumberOfBytesPerRowInFile() const;
    [[nodiscard]] uint32_t getBitMaskForValue() const;

    [[nodiscard]] BitmapXY getPointWithinTheBitmap(int const xCoordinate, int const yCoordinate) const;
    [[nodiscard]] int getXCoordinateWithinTheBitmap(int const coordinate) const;
    [[nodiscard]] int getYCoordinateWithinTheBitmap(int const coordinate) const;
    static int getCoordinateWithinRange(int const coordinate, int maxLength);
    static BitmapXY getUpLeftCornerPoint();
    [[nodiscard]] BitmapXY getDownRightCornerPoint() const;

    [[nodiscard]] uint32_t getColorUsingPixelValue(uint32_t const pixelValue) const;
    [[nodiscard]] int convertPixelsToBytesRoundedToFloor(int pixels) const;
    [[nodiscard]] int convertPixelsToBytesRoundedToCeil(int pixels) const;
    [[nodiscard]] int convertBytesToPixels(int bytes) const;
    [[nodiscard]] int getNumberOfPixelsForOneByte() const;
    [[nodiscard]] int getMaximumNumberOfPixelsBeforeOneByte() const;
    [[nodiscard]] int getMinimumNumberOfBytesForOnePixel() const;
    [[nodiscard]] int getEstimatedSquareSideInPixels(int const numberOfBytesToRead) const;
    [[nodiscard]] int getOneRowSizeInBytesFromPixels(int const leftPixelInclusive, int const rightPixelInclusive) const;
    [[nodiscard]] int getOneRowSizeInBytesFromBytes(int const leftByteInclusive, int const rightByteInclusive) const;

    [[nodiscard]] Colors getColorTable() const;

    void readBitmap(std::string const& path);

private:
    void readBitmapFileHeader(AlbaFileReader& fileReader);
    void readDibHeader(AlbaFileReader& fileReader);
    void readColors(AlbaFileReader& fileReader);
    void calculateOtherValuesAfterReading();
    static CompressedMethodType determineCompressedMethodType(uint32_t compressedMethodValue);
    uint32_t m_fileSize;
    uint32_t m_pixelArrayAddress;
    uint32_t m_sizeOfHeader;
    uint32_t m_bitmapWidth;
    uint32_t m_bitmapHeight;
    uint16_t m_numberOfColorPlanes;
    uint16_t m_numberOfBitsPerPixel;
    CompressedMethodType m_compressionMethodType;
    uint32_t m_imageSize;
    uint64_t m_bitmapSize;
    uint32_t m_horizontalResolutionPixelInAMeter;
    uint32_t m_verticalResolutionPixelInAMeter;
    uint32_t m_numberOfColors;
    uint32_t m_numberImportantOfColors;
    uint32_t m_numberOfBytesForDataInRow;
    uint32_t m_paddingForRowMemoryAlignment;
    uint32_t m_numberOfBytesPerRowInFile;
    uint32_t m_bitMaskForValue;
    std::string m_path;
    std::string m_signature;
    Colors m_colors;
};

bool areBitmapConfigurationsCompatibleForChangingPixelData(
    BitmapConfiguration const& configuration1, BitmapConfiguration const& configuration2);

}  // namespace alba::AprgBitmap
