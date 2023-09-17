#include <Algebra/Series/SpecificSeries/SummationSeriesOfGeometricSeries.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(SummationSeriesOfGeometricSeriesTest, IsConvergentWorks) {
    SummationSeriesOfGeometricSeries const seriesWithMultiplierLessThanOne(1, AlbaNumber::createFraction(1, 2));
    SummationSeriesOfGeometricSeries const seriesWithMultiplierEqualsToOne(1, 1);
    SummationSeriesOfGeometricSeries const seriesWithMultiplierMoreThanOne(1, 2);

    EXPECT_TRUE(seriesWithMultiplierLessThanOne.isSummationModelValid());
    EXPECT_TRUE(seriesWithMultiplierEqualsToOne.isSummationModelValid());
    EXPECT_TRUE(seriesWithMultiplierMoreThanOne.isSummationModelValid());
    EXPECT_TRUE(seriesWithMultiplierLessThanOne.isConvergent());
    EXPECT_FALSE(seriesWithMultiplierEqualsToOne.isConvergent());
    EXPECT_FALSE(seriesWithMultiplierMoreThanOne.isConvergent());
}

}  // namespace alba::algebra
