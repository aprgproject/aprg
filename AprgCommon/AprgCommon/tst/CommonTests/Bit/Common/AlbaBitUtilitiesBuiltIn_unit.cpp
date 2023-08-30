#include <Common/Bit/Common/AlbaBitUtilitiesBuiltIn.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaBitUtilitiesBuiltInTest, IsEvenParityWorks) {
    EXPECT_TRUE(bitUtilitiesBuiltIn::isEvenParity(0U));
    EXPECT_FALSE(bitUtilitiesBuiltIn::isEvenParity(1U));
    EXPECT_FALSE(bitUtilitiesBuiltIn::isEvenParity(2U));
    EXPECT_TRUE(bitUtilitiesBuiltIn::isEvenParity(3U));
    EXPECT_FALSE(bitUtilitiesBuiltIn::isEvenParity(4U));
}

TEST(AlbaBitUtilitiesBuiltInTest, IsEvenParityWorksUsingWithoutBuiltIn) {
    EXPECT_TRUE(bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::isEvenParity(0U));
    EXPECT_FALSE(bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::isEvenParity(1U));
    EXPECT_FALSE(bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::isEvenParity(2U));
    EXPECT_TRUE(bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::isEvenParity(3U));
    EXPECT_FALSE(bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::isEvenParity(4U));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfOnesWorks) {
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfOnes<uint8_t>(0xA1U));
    EXPECT_EQ(8U, bitUtilitiesBuiltIn::getNumberOfOnes<uint16_t>(0xA1BAU));
    EXPECT_EQ(16U, bitUtilitiesBuiltIn::getNumberOfOnes<uint32_t>(0xA1BA'A1BAU));
    EXPECT_EQ(32U, bitUtilitiesBuiltIn::getNumberOfOnes<uint64_t>(0xA1BA'A1BA'A1BA'A1BAULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfOnesWorksUsingWithoutBuiltIn) {
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfOnes<uint8_t>(0xA1U));
    EXPECT_EQ(8U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfOnes<uint16_t>(0xA1BAU));
    EXPECT_EQ(16U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfOnes<uint32_t>(0xA1BA'A1BAU));
    EXPECT_EQ(
        32U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfOnes<uint64_t>(0xA1BA'A1BA'A1BA'A1BAULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfConsecutiveZerosFromMsbWorks) {
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x80U));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x10U));
    EXPECT_EQ(7U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x01U));
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x8000U));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x1000U));
    EXPECT_EQ(15U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x0001U));
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x8000'0000U));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x1000'0000U));
    EXPECT_EQ(31U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x0000'0001U));
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x8000'0000'0000'0000ULL));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x1000'0000'0000'0000ULL));
    EXPECT_EQ(63U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x0000'0000'0000'0001ULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfConsecutiveZerosFromMsbWorksUsingWithoutBuiltIn) {
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x80U));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x10U));
    EXPECT_EQ(7U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x01U));
    EXPECT_EQ(
        0U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x8000U));
    EXPECT_EQ(
        3U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x1000U));
    EXPECT_EQ(
        15U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x0001U));
    EXPECT_EQ(
        0U,
        bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x8000'0000U));
    EXPECT_EQ(
        3U,
        bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x1000'0000U));
    EXPECT_EQ(
        31U,
        bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x0000'0001U));
    EXPECT_EQ(
        0U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(
                0x8000'0000'0000'0000ULL));
    EXPECT_EQ(
        3U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(
                0x1000'0000'0000'0000ULL));
    EXPECT_EQ(
        63U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(
                 0x0000'0000'0000'0001ULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfConsecutiveZerosFromLsbWorks) {
    EXPECT_EQ(7U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x80U));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x08U));
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x01U));
    EXPECT_EQ(15U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x8000U));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x0008U));
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x0001U));
    EXPECT_EQ(31U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x8000'0000U));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x0000'0008U));
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x0000'0001U));
    EXPECT_EQ(63U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x8000'0000'0000'0000ULL));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x0000'0000'0000'0008ULL));
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x0000'0000'0000'0001ULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfConsecutiveZerosFromLsbWorksUsingWithoutBuiltIn) {
    EXPECT_EQ(7U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x80U));
    EXPECT_EQ(3U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x08U));
    EXPECT_EQ(0U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x01U));
    EXPECT_EQ(
        15U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x8000U));
    EXPECT_EQ(
        3U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x0008U));
    EXPECT_EQ(
        0U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x0001U));
    EXPECT_EQ(
        31U,
        bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x8000'0000U));
    EXPECT_EQ(
        3U,
        bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x0000'0008U));
    EXPECT_EQ(
        0U,
        bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x0000'0001U));
    EXPECT_EQ(
        63U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(
                 0x8000'0000'0000'0000ULL));
    EXPECT_EQ(
        3U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(
                0x0000'0000'0000'0008ULL));
    EXPECT_EQ(
        0U, bitUtilitiesBuiltIn::bitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(
                0x0000'0000'0000'0001ULL));
}

}  // namespace alba
