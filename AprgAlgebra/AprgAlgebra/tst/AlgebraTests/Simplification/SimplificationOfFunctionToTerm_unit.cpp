#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfFunctionToTerm.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra::Simplification {

TEST(SimplificationOfFunctionToTermTest, SimplifyWorksWhenInputIsConstant) {
    SimplificationOfFunctionToTerm const simplification;

    Term const termToVerify1(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(Functions::abs(-5)));
    Term const termToVerify2(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(Functions::abs(-5)));

    Term const termToExpect1(5);
    Term const termToExpect2(5);
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(
    SimplificationOfFunctionToTermTest,
    SimplifyOfTrigonometricFunctionsWorksWhenShouldSimplifyTrigonometricFunctionsToSinAndCosIsFalse) {
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldSimplifyTrigonometricFunctionsToSinAndCos = false;
    SimplificationOfFunctionToTerm::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm const simplification;

    Term const termToVerify1(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(sin("x")));
    Term const termToVerify2(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(cos("x")));
    Term const termToVerify3(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(tan("x")));
    Term const termToVerify4(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(csc("x")));
    Term const termToVerify5(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(sec("x")));
    Term const termToVerify6(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(cot("x")));

    Term const termToExpect1(sin("x"));
    Term const termToExpect2(cos("x"));
    Term const termToExpect3(tan("x"));
    Term const termToExpect4(csc("x"));
    Term const termToExpect5(sec("x"));
    Term const termToExpect6(cot("x"));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(
    SimplificationOfFunctionToTermTest,
    SimplifyOfTrigonometricFunctionsWorksWhenShouldSimplifyTrigonometricFunctionsToSinAndCosIsTrue) {
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldSimplifyTrigonometricFunctionsToSinAndCos = true;
    SimplificationOfFunctionToTerm::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm const simplification;

    Term const termToVerify1(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(sin("x")));
    Term const termToVerify2(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(cos("x")));
    Term const termToVerify3(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(tan("x")));
    Term const termToVerify4(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(csc("x")));
    Term const termToVerify5(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(sec("x")));
    Term const termToVerify6(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(cot("x")));

    Term const termToExpect1(sin("x"));
    Term const termToExpect2(cos("x"));
    Term const termToExpect3(createExpressionIfPossible({sin("x"), "/", cos("x")}));
    Term const termToExpect4(createExpressionIfPossible({1, "/", sin("x")}));
    Term const termToExpect5(createExpressionIfPossible({1, "/", cos("x")}));
    Term const termToExpect6(createExpressionIfPossible({cos("x"), "/", sin("x")}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(
    SimplificationOfFunctionToTermTest,
    SimplifyOfLogarithmicFunctionsWorksWhenShouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevelFalse) {
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel = false;
    SimplificationOfFunctionToTerm::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm const simplification;
    Term const addAndSubtractExpression(createExpressionIfPossible({"x", "+", "y", "-", "z"}));
    Term const multiplicationAndDivisionExpression(createExpressionIfPossible({"x", "*", "y", "/", "z"}));
    Term const raiseToPowerExpression(createExpressionIfPossible({"x", "^", "y", "^", "z"}));

    Term const termToVerify1(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(ln("x")));
    Term const termToVerify2(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(ln(addAndSubtractExpression)));
    Term const termToVerify3(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(
        ln(multiplicationAndDivisionExpression)));
    Term const termToVerify4(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(ln(raiseToPowerExpression)));
    Term const termToVerify5(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(log("x")));
    Term const termToVerify6(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(log(addAndSubtractExpression)));
    Term const termToVerify7(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(
        log(multiplicationAndDivisionExpression)));
    Term const termToVerify8(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(log(raiseToPowerExpression)));

    Term const termToExpect1(ln("x"));
    Term const termToExpect2(ln(addAndSubtractExpression));
    Term const termToExpect3(createExpressionIfPossible({ln("x"), "+", ln("y"), "-", ln("z")}));
    Term const termToExpect4(createExpressionIfPossible({Monomial(1, {{"y", 1}, {"z", 1}}), "*", ln("x")}));
    Term const termToExpect5(log("x"));
    Term const termToExpect6(log(addAndSubtractExpression));
    Term const termToExpect7(createExpressionIfPossible({log("x"), "+", log("y"), "-", log("z")}));
    Term const termToExpect8(createExpressionIfPossible({Monomial(1, {{"y", 1}, {"z", 1}}), "*", log("x")}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
    EXPECT_EQ(termToExpect7, termToVerify7);
    EXPECT_EQ(termToExpect8, termToVerify8);
}

TEST(
    SimplificationOfFunctionToTermTest,
    SimplifyOfLogarithmicFunctionsWorksWhenShouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevelTrue) {
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel = true;
    SimplificationOfFunctionToTerm::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm const simplification;
    Term const addAndSubtractExpression(createExpressionIfPossible({"x", "+", "y", "-", "z"}));
    Term const multiplicationAndDivisionExpression(createExpressionIfPossible({"x", "*", "y", "/", "z"}));
    Term const raiseToPowerExpression(createExpressionIfPossible({"x", "^", "y", "^", "z"}));

    Term const termToVerify1(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(ln("x")));
    Term const termToVerify2(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(ln(addAndSubtractExpression)));
    Term const termToVerify3(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(
        ln(multiplicationAndDivisionExpression)));
    Term const termToVerify4(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(ln(raiseToPowerExpression)));
    Term const termToVerify5(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(log("x")));
    Term const termToVerify6(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(log(addAndSubtractExpression)));
    Term const termToVerify7(alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(
        log(multiplicationAndDivisionExpression)));
    Term const termToVerify8(
        alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(log(raiseToPowerExpression)));

    Term const termToExpect1(ln("x"));
    Term const termToExpect2(ln(addAndSubtractExpression));
    Term const termToExpect3(ln(multiplicationAndDivisionExpression));
    Term const termToExpect4(ln(raiseToPowerExpression));
    Term const termToExpect5(log("x"));
    Term const termToExpect6(log(addAndSubtractExpression));
    Term const termToExpect7(log(multiplicationAndDivisionExpression));
    Term const termToExpect8(log(raiseToPowerExpression));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
    EXPECT_EQ(termToExpect7, termToVerify7);
    EXPECT_EQ(termToExpect8, termToVerify8);
}

}  // namespace alba::algebra::Simplification
