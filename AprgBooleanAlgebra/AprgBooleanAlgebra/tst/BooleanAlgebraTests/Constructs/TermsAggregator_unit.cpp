#include <BooleanAlgebra/Constructs/TermsAggregator.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithNoTerms) {
    TermsAggregator aggregator({});

    aggregator.buildExpressionFromTerms();

    Terms const termsToVerify(aggregator.getTermsConstReference());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithUnaryOperation) {
    TermsAggregator aggregator({"~", "x"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect("x'");
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithBinaryOperation) {
    TermsAggregator aggregator({"x", "&", "y"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithDifferentOperationLevelsAndOperationPrioritizedBeforeOrOperation) {
    TermsAggregator aggregator({"a", "|", "b", "&", "c", "&", "d", "|", "e"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Expression const subExpression1(createExpressionIfPossible({"b", "&", "c", "&", "d"}));
    Expression const subExpression2(createExpressionIfPossible({"a", "|", subExpression1, "|", "e"}));
    Term const termToExpect(subExpression2);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithParenthesis) {
    TermsAggregator aggregator({"(", "(", "(", "a", "|", "b", ")", "&", "c", ")", "|", "d", ")"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Expression const subExpression1(createExpressionIfPossible({"a", "|", "b"}));
    Expression const subExpression2(createExpressionIfPossible({subExpression1, "&", "c"}));
    Expression const subExpression3(createExpressionIfPossible({subExpression2, "|", "d"}));
    Term const termToExpect(subExpression3);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithNoTerms) {
    TermsAggregator aggregator({});

    aggregator.simplifyTerms();

    Terms const termsToVerify(aggregator.getTermsConstReference());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(TermsAggregatorTest, SimplifyWorksWithUnaryOperation) {
    TermsAggregator aggregator({"~", true});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect(false);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithBinaryOperation) {
    TermsAggregator aggregator({true, "&", false});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect(false);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithDifferentOperationLevels) {
    TermsAggregator aggregator({false, "|", true, "&", false, "&", true, "|", false});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect(false);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithParenthesis) {
    TermsAggregator aggregator({"(", "(", "(", false, "|", true, ")", "&", true, ")", "|", false, ")"});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term const termToExpect(true);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(TermsAggregatorTest, SimplifyWorksWithNegatedTermsAndVariousOperations) {
    TermsAggregator aggregator(tokenizeToTerms("~a&~b|~c&x|y"));

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Expression const subExpression1(createExpressionIfPossible({"a'", "&", "b'"}));
    Expression const subExpression2(createExpressionIfPossible({"c'", "&", "x"}));
    Expression const subExpression3(createExpressionIfPossible({subExpression1, "|", subExpression2, "|", "y"}));
    Term const termToExpect(subExpression3);
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

}  // namespace alba::booleanAlgebra
