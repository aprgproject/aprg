#include <Algebra/Series/SpecificSeries/PowerSeries.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(PowerSeriesTest, IsSummationModelValidWorks) {
    Term const multiplier("n");
    PowerSeries const series(multiplier, "n", "x", 2);

    EXPECT_FALSE(series.isSummationModelValid());
}

TEST(PowerSeriesTest, GetRadiusOfConvergenceWorks) {
    Term const multiplier("n");
    PowerSeries const series(multiplier, "n", "x", 2);

    EXPECT_EQ(AlbaNumber(1), series.getRadiusOfConvergence());
}

TEST(PowerSeriesTest, GetIntervalsOfConvergenceWorks) {
    Term const multiplier("n");
    PowerSeries const series(multiplier, "n", "x", 2);

    AlbaNumberIntervals expectedIntervals(series.getIntervalsOfConvergence());
    ASSERT_EQ(1U, expectedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createOpenEndpoint(3)), expectedIntervals[0]);
}

TEST(PowerSeriesTest, DifferentiateWorks) {
    Term const multiplier("n");
    PowerSeries series(multiplier, "n", "x", 2);

    series.differentiate();

    string const stringToExpect("(1[n^2]*((1[x] + -2)^(1[n] + -1)))");
    EXPECT_EQ(stringToExpect, convertToString(series.getFormulaForEachTermInSummation()));
}

TEST(PowerSeriesTest, IntegrateWorks) {
    Term const multiplier("n");
    PowerSeries series(multiplier, "n", "x", 2);

    series.integrate();

    string const stringToExpect("(n*((1[x] + -2)^(1[n] + 1))/(1[n] + 1))");
    EXPECT_EQ(stringToExpect, convertToString(series.getFormulaForEachTermInSummation()));
}

}  // namespace alba::algebra
