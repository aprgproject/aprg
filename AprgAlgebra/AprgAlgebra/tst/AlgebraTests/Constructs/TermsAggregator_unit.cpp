#include <Algebra/Constructs/TermsAggregator.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithNoTerms) {
    TermsAggregator aggregator({});

    aggregator.buildExpressionFromTerms();

    Terms const termsToVerify(aggregator.getTermsConstReference());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithUnaryOperation) {
    TermsAggregator aggregator({"-", "x"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect(createExpressionIfPossible({"-", "x"}));
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithBinaryOperation) {
    TermsAggregator aggregator({"x", "+", "x"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect(createExpressionIfPossible({"x", "+", "x"}));
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithDifferentOperationLevels) {
    TermsAggregator aggregator({"a", "+", "b", "*", "c", "^", "d"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Expression const subExpression1(createExpressionIfPossible({"c", "^", "d"}));
    Expression const subExpression2(createExpressionIfPossible({"b", "*", subExpression1}));
    Expression const subExpression3(createExpressionIfPossible({"a", "+", subExpression2}));
    Term const termToExpect(subExpression3);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithParenthesis) {
    TermsAggregator aggregator({"(", "(", "(", "a", "+", "b", ")", "*", "c", ")", "^", "d", ")"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify[0].getTermType());
    Expression const subExpression1(createExpressionIfPossible({"a", "+", "b"}));
    Expression const subExpression2(createExpressionIfPossible({subExpression1, "*", "c"}));
    Expression const subExpression3(createExpressionIfPossible({subExpression2, "^", "d"}));
    Term const termToExpect(subExpression3);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, BuildExpressionFromTermsWorksOnNegativeFractionInParenthesis) {
    TermsAggregator aggregator({"(", "-", 1, "/", 3, ")"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify[0].getTermType());
    Expression const subExpression1(createExpressionIfPossible({"-", 1}));
    Term const termToExpect(createExpressionIfPossible({subExpression1, "/", 3}));
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithNoTerms) {
    TermsAggregator aggregator({});

    aggregator.simplifyTerms();

    Terms const termsToVerify(aggregator.getTermsConstReference());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(TermsAggregatorTest, SimplifyWorksWithUnaryOperation) {
    TermsAggregator aggregator({"-", 14});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(-14), termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithBinaryOperation) {
    TermsAggregator aggregator({2, "+", 3});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(5), termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithDifferentOperationLevels) {
    TermsAggregator aggregator({2, "+", 3, "*", 4, "^", 5});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(3074), termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithParenthesis) {
    TermsAggregator aggregator({"(", "(", "(", 2, "+", 3, ")", "*", 4, ")", "^", 5, ")"});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(3200000), termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithNegativeValues) {
    TermsAggregator aggregator(tokenizeToTerms("x^2*y^-3*z^4"));

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify[0].getTermType());
    Term const termToExpect(Monomial(1, {{"x", 2}, {"y", -3}, {"z", 4}}));
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithFunction) {
    TermsAggregator aggregator(tokenizeToTerms("abs(5)"));

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect(Functions::abs(5));
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

}  // namespace alba::algebra
