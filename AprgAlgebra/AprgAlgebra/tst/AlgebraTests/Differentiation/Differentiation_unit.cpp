#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(DifferentiationTest, DifferentiateWorksForTerm) {
    Differentiation const differentiationForX("x");
    Term const constantTerm(5);
    Term const variableTerm("x");
    Term const monomialTerm(Monomial(1, {{"x", 8}}));
    Term const polynomialTerm(
        Polynomial{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})});
    Term const expressionTerm(createExpressionIfPossible({cos("x")}));
    Term const functionTerm(sin("x"));

    Term const termToVerify1(differentiationForX.differentiate(constantTerm));
    Term const termToVerify2(differentiationForX.differentiate(variableTerm));
    Term const termToVerify3(differentiationForX.differentiate(monomialTerm));
    Term const termToVerify4(differentiationForX.differentiate(polynomialTerm));
    Term const termToVerify5(differentiationForX.differentiate(expressionTerm));
    Term const termToVerify6(differentiationForX.differentiate(functionTerm));

    Term const termToExpect1(0);
    Term const termToExpect2(1);
    Term const termToExpect3(Monomial(8, {{"x", 7}}));
    Term const termToExpect4(Polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})});
    Term const termToExpect5(createExpressionIfPossible({-1, "*", sin("x")}));
    Term const termToExpect6(cos("x"));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(DifferentiationTest, DifferentiateWorksForConstant) {
    Differentiation const differentiationForX("x");

    EXPECT_EQ(Term(0), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationTest, DifferentiateWorksForVariable) {
    Differentiation const differentiationForXWithY("x", {"y"});

    Term const termToVerify1(differentiationForXWithY.differentiate(Variable("x")));
    Term const termToVerify2(differentiationForXWithY.differentiate(Variable("y")));
    Term const termToVerify3(differentiationForXWithY.differentiate(Variable("a")));

    Term const termToExpect1(1);
    Term const termToExpect2(Variable("d[y]/d[x]"));
    Term const termToExpect3(0);
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationTest, DifferentiateWorksForMonomial) {
    Differentiation const differentiationForXWithY("x", {"y"});

    Term const termToVerify1(differentiationForXWithY.differentiate(Monomial(13, {})));
    Term const termToVerify2(
        differentiationForXWithY.differentiate(Monomial(5, {{"d[y]/d[x]", 6}, {"x", 7}, {"y", 8}, {"z", 9}})));

    Term const termToExpect1(0);
    Term const termToExpect2(Polynomial(
        {Monomial(30, {{"d2[y]/d[x]2", 1}, {"d[y]/d[x]", 5}, {"x", 7}, {"y", 8}, {"z", 9}}),
         Monomial(35, {{"d[y]/d[x]", 6}, {"x", 6}, {"y", 8}, {"z", 9}}),
         Monomial(40, {{"d[y]/d[x]", 1}, {"x", 7}, {"y", 7}, {"z", 9}})}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(DifferentiationTest, DifferentiateWorksForPolynomial) {
    Differentiation const differentiationForXWithY("x", {"y"});
    Polynomial const polynomial1{Monomial(13, {})};
    Polynomial const polynomial2{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term const termToVerify1(differentiationForXWithY.differentiate(polynomial1));
    Term const termToVerify2(differentiationForXWithY.differentiate(polynomial2));

    Term const termToExpect1(0);
    Term const termToExpect2(Polynomial{
        Monomial(3, {{"d[y]/d[x]", 1}, {"x", -2}, {"y", -4}}), Monomial(2, {{"x", -3}, {"y", -3}}),
        Monomial(20, {{"x", -6}, {"z", -6}})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(DifferentiationTest, DifferentiateWorksForExpression) {
    Differentiation const differentiationForX("x");
    Expression const expression01{createExpressionIfPossible({"x"})};
    Expression const expression02{createExpressionIfPossible({cos("x"), "^", 3})};

    Term const termToVerify1(differentiationForX.differentiate(expression01));
    Term const termToVerify2(differentiationForX.differentiate(expression02));

    Term const cosSquared{createExpressionIfPossible({cos("x"), "^", 2})};
    Term const termToExpect01(1);
    Term const termToExpect02(createExpressionIfPossible({-3, "*", cosSquared, "*", sin("x")}));
    EXPECT_EQ(termToExpect01, termToVerify1);
    EXPECT_EQ(termToExpect02, termToVerify2);
}

TEST(DifferentiationTest, DifferentiateWorksForFunction) {
    Differentiation const differentiationForX("x");

    EXPECT_EQ(Term(cos("x")), differentiationForX.differentiate(sin("x")));
}

TEST(DifferentiationTest, DifferentiateWorksForEquation) {
    Differentiation const differentiationForXWithY("x", {"y"});
    Term const term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term const term2ForEquation1(
        Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation const equation1(term1ForEquation1, "=", term2ForEquation1);

    EXPECT_EQ(
        "(18[d[y]/d[x]][y^5] + 5[d[y]/d[x]][y^4] + -6[x^5] + -2[d[y]/d[x]][y] + 2) = 0",
        convertToString(differentiationForXWithY.differentiate(equation1)));
}

TEST(DifferentiationTest, DifferentiateWorksOnOneOverPolynomial) {
    Differentiation const differentiationForX("x");
    Term const numerator(1);
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(2, {})});
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    Term const termToVerify(differentiationForX.differentiate(termToTest));

    Term const expectedNumeratorPart(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term const expectedNumerator(createExpressionIfPossible({-2, "*", expectedNumeratorPart}));
    Term const expectedDenominator(Polynomial{
        Monomial(1, {{"x", 4}}), Monomial(4, {{"x", 3}}), Monomial(8, {{"x", 2}}), Monomial(8, {{"x", 1}}),
        Monomial(4, {})});
    Term const termToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(DifferentiationTest, DifferentiateWorksWithTermRaiseToTerm) {
    Differentiation const differentiationForX("x");
    Term const termToTest1(createExpressionIfPossible({"n", "^", "n"}));
    Term const termToTest2(createExpressionIfPossible({"n", "^", "x"}));
    Term const termToTest3(createExpressionIfPossible({"x", "^", "n"}));
    Term const termToTest4(createExpressionIfPossible({"x", "^", "x"}));

    Term const termToVerify1(differentiationForX.differentiate(termToTest1));
    Term const termToVerify2(differentiationForX.differentiate(termToTest2));
    Term const termToVerify3(differentiationForX.differentiate(termToTest3));
    Term const termToVerify4(differentiationForX.differentiate(termToTest4));

    Term const termToExpect1(0);
    Term const termToExpect2(createExpressionIfPossible({"n", "^", "x", "*", ln("n")}));
    Term const exponentForTerm3(Polynomial{Monomial(1, {{"n", 1}}), Monomial(-1, {})});
    Term const termToExpect3(createExpressionIfPossible({"n", "*", "x", "^", exponentForTerm3}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_TRUE(isNan(termToVerify4));
}

TEST(DifferentiationTest, DifferentiateWorksWithDivisionExpressionRaiseToAConstant) {
    Differentiation const differentiationForX("x");
    Term const subTerm1(createExpressionIfPossible({2, "/", Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})}}));
    Term const termToTest(createExpressionIfPossible({subTerm1, "^", 5}));

    Term const termToVerify(differentiationForX.differentiate(termToTest));

    string const stringToExpect("(-160/((1[x] + -1)^6))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(DifferentiationTest, DifferentiateWorksWithChainRule) {
    Differentiation const differentiationForX("x");
    Term const termToTest(createExpressionIfPossible({sec(Monomial(2, {{"x", 2}})), "^", 4}));

    Term const termToVerify(differentiationForX.differentiate(termToTest));

    string const stringToExpect("(16[x]*(sec(2[x^2])^4)*tan(2[x^2]))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(DifferentiationTest, DifferentiateWorksWithSquareRootOfAPolynomial) {
    Differentiation const differentiationForX("x");
    Polynomial const subPolynomial{Monomial(2, {{"x", 3}}), Monomial(-4, {{"x", 1}}), Monomial(5, {})};
    Term const termToTest(createExpressionIfPossible({subPolynomial, "^", AlbaNumber::createFraction(1, 2)}));

    Term const termToVerify(differentiationForX.differentiate(termToTest));

    string const stringToExpect("((3[x^2] + -2)/((2[x^3] + -4[x] + 5)^(1/2)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(DifferentiationTest, DifferentiateMultipleTimesWorksForTerm) {
    Differentiation const differentiationForX("x");
    Term const termToTest(Monomial(3, {{"x", 4}}));

    Term const termToVerify1(differentiationForX.differentiateMultipleTimes(termToTest, 0));
    Term const termToVerify2(differentiationForX.differentiateMultipleTimes(termToTest, 1));
    Term const termToVerify3(differentiationForX.differentiateMultipleTimes(termToTest, 2));

    Term const termToExpect1(Monomial(3, {{"x", 4}}));
    Term const termToExpect2(Monomial(12, {{"x", 3}}));
    Term const termToExpect3(Monomial(36, {{"x", 2}}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationTest, DifferentiateMultipleTimesWorksForEquation) {
    Differentiation const differentiationForX("x");
    Equation const equationToTest(Monomial(3, {{"x", 4}}), "=", Monomial(5, {{"x", 6}}));

    Equation const equationToVerify1(differentiationForX.differentiateMultipleTimes(equationToTest, 0));
    Equation const equationToVerify2(differentiationForX.differentiateMultipleTimes(equationToTest, 1));
    Equation const equationToVerify3(differentiationForX.differentiateMultipleTimes(equationToTest, 2));

    Equation const equationToExpect1(Monomial(3, {{"x", 4}}), "=", Monomial(5, {{"x", 6}}));
    Equation const equationToExpect2(Polynomial{Monomial(5, {{"x", 5}}), Monomial(-2, {{"x", 3}})}, "=", 0);
    Equation const equationToExpect3(Polynomial{Monomial(25, {{"x", 4}}), Monomial(-6, {{"x", 2}})}, "=", 0);
    EXPECT_EQ(equationToExpect1, equationToVerify1);
    EXPECT_EQ(equationToExpect2, equationToVerify2);
    EXPECT_EQ(equationToExpect3, equationToVerify3);
}

TEST(DifferentiationTest, DifferentiateEquationWorks) {
    Differentiation const differentiationForXWithY("x", {"y"});
    Term const term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term const term2ForEquation1(
        Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation const equation1(term1ForEquation1, "=", term2ForEquation1);
    Term const term1ForEquation2(Polynomial{Monomial(3, {{"x", 4}, {"y", 2}}), Monomial(-7, {{"x", 1}, {"y", 3}})});
    Term const term2ForEquation2(Polynomial{Monomial(4, {}), Monomial(8, {{"y", 1}})});
    Equation const equation2(term1ForEquation2, "=", term2ForEquation2);

    Equation const equationToVerify1(differentiationForXWithY.differentiateEquation(equation1));
    Equation const equationToVerify2(differentiationForXWithY.differentiateEquation(equation2));

    string const stringToExpect1("(18[d[y]/d[x]][y^5] + 5[d[y]/d[x]][y^4] + -6[x^5] + -2[d[y]/d[x]][y] + 2) = 0");
    string const stringToExpect2(
        "(6[d[y]/d[x]][x^4][y] + 12[x^3][y^2] + -21[d[y]/d[x]][x][y^2] + -7[y^3] + -8[d[y]/d[x]]) = 0");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
}

TEST(DifferentiationTest, DifferentiateVariableWorks) {
    Differentiation const differentiationForXWithY("x", {"y"});

    Monomial const monomialToVerify1(differentiationForXWithY.differentiateVariable(Variable("x")));
    Monomial const monomialToVerify2(differentiationForXWithY.differentiateVariable(Variable("y")));
    Monomial const monomialToVerify3(differentiationForXWithY.differentiateVariable(Variable("a")));
    Monomial const monomialToVerify4(differentiationForXWithY.differentiateVariable(Variable("d[y]/d[x]")));

    Monomial const monomialToExpect1(1, {});
    Monomial const monomialToExpect2(1, {{"d[y]/d[x]", 1}});
    Monomial const monomialToExpect3(0, {});
    Monomial const monomialToExpect4(1, {{"d2[y]/d[x]2", 1}});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
}

TEST(DifferentiationTest, DifferentiateMonomialWorks) {
    Differentiation const differentiationForXWithY("x", {"y"});

    Polynomial const polynomialToVerify1(differentiationForXWithY.differentiateMonomial(Monomial(13, {})));
    Polynomial const polynomialToVerify2(differentiationForXWithY.differentiateMonomial(Monomial(13, {{"x", 0}})));
    Polynomial const polynomialToVerify3(differentiationForXWithY.differentiateMonomial(Monomial(1, {{"x", 8}})));
    Polynomial const polynomialToVerify4(differentiationForXWithY.differentiateMonomial(Monomial(3, {{"x", -5}})));
    Polynomial const polynomialToVerify5(differentiationForXWithY.differentiateMonomial(Monomial(3, {{"z", -5}})));
    Polynomial const polynomialToVerify6(
        differentiationForXWithY.differentiateMonomial(Monomial(5, {{"d[y]/d[x]", 6}, {"x", 7}, {"y", 8}, {"z", 9}})));

    Polynomial const polynomialToExpect1;
    Polynomial const polynomialToExpect2;
    Polynomial const polynomialToExpect3{Monomial(8, {{"x", 7}})};
    Polynomial const polynomialToExpect4{Monomial(-15, {{"x", -6}})};
    Polynomial const polynomialToExpect5;
    Polynomial const polynomialToExpect6{
        Monomial(30, {{"d2[y]/d[x]2", 1}, {"d[y]/d[x]", 5}, {"x", 7}, {"y", 8}, {"z", 9}}),
        Monomial(35, {{"d[y]/d[x]", 6}, {"x", 6}, {"y", 8}, {"z", 9}}),
        Monomial(40, {{"d[y]/d[x]", 1}, {"x", 7}, {"y", 7}, {"z", 9}})};
    EXPECT_EQ(polynomialToExpect1, polynomialToVerify1);
    EXPECT_EQ(polynomialToExpect2, polynomialToVerify2);
    EXPECT_EQ(polynomialToExpect3, polynomialToVerify3);
    EXPECT_EQ(polynomialToExpect4, polynomialToVerify4);
    EXPECT_EQ(polynomialToExpect5, polynomialToVerify5);
    EXPECT_EQ(polynomialToExpect6, polynomialToVerify6);
}

TEST(DifferentiationTest, DifferentiatePolynomialWorks) {
    Differentiation const differentiationForXWithY("x", {"y"});
    Polynomial const polynomial1{Monomial(0, {})};
    Polynomial const polynomial2{Monomial(5, {{"x", 0}})};
    Polynomial const polynomial3{
        Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})};
    Polynomial const polynomial4{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};
    Polynomial const polynomial5{
        Monomial(1, {{"a", 2}}), Monomial(3, {{"b", 4}}), Monomial(5, {{"c", 6}}), Monomial(7, {})};

    Polynomial const polynomialToVerify1(differentiationForXWithY.differentiatePolynomial(polynomial1));
    Polynomial const polynomialToVerify2(differentiationForXWithY.differentiatePolynomial(polynomial2));
    Polynomial const polynomialToVerify3(differentiationForXWithY.differentiatePolynomial(polynomial3));
    Polynomial const polynomialToVerify4(differentiationForXWithY.differentiatePolynomial(polynomial4));
    Polynomial const polynomialToVerify5(differentiationForXWithY.differentiatePolynomial(polynomial5));

    Polynomial const polynomialToExpect1;
    Polynomial const polynomialToExpect2;
    Polynomial const polynomialToExpect3{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Polynomial const polynomialToExpect4{
        Monomial(3, {{"d[y]/d[x]", 1}, {"x", -2}, {"y", -4}}), Monomial(2, {{"x", -3}, {"y", -3}}),
        Monomial(20, {{"x", -6}, {"z", -6}})};
    Polynomial const polynomialToExpect5;
    EXPECT_EQ(polynomialToExpect1, polynomialToVerify1);
    EXPECT_EQ(polynomialToExpect2, polynomialToVerify2);
    EXPECT_EQ(polynomialToExpect3, polynomialToVerify3);
    EXPECT_EQ(polynomialToExpect4, polynomialToVerify4);
    EXPECT_EQ(polynomialToExpect5, polynomialToVerify5);
}

TEST(DifferentiationTest, DifferentiateWithDefiniteValueWorks) {
    Differentiation const differentiationForX("x");
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    Term const termToVerify1(differentiationForX.differentiateWithDefiniteValue(termToTest1, 5));
    Term const termToVerify2(differentiationForX.differentiateWithDefiniteValue(termToTest2, 5));
    Term const termToVerify3(differentiationForX.differentiateWithDefiniteValue(termToTest3, 5));

    Term const termToExpect1(1);
    Term const termToExpect2(10);
    Term const termToExpect3(75);
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationTest, DifferentiateExpressionWorks) {
    Differentiation const differentiationForXWithY("x", {"y"});
    Expression const expression01{createExpressionIfPossible({"x"})};
    Expression const expression02{createExpressionIfPossible({cos("x")})};
    Expression const expression03{createExpressionIfPossible({cos("y")})};
    Expression const expression04{createExpressionIfPossible({sin("x"), "+", cos("x")})};
    Expression const expression05{createExpressionIfPossible({sin("x"), "-", cos("x")})};
    Expression const expression06{createExpressionIfPossible({sin("x"), "*", cos("x")})};
    Expression const expression07{createExpressionIfPossible({sin("x"), "/", cos("x")})};
    Expression const expression08{createExpressionIfPossible({cos("x"), "^", 3})};
    Expression const expression09{createExpressionIfPossible({3, "^", cos("x")})};
    Expression const expression10{createExpressionIfPossible({sin("x"), "^", cos("x")})};

    Term const expressionToVerify01(differentiationForXWithY.differentiateExpression(expression01));
    Term const expressionToVerify02(differentiationForXWithY.differentiateExpression(expression02));
    Term const expressionToVerify03(differentiationForXWithY.differentiateExpression(expression03));
    Term const expressionToVerify04(differentiationForXWithY.differentiateExpression(expression04));
    Term const expressionToVerify05(differentiationForXWithY.differentiateExpression(expression05));
    Term const expressionToVerify06(differentiationForXWithY.differentiateExpression(expression06));
    Term const expressionToVerify07(differentiationForXWithY.differentiateExpression(expression07));
    Term const expressionToVerify08(differentiationForXWithY.differentiateExpression(expression08));
    Term const expressionToVerify09(differentiationForXWithY.differentiateExpression(expression09));
    Term const expressionToVerify10(differentiationForXWithY.differentiateExpression(expression10));

    Term const sinSquared{createExpressionIfPossible({sin("x"), "^", 2})};
    Term const cosSquared{createExpressionIfPossible({cos("x"), "^", 2})};
    Term const termToExpect01(1);
    Term const termToExpect02(createExpressionIfPossible({-1, "*", sin("x")}));
    Term const termToExpect03(createExpressionIfPossible({Monomial(-1, {{"d[y]/d[x]", 1}}), "*", sin("y")}));
    Term const termToExpect04(createExpressionIfPossible({cos("x"), "-", sin("x")}));
    Term const termToExpect05(createExpressionIfPossible({cos("x"), "+", sin("x")}));
    Term const termToExpect06(createExpressionIfPossible({cosSquared, "-", sinSquared}));
    Term const expectedNumerator07(createExpressionIfPossible({cosSquared, "+", sinSquared}));
    Term const expectedDenominator07(createExpressionIfPossible({cosSquared}));
    Term const termToExpect07(createExpressionIfPossible({expectedNumerator07, "/", expectedDenominator07}));
    Term const termToExpect08(createExpressionIfPossible({-3, "*", cosSquared, "*", sin("x")}));
    Term const termToExpect09(createExpressionIfPossible({-1.09861228866811, "*", 3, "^", cos("x"), "*", sin("x")}));
    EXPECT_EQ(termToExpect01, expressionToVerify01);
    EXPECT_EQ(termToExpect02, expressionToVerify02);
    EXPECT_EQ(termToExpect03, expressionToVerify03);
    EXPECT_EQ(termToExpect04, expressionToVerify04);
    EXPECT_EQ(termToExpect05, expressionToVerify05);
    EXPECT_EQ(termToExpect06, expressionToVerify06);
    EXPECT_EQ(termToExpect07, expressionToVerify07);
    EXPECT_EQ(termToExpect08, expressionToVerify08);
    EXPECT_EQ(termToExpect09, expressionToVerify09);
    EXPECT_TRUE(isNan(expressionToVerify10));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithFunctionsInCommonFunctionLibrary) {
    Differentiation const differentiationForXWithY("x", {"y"});

    Term const termToVerify01(differentiationForXWithY.differentiateFunction(abs("x")));
    Term const termToVerify02(differentiationForXWithY.differentiateFunction(ln("x")));
    Term const termToVerify03(differentiationForXWithY.differentiateFunction(log("x")));
    Term const termToVerify04(differentiationForXWithY.differentiateFunction(sin("x")));
    Term const termToVerify05(differentiationForXWithY.differentiateFunction(cos("x")));
    Term const termToVerify06(differentiationForXWithY.differentiateFunction(cos("y")));
    Term const termToVerify07(differentiationForXWithY.differentiateFunction(tan("x")));
    Term const termToVerify08(differentiationForXWithY.differentiateFunction(csc("x")));
    Term const termToVerify09(differentiationForXWithY.differentiateFunction(sec("x")));
    Term const termToVerify10(differentiationForXWithY.differentiateFunction(cot("x")));
    Term const termToVerify11(differentiationForXWithY.differentiateFunction(arcsin("x")));
    Term const termToVerify12(differentiationForXWithY.differentiateFunction(arccos("x")));
    Term const termToVerify13(differentiationForXWithY.differentiateFunction(arctan("x")));
    Term const termToVerify14(differentiationForXWithY.differentiateFunction(arccsc("x")));
    Term const termToVerify15(differentiationForXWithY.differentiateFunction(arcsec("x")));
    Term const termToVerify16(differentiationForXWithY.differentiateFunction(arccot("x")));
    Term const termToVerify17(differentiationForXWithY.differentiateFunction(sinh("x")));
    Term const termToVerify18(differentiationForXWithY.differentiateFunction(cosh("x")));
    Term const termToVerify19(differentiationForXWithY.differentiateFunction(tanh("x")));
    Term const termToVerify20(differentiationForXWithY.differentiateFunction(csch("x")));
    Term const termToVerify21(differentiationForXWithY.differentiateFunction(sech("x")));
    Term const termToVerify22(differentiationForXWithY.differentiateFunction(coth("x")));

    Term const cscSquared(createExpressionIfPossible({csc("x"), "^", 2}));
    Term const termToExpect01(sgn("x"));
    Term const termToExpect02(Monomial(1, {{"x", -1}}));
    Term const termToExpect03(Monomial(2.302585092994046, {{"x", -1}}));
    Term const termToExpect04(cos("x"));
    Term const termToExpect05(createExpressionIfPossible({-1, "*", sin("x")}));
    Term const termToExpect06(createExpressionIfPossible({Monomial(-1, {{"d[y]/d[x]", 1}}), "*", sin("y")}));
    Term const termToExpect07(createExpressionIfPossible({sec("x"), "^", 2}));
    Term const termToExpect08(createExpressionIfPossible({-1, "*", cot("x"), "*", csc("x")}));
    Term const termToExpect09(createExpressionIfPossible({sec("x"), "*", tan("x")}));
    Term const termToExpect10(createExpressionIfPossible({-1, "*", cscSquared}));
    string const stringToExpect11("(1/((-1[x^2] + 1)^(1/2)))");
    string const stringToExpect12("(-1/((-1[x^2] + 1)^(1/2)))");
    string const stringToExpect13("(1/(1[x^2] + 1))");
    string const stringToExpect14("(-1/x/((1[x] + -1)^(1/2))/((1[x] + 1)^(1/2)))");
    string const stringToExpect15("(1/x/((1[x] + -1)^(1/2))/((1[x] + 1)^(1/2)))");
    string const stringToExpect16("(-1/(1[x^2] + 1))");
    string const stringToExpect17("cosh(x)");
    string const stringToExpect18("sinh(x)");
    string const stringToExpect19("(sech(x)^2)");
    string const stringToExpect20("(-1*coth(x)*csch(x))");
    string const stringToExpect21("(-1*sech(x)*tanh(x))");
    string const stringToExpect22("(-1*(csch(x)^2))");
    EXPECT_EQ(termToExpect01, termToVerify01);
    EXPECT_EQ(termToExpect02, termToVerify02);
    EXPECT_EQ(termToExpect03, termToVerify03);
    EXPECT_EQ(termToExpect04, termToVerify04);
    EXPECT_EQ(termToExpect05, termToVerify05);
    EXPECT_EQ(termToExpect06, termToVerify06);
    EXPECT_EQ(termToExpect07, termToVerify07);
    EXPECT_EQ(termToExpect08, termToVerify08);
    EXPECT_EQ(termToExpect09, termToVerify09);
    EXPECT_EQ(termToExpect10, termToVerify10);
    EXPECT_EQ(stringToExpect11, convertToString(termToVerify11));
    EXPECT_EQ(stringToExpect12, convertToString(termToVerify12));
    EXPECT_EQ(stringToExpect13, convertToString(termToVerify13));
    EXPECT_EQ(stringToExpect14, convertToString(termToVerify14));
    EXPECT_EQ(stringToExpect15, convertToString(termToVerify15));
    EXPECT_EQ(stringToExpect16, convertToString(termToVerify16));
    EXPECT_EQ(stringToExpect17, convertToString(termToVerify17));
    EXPECT_EQ(stringToExpect18, convertToString(termToVerify18));
    EXPECT_EQ(stringToExpect19, convertToString(termToVerify19));
    EXPECT_EQ(stringToExpect20, convertToString(termToVerify20));
    EXPECT_EQ(stringToExpect21, convertToString(termToVerify21));
    EXPECT_EQ(stringToExpect22, convertToString(termToVerify22));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithChainRule) {
    Differentiation const differentiationForX("x");
    Function const functionToTest(sin(Monomial(10, {{"x", 8}})));

    Term const termToVerify(differentiationForX.differentiateFunction(functionToTest));

    Term const termToExpect(createExpressionIfPossible({Monomial(80, {{"x", 7}}), "*", cos(Monomial(10, {{"x", 8}}))}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(DifferentiationTest, DifferentiateTwoMultipliedTermsWorks) {
    Differentiation const differentiationForX("x");
    Term const term1(Polynomial{Monomial(2, {{"x", 2}}), Monomial(-4, {{"x", 1}})});
    Term const term2(Polynomial{Monomial(3, {{"x", 2}}), Monomial(7, {{"x", 1}})});

    Term const termToVerify(differentiationForX.differentiateTwoMultipliedTerms(term1, term2));

    string const stringToExpect("(((2[x^2] + -4[x])*(6[x] + 7))+((3[x^2] + 7[x])*(4[x] + -4)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(DifferentiationTest, DifferentiateTwoDividedTermsWorks) {
    Differentiation const differentiationForX("x");
    Term const numerator(Polynomial{Monomial(2, {{"x", 3}}), Monomial(4, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(1, {})});

    Term const termToVerify(differentiationForX.differentiateTwoDividedTerms(numerator, denominator));

    string const stringToExpect(
        "((((1[x^2] + -4[x] + 1)*6[x^2])-((2[x^3] + 4)*(2[x] + -4)))/((1[x^2] + -4[x] + 1)^2))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(DifferentiationTest, DifferentiateConstantWorks) {
    Differentiation const differentiationForX("x");

    EXPECT_EQ(AlbaNumber(0), differentiationForX.differentiateConstant(Constant(5)));
}

}  // namespace alba::algebra
