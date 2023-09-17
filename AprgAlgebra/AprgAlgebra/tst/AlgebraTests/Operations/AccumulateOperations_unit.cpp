#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba::algebra {

TEST(AccumulateOperationsTest, AccumulateAndDoOperationOnTermDetailsWorks) {
    Term termToTest1(45);
    Term termToTest2(45);
    TermWithDetails const termWithDetails1(Term(25), TermAssociationType::Positive);
    TermWithDetails const termWithDetails2(Term(25), TermAssociationType::Negative);

    accumulateAndDoOperationOnTermDetails(termToTest1, OperatorLevel::AdditionAndSubtraction, termWithDetails1);
    accumulateAndDoOperationOnTermDetails(termToTest2, OperatorLevel::AdditionAndSubtraction, termWithDetails2);

    EXPECT_EQ(Term(70), termToTest1);
    EXPECT_EQ(Term(20), termToTest2);
}

TEST(AccumulateOperationsTest, AccumulateTermsForAdditionAndSubtractionWorks) {
    Term termToTest(0);
    Term const xToTheY(createExpressionIfPossible({"x", "^", "y"}));
    Term const term1(createExpressionIfPossible({11, "*", xToTheY}));
    Term const term2(createExpressionIfPossible({13, "*", xToTheY}));
    Term const term3(0);
    TermsWithDetails const termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Negative), TermWithDetails(term2, TermAssociationType::Positive),
        TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForAdditionAndSubtraction(termToTest, termsWithDetails);

    Term const termToExpectPart1(createExpressionIfPossible({-11, "*", xToTheY}));
    Term const termToExpectPart2(createExpressionIfPossible({13, "*", xToTheY}));
    Term const termToExpect(createExpressionIfPossible({termToExpectPart1, "+", termToExpectPart2}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForAdditionAndSubtractionWorksWithEmptyTermAtTheStart) {
    Term termToTest;
    Term const term1;
    Term const term2(0);
    TermsWithDetails const termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Positive), TermWithDetails(term2, TermAssociationType::Positive)};

    accumulateTermsForAdditionAndSubtraction(termToTest, termsWithDetails);

    EXPECT_EQ(Term(0), termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForAdditionAndSubtractionWorksWithNan) {
    Term termToTest;
    Term const term1(1);
    Term const term2(2);
    Term const term3(ALBA_NUMBER_NOT_A_NUMBER);
    TermsWithDetails const termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Positive), TermWithDetails(term2, TermAssociationType::Positive),
        TermWithDetails(term3, TermAssociationType::Positive)};

    accumulateTermsForAdditionAndSubtraction(termToTest, termsWithDetails);

    EXPECT_TRUE(isNan(termToTest));
}

TEST(AccumulateOperationsTest, AccumulateTermsForMultiplicationAndDivisionWorks) {
    Term termToTest(1);
    Term const xToTheY(createExpressionIfPossible({"x", "^", "y"}));
    Term const term1(createExpressionIfPossible({11, "*", xToTheY}));
    Term const term2(createExpressionIfPossible({13, "*", xToTheY}));
    Term const term3(1);
    TermsWithDetails const termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Negative), TermWithDetails(term2, TermAssociationType::Positive),
        TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForMultiplicationAndDivision(termToTest, termsWithDetails);

    Term const termToExpect(createExpressionIfPossible({1, "/", 11, "/", xToTheY, "*", 13, "*", xToTheY}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForMultiplicationAndDivisionWorksWithEmptyTermAtTheStart) {
    Term termToTest;
    Term const term1;
    Term const term2(1);
    TermsWithDetails const termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Positive), TermWithDetails(term2, TermAssociationType::Positive)};

    accumulateTermsForMultiplicationAndDivision(termToTest, termsWithDetails);

    EXPECT_EQ(Term(1), termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForRaiseToPowerWorks) {
    Term termToTest(1);
    Term const xToTheY(createExpressionIfPossible({"x", "^", "y"}));
    Term const term1(createExpressionIfPossible({11, "*", xToTheY}));
    Term const term2(createExpressionIfPossible({13, "*", xToTheY}));
    Term const term3(1);
    TermsWithDetails const termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Negative), TermWithDetails(term2, TermAssociationType::Positive),
        TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForRaiseToPower(termToTest, termsWithDetails);

    Term const termToExpectPart1(createExpressionIfPossible({11, "*", xToTheY}));
    Term const termToExpectPart2(createExpressionIfPossible({13, "*", xToTheY}));
    Term const termToExpect(createExpressionIfPossible({termToExpectPart1, "^", termToExpectPart2}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForRaiseToPowerWorksWithEmptyTermAtTheStart) {
    Term termToTest;
    Term const term1;
    Term const term2(1);
    TermsWithDetails const termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Positive), TermWithDetails(term2, TermAssociationType::Positive)};

    accumulateTermsForRaiseToPower(termToTest, termsWithDetails);

    EXPECT_EQ(Term(1), termToTest);
}

}  // namespace alba::algebra
