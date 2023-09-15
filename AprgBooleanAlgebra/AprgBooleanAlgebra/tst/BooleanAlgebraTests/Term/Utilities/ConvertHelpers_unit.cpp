#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::booleanAlgebra {

TEST(ConvertHelpersTest, SimplifyAndConvertExpressionToSimplestTermWorks) {
    Expression const expression1(createExpressionIfPossible({true}));
    Expression const expression2(createExpressionInAnExpression(expression1));
    Expression const expression3(createExpressionInAnExpression(expression2));
    Expression const expression4(createExpressionInAnExpression(expression3));

    Term const termToVerify1(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({})));
    Term const termToVerify2(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({expression1})));
    Term const termToVerify3(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({expression2})));
    Term const termToVerify4(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({expression3})));
    Term const termToVerify5(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({expression4})));

    ASSERT_EQ(TermType::Empty, termToVerify1.getTermType());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_TRUE(termToVerify2.getBooleanValue());
    ASSERT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_TRUE(termToVerify3.getBooleanValue());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_TRUE(termToVerify4.getBooleanValue());
    ASSERT_EQ(TermType::Constant, termToVerify5.getTermType());
    EXPECT_TRUE(termToVerify5.getBooleanValue());
}

TEST(ConvertHelpersTest, ConvertExpressionToSimplestTermWorks) {
    Term const termToVerify1(convertExpressionToSimplestTerm(createExpressionIfPossible({})));
    Term const termToVerify2(convertExpressionToSimplestTerm(createExpressionIfPossible({true})));
    Term const termToVerify3(convertExpressionToSimplestTerm(createExpressionIfPossible({"x", "&", "y"})));

    EXPECT_EQ(Term(), termToVerify1);
    EXPECT_EQ(Term(true), termToVerify2);
    Term const termToExpect3(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect3, termToVerify3);
}

}  // namespace alba::booleanAlgebra
