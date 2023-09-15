#include <BooleanAlgebra/Simplification/SimplificationOfExpression.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::booleanAlgebra::Simplification {

TEST(SimplificationOfExpressionTest, SimplifyWorksOnSimplifyingInnerTerms) {
    Expression const subExpression1(createExpressionIfPossible({"x", "&", "x"}));
    Expression const subExpression2(createExpressionIfPossible({"y", "|", "y"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression1, "|", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"x", "|", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForAMultipleTermExpression) {
    Term const expressionTerm(createExpressionIfPossible({"x", "&", "y"}));
    Term const expressionInExpressionTerm(createAndWrapExpressionFromATerm(expressionTerm));
    Term const expressionInExpressionInExpressionTerm(createAndWrapExpressionFromATerm(expressionInExpressionTerm));
    Expression const expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddOperationDifferentExpressionLevels) {
    Term const expressionTermLevel1(createExpressionIfPossible({"c", "&", "d"}));
    Term const expressionTermLevel2(createExpressionIfPossible({"b", "&", expressionTermLevel1}));
    Term const expressionTermLevel3(createExpressionIfPossible({"a", "&", expressionTermLevel2}));
    Expression const expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnOrOperationDifferentExpressionLevels) {
    Term const expressionTermLevel1(createExpressionIfPossible({"c", "|", "d"}));
    Term const expressionTermLevel2(createExpressionIfPossible({"b", "|", expressionTermLevel1}));
    Term const expressionTermLevel3(createExpressionIfPossible({"a", "|", expressionTermLevel2}));
    Expression const expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForASingleTermExpression) {
    Term const expressionTerm(createAndWrapExpressionFromATerm("x"));
    Term const expressionInExpressionTerm(createAndWrapExpressionFromATerm(expressionTerm));
    Term const expressionInExpressionInExpressionTerm(createAndWrapExpressionFromATerm(expressionInExpressionTerm));
    Expression const expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createOrCopyExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddOperationWithNullExpressions) {
    Expression const nullExpression(createExpressionInAnExpression(Expression()));
    Expression const expressionToTest(
        createExpressionIfPossible({nullExpression, "&", nullExpression, "&", nullExpression}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect;
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddOperationWithTrue) {
    Expression const expressionToTest(createExpressionIfPossible({"a", "&", "b", "&", true, "&", "c", "&", "d"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddOperationWithFalse) {
    Expression const expressionToTest(createExpressionIfPossible({"a", "&", "b", "&", false, "&", "c", "&", "d"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm(false));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnOrOperationWithTrue) {
    Expression const expressionToTest(createExpressionIfPossible({"a", "|", "b", "|", false, "|", "c", "|", "d"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnOrOperationWithFalse) {
    Expression const expressionToTest(createExpressionIfPossible({"a", "|", "b", "|", true, "|", "c", "|", "d"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRemovingSameTermsInAndOperationInDifferentLevels) {
    Expression const subExpression1(createExpressionIfPossible({"x", "&", "x"}));
    Expression const subExpression2(createExpressionIfPossible({"x", "&", subExpression1}));
    Expression const expressionToTest(createExpressionIfPossible({"x", "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRemovingSameTermsInOrOperationInDifferentLevels) {
    Expression const subExpression1(createExpressionIfPossible({"x", "|", "x"}));
    Expression const subExpression2(createExpressionIfPossible({"x", "|", subExpression1}));
    Expression const expressionToTest(createExpressionIfPossible({"x", "|", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksBySortingTermsInAndOperationInDifferentLevels) {
    Expression const subExpression1(createExpressionIfPossible({"b", "&", "a"}));
    Expression const subExpression2(createExpressionIfPossible({"c", "&", subExpression1}));
    Expression const expressionToTest(createExpressionIfPossible({"d", "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksBySortingTermsInOrOperationInDifferentLevels) {
    Expression const subExpression1(createExpressionIfPossible({"b", "|", "a"}));
    Expression const subExpression2(createExpressionIfPossible({"c", "|", subExpression1}));
    Expression const expressionToTest(createExpressionIfPossible({"d", "|", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByComplimentaryTermsInAndOperation) {
    Expression const expressionToTest(createExpressionIfPossible({"x", "&", "x'"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm(false));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByComplimentaryTermsInOrOperation) {
    Expression const expressionToTest(createExpressionIfPossible({"x", "|", "x'"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByWithOuterOrAndInnerAnd) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const subExpression1(createExpressionIfPossible({"x", "|", "y"}));
    Expression const subExpression2(createExpressionIfPossible({"x'", "|", "z"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression1, "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string const stringToVerify(convertToString(simplification.getExpression()));
    string const stringToExpect("((x&z)|(x'&y))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithOuterAndAndInnerOr) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const subExpression1(createExpressionIfPossible({"x'", "|", "y"}));
    Expression const subExpression2(createExpressionIfPossible({"x", "|", "z"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression1, "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string const stringToVerify(convertToString(simplification.getExpression()));
    string const stringToExpect("((x|z)&(x'|y))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByAlternatingAndOperationAndOrOperationWithDefaultConfiguration) {
    Expression const subExpression1(createExpressionIfPossible({"a", "&", "b"}));
    Expression const subExpression2(createExpressionIfPossible({subExpression1, "|", "c"}));
    Expression const subExpression3(createExpressionIfPossible({subExpression2, "&", "d"}));
    Expression const subExpression4(createExpressionIfPossible({subExpression3, "|", "e"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression4, "&", "f"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string const stringToVerify(convertToString(simplification.getExpression()));
    string const stringToExpect("((a&b&d&f)|(c&d&f)|(e&f))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByAlternatingAndOperationAndOrOperationWithOuterOrAndInnerAnd) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const subExpression1(createExpressionIfPossible({"a", "&", "b"}));
    Expression const subExpression2(createExpressionIfPossible({subExpression1, "|", "c"}));
    Expression const subExpression3(createExpressionIfPossible({subExpression2, "&", "d"}));
    Expression const subExpression4(createExpressionIfPossible({subExpression3, "|", "e"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression4, "&", "f"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string const stringToVerify(convertToString(simplification.getExpression()));
    string const stringToExpect("((a&b&d&f)|(c&d&f)|(e&f))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByAlternatingAndOperationAndOrOperationWithOuterAndAndInnerOr) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const subExpression1(createExpressionIfPossible({"a", "&", "b"}));
    Expression const subExpression2(createExpressionIfPossible({subExpression1, "|", "c"}));
    Expression const subExpression3(createExpressionIfPossible({subExpression2, "&", "d"}));
    Expression const subExpression4(createExpressionIfPossible({subExpression3, "|", "e"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression4, "&", "f"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string const stringToVerify(convertToString(simplification.getExpression()));
    string const stringToExpect("(f&(a|c|e)&(b|c|e)&(d|e))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByRemovingNeededTermsWithOuterOrAndInnerAnd) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const subExpression1(createExpressionIfPossible({"x", "|", "y'"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression1, "&", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksByRemovingNeededTermsWithOuterAndAndInnerOr) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const subExpression1(createExpressionIfPossible({"x", "&", "y'"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression1, "|", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createExpressionIfPossible({"x", "|", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithCombininingTermsByCheckingTheCommonFactorUsingPattern1) {
    Expression const subExpression1(createExpressionIfPossible({"x", "&", "y"}));
    Expression const subExpression2(createExpressionIfPossible({"x", "&", "y'"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression1, "|", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithCombininingTermsByCheckingTheCommonFactorUsingPattern2) {
    Expression const subExpression1(createExpressionIfPossible({"x", "|", "y"}));
    Expression const subExpression2(createExpressionIfPossible({"x", "|", "y'"}));
    Expression const expressionToTest(createExpressionIfPossible({subExpression1, "&", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithCombininingTermsByCheckingTheCommonFactorUsingPattern3) {
    Expression const subExpression1(createExpressionIfPossible({"x", "&", "y"}));
    Expression const expressionToTest(createExpressionIfPossible({"x", "|", subExpression1}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithCombininingTermsByCheckingTheCommonFactorUsingPattern4) {
    Expression const subExpression1(createExpressionIfPossible({"x", "|", "y"}));
    Expression const expressionToTest(createExpressionIfPossible({"x", "&", subExpression1}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression const expressionToVerify(simplification.getExpression());
    Expression const expressionToExpect(createAndWrapExpressionFromATerm("x"));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnConsensusTheoremPattern1) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const subExpression1(createExpressionIfPossible({"x", "&", "y"}));
    Expression const subExpression2(createExpressionIfPossible({"y", "&", "z"}));
    Expression const subExpression3(createExpressionIfPossible({"x'", "&", "z"}));
    Expression const expressionToTest(
        createExpressionIfPossible({subExpression1, "|", subExpression2, "|", subExpression3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string const stringToVerify(convertToString(simplification.getExpression()));
    string const stringToExpect("((x&y)|(x'&z))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnConsensusTheoremPattern2) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const subExpression1(createExpressionIfPossible({"x", "|", "y"}));
    Expression const subExpression2(createExpressionIfPossible({"y", "|", "z"}));
    Expression const subExpression3(createExpressionIfPossible({"x'", "|", "z"}));
    Expression const expressionToTest(
        createExpressionIfPossible({subExpression1, "&", subExpression2, "&", subExpression3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    string const stringToVerify(convertToString(simplification.getExpression()));
    string const stringToExpect("((x|y)&(x'|z))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyWithOuterOrAndInnerAndWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyWithOuterOrAndInnerAnd());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyWithOuterOrAndInnerAnd = true;
        SimplificationOfExpression::ScopeObject const scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyWithOuterOrAndInnerAnd());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyWithOuterOrAndInnerAnd());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyWithOuterAndAndInnerOrWorks) {
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyWithOuterAndAndInnerOr());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyWithOuterAndAndInnerOr = true;
        SimplificationOfExpression::ScopeObject const scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyWithOuterAndAndInnerOr());
    }
    EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyWithOuterAndAndInnerOr());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyByQuineMcKluskeyWorks) {
    EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyByQuineMcKluskey());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
            SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyByQuineMcKluskey = false;
        SimplificationOfExpression::ScopeObject const scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_FALSE(SimplificationOfExpression::shouldSimplifyByQuineMcKluskey());
    }
    EXPECT_TRUE(SimplificationOfExpression::shouldSimplifyByQuineMcKluskey());
}

}  // namespace alba::booleanAlgebra::Simplification
