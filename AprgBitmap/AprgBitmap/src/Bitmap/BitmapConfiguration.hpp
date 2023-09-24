#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <Common/File/AlbaFileReader.hpp>

#include <cstdint>
#include <filesystem>
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
    [[nodiscard]] BitmapXY getPointWithinTheBitmap(int const xCoordinate, int const yCoordinate) const;
    [[nodiscard]] BitmapXY getDownRightCornerPoint() const;
    [[nodiscard]] Colors getColorTable() const;
    [[nodiscard]] CompressedMethodType getCompressedMethodType() const;
    [[nodiscard]] std::filesystem::path getPath() const;
    [[nodiscard]] int getXCoordinateWithinTheBitmap(int const coordinate) const;
    [[nodiscard]] int getYCoordinateWithinTheBitmap(int const coordinate) const;
    [[nodiscard]] int convertPixelsToBytesRoundedToFloor(int const pixels) const;
    [[nodiscard]] int convertPixelsToBytesRoundedToCeil(int const pixels) const;
    [[nodiscard]] int convertBytesToPixels(int const bytes) const;
    [[nodiscard]] int getNumberOfPixelsForOneByte() const;
    [[nodiscard]] int getMaximumNumberOfPixelsBeforeOneByte() const;
    [[nodiscard]] int getMinimumNumberOfBytesForOnePixel() const;
    [[nodiscard]] int getEstimatedSquareSideInPixels(int const numberOfBytesToRead) const;
    [[nodiscard]] int getOneRowSizeInBytesFromPixels(int const leftPixelInclusive, int const rightPixelInclusive) const;
    [[nodiscard]] int getOneRowSizeInBytesFromBytes(int const leftByteInclusive, int const rightByteInclusive) const;
    [[nodiscard]] uint16_t getNumberOfBitsPerPixel() const;
    [[nodiscard]] uint32_t getPixelArrayAddress() const;
    [[nodiscard]] uint32_t getBitmapWidth() const;
    [[nodiscard]] uint32_t getBitmapHeight() const;
    [[nodiscard]] uint32_t getNumberOfBytesPerRowInFile() const;
    [[nodiscard]] uint32_t getBitMaskForValue() const;
    [[nodiscard]] uint32_t getColorUsingPixelValue(uint32_t const pixelValue) const;
    [[nodiscard]] bool isValid() const;
    [[nodiscard]] bool isSignatureValid() const;
    [[nodiscard]] bool isHeaderValid() const;
    [[nodiscard]] bool isNumberOfColorPlanesValid() const;
    [[nodiscard]] bool isNumberOfBitsPerPixelValid() const;
    [[nodiscard]] bool isCompressedMethodSupported() const;
    [[nodiscard]] bool isPositionWithinTheBitmap(BitmapXY const position) const;
    [[nodiscard]] bool isPositionWithinTheBitmap(int const x, int const y) const;
    void readBitmap(std::filesystem::path const& path);
    static BitmapXY getUpLeftCornerPoint();
    static int getCoordinateWithinRange(int const coordinate, int const maxLength);

private:
    void readBitmapFileHeader(AlbaFileReader& fileReader);
    void readDibHeader(AlbaFileReader& fileReader);
    void readColors(AlbaFileReader& fileReader);
    void calculateOtherValuesAfterReading();
    static CompressedMethodType determineCompressedMethodType(uint32_t const compressedMethodValue);
    uint32_t m_fileSize{0};
    uint32_t m_pixelArrayAddress{0};
    uint32_t m_sizeOfHeader{0};
    uint32_t m_bitmapWidth{0};
    uint32_t m_bitmapHeight{0};
    uint16_t m_numberOfColorPlanes{0};
    uint16_t m_numberOfBitsPerPixel{8};
    CompressedMethodType m_compressionMethodType{CompressedMethodType::Unknown};
    uint32_t m_imageSize{0};
    uint64_t m_bitmapSize{0};
    uint32_t m_horizontalResolutionPixelInAMeter{0};
    uint32_t m_verticalResolutionPixelInAMeter{0};
    uint32_t m_numberOfColors{0};
    uint32_t m_numberImportantOfColors{0};
    uint32_t m_numberOfBytesForDataInRow{0};
    uint32_t m_paddingForRowMemoryAlignment{0};
    uint32_t m_numberOfBytesPerRowInFile{0};
    uint32_t m_bitMaskForValue{0};
    std::filesystem::path m_path;
    std::string m_signature;
    Colors m_colors;
};

bool areBitmapConfigurationsCompatibleForChangingPixelData(
    BitmapConfiguration const& configuration1, BitmapConfiguration const& configuration2);

}  // namespace alba::AprgBitmap
