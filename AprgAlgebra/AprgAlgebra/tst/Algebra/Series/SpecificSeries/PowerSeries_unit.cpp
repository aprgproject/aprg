#include <Algebra/Series/SpecificSeries/PowerSeries.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>


#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(PowerSeriesTest, IsSummationModelValidWorks)
{
    Term n("n");
    Term multiplier("n");
    PowerSeries series(multiplier, "n", "x", 2);

    EXPECT_FALSE(series.isSummationModelValid());
}

TEST(PowerSeriesTest, GetIntervalsOfConvergenceWorks)
{
    Term n("n");
    Term multiplier("n");
    PowerSeries series(multiplier, "n", "x", 2);

    AlbaNumberIntervals expectedIntervals(series.getIntervalsOfConvergence());
    ASSERT_EQ(1U, expectedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createOpenEndpoint(3)), expectedIntervals.at(0));
}

TEST(PowerSeriesTest, GetRadiusOfConvergenceWorks)
{
    Term n("n");
    Term multiplier("n");
    PowerSeries series(multiplier, "n", "x", 2);

    EXPECT_EQ(AlbaNumber(1), series.getRadiusOfConvergence());
}

TEST(PowerSeriesTest, DifferentiateWorks)
{
    Term n("n");
    Term multiplier("n");
    PowerSeries series(multiplier, "n", "x", 2);

    series.differentiate();

    string stringToExpect("(1[n^2]*((1[x] + -2)^(1[n] + -1)))");
    EXPECT_EQ(stringToExpect, series.getFormulaForEachTermInSummation().getDisplayableString());
}

TEST(PowerSeriesTest, IntegrateWorks)
{
    Term n("n");
    Term multiplier("n");
    PowerSeries series(multiplier, "n", "x", 2);

    series.integrate();

    string stringToExpect("(n*((1[x] + -2)^(1[n] + 1))/(1[n] + 1))");
    EXPECT_EQ(stringToExpect, series.getFormulaForEachTermInSummation().getDisplayableString());
}

}

}
