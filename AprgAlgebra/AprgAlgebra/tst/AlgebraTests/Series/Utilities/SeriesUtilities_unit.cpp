#include <Algebra/Series/Utilities/SeriesUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(SeriesUtilitiesTest, PerformLimitComparisonTestWorks) {
    Term const numerator1(1);
    Term const denominator1(Monomial(1, {{"n", AlbaNumber::createFraction(1, 2)}}));
    Term const formula1(createExpressionIfPossible({numerator1, "/", denominator1}));
    SeriesBasedOnSummation const series1(formula1, "n");
    Term const numerator2(1);
    Term const denominator2("n");
    Term const formula2(createExpressionIfPossible({numerator2, "/", denominator2}));
    SeriesBasedOnSummation const series2(formula2, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performLimitComparisonTest(isConvergent, isDivergent, series1, series2, "n");

    EXPECT_FALSE(isConvergent);
    EXPECT_TRUE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformIntegralTestWorksOnPSeriesWithPowerIsOneHalf) {
    Term const numerator(1);
    Term const denominator(Monomial(1, {{"n", AlbaNumber::createFraction(1, 2)}}));
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation const series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performIntegralTest(isConvergent, isDivergent, series, "n");

    EXPECT_FALSE(isConvergent);
    EXPECT_TRUE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformIntegralTestWorksOnPSeriesWithPowerIsTwo) {
    Term const numerator(1);
    Term const denominator(Monomial(1, {{"n", 2}}));
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation const series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performIntegralTest(isConvergent, isDivergent, series, "n");

    EXPECT_TRUE(isConvergent);
    EXPECT_FALSE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformRatioTestWorksWhenConvergent) {
    Term const numerator("n");
    Term const denominator(createExpressionIfPossible({2, "^", "n"}));
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation const series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performRatioTest(isConvergent, isDivergent, series, "n");

    EXPECT_TRUE(isConvergent);
    EXPECT_FALSE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformRatioTestWorksWhenConvergentOrDivergent) {
    Term const numerator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {{"n", 1}})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation const series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performRatioTest(isConvergent, isDivergent, series, "n");

    EXPECT_FALSE(isConvergent);
    EXPECT_FALSE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformRootTestWorks) {
    Term const exponentNumerator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term const exponentDenominator(Polynomial{Monomial(2, {{"n", 1}})});
    Term const numerator(createExpressionIfPossible({3, "^", exponentNumerator}));
    Term const denominator(createExpressionIfPossible({"n", "^", exponentDenominator}));
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation const series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performRootTest(isConvergent, isDivergent, series, "n");

    EXPECT_TRUE(isConvergent);
    EXPECT_FALSE(isDivergent);
}

TEST(SeriesUtilitiesTest, GetEToTheXPowerSeriesWorks) {
    PowerSeries const series(getEToTheXPowerSeries());

    string const stringToExpect1("1");
    string const stringToExpect2("(1[x] + 1)");
    string const stringToExpect3("((1/2)[x^2] + 1[x] + 1)");
    string const stringToExpect4("((1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    string const stringToExpect5("(1/factorial(n)*(x^n))");
    EXPECT_FALSE(series.isSummationModelValid());
    EXPECT_EQ(stringToExpect1, convertToString(series.getValueAtIndex(0)));
    EXPECT_EQ(stringToExpect2, convertToString(series.getValueAtIndex(1)));
    EXPECT_EQ(stringToExpect3, convertToString(series.getValueAtIndex(2)));
    EXPECT_EQ(stringToExpect4, convertToString(series.getValueAtIndex(3)));
    EXPECT_EQ(stringToExpect5, convertToString(series.getFormulaForEachTermInSummation()));
}

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithValues) {
    EXPECT_EQ(Term(60), getSumOfArithmeticSeriesUsingFirstAndLastTerm(12, 18, 4));
}

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample1) {
    Term const firstTerm(1);
    Term const lastTerm("n");
    Term const count("n");

    Term const expectedSum(
        Polynomial{Monomial(AlbaNumber(1) / 2, {{"n", 2}}), Monomial(AlbaNumber(1) / 2, {{"n", 1}})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample2) {
    Term const firstTerm(4);
    Term const lastTerm(Monomial(4, {{"n", 1}}));
    Term const count("n");

    Term const expectedSum(Polynomial{Monomial(2, {{"n", 2}}), Monomial(2, {{"n", 1}})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample3) {
    Term const firstTerm(1);
    Term const lastTerm(Polynomial{Monomial(3, {{"n", 1}}), Monomial(-2, {})});
    Term const count(Polynomial{Monomial(1, {{"n", 1}}), Monomial(-1, {})});

    Term const expectedSum(
        Polynomial{Monomial(AlbaNumber(3) / 2, {{"n", 2}}), Monomial(-2, {{"n", 1}}), Monomial(AlbaNumber(1) / 2, {})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}

TEST(SeriesUtilitiesTest, GetSumOfGeometricSeriesUsingFirstValueAndCommonMultiplierWorksWithValues) {
    EXPECT_EQ(Term(10230), getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(10, 2, 10));
}

TEST(SeriesUtilitiesTest, GetInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractionalWorksWithValues) {
    EXPECT_EQ(
        Term(20), getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(10, AlbaNumber::createFraction(1, 2)));
}

TEST(SeriesUtilitiesTest, IsAxiomOfCompletenessTrueWorks) {
    Term const numerator("n");
    Term const denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_TRUE(isAxiomOfCompletenessTrue(series));
}

TEST(SeriesUtilitiesTest, IsBoundedMonotonicSeriesConvergentWorks) {
    Term const numerator("n");
    Term const denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_TRUE(isBoundedMonotonicSeriesConvergent(series));
}

TEST(SeriesUtilitiesTest, IsConvergentMonotonicSeriesBoundedWorks) {
    Term const numerator("n");
    Term const denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_TRUE(isConvergentMonotonicSeriesBounded(series));
}

TEST(SeriesUtilitiesTest, IsConvergentUsingComparisonTestWorks) {
    Term const numeratorToTest(4);
    Term const denominatorToTest(createExpressionIfPossible({3, "^", "n", "^", 1}));
    Term const formulaToTest(createExpressionIfPossible({numeratorToTest, "/", denominatorToTest}));
    SeriesBasedOnSummation const seriesToTest(formulaToTest, "n");
    Term const convergentNumerator(4);
    Term const convergentDenominator(createExpressionIfPossible({3, "^", "n"}));
    Term const convergentFormula(createExpressionIfPossible({convergentNumerator, "/", convergentDenominator}));
    SeriesBasedOnSummation const convergentSeries(convergentFormula, "n");

    EXPECT_TRUE(isConvergentUsingComparisonTest(seriesToTest, convergentSeries, 10));
}

TEST(SeriesUtilitiesTest, IsDivergentUsingComparisonTestWorks) {
    Term const numeratorToTest(1);
    Term const denominatorToTest(Monomial(1, {{"n", AlbaNumber::createFraction(1, 2)}}));
    Term const formulaToTest(createExpressionIfPossible({numeratorToTest, "/", denominatorToTest}));
    SeriesBasedOnSummation const seriesToTest(formulaToTest, "n");
    Term const divergentNumerator(1);
    Term const divergentDenominator("n");
    Term const divergentFormula(createExpressionIfPossible({divergentNumerator, "/", divergentDenominator}));
    SeriesBasedOnSummation const divergentSeries(divergentFormula, "n");

    EXPECT_TRUE(isDivergentUsingComparisonTest(seriesToTest, divergentSeries, 10));
}

TEST(SeriesUtilitiesTest, HasLinearityWorks) {
    EXPECT_TRUE(hasLinearity("n", "n", 5, 10));
    EXPECT_TRUE(hasLinearity(Monomial(1, {{"n", 2}}), "n", 6, 12));
}

}  // namespace alba::algebra
