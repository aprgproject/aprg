#include "Utilities.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

double calculateColorIntensityDecimal(uint32_t const color) {
    return (static_cast<double>(static_cast<uint32_t>(extractRed(color)) + extractGreen(color) + extractBlue(color)) /
            0xFF) /
           3;
}

XY convertToXY(BitmapXY const& bitmapXY) { return bitmapXY; }
BitmapXY convertToBitmapXY(XY const& xy) { return xy; }
uint8_t extractRed(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<2>(color)); }
uint8_t extractGreen(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<1>(color)); }
uint8_t extractBlue(uint32_t const color) { return (AlbaBitManipulation<uint32_t>::getByteAt<0>(color)); }

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba
