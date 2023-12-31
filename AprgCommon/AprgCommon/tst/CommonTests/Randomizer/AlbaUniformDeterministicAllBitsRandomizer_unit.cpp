#include <Common/Randomizer/AlbaUniformDeterministicAllBitsRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

namespace {
using IntegerRandomizerForTest = AlbaUniformDeterministicAllBitsRandomizer<int>;
using FloatingPointRandomizerForTest = AlbaUniformDeterministicAllBitsRandomizer<double>;
}  // namespace

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, SetRandomSeedWorks) {
    constexpr auto minimumValue(static_cast<long long>(numeric_limits<int>::min()));
    constexpr auto maximumValue(static_cast<long long>(numeric_limits<int>::max()));
    constexpr double customSeed(10);
    IntegerRandomizerForTest randomizer(customSeed);

    constexpr int newCustomSeed(42);
    randomizer.setRandomSeed(newCustomSeed);

    for (int i = 0; i < 1000; ++i) {
        auto randomValue(static_cast<long long>(randomizer.getRandomValue()));
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

// Dont test if uniformly distributed because its too large just trust the C++ implementation
TEST(AlbaUniformDeterministicAllBitsRandomizerTest, DefaultConstructorWorks) {
    IntegerRandomizerForTest randomizer;

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
    EXPECT_NO_FATAL_FAILURE(randomizer.getRandomValue());
}

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, GetRandomIntegerWorksWithinMinimumAndMaximumValues) {
    constexpr auto minimumValue(static_cast<long long>(numeric_limits<int>::min()));
    constexpr auto maximumValue(static_cast<long long>(numeric_limits<int>::max()));
    constexpr int customSeed(5);
    IntegerRandomizerForTest randomizer(customSeed);

    for (int i = 0; i < 1000; ++i) {
        auto randomValue(static_cast<long long>(randomizer.getRandomValue()));
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, GetRandomIntegerWorksAsDeterministic) {
    constexpr int customSeed(5);
    IntegerRandomizerForTest randomizer1(customSeed);
    IntegerRandomizerForTest randomizer2(customSeed);

    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(randomizer1.getRandomValue(), randomizer2.getRandomValue());
    }
}

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, GetRandomFloatingValueWorksAsDeterministic) {
    constexpr double customSeed(10);
    FloatingPointRandomizerForTest randomizer1(customSeed);
    FloatingPointRandomizerForTest randomizer2(customSeed);

    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(randomizer1.getRandomValue(), randomizer2.getRandomValue());
    }
}

}  // namespace alba
