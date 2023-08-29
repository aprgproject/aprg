#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Operators/TermTypeOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(TermTypesOperatorsTest, UnaryPlusOperatorPlusConstantOperationWorks) {
    Term term(+Constant(6));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperatorPlusVariableOperationWorks) {
    Term term(+Variable("x"));

    EXPECT_EQ(Term("x"), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperatorPlusMonomialOperationWorks) {
    Term term(+Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperatorPlusPolynomialOperationWorks) {
    Term term(+Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperatorPlusExpressionOperationWorks) {
    Term term(+createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({54})), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperatorPlusFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(+absoluteValueFunction);

    EXPECT_EQ(Term(absoluteValueFunction), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperatorMinusConstantOperationWorks) {
    Term term(-Constant(6));

    EXPECT_EQ(Term(-6), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperatorMinusVariableOperationWorks) {
    Term term(-Variable("x"));

    EXPECT_EQ(Term(Monomial(-1, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperatorMinusMonomialOperationWorks) {
    Term term(-Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(-4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperatorMinusPolynomialOperationWorks) {
    Term term(-Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperatorMinusExpressionOperationWorks) {
    Term term(-createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({-1, "*", 54})), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperatorMinusFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(-absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({-1, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() + Constant(2));

    EXPECT_EQ(Term(2), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) + Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddConstantOperationWorks) {
    Term term(Constant(6) + Constant(2));

    EXPECT_EQ(Term(8), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddVariableOperationWorks) {
    Term term(Constant(5) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) + Monomial(2, {}));

    EXPECT_EQ(Term(10), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddPolynomialOperationWorks) {
    Term term(Constant(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddExpressionOperationWorks) {
    Term term(Constant(10) + createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorConstantAddTermOperationWorks) {
    Term term(Constant(10) + Term(5));

    EXPECT_EQ(Term(15), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddConstantOperationWorks) {
    Term term(Variable("y") + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") + Variable("i"));

    EXPECT_EQ(Term(Monomial(2, {{"i", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") + Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(1, {{"j", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") + Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") + Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddPolynomialOperationWorks) {
    Term term(Variable("x") + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddExpressionOperationWorks) {
    Term term(Variable("x") + createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorVariableAddTermOperationWorks) {
    Term term(Variable("y") + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) + Constant(2));

    EXPECT_EQ(Term(10), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(12, {{"x", 2}})), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddPolynomialOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) + createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorMonomialAddTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorPolynomialAddConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorPolynomialAddVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorPolynomialAddMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorPolynomialAddPolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} + Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(20, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorPolynomialAddExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorPolynomialAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorPolynomialAddTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorExpressionAddConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorExpressionAddVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorExpressionAddMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorExpressionAddPolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({54, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorExpressionAddExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorExpressionAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) + absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorExpressionAddTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) + Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorFunctionAddConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorFunctionAddVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorFunctionAddMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorFunctionAddPolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorFunctionAddExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "+", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorFunctionAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorFunctionAddTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorTermAddConstantOperationWorks) {
    Term term(Term(5) + Constant(10));

    EXPECT_EQ(Term(15), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorTermAddVariableOperationWorks) {
    Term term(Term(4) + Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorTermAddMonomialOperationWorks) {
    Term term(Term(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorTermAddPolynomialOperationWorks) {
    Term term(Term(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorTermAddExpressionOperationWorks) {
    Term term(Term(10) + createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperatorTermAddFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) + absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() - Constant(2));

    EXPECT_EQ(Term(-2), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) - Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantSubtractConstantOperationWorks) {
    Term term(Constant(6) - Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantSubtractVariableOperationWorks) {
    Term term(Constant(5) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantSubtractMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) - Monomial(2, {}));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantSubtractMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantSubtractPolynomialOperationWorks) {
    Term term(Constant(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantSubtractExpressionOperationWorks) {
    Term term(Constant(10) - createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorConstantSubtractTermOperationWorks) {
    Term term(Constant(6) - Term(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractConstantOperationWorks) {
    Term term(Variable("y") - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") - Variable("i"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") - Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(-1, {{"j", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") - Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(-6, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") - Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-7, {{"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractPolynomialOperationWorks) {
    Term term(Variable("x") - Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-3, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractExpressionOperationWorks) {
    Term term(Variable("x") - createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorVariableSubtractTermOperationWorks) {
    Term term(Variable("y") - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) - Constant(2));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Monomial(6, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialThatResultsInZeroOperationWorks) {
    Term term(Monomial(4, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 2}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(-4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractPolynomialOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) - createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorMonomialSubtractTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorPolynomialSubtractConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorPolynomialSubtractVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(7, {{"x", 1}})} - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorPolynomialSubtractMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorPolynomialSubtractPolynomialThatResultsInZeroOperationWorks) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorPolynomialSubtractPolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(-10, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorPolynomialSubtractExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorPolynomialSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorPolynomialSubtractTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorExpressionSubtractConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorExpressionSubtractVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorExpressionSubtractMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorExpressionSubtractPolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({54, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorExpressionSubtractExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorExpressionSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) - absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorExpressionSubtractTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) - Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorFunctionSubtractConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorFunctionSubtractVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorFunctionSubtractMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorFunctionSubtractPolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorFunctionSubtractExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "-", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorFunctionSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorFunctionSubtractTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorTermSubtractConstantOperationWorks) {
    Term term(Term(5) - Constant(10));

    EXPECT_EQ(Term(-5), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorTermSubtractVariableOperationWorks) {
    Term term(Term(4) - Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorTermSubtractMonomialOperationWorks) {
    Term term(Term(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorTermSubtractPolynomialOperationWorks) {
    Term term(Term(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorTermSubtractExpressionOperationWorks) {
    Term term(Term(10) - createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperatorTermSubtractFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) - absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() * Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) * Term());

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorConstantMultiplyConstantOperationWorks) {
    Term term(Constant(6) * Constant(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorConstantMultiplyVariableOperationWorks) {
    Term term(Constant(5) * Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorConstantMultiplyMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) * Monomial(2, {}));

    EXPECT_EQ(Term(16), term);
}

TEST(
    TermTypesOperatorsTest, BinaryMultiplyOperatorConstantMultiplyMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorConstantMultiplyPolynomialOperationWorks) {
    Term term(Constant(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorConstantMultiplyExpressionOperationWorks) {
    Term term(Constant(10) * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorConstantMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorConstantMultiplyTermOperationWorks) {
    Term term(Constant(6) * Term(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyConstantOperationWorks) {
    Term term(Variable("y") * Constant(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") * Variable("i"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 2}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") * Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") * Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(
    TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") * Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyPolynomialOperationWorks) {
    Term term(Variable("x") * Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyExpressionOperationWorks) {
    Term term(Variable("x") * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorVariableMultiplyTermOperationWorks) {
    Term term(Variable("y") * Term(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) * Constant(2));

    EXPECT_EQ(Term(16), term);
}

TEST(
    TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Constant(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(
    TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 3}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyPolynomialOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorMonomialMultiplyTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Term(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})} * Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyPolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Polynomial{Monomial(2, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(10, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible(
        {createExpressionIfPossible({Monomial(5, {}), "*", 54}), "+",
         createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", 54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorPolynomialMultiplyTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyPolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(createExpressionIfPossible(
        {createExpressionIfPossible({54, "*", Monomial(5, {})}), "+",
         createExpressionIfPossible({54, "*", Monomial(1, {{"x", 1}})})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) * createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) * absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorExpressionMultiplyTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) * Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyPolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "*", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "*", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorFunctionMultiplyTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorTermMultiplyConstantOperationWorks) {
    Term term(Term(2) * Constant(6));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorTermMultiplyVariableOperationWorks) {
    Term term(Term(4) * Variable("y"));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorTermMultiplyMonomialOperationWorks) {
    Term term(Term(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorTermMultiplyPolynomialOperationWorks) {
    Term term(Term(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorTermMultiplyExpressionOperationWorks) {
    Term term(Term(10) * createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperatorTermMultiplyFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) * absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() / Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) / Term());

    EXPECT_EQ(getPositiveInfinityAsATerm(), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantDivideConstantOperationWorks) {
    Term term(Constant(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantDivideVariableOperationWorks) {
    Term term(Constant(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantDivideMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) / Monomial(2, {}));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantDivideMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantDividePolynomialOperationWorks) {
    Term term(Constant(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantDivideExpressionOperationWorks) {
    Term term(Constant(10) / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorConstantDivideTermOperationWorks) {
    Term term(Constant(6) / Term(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDivideConstantOperationWorks) {
    Term term(Variable("y") / Constant(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDivideVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") / Variable("i"));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDivideVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") / Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDivideMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") / Monomial(4, {{"x", 1}}));

    EXPECT_EQ(Term(0.25), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDivideMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") / Monomial(4, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(0.25, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDividePolynomialOperationWorks) {
    Term term(Variable("x") / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Variable("x"), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDivideExpressionOperationWorks) {
    Term term(Variable("x") / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorVariableDivideTermOperationWorks) {
    Term term(Variable("y") / Term(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) / Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Constant(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) / Variable("x"));

    EXPECT_EQ(Term(7), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) / Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", -1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(2), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDividePolynomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Monomial(8, {{"x", 2}}), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorMonomialDivideTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Term(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorPolynomialDivideConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorPolynomialDivideVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 2}})} / Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {{"x", -1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorPolynomialDivideMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 2}})} / Monomial(2, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(0.5, {{"x", 1}}), Monomial(2.5, {{"x", -1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorPolynomialDividePolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} / Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})}, "/",
             Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorPolynomialDivideExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorPolynomialDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorPolynomialDivideTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorExpressionDivideConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorExpressionDivideVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorExpressionDivideMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorExpressionDividePolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({54, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorExpressionDivideExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) / createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorExpressionDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) / absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorExpressionDivideTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) / Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorFunctionDivideConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorFunctionDivideVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorFunctionDivideMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorFunctionDividePolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorFunctionDivideExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "/", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorFunctionDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorFunctionDivideTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorTermDivideConstantOperationWorks) {
    Term term(Term(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorTermDivideVariableOperationWorks) {
    Term term(Term(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorTermDivideMonomialOperationWorks) {
    Term term(Term(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorTermDividePolynomialOperationWorks) {
    Term term(Term(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorTermDivideExpressionOperationWorks) {
    Term term(Term(10) / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperatorTermDivideFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) / absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorEmptyAddConstantOperationWorks) {
    Term term(Term() ^ Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorConstantAddEmptyOperationWorks) {
    Term term(Constant(6) ^ Term());

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerConstantOperationWorks) {
    Term term(Constant(6) ^ Constant(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerConstantOperationWithZeroExponentWorks) {
    Term term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerVariableOperationWorks) {
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(5), "^", Variable("x")})), term);
}

TEST(
    TermTypesOperatorsTest,
    BinaryRaiseToPowerOperatorConstantRaiseToPowerMonomialWithSameMonomialConstantOperationWorks) {
    Term term(Constant(8) ^ Monomial(2, {}));

    EXPECT_EQ(Term(64), term);
}

TEST(
    TermTypesOperatorsTest,
    BinaryRaiseToPowerOperatorConstantRaiseToPowerMonomialWithDifferentMonomialConstantOperationWorks) {
    Term term(Constant(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(4), "^", Monomial(6, {{"x", 2}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerPolynomialOperationWorks) {
    Term term(Constant(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerExpressionOperationWorks) {
    Term term(Constant(10) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorConstantRaiseToPowerTermOperationWorks) {
    Term term(Constant(6) ^ Term(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerConstantOperationWorks) {
    Term term(Variable("y") ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerVariableWithSameVariableOperationWorks) {
    Term term(Variable("i") ^ Variable("i"));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("i"), "^", Variable("i")})), term);
}

TEST(
    TermTypesOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerVariableWithDifferentVariableOperationWorks) {
    Term term(Variable("i") ^ Variable("j"));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("i"), "^", Variable("j")})), term);
}

TEST(
    TermTypesOperatorsTest,
    BinaryRaiseToPowerOperatorVariableRaiseToPowerMonomialWithSameMonomialVariableOperationWorks) {
    Term term(Variable("x") ^ Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("x"), "^", Monomial(7, {{"x", 1}})})), term);
}

TEST(
    TermTypesOperatorsTest,
    BinaryRaiseToPowerOperatorVariableRaiseToPowerMonomialWithDifferentMonomialVariableOperationWorks) {
    Term term(Variable("x") ^ Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Variable("x"), "^", Monomial(7, {{"y", 1}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerPolynomialOperationWorks) {
    Term term(Variable("x") ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Variable("x"), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerExpressionOperationWorks) {
    Term term(Variable("x") ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({"x", "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({"x", "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorVariableRaiseToPowerTermOperationWorks) {
    Term term(Variable("y") ^ Term(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(
    TermTypesOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerConstantWithSameMonomialConstantOperationWorks) {
    Term term(Monomial(8, {}) ^ Constant(2));

    EXPECT_EQ(Term(64), term);
}

TEST(
    TermTypesOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerConstantWithDifferentMonomialConstantOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(
    TermTypesOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerVariableWithSameMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"x", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(7, {{"x", 1}}), "^", Variable("x")})), term);
}

TEST(
    TermTypesOperatorsTest,
    BinaryRaiseToPowerOperatorMonomialRaiseToPowerVariableWithDifferentMonomialVariableOperationWorks) {
    Term term(Monomial(7, {{"y", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(7, {{"y", 1}}), "^", Variable("x")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerMonomialWithSameMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 2}})})), term);
}

TEST(
    TermTypesOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerMonomialWithDifferentMonomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(
        Term(createExpressionIfPossible({Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 1}, {"y", 1}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerPolynomialOperationWorks) {
    Term term(Monomial(8, {{"x", 2}}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Monomial(8, {{"x", 2}}), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerExpressionOperationWorks) {
    Term term(Monomial(3, {{"x", 1}}) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({Monomial(3, {{"x", 1}}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorMonomialRaiseToPowerTermOperationWorks) {
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Term(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerZeroOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 0);

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerPositiveConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(3));

    EXPECT_EQ(
        Term(
            Polynomial{Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerNegativeConstantOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(-3));

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Constant(1), "/",
             Polynomial{
                 Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerVariableOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Variable("x"));

    EXPECT_EQ(
        Term(createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", Variable("x")})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerMonomialOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Monomial(8, {{"x", 2}}));

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", Monomial(8, {{"x", 2}})})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerPolynomialOperationWorks) {
    Term term(
        Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} ^ Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible(
            {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})}, "^",
             Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerExpressionOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorPolynomialRaiseToPowerTermOperationWorks) {
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Term(3));

    EXPECT_EQ(
        Term(
            Polynomial{Monomial(1, {{"x", 3}}), Monomial(15, {{"x", 2}}), Monomial(75, {{"x", 1}}), Monomial(125, {})}),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerConstantOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerVariableOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerMonomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerPolynomialOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({54, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerExpressionOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ createExpressionIfPossible({87}));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) ^ absoluteValueFunction);

    Expression expressionToExpect(
        createExpressionIfPossible({createExpressionIfPossible({54}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorExpressionRaiseToPowerTermOperationWorks) {
    Term term(createExpressionIfPossible({54}) ^ Term(10));

    Expression expressionToExpect(createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerConstantOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Constant(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerVariableOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Variable("x"));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerMonomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerPolynomialOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerExpressionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
        createExpressionIfPossible({absoluteValueFunction, "^", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorFunctionRaiseToPowerTermOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Term(10));

    Expression expressionToExpect(createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerConstantOperationWithZeroExponentWorks) {
    Term term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerVariableOperationWorks) {
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(5), "^", Variable("x")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerMonomialOperationWorks) {
    Term term(Term(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible({Constant(4), "^", Monomial(6, {{"x", 2}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerPolynomialOperationWorks) {
    Term term(Term(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(
        Term(createExpressionIfPossible({Constant(10), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})),
        term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerExpressionOperationWorks) {
    Term term(Term(10) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperatorTermRaiseToPowerFunctionOperationWorks) {
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) ^ absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenSubtractingSameConstant) {
    Term term(Constant(24) - Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenSubtractingSameVariable) {
    Term term(Variable("power") - Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenSubtractingSameMonomial) {
    Term term(Monomial(15, {{"x", 4}}) - Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenSubtractingSamePolynomial) {
    Term term(
        Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})} - Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenMultiplyingZeroToConstant) {
    Term term(0 * Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenMultiplyingZeroToVariable) {
    Term term(0 * Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenMultiplyingZeroToMonomial) {
    Term term(0 * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenMultiplyingZeroToPolynomial) {
    Term term(0 * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsSameWhenMultiplyingOneToConstant) {
    Term term(Constant(1) * Constant(24));

    EXPECT_EQ(Term(24), term);
}

TEST(TermTypesOperatorsTest, ValueIsSameWhenMultiplyingOneToVariable) {
    Term term(Constant(1) * Variable("power"));

    EXPECT_EQ(Term(Variable("power")), term);
}

TEST(TermTypesOperatorsTest, ValueIsSameWhenMultiplyingOneToMonomial) {
    Term term(Constant(1) * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(Monomial(15, {{"x", 4}})), term);
}

TEST(TermTypesOperatorsTest, ValueIsSameWhenMultiplyingOneToPolynomial) {
    Term term(Constant(1) * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 7}}), Monomial(5, {})}), term);
}

}  // namespace alba::algebra
