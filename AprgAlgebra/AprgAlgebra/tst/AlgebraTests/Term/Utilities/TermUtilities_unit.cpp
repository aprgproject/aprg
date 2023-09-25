#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;

namespace alba::algebra {

TEST(TermUtilitiesTest, GetConstantFactorWorks) {
    EXPECT_EQ(AlbaNumber(5), getConstantFactor(5));
    EXPECT_EQ(AlbaNumber(6), getConstantFactor(Monomial(6, {{"x", 7}})));
    EXPECT_EQ(AlbaNumber(4), getConstantFactor(Polynomial{Monomial(8, {{"x", 3}}), Monomial(12, {{"x", 4}})}));
    EXPECT_EQ(AlbaNumber(1), getConstantFactor("x"));
}

TEST(TermUtilitiesTest, EvaluateAndGetInputOutputPairWorks) {
    AlbaNumbers const inputNumbers{-2, -1, 0, 1, 2};

    AlbaNumberPairs inputAndOutputPairs(evaluateAndGetInputOutputPair(inputNumbers, "x", Monomial(-2, {{"x", 3}})));

    ASSERT_EQ(5U, inputAndOutputPairs.size());
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs[0].first);
    EXPECT_EQ(AlbaNumber(16), inputAndOutputPairs[0].second);
    EXPECT_EQ(AlbaNumber(-1), inputAndOutputPairs[1].first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs[1].second);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs[2].first);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs[2].second);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs[3].first);
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs[3].second);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs[4].first);
    EXPECT_EQ(AlbaNumber(-16), inputAndOutputPairs[4].second);
}

TEST(TermUtilitiesTest, NegateExpressionWorks) {
    Expression const expression1(createExpressionIfPossible({-5, "+", "x"}));
    Expression const expression2(createExpressionIfPossible({5, "+", "x"}));
    Expression const expression3(createExpressionIfPossible({-5, "*", "x"}));
    Expression const expression4(createExpressionIfPossible({-5, "*", -3}));
    Expression const expression5(createExpressionIfPossible({-5, "^", "x"}));

    Expression const expressionToVerify1(negateExpression(expression1));
    Expression const expressionToVerify2(negateExpression(expression2));
    Expression const expressionToVerify3(negateExpression(expression3));
    Expression const expressionToVerify4(negateExpression(expression4));
    Expression const expressionToVerify5(negateExpression(expression5));

    Expression const expectedExpression1(
        createExpressionIfPossible({Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}}));
    Expression const expectedExpression2(
        createExpressionIfPossible({Polynomial{Monomial(-1, {{"x", 1}}), Monomial(-5, {})}}));
    Expression const expectedExpression3(createExpressionIfPossible({Monomial(5, {{"x", 1}})}));
    Expression const expectedExpression4(createExpressionIfPossible({-15}));
    Expression const subExpression5(createExpressionIfPossible({-5, "^", "x"}));
    Expression const expectedExpression5(createExpressionIfPossible({-1, "*", subExpression5}));
    EXPECT_EQ(expectedExpression1, expressionToVerify1);
    EXPECT_EQ(expectedExpression2, expressionToVerify2);
    EXPECT_EQ(expectedExpression3, expressionToVerify3);
    EXPECT_EQ(expectedExpression4, expressionToVerify4);
    EXPECT_EQ(expectedExpression5, expressionToVerify5);
}

TEST(TermUtilitiesTest, GetPiAsTermWorks) { EXPECT_EQ(Term(ALBA_NUMBER_PI), getPiAsATerm()); }
TEST(TermUtilitiesTest, GetEAsTermWorks) { EXPECT_EQ(Term(ALBA_NUMBER_E), getEAsATerm()); }

TEST(TermUtilitiesTest, GetPositiveInfinityAsATermWorks) {
    EXPECT_EQ(Term(ALBA_NUMBER_POSITIVE_INFINITY), getPositiveInfinityAsATerm());
}

TEST(TermUtilitiesTest, GetNegativeInfinityAsATermWorks) {
    EXPECT_EQ(Term(ALBA_NUMBER_NEGATIVE_INFINITY), getNegativeInfinityAsATerm());
}

TEST(TermUtilitiesTest, ConvertPositiveTermIfNegativeWorks) {
    EXPECT_EQ(Term(5), convertPositiveTermIfNegative(-5));
    EXPECT_EQ(Term(5), convertPositiveTermIfNegative(5));
}

TEST(TermUtilitiesTest, NegateTermWorks) {
    Term const sinX(sin("x"));
    Term const sinY(sin("y"));
    Term const sinZ(sin("z"));
    Term const term1(createExpressionIfPossible({sinX, "+", sinY, "-", sinZ}));
    Term const term2(createExpressionIfPossible({sinX, "*", sinY, "/", sinZ}));
    Term const term3(createExpressionIfPossible({sinX, "^", sinY, "^", sinZ}));

    Term const termToVerify1(negateTerm(5));
    Term const termToVerify2(negateTerm("x"));
    Term const termToVerify3(negateTerm(term1));
    Term const termToVerify4(negateTerm(term2));
    Term const termToVerify5(negateTerm(term3));

    Term const termToExpect1(-5);
    Term const termToExpect2(Monomial(-1, {{"x", 1}}));
    Term const termToExpect3(createExpressionIfPossible({sinZ, "-", sinX, "-", sinY}));
    Term const termToExpect4(createExpressionIfPossible({-1, "*", sinX, "*", sinY, "/", sinZ}));
    Term const termToExpect5(createExpressionIfPossible({-1, "*", sinX, "^", "(", sinY, "*", sinZ, ")"}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(TermUtilitiesTest, FlipTermWorks) { EXPECT_EQ(Term(AlbaNumber::createFraction(1, 5)), flipTerm(5)); }

TEST(TermUtilitiesTest, NegateTermIfHasNegativeAssociationWorks) {
    EXPECT_EQ(Term(5), negateTermIfHasNegativeAssociation(TermWithDetails{Term(5), TermAssociationType::Positive}));
    EXPECT_EQ(Term(-5), negateTermIfHasNegativeAssociation(TermWithDetails{Term(5), TermAssociationType::Negative}));
}

TEST(TermUtilitiesTest, FlipTermIfHasNegativeAssociationWorks) {
    EXPECT_EQ(Term(5), flipTermIfHasNegativeAssociation(TermWithDetails{Term(5), TermAssociationType::Positive}));
    EXPECT_EQ(
        Term(AlbaNumber::createFraction(1, 5)),
        flipTermIfHasNegativeAssociation(TermWithDetails{Term(5), TermAssociationType::Negative}));
}

TEST(TermUtilitiesTest, InvertTermWorks) {
    Term const termToTest1(5);
    Term const termToTest2("x");
    Term const termToTest3(Monomial(1, {{"x", 4}}));
    Term const termToTest4(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {})});
    Term const termToTest5(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", AlbaNumber::createFraction(1, 2)}));

    Term const termToVerify1(invertTerm(termToTest1, "x"));
    Term const termToVerify2(invertTerm(termToTest2, "x"));
    Term const termToVerify3(invertTerm(termToTest3, "x"));
    Term const termToVerify4(invertTerm(termToTest4, "x"));
    Term const termToVerify5(invertTerm(termToTest5, "x"));

    Term const termToExpect1;
    Term const termToExpect2("x");
    Term const termToExpect3(Monomial(1, {{"x", AlbaNumber::createFraction(1, 4)}}));
    Term const termToExpect4(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", AlbaNumber::createFraction(1, 2)}));
    Term const termToExpect5(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(TermUtilitiesTest, GetNumberOfTermsWorks) {
    EXPECT_EQ(7, getNumberOfTerms(createExpressionIfPossible({"w", "+", "x", "*", "y", "^", "z"})));
}

TEST(TermUtilitiesTest, IsNegatedTermSimplerWorks) {
    Term const xToTheX(createExpressionIfPossible({"x", "^", "x"}));
    Term const negativeXToTheX(createExpressionIfPossible({-1, "*", "x", "^", "x"}));

    EXPECT_FALSE(isNegatedTermSimpler(xToTheX, negativeXToTheX));
    // NOLINTNEXTLINE(readability-suspicious-call-argument)
    EXPECT_TRUE(isNegatedTermSimpler(negativeXToTheX, xToTheX));
    EXPECT_FALSE(isNegatedTermSimpler(Monomial(5, {}), Monomial(-5, {})));
    EXPECT_TRUE(isNegatedTermSimpler(Monomial(-5, {}), Monomial(5, {})));
}

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorTypeWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(isNonEmptyOrNonOperatorType(term1));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term2));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term3));
    EXPECT_FALSE(isNonEmptyOrNonOperatorType(term4));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term5));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term6));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term7));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term8));
}

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorOrNonExpressionTypeWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term1));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term2));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term3));
    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term4));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term5));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term6));
    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term7));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term8));
}

TEST(TermUtilitiesTest, IsARadicalTermWorks) {
    Term const nonMonomialOrExpressionTerm("x");
    Term const monomialWithIntegerExponent(Monomial(1, {{"x", 34}}));
    Term const monomialWithDoubleExponent(Monomial(1, {{"x", 3.4}}));
    Term const nonRaiseToPowerExpressionTerm(createExpressionIfPossible({"x", "*", "x"}));
    Term const raiseToIntegerExpressionTerm(createExpressionIfPossible({"x", "^", 5}));
    Term const raiseToDoubleExpressionTerm(createExpressionIfPossible({"x", "^", 1.79}));
    Term const multipleRaiseToPowerExpressionTerm(createExpressionIfPossible({"x", "^", 1.79, "^", "y"}));
    Term const raiseToMonomialWithDoubleExpressionTerm(
        createExpressionIfPossible({"x", "^", Monomial(2.84, {{"x", 2}, {"y", 3}})}));

    EXPECT_FALSE(isARadicalTerm(nonMonomialOrExpressionTerm));
    EXPECT_FALSE(isARadicalTerm(monomialWithIntegerExponent));
    EXPECT_TRUE(isARadicalTerm(monomialWithDoubleExponent));
    EXPECT_FALSE(isARadicalTerm(nonRaiseToPowerExpressionTerm));
    EXPECT_FALSE(isARadicalTerm(raiseToIntegerExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(raiseToDoubleExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(multipleRaiseToPowerExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(raiseToMonomialWithDoubleExpressionTerm));
}

}  // namespace alba::algebra
