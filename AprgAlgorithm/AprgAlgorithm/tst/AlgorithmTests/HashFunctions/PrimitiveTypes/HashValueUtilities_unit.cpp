#include <Algorithm/HashFunctions/PrimitiveTypes/HashValueUtilities.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

TEST(HashValueUtilitiesTest, GetHashUsingDivisionMethodWorks) {
    EXPECT_EQ(89ULL, (getHashUsingDivisionMethod<uint64_t>(123456789, 100)));
    EXPECT_EQ(597ULL, (getHashUsingDivisionMethod<uint64_t>(1999, 701)));
}

TEST(HashValueUtilitiesTest, GetHashUsingMultiplicationMethodWorksWithDouble) {
    double const knuthSuggestion = (sqrt(5) - 1) / 2;
    EXPECT_EQ(74ULL, (getHashUsingMultiplicationMethod<uint64_t>(123456789, 100, knuthSuggestion)));
    EXPECT_EQ(10315ULL, (getHashUsingMultiplicationMethod<uint64_t>(12345, 16384, knuthSuggestion)));
}

TEST(HashValueUtilitiesTest, GetHashUsingMultiplicationMethodWorksWithNumeratorAndDenominator) {
    constexpr uint64_t knuthNumerator = 475245693;
    constexpr uint64_t knuthDenominator = 2294689195;
    EXPECT_EQ(18ULL, (getHashUsingMultiplicationMethod<uint64_t>(123456789, 100, knuthNumerator, knuthDenominator)));
    EXPECT_EQ(12012ULL, (getHashUsingMultiplicationMethod<uint64_t>(12345, 16384, knuthNumerator, knuthDenominator)));
}

}  // namespace alba::algorithm
