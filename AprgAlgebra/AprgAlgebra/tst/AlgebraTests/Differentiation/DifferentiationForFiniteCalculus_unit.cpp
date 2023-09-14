#include <Algebra/Differentiation/DifferentiationForFiniteCalculus.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForTerm) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const termToTest(5);

    EXPECT_EQ(Term(0), differentiationForX.differentiate(termToTest));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForConstant) {
    DifferentiationForFiniteCalculus const differentiationForX("x");

    EXPECT_EQ(Term(0), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForVariable) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Polynomial const xPlusOne{Monomial(1, {{"x", 1}}), Monomial(1, {})};

    EXPECT_EQ(Term(xPlusOne), differentiationForX.differentiate(Variable("x")));
    EXPECT_EQ(Term(0), differentiationForX.differentiate(Variable("y")));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForMonomial) {
    DifferentiationForFiniteCalculus const differentiationForX("x");

    Term const termToVerify1(differentiationForX.differentiate(Monomial(13, {})));
    Term const termToVerify2(differentiationForX.differentiate(Monomial(5, {{"x", 7}, {"y", 8}, {"z", 9}})));
    Term const termToVerify3(differentiationForX.differentiate(Monomial(5, {{"x", -2}, {"y", 8}, {"z", 9}})));

    Term const termToExpect1(0);
    Term const termToExpect2(Polynomial(
        {Monomial(35, {{"x", 6}, {"y", 8}, {"z", 9}}), Monomial(105, {{"x", 5}, {"y", 8}, {"z", 9}}),
         Monomial(175, {{"x", 4}, {"y", 8}, {"z", 9}}), Monomial(175, {{"x", 3}, {"y", 8}, {"z", 9}}),
         Monomial(105, {{"x", 2}, {"y", 8}, {"z", 9}}), Monomial(35, {{"x", 1}, {"y", 8}, {"z", 9}}),
         Monomial(5, {{"y", 8}, {"z", 9}})}));
    Term const termToExpect3(createExpressionIfPossible(
        {Monomial(-5, {{"x", -2}, {"y", 8}, {"z", 9}}), "+",
         createExpressionIfPossible(
             {Monomial(5, {{"y", 8}, {"z", 9}}), "/",
              Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}})}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForPolynomial) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Polynomial const polynomial1{Monomial(13, {})};
    Polynomial const polynomial2{Monomial(-1, {{"x", 2}, {"y", -3}}), Monomial(-4, {{"x", 3}, {"z", -6}})};
    Polynomial const polynomial3{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term const termToVerify1(differentiationForX.differentiate(polynomial1));
    Term const termToVerify2(differentiationForX.differentiate(polynomial2));
    Term const termToVerify3(differentiationForX.differentiate(polynomial3));

    Term const termToExpect1(0);
    Term const termToExpect2(Polynomial{
        Monomial(-2, {{"x", 1}, {"y", -3}}), Monomial(-1, {{"y", -3}}), Monomial(-12, {{"x", 2}, {"z", -6}}),
        Monomial(-12, {{"x", 1}, {"z", -6}}), Monomial(-4, {{"z", -6}})});
    Term const polynomial1OfTerm3(Polynomial{Monomial(1, {{"x", -2}, {"y", -3}}), Monomial(4, {{"x", -5}, {"z", -6}})});
    Term const polynomial2OfTerm3(
        Polynomial{Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(2, {{"x", 1}, {"y", 3}}), Monomial(1, {{"y", 3}})});
    Term const polynomial3OfTerm3(Polynomial{
        Monomial(1, {{"x", 5}, {"z", 6}}), Monomial(5, {{"x", 4}, {"z", 6}}), Monomial(10, {{"x", 3}, {"z", 6}}),
        Monomial(10, {{"x", 2}, {"z", 6}}), Monomial(5, {{"x", 1}, {"z", 6}}), Monomial(1, {{"z", 6}})});
    Expression const expression1OfTerm3(createExpressionIfPossible({1, "/", polynomial2OfTerm3}));
    Expression const expression2OfTerm3(createExpressionIfPossible({4, "/", polynomial3OfTerm3}));
    Term const termToExpect3(
        createExpressionIfPossible({polynomial1OfTerm3, "-", expression1OfTerm3, "-", expression2OfTerm3}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForExpression) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression const expression01{createExpressionIfPossible({"x"})};
    Expression const expression02{createExpressionIfPossible({3, "^", "x"})};

    Term const termToVerify1(differentiationForX.differentiate(expression01));
    Term const termToVerify2(differentiationForX.differentiate(expression02));

    Term const termToExpect1(1);
    Term const termToExpect2(createExpressionIfPossible({3, "^", xPlusOne, "-", 3, "^", "x"}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForFunction) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});

    Term const termToVerify(differentiationForX.differentiate(sin("x")));

    Term const termToExpect(createExpressionIfPossible({sin(xPlusOne), "-", sin("x")}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForEquation) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const term1ForEquation(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term const term2ForEquation(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation const equation(term1ForEquation, "=", term2ForEquation);

    Equation const equationToVerify(differentiationForX.differentiate(equation));

    string const stringToExpect("(6[x^5] + 15[x^4] + 20[x^3] + 15[x^2] + 6[x] + -1) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksWithTermRaiseToTerm) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const termToTest1(createExpressionIfPossible({"n", "^", "n"}));
    Term const termToTest2(createExpressionIfPossible({"n", "^", "x"}));
    Term const termToTest3(createExpressionIfPossible({"x", "^", "n"}));
    Term const termToTest4(createExpressionIfPossible({"x", "^", "x"}));

    Term const termToVerify1(differentiationForX.differentiate(termToTest1));
    Term const termToVerify2(differentiationForX.differentiate(termToTest2));
    Term const termToVerify3(differentiationForX.differentiate(termToTest3));
    Term const termToVerify4(differentiationForX.differentiate(termToTest4));

    Term const termToExpect1(0);
    string const stringToExpect2("((n^(1[x] + 1))-(n^x))");
    string const stringToExpect3("(((1[x] + 1)^n)-(x^n))");
    string const stringToExpect4("(((1[x] + 1)^(1[x] + 1))-(x^x))");
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(stringToExpect2, convertToString(termToVerify2));
    EXPECT_EQ(stringToExpect3, convertToString(termToVerify3));
    EXPECT_EQ(stringToExpect4, convertToString(termToVerify4));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateFunctionWorks) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});

    Term const termToVerify(differentiationForX.differentiate(sin("x")));

    Term const termToExpect(createExpressionIfPossible({sin(xPlusOne), "-", sin("x")}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateEquationWorks) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term const term2ForEquation1(
        Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation const equation1(term1ForEquation1, "=", term2ForEquation1);
    Term const term1ForEquation2(Polynomial{Monomial(3, {{"x", 4}, {"y", 2}}), Monomial(-7, {{"x", 1}, {"y", 3}})});
    Term const term2ForEquation2(Polynomial{Monomial(4, {}), Monomial(8, {{"y", 1}})});
    Equation const equation2(term1ForEquation2, "=", term2ForEquation2);

    Equation const equationToVerify1(differentiationForX.differentiate(equation1));
    Equation const equationToVerify2(differentiationForX.differentiate(equation2));

    string const stringToExpect1("(6[x^5] + 15[x^4] + 20[x^3] + 15[x^2] + 6[x] + -1) = 0");
    string const stringToExpect2("(12[x^3][y^2] + 18[x^2][y^2] + 12[x][y^2] + -7[y^3] + 3[y^2]) = 0");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMultipleTimesWorksForTerm) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const termToTest(Monomial(3, {{"x", 4}}));

    Term const termToVerify1(differentiationForX.differentiateMultipleTimes(termToTest, 0));
    Term const termToVerify2(differentiationForX.differentiateMultipleTimes(termToTest, 1));
    Term const termToVerify3(differentiationForX.differentiateMultipleTimes(termToTest, 2));

    Term const termToExpect1(Monomial(3, {{"x", 4}}));
    Term const termToExpect2(
        Polynomial{Monomial(12, {{"x", 3}}), Monomial(18, {{"x", 2}}), Monomial(12, {{"x", 1}}), Monomial(3, {})});
    Term const termToExpect3(Polynomial{Monomial(36, {{"x", 2}}), Monomial(72, {{"x", 1}}), Monomial(42, {})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMultipleTimesWorksForEquation) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Equation const equationToTest(Monomial(3, {{"x", 4}}), "=", Monomial(5, {{"x", 6}}));

    Equation const equationToVerify1(differentiationForX.differentiateMultipleTimes(equationToTest, 0));
    Equation const equationToVerify2(differentiationForX.differentiateMultipleTimes(equationToTest, 1));
    Equation const equationToVerify3(differentiationForX.differentiateMultipleTimes(equationToTest, 2));

    string const stringToExpect1("3[x^4] = 5[x^6]");
    string const stringToExpect2("(30[x^5] + 75[x^4] + 88[x^3] + 57[x^2] + 18[x] + 2) = 0");
    string const stringToExpect3("(75[x^4] + 300[x^3] + 507[x^2] + 414[x] + 134) = 0");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
    EXPECT_EQ(stringToExpect3, convertToString(equationToVerify3));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateVariableWorks) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Polynomial const zeroPolynomial(createPolynomialFromNumber(0));
    Polynomial const xPlusOne{Monomial(1, {{"x", 1}}), Monomial(1, {})};

    EXPECT_EQ(xPlusOne, differentiationForX.differentiateVariable(Variable("x")));
    EXPECT_EQ(zeroPolynomial, differentiationForX.differentiateVariable(Variable("y")));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateTermWorks) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term const polynomialTerm(Polynomial{Monomial(-2, {{"x", 2}}), Monomial(8, {{"x", 1}}), Monomial(5, {})});
    Expression const expressionTerm{createExpressionIfPossible({3, "^", "x"})};

    Term const termToVerify1(differentiationForX.differentiateTerm(5));
    Term const termToVerify2(differentiationForX.differentiateTerm("x"));
    Term const termToVerify3(differentiationForX.differentiateTerm(Monomial(5, {{"x", 3}})));
    Term const termToVerify4(differentiationForX.differentiateTerm(polynomialTerm));
    Term const termToVerify5(differentiationForX.differentiateTerm(expressionTerm));

    Term const termToExpect1(0);
    Term const& termToExpect2(xPlusOne);
    Term const termToExpect3(Polynomial{Monomial(15, {{"x", 2}}), Monomial(15, {{"x", 1}}), Monomial(5, {})});
    Term const termToExpect4(Polynomial{Monomial(-4, {{"x", 1}}), Monomial(6, {})});
    Term const termToExpect5(createExpressionIfPossible({3, "^", xPlusOne, "-", 3, "^", "x"}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMonomialWorks) {
    DifferentiationForFiniteCalculus const differentiationForX("x");

    Term const termToVerify1(differentiationForX.differentiateMonomial(Monomial(13, {})));
    Term const termToVerify2(differentiationForX.differentiateMonomial(Monomial(5, {{"x", 7}, {"y", 8}, {"z", 9}})));
    Term const termToVerify3(differentiationForX.differentiateMonomial(Monomial(5, {{"x", -2}, {"y", 8}, {"z", 9}})));

    Term const termToExpect1(0);
    Term const termToExpect2(Polynomial(
        {Monomial(35, {{"x", 6}, {"y", 8}, {"z", 9}}), Monomial(105, {{"x", 5}, {"y", 8}, {"z", 9}}),
         Monomial(175, {{"x", 4}, {"y", 8}, {"z", 9}}), Monomial(175, {{"x", 3}, {"y", 8}, {"z", 9}}),
         Monomial(105, {{"x", 2}, {"y", 8}, {"z", 9}}), Monomial(35, {{"x", 1}, {"y", 8}, {"z", 9}}),
         Monomial(5, {{"y", 8}, {"z", 9}})}));
    Term const termToExpect3(createExpressionIfPossible(
        {Monomial(-5, {{"x", -2}, {"y", 8}, {"z", 9}}), "+",
         createExpressionIfPossible(
             {Monomial(5, {{"y", 8}, {"z", 9}}), "/",
              Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}})}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiatePolynomialWorks) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Polynomial const polynomial1{Monomial(13, {})};
    Polynomial const polynomial2{Monomial(-1, {{"x", 2}, {"y", -3}}), Monomial(-4, {{"x", 3}, {"z", -6}})};
    Polynomial const polynomial3{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term const termToVerify1(differentiationForX.differentiatePolynomial(polynomial1));
    Term const termToVerify2(differentiationForX.differentiatePolynomial(polynomial2));
    Term const termToVerify3(differentiationForX.differentiatePolynomial(polynomial3));

    Term const termToExpect1(0);
    Term const termToExpect2(Polynomial{
        Monomial(-2, {{"x", 1}, {"y", -3}}), Monomial(-1, {{"y", -3}}), Monomial(-12, {{"x", 2}, {"z", -6}}),
        Monomial(-12, {{"x", 1}, {"z", -6}}), Monomial(-4, {{"z", -6}})});
    Term const polynomial1OfTerm3(Polynomial{Monomial(1, {{"x", -2}, {"y", -3}}), Monomial(4, {{"x", -5}, {"z", -6}})});
    Term const polynomial2OfTerm3(
        Polynomial{Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(2, {{"x", 1}, {"y", 3}}), Monomial(1, {{"y", 3}})});
    Term const polynomial3OfTerm3(Polynomial{
        Monomial(1, {{"x", 5}, {"z", 6}}), Monomial(5, {{"x", 4}, {"z", 6}}), Monomial(10, {{"x", 3}, {"z", 6}}),
        Monomial(10, {{"x", 2}, {"z", 6}}), Monomial(5, {{"x", 1}, {"z", 6}}), Monomial(1, {{"z", 6}})});
    Expression const expression1OfTerm3(createExpressionIfPossible({1, "/", polynomial2OfTerm3}));
    Expression const expression2OfTerm3(createExpressionIfPossible({4, "/", polynomial3OfTerm3}));
    Term const termToExpect3(
        createExpressionIfPossible({polynomial1OfTerm3, "-", expression1OfTerm3, "-", expression2OfTerm3}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateExpressionWorks) {
    DifferentiationForFiniteCalculus const differentiationForX("x");
    Term const xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression const expression01{createExpressionIfPossible({"x"})};
    Expression const expression02{createExpressionIfPossible({3, "^", "x"})};

    Term const termToVerify1(differentiationForX.differentiateExpression(expression01));
    Term const termToVerify2(differentiationForX.differentiateExpression(expression02));

    Term const termToExpect1(1);
    Term const termToExpect2(createExpressionIfPossible({3, "^", xPlusOne, "-", 3, "^", "x"}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateConstantWorks) {
    DifferentiationForFiniteCalculus const differentiationForX("x");

    EXPECT_EQ(AlbaNumber(0), differentiationForX.differentiateConstant(Constant(5)));
}

}  // namespace alba::algebra
