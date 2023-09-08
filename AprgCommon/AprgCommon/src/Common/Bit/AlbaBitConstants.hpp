#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>

namespace alba::AlbaBitConstants {

// user defined constants:
constexpr std::size_t NIBBLE_SIZE_IN_BITS = 4;
constexpr std::size_t NUMBER_OF_NIBBLES_IN_BYTE = 2;
constexpr uint8_t ALL_ONES_8_BITS = 0xFF;
constexpr uint16_t ALL_ONES_16_BITS = 0xFFFF;
constexpr uint32_t ALL_ONES_32_BITS = 0xFFFFFFFF;
constexpr uint64_t ALL_ONES_64_BITS = 0xFFFFFFFF'FFFFFFFF;
constexpr uint8_t ZERO_THEN_ONE_8_BITS = 0xAA;
constexpr uint16_t ZERO_THEN_ONE_16_BITS = 0xAAAA;
constexpr uint32_t ZERO_THEN_ONE_32_BITS = 0xAAAAAAAA;
constexpr uint64_t ZERO_THEN_ONE_64_BITS = 0xAAAAAAAA'AAAAAAAA;
constexpr uint8_t ONE_THEN_ZERO_8_BITS = 0x55;
constexpr uint16_t ONE_THEN_ZERO_16_BITS = 0x5555;
constexpr uint32_t ONE_THEN_ZERO_32_BITS = 0x55555555;
constexpr uint64_t ONE_THEN_ZERO_64_BITS = 0x55555555'55555555;
constexpr uint8_t NIBBLE_MASK = 0B00001111;  // digit separator carat ' cannot be used for binary literal
constexpr uint8_t BIT_MASK = 0B00000001;
// defined in climits
constexpr std::size_t BYTE_SIZE_IN_BITS = CHAR_BIT;  // 8
constexpr std::size_t BYTE_MASK = UCHAR_MAX;         // 0xFF or 255

}  // namespace alba::AlbaBitConstants
