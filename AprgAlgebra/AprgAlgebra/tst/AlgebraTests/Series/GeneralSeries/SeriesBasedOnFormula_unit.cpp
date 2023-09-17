#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(SeriesBasedOnFormulaTest, ConstructionWorks) { SeriesBasedOnFormula const series("n", "n"); }

TEST(SeriesBasedOnFormulaTest, GetGreatestLowerBoundWorks) {
    Term const numerator("n");
    Term const denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    AlbaNumberOptional greatestLowerBoundOptional(series.getGreatestLowerBound());

    ASSERT_TRUE(greatestLowerBoundOptional);
    EXPECT_EQ(AlbaNumber::createFraction(-4, 15), greatestLowerBoundOptional.value());
}

TEST(SeriesBasedOnFormulaTest, GetLeastUpperBoundWorks) {
    Term const numerator("n");
    Term const denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    AlbaNumberOptional leastUpperBoundOptional(series.getLeastUpperBound());

    ASSERT_TRUE(leastUpperBoundOptional);
    EXPECT_EQ(AlbaNumber::createFraction(1, 2), leastUpperBoundOptional.value());
}

TEST(SeriesBasedOnFormulaTest, GetFormulaForSeriesWorks) {
    Term const formula(Polynomial{Monomial(1, {{"n", 2}}), Monomial(3, {{"n", 4}}), Monomial(5, {{"n", 6}})});
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_EQ(formula, series.getFormulaForSeries());
}

TEST(SeriesBasedOnFormulaTest, GetValueAtIndexWorks) {
    SeriesBasedOnFormula const series("n", "n");

    EXPECT_EQ(Term(-5), series.getValueAtIndex(-5));
    EXPECT_EQ(Term(0), series.getValueAtIndex(0));
    EXPECT_EQ(Term(5), series.getValueAtIndex(5));
}

TEST(SeriesBasedOnFormulaTest, GetSumWorks) {
    SeriesBasedOnFormula const series("n", "n");

    EXPECT_EQ(Term(55), series.getSum(0, 10));
}

TEST(SeriesBasedOnFormulaTest, GetSumStartingAtIndexAndToInfinityWorks) {
    Term const formula(createExpressionIfPossible({AlbaNumber::createFraction(1, 2), "^", "n"}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_EQ(Term(2), series.getSumStartingAtIndexAndToInfinity(0));
}

TEST(SeriesBasedOnFormulaTest, GetValueAtInfinityWorks) {
    Term const numerator("n");
    Term const denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getValueAtInfinity());
}

TEST(SeriesBasedOnFormulaTest, GetRemainderAtIndexWorks) {
    Term const numerator("n");
    Term const denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getRemainderAtIndex(0));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 6)), series.getRemainderAtIndex(1));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 10)), series.getRemainderAtIndex(2));
}

TEST(SeriesBasedOnFormulaTest, IsConvergentWorksOnConvergentSeries) {
    Term const numerator(Polynomial{Monomial(4, {{"n", 2}})});
    Term const denominator(Polynomial{Monomial(2, {{"n", 2}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_TRUE(series.isConvergent());
}

TEST(SeriesBasedOnFormulaTest, IsConvergentWorksOnDivergentSeries) {
    Term const formula(createExpressionIfPossible({-1, "^", "n", "+", 1}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_FALSE(series.isConvergent());
}

TEST(SeriesBasedOnFormulaTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnIncreasingFunction) {
    Term const numerator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term const denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(3, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_TRUE(series.isIncreasing());
    EXPECT_FALSE(series.isDecreasing());
    EXPECT_TRUE(series.isMonotonic());
}

TEST(SeriesBasedOnFormulaTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnNonIncreasingAndDecreasingFunction) {
    Term const formula(sin("n"));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_FALSE(series.isIncreasing());
    EXPECT_FALSE(series.isDecreasing());
    EXPECT_FALSE(series.isMonotonic());
}

TEST(SeriesBasedOnFormulaTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnDecreasingFunction) {
    Term const numerator(1);
    Term const denominator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula const series(formula, "n");

    EXPECT_FALSE(series.isIncreasing());
    EXPECT_TRUE(series.isDecreasing());
    EXPECT_TRUE(series.isMonotonic());
}

}  // namespace alba::algebra
