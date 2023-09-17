#include <Algebra/Simplification/SimplificationOfEquation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra::Simplification {

TEST(SimplificationOfEquationTest, SimplifyWorksOnEqualityOperator) {
    SimplificationOfEquation simplification(Equation("x", "=", "y"));

    simplification.simplify();

    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(
        Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnLessThanOperator) {
    SimplificationOfEquation simplification(Equation("x", "<", "y"));

    simplification.simplify();

    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(
        Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("<", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnGreaterThanOperator) {
    SimplificationOfEquation simplification(Equation("x", ">", "y"));

    simplification.simplify();

    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(
        Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ(">", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnLessThanOrEqualOperator) {
    SimplificationOfEquation simplification(Equation("x", "<=", "y"));

    simplification.simplify();

    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(
        Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("<=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksToHaveCommonDenominator) {
    Polynomial const denominatorLeft{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial const denominatorRight{Monomial(2, {{"x", 1}}), Monomial(3, {})};
    Expression const expressionLeft(createExpressionIfPossible({1, "/", denominatorLeft}));
    Expression const expressionRight(createExpressionIfPossible({1, "/", denominatorRight}));
    SimplificationOfEquation simplification(Equation(expressionLeft, "=", expressionRight));

    simplification.simplify();

    Polynomial const expectedNumerator{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial const expectedDenominator{Monomial(2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(3, {})};
    Equation const simplifiedEquation(simplification.getEquation());
    Term const expectedTerm(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expectedTerm, simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnSimplifyingAnExpression) {
    Expression const expression(createExpressionIfPossible({"x", "/", 523}));
    SimplificationOfEquation simplification(Equation(expression, "=", 0));

    simplification.simplify();

    Equation const simplifiedEquation(simplification.getEquation());
    Term const expectedTerm("x");
    EXPECT_EQ(expectedTerm, simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnNegatingTermIfNeeded) {
    SimplificationOfEquation simplification1(Equation("x", "=", "y"));
    SimplificationOfEquation simplification2(Equation("x", "=", "y"));

    simplification1.simplify();
    simplification2.simplify();

    Equation const simplifiedEquation1(simplification1.getEquation());
    EXPECT_EQ(
        Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation1.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation1.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation1.getRightHandTerm());
    Equation const simplifiedEquation2(simplification2.getEquation());
    EXPECT_EQ(
        Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation2.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation2.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation2.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingExponentIfNeeded) {
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Expression const expression(createExpressionIfPossible({polynomial, "^", "x"}));
    SimplificationOfEquation simplification(Equation(expression, "=", 0));

    simplification.simplify();

    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(polynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnCompletingExpressionWithFractionalExponentsIfNeeded) {
    Polynomial const polynomial1{Monomial(-1, {{"x", 1}}), Monomial(1, {})};
    Polynomial const polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Expression const expression(createExpressionIfPossible(
        {polynomial1, "^", AlbaNumber::createFraction(1, 2), "-", polynomial2, "^", AlbaNumber::createFraction(1, 3)}));
    SimplificationOfEquation simplification(Equation(expression, "=", 0));

    simplification.simplify();

    Polynomial const expectedPolynomial{
        Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(3, {})};
    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedPolynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksXPlusOneToTheOneHalf) {
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Expression const expression(createExpressionIfPossible({polynomial, "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfEquation simplification(Equation("y", "=", expression));

    simplification.simplify();

    Polynomial const expectedPolynomial{Monomial(1, {{"y", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-1, {})};
    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedPolynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingCommonConstantsInMonomial) {
    Monomial const monomial(24, {{"x", 2}, {"y", 2}});
    SimplificationOfEquation simplification(Equation(monomial, "=", 0));

    simplification.simplify();

    Monomial const expectedMonomial(1, {{"x", 2}, {"y", 2}});
    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedMonomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingCommonConstantsInPolynomial) {
    Polynomial const polynomial{Monomial(24, {{"x", 2}, {"y", 2}}), Monomial(18, {{"x", 2}})};
    SimplificationOfEquation simplification(Equation(polynomial, "=", 0));

    simplification.simplify();

    Polynomial const expectedPolynomial{Monomial(4, {{"x", 2}, {"y", 2}}), Monomial(3, {{"x", 2}})};
    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedPolynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingCommonConstantsInExpression) {
    Term const xToTheX(createExpressionIfPossible({"x", "^", "x"}));
    Term const yToTheY(createExpressionIfPossible({"y", "^", "y"}));
    Term const expression(createExpressionIfPossible({18, "*", xToTheX, "+", 24, "*", yToTheY}));
    SimplificationOfEquation simplification(Equation(expression, "=", 0));

    simplification.simplify();

    Term const expectedExpression(createExpressionIfPossible({3, "*", xToTheX, "+", 4, "*", yToTheY}));
    Equation const simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedExpression), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

}  // namespace alba::algebra::Simplification
