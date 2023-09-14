#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Operators/TermTypeOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusConstantOperationWorks) {
    Term term(+Constant(6));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusVariableOperationWorks) {
    Term term(+Variable("x"));

    EXPECT_EQ(Term("x"), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusMonomialOperationWorks) {
    Term term(+Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusPolynomialOperationWorks) {
    Term term(+Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusExpressionOperationWorks) {
    Term term(+createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({54})), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(+absoluteValueFunction);

    EXPECT_EQ(Term(absoluteValueFunction), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusConstantOperationWorks) {
    Term term(-Constant(6));

    EXPECT_EQ(Term(-6), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusVariableOperationWorks) {
    Term term(-Variable("x"));

    EXPECT_EQ(Term(Monomial(-1, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusMonomialOperationWorks) {
    Term term(-Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(-4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusPolynomialOperationWorks) {
    Term term(-Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusExpressionOperationWorks) {
    Term term(-createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({-1, "*", 54})), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(-absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({-1, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() + Constant(2));

    EXPECT_EQ(Term(2), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) + Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddConstantOperationWorks) {
    Term term(Constant(6) + Constant(2));

    EXPECT_EQ(Term(8), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddVariableOperationWorks) {
    Term term(Constant(5) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) + Monomial(2, {}));

    EXPECT_EQ(Term(10), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddPolynomialOperationWorks) {
    Term term(Constant(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddExpressionOperationWorks) {
    Term term(Constant(10) + createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddTermOperationWorks) {
    Term term(Constant(10) + Term(5));

    EXPECT_EQ(Term(15), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddConstantOperationWorks) {
    Term term(Variable("y") + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") + Variable("i"));

    EXPECT_EQ(Term(Monomial(2, {{"i", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") + Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(1, {{"j", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") + Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") + Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddPolynomialOperationWorks) {
    Term term(Variable("x") + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddExpressionOperationWorks) {
    Term term(Variable("x") + createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddTermOperationWorks) {
    Term term(Variable("y") + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) + Constant(2));

    EXPECT_EQ(Term(10), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(12, {{"x", 2}})), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddPolynomialOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) + createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddPolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} + Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(20, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddPolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({54, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) + absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddPolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "+", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddConstantOperationWorks) {
    Term term(Term(5) + Constant(10));

    EXPECT_EQ(Term(15), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddVariableOperationWorks) {
    Term term(Term(4) + Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddMonomialOperationWorks) {
    Term term(Term(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddPolynomialOperationWorks) {
    Term term(Term(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddExpressionOperationWorks) {
    Term term(Term(10) + createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() - Constant(2));

    EXPECT_EQ(Term(-2), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) - Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractConstantOperationWorks) {
    Term term(Constant(6) - Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractVariableOperationWorks) {
    Term term(Constant(5) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) - Monomial(2, {}));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractPolynomialOperationWorks) {
    Term term(Constant(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractExpressionOperationWorks) {
    Term term(Constant(10) - createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractTermOperationWorks) {
    Term term(Constant(6) - Term(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractConstantOperationWorks) {
    Term term(Variable("y") - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") - Variable("i"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") - Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(-1, {{"j", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") - Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(-6, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") - Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-7, {{"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractPolynomialOperationWorks) {
    Term term(Variable("x") - Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-3, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractExpressionOperationWorks) {
    Term term(Variable("x") - createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractTermOperationWorks) {
    Term term(Variable("y") - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) - Constant(2));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Monomial(6, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialThatResultsInZeroOperationWorks) {
    Term term(Monomial(4, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 2}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(-4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractPolynomialOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) - createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(7, {{"x", 1}})} - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractPolynomialThatResultsInZeroOperationWorks) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractPolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(-10, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractPolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({54, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) - absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractPolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "-", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractConstantOperationWorks) {
    Term term(Term(5) - Constant(10));

    EXPECT_EQ(Term(-5), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractVariableOperationWorks) {
    Term term(Term(4) - Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractMonomialOperationWorks) {
    Term term(Term(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractPolynomialOperationWorks) {
    Term term(Term(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractExpressionOperationWorks) {
    Term term(Term(10) - createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() * Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) * Term());

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyConstantOperationWorks) {
    Term term(Constant(6) * Constant(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyVariableOperationWorks) {
    Term term(Constant(5) * Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) * Monomial(2, {}));

    EXPECT_EQ(Term(16), term);
}

TEST(
    TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyPolynomialOperationWorks) {
    Term term(Constant(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyExpressionOperationWorks) {
    Term term(Constant(10) * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyTermOperationWorks) {
    Term term(Constant(6) * Term(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyConstantOperationWorks) {
    Term term(Variable("y") * Constant(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") * Variable("i"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 2}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") * Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") * Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(
    TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") * Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyPolynomialOperationWorks) {
    Term term(Variable("x") * Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyExpressionOperationWorks) {
    Term term(Variable("x") * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyTermOperationWorks) {
    Term term(Variable("y") * Term(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) * Constant(2));

    EXPECT_EQ(Term(16), term);
}

TEST(
    TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Constant(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(
    TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 3}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyPolynomialOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Term(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})} * Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyPolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Polynomial{Monomial(2, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(10, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible(
        {createExpressionIfPossible({Monomial(5, {}), "*", 54}), "+",
         createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", 54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyPolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(createExpressionIfPossible(
        {createExpressionIfPossible({54, "*", Monomial(5, {})}), "+",
         createExpressionIfPossible({54, "*", Monomial(1, {{"x", 1}})})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) * createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) * absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyPolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "*", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "*", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyConstantOperationWorks) {
    Term term(Term(2) * Constant(6));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyVariableOperationWorks) {
    Term term(Term(4) * Variable("y"));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyMonomialOperationWorks) {
    Term term(Term(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyPolynomialOperationWorks) {
    Term term(Term(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyExpressionOperationWorks) {
    Term term(Term(10) * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() / Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) / Term());

    EXPECT_EQ(getPositiveInfinityAsATerm(), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideConstantOperationWorks) {
    Term term(Constant(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideVariableOperationWorks) {
    Term term(Constant(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) / Monomial(2, {}));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDividePolynomialOperationWorks) {
    Term term(Constant(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideExpressionOperationWorks) {
    Term term(Constant(10) / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideTermOperationWorks) {
    Term term(Constant(6) / Term(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideConstantOperationWorks) {
    Term term(Variable("y") / Constant(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") / Variable("i"));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") / Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") / Monomial(4, {{"x", 1}}));

    EXPECT_EQ(Term(0.25), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") / Monomial(4, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(0.25, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDividePolynomialOperationWorks) {
    Term term(Variable("x") / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Variable("x"), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideExpressionOperationWorks) {
    Term term(Variable("x") / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideTermOperationWorks) {
    Term term(Variable("y") / Term(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) / Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Constant(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) / Variable("x"));

    EXPECT_EQ(Term(7), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) / Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", -1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(2), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDividePolynomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Monomial(8, {{"x", 2}}), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Term(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 2}})} / Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {{"x", -1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 2}})} / Monomial(2, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(0.5, {{"x", 1}}), Monomial(2.5, {{"x", -1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDividePolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} / Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})}, "/",
             Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDividePolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({54, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) / createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) / absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDividePolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "/", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideConstantOperationWorks) {
    Term term(Term(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideVariableOperationWorks) {
    Term term(Term(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideMonomialOperationWorks) {
    Term term(Term(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDividePolynomialOperationWorks) {
    Term term(Term(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideExpressionOperationWorks) {
    Term term(Term(10) / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() ^ Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) ^ Term());

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerConstantOperationWorks) {
    Term term(Constant(6) ^ Constant(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerConstantOperationWithZeroExponentWorks) {
    Term term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerVariableOperationWorks) {
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(5), "^", Variable("x")})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorConstantRaiseToPowerMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) ^ Monomial(2, {}));

    EXPECT_EQ(Term(64), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorConstantRaiseToPowerMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(4), "^", Monomial(6, {{"x", 2}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerPolynomialOperationWorks) {
    Term term(Constant(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerExpressionOperationWorks) {
    Term term(Constant(10) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerTermOperationWorks) {
    Term term(Constant(6) ^ Term(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerConstantOperationWorks) {
    Term term(Variable("y") ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") ^ Variable("i"));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("i"), "^", Variable("i")})), term);
}

TEST(
    TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") ^ Variable("j"));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("i"), "^", Variable("j")})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorVariableRaiseToPowerMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") ^ Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("x"), "^", Monomial(7, {{"x", 1}})})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorVariableRaiseToPowerMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") ^ Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("x"), "^", Monomial(7, {{"y", 1}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerPolynomialOperationWorks) {
    Term term(Variable("x") ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Variable("x"), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerExpressionOperationWorks) {
    Term term(Variable("x") ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerTermOperationWorks) {
    Term term(Variable("y") ^ Term(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) ^ Constant(2));

    EXPECT_EQ(Term(64), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(7, {{"x", 1}}), "^", Variable("x")})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(7, {{"y", 1}}), "^", Variable("x")})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 2}})})), term);
}

TEST(
    TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(
        Term(createExpressionIfPossible({Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 1}, {"y", 1}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerPolynomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Monomial(8, {{"x", 2}}), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Term(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerZeroOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 0);

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerPositiveConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(3));

    EXPECT_EQ(
        Term(
            Polynomial{Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerNegativeConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(-3));

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Constant(1), "/",
             Polynomial{
                 Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Variable("x"));

    EXPECT_EQ(
        Term(createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", Variable("x")})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Monomial(8, {{"x", 2}}));

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", Monomial(8, {{"x", 2}})})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerPolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} ^ Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})}, "^",
             Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Term(3));

    EXPECT_EQ(
        Term(
            Polynomial{Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerPolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({54, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) ^ absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerPolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "^", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerConstantOperationWithZeroExponentWorks) {
    Term term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerVariableOperationWorks) {
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(5), "^", Variable("x")})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerMonomialOperationWorks) {
    Term term(Term(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(4), "^", Monomial(6, {{"x", 2}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerPolynomialOperationWorks) {
    Term term(Term(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerExpressionOperationWorks) {
    Term term(Term(10) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenSubtractingSameConstant) {
    Term term(Constant(24) - Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenSubtractingSameVariable) {
    Term term(Variable("power") - Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenSubtractingSameMonomial) {
    Term term(Monomial(15, {{"x", 4}}) - Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenSubtractingSamePolynomial) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})} - Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenMultiplyingZeroToConstant) {
    Term term(0 * Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenMultiplyingZeroToVariable) {
    Term term(0 * Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenMultiplyingZeroToMonomial) {
    Term term(0 * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenMultiplyingZeroToPolynomial) {
    Term term(0 * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsSameWhenMultiplyingOneToConstant) {
    Term term(Constant(1) * Constant(24));

    EXPECT_EQ(Term(24), term);
}

TEST(TermTypeOperatorsTest, ValueIsSameWhenMultiplyingOneToVariable) {
    Term term(Constant(1) * Variable("power"));

    EXPECT_EQ(Term(Variable("power")), term);
}

TEST(TermTypeOperatorsTest, ValueIsSameWhenMultiplyingOneToMonomial) {
    Term term(Constant(1) * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(Monomial(15, {{"x", 4}})), term);
}

TEST(TermTypeOperatorsTest, ValueIsSameWhenMultiplyingOneToPolynomial) {
    Term term(Constant(1) * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 7}}), Monomial(5, {})}), term);
}

}  // namespace alba::algebra
