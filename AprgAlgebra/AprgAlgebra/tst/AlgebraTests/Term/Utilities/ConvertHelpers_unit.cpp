#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;

namespace alba::algebra {

TEST(ConvertHelpersTest, ReverseWorks) {
    Operator const nullOperator;
    Operator const addOperator("+");
    Operator const subtractOperator("-");
    Operator const multiplyOperator("*");
    Operator const divideOperator("/");
    Operator const raiseToPowerOperator("^");
    Operator const openingGroupOperator("(");
    Operator const closingGroupOperator(")");
    Operator const invalidOperator("invalid");

    EXPECT_TRUE(reverse(nullOperator).getOperatorString().empty());
    EXPECT_EQ("-", reverse(addOperator).getOperatorString());
    EXPECT_EQ("+", reverse(subtractOperator).getOperatorString());
    EXPECT_EQ("/", reverse(multiplyOperator).getOperatorString());
    EXPECT_EQ("*", reverse(divideOperator).getOperatorString());
    EXPECT_TRUE(reverse(raiseToPowerOperator).getOperatorString().empty());
    EXPECT_TRUE(reverse(openingGroupOperator).getOperatorString().empty());
    EXPECT_TRUE(reverse(closingGroupOperator).getOperatorString().empty());
    EXPECT_TRUE(reverse(invalidOperator).getOperatorString().empty());
}

TEST(ConvertHelpersTest, SimplifyAndConvertMonomialToSimplestTermWorks) {
    Term const termToVerify1(simplifyAndConvertMonomialToSimplestTerm(Monomial()));
    Term const termToVerify2(simplifyAndConvertMonomialToSimplestTerm(Monomial(6, {})));
    Term const termToVerify3(simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{"x", 1}})));
    Term const termToVerify4(simplifyAndConvertMonomialToSimplestTerm(Monomial(10, {{"x", 0}})));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Variable, termToVerify3.getTermType());
    EXPECT_EQ("x", termToVerify3.getAsVariable().getVariableName());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(10, termToVerify4.getAsNumber().getDouble());
}

TEST(ConvertHelpersTest, SimplifyAndConvertPolynomialToSimplestTermWorks) {
    Term const termToVerify1(simplifyAndConvertPolynomialToSimplestTerm(Polynomial{}));
    Term const termToVerify2(simplifyAndConvertPolynomialToSimplestTerm(Polynomial{Monomial(6, {})}));
    Term const termToVerify3(
        simplifyAndConvertPolynomialToSimplestTerm(Polynomial{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})}));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify3.getAsNumber().getDouble());
}

TEST(ConvertHelpersTest, SimplifyAndConvertExpressionToSimplestTermWorks) {
    Expression const expression1(createExpressionIfPossible({88}));
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
    EXPECT_DOUBLE_EQ(88, termToVerify2.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify3.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify4.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify5.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify5.getAsNumber().getDouble());
}

TEST(ConvertHelpersTest, SimplifyAndConvertFunctionToSimplestTermWorks) {
    Function const function1;
    Function const function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function3(
        "functionName", Term(createExpressionIfPossible({5, "+", 5})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    Term const termToVerify1(simplifyAndConvertFunctionToSimplestTerm(function1));
    Term const termToVerify2(simplifyAndConvertFunctionToSimplestTerm(function2));
    Term const termToVerify3(simplifyAndConvertFunctionToSimplestTerm(function3));

    ASSERT_TRUE(termToVerify1.isFunction());
    EXPECT_EQ(function1, termToVerify1.getAsFunction());
    EXPECT_EQ(Term(5), termToVerify2);
    EXPECT_EQ(Term(10), termToVerify3);
}

TEST(ConvertHelpersTest, ConvertMonomialToSimplestTermWorks) {
    Term const termToVerify1(convertMonomialToSimplestTerm(Monomial()));
    Term const termToVerify2(convertMonomialToSimplestTerm(Monomial(6, {})));
    Term const termToVerify3(convertMonomialToSimplestTerm(Monomial(1, {{"x", 1}})));
    Term const termToVerify4(convertMonomialToSimplestTerm(Monomial(10, {{"x", 0}})));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Variable, termToVerify3.getTermType());
    EXPECT_EQ("x", termToVerify3.getAsVariable().getVariableName());
    ASSERT_EQ(TermType::Monomial, termToVerify4.getTermType());
    Monomial const monomialToExpect(10, {{"x", 0}});
    EXPECT_EQ(monomialToExpect, termToVerify4.getAsMonomial());
}

TEST(ConvertHelpersTest, ConvertPolynomialToSimplestTermWorks) {
    Term const termToVerify1(convertPolynomialToSimplestTerm(Polynomial{}));
    Term const termToVerify2(convertPolynomialToSimplestTerm(Polynomial{Monomial(6, {})}));
    Term const termToVerify3(
        convertPolynomialToSimplestTerm(Polynomial{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})}));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getAsNumber().getDouble());
    ASSERT_EQ(TermType::Polynomial, termToVerify3.getTermType());
    Polynomial const polynomialToExpect{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})};
    EXPECT_EQ(polynomialToExpect, termToVerify3.getAsPolynomial());
}

TEST(ConvertHelpersTest, ConvertExpressionToSimplestTermWorks) {
    Term const termToVerify1(convertExpressionToSimplestTerm(createExpressionIfPossible({})));
    Term const termToVerify2(convertExpressionToSimplestTerm(createExpressionIfPossible({156})));
    Term const termToVerify3(convertExpressionToSimplestTerm(createExpressionIfPossible({Monomial(444, {})})));
    Term const termToVerify4(convertExpressionToSimplestTerm(createExpressionIfPossible({1, "/", Monomial(444, {})})));

    EXPECT_EQ(Term(), termToVerify1);
    EXPECT_EQ(Term(156), termToVerify2);
    EXPECT_EQ(Term(444), termToVerify3);
    Term const termToExpect4(createExpressionIfPossible({1, "/", Monomial(444, {})}));
    EXPECT_EQ(termToExpect4, termToVerify4);
}

TEST(ConvertHelpersTest, ConvertFunctionToSimplestTermWorks) {
    Function const function1;
    Function const function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function3("functionName", Term("x"), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term const multiplicationAndDivisionExpression(createExpressionIfPossible({"x", "*", "y", "/", "z"}));

    Term const termToVerify1(convertFunctionToSimplestTerm(function1));
    Term const termToVerify2(convertFunctionToSimplestTerm(function2));
    Term const termToVerify3(convertFunctionToSimplestTerm(function3));
    Term const termToVerify4(convertFunctionToSimplestTerm(ln(multiplicationAndDivisionExpression)));

    Term const termToExpect(createExpressionIfPossible({ln("x"), "+", ln("y"), "-", ln("z")}));
    ASSERT_TRUE(termToVerify1.isFunction());
    EXPECT_EQ(function1, termToVerify1.getAsFunction());
    EXPECT_EQ(Term(5), termToVerify2);
    ASSERT_TRUE(termToVerify3.isFunction());
    EXPECT_EQ(function3, termToVerify3.getAsFunction());
    EXPECT_EQ(termToExpect, termToVerify4);
}

TEST(ConvertHelpersTest, CanBeConvertedToConstantWorks) {
    EXPECT_TRUE(canBeConvertedToConstant(Polynomial()));
    EXPECT_TRUE(canBeConvertedToConstant(Polynomial{Monomial(96, {})}));
    EXPECT_FALSE(canBeConvertedToConstant(Polynomial{Monomial(96, {{"x", 1}})}));
    EXPECT_FALSE(canBeConvertedToConstant(Polynomial{Monomial(96, {}), Monomial(96, {{"x", 1}})}));
}

TEST(ConvertHelpersTest, CanBeConvertedToMonomialWorks) {
    EXPECT_FALSE(canBeConvertedToMonomial(Term()));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(0)));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(15)));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Variable("x"))));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(Polynomial{Monomial(96, {{"x", 1}}), Monomial(73, {{"y", 1}})})));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(createExpressionIfPossible({254}))));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(Expression())));
}

TEST(ConvertHelpersTest, CanBeConvertedToPolynomialWorks) {
    EXPECT_FALSE(canBeConvertedToPolynomial(Term()));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(0)));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(15)));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Variable("x"))));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(canBeConvertedToPolynomial(Term(createExpressionIfPossible({254}))));
    EXPECT_FALSE(canBeConvertedToPolynomial(Term(Expression())));
}

}  // namespace alba::algebra
