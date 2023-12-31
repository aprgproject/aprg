#include <Algebra/Series/SpecificSeries/HarmonicSeries.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(HarmonicSeriesTest, IsSummationModelValidWorks) {
    HarmonicSeries const series;

    EXPECT_FALSE(series.isSummationModelValid());
}

TEST(HarmonicSeriesTest, GetValueAtIndexWorks) {
    HarmonicSeries const series;

    EXPECT_EQ(Term(1), series.getValueAtIndex(0));
    EXPECT_EQ(Term(AlbaNumber::createFraction(3, 2)), series.getValueAtIndex(1));
    EXPECT_EQ(Term(AlbaNumber::createFraction(11, 6)), series.getValueAtIndex(2));
    EXPECT_EQ(Term(AlbaNumber::createFraction(25, 12)), series.getValueAtIndex(3));
}

}  // namespace alba::algebra
