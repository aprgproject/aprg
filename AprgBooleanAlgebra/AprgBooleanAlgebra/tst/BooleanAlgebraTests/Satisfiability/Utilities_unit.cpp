#include <BooleanAlgebra/Satisfiability/Utilities.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::booleanAlgebra {

TEST(SatisfiabilityUtilitiesTest, GetSatisfiabilityTermsWorksWithTerm) {
    Term const term1(true);
    Term const term2("x");
    Expression const subExpression1(createExpressionIfPossible({"b", "|", "c"}));
    Expression const subExpression2(createExpressionIfPossible({"d", "|", "e", "|", "f"}));
    Term const term3(createExpressionIfPossible({"a", "&", subExpression1, "&", subExpression2}));

    SatisfiabilityTerms const satTermsToVerify1(getSatisfiabilityTerms(term1));
    SatisfiabilityTerms const satTermsToVerify2(getSatisfiabilityTerms(term2));
    SatisfiabilityTerms const satTermsToVerify3(getSatisfiabilityTerms(term3));

    SatisfiabilityTerms const satTermsToExpect1;
    SatisfiabilityTerms const satTermsToExpect2{{VariableTerm("x")}};
    SatisfiabilityTerms const satTermsToExpect3{
        {VariableTerm("a")},
        {VariableTerm("b"), VariableTerm("c")},
        {VariableTerm("d"), VariableTerm("e"), VariableTerm("f")}};
    EXPECT_EQ(satTermsToExpect1, satTermsToVerify1);
    EXPECT_EQ(satTermsToExpect2, satTermsToVerify2);
    EXPECT_EQ(satTermsToExpect3, satTermsToVerify3);
}

TEST(SatisfiabilityUtilitiesTest, GetSatisfiabilityTermsWorksWithExpression) {
    Expression const subExpression1(createExpressionIfPossible({"b", "|", "c"}));
    Expression const subExpression2(createExpressionIfPossible({"d", "|", "e", "|", "f"}));
    Expression const expressionToTest(createExpressionIfPossible({"a", "&", subExpression1, "&", subExpression2}));

    SatisfiabilityTerms const satTermsToVerify(getSatisfiabilityTerms(expressionToTest));

    SatisfiabilityTerms const satTermsToExpect{
        {VariableTerm("a")},
        {VariableTerm("b"), VariableTerm("c")},
        {VariableTerm("d"), VariableTerm("e"), VariableTerm("f")}};
    EXPECT_EQ(satTermsToExpect, satTermsToVerify);
}

TEST(
    SatisfiabilityUtilitiesTest,
    GetSatisfiabilityTermsWorksWithExpressionAndResultsAreEmptyWithConstantInAndExpression) {
    Expression const subExpression1(createExpressionIfPossible({"b", "|", "c"}));
    Expression const subExpression2(createExpressionIfPossible({"d", "|", "e", "|", "f"}));
    Expression const expressionToTest(OperatorLevel::And, {Term(true), Term(subExpression1), Term(subExpression2)});

    SatisfiabilityTerms const satTermsToVerify(getSatisfiabilityTerms(expressionToTest));

    EXPECT_TRUE(satTermsToVerify.empty());
}

TEST(
    SatisfiabilityUtilitiesTest,
    GetSatisfiabilityTermsWorksWithExpressionAndResultsAreEmptyWithConstantInOrExpression) {
    Expression const subExpression1(createExpressionIfPossible({"b", "|", "c"}));
    Expression const subExpression2(createExpressionIfPossible({true, "|", "e", "|", "f"}));
    Expression const expressionToTest(OperatorLevel::And, {Term("a"), Term(subExpression1), Term(subExpression2)});

    SatisfiabilityTerms const satTermsToVerify(getSatisfiabilityTerms(expressionToTest));

    EXPECT_TRUE(satTermsToVerify.empty());
}

TEST(SatisfiabilityUtilitiesTest, GetSatisfiabilityLevelWorks) {
    SatisfiabilityTerms const satTermsToTest{
        {VariableTerm("a")},
        {VariableTerm("b"), VariableTerm("c")},
        {VariableTerm("d"), VariableTerm("e"), VariableTerm("f")}};

    EXPECT_EQ(3, getSatisfiabilityLevel(satTermsToTest));
}

}  // namespace alba::booleanAlgebra
