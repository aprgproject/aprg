#include <BooleanAlgebra/Operations/AccumulateOperations.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(AccumulateOperationsTest, AccumulateTermsWorks) {
    Term termToTest1;
    Term termToTest2;

    accumulateTerms(termToTest1, {"a", "b", "c", "d"}, OperatorLevel::And);
    accumulateTerms(termToTest2, {"a", "b", "c", "d"}, OperatorLevel::Or);

    Term const termToExpect1(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d"}));
    Term const termToExpect2(createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d"}));
    EXPECT_EQ(termToExpect1, termToTest1);
    EXPECT_EQ(termToExpect2, termToTest2);
}

TEST(AccumulateOperationsTest, AccumulateTermsWithAndOperationWorks) {
    Term termToTest(true);
    Term const term1(createExpressionIfPossible({"a", "&", "b"}));
    Term const term2(createExpressionIfPossible({"c", "&", "d"}));
    Term const term3(createExpressionIfPossible({"e", "&", "f"}));
    Term const term4(createExpressionIfPossible({"g", "&", "h"}));
    Terms const termsToCombine{term1, term2, term3, term4};

    accumulateTermsWithAndOperation(termToTest, termsToCombine);

    Term const termToExpect(
        createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d", "&", "e", "&", "f", "&", "g", "&", "h"}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsWithAndOperationWorksWithEmptyTermAtTheStart) {
    Term termToTest;
    Term const term1;
    Term const term2(true);
    Terms const termsToCombine{term1, term2};

    accumulateTermsWithAndOperation(termToTest, termsToCombine);

    EXPECT_EQ(Term(true), termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsWithOrOperationWorks) {
    Term termToTest(false);
    Term const term1(createExpressionIfPossible({"a", "|", "b"}));
    Term const term2(createExpressionIfPossible({"c", "|", "d"}));
    Term const term3(createExpressionIfPossible({"e", "|", "f"}));
    Term const term4(createExpressionIfPossible({"g", "|", "h"}));
    Terms const termsToCombine{term1, term2, term3, term4};

    accumulateTermsWithOrOperation(termToTest, termsToCombine);

    Term const termToExpect(
        createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d", "|", "e", "|", "f", "|", "g", "|", "h"}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsWithOrOperationWorksWithEmptyTermAtTheStart) {
    Term termToTest;
    Term const term1;
    Term const term2(false);
    Terms const termsToCombine{term1, term2};

    accumulateTermsWithOrOperation(termToTest, termsToCombine);

    EXPECT_EQ(Term(false), termToTest);
}

}  // namespace alba::booleanAlgebra
