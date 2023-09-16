#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(LimitTest, GetLimitAtAValueWorksForSinXOverX) {
    Term const sinXOverX(createExpressionIfPossible({sin("x"), "/", "x"}));

    EXPECT_EQ(Term(1), getLimitAtAValue(sinXOverX, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(1), getLimitAtAValue(sinXOverX, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(1), getLimitAtAValue(sinXOverX, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForSinXHarmonicOverSinXHarmonic) {
    Term const numerator(sin(Monomial(3, {{"x", 1}})));
    Term const denominator(sin(Monomial(5, {{"x", 1}})));
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(0.6), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(0.6), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(0.6), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForCosineExpression) {
    Term const numerator(createExpressionIfPossible({1, "-", cos("x")}));
    Term const denominator("x");
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(0), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(0), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(0), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForCosineAndSineExpression) {
    Term const numerator(createExpressionIfPossible({1, "-", cos("x")}));
    Term const denominator(sin("x"));
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(0), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(0), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(0), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForTangentExpression) {
    Term const numerator(createExpressionIfPossible({2, "*", tan("x"), "^", 2}));
    Term const denominator(Monomial(1, {{"x", 2}}));
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(2), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(2), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(2), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForComplicatedSinOverX) {
    Term const numerator(sin(Monomial(ALBA_NUMBER_PI, {{"x", 1}})));
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {{"x", 1}})});
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(-3.141592653589794), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(-3.141592653589794), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(-3.141592653589794), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));

    // The limit in 1 should not be negative infinity (it should be negative pi)
    // but the calculation of sin of pi is not zero (its only near zero) for some reason.
    EXPECT_EQ(getNegativeInfinityAsATerm(), getLimitAtAValue(termToTest, "x", 1, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(
        getNegativeInfinityAsATerm(), getLimitAtAValue(termToTest, "x", 1, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        getNegativeInfinityAsATerm(), getLimitAtAValue(termToTest, "x", 1, LimitAtAValueApproachType::NegativeSide));
}

}  // namespace alba::algebra
