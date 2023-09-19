#include <Common/Randomizer/AlbaOldRandomizer.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

namespace alba {

TEST(AlbaOldRandomizerTest, GetRandomValueInUniformDistributionWorksWithinMinimumAndMaximumValues) {
    AlbaOldRandomizer const randomizer;
    constexpr double minimumValue(-11.5);
    constexpr double maximumValue(23.25);
    for (int i = 0; i < 1000; ++i) {
        double const random(AlbaOldRandomizer::getRandomFloatingValueInUniformDistribution(minimumValue, maximumValue));
        ASSERT_GE(random, minimumValue);
        ASSERT_LE(random, maximumValue);
    }
}

TEST(AlbaOldRandomizerTest, GetRandomIntegerInUniformDistributionWorksWithinMinimumAndMaximumValues) {
    AlbaOldRandomizer const randomizer;
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    for (int i = 0; i < 1000; ++i) {
        int const random(AlbaOldRandomizer::getRandomIntegerInUniformDistribution(minimumValue, maximumValue));
        ASSERT_GE(random, minimumValue);
        ASSERT_LE(random, maximumValue);
    }
}

TEST(AlbaOldRandomizerTest, GetRandomIntegerInUniformDistributionWorksAsUniformlyDistributed) {
    AlbaOldRandomizer const randomizer;
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    int const numberOfRandomValues(maximumValue - minimumValue + 1);
    constexpr int iterations=1000;
    int const allowedDeviation(iterations / 10);
    vector<int> hitsForEachValue(numberOfRandomValues, 0);

    for (int i = 0; i < iterations; ++i) {
        int const random(AlbaOldRandomizer::getRandomIntegerInUniformDistribution(minimumValue, maximumValue));
        hitsForEachValue[random]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());
    auto&& [maxIterator, minIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int const deviation(*maxIterator - *minIterator);
    EXPECT_LE(deviation, allowedDeviation);
}

}  // namespace alba
