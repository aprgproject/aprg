#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Operators/TermTypeOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusConstantOperationWorks) {
    Term const term(+Constant(6));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusVariableOperationWorks) {
    Term const term(+Variable("x"));

    EXPECT_EQ(Term("x"), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusMonomialOperationWorks) {
    Term const term(+Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusPolynomialOperationWorks) {
    Term const term(+Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusExpressionOperationWorks) {
    Term const term(+createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({54})), term);
}

TEST(TermTypeOperatorsTest, UnaryPlusOperatorPlusFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(+absoluteValueFunction);

    EXPECT_EQ(Term(absoluteValueFunction), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusConstantOperationWorks) {
    Term const term(-Constant(6));

    EXPECT_EQ(Term(-6), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusVariableOperationWorks) {
    Term const term(-Variable("x"));

    EXPECT_EQ(Term(Monomial(-1, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusMonomialOperationWorks) {
    Term const term(-Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(-4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusPolynomialOperationWorks) {
    Term const term(-Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusExpressionOperationWorks) {
    Term const term(-createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({-1, "*", 54})), term);
}

TEST(TermTypeOperatorsTest, UnaryMinusOperatorMinusFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(-absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({-1, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorEmptyAddConstantOperationWorks) {
    Term const term(Term() + Constant(2));

    EXPECT_EQ(Term(2), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddEmptyOperationWorks) {
    Term const term(Constant(6) + Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddConstantOperationWorks) {
    Term const term(Constant(6) + Constant(2));

    EXPECT_EQ(Term(8), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddVariableOperationWorks) {
    Term const term(Constant(5) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddMonomialWithSameMonomialConstantOperationWorks) {
    Term const term(Constant(8) + Monomial(2, {}));

    EXPECT_EQ(Term(10), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddMonomialWithDifferentMonomialConstantOperationWorks) {
    Term const term(Constant(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddPolynomialOperationWorks) {
    Term const term(Constant(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddExpressionOperationWorks) {
    Term const term(Constant(10) + createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Constant(10) + absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorConstantAddTermOperationWorks) {
    Term const term(Constant(10) + Term(5));

    EXPECT_EQ(Term(15), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddConstantOperationWorks) {
    Term const term(Variable("y") + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddVariableWithSameVariableOperationWorks) {
    Term const term(Variable("i") + Variable("i"));

    EXPECT_EQ(Term(Monomial(2, {{"i", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddVariableWithDifferentVariableOperationWorks) {
    Term const term(Variable("i") + Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(1, {{"j", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddMonomialWithSameMonomialVariableOperationWorks) {
    Term const term(Variable("x") + Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddMonomialWithDifferentMonomialVariableOperationWorks) {
    Term const term(Variable("x") + Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddPolynomialOperationWorks) {
    Term const term(Variable("x") + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddExpressionOperationWorks) {
    Term const term(Variable("x") + createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({"x", "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Variable("x") + absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({"x", "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorVariableAddTermOperationWorks) {
    Term const term(Variable("y") + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddConstantWithSameMonomialConstantOperationWorks) {
    Term const term(Monomial(8, {}) + Constant(2));

    EXPECT_EQ(Term(10), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddConstantWithDifferentMonomialConstantOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddVariableWithSameMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"x", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddVariableWithDifferentMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"y", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddMonomialWithSameMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(12, {{"x", 2}})), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddMonomialWithDifferentMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddPolynomialOperationWorks) {
    Term const term(Monomial(3, {{"x", 1}}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddExpressionOperationWorks) {
    Term const term(Monomial(3, {{"x", 1}}) + createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Monomial(3, {{"x", 1}}) + absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorMonomialAddTermOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddConstantOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddVariableOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddMonomialOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddPolynomialOperationWorks) {
    Term const term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} + Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(20, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddExpressionOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorPolynomialAddTermOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddConstantOperationWorks) {
    Term const term(createExpressionIfPossible({54}) + Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddVariableOperationWorks) {
    Term const term(createExpressionIfPossible({54}) + Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({54, "+", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddMonomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) + Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddPolynomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({54, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddExpressionOperationWorks) {
    Term const term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(createExpressionIfPossible({54}) + absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorExpressionAddTermOperationWorks) {
    Term const term(createExpressionIfPossible({54}) + Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddConstantOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction + Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddVariableOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction + Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddMonomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction + Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddPolynomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddExpressionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction + createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "+", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction + absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorFunctionAddTermOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction + Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddConstantOperationWorks) {
    Term const term(Term(5) + Constant(10));

    EXPECT_EQ(Term(15), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddVariableOperationWorks) {
    Term const term(Term(4) + Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddMonomialOperationWorks) {
    Term const term(Term(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddPolynomialOperationWorks) {
    Term const term(Term(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddExpressionOperationWorks) {
    Term const term(Term(10) + createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryPlusOperatorTermAddFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Term(10) + absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorEmptyAddConstantOperationWorks) {
    Term const term(Term() - Constant(2));

    EXPECT_EQ(Term(-2), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantAddEmptyOperationWorks) {
    Term const term(Constant(6) - Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractConstantOperationWorks) {
    Term const term(Constant(6) - Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractVariableOperationWorks) {
    Term const term(Constant(5) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractMonomialWithSameMonomialConstantOperationWorks) {
    Term const term(Constant(8) - Monomial(2, {}));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractMonomialWithDifferentMonomialConstantOperationWorks) {
    Term const term(Constant(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractPolynomialOperationWorks) {
    Term const term(Constant(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractExpressionOperationWorks) {
    Term const term(Constant(10) - createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Constant(10) - absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorConstantSubtractTermOperationWorks) {
    Term const term(Constant(6) - Term(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractConstantOperationWorks) {
    Term const term(Variable("y") - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractVariableWithSameVariableOperationWorks) {
    Term const term(Variable("i") - Variable("i"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractVariableWithDifferentVariableOperationWorks) {
    Term const term(Variable("i") - Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(-1, {{"j", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractMonomialWithSameMonomialVariableOperationWorks) {
    Term const term(Variable("x") - Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(-6, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractMonomialWithDifferentMonomialVariableOperationWorks) {
    Term const term(Variable("x") - Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-7, {{"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractPolynomialOperationWorks) {
    Term const term(Variable("x") - Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-3, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractExpressionOperationWorks) {
    Term const term(Variable("x") - createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({"x", "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Variable("x") - absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({"x", "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorVariableSubtractTermOperationWorks) {
    Term const term(Variable("y") - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractConstantWithSameMonomialConstantOperationWorks) {
    Term const term(Monomial(8, {}) - Constant(2));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractConstantWithDifferentMonomialConstantOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractVariableWithSameMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"x", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Monomial(6, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractVariableWithDifferentMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"y", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialThatResultsInZeroOperationWorks) {
    Term const term(Monomial(4, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialWithSameMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 2}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialWithDifferentMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(-4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractPolynomialOperationWorks) {
    Term const term(Monomial(3, {{"x", 1}}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractExpressionOperationWorks) {
    Term const term(Monomial(3, {{"x", 1}}) - createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Monomial(3, {{"x", 1}}) - absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorMonomialSubtractTermOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractConstantOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractVariableOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(7, {{"x", 1}})} - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractMonomialOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractPolynomialThatResultsInZeroOperationWorks) {
    Term const term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractPolynomialOperationWorks) {
    Term const term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(-10, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractExpressionOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorPolynomialSubtractTermOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractConstantOperationWorks) {
    Term const term(createExpressionIfPossible({54}) - Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractVariableOperationWorks) {
    Term const term(createExpressionIfPossible({54}) - Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({54, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractMonomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) - Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractPolynomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({54, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractExpressionOperationWorks) {
    Term const term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(createExpressionIfPossible({54}) - absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorExpressionSubtractTermOperationWorks) {
    Term const term(createExpressionIfPossible({54}) - Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractConstantOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction - Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractVariableOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction - Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractMonomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction - Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractPolynomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractExpressionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction - createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "-", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    // NOLINTNEXTLINE(misc-redundant-expression)
    Term const term(absoluteValueFunction - absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorFunctionSubtractTermOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction - Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractConstantOperationWorks) {
    Term const term(Term(5) - Constant(10));

    EXPECT_EQ(Term(-5), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractVariableOperationWorks) {
    Term const term(Term(4) - Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractMonomialOperationWorks) {
    Term const term(Term(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractPolynomialOperationWorks) {
    Term const term(Term(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractExpressionOperationWorks) {
    Term const term(Term(10) - createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMinusOperatorTermSubtractFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Term(10) - absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorEmptyAddConstantOperationWorks) {
    Term const term(Term() * Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantAddEmptyOperationWorks) {
    Term const term(Constant(6) * Term());

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyConstantOperationWorks) {
    Term const term(Constant(6) * Constant(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyVariableOperationWorks) {
    Term const term(Constant(5) * Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyMonomialWithSameMonomialConstantOperationWorks) {
    Term const term(Constant(8) * Monomial(2, {}));

    EXPECT_EQ(Term(16), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyMonomialWithDifferentMonomialConstantOperationWorks) {
    Term const term(Constant(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyPolynomialOperationWorks) {
    Term const term(Constant(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyExpressionOperationWorks) {
    Term const term(Constant(10) * createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Constant(10) * absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorConstantMultiplyTermOperationWorks) {
    Term const term(Constant(6) * Term(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyConstantOperationWorks) {
    Term const term(Variable("y") * Constant(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyVariableWithSameVariableOperationWorks) {
    Term const term(Variable("i") * Variable("i"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 2}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyVariableWithDifferentVariableOperationWorks) {
    Term const term(Variable("i") * Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyMonomialWithSameMonomialVariableOperationWorks) {
    Term const term(Variable("x") * Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyMonomialWithDifferentMonomialVariableOperationWorks) {
    Term const term(Variable("x") * Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyPolynomialOperationWorks) {
    Term const term(Variable("x") * Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyExpressionOperationWorks) {
    Term const term(Variable("x") * createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({"x", "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Variable("x") * absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({"x", "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorVariableMultiplyTermOperationWorks) {
    Term const term(Variable("y") * Term(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyConstantWithSameMonomialConstantOperationWorks) {
    Term const term(Monomial(8, {}) * Constant(2));

    EXPECT_EQ(Term(16), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyConstantWithDifferentMonomialConstantOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) * Constant(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyVariableWithSameMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"x", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyVariableWithDifferentMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"y", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyMonomialWithSameMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyMonomialWithDifferentMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 3}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyPolynomialOperationWorks) {
    Term const term(Monomial(3, {{"x", 1}}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyExpressionOperationWorks) {
    Term const term(Monomial(3, {{"x", 1}}) * createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Monomial(3, {{"x", 1}}) * absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyTermOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) * Term(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyConstantOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyVariableOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})} * Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyMonomialOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyPolynomialOperationWorks) {
    Term const term(
        Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Polynomial{Monomial(2, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(10, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyExpressionOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible(
        {createExpressionIfPossible({Monomial(5, {}), "*", 54}), "+",
         createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", 54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyTermOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyConstantOperationWorks) {
    Term const term(createExpressionIfPossible({54}) * Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyVariableOperationWorks) {
    Term const term(createExpressionIfPossible({54}) * Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({54, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyMonomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) * Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyPolynomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(createExpressionIfPossible(
        {createExpressionIfPossible({54, "*", Monomial(5, {})}), "+",
         createExpressionIfPossible({54, "*", Monomial(1, {{"x", 1}})})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyExpressionOperationWorks) {
    Term const term(createExpressionIfPossible({54}) * createExpressionIfPossible({87}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "*", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(createExpressionIfPossible({54}) * absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyTermOperationWorks) {
    Term const term(createExpressionIfPossible({54}) * Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyConstantOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction * Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyVariableOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction * Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyMonomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction * Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyPolynomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "*", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyExpressionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction * createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "*", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction * absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyTermOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction * Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyConstantOperationWorks) {
    Term const term(Term(2) * Constant(6));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyVariableOperationWorks) {
    Term const term(Term(4) * Variable("y"));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyMonomialOperationWorks) {
    Term const term(Term(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyPolynomialOperationWorks) {
    Term const term(Term(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyExpressionOperationWorks) {
    Term const term(Term(10) * createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryMultiplyOperatorTermMultiplyFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Term(10) * absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorEmptyAddConstantOperationWorks) {
    Term const term(Term() / Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantAddEmptyOperationWorks) {
    Term const term(Constant(6) / Term());

    EXPECT_EQ(getPositiveInfinityAsATerm(), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideConstantOperationWorks) {
    Term const term(Constant(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideVariableOperationWorks) {
    Term const term(Constant(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideMonomialWithSameMonomialConstantOperationWorks) {
    Term const term(Constant(8) / Monomial(2, {}));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideMonomialWithDifferentMonomialConstantOperationWorks) {
    Term const term(Constant(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDividePolynomialOperationWorks) {
    Term const term(Constant(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideExpressionOperationWorks) {
    Term const term(Constant(10) / createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Constant(10) / absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorConstantDivideTermOperationWorks) {
    Term const term(Constant(6) / Term(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideConstantOperationWorks) {
    Term const term(Variable("y") / Constant(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideVariableWithSameVariableOperationWorks) {
    Term const term(Variable("i") / Variable("i"));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideVariableWithDifferentVariableOperationWorks) {
    Term const term(Variable("i") / Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideMonomialWithSameMonomialVariableOperationWorks) {
    Term const term(Variable("x") / Monomial(4, {{"x", 1}}));

    EXPECT_EQ(Term(0.25), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideMonomialWithDifferentMonomialVariableOperationWorks) {
    Term const term(Variable("x") / Monomial(4, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(0.25, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDividePolynomialOperationWorks) {
    Term const term(Variable("x") / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Variable("x"), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideExpressionOperationWorks) {
    Term const term(Variable("x") / createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({"x", "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Variable("x") / absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({"x", "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorVariableDivideTermOperationWorks) {
    Term const term(Variable("y") / Term(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideConstantWithSameMonomialConstantOperationWorks) {
    Term const term(Monomial(8, {}) / Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideConstantWithDifferentMonomialConstantOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) / Constant(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideVariableWithSameMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"x", 1}}) / Variable("x"));

    EXPECT_EQ(Term(7), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideVariableWithDifferentMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"y", 1}}) / Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", -1}, {"y", 1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideMonomialWithSameMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(2), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideMonomialWithDifferentMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDividePolynomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Monomial(8, {{"x", 2}}), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideExpressionOperationWorks) {
    Term const term(Monomial(3, {{"x", 1}}) / createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Monomial(3, {{"x", 1}}) / absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Monomial(3, {{"x", 1}}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorMonomialDivideTermOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) / Term(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideConstantOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideVariableOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 2}})} / Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {{"x", -1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideMonomialOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 2}})} / Monomial(2, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(0.5, {{"x", 1}}), Monomial(2.5, {{"x", -1}})}), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDividePolynomialOperationWorks) {
    Term const term(
        Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} / Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})}, "/",
             Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideExpressionOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorPolynomialDivideTermOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideConstantOperationWorks) {
    Term const term(createExpressionIfPossible({54}) / Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideVariableOperationWorks) {
    Term const term(createExpressionIfPossible({54}) / Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({54, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideMonomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) / Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDividePolynomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({54, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideExpressionOperationWorks) {
    Term const term(createExpressionIfPossible({54}) / createExpressionIfPossible({87}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "/", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(createExpressionIfPossible({54}) / absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorExpressionDivideTermOperationWorks) {
    Term const term(createExpressionIfPossible({54}) / Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideConstantOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction / Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideVariableOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction / Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideMonomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction / Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDividePolynomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideExpressionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction / createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "/", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    // NOLINTNEXTLINE(misc-redundant-expression)
    Term const term(absoluteValueFunction / absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorFunctionDivideTermOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction / Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideConstantOperationWorks) {
    Term const term(Term(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideVariableOperationWorks) {
    Term const term(Term(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideMonomialOperationWorks) {
    Term const term(Term(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDividePolynomialOperationWorks) {
    Term const term(Term(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideExpressionOperationWorks) {
    Term const term(Term(10) / createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryDivideOperatorTermDivideFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Term(10) / absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorEmptyAddConstantOperationWorks) {
    Term const term(Term() ^ Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantAddEmptyOperationWorks) {
    Term const term(Constant(6) ^ Term());

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerConstantOperationWorks) {
    Term const term(Constant(6) ^ Constant(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerConstantOperationWithZeroExponentWorks) {
    Term const term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerVariableOperationWorks) {
    Term const term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(5), "^", Variable("x")})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorConstantRaiseToPowerMonomialWithSameMonomialConstantOperationWorks) {
    Term const term(Constant(8) ^ Monomial(2, {}));

    EXPECT_EQ(Term(64), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorConstantRaiseToPowerMonomialWithDifferentMonomialConstantOperationWorks) {
    Term const term(Constant(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(4), "^", Monomial(6, {{"x", 2}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerPolynomialOperationWorks) {
    Term const term(Constant(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerExpressionOperationWorks) {
    Term const term(Constant(10) ^ createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Constant(10) ^ absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerTermOperationWorks) {
    Term const term(Constant(6) ^ Term(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerConstantOperationWorks) {
    Term const term(Variable("y") ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerVariableWithSameVariableOperationWorks) {
    Term const term(Variable("i") ^ Variable("i"));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("i"), "^", Variable("i")})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerVariableWithDifferentVariableOperationWorks) {
    Term const term(Variable("i") ^ Variable("j"));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("i"), "^", Variable("j")})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorVariableRaiseToPowerMonomialWithSameMonomialVariableOperationWorks) {
    Term const term(Variable("x") ^ Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("x"), "^", Monomial(7, {{"x", 1}})})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorVariableRaiseToPowerMonomialWithDifferentMonomialVariableOperationWorks) {
    Term const term(Variable("x") ^ Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("x"), "^", Monomial(7, {{"y", 1}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerPolynomialOperationWorks) {
    Term const term(Variable("x") ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Variable("x"), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerExpressionOperationWorks) {
    Term const term(Variable("x") ^ createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({"x", "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Variable("x") ^ absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({"x", "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerTermOperationWorks) {
    Term const term(Variable("y") ^ Term(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerConstantWithSameMonomialConstantOperationWorks) {
    Term const term(Monomial(8, {}) ^ Constant(2));

    EXPECT_EQ(Term(64), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerConstantWithDifferentMonomialConstantOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerVariableWithSameMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"x", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(7, {{"x", 1}}), "^", Variable("x")})), term);
}

TEST(
    TermTypeOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerVariableWithDifferentMonomialVariableOperationWorks) {
    Term const term(Monomial(7, {{"y", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(7, {{"y", 1}}), "^", Variable("x")})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerMonomialWithSameMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 2}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerMonomialWithDifferentMonomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(
        Term(createExpressionIfPossible({Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 1}, {"y", 1}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerPolynomialOperationWorks) {
    Term const term(Monomial(8, {{"x", 2}}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Monomial(8, {{"x", 2}}), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerExpressionOperationWorks) {
    Term const term(Monomial(3, {{"x", 1}}) ^ createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Monomial(3, {{"x", 1}}) ^ absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Monomial(3, {{"x", 1}}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerTermOperationWorks) {
    Term const term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Term(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerZeroOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 0);

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerPositiveConstantOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(3));

    EXPECT_EQ(
        Term(
            Polynomial{Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerNegativeConstantOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(-3));

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Constant(1), "/",
             Polynomial{
                 Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerVariableOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Variable("x"));

    EXPECT_EQ(
        Term(createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", Variable("x")})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerMonomialOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Monomial(8, {{"x", 2}}));

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", Monomial(8, {{"x", 2}})})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerPolynomialOperationWorks) {
    Term const term(
        Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} ^ Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})}, "^",
             Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerExpressionOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerTermOperationWorks) {
    Term const term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Term(3));

    EXPECT_EQ(
        Term(
            Polynomial{Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerConstantOperationWorks) {
    Term const term(createExpressionIfPossible({54}) ^ Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerVariableOperationWorks) {
    Term const term(createExpressionIfPossible({54}) ^ Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({54, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerMonomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) ^ Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerPolynomialOperationWorks) {
    Term const term(createExpressionIfPossible({54}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({54, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerExpressionOperationWorks) {
    Term const term(createExpressionIfPossible({54}) ^ createExpressionIfPossible({87}));

    Expression const expressionToExpect(createExpressionIfPossible({54, "^", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(createExpressionIfPossible({54}) ^ absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerTermOperationWorks) {
    Term const term(createExpressionIfPossible({54}) ^ Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerConstantOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction ^ Constant(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerVariableOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction ^ Variable("x"));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerMonomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction ^ Monomial(3, {{"x", 1}}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerPolynomialOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerExpressionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction ^ createExpressionIfPossible({54}));

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "^", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    // NOLINTNEXTLINE(misc-redundant-expression)
    Term const term(absoluteValueFunction ^ absoluteValueFunction);

    Expression const expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerTermOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(absoluteValueFunction ^ Term(10));

    Expression const expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerConstantOperationWithZeroExponentWorks) {
    Term const term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerVariableOperationWorks) {
    Term const term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(5), "^", Variable("x")})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerMonomialOperationWorks) {
    Term const term(Term(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(4), "^", Monomial(6, {{"x", 2}})})), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerPolynomialOperationWorks) {
    Term const term(Term(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerExpressionOperationWorks) {
    Term const term(Term(10) ^ createExpressionIfPossible({54}));

    Expression const expressionToExpect(createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerFunctionOperationWorks) {
    Function const absoluteValueFunction(abs(Expression{}));

    Term const term(Term(10) ^ absoluteValueFunction);

    Expression const expressionToExpect(createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenSubtractingSameConstant) {
    Term const term(Constant(24) - Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenSubtractingSameVariable) {
    Term const term(Variable("power") - Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenSubtractingSameMonomial) {
    Term const term(Monomial(15, {{"x", 4}}) - Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenSubtractingSamePolynomial) {
    Term const term(
        Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})} - Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenMultiplyingZeroToConstant) {
    Term const term(0 * Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenMultiplyingZeroToVariable) {
    Term const term(0 * Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenMultiplyingZeroToMonomial) {
    Term const term(0 * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsZeroWhenMultiplyingZeroToPolynomial) {
    Term const term(0 * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypeOperatorsTest, ValueIsSameWhenMultiplyingOneToConstant) {
    Term const term(Constant(1) * Constant(24));

    EXPECT_EQ(Term(24), term);
}

TEST(TermTypeOperatorsTest, ValueIsSameWhenMultiplyingOneToVariable) {
    Term const term(Constant(1) * Variable("power"));

    EXPECT_EQ(Term(Variable("power")), term);
}

TEST(TermTypeOperatorsTest, ValueIsSameWhenMultiplyingOneToMonomial) {
    Term const term(Constant(1) * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(Monomial(15, {{"x", 4}})), term);
}

TEST(TermTypeOperatorsTest, ValueIsSameWhenMultiplyingOneToPolynomial) {
    Term const term(Constant(1) * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 7}}), Monomial(5, {})}), term);
}

}  // namespace alba::algebra
