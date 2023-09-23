#include "BitmapSnippet.hpp"

#include <Common/Bit/AlbaBitConstants.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>

using namespace std;

namespace alba::AprgBitmap {

BitmapSnippet::BitmapSnippet(
    BitmapXY const topLeftCornerPosition, BitmapXY const bottomRightCornerPosition,
    BitmapConfiguration const& configuration)
    : m_topLeftCorner(topLeftCornerPosition),
      m_bottomRightCorner(bottomRightCornerPosition),
      m_configuration(configuration) {
    loadPixelDataFromFileInConfiguration();
}

BitmapConfiguration BitmapSnippet::getConfiguration() const { return m_configuration; }
BitmapXY BitmapSnippet::getTopLeftCorner() const { return m_topLeftCorner; }
BitmapXY BitmapSnippet::getBottomRightCorner() const { return m_bottomRightCorner; }
PixelData const& BitmapSnippet::getPixelDataConstReference() const { return m_pixelData; }

uint32_t BitmapSnippet::getPixelAt(BitmapXY const position) const {
    uint32_t result(0);
    if (isPositionInsideTheSnippet(position)) {
        int const index = calculateIndexInPixelData(position);
        auto const* reader = static_cast<uint8_t const*>(m_pixelData.getConstantBufferPointer());
        if (m_configuration.getNumberOfBitsPerPixel() < AlbaBitConstants::BYTE_SIZE_IN_BITS) {
            result = getPixelAtForPixelInAByte(reader, index, position);
        } else {
            result = getPixelAtForMultipleBytePixels(reader, index);
        }
    }
    return result;
}

uint32_t BitmapSnippet::getColorAt(BitmapXY const position) const {
    return m_configuration.getColorUsingPixelValue(getPixelAt(position));
}

int BitmapSnippet::getDeltaX() const { return m_bottomRightCorner.getX() - m_topLeftCorner.getX(); }
int BitmapSnippet::getDeltaY() const { return m_bottomRightCorner.getY() - m_topLeftCorner.getY(); }
int BitmapSnippet::getNumberOfPixelsInSnippet() const { return getDeltaX() * getDeltaY(); }
int BitmapSnippet::getPixelDataSize() const { return static_cast<int>(m_pixelData.getSize()); }

bool BitmapSnippet::isPositionInsideTheSnippet(BitmapXY const position) const {
    return m_topLeftCorner.getX() <= position.getX() && m_topLeftCorner.getY() <= position.getY() &&
           m_bottomRightCorner.getX() >= position.getX() && m_bottomRightCorner.getY() >= position.getY();
}

bool BitmapSnippet::isBlackAt(BitmapXY const position) const {
    // this is the only assumption, colors can depend on numberofbits of pixel and color table
    return (m_configuration.getColorUsingPixelValue(getPixelAt(position)) == 0x00000000);
}

void BitmapSnippet::traverse(TraverseFunction const& traverseFunction) const {
    for (int y = m_topLeftCorner.getY(); y <= m_bottomRightCorner.getY(); ++y) {
        for (int x = m_topLeftCorner.getX(); x <= m_bottomRightCorner.getX(); ++x) {
            BitmapXY const currentPoint(x, y);
            traverseFunction(currentPoint, getPixelAt(currentPoint));
        }
    }
}

void BitmapSnippet::loadPixelDataFromFileInConfiguration() {
    if (m_configuration.isPositionWithinTheBitmap(m_topLeftCorner) &&
        m_configuration.isPositionWithinTheBitmap(m_bottomRightCorner)) {
        ifstream inputStream(m_configuration.getPath(), ios::binary);
        AlbaFileReader fileReader(inputStream);
        if (inputStream.is_open()) {
            int const byteOffsetInXForStart =
                static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(m_topLeftCorner.getX()));
            int const byteOffsetInXForEnd =
                static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(m_bottomRightCorner.getX()));
            int const offsetInYForStart =
                static_cast<int>(m_configuration.getBitmapHeight()) - static_cast<int>(m_topLeftCorner.getY()) - 1;
            int const offsetInYForEnd =
                static_cast<int>(m_configuration.getBitmapHeight()) - static_cast<int>(m_bottomRightCorner.getY()) - 1;
            int const numberOfBytesToBeCopiedForX = static_cast<int>(
                m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd));

            for (int y = offsetInYForStart; y >= offsetInYForEnd; --y) {
                uint64_t const fileOffsetForStart =
                    m_configuration.getPixelArrayAddress() +
                    (static_cast<uint64_t>(m_configuration.getNumberOfBytesPerRowInFile()) * y) + byteOffsetInXForStart;
                fileReader.moveLocation(fileOffsetForStart);
                fileReader.saveDataToMemoryBuffer(m_pixelData, numberOfBytesToBeCopiedForX);
            }
        }
    }
}

void BitmapSnippet::clear() { m_pixelData.clear(); }

void BitmapSnippet::clearAndPutOneColorOnWholeSnippet(uint8_t const colorByte) {
    clear();

    int const byteOffsetInXForStart =
        static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(m_topLeftCorner.getX()));
    int const byteOffsetInXForEnd =
        static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(m_bottomRightCorner.getX()));
    int const numberOfBytesToBeCopiedForX =
        static_cast<int>(m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd));
    int const yDifference = static_cast<int>(m_bottomRightCorner.getY()) - static_cast<int>(m_topLeftCorner.getY()) + 1;
    m_pixelData.resize(numberOfBytesToBeCopiedForX * yDifference, colorByte);
}

void BitmapSnippet::setPixelAt(BitmapXY const position, uint32_t const value) {
    if (isPositionInsideTheSnippet(position)) {
        int const index = calculateIndexInPixelData(position);
        auto* writer = static_cast<uint8_t*>(m_pixelData.getBufferPointer());
        if (m_configuration.getNumberOfBitsPerPixel() < AlbaBitConstants::BYTE_SIZE_IN_BITS) {
            setPixelAtForPixelInAByte(writer, index, position, value);
        } else {
            setPixelAtForMultipleBytePixels(writer, index, value);
        }
    }
}

void BitmapSnippet::traverseAndUpdate(TraverseAndUpdateFunction const& traverseAndUpdateFunction) {
    for (int x = m_topLeftCorner.getX(); x <= m_bottomRightCorner.getX(); ++x) {
        for (int y = m_topLeftCorner.getY(); y <= m_bottomRightCorner.getY(); ++y) {
            BitmapXY const currentPoint(x, y);
            uint32_t colorToBeUpdated(getPixelAt(currentPoint));
            traverseAndUpdateFunction(currentPoint, colorToBeUpdated);
            setPixelAt(currentPoint, colorToBeUpdated);
        }
    }
}

PixelData& BitmapSnippet::getPixelDataReference() { return m_pixelData; }

int BitmapSnippet::calculateShiftValue(BitmapXY const position) const {
    int const numberOfPixelsInOneByte = m_configuration.getNumberOfPixelsForOneByte();
    int const numberOfBitsPerPixel = m_configuration.getNumberOfBitsPerPixel();
    int const positionRemainder = position.getX() % numberOfPixelsInOneByte;
    int const loopAround = numberOfPixelsInOneByte - positionRemainder - 1;
    return numberOfBitsPerPixel * loopAround;
}

int BitmapSnippet::calculateIndexInPixelData(BitmapXY const position) const {
    int const xPartInIndex = m_configuration.convertPixelsToBytesRoundedToFloor(position.getX()) -
                             m_configuration.convertPixelsToBytesRoundedToFloor(m_topLeftCorner.getX());
    int const oneRowOffset =
        m_configuration.getOneRowSizeInBytesFromPixels(m_topLeftCorner.getX(), m_bottomRightCorner.getX());
    int const yPartInIndex = oneRowOffset * (position.getY() - m_topLeftCorner.getY());
    return xPartInIndex + yPartInIndex;
}

uint32_t BitmapSnippet::getPixelAtForPixelInAByte(
    uint8_t const* reader, int const index, BitmapXY const position) const {
    uint32_t result(0);
    if (index < static_cast<int>(m_pixelData.getSize())) {
        result = static_cast<uint32_t>(*(reader + index));
        int const shiftValue = calculateShiftValue(position);
        result = (result >> shiftValue) & m_configuration.getBitMaskForValue();
    }
    return result;
}

uint32_t BitmapSnippet::getPixelAtForMultipleBytePixels(uint8_t const* reader, int const index) const {
    uint32_t result(0);
    int const minimumNumberOfBytesForOnePixel = m_configuration.getMinimumNumberOfBytesForOnePixel();
    if (index + minimumNumberOfBytesForOnePixel - 1 < static_cast<int>(m_pixelData.getSize())) {
        for (int indexForMultipleBytePixel = static_cast<int>(minimumNumberOfBytesForOnePixel) - 1;
             indexForMultipleBytePixel >= 0; --indexForMultipleBytePixel) {
            result <<= AlbaBitConstants::BYTE_SIZE_IN_BITS;
            result = result | static_cast<uint32_t>(*(reader + index + indexForMultipleBytePixel));
        }
    }
    return result;
}

void BitmapSnippet::setPixelAtForPixelInAByte(
    uint8_t* writer, int const index, BitmapXY const position, uint32_t const value) {
    if (index < static_cast<int>(m_pixelData.getSize())) {
        auto oldValue = static_cast<uint32_t>(*(writer + index));
        int const shiftValue = calculateShiftValue(position);
        uint32_t const replacePart = (m_configuration.getBitMaskForValue() & value) << shiftValue;
        uint32_t const retainMask =
            (m_configuration.getBitMaskForValue() << shiftValue) ^ AlbaBitValueUtilities<uint32_t>::getAllOnes();
        uint32_t const retainPart = (retainMask & oldValue);
        *(writer + index) = replacePart | retainPart;
    }
}

void BitmapSnippet::setPixelAtForMultipleBytePixels(uint8_t* writer, int const index, uint32_t const value) {
    uint32_t valueToSave(value);
    int const minimumNumberOfBytesForOnePixel = m_configuration.getMinimumNumberOfBytesForOnePixel();
    if (index + minimumNumberOfBytesForOnePixel - 1 < static_cast<int>(m_pixelData.getSize())) {
        for (int indexForMultipleBytePixel = 0; indexForMultipleBytePixel < minimumNumberOfBytesForOnePixel;
             ++indexForMultipleBytePixel) {
            *(writer + index + indexForMultipleBytePixel) = valueToSave & AlbaBitConstants::BYTE_MASK;
            valueToSave >>= AlbaBitConstants::BYTE_SIZE_IN_BITS;
        }
    }
}

BitmapSnippet::BitmapSnippet() = default;

}  // namespace alba::AprgBitmap
