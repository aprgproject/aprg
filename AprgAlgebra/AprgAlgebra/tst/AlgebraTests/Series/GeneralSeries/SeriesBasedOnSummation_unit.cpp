#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(SeriesBasedOnSummationTest, ConstructionWorks) { SeriesBasedOnSummation("n", "n"); }

TEST(SeriesBasedOnSummationTest, IsConvergentWorksWhenSummationModelIsValid) {
    Term const exponent(Polynomial{Monomial(1, {}), Monomial(-1, {{"n", 1}})});
    Term const formula(createExpressionIfPossible({2, "^", exponent}));
    SeriesBasedOnSummation const series(formula, "n");

    EXPECT_TRUE(series.isSummationModelValid());
    EXPECT_TRUE(series.isConvergent());
}

TEST(SeriesBasedOnSummationTest, IsConvergentWorksWhenSummationModelIsInvalid) {
    Term const numerator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {})});
    Term const denominator(Monomial(1, {{"n", 2}}));
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation const series(formula, "n");

    EXPECT_FALSE(series.isSummationModelValid());
    EXPECT_FALSE(series.isConvergent());
}

TEST(SeriesBasedOnSummationTest, IsAbsolutelyConvergentWorksWhenSummationModelIsValid) {
    Term const exponent(Polynomial{Monomial(1, {}), Monomial(-1, {{"n", 1}})});
    Term const formula(createExpressionIfPossible({2, "^", exponent}));
    SeriesBasedOnSummation const series(formula, "n");

    EXPECT_TRUE(series.isSummationModelValid());
    EXPECT_TRUE(series.isAbsolutelyConvergent());
}

TEST(SeriesBasedOnSummationTest, IsAbsolutelyConvergentWorksWhenSummationModelIsInvalid) {
    Term const numerator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {})});
    Term const denominator(Monomial(1, {{"n", 2}}));
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation const series(formula, "n");

    EXPECT_FALSE(series.isSummationModelValid());
    EXPECT_FALSE(series.isAbsolutelyConvergent());
}

TEST(SeriesBasedOnSummationTest, IsConditionallyConvergentWorksWhenSummationModelIsValid) {
    Term const exponent(Polynomial{Monomial(1, {}), Monomial(-1, {{"n", 1}})});
    Term const formula(createExpressionIfPossible({2, "^", exponent}));
    SeriesBasedOnSummation const series(formula, "n");

    EXPECT_TRUE(series.isSummationModelValid());
    EXPECT_TRUE(series.isConditionallyConvergent());
}

TEST(SeriesBasedOnSummationTest, IsConditionallyConvergentWorksWhenSummationModelIsInvalid) {
    Term const numerator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {})});
    Term const denominator(Monomial(1, {{"n", 2}}));
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation const series(formula, "n");

    EXPECT_FALSE(series.isSummationModelValid());
    EXPECT_TRUE(series.isConditionallyConvergent());
}

}  // namespace alba::algebra
