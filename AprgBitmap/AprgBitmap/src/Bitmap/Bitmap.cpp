#include "Bitmap.hpp"

using namespace std;
using namespace std::filesystem;

namespace alba::AprgBitmap {

Bitmap::Bitmap(path const& filePath) { m_configuration.readBitmap(filePath); }
BitmapConfiguration Bitmap::getConfiguration() const { return m_configuration; }

BitmapSnippet Bitmap::createColorFilledSnippetWithSizeOfWholeBitmap(uint8_t const colorByte) const {
    BitmapSnippet snippet(
        alba::AprgBitmap::BitmapConfiguration::getUpLeftCornerPoint(), m_configuration.getDownRightCornerPoint(),
        m_configuration);
    snippet.clearAndPutOneColorOnWholeSnippet(colorByte);
    return snippet;
}

BitmapSnippet Bitmap::getSnippetReadFromFileWholeBitmap() const {
    return getSnippetReadFromFile(
        alba::AprgBitmap::BitmapConfiguration::getUpLeftCornerPoint(), m_configuration.getDownRightCornerPoint());
}

BitmapSnippet Bitmap::getSnippetReadFromFileWithOutOfRangeCoordinates(
    int const outOfRangeLeft, int const outOfRangeTop, int const outOfRangeRight, int const outOfRangeBottom) const {
    int left = outOfRangeLeft;
    int top = outOfRangeTop;
    int right = outOfRangeRight;
    int bottom = outOfRangeBottom;
    if (left > right) {
        swap(left, right);
    }
    if (top > bottom) {
        swap(top, bottom);
    }
    BitmapXY const topLeftCorner = m_configuration.getPointWithinTheBitmap(left, top);
    BitmapXY const bottomRightCorner = m_configuration.getPointWithinTheBitmap(right, bottom);
    return getSnippetReadFromFile(topLeftCorner, bottomRightCorner);
}

BitmapSnippet Bitmap::getSnippetReadFromFileWithNumberOfBytesToRead(
    BitmapXY const center, int const numberOfBytesToRead) const {
    BitmapSnippet snippet;
    if (m_configuration.isPositionWithinTheBitmap(center)) {
        BitmapXY topLeftCorner;
        BitmapXY bottomRightCorner;
        calculateNewCornersBasedOnCenterAndNumberOfBytes(topLeftCorner, bottomRightCorner, center, numberOfBytesToRead);
        snippet = getSnippetReadFromFile(topLeftCorner, bottomRightCorner);
    }
    return snippet;
}

BitmapSnippet Bitmap::getSnippetReadFromFile(BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const {
    int const byteOffsetInXForStart =
        static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(topLeftCorner.getX()));
    int const byteOffsetInXForEnd =
        static_cast<int>(m_configuration.convertPixelsToBytesRoundedToFloor(bottomRightCorner.getX()));
    int const startPixelInX = static_cast<int>(m_configuration.getXCoordinateWithinTheBitmap(
        static_cast<int>(m_configuration.convertBytesToPixels(byteOffsetInXForStart))));
    int const endPixelInX = static_cast<int>(m_configuration.getXCoordinateWithinTheBitmap(static_cast<int>(
        m_configuration.convertBytesToPixels(byteOffsetInXForEnd) +
        m_configuration.getMaximumNumberOfPixelsBeforeOneByte())));

    return {
        BitmapXY(startPixelInX, topLeftCorner.getY()), BitmapXY(endPixelInX, bottomRightCorner.getY()),
        m_configuration};
}

void Bitmap::setSnippetWriteToFile(BitmapSnippet const& snippet) const {
    if (areBitmapConfigurationsCompatibleForChangingPixelData(m_configuration, snippet.getConfiguration())) {
        if (m_configuration.isPositionWithinTheBitmap(snippet.getTopLeftCorner()) &&
            m_configuration.isPositionWithinTheBitmap(snippet.getBottomRightCorner())) {
            fstream streamFile(m_configuration.getPath(), fstream::in | fstream::out | fstream::binary);
            if (streamFile.is_open()) {
                int const byteOffsetInXForStart = static_cast<int>(
                    m_configuration.convertPixelsToBytesRoundedToFloor(snippet.getTopLeftCorner().getX()));
                int const byteOffsetInXForEnd = static_cast<int>(
                    m_configuration.convertPixelsToBytesRoundedToFloor(snippet.getBottomRightCorner().getX()));
                int const offsetInYForStart = static_cast<int>(m_configuration.getBitmapHeight()) -
                                              static_cast<int>(snippet.getTopLeftCorner().getY()) - 1;
                int const offsetInYForEnd = static_cast<int>(m_configuration.getBitmapHeight()) -
                                            static_cast<int>(snippet.getBottomRightCorner().getY()) - 1;
                int const numberOfBytesToBeCopiedForX = static_cast<int>(
                    m_configuration.getOneRowSizeInBytesFromBytes(byteOffsetInXForStart, byteOffsetInXForEnd));
                int const snippetSize = snippet.getPixelDataSize();
                int snippetIndex = 0;

                for (int y = offsetInYForStart; y >= offsetInYForEnd && snippetIndex < snippetSize; --y) {
                    uint64_t const fileOffsetForStart =
                        m_configuration.getPixelArrayAddress() +
                        (static_cast<uint64_t>(m_configuration.getNumberOfBytesPerRowInFile()) * y) +
                        byteOffsetInXForStart;
                    char const* pixelDataPointer =
                        static_cast<char const*>(snippet.getPixelDataConstReference().getConstantBufferPointer()) +
                        snippetIndex;
                    streamFile.seekg(static_cast<fstream::off_type>(fileOffsetForStart), std::fstream::beg);
                    streamFile.write(pixelDataPointer, numberOfBytesToBeCopiedForX);
                    snippetIndex += numberOfBytesToBeCopiedForX;
                }
                streamFile.flush();
            }
        }
    }
}

void Bitmap::calculateNewCornersBasedOnCenterAndNumberOfBytes(
    BitmapXY& topLeftCorner, BitmapXY& bottomRightCorner, BitmapXY const center, int const numberOfBytes) const {
    int const side(static_cast<int>(m_configuration.getEstimatedSquareSideInPixels(numberOfBytes)));
    int const halfSide(side / 2);
    int left(
        static_cast<int>(m_configuration.getXCoordinateWithinTheBitmap(static_cast<int>(center.getX()) - halfSide)));
    int right(
        static_cast<int>(m_configuration.getXCoordinateWithinTheBitmap(static_cast<int>(center.getX()) + halfSide)));
    adjustToTargetLength(left, right, side, static_cast<int>(m_configuration.getBitmapWidth()));

    int xSizeInBytes(static_cast<int>(m_configuration.getOneRowSizeInBytesFromPixels(left, right)));
    xSizeInBytes = (xSizeInBytes > 0) ? xSizeInBytes : 1;
    int const ySizeInBytes(static_cast<int>(numberOfBytes / xSizeInBytes));
    int const halfYSizeInBytes(ySizeInBytes / 2);
    int top(static_cast<int>(
        m_configuration.getYCoordinateWithinTheBitmap(static_cast<int>(center.getY()) - halfYSizeInBytes)));
    int bottom(static_cast<int>(
        m_configuration.getYCoordinateWithinTheBitmap(static_cast<int>(center.getY()) + halfYSizeInBytes)));
    adjustToTargetLength(top, bottom, ySizeInBytes, static_cast<int>(m_configuration.getBitmapHeight()));

    topLeftCorner.setX(left);
    topLeftCorner.setY(top);
    bottomRightCorner.setX(right);
    bottomRightCorner.setY(bottom);
}

void Bitmap::adjustToTargetLength(int& low, int& high, int const targetLength, int const maxLength) {
    if (high - low + 1 < targetLength) {
        int const additionalSizeInX = targetLength - (high - low + 1);
        if ((low - additionalSizeInX) >= 0) {
            low = low - additionalSizeInX;
        } else if ((high + additionalSizeInX) < maxLength) {
            high = high + additionalSizeInX;
        }
    }
}

}  // namespace alba::AprgBitmap
