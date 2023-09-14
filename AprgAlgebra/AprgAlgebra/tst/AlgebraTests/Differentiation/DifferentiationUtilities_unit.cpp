#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(DifferentiationUtilitiesTest, SimplifyDerivativeByDefinitionWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression const squareRootOfXPlusOne(
        createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Term termToTest(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));

    simplifyDerivativeByDefinition(termToTest);

    string const stringToExpect("(x*((1[x] + 1)^(1/2)))");
    EXPECT_EQ(stringToExpect, convertToString(termToTest));
}

TEST(DifferentiationUtilitiesTest, GetRelationshipOfDerivativeOfTheInverseAndTheDerivativeWorks) {
    Term const termToTest1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term const termToTest2(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {})});
    Term const termToTest3(Polynomial{Monomial(1, {{"x", 3}}), Monomial(3, {})});

    Equation const equation1(getRelationshipOfDerivativeOfTheInverseAndTheDerivative(termToTest1, "x", "c", "d"));
    Equation const equation2(getRelationshipOfDerivativeOfTheInverseAndTheDerivative(termToTest2, "x", "c", "d"));
    Equation const equation3(getRelationshipOfDerivativeOfTheInverseAndTheDerivative(termToTest3, "x", "c", "d"));

    string const stringToExpect1("1 = 1");
    string const stringToExpect2("((1/2)/((1[d] + -2)^(1/2))) = (1/2)[c^-1]");
    string const stringToExpect3("((1/3)/((1[d] + -3)^(2/3))) = (1/3)[c^-2]");
    EXPECT_EQ(stringToExpect1, convertToString(equation1));
    EXPECT_EQ(stringToExpect2, convertToString(equation2));
    EXPECT_EQ(stringToExpect3, convertToString(equation3));
}

TEST(DifferentiationUtilitiesTest, GetIntegralEquationForFirstOrderDifferentialEquationWorks) {
    Term const leftHandSide(
        Polynomial{Monomial(1, {{"d[y]/d[x]", 1}}), Monomial(-2, {{"x", 1}, {"y", 1}}), Monomial(-3, {{"x", 1}})});
    Equation const equationToTest(leftHandSide, "=", 0);

    Equation const equationToVerify(getIntegralEquationForFirstOrderDifferentialEquation(equationToTest, "x", "y"));

    string const stringToExpect(
        "y = ((((e)^1[x^2][y])*-3/2[y^2]/((e)^1[x^2][y]))+(((e)^1[x^2][y])*(e)*((e)^1[x^2][y])))");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(DifferentiationUtilitiesTest, GetDifferentiabilityDomainWorks) {
    Polynomial const numerator{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomial const denominator{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    SolutionSet const differentiabilityDomain(getDifferentiabilityDomain(termToTest, "x"));

    AlbaNumberIntervals const& intervalToVerify(differentiabilityDomain.getAcceptedIntervals());
    ASSERT_EQ(2U, intervalToVerify.size());
    EXPECT_EQ(
        AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(0.9999979999999644)),
        intervalToVerify[0]);
    EXPECT_EQ(
        AlbaNumberInterval(createOpenEndpoint(1.000001999999898), createPositiveInfinityOpenEndpoint()),
        intervalToVerify[1]);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeDefinitionWorks) {
    Term const termToTest(Polynomial{Monomial(1, {{"a", 2}}), Monomial(1, {})});

    Term const derivative(getDerivativeDefinition(termToTest, "a"));

    Term const termToExpect(Polynomial{Monomial(1, {{"deltaX", 1}}), Monomial(2, {{"x", 1}})});
    EXPECT_EQ(termToExpect, derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeDefinitionWorksWithRadical) {
    Term const termToTest(Monomial(1, {{"a", AlbaNumber::createFraction(1, 3)}}));

    Term const derivative(getDerivativeDefinition(termToTest, "a"));

    string const stringToExpect("(1/(1[x^(2/3)]+(1[x^(1/3)]*((1[deltaX] + 1[x])^(1/3)))+((1[deltaX] + 1[x])^(2/3))))");
    EXPECT_EQ(stringToExpect, convertToString(derivative));
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenInputIsAConstant) {
    Term const termToTest(5);

    Term const derivative(getDerivativeAtUsingLimit(termToTest, "x", 2, LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(0), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenXIsAValue) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    Term const derivative(getDerivativeAtUsingLimit(termToTest, "x", 2, LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(4), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenXIsAVariable) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    Term const derivative(getDerivativeAtUsingLimit(termToTest, "x", "y", LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Monomial(2, {{"y", 1}})), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksWhenXIsAVariableAndMonomialIsRadical) {
    Term const termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}));

    Term const derivative(getDerivativeAtUsingLimit(termToTest, "x", "y", LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Monomial(AlbaNumber::createFraction(1, 3), {{"y", AlbaNumber::createFraction(-2, 3)}})), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForPolynomialAndWhenXIsAValue) {
    Term const polynomialTerm(Polynomial{Monomial(3, {{"x", 2}}), Monomial(12, {})});

    Term const derivative(getDerivativeAtUsingLimit(polynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(12), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForPolynomialAndWhenXIsAVariable) {
    Term const polynomialTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-3, {{"x", 1}}), Monomial(4, {})});

    Term const derivative(getDerivativeAtUsingLimit(polynomialTerm, "x", "z", LimitAtAValueApproachType::BothSides));

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"z", 2}}), Monomial(-3, {})}), derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForRadicalAndWhenXIsAVariable) {
    Term const polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term const radicalTerm(createExpressionIfPossible({polynomialTerm, "^", AlbaNumber::createFraction(1, 2)}));

    Term const derivative(getDerivativeAtUsingLimit(radicalTerm, "x", "a", LimitAtAValueApproachType::BothSides));

    Term const expectedSubPolynomial(Polynomial{Monomial(1, {{"a", 1}}), Monomial(-3, {})});
    Term const expectedRadicalTerm(
        createExpressionIfPossible({expectedSubPolynomial, "^", AlbaNumber::createFraction(1, 2)}));
    Term const termToExpect(createExpressionIfPossible({AlbaNumber::createFraction(1, 2), "/", expectedRadicalTerm}));
    EXPECT_EQ(termToExpect, derivative);
}

TEST(DifferentiationUtilitiesTest, GetDerivativeAtUsingLimitWorksForPolynomialOverPolynomialAndWhenXIsAVariable) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(3, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    Term const derivative(
        getDerivativeAtUsingLimit(polynomialOverPolynomialTerm, "x", "a", LimitAtAValueApproachType::BothSides));

    Term const expectedDenominator(Polynomial{Monomial(1, {{"a", 2}}), Monomial(-6, {{"a", 1}}), Monomial(9, {})});
    Term const termToExpect(createExpressionIfPossible({5, "/", expectedDenominator}));
    EXPECT_EQ(termToExpect, derivative);
}

TEST(DifferentiationUtilitiesTest, GetLogarithmicDifferentiationToYieldDyOverDxWorks) {
    Polynomial const xMinusOne{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Term const termToTest(createExpressionIfPossible({xMinusOne, "^", AlbaNumber::createFraction(1, 2)}));

    Term const dyOverDx(getLogarithmicDifferentiationToYieldDyOverDx(termToTest, "x", "y"));

    Term const insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})});
    Term const squareRootTerm(
        createExpressionIfPossible({insideSquareRootTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Term const termToExpect(createExpressionIfPossible({1, "/", 2, "/", squareRootTerm}));
    EXPECT_EQ(termToExpect, dyOverDx);
}

TEST(DifferentiationUtilitiesTest, GetCartesianDerivativeOfTermInPolarCoordinatesWorks) {
    string const thetaName("theta");
    Term const theta(thetaName);
    Term const radiusOfLimacon(createExpressionIfPossible({3, "+", 2, "*", sin(theta)}));

    Term const dyOverDx(getCartesianDerivativeOfTermInPolarCoordinates(radiusOfLimacon, thetaName));

    string const stringToExpect(
        "(((4*cos(theta)*sin(theta))+(3*cos(theta)))/"
        "((2*cos(theta)*cos(theta))-(3*sin(theta))-(2*sin(theta)*sin(theta))))");
    EXPECT_EQ(stringToExpect, convertToString(dyOverDx));
}

TEST(DifferentiationUtilitiesTest, GetSlopeOfTermInPolarCoordinatesWorks) {
    string const thetaName("theta");
    Term const theta(thetaName);
    Term const radiusOfLimacon(createExpressionIfPossible({3, "+", 2, "*", cos(theta)}));

    Term const termToVerify(getSlopeOfTermInPolarCoordinates(radiusOfLimacon, thetaName, ALBA_NUMBER_PI / 2));

    EXPECT_EQ(Term(AlbaNumber::createFraction(2, 3)), termToVerify);
}

TEST(DifferentiationUtilitiesTest, GetApproximationUsingTaylorsFormulaWorksForEToTheX) {
    Term const termToTest(createExpressionIfPossible({getEAsATerm(), "^", "x"}));

    Term const termToVerify(getApproximationUsingTaylorsFormula(termToTest, "x", 0, "q", 3));

    string const stringToExpect("((1/6)[q^3] + (1/2)[q^2] + 1[q] + 1)");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(DifferentiationUtilitiesTest, GetApproximationUsingTaylorsFormulaWorksForSin) {
    Term const termToTest(sin("x"));

    Term const termToVerify(getApproximationUsingTaylorsFormula(termToTest, "x", 0, "q", 8));

    string const stringToExpect("((-1/5040)[q^7] + (1/120)[q^5] + (-1/6)[q^3] + 1[q])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(DifferentiationUtilitiesTest, GetApproximationUsingTaylorsRemainderWorks) {
    Term const termToTest(createExpressionIfPossible({getEAsATerm(), "^", "x"}));

    Term const termToVerify(
        getApproximationOfErrorUsingTaylorsRemainder(termToTest, "x", 0, AlbaNumber::createFraction(1, 2), 0, 5));

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 46080)), termToVerify);
    // this means the when n=5 the square root of e is accurate up to 4 decimal places.
}

TEST(DifferentiationUtilitiesTest, GetTotalDerivativeWithInnerTermsUsingChainRuleWorks) {
    Term const termToTest(
        Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(1, {{"y", 2}})});
    Term const x(createExpressionIfPossible({"t", "*", cos("t")}));
    Term const y(createExpressionIfPossible({"t", "*", sin("t")}));
    SubstitutionOfVariablesToTerms substitution;
    substitution.putVariableWithTerm("x", x);
    substitution.putVariableWithTerm("y", y);

    Term const termToVerify(getTotalDerivativeWithInnerTermsUsingChainRule(termToTest, substitution, "t"));

    string const stringToExpect1(
        "((2[t]*(cos(t)^2))+(4[t]*cos(t)*sin(t))-(2[t^2]*(sin(t)^2))+(2[t^2]*(cos(t)^2))+(2[t]*(sin(t)^2)))");
    EXPECT_EQ(stringToExpect1, convertToString(termToVerify));
}

TEST(DifferentiationUtilitiesTest, GetTotalDerivativeWorks) {
    Term const termToTest(
        Polynomial{Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 1}, {"y", 1}}), Monomial(-5, {{"y", 3}})});

    Term const termToVerify(getTotalDerivative(termToTest, {"x", "y"}));

    string const stringToExpect1("(3[d[x]][x^2] + -15[d[y]][y^2] + 3[d[x]][y] + 3[d[y]][x])");
    EXPECT_EQ(stringToExpect1, convertToString(termToVerify));
}

TEST(DifferentiationUtilitiesTest, GetPartialDerivativeWorks) {
    Term const termToTest(
        Polynomial{Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 1}, {"y", 1}}), Monomial(-5, {{"y", 3}})});

    Term const termToVerify1(getPartialDerivative(termToTest, "x"));
    Term const termToVerify2(getPartialDerivative(termToTest, "y"));

    string const stringToExpect1("(3[x^2] + 3[y])");
    string const stringToExpect2("(-15[y^2] + 3[x])");
    EXPECT_EQ(stringToExpect1, convertToString(termToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(termToVerify2));
}

TEST(DifferentiationUtilitiesTest, GetPartialDerivativeContinuouslyWorks) {
    Term const part1(createExpressionIfPossible({getEAsATerm(), "^", "x", "*", sin("y")}));
    Term const part2(ln(Monomial(1, {{"x", 1}, {"y", 1}})));
    Term const termToTest(createExpressionIfPossible({part1, "+", part2}));

    Term const termToVerify(
        getPartialDerivative(getPartialDerivative(getPartialDerivative(termToTest, "y"), "y"), "x"));

    string const stringToExpect("(-1*((e)^x)*sin(y))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(DifferentiationUtilitiesTest, IsTheFirstFundamentalTheoremOfCalculusTrueWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_TRUE(isTheFirstFundamentalTheoremOfCalculusTrue(termToTest1, "x"));
    EXPECT_TRUE(isTheFirstFundamentalTheoremOfCalculusTrue(termToTest2, "x"));
    EXPECT_TRUE(isTheFirstFundamentalTheoremOfCalculusTrue(termToTest3, "x"));
}

TEST(DifferentiationUtilitiesTest, IsDifferentiableAtWorks) {
    Term const termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}));

    EXPECT_FALSE(isDifferentiableAt(termToTest, "x", 0));
    EXPECT_TRUE(isDifferentiableAt(termToTest, "x", 2));
}

TEST(DifferentiationUtilitiesTest, IsDifferentiableAtUsingDerivativeDefinitionWorks) {
    Term const termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}));

    EXPECT_FALSE(isDifferentiableAtUsingDerivativeDefinition(termToTest, "x", 0));
    EXPECT_TRUE(isDifferentiableAtUsingDerivativeDefinition(termToTest, "x", 2));
}

}  // namespace alba::algebra
