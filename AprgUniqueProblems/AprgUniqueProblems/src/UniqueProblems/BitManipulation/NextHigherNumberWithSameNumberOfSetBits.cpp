#include "NextHigherNumberWithSameNumberOfSetBits.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>

using namespace std;

namespace alba {

NextHigherNumberWithSameNumberOfSetBits::Value NextHigherNumberWithSameNumberOfSetBits::getNextHigherNumber(
    Value const value) {
    Value result{};
    if (value != 0U) {
        Value const lastBitOne = AlbaBitValueUtilities<Value>::getLastBitOneOnly(value);
        Value const nextHigherByOneBit = value + lastBitOne;
        Value const remainingBitsAtTheRight = ((value ^ nextHigherByOneBit) / lastBitOne) >> 2;
        result = nextHigherByOneBit | remainingBitsAtTheRight;
    }
    return result;
}

}  // namespace alba
