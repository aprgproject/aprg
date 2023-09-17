#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra::Simplification {

TEST(SimplificationOfExpressionTest, SimplifyWorksOnSimplifyingInnerTerms) {
    Expression const monomialRaiseToMonomial(
        createExpressionIfPossible({Monomial(1, {{"x", 1}}), "^", Monomial(1, {{"y", 1}})}));
    SimplificationOfExpression simplification(monomialRaiseToMonomial);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"x", "^", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForAMultipleTermExpression) {
    Term const expressionTerm(createExpressionIfPossible({"x", "^", "x"}));
    Term const expressionInExpressionTerm(createAndWrapExpressionFromATerm(expressionTerm));
    Term const expressionInExpressionInExpressionTerm(createAndWrapExpressionFromATerm(expressionInExpressionTerm));
    Expression const expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"x", "^", "x"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentAdditionExpressionLevels) {
    Term const expressionTermLevel1(createExpressionIfPossible({"c", "+", "d"}));
    Term const expressionTermLevel2(createExpressionIfPossible({"b", "+", expressionTermLevel1}));
    Term const expressionTermLevel3(createExpressionIfPossible({"a", "+", expressionTermLevel2}));
    Expression const expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm(Polynomial{
        Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}}), Monomial(1, {{"c", 1}}), Monomial(1, {{"d", 1}})}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentMultiplicationExpressionLevels) {
    Term const expressionTermLevel1(createExpressionIfPossible({"c", "*", "d"}));
    Term const expressionTermLevel2(createExpressionIfPossible({"b", "*", expressionTermLevel1}));
    Term const expressionTermLevel3(createExpressionIfPossible({"a", "*", expressionTermLevel2}));
    Expression const expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(
        createAndWrapExpressionFromATerm(Monomial(1, {{"a", 1}, {"b", 1}, {"c", 1}, {"d", 1}})));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentRaiseToPowerExpressionLevels) {
    Term const expressionTermLevel1(createExpressionIfPossible({"c", "^", "d"}));
    Term const expressionTermLevel2(createExpressionIfPossible({"b", "^", expressionTermLevel1}));
    Term const expressionTermLevel3(createExpressionIfPossible({"a", "^", expressionTermLevel2}));
    Expression const expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const& expressionToExpect(expressionToTest);
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForASingleTermExpression) {
    Term const expressionTerm(createAndWrapExpressionFromATerm(967));
    Term const expressionInExpressionTerm(createAndWrapExpressionFromATerm(expressionTerm));
    Term const expressionInExpressionInExpressionTerm(createAndWrapExpressionFromATerm(expressionInExpressionTerm));
    Expression const expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(967));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingNullExpressions) {
    Expression const nullExpression(createExpressionInAnExpression(Expression()));
    Expression const expressionToTest(
        createExpressionIfPossible({nullExpression, "+", nullExpression, "+", nullExpression}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect;
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForAddingAndSubtracting) {
    Expression const expressionToTest(createExpressionIfPossible({0, "-", 200, "-", 50, "-", 0}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(-250));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForMultiplying) {
    Expression const expressionToTest(createExpressionIfPossible({0, "*", 200, "*", 50}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(0));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForMultiplyingWithRaiseToPowerExpression) {
    Expression const expressionToTest(createExpressionIfPossible({0, "*", "z", "^", "z"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(0));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForDividing) {
    Expression const expressionToTest(createExpressionIfPossible({0, "/", 1.17157287525381}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(0));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForDividingWithRaiseToPowerExpression) {
    Expression const expressionToTest(createExpressionIfPossible({0, "/", "z", "^", "z"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(0));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstants) {
    Expression const expressionToTest(createExpressionIfPossible({100, "+", 200, "-", 50}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(250));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsMonomialPolynomial) {
    Expression const expressionToTest(createExpressionIfPossible(
        {Monomial(43, {{"x", 2}, {"y", 3}}), "+", 159, "-",
         Polynomial{Monomial(56, {{"x", 3}}), Monomial(-251, {}), Monomial(13, {{"x", 2}, {"y", 3}})}}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible(
        {Polynomial{Monomial(30, {{"x", 2}, {"y", 3}}), Monomial(-56, {{"x", 3}}), Monomial(410, {})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsWithExpressionInBetween) {
    Expression const expressionToTest(createExpressionIfPossible({500, "+", "y", "^", "y", "-", 150}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const subExpression(createExpressionIfPossible({"y", "^", "y"}));
    Expression expressionToExpect(createExpressionIfPossible({350, "+", subExpression}));
    expressionToExpect.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingZerosWithExpressionInBetween) {
    Expression const expressionToTest(createExpressionIfPossible({0, "+", "y", "^", "y", "-", 0}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"y", "^", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingRaiseToPowerExpressions) {
    Expression const expressionToTest(
        createExpressionIfPossible({5, "*", "y", "^", "y", "+", "y", "^", "y", "-", 3, "*", "y", "^", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const subExpression(createExpressionIfPossible({"y", "^", "y"}));
    Expression const expressionToExpect(createExpressionIfPossible({3, "*", subExpression}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingMultipleRaiseToPowerExpressions) {
    Expression const expressionToTest(
        createExpressionIfPossible({"x", "^", "y", "-", 2, "*", "y", "^", "y", "-", 3, "*", "x", "^", "y", "+",
                                    "y", "^", "y", "+", 4, "*", "x", "^", "y", "+", 5, "*", "y", "^", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const subExpression1(createExpressionIfPossible({"x", "^", "y"}));
    Expression const subExpression2(createExpressionIfPossible({"y", "^", "y"}));
    Expression const subExpression3(createExpressionIfPossible({2, "*", subExpression1}));
    Expression const subExpression4(createExpressionIfPossible({4, "*", subExpression2}));
    Expression const expressionToExpect(createExpressionIfPossible({subExpression3, "+", subExpression4}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingNonSortedRaiseToPowerExpressions) {
    Expression const expressionToTest(createExpressionIfPossible(
        {100, "*", "y", "^", "y", "*", "x", "^", "x", "-", 10, "*", "x", "^", "x", "*", "y", "^", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const subExpression1(createExpressionIfPossible({"x", "^", "x"}));
    Expression const subExpression2(createExpressionIfPossible({"y", "^", "y"}));
    Expression const subExpression3(createExpressionIfPossible({subExpression1, "*", subExpression2}));
    Expression const expressionToExpect(createExpressionIfPossible({90, "*", subExpression3}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingRaiseToPowerExpressionsThatCannotBeAdded) {
    Expression const expressionToTest(
        createExpressionIfPossible({10,  "*", "y", "^", "y", "+", "x", "*", "y", "^", "y", "-", 8,
                                    "*", "y", "^", "y", "-", 6,   "*", "x", "*", "y", "^", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const subExpression1(createExpressionIfPossible({"y", "^", "y"}));
    Expression const subExpression2(createExpressionIfPossible({2, "*", subExpression1}));
    Expression const subExpression3(createExpressionIfPossible({Monomial(5, {{"x", 1}}), "*", subExpression1}));
    Expression const expressionToExpect(createExpressionIfPossible({subExpression2, "-", subExpression3}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingConstants) {
    Expression const expressionToTest(createExpressionIfPossible({100, "*", 200, "/", 50}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({400}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingPolynomials) {
    Expression const expressionToTest(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}, {"y", -1}}), Monomial(2, {{"x", -1}, {"y", 1}})}, "/",
         Polynomial{Monomial(3, {{"y", 1}}), Monomial(4, {{"z", -1}})}}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 2}, {"z", 1}}), Monomial(2, {{"y", 2}, {"z", 1}})}, "/",
         Polynomial{Monomial(3, {{"x", 1}, {"y", 2}, {"z", 1}}), Monomial(4, {{"x", 1}, {"y", 1}})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingRaiseToPowerExpressionsCanBeCancelled) {
    Expression const expressionToTest(
        createExpressionIfPossible({"x", "^", "x", "*", "y", "^", "y", "*", "z", "^", "z", "/",
                                    "z", "^", "z", "/", "y", "^", "y", "/", "x", "^", "x"}));

    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({1}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerWithMultipleTerms) {
    Expression const expression1(createExpressionIfPossible({"a", "^", "b", "^", "c", "^", "d"}));
    Expression const expression2(createExpressionIfPossible({"x", "^", 2, "^", 3, "^", "y"}));
    SimplificationOfExpression simplification1(expression1);
    SimplificationOfExpression simplification2(expression2);

    simplification1.simplify();
    simplification2.simplify();

    Expression const expressionToVerify1(simplification1.getExpression());
    Expression const expressionToVerify2(simplification2.getExpression());
    Expression const expressionToExpect1(
        createExpressionIfPossible({"a", "^", Monomial(1, {{"b", 1}, {"c", 1}, {"d", 1}})}));
    Expression const expressionToExpect2(createExpressionIfPossible({"x", "^", Monomial(6, {{"y", 1}})}));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerAndItsNotAssociative) {
    Term const aToTheB(createExpressionIfPossible({"a", "^", "b"}));
    Term const xToTheY(createExpressionIfPossible({"x", "^", "y"}));
    Expression const expression(createExpressionIfPossible({aToTheB, "^", xToTheY}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(
        createExpressionIfPossible({"a", "^", createExpressionIfPossible({"b", "*", xToTheY})}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksMultiplyingPolynomialOverPolynomials) {
    Polynomial const polynomial1{Monomial(3, {{"x", 2}}), Monomial(-12, {{"x", 1}}), Monomial(-2, {})};
    Polynomial const polynomial2{Monomial(1, {{"x", 2}}), Monomial(-6, {{"x", 1}}), Monomial(9, {})};
    Polynomial const polynomial3{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(6, {})};
    Polynomial const polynomial4{Monomial(1, {{"x", 2}}), Monomial(6, {{"x", 1}}), Monomial(9, {})};
    Polynomial const polynomial5{
        Monomial(3, {{"x", 4}}), Monomial(-32, {{"x", 2}}), Monomial(-80, {{"x", 1}}), Monomial(-12, {})};
    Polynomial const polynomial6{Monomial(1, {{"x", 4}}), Monomial(-18, {{"x", 2}}), Monomial(81, {})};
    Expression const subExpression1(createExpressionIfPossible({polynomial1, "/", polynomial2}));
    Expression const subExpression2(createExpressionIfPossible({polynomial3, "/", polynomial4}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression1, "*", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({polynomial5, "/", polynomial6}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksInsideAFunction) {
    Function const absoluteValueFunction(abs(createOrCopyExpressionFromATerm(-100)));
    Expression const expressionToTest(createOrCopyExpressionFromATerm(absoluteValueFunction));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(100));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnConstantOverConstant) {
    Expression expressionToTest;
    expressionToTest.putTermWithMultiplicationIfNeeded(Term(-252));
    expressionToTest.putTermWithDivisionIfNeeded(Term(25));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    EXPECT_EQ(Expression(Term(AlbaNumber::createFraction(-252, 25))), expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnPolynomialsToFractionalExponents) {
    Expression const expressionToTest(
        createExpressionIfPossible(tokenizeToTerms("(x+1)^(1/2)*(y+1)^(-1/3)*(z+1)^(1/4)")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const xPolynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term const yPolynomialTerm(Polynomial{Monomial(1, {{"y", 1}}), Monomial(1, {})});
    Term const zPolynomialTerm(Polynomial{Monomial(1, {{"z", 1}}), Monomial(1, {})});
    Term const xExpressionTerm(createExpressionIfPossible({xPolynomialTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Term const yExpressionTerm(createExpressionIfPossible({yPolynomialTerm, "^", AlbaNumber::createFraction(1, 3)}));
    Term const zExpressionTerm(createExpressionIfPossible({zPolynomialTerm, "^", AlbaNumber::createFraction(1, 4)}));
    Expression const expressionToExpect(
        createExpressionIfPossible({xExpressionTerm, "*", zExpressionTerm, "/", yExpressionTerm}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithEvaluatingFunctions) {
    Expression const expressionToTest(createExpressionIfPossible(tokenizeToTerms("x^2*y^-abs(-3)*z^4")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Monomial const monomialToExpect(1, {{"x", 2}, {"y", -3}, {"z", 4}});
    Expression const expressionToExpect(createAndWrapExpressionFromATerm(monomialToExpect));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(ExpressionTest, SimplifyWorksOnAddingMonomialAndExponentialTerms) {
    Expression const subExpression1(createExpressionIfPossible({"a", "^", "b"}));
    Expression const subExpression2(createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", subExpression1}));
    Expression const subExpression3(createExpressionIfPossible({Monomial(1, {{"y", 1}}), "*", subExpression1}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression2, "+", subExpression3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible(
        {createExpressionIfPossible({"x", "*", subExpression1}), "+",
         createExpressionIfPossible({"y", "*", subExpression1})}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ZeroOverZeroResultsToNanAndDoesNotCrash) {
    Expression const expression(createExpressionIfPossible({0, "/", 0}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    EXPECT_TRUE(isNan(expressionToVerify));
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorksAsDefault) {
    Expression const expressionToTest(
        createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const firstPart(createExpressionIfPossible({4, "/", Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}}));
    Term const secondPart(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}, "/",
         Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}}));
    Term const thirdPart(createExpressionIfPossible(
        {Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}, "/",
         Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}}));
    Expression const expressionToExpect(createExpressionIfPossible({firstPart, "+", secondPart, "+", thirdPart}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorksIfItsNotSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToACommonDenominator = false;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const expressionToTest(
        createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const firstPart(createExpressionIfPossible({4, "/", Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}}));
    Term const secondPart(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}, "/",
         Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}}));
    Term const thirdPart(createExpressionIfPossible(
        {Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}, "/",
         Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}}));
    Expression const expressionToExpect(createExpressionIfPossible({firstPart, "+", secondPart, "+", thirdPart}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorksIfItsSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const expressionToTest(
        createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible(
        {Polynomial{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})}, "/",
         Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorksWithExponentialAndTrigonometricFunction) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const eToTheX(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    Term const eToTheXTimesSinX(createExpressionIfPossible({eToTheX, "*", sin("x")}));
    Term const eToTheXTimesCosX(createExpressionIfPossible({eToTheX, "*", cos("x")}));
    Term const expression1(createExpressionIfPossible({eToTheXTimesSinX, "-", eToTheXTimesCosX}));
    Term const expression2(createExpressionIfPossible({expression1, "/", 2}));
    Term const expressionToTest(
        createExpressionIfPossible({eToTheXTimesSinX, "-", eToTheXTimesCosX, "-", expression2}));
    SimplificationOfExpression simplification((Expression(expressionToTest)));

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    EXPECT_EQ("(((((e)^x)*sin(x))-(((e)^x)*cos(x)))/2)", convertToString(expressionToVerify));
}

TEST(SimplificationOfExpressionTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorksAsDefault) {
    Expression const expression(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", 4, "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(
        {Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorksIfItsNotSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase = false;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const expression(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", 4, "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm(
        {Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorksIfItsSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const expression(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", 4, "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(
        createExpressionIfPossible({abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), "^", 2}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningRadicalsInMultiplicationAndDivisionWorksAsDefault) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression const squareRootOfXPlusOne(
        createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Expression const expressionToTest(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningRadicalsInMultiplicationAndDivisionWorksIfItsNotSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = false;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression const squareRootOfXPlusOne(
        createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Expression const expressionToTest(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningRadicalsInMultiplicationAndDivisionWorksIfItsSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression const squareRootOfXPlusOne(
        createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Expression const expressionToTest(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}})});
    Expression const expressionToExpect(
        createExpressionIfPossible({insideSquareRootTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorksAsDefault) {
    Term const xPlusOneSquaredExpandedTerm(
        Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression const expressionToTest(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorksIfItsNotSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = false;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const xPlusOneSquaredExpandedTerm(
        Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression const expressionToTest(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorksIfItsSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const xPlusOneSquaredExpandedTerm(
        Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression const expressionToTest(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", Monomial(2, {{"x", 1}})}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingNumeratorWorksAsDefault) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingNumeratorWorksIfItsNotSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByRationalizingNumerator = false;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingNumeratorWorksIfItsSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByRationalizingNumerator = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term const expectedDenominator(
        Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    Expression const expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingDenominatorWorksAsDefault) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingDenominatorWorksIfItsNotSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByRationalizingDenominator = false;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingDenominatorWorksIfItsSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByRationalizingDenominator = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Term const expectedNumerator(
        Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-9, {})});
    Expression const expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySubstitutingExpressionAndFunctionsToVariablesWorksAsDefault) {
    Term const tanX(tan("x"));
    Term const numerator(createExpressionIfPossible({1, "+", tanX, "^", 2, "+", 2, "*", tanX}));
    Term const denominator(createExpressionIfPossible({tanX, "+", 1}));
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({numerator, "/", denominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySubstitutingExpressionAndFunctionsToVariablesWorksIfItsNotSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables = false;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const tanX(tan("x"));
    Term const numerator(createExpressionIfPossible({1, "+", tanX, "^", 2, "+", 2, "*", tanX}));
    Term const denominator(createExpressionIfPossible({tanX, "+", 1}));
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({numerator, "/", denominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySubstitutingExpressionAndFunctionsToVariablesWorksIfItsSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const tanX(tan("x"));
    Term const numerator(createExpressionIfPossible({1, "+", tanX, "^", 2, "+", 2, "*", tanX}));
    Term const denominator(createExpressionIfPossible({tanX, "+", 1}));
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({tanX, "+", 1}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(
    SimplificationOfExpressionTest,
    SimplifyBySubstitutingExpressionAndFunctionsToVariablesDoesNotCauseInfiniteLoopIfItsSet) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const xToTheX(createExpressionIfPossible({"x", "^", "x"}));
    Term const yToTheY(createExpressionIfPossible({"y", "^", "y"}));
    Expression const expressionToTest(createExpressionIfPossible({xToTheX, "-", yToTheY}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({xToTheX, "-", yToTheY}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySimplifyingToFactorsWorks) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToFactors = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const polynomialTerm(Polynomial{Monomial(7, {{"x", 3}}), Monomial(-1, {})});
    Term const numerator(createExpressionIfPossible({polynomialTerm, "^", 2}));
    Term const denominator(createExpressionIfPossible({polynomialTerm, "^", 8}));
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    string const stringToExpect("(1/117649/((1[x] + -0.522758)^6)/((1[x^2] + 0.522758[x] + 0.273276)^6))");
    EXPECT_EQ(stringToExpect, convertToString(expressionToVerify));
}

TEST(
    SimplificationOfExpressionTest,
    ShouldSimplifyToACommonDenominatorAndShouldSimplifyToFactorsWorksToConvertPolynomialOverPolynomial) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToFactors = true;
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Polynomial const polynomial{Monomial(1, {}), Monomial(1, {{"x", -2}})};
    Expression const expressionToTest(createExpressionIfPossible({polynomial, "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Polynomial const polynomialToExpect{Monomial(1, {{"x", 2}}), Monomial(1, {})};
    Expression const expressionToExpect(
        createExpressionIfPossible({polynomialToExpect, "^", AlbaNumber::createFraction(1, 2), "/", "x"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsOverTermsTest, SimplifyBySimplifyingToFactorsWithoutDoubleValueWorks) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToFactors = true;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term const numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-5, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-7, {})});
    Expression const expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({numerator, "/", denominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

}  // namespace alba::algebra::Simplification
