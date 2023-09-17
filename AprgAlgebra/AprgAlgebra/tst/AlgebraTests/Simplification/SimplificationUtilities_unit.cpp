#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra::Simplification {

TEST(SimplificationUtilitiesTest, SimplifyTermToACommonDenominatorWorks) {
    Term const denominator1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term const denominator2(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(3, {})});
    Term const firstTerm(createExpressionIfPossible({1, "/", denominator1}));
    Term const secondTerm(createExpressionIfPossible({1, "/", denominator2}));

    Term termToTest(createExpressionIfPossible({firstTerm, "+", secondTerm}));
    simplifyTermToACommonDenominator(termToTest);

    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-6, {})});
    Term const expectedTerm(createExpressionIfPossible({-5, "/", expectedDenominator}));
    EXPECT_EQ(expectedTerm, termToTest);
}

TEST(SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTerm) {
    TermsWithDetails inputTermWithDetails;
    inputTermWithDetails.emplace_back(Term(Monomial(5, {{}})), TermAssociationType::Positive);
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    TermsWithDetails outputTermsWithDetails;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputTermsWithDetails, operatorLevel, inputTermWithDetails);

    TermsWithDetails expectedTermsWithDetails;
    expectedTermsWithDetails.emplace_back(Term(5), TermAssociationType::Positive);
    EXPECT_EQ(expectedTermsWithDetails, outputTermsWithDetails);
}

TEST(
    SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTermWithManyExpressions) {
    Term const oneTerm(createExpressionInAnExpression(
        createExpressionInAnExpression(createAndWrapExpressionFromATerm(Monomial(5, {{}})))));
    TermsWithDetails inputTermWithDetails;
    inputTermWithDetails.emplace_back(oneTerm, TermAssociationType::Positive);
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    TermsWithDetails outputTermsWithDetails;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputTermsWithDetails, operatorLevel, inputTermWithDetails);

    TermsWithDetails expectedTermsWithDetails;
    expectedTermsWithDetails.emplace_back(Term(5), TermAssociationType::Positive);
    EXPECT_EQ(expectedTermsWithDetails, outputTermsWithDetails);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorks) {
    Expression expression(createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));

    bool const didItOccurOnTopLevelExpression =
        simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    Expression const expressionToExpect(createExpressionIfPossible(
        {Polynomial{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})}, "/",
         Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}}));
    EXPECT_EQ(expressionToExpect, expression);
    EXPECT_TRUE(didItOccurOnTopLevelExpression);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorksOnExponentPlusPolynomialDenominator) {
    Expression expression(createExpressionIfPossible(tokenizeToTerms("2^x+((1)/(x+2))")));

    bool const didItOccurOnTopLevelExpression =
        simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    string const stringToExpect("((1+(x*(2^x))+(2^(1[x] + 1)))/(1[x] + 2))");
    EXPECT_EQ(stringToExpect, convertToString(expression));
    EXPECT_TRUE(didItOccurOnTopLevelExpression);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorksOnExponentWithFractionExpressions) {
    Expression expression(createExpressionIfPossible(tokenizeToTerms("2^(((1)/(x+2))+((1)/(x-2)))")));

    bool const didItOccurOnTopLevelExpression =
        simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    Polynomial const polynomialToExpect{Monomial(1, {{"x", 2}}), Monomial(-4, {})};
    Expression const subExpression(createExpressionIfPossible({Monomial(2, {{"x", 1}}), "/", polynomialToExpect}));
    Expression const expressionToExpect(createExpressionIfPossible({2, "^", subExpression}));
    EXPECT_EQ(expressionToExpect, expression);
    EXPECT_FALSE(didItOccurOnTopLevelExpression);
}

}  // namespace alba::algebra::Simplification
