#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(LimitsAtInfinityTest, XWorksAndSimplifiesToZero) {
    LimitsAtInfinity const limits("x", "x");

    EXPECT_EQ(Term("x"), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(getNegativeInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(getPositiveInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, OneOverXWorksAndSimplifiesToZero) {
    Term const term(createExpressionIfPossible({1, "/", "x"}));

    LimitsAtInfinity const limits(term, "x");

    Term const expectedTerm(0);
    Term const expectedValueTerm(0);
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithEqualDegreeWorks) {
    Term const numerator(Polynomial{Monomial(2, {{"x", 2}})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term const term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity const limits(term, "x");

    Term const expectedTerm(2);
    Term const expectedValueTerm(2);
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithNumeratorDegreeIsGreaterAndPositiveWorks) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 2}})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term const term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity const limits(term, "x");

    EXPECT_EQ(Term("x"), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(getNegativeInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(getPositiveInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithNumeratorDegreeIsGreaterAndNegativeWorks) {
    Term const numerator(Polynomial{Monomial(-6, {{"x", 2}}), Monomial(2, {{"x", 1}})});
    Term const denominator(Polynomial{Monomial(3, {{"x", 1}}), Monomial(5, {})});
    Term const term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity const limits(term, "x");

    EXPECT_EQ(Term(Monomial(-2, {{"x", 1}})), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(getPositiveInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(getNegativeInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithDenominatorDegreeIsGreaterWorks) {
    Term const numerator(Polynomial{Monomial(2, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(5, {})});
    Term const denominator(Polynomial{Monomial(4, {{"x", 3}}), Monomial(-1, {})});
    Term const term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity const limits(term, "x");

    Term const expectedTerm(0);
    Term const expectedValueTerm(0);
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverSquareRootOfPolynomialWithEqualDegreeWorks) {
    Term const numerator("x");
    Term const denominatorInSquareRoot(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term const denominator(
        createExpressionIfPossible({denominatorInSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term const term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity const limits(term, "x");

    Term const expectedTerm(1);
    Term const expectedValueTerm(1);
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, ExpressionWithTrigonometricFunctionsWorks) {
    Term const numerator(sin(Monomial(1, {{"x", -1}})));
    Term const denominator(arctan(Monomial(1, {{"x", -1}})));
    Term const term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity const limits(term, "x");

    EXPECT_TRUE(isNan(limits.getSimplifiedTermAtInfinity()));
    EXPECT_TRUE(isNan(limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY)));
    EXPECT_TRUE(isNan(limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY)));
}

}  // namespace alba::algebra
