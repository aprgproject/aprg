#include <Common/Randomizer/AlbaUniformDeterministicRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

namespace {
using IntegerRandomizerForTest = AlbaUniformDeterministicRandomizer<int>;
using FloatingPointRandomizerForTest = AlbaUniformDeterministicRandomizer<double>;
}  // namespace

TEST(AlbaUniformDeterministicRandomizerTest, SetMinimumAndMaximumWorks) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    IntegerRandomizerForTest randomizer;

    randomizer.setMinimumAndMaximum(minimumValue, maximumValue);

    for (int i = 0; i < 1000; ++i) {
        auto randomValue(randomizer.getRandomValue());
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

TEST(AlbaUniformDeterministicRandomizerTest, SetRandomSeedWorks) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    constexpr double customSeed(10);
    IntegerRandomizerForTest randomizer(minimumValue, maximumValue, customSeed);

    constexpr int newCustomSeed(42);
    randomizer.setRandomSeed(newCustomSeed);

    for (int i = 0; i < 1000; ++i) {
        auto randomValue(randomizer.getRandomValue());
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

TEST(AlbaUniformDeterministicRandomizerTest, DefaultConstructorWorks) {
    IntegerRandomizerForTest randomizer;

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
    EXPECT_NO_FATAL_FAILURE(randomizer.getRandomValue());
}

TEST(AlbaUniformDeterministicRandomizerTest, GetRandomIntegerWorksWithinMinimumAndMaximumValues) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    constexpr int customSeed(5);
    IntegerRandomizerForTest randomizer(minimumValue, maximumValue, customSeed);

    for (int i = 0; i < 1000; ++i) {
        auto randomValue(randomizer.getRandomValue());
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

TEST(AlbaUniformDeterministicRandomizerTest, GetRandomIntegerWorksAsDeterministic) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    constexpr int customSeed(5);
    IntegerRandomizerForTest randomizer1(minimumValue, maximumValue, customSeed);
    IntegerRandomizerForTest randomizer2(minimumValue, maximumValue, customSeed);

    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(randomizer1.getRandomValue(), randomizer2.getRandomValue());
    }
}

TEST(AlbaUniformDeterministicRandomizerTest, GetRandomIntegerWorksAsUniformlyDistributed) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    constexpr int customSeed(5);
    IntegerRandomizerForTest randomizer(minimumValue, maximumValue, customSeed);
    int const numberOfRandomValues(maximumValue - minimumValue + 1);
    constexpr int iterations = 1000;
    int const allowedDeviationCount(iterations / 10);
    vector<int> hitsForEachValue(numberOfRandomValues, 0);

    for (int i = 0; i < iterations; ++i) {
        auto randomValue(randomizer.getRandomValue());
        hitsForEachValue[randomValue]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());
    auto&& [minIterator, maxIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int const deviationCount(*maxIterator - *minIterator);
    EXPECT_LT(deviationCount, allowedDeviationCount);
}

TEST(AlbaUniformDeterministicRandomizerTest, GetRandomFloatingValueWorksWithinMinimumAndMaximumValues) {
    constexpr double minimumValue(-11.5);
    constexpr double maximumValue(23.25);
    constexpr double customSeed(10);
    FloatingPointRandomizerForTest randomizer(minimumValue, maximumValue, customSeed);

    for (int i = 0; i < 1000; ++i) {
        auto randomValue(randomizer.getRandomValue());
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

TEST(AlbaUniformDeterministicRandomizerTest, GetRandomFloatingValueWorksAsDeterministic) {
    constexpr double minimumValue(-11.5);
    constexpr double maximumValue(23.25);
    constexpr double customSeed(10);
    FloatingPointRandomizerForTest randomizer1(minimumValue, maximumValue, customSeed);
    FloatingPointRandomizerForTest randomizer2(minimumValue, maximumValue, customSeed);

    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(randomizer1.getRandomValue(), randomizer2.getRandomValue());
    }
}

TEST(AlbaUniformDeterministicRandomizerTest, GetRandomFloatingValueWorksAsUniformlyDistributed) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    constexpr double customSeed(10);
    FloatingPointRandomizerForTest randomizer(
        static_cast<double>(minimumValue), static_cast<double>(maximumValue), customSeed);
    int const numberOfRandomValues(maximumValue - minimumValue);  // number of integer values for floating point
    constexpr int iterations = 1000;
    int const allowedDeviationCount(iterations / 10);
    vector<int> hitsForEachValue(numberOfRandomValues, 0);

    for (int i = 0; i < iterations; ++i) {
        hitsForEachValue[static_cast<int>(randomizer.getRandomValue())]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());
    auto&& [minIterator, maxIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int const deviationCount(*maxIterator - *minIterator);
    EXPECT_LT(deviationCount, allowedDeviationCount);
}

}  // namespace alba
