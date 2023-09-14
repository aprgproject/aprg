#include <Algebra/Integration/IntegrationUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(IntegrationUtilitiesTest, GetInputForAverageValueInBetweenTwoValuesWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    AlbaNumbers numbersToVerify1(getInputForAverageValueInBetweenTwoValues(termToTest1, "x", 5, 10));
    AlbaNumbers numbersToVerify2(getInputForAverageValueInBetweenTwoValues(termToTest2, "x", 5, 10));
    AlbaNumbers numbersToVerify3(getInputForAverageValueInBetweenTwoValues(termToTest3, "x", 5, 10));

    ASSERT_EQ(1U, numbersToVerify1.size());
    EXPECT_EQ(AlbaNumber::createFraction(15, 2), numbersToVerify1[0]);
    ASSERT_EQ(1U, numbersToVerify2.size());
    EXPECT_EQ(AlbaNumber(7.637626158259732), numbersToVerify2[0]);
    ASSERT_EQ(1U, numbersToVerify3.size());
    EXPECT_EQ(AlbaNumber(7.76808126488466), numbersToVerify3[0]);
}

TEST(IntegrationUtilitiesTest, GetApproximateValuesForDefiniteIntegralWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    LowerAndHigherValues const valuesToVerify1(getApproximateValuesForDefiniteIntegral(termToTest1, "x", 5, 10));
    LowerAndHigherValues const valuesToVerify2(getApproximateValuesForDefiniteIntegral(termToTest2, "x", 5, 10));
    LowerAndHigherValues const valuesToVerify3(getApproximateValuesForDefiniteIntegral(termToTest3, "x", 5, 10));

    EXPECT_EQ(AlbaNumber(25), valuesToVerify1.lowerValue);
    EXPECT_EQ(AlbaNumber(50), valuesToVerify1.higherValue);
    EXPECT_EQ(AlbaNumber(0), valuesToVerify2.lowerValue);
    EXPECT_EQ(AlbaNumber(500), valuesToVerify2.higherValue);
    EXPECT_EQ(AlbaNumber(0), valuesToVerify3.lowerValue);
    EXPECT_EQ(AlbaNumber(5000), valuesToVerify3.higherValue);
}

TEST(IntegrationUtilitiesTest, GetAverageValueInBetweenTwoValuesWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_EQ(Term(AlbaNumber::createFraction(15, 2)), getAverageValueInBetweenTwoValues(termToTest1, {"x", 5, 10}));
    EXPECT_EQ(Term(AlbaNumber::createFraction(175, 3)), getAverageValueInBetweenTwoValues(termToTest2, {"x", 5, 10}));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1875, 4)), getAverageValueInBetweenTwoValues(termToTest3, {"x", 5, 10}));
}

TEST(IntegrationUtilitiesTest, EvaluateValuesAndGetDifferenceWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_EQ(Term(5), evaluateValuesAndGetDifference(termToTest1, "x", 5, 10));
    EXPECT_EQ(Term(75), evaluateValuesAndGetDifference(termToTest2, "x", 5, 10));
    EXPECT_EQ(Term(875), evaluateValuesAndGetDifference(termToTest3, "x", 5, 10));
}

TEST(IntegrationUtilitiesTest, EvaluateTermsAndGetDifferenceWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    Term const termToVerify1(evaluateTermsAndGetDifference(termToTest1, "x", "a", "b"));
    Term const termToVerify2(evaluateTermsAndGetDifference(termToTest2, "x", "a", "b"));
    Term const termToVerify3(evaluateTermsAndGetDifference(termToTest3, "x", "a", "b"));

    Term const termToExpect1(Polynomial{Monomial(-1, {{"a", 1}}), Monomial(1, {{"b", 1}})});
    Term const termToExpect2(Polynomial{Monomial(-1, {{"a", 2}}), Monomial(1, {{"b", 2}})});
    Term const termToExpect3(Polynomial{Monomial(-1, {{"a", 3}}), Monomial(1, {{"b", 3}})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(IntegrationUtilitiesTest, GetAreaUnderACurveUsingReimannSumsWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_EQ(Term(AlbaNumber::createFraction(75, 2)), getAreaUnderACurveUsingReimannSums(termToTest1, "x", 5, 10));
    EXPECT_EQ(Term(AlbaNumber::createFraction(875, 3)), getAreaUnderACurveUsingReimannSums(termToTest2, "x", 5, 10));
    EXPECT_EQ(Term(AlbaNumber::createFraction(9375, 4)), getAreaUnderACurveUsingReimannSums(termToTest3, "x", 5, 10));
}

TEST(IntegrationUtilitiesTest, IsTheSecondFundamentalTheoremOfCalculusTrueWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_TRUE(isTheSecondFundamentalTheoremOfCalculusTrue(termToTest1, "x", 5, 10));
    EXPECT_TRUE(isTheSecondFundamentalTheoremOfCalculusTrue(termToTest2, "x", 5, 10));
    EXPECT_TRUE(isTheSecondFundamentalTheoremOfCalculusTrue(termToTest3, "x", 5, 10));
}

TEST(IntegrationUtilitiesTest, IsTheIntegralDefinitionForFiniteCalculusIsTrueWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_TRUE(isTheIntegralDefinitionForFiniteCalculusIsTrue(termToTest1, "x", 5, 10));
    EXPECT_TRUE(isTheIntegralDefinitionForFiniteCalculusIsTrue(termToTest2, "x", 5, 10));
    EXPECT_TRUE(isTheIntegralDefinitionForFiniteCalculusIsTrue(termToTest3, "x", 5, 10));
}

TEST(IntegrationUtilitiesTest, IsAreaUnderTheCurveEqualToDefiniteIntegralWorks) {
    Term const termToTest1(Monomial(1, {{"x", 1}}));
    Term const termToTest2(Monomial(1, {{"x", 2}}));
    Term const termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_TRUE(isAreaUnderTheCurveEqualToDefiniteIntegral(termToTest1, "x", 5, 10));
    EXPECT_TRUE(isAreaUnderTheCurveEqualToDefiniteIntegral(termToTest2, "x", 5, 10));
    EXPECT_TRUE(isAreaUnderTheCurveEqualToDefiniteIntegral(termToTest3, "x", 5, 10));
}

}  // namespace alba::algebra
