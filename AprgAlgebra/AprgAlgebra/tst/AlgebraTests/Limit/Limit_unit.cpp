#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(LimitTest, CalculateTermAndLimitUsingLhopitalsRuleWorksUsingTrigonometricExample) {
    Term const oneOverX(createExpressionIfPossible({1, "/", "x"}));
    Term const termToTest(createExpressionIfPossible({sin(oneOverX), "/", arctan(oneOverX)}));

    Term newTerm;
    Term limitValue;
    calculateTermAndLimitUsingLhopitalsRule(newTerm, limitValue, termToTest, "x", ALBA_NUMBER_POSITIVE_INFINITY);

    string const stringToExpect("((1[x^2] + 1)*cos((1/x))/1[x^2])");
    EXPECT_EQ(Term(1), limitValue);
    EXPECT_EQ(stringToExpect, convertToString(newTerm));
}

TEST(LimitTest, CalculateTermAndLimitUsingLhopitalsRuleWorksUsingLogarithmicAndExponentialExample) {
    Term const insideLogarithm(createExpressionIfPossible({2, "+", getEAsATerm(), "^", "x"}));
    Term const numerator(ln(insideLogarithm));
    Term const denominator(Monomial(3, {{"x", 1}}));
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    Term newTerm;
    Term limitValue;
    calculateTermAndLimitUsingLhopitalsRule(newTerm, limitValue, termToTest, "x", ALBA_NUMBER_POSITIVE_INFINITY);

    string const stringToExpect("(1/3)");
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 3)), limitValue);
    EXPECT_EQ(stringToExpect, convertToString(newTerm));
}

TEST(LimitTest, CalculateTermAndLimitUsingLhopitalsRuleWorksUsingTrigonometricExample2) {
    Term const xSquared(Monomial(1, {{"x", 2}}));
    Term const termToTestPart1(createExpressionIfPossible({1, "/", xSquared}));
    Term const termToTestPart2(createExpressionIfPossible({1, "/", xSquared, "/", sec("x")}));
    Term const termToTest(createExpressionIfPossible({termToTestPart1, "-", termToTestPart2}));

    Term newTerm;
    Term limitValue;
    calculateTermAndLimitUsingLhopitalsRule(newTerm, limitValue, termToTest, "x", 0);

    string const stringToExpect("((sec(x)^2)/(2+(1[x^2]*(sec(x)^2))+(2[x]*tan(x))))");
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), limitValue);
    EXPECT_EQ(stringToExpect, convertToString(newTerm));
}

TEST(LimitTest, GetLimitAtAValueByApproachTypeWorksForPolynomialOverPolynomial) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(
        AlbaNumber(10),
        getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(
        AlbaNumber(10),
        getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        AlbaNumber(10),
        getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueInBothSidesWorksForPolynomialOverPolynomial) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInBothSides(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueInThePositiveSideWorksForPolynomialOverPolynomial) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInThePositiveSide(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueInTheNegativeSideWorksForPolynomialOverPolynomial) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInTheNegativeSide(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueByIterationAndLinearInterpolationWorksForPolynomialOverPolynomial) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(
        AlbaNumber(10), getLimitAtAValueByIterationAndLinearInterpolation(polynomialOverPolynomialTerm, "x", 5, 6, 10));
    EXPECT_EQ(
        AlbaNumber(10), getLimitAtAValueByIterationAndLinearInterpolation(polynomialOverPolynomialTerm, "x", 5, 4, 10));
}

TEST(LimitTest, GetLimitAtAValueUsingTrendOfValuesWorks) {
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const constantOverPolynomialTerm(createExpressionIfPossible({3, "/", denominator}));

    EXPECT_EQ(
        ALBA_NUMBER_POSITIVE_INFINITY, getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 2, 3, 4));
    EXPECT_EQ(
        ALBA_NUMBER_NEGATIVE_INFINITY, getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 2, 1, 0));
    EXPECT_EQ(
        AlbaNumber::createFraction(9, 10),
        getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 5, 6, 7));
}

TEST(LimitTest, GetValueUsingLinearInterpolationWorks) {
    EXPECT_EQ(AlbaNumber(6), getValueUsingLinearInterpolation(1, 2, 3, 2, 4));
    EXPECT_EQ(AlbaNumber(2), getValueUsingLinearInterpolation(1, 2, 3, 2, 2));
    EXPECT_TRUE(getValueUsingLinearInterpolation(1, 1, 3, 1, 2).isNotANumber());
    EXPECT_TRUE(getValueUsingLinearInterpolation(1, 1, 3, 2, 2).isNotANumber());
}

TEST(LimitTest, GetLimitWorksOnSingleVariable) {
    Term const termToVerify(getLimit("x", "x", 5));

    EXPECT_EQ(Term(5), termToVerify);
}

TEST(LimitTest, GetLimitWithMultipleVariablesWithDifferentApproachesWorksOnExample1) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-1, {{"y", 4}})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})});
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SubstitutionsOfVariablesToTerms substitutions;
    substitutions.emplace_back(VariablesToTermsMap{{"y", "x"}});
    substitutions.emplace_back(VariablesToTermsMap{{"y", Monomial(1, {{"x", 2}})}});
    Term const termToVerify(getLimitWithMultipleVariablesWithDifferentApproaches(termToTest, "x", 0, substitutions));

    EXPECT_EQ(Term(0), termToVerify);
}

TEST(LimitTest, GetLimitWithMultipleVariablesWithDifferentApproachesWorksOnExample2) {
    Term const numerator(Monomial(1, {{"x", 1}, {"y", 1}}));
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})});
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SubstitutionsOfVariablesToTerms substitutions;
    substitutions.emplace_back(VariablesToTermsMap{{"y", "x"}});
    substitutions.emplace_back(VariablesToTermsMap{{"y", Monomial(1, {{"x", 2}})}});
    Term const termToVerify(getLimitWithMultipleVariablesWithDifferentApproaches(termToTest, "x", 0, substitutions));

    EXPECT_TRUE(isNan(termToVerify));
}

TEST(LimitTest, GetLimitUsingLhopitalsRuleWorks) {
    Term const oneMinusEToTheX(createExpressionIfPossible({1, "-", getEAsATerm(), "^", "x"}));
    Term const oneOverX(createExpressionIfPossible({1, "/", "x"}));
    Term const termToTest1("x");
    Term const termToTest2(createExpressionIfPossible({"x", "/", oneMinusEToTheX}));
    Term const termToTest3(createExpressionIfPossible({sin(oneOverX), "/", arctan(oneOverX)}));

    Term const termToVerify1(getLimitUsingLhopitalsRule(termToTest1, "x", 5));
    Term const termToVerify2(getLimitUsingLhopitalsRule(termToTest2, "x", 0));
    Term const termToVerify3(getLimitUsingLhopitalsRule(termToTest3, "x", ALBA_NUMBER_POSITIVE_INFINITY));

    EXPECT_EQ(Term(5), termToVerify1);
    EXPECT_EQ(Term(-1), termToVerify2);
    EXPECT_EQ(Term(1), termToVerify3);
}

TEST(LimitTest, GetTermUsingLhopitalsRuleWorks) {
    Term const oneMinusEToTheX(createExpressionIfPossible({1, "-", getEAsATerm(), "^", "x"}));
    Term const oneOverX(createExpressionIfPossible({1, "/", "x"}));
    Term const termToTest1("x");
    Term const termToTest2(createExpressionIfPossible({"x", "/", oneMinusEToTheX}));
    Term const termToTest3(createExpressionIfPossible({sin(oneOverX), "/", arctan(oneOverX)}));

    Term const termToVerify1(getTermUsingLhopitalsRule(termToTest1, "x", 5));
    Term const termToVerify2(getTermUsingLhopitalsRule(termToTest2, "x", 0));
    Term const termToVerify3(getTermUsingLhopitalsRule(termToTest3, "x", ALBA_NUMBER_POSITIVE_INFINITY));

    string const stringToExpect1("x");
    string const stringToExpect2("(-1/((e)^x))");
    string const stringToExpect3("((1[x^2] + 1)*cos((1/x))/1[x^2])");
    EXPECT_EQ(stringToExpect1, convertToString(termToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(termToVerify2));
    EXPECT_EQ(stringToExpect3, convertToString(termToVerify3));
}

TEST(LimitTest, GetLimitAtAValueOrInfinityWorks) {
    Term const termToTest1(Polynomial{Monomial(4, {{"x", 1}}), Monomial(-7, {})});
    Term const termToTest2(createExpressionIfPossible({1, "/", "x"}));

    EXPECT_EQ(Term(5), getLimitAtAValueOrInfinity(termToTest1, "x", 3));
    EXPECT_EQ(Term(0), getLimitAtAValueOrInfinity(termToTest2, "x", ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitTest, GetLimitAtAValueWorksWhichDoesNotResultToConstant) {
    Term const polynomialTerm(Polynomial{Monomial(4, {{"x", 1}, {"y", 2}}), Monomial(-7, {})});

    Term const expectedTermWithY(Polynomial{Monomial(12, {{"y", 2}}), Monomial(-7, {})});
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomial) {
    Term const polynomialTerm(Polynomial{Monomial(4, {{"x", 1}}), Monomial(-7, {})});

    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForConstantOverPolynomial) {
    Term const numerator(3);
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const constantOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_TRUE(isNan(getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(
        getPositiveInfinityAsATerm(),
        getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        getNegativeInfinityAsATerm(),
        getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForConstantOverPolynomialSquared) {
    Term const numerator(3);
    Term const polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const denominator(createExpressionIfPossible({polynomialTerm, "^", 2}));
    Term const constantOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(
        getPositiveInfinityAsATerm(),
        getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(
        getPositiveInfinityAsATerm(),
        getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        getPositiveInfinityAsATerm(),
        getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomial) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(
        Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomialWithDiscontinuityAtOneTwoThree) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}})});
    Term const denominator(
        Polynomial{Monomial(1, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(11, {{"x", 1}}), Monomial(-6, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_TRUE(isNan(getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(
        Term(-4), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        Term(-3.88235294117647056211239942058),
        getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomialWithEqualDegreeButNoCommonFactors) {
    Term const numerator(Polynomial{Monomial(2, {{"x", 2}}), Monomial(5, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-3, {{"x", 1}}), Monomial(2, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_TRUE(isNan(getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(
        getPositiveInfinityAsATerm(),
        getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        getNegativeInfinityAsATerm(),
        getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomialWithFractionalValues) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(
        Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForSignumFunction) {
    Term const signumFunctionTerm(sgn("x"));

    EXPECT_TRUE(isNan(getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(Term(1), getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(-1), getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForAbsoluteValueFunction) {
    Term const absoluteValueFunction(Functions::abs("x"));

    EXPECT_EQ(Term(0), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(0), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(0), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForASpecifiedFunction) {
    Function const functionToTest("functionToTest", Term("x"), [](AlbaNumber const& number) {
        AlbaNumber result;
        AlbaNumber const numberSquared(number ^ 2);
        if (number > 1) {
            result = numberSquared + 2;
        } else if (number < 1) {
            result = AlbaNumber(4) - numberSquared;
        } else {
            result = ALBA_NUMBER_NOT_A_NUMBER;
        }
        return result;
    });
    Term const functionTermToTest(functionToTest);

    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::NegativeSide));
}

TEST(
    LimitTest,
    SimplifyAndGetLimitAtAValueWorksForPolynomialOverPolynomialWithDiscontinuityAtOneTwoThreeAndCancelsProblematicFactors) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}})});
    Term const denominator(
        Polynomial{Monomial(1, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(11, {{"x", 1}}), Monomial(-6, {})});
    Term const polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(
        Term(-4),
        simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(
        Term(-4),
        simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(
        Term(-4),
        simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtInfinityWorks) {
    EXPECT_EQ(getNegativeInfinityAsATerm(), getLimitAtInfinity("x", "x", ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(getPositiveInfinityAsATerm(), getLimitAtInfinity("x", "x", ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitTest, GetObliqueAsymptoteWorksAsResultIsEmptyWhenItsALine) {
    Term const termToTest(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});

    EXPECT_EQ(Term(), getObliqueAsymptote(termToTest));
}

TEST(LimitTest, GetObliqueAsymptoteWorksAsResultIsEmptyWhenDegreeOfDenominatorIsGreater) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(3, {})});
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(), getObliqueAsymptote(termToTest));
}

TEST(LimitTest, GetObliqueAsymptoteWorksWhenThereIsAnObliqueAsymptote) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(3, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})});
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), getObliqueAsymptote(termToTest));
}

TEST(LimitTest, IsAlmostEqualForLimitIterationWorks) {
    AlbaNumber::ScopeConfigurationObject const scopeConfigurationObject;
    AlbaNumber::ScopeConfigurationObject::setInThisScopeTheTolerancesToZero();

    EXPECT_TRUE(isAlmostEqualForLimitIteration(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_FALSE(isAlmostEqualForLimitIteration(AlbaNumber(0.1), AlbaNumber(0.2)));
    EXPECT_FALSE(isAlmostEqualForLimitIteration(AlbaNumber(1E-15), AlbaNumber(3E-15)));
    EXPECT_TRUE(isAlmostEqualForLimitIteration(AlbaNumber(1E-16), AlbaNumber(3E-16)));
}

TEST(LimitTest, IsAlmostEqualForLimitCheckingWorks) {
    EXPECT_TRUE(isAlmostEqualForLimitChecking(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_FALSE(isAlmostEqualForLimitChecking(AlbaNumber(0.1), AlbaNumber(0.2)));
    EXPECT_FALSE(isAlmostEqualForLimitChecking(AlbaNumber(1E-5), AlbaNumber(3E-5)));
    EXPECT_TRUE(isAlmostEqualForLimitChecking(AlbaNumber(1E-6), AlbaNumber(3E-6)));
}

TEST(LimitTest, HasVerticalAsymptoteAtValueWorks) {
    Term const numerator(3);
    Term const denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const constantOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_FALSE(hasVerticalAsymptoteAtValue("x", "x", 2));
    EXPECT_TRUE(hasVerticalAsymptoteAtValue(constantOverPolynomialTerm, "x", 2));
}

TEST(LimitTest, HasHorizontalAsymptoteAtValueWorks) {
    Term const numerator("x");
    Term const denominatorInSquareRoot(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term const denominator(
        createExpressionIfPossible({denominatorInSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term const term(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_FALSE(hasHorizontalAsymptoteAtValue(term, "x", 3));
    EXPECT_TRUE(hasHorizontalAsymptoteAtValue(term, "x", 1));
}

TEST(LimitTest, IsSqueezeTheoremSatisfiedWorks) {
    Term const f(buildTermIfPossible("-4*(x-2)^2 + 3"));
    Term const g(buildTermIfPossible("(x-2)*(x^2 - 4*x + 7)/(x-2)"));
    Term const h(buildTermIfPossible("4*(x-2)^2 + 3"));

    EXPECT_FALSE(isSqueezeTheoremSatisfied(h, g, f, "x", 1));
    EXPECT_TRUE(isSqueezeTheoremSatisfied(h, g, f, "x", 2));
}

}  // namespace alba::algebra
