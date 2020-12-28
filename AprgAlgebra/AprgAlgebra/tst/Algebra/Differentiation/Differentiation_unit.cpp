#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(DifferentiationTest, DifferentiateWorksForTerm)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Term(5)));
}

TEST(DifferentiationTest, DifferentiateWorksForConstant)
{
    Differentiation differentiationForX("x");
    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationTest, DifferentiateWorksForVariable)
{
    Differentiation differentiationForXWithY("x", {"y"});

    EXPECT_EQ(Term(1), differentiationForXWithY.differentiate(Variable("x")));
}

TEST(DifferentiationTest, DifferentiateWorksForMonomial){
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Monomial(13, {})));
}

TEST(DifferentiationTest, DifferentiateWorksForPolynomial)
{
    Differentiation differentiationForX("x");
    Polynomial polynomial{Monomial(0, {})};

    Term expectedTerm(Constant(0));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiate(polynomial));
}

TEST(DifferentiationTest, DifferentiateWorksForExpression)
{
    Differentiation differentiationForX("x");
    Term x("x");
    Expression expression{createExpressionIfPossible({x})};

    Term expectedTerm(1);
    EXPECT_EQ(expectedTerm, differentiationForX.differentiate(expression));
}

TEST(DifferentiationTest, DifferentiateWorksForFunction)
{
    Differentiation differentiationForX("x");

    Term x("x");
    EXPECT_EQ(Term(cos(x)), differentiationForX.differentiate(sin(x)));
}

TEST(DifferentiationTest, DifferentiateWorksForEquation)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Term term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term term2ForEquation1(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation equation1(term1ForEquation1, "=", term2ForEquation1);

    EXPECT_EQ("(18[dy/dx][y^5] + 5[dy/dx][y^4] + -6[x^5] + -2[dy/dx][y] + 2) = 0", differentiationForXWithY.differentiate(equation1).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateTermWorks)
{
    Differentiation differentiationForX("x");    Term x("x");
    Term polynomialTerm(Polynomial({Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})}));
    Term expressionTerm(createExpressionIfPossible({cos(x)}));

    Term expectedTerm1(Polynomial({Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})}));
    Term expectedTerm2(createExpressionIfPossible({Term(-1), Term("*"), sin(x)}));
    Term expectedTerm3(cos(x));
    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiateTerm(Term(5)));
    EXPECT_EQ(Term(1), differentiationForX.differentiateTerm(Term("x")));
    EXPECT_EQ(Term(Monomial(8, {{"x", 7}})), differentiationForX.differentiateTerm(Term(Monomial(1, {{"x", 8}}))));
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiateTerm(polynomialTerm));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiateTerm(expressionTerm));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiateTerm(Term(sin(x))));
}

TEST(DifferentiationTest, DifferentiateConstantWorks)
{
    Differentiation differentiationForX("x");
    EXPECT_EQ(AlbaNumber(0), differentiationForX.differentiateConstant(Constant(5)));
}

TEST(DifferentiationTest, DifferentiateVariableWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});

    EXPECT_EQ(Monomial(1, {}), differentiationForXWithY.differentiateVariable(Variable("x")));
    EXPECT_EQ(Monomial(1, {{"dy/dx", 1}}), differentiationForXWithY.differentiateVariable(Variable("y")));
    EXPECT_EQ(Monomial(0, {}), differentiationForXWithY.differentiateVariable(Variable("a")));
}

TEST(DifferentiationTest, DifferentiateMonomialWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});

    EXPECT_EQ(Monomial(0, {}), differentiationForXWithY.differentiateMonomial(Monomial(13, {})));
    EXPECT_EQ(Monomial(0, {}), differentiationForXWithY.differentiateMonomial(Monomial(13, {{"x", 0}})));
    EXPECT_EQ(Monomial(8, {{"x", 7}}), differentiationForXWithY.differentiateMonomial(Monomial(1, {{"x", 8}})));
    EXPECT_EQ(Monomial(-15, {{"x", -6}}), differentiationForXWithY.differentiateMonomial(Monomial(3, {{"x", -5}})));
    EXPECT_EQ(Monomial(0, {}), differentiationForXWithY.differentiateMonomial(Monomial(3, {{"z", -5}})));
    EXPECT_EQ(Monomial(336, {{"dy/dx", 1}, {"x", 6}, {"y", 7}, {"z", 9}}), differentiationForXWithY.differentiateMonomial(Monomial(6, {{"x", 7}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationTest, DifferentiatePolynomialWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Polynomial polynomial1{Monomial(0, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 0}})};
    Polynomial polynomial3{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})};
    Polynomial polynomial4{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};
    Polynomial polynomial5{Monomial(1, {{"a", 2}}), Monomial(3, {{"b", 4}}), Monomial(5, {{"c", 6}}), Monomial(7, {})};

    Polynomial expectedPolynomial1;
    Polynomial expectedPolynomial2;
    Polynomial expectedPolynomial3{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Polynomial expectedPolynomial4{Monomial(-6, {{"dy/dx", 1}, {"x", -3}, {"y", -4}}), Monomial(20, {{"x", -6}, {"z", -6}})};
    Polynomial expectedPolynomial5;
    EXPECT_EQ(expectedPolynomial1, differentiationForXWithY.differentiatePolynomial(polynomial1));
    EXPECT_EQ(expectedPolynomial2, differentiationForXWithY.differentiatePolynomial(polynomial2));
    EXPECT_EQ(expectedPolynomial3, differentiationForXWithY.differentiatePolynomial(polynomial3));
    EXPECT_EQ(expectedPolynomial4, differentiationForXWithY.differentiatePolynomial(polynomial4));
    EXPECT_EQ(expectedPolynomial5, differentiationForXWithY.differentiatePolynomial(polynomial5));
}

TEST(DifferentiationTest, DifferentiateExpressionWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Term x("x");
    Term y("y");
    Expression expression01{createExpressionIfPossible({x})};
    Expression expression02{createExpressionIfPossible({cos(x)})};
    Expression expression03{createExpressionIfPossible({cos(y)})};
    Expression expression04{createExpressionIfPossible({sin(x), Term("+"), cos(x)})};
    Expression expression05{createExpressionIfPossible({sin(x), Term("-"), cos(x)})};
    Expression expression06{createExpressionIfPossible({sin(x), Term("*"), cos(x)})};
    Expression expression07{createExpressionIfPossible({sin(x), Term("/"), cos(x)})};
    Expression expression08{createExpressionIfPossible({cos(x), Term("^"), Term(3)})};
    Expression expression09{createExpressionIfPossible({Term(3), Term("^"), cos(x)})};
    Expression expression10{createExpressionIfPossible({sin(x), Term("^"), cos(x)})};

    Term expectedTerm01(1);
    Term expectedTerm02(createExpressionIfPossible({Term(-1), Term("*"), sin(x)}));
    Term expectedTerm03(createExpressionIfPossible({Term(Monomial(-1, {{"dy/dx", 1}})), Term("*"), sin(y)}));
    Term expectedTerm04(createExpressionIfPossible({cos(x), Term("-"), sin(x)}));
    Term expectedTerm05(createExpressionIfPossible({cos(x), Term("+"), sin(x)}));
    Term expectedTerm06(createExpressionIfPossible({Term(-1), Term("*"), sin(x), Term("*"), sin(x), Term("+"), cos(x), Term("*"), cos(x)}));
    Term expectedNumerator07(createExpressionIfPossible({cos(x), Term("*"), cos(x), Term("+"), sin(x), Term("*"), sin(x)}));
    Term expectedDenominator07(createExpressionIfPossible({cos(x), Term("*"), cos(x)}));
    Term expectedTerm07(createExpressionIfPossible({expectedNumerator07, Term("/"), expectedDenominator07}));
    Term expectedTerm08(createExpressionIfPossible({Term(-3), Term("*"), cos(x), Term("*"), cos(x), Term("*"), sin(x)}));
    Term expectedTerm09(createExpressionIfPossible({Term(-1.09861228866811), Term("*"), Term(3), Term("^"), cos(x), Term("*"), sin(x)}));
    EXPECT_EQ(expectedTerm01, differentiationForXWithY.differentiateExpression(expression01));
    EXPECT_EQ(expectedTerm02, differentiationForXWithY.differentiateExpression(expression02));
    EXPECT_EQ(expectedTerm03, differentiationForXWithY.differentiateExpression(expression03));
    EXPECT_EQ(expectedTerm04, differentiationForXWithY.differentiateExpression(expression04));
    EXPECT_EQ(expectedTerm05, differentiationForXWithY.differentiateExpression(expression05));
    EXPECT_EQ(expectedTerm06, differentiationForXWithY.differentiateExpression(expression06));
    EXPECT_EQ(expectedTerm07, differentiationForXWithY.differentiateExpression(expression07));
    EXPECT_EQ(expectedTerm08, differentiationForXWithY.differentiateExpression(expression08));
    EXPECT_EQ(expectedTerm09, differentiationForXWithY.differentiateExpression(expression09));
    EXPECT_TRUE(isNotANumber(differentiationForXWithY.differentiateExpression(expression10)));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithTrigonometricFunction)
{
    Differentiation differentiationForXWithY("x", {"y"});

    Term x("x");
    Term y("y");
    EXPECT_EQ(Term(cos(x)), differentiationForXWithY.differentiateFunction(sin(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), sin(x)})), differentiationForXWithY.differentiateFunction(cos(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(Monomial(-1, {{"dy/dx", 1}})), Term("*"), sin(y)})), differentiationForXWithY.differentiateFunction(cos(y)));
    EXPECT_EQ(Term(createExpressionIfPossible({sec(x), Term("^"), Term(2)})), differentiationForXWithY.differentiateFunction(tan(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), csc(x), Term("*"), cot(x)})), differentiationForXWithY.differentiateFunction(csc(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({sec(x), Term("*"), tan(x)})), differentiationForXWithY.differentiateFunction(sec(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), csc(x), Term("*"), csc(x)})), differentiationForXWithY.differentiateFunction(cot(x)));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithChainRule){
    Differentiation differentiationForX("x");
    Function functionToTest(sin(Term(Monomial(10, {{"x", 8}}))));

    Term expectedTerm(createExpressionIfPossible({Term(Monomial(80, {{"x", 7}})), Term("*"), cos(Term(Monomial(10, {{"x", 8}})))}));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateFunction(functionToTest));
}

TEST(DifferentiationTest, DifferentiateEquationWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Term term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term term2ForEquation1(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation equation1(term1ForEquation1, "=", term2ForEquation1);
    Term term1ForEquation2(Polynomial{Monomial(3, {{"x", 4}, {"y", 2}}), Monomial(-7, {{"x", 1}, {"y", 3}})});
    Term term2ForEquation2(Polynomial{Monomial(4, {}), Monomial(8, {{"y", 1}})});
    Equation equation2(term1ForEquation2, "=", term2ForEquation2);

    EXPECT_EQ("(18[dy/dx][y^5] + 5[dy/dx][y^4] + -6[x^5] + -2[dy/dx][y] + 2) = 0", differentiationForXWithY.differentiateEquation(equation1).getDisplayableString());
    EXPECT_EQ("(24[dy/dx][x^3][y] + -21[dy/dx][y^2] + -8[dy/dx]) = 0", differentiationForXWithY.differentiateEquation(equation2).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateTwoMultipliedTermsWorks)
{
    Differentiation differentiationForX("x");    Term term1(Polynomial{Monomial(2, {{"x", 3}}), Monomial(-4, {{"x", 2}})});
    Term term2(Polynomial{Monomial(3, {{"x", 5}}), Monomial(1, {{"x", 2}})});

    Term expectedTerm(Polynomial{Monomial(48, {{"x", 7}}), Monomial(-84, {{"x", 6}}), Monomial(10, {{"x", 4}}), Monomial(-16, {{"x", 3}})});
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateTwoMultipliedTerms(term1, term2));
}

TEST(DifferentiationTest, DifferentiateTwoDividedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term numerator(Polynomial{Monomial(2, {{"x", 3}}), Monomial(4, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(1, {})});

    Term expectedNumerator(Polynomial{Monomial(2, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(6, {{"x", 2}}), Monomial(-8, {{"x", 1}}), Monomial(16, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-8, {{"x", 3}}), Monomial(18, {{"x", 2}}), Monomial(-8, {{"x", 1}}), Monomial(1, {})});
    Term expectedTerm(createExpressionIfPossible({expectedNumerator, Term("/"), expectedDenominator}));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateTwoDividedTerms(numerator, denominator));
}

TEST(DifferentiationTest, DifferentiateWorksWithDivisionExpressionRaiseToAConstant)
{
    Differentiation differentiationForX("x");
    Term subTerm1(createExpressionIfPossible({Term(2), Term("/"), Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})})}));
    Term termToTest(createExpressionIfPossible({subTerm1, Term("^"), Term(5)}));

    EXPECT_EQ("(-160/(1[x^6] + -6[x^5] + 15[x^4] + -20[x^3] + 15[x^2] + -6[x] + 1))", differentiationForX.differentiate(termToTest).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithChainRule){
    Differentiation differentiationForX("x");
    Term termToTest(createExpressionIfPossible({sec(Term(Monomial(2, {{"x", 2}}))), Term("^"), Term(4)}));

    EXPECT_EQ("(16[x]*sec(2[x^2])*sec(2[x^2])*sec(2[x^2])*sec(2[x^2])*tan(2[x^2]))", differentiationForX.differentiate(termToTest).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithSquareRootOfAPolynomial){
    Differentiation differentiationForX("x");
    Polynomial subPolynomial{Monomial(2, {{"x", 3}}), Monomial(-4, {{"x", 1}}), Monomial(5, {})};
    Term termToTest(createExpressionIfPossible({Term(subPolynomial), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    EXPECT_EQ("((3[x^2] + -2)/((2[x^3] + -4[x] + 5)^(1/2)))", differentiationForX.differentiate(termToTest).getDisplayableString());
}

}

}
