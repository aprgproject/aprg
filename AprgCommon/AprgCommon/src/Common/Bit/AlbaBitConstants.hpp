#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>

namespace alba::AlbaBitConstants {
// user defined constants:
inline constexpr std::size_t NIBBLE_SIZE_IN_BITS = 4;
inline constexpr std::size_t NUMBER_OF_NIBBLES_IN_BYTE = 2;
inline constexpr uint8_t ALL_ONES_8_BITS = 0xFF;
inline constexpr uint16_t ALL_ONES_16_BITS = 0xFFFF;
inline constexpr uint32_t ALL_ONES_32_BITS = 0xFFFFFFFF;
inline constexpr uint64_t ALL_ONES_64_BITS = 0xFFFFFFFF'FFFFFFFF;
inline constexpr uint8_t ZERO_THEN_ONE_8_BITS = 0xAA;
inline constexpr uint16_t ZERO_THEN_ONE_16_BITS = 0xAAAA;
inline constexpr uint32_t ZERO_THEN_ONE_32_BITS = 0xAAAAAAAA;
inline constexpr uint64_t ZERO_THEN_ONE_64_BITS = 0xAAAAAAAA'AAAAAAAA;
inline constexpr uint8_t ONE_THEN_ZERO_8_BITS = 0x55;
inline constexpr uint16_t ONE_THEN_ZERO_16_BITS = 0x5555;
inline constexpr uint32_t ONE_THEN_ZERO_32_BITS = 0x55555555;
inline constexpr uint64_t ONE_THEN_ZERO_64_BITS = 0x55555555'55555555;
inline constexpr uint8_t NIBBLE_MASK = 0B00001111;  // digit separator carat ' cannot be used for binary literal
inline constexpr uint8_t BIT_MASK = 0B00000001;
// defined in climits
inline constexpr std::size_t BYTE_SIZE_IN_BITS = CHAR_BIT;  // 8
inline constexpr std::size_t BYTE_MASK = UCHAR_MAX;         // 0xFF or 255
}  // namespace alba::AlbaBitConstants
