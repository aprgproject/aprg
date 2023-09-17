#include <Algebra/Series/SpecificSeries/AlternatingSeries.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(AlternatingSeriesTest, IsSummationModelValidWorks) {
    Term const numerator(1);
    Term const denominator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    AlternatingSeries const series(formula, "n");

    EXPECT_FALSE(series.isSummationModelValid());
}

TEST(AlternatingSeriesTest, GetValueAtIndexWorks) {
    Term const numerator(1);
    Term const denominator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    AlternatingSeries const series(formula, "n");

    EXPECT_EQ(Term(1), series.getValueAtIndex(0));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getValueAtIndex(1));
    EXPECT_EQ(Term(AlbaNumber::createFraction(5, 6)), series.getValueAtIndex(2));
    EXPECT_EQ(Term(AlbaNumber::createFraction(7, 12)), series.getValueAtIndex(3));
}

TEST(AlternatingSeriesTest, GetRemainderAtIndexWorks) {
    Term const numerator(1);
    Term const denominator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    AlternatingSeries const series(formula, "n");

    EXPECT_EQ(Term(1), series.getRemainderAtIndex(0));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getRemainderAtIndex(1));
    EXPECT_EQ(Term(AlbaNumber::createFraction(5, 6)), series.getRemainderAtIndex(2));
    EXPECT_EQ(Term(AlbaNumber::createFraction(7, 12)), series.getRemainderAtIndex(3));
}

TEST(AlternatingSeriesTest, IsConvergentWorks) {
    Term const numerator(1);
    Term const denominator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term const formula(createExpressionIfPossible({numerator, "/", denominator}));
    AlternatingSeries const series(formula, "n");

    EXPECT_TRUE(series.isConvergent());
}

}  // namespace alba::algebra
