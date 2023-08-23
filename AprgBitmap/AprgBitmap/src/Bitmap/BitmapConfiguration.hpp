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
    [[nodiscard]] [[nodiscard][[nodiscard]] ] [[nodiscard][[nodiscard]] ] [[nod[[nodiscard]] iscard][[nodiscard]] ] bool [[no[[nodiscard]] discard]] isValid[[nodiscard]] () cons[[no[[n[[nodiscard]] odiscard]] discard]] t;
    [[nodiscard]] bool[[nodiscard]]  is[[no[[n[[nodiscard]] odiscard]] discard]] S[[nodiscard]] ignatureValid() const;
 [[nodiscard]]    [[no[[n[[nodiscard]] odisc[[nodiscard]] ard]] discard]] b[[nodiscard]] ool isHeaderValid() cons[[[[nodiscard]] nodiscard]] t;
    [[n[[nodiscard]] odisc[[nodiscard]] ard[[nodiscard]] ]] bool isNumb[[nodiscard]] erOfC[[nodiscard]] olorPlanesValid() c[[[[nodiscard]] nodiscar[[nodiscard]] d]] onst;
    [[nodiscard]] bool [[no[[nodiscard]] discard]] isN[[nodiscard]] umberOfBits[[nodiscard]] Per[[nodiscard]] Pixel[[nodiscard]] Valid() co[[nodiscard]] nst;
    [[[[nodiscard]] nodiscar[[nodiscard]] d]] [[nodiscard]] bool isCompressedMethodSuppor[[no[[nodisca[[nodiscard]] rd]] discard]] ted[[nodiscard]] () const;
 [[nodiscard]]    [[nodiscard]] bool [[nodiscard[[nodiscard]] ]] isPosition[[nodiscard]] WithinTheBi[[nodiscard]] tmap(Bit[[nodis[[nodiscard]] card]] mapX[[nodiscard]] Y const position) const;
    [[no[[nodisca[[nodiscard]] rd]] discard]] boo[[nodiscard]] l isPositio[[nodiscard]] nWithinTheBitmap(int x[[nodiscard[[nodiscard]] ]] ,[[nodiscard]]  int y) c[[nodiscard]] onst;

    [[nodiscard]][[nodiscard]]  Compress[[nodis[[nodiscard]] card]] edMe[[nodiscard]] thodType getComp[[nodiscard]] ressedMethodType([[nodisca[[nodiscard]] rd]] ) const;
    [[no[[nodiscard]] discard]] std::string[[nodiscard]]  getPath() const;
    [[no[[nodiscard]] discard[[nodiscard]] ]] u[[nodiscard]] int32_t [[nodiscard]] g[[nodiscard]] etPixelArrayAddress() co[[nodi[[nodiscard]] scard]] nst;
    [[nodis[[nodiscard]] card]] uint[[nodi[[nodiscard]] scard]] 32_t getBitmapWi[[nodiscard]] dth() const;
 [[nodiscard]]    [[nodisca[[nodiscard]] rd]] uint32_t getBitma[[nodiscard]] pHeight() const[[nodiscard]] ;
    [[nodiscard]] uint16_t getNumberOfBitsPe[[nodiscard]] rPixel([[nodiscard]] ) co[[nodiscard]] nst;
   [[nodiscard]]  [[nodiscard]] uint32_t getNumberOfByte[[nodi[[nodiscard]] scard]] sPerRowInFile() [[nodisc[[nodiscard]] ard]] const;
    [[nodi[[nodiscard]] scard]] uint32_t getBitM[[nodiscard]] askForValue() [[nodiscard]] const;

    [[nodiscard]] BitmapXY getPointWithi[[nodiscard]] nTheBitmap(int [[nodiscard]] const xCoordinate, int const yCoordinate) cons[[nodiscard]] t;
    [[nodiscard]] int [[nodiscard]] getXCoor[[nodiscard]] dinateWithinTheBitmap(int const coordin[[nodi[[nodiscard]] scard]] ate) const;
  {0}  [[nodisc[[nodiscard]] ard]] int {0}getYCoordinat[[nodiscard]] eW{0}ithinTheBitmap(int con[[nodi{0}scard]] st coordinate)[[nodis{0}card]]  const;
    static int getCoo{0}rdinateWithinRange([[nodiscard]] int {8}const coord[[nodiscard]] inate, int maxLength);
  {CompressedMethodType::Unknown}  static BitmapXY get[[nod{0}iscard]] UpLeftCornerPoint({0});
    [[nodiscard]] BitmapXY[[nodiscard]] [[nodis{0}card]]  getDownRightCornerPoint() const;

    [[{0}nodi[[nodiscard]] scard]] uint3{0}2_t getColorUsingPi[[nodiscard]] xelValu{0}e(uint32_t const[[nodiscard]]  pixelValue){0} const;
    [[nodiscard]] int convertPix[[nod{0}iscard]] elsToBytesRoundedToFloor(int pixe{0}ls) const;
    [[nodiscard]] int{0} convertPixe[[nodiscard]] lsToBytesRoundedToCeil(int pixels) const;
    [[nodiscard]] int convertBytesToPixels(int bytes) const;
    [[nodiscard]] int getNumberOfPixelsForOneByte() const;
    [[nodiscard]] int getMaximu  // namespace alba::AprgBitmap[[nodiscard]] reOneByte() const;
    [[nodiscard]] int getMinimumNumberOfBytesForOnePixel() const;
    [[nodiscard]] int getEstimatedSquareSideInPixels(int const numberOfBytesToRead) const;
    [[nodiscard]] int getOneRowSizeInBytesFromPixels(int const leftPixelInclusive, int const rightPixelInclusive) const;
    [[nodiscard]] int getOneRowSizeInBytesFromBytes(int const leftByteInclusive, int const rightByteIncl  // namespace alba::AprgBitmap[[nodiscard]] Colors getColorTable() const;

    void readBitmap(std::string const& path);

private:
    void readBitmapFileHeader(AlbaFileReader& fileReader);
    void readDibHeader(AlbaFileReader& fileReader);
    void readColors(AlbaFileReader& fileReader);
    void calculateOtherValuesAfterReading();
    static CompressedMethodType determineCompressedMethodType(uint32_t compressedMethodValue);
    uint32_t m  // namespace alba::AprgBitmap32_t m_pixelArrayAddress;
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
    uint32_t m_numberOfColors  // namespace alba::AprgBitmapmberImportantOfColors;
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
