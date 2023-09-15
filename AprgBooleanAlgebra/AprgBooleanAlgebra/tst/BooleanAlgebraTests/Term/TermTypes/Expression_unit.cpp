#include <BooleanAlgebra/Term/TermTypes/Expression.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::booleanAlgebra {

TEST(ExpressionTest, EqualityOperatorWorks) {
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&", "x"})}));
    Expression const expression3(createExpressionIfPossible({false, "&", "x"}));
    Expression const expression4(createOrCopyExpressionFromATerm(true));
    Expression const expression5(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&"})}));
    Expression const expression6(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&", "x"})}));

    EXPECT_TRUE(expression1 == expression1);
    EXPECT_FALSE(expression1 == expression2);
    EXPECT_TRUE(expression2 == expression2);
    EXPECT_FALSE(expression2 == expression3);
    EXPECT_FALSE(expression2 == expression4);
    EXPECT_FALSE(expression2 == expression5);
    EXPECT_TRUE(expression2 == expression6);
}

TEST(ExpressionTest, InequalityOperatorWorks) {
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&", "x"})}));
    Expression const expression3(createExpressionIfPossible({false, "&", "x"}));
    Expression const expression4(createOrCopyExpressionFromATerm(true));
    Expression const expression5(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&"})}));
    Expression const expression6(createExpressionIfPossible({true, "&", createExpressionIfPossible({true, "&", "x"})}));

    EXPECT_FALSE(expression1 != expression1);
    EXPECT_TRUE(expression1 != expression2);
    EXPECT_FALSE(expression2 != expression2);
    EXPECT_TRUE(expression2 != expression3);
    EXPECT_TRUE(expression2 != expression4);
    EXPECT_TRUE(expression2 != expression5);
    EXPECT_FALSE(expression2 != expression6);
}

TEST(ExpressionTest, LessThanOperatorWorks) {
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({true, "&", "x"}));
    Expression const expression3(createOrCopyExpressionFromATerm(true));
    Expression const expression4(createExpressionIfPossible({true, "&", "x", "&", "y"}));
    Expression const expression5(createExpressionIfPossible({false, "&", "x"}));

    EXPECT_FALSE(expression1 < expression1);
    EXPECT_FALSE(expression2 < expression2);
    EXPECT_FALSE(expression2 < expression3);
    EXPECT_TRUE(expression2 < expression4);
    EXPECT_FALSE(expression2 < expression5);
}

TEST(ExpressionTest, NotOperationWorks) {
    Expression const expressionToTest(createExpressionIfPossible({"x", "&", "x'", "&", "y", "&", "z"}));
    Expression const expressionToExpect(createExpressionIfPossible({"x'", "|", "x", "|", "y'", "|", "z'"}));

    EXPECT_EQ(expressionToExpect, ~expressionToTest);
}

TEST(ExpressionTest, GetFirstTermConstReferenceWorks) {
    Expression const expression1(createOrCopyExpressionFromATerm(true));
    Expression const expression2(createExpressionIfPossible({true, "&", "x"}));
    Expression const expression3(createExpressionIfPossible({"~", false}));

    EXPECT_EQ(Term(true), getTermConstReferenceFromBaseTerm(expression1.getFirstTermConstReference()));
    EXPECT_EQ(Term("x"), getTermConstReferenceFromBaseTerm(expression2.getFirstTermConstReference()));
    EXPECT_EQ(Term(true), getTermConstReferenceFromBaseTerm(expression3.getFirstTermConstReference()));
}

TEST(ExpressionTest, ClearAllInnerSimplifiedFlagsWorks) {
    Term innerTerm;
    innerTerm.setAsSimplified();
    Expression expression(innerTerm);
    expression.setAsSimplified();
    EXPECT_TRUE(expression.isSimplified());
    EXPECT_TRUE(getTermConstReferenceFromBaseTerm(expression.getFirstTermConstReference()).isSimplified());

    expression.clearAllInnerSimplifiedFlags();

    EXPECT_FALSE(expression.isSimplified());
    EXPECT_FALSE(getTermConstReferenceFromBaseTerm(expression.getFirstTermConstReference()).isSimplified());
}

TEST(ExpressionTest, GetCommonOperatorTypeWorks) {
    Expression const expression1;
    Expression const expression2(createOrCopyExpressionFromATerm(true));
    Expression const expression3(createExpressionIfPossible({"x", "&", "y"}));
    Expression const expression4(createExpressionIfPossible({"x", "|", "y"}));

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::And, expression3.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::Or, expression4.getCommonOperatorLevel());
}

TEST(ExpressionTest, ConstructionWorks) {
    WrappedTerm const wrappedTerm1(Term(false));
    WrappedTerm const wrappedTerm2(Term(true));
    Expression const expression1;
    Expression const expression2(Term(false));
    Expression const expression3(OperatorLevel::And, {});
    Expression const expression4(OperatorLevel::And, {wrappedTerm1, wrappedTerm2});

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify1(expression1.getWrappedTerms());
    ASSERT_TRUE(termsToVerify1.empty());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify2(expression2.getWrappedTerms());
    ASSERT_EQ(1U, termsToVerify2.size());
    EXPECT_EQ(Term(false), getTermConstReferenceFromUniquePointer(termsToVerify2[0].baseTermPointer));
    EXPECT_EQ(OperatorLevel::Unknown, expression3.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify3(expression3.getWrappedTerms());
    EXPECT_TRUE(termsToVerify3.empty());
    EXPECT_EQ(OperatorLevel::And, expression4.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify4(expression4.getWrappedTerms());
    ASSERT_EQ(2U, termsToVerify4.size());
    EXPECT_EQ(Term(false), getTermConstReferenceFromUniquePointer(termsToVerify4[0].baseTermPointer));
    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(termsToVerify4[1].baseTermPointer));
}

TEST(ExpressionTest, SetCommonOperatorLevelWorks) {
    Expression expression1;
    Expression expression2;
    Expression expression3;

    expression1.setCommonOperatorLevel(OperatorLevel::Unknown);
    expression2.setCommonOperatorLevel(OperatorLevel::And);
    expression3.setCommonOperatorLevel(OperatorLevel::Or);

    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::And, expression2.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::Or, expression3.getCommonOperatorLevel());
}

TEST(ExpressionTest, SetCommonOperatorTypeIfStillUnknownWorks) {
    Expression expression1;
    Expression expression2;
    expression1.setCommonOperatorLevel(OperatorLevel::Unknown);
    expression2.setCommonOperatorLevel(OperatorLevel::And);

    expression1.setCommonOperatorLevelIfStillUnknown(OperatorLevel::Or);
    expression2.setCommonOperatorLevelIfStillUnknown(OperatorLevel::Or);

    EXPECT_EQ(OperatorLevel::Or, expression1.getCommonOperatorLevel());
    EXPECT_EQ(OperatorLevel::And, expression2.getCommonOperatorLevel());
}

TEST(ExpressionTest, GetWrappedTermsWorks) {
    Expression const expression(createExpressionIfPossible({true, "&", "x", "|", "y"}));

    WrappedTerms const& wrappedTermsToVerify(expression.getWrappedTerms());

    ASSERT_EQ(2U, wrappedTermsToVerify.size());
    EXPECT_EQ(Term("x"), getTermConstReferenceFromUniquePointer(wrappedTermsToVerify[0].baseTermPointer));
    EXPECT_EQ(Term("y"), getTermConstReferenceFromUniquePointer(wrappedTermsToVerify[1].baseTermPointer));
}

TEST(ExpressionTest, PutTermWorks) {
    Expression expressionToTest;

    expressionToTest.putTerm(Term("a"));
    expressionToTest.putTerm(Term("b"));
    expressionToTest.putTerm(Term("c"));
    expressionToTest.putTerm(Term("d"));

    WrappedTerms termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(4U, termsToVerify.size());
    EXPECT_EQ(Term("a"), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(Term("b"), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(Term("c"), getTermConstReferenceFromUniquePointer(termsToVerify[2].baseTermPointer));
    EXPECT_EQ(Term("d"), getTermConstReferenceFromUniquePointer(termsToVerify[3].baseTermPointer));
}

TEST(ExpressionTest, PutWrappedTermWorks) {
    Expression expressionToTest;
    WrappedTerm const wrappedTerm1(Term(true));
    WrappedTerm const wrappedTerm2(Term(false));
    WrappedTerm const wrappedTerm3(Term(true));

    expressionToTest.putWrappedTerm(wrappedTerm1);
    expressionToTest.putWrappedTerm(wrappedTerm2);
    expressionToTest.putWrappedTerm(wrappedTerm3);

    WrappedTerms termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(Term(false), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(termsToVerify[2].baseTermPointer));
}

TEST(ExpressionTest, PutWrappedTermsWorks) {
    Expression expressionToTest;
    WrappedTerms wrappedTerms;
    wrappedTerms.emplace_back(Term(true));
    wrappedTerms.emplace_back(Term(false));
    wrappedTerms.emplace_back(Term(true));

    expressionToTest.putWrappedTerms(wrappedTerms);

    WrappedTerms termsToVerify(expressionToTest.getWrappedTerms());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(Term(false), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(termsToVerify[2].baseTermPointer));
}

TEST(ExpressionTest, GetDebugStringWorks) {
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({true, "&", "x", "|", "y"}));
    Expression expression3;
    expression3.putTermWithAndOperationIfNeeded(Term(true));
    Expression const expression4(createExpressionIfPossible({expression2, "&", "z"}));

    EXPECT_EQ("( {?}|| )", expression1.getDebugString());
    EXPECT_EQ("( {|}|||x{VariableTerm}|y{VariableTerm} )", expression2.getDebugString());
    EXPECT_EQ("( {?}||[true]{Constant} )", expression3.getDebugString());
    EXPECT_EQ(
        "( {&}||&( {|}|||x{VariableTerm}|y{VariableTerm} ){Expression}&z{VariableTerm} )",
        expression4.getDebugString());
}

TEST(ExpressionTest, IsEmptyWorks) {
    Expression const expression1;
    Expression const expression2(createOrCopyExpressionFromATerm(false));
    Expression const expression3(createExpressionIfPossible({true, "&", "x"}));

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_FALSE(expression2.isEmpty());
    EXPECT_FALSE(expression3.isEmpty());
}

TEST(ExpressionTest, ClearWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({"x", "&", "y", "|", "z"}));

    expression1.clear();
    expression2.clear();

    EXPECT_TRUE(expression1.isEmpty());
    EXPECT_TRUE(expression2.isEmpty());
}

TEST(ExpressionTest, ExpressionThatIsDefaultConstructedHasIsSimplifiedFlagNotSet) {
    Expression const expression;

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, ExpressionThatIsConstructedWithWrappedTermsHasIsSimplifiedFlagNotSet) {
    WrappedTerm const wrappedTerm1(Term(true));
    WrappedTerm const wrappedTerm2(Term(false));
    Expression const expression(OperatorLevel::And, {wrappedTerm1, wrappedTerm2});

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, ExpressionThatIsCopyConstructedHasIsSimplifiedFlagCopied) {
    Expression const expressionWithSimplifiedNotSet;
    Expression expressionWithSimplifiedSet;
    expressionWithSimplifiedSet.setAsSimplified();

    Expression const& expression1(expressionWithSimplifiedNotSet);
    Expression const expression2(expressionWithSimplifiedSet);

    EXPECT_FALSE(expression1.isSimplified());
    EXPECT_TRUE(expression2.isSimplified());
}

TEST(ExpressionTest, IsSimplifiedWorks) {
    Expression const expression1;
    Expression expression2;
    expression2.setAsSimplified();

    EXPECT_FALSE(expression1.isSimplified());
    EXPECT_TRUE(expression2.isSimplified());
}

TEST(ExpressionTest, SetAsSimplifiedWorks) {
    Expression expression;

    expression.setAsSimplified();

    EXPECT_TRUE(expression.isSimplified());
}

TEST(ExpressionTest, ClearSimplifiedFlagWorks) {
    Expression expression;
    expression.setAsSimplified();

    expression.clearSimplifiedFlag();

    EXPECT_FALSE(expression.isSimplified());
}

TEST(ExpressionTest, ContainsOnlyOneTermWorks) {
    Expression const expression1;
    Expression const expression2(createOrCopyExpressionFromATerm(false));
    Expression const expression3(createExpressionIfPossible({"~", "x"}));
    Expression const expression4(createExpressionIfPossible({"x", "&", "y"}));

    EXPECT_FALSE(expression1.containsOnlyOneTerm());
    EXPECT_TRUE(expression2.containsOnlyOneTerm());
    EXPECT_TRUE(expression3.containsOnlyOneTerm());
    EXPECT_FALSE(expression4.containsOnlyOneTerm());
}

TEST(ExpressionTest, ClearAndPutTermInWrappedTermsWorks) {
    Expression expression1;
    Expression expression2(createExpressionIfPossible({true, "&", "x", "|", "y"}));

    expression1.clearAndPutTermInWrappedTerms(Term(true));
    expression2.clearAndPutTermInWrappedTerms(Term(true));

    EXPECT_EQ(createOrCopyExpressionFromATerm(true), expression1);
    EXPECT_EQ(createOrCopyExpressionFromATerm(true), expression2);
}

TEST(ExpressionTest, PutTermWithOperationLevelWorks) {
    Expression expressionToTest;

    expressionToTest.putTerm(Term("a"), OperatorLevel::And);
    expressionToTest.putTerm(Term("b"), OperatorLevel::Or);
    expressionToTest.putTerm(Term("c"), OperatorLevel::And);
    expressionToTest.putTerm(Term("d"), OperatorLevel::Or);

    EXPECT_EQ("(((a|b)&c)|d)", convertToString(expressionToTest));
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingNullExpressionWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression const nullExpression;
    expression1.putTermWithAndOperationIfNeeded(Term(nullExpression));
    expression2.putTermWithAndOperationIfNeeded(Term(nullExpression));
    expression3.putTermWithAndOperationIfNeeded(Term(nullExpression));
    expression4.putTermWithAndOperationIfNeeded(Term(nullExpression));
    expression5.putTermWithAndOperationIfNeeded(Term(nullExpression));

    Expression const expressionToExpect1(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect4(createExpressionIfPossible({"x"}));
    Expression const expressionToExpect5(createExpressionIfPossible({"x"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingTermWithNoEffectWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Term const noEffectTerm(true);
    expression1.putTermWithAndOperationIfNeeded(noEffectTerm);
    expression2.putTermWithAndOperationIfNeeded(noEffectTerm);
    expression3.putTermWithAndOperationIfNeeded(noEffectTerm);
    expression4.putTermWithAndOperationIfNeeded(noEffectTerm);
    expression5.putTermWithAndOperationIfNeeded(noEffectTerm);

    Expression const expressionToExpect1(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect3(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect4(createExpressionIfPossible({"x"}));
    Expression const expressionToExpect5(createExpressionIfPossible({"x"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression2);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingShortCircuitValueWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Term const shortCircuitValue(false);
    expression1.putTermWithAndOperationIfNeeded(shortCircuitValue);
    expression2.putTermWithAndOperationIfNeeded(shortCircuitValue);
    expression3.putTermWithAndOperationIfNeeded(shortCircuitValue);
    expression4.putTermWithAndOperationIfNeeded(shortCircuitValue);
    expression5.putTermWithAndOperationIfNeeded(shortCircuitValue);

    Expression const expressionToExpect1(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect3(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect4(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect5(createOrCopyExpressionFromATerm(false));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingExpressionWithSameOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression const expressionToApply(createExpressionIfPossible({"x", "&", "y"}));
    expression1.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression2.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression3.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression4.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression5.putTermWithAndOperationIfNeeded(Term(expressionToApply));

    Expression const expressionToExpect1(createExpressionIfPossible({"x", "&", "y"}));
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect3(createExpressionIfPossible({"x", "&", "y"}));
    Expression const expressionToExpect4(createExpressionIfPossible({"x", "&", "x", "&", "y"}));
    Expression const expressionToExpect5(createExpressionIfPossible({"x", "&", "x", "&", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithAndOperationIfNeededUsingExpressionWithDifferentOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression const expressionToApply(createExpressionIfPossible({"x", "|", "y"}));
    expression1.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression2.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression3.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression4.putTermWithAndOperationIfNeeded(Term(expressionToApply));
    expression5.putTermWithAndOperationIfNeeded(Term(expressionToApply));

    Expression const expressionToExpect1(createExpressionIfPossible({"x", "|", "y"}));
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect3(createExpressionIfPossible({"x", "|", "y"}));
    Expression const expressionToExpect4(createExpressionIfPossible({"x", "&", expressionToApply}));
    Expression const expressionToExpect5(createExpressionIfPossible({"x", "&", expressionToApply}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, OutputStreamOperatorWorks) {
    stringstream ss;
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({true, "&", "x", "|", "y"}));
    Expression expression3;
    expression3.putTermWithAndOperationIfNeeded(Term(true));
    Expression const expression4(createExpressionIfPossible({expression2, "&", "z"}));

    ss << expression1 << "," << expression2 << "," << expression3 << "," << expression4;

    EXPECT_EQ("(),(x|y),([true]),((x|y)&z)", ss.str());
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingNullExpressionWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression const nullExpression;
    expression1.putTermWithOrOperationIfNeeded(Term(nullExpression));
    expression2.putTermWithOrOperationIfNeeded(Term(nullExpression));
    expression3.putTermWithOrOperationIfNeeded(Term(nullExpression));
    expression4.putTermWithOrOperationIfNeeded(Term(nullExpression));
    expression5.putTermWithOrOperationIfNeeded(Term(nullExpression));

    Expression const expressionToExpect1(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect4(createExpressionIfPossible({"x"}));
    Expression const expressionToExpect5(createExpressionIfPossible({"x"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingTermWithNoEffectWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Term const noEffectTerm(false);
    expression1.putTermWithOrOperationIfNeeded(noEffectTerm);
    expression2.putTermWithOrOperationIfNeeded(noEffectTerm);
    expression3.putTermWithOrOperationIfNeeded(noEffectTerm);
    expression4.putTermWithOrOperationIfNeeded(noEffectTerm);
    expression5.putTermWithOrOperationIfNeeded(noEffectTerm);

    Expression const expressionToExpect1(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(false));
    Expression const expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect4(createExpressionIfPossible({"x"}));
    Expression const expressionToExpect5(createExpressionIfPossible({"x"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingShortCircuitValueWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Term const shortCircuitValue(true);
    expression1.putTermWithOrOperationIfNeeded(shortCircuitValue);
    expression2.putTermWithOrOperationIfNeeded(shortCircuitValue);
    expression3.putTermWithOrOperationIfNeeded(shortCircuitValue);
    expression4.putTermWithOrOperationIfNeeded(shortCircuitValue);
    expression5.putTermWithOrOperationIfNeeded(shortCircuitValue);

    Expression const expressionToExpect1(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect4(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect5(createOrCopyExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingExpressionWithSameOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression const expressionToApply(createExpressionIfPossible({"x", "|", "y"}));
    expression1.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression2.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression3.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression4.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression5.putTermWithOrOperationIfNeeded(Term(expressionToApply));

    Expression const expressionToExpect1(createExpressionIfPossible({"x", "|", "y"}));
    Expression const expressionToExpect2(createExpressionIfPossible({"x", "|", "y"}));
    Expression const expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect4(createExpressionIfPossible({"x", "|", "x", "|", "y"}));
    Expression const expressionToExpect5(createExpressionIfPossible({"x", "|", "x", "|", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, PutTermWithOrOperationIfNeededUsingExpressionWithDifferentOperationLevelWorks) {
    Expression expression1;
    Expression expression2(createOrCopyExpressionFromATerm(false));
    Expression expression3(createExpressionIfPossible({"~", false}));
    Expression expression4(createExpressionIfPossible({true, "&", "x"}));
    Expression expression5(createExpressionIfPossible({false, "|", "x"}));

    Expression const expressionToApply(createExpressionIfPossible({"x", "&", "y"}));
    expression1.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression2.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression3.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression4.putTermWithOrOperationIfNeeded(Term(expressionToApply));
    expression5.putTermWithOrOperationIfNeeded(Term(expressionToApply));

    Expression const expressionToExpect1(createExpressionIfPossible({"x", "&", "y"}));
    Expression const expressionToExpect2(createExpressionIfPossible({"x", "&", "y"}));
    Expression const expressionToExpect3(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect4(createExpressionIfPossible({"x", "|", "x", "&", "y"}));
    Expression const expressionToExpect5(createExpressionIfPossible({"x", "|", "x", "&", "y"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
    EXPECT_EQ(expressionToExpect4, expression4);
    EXPECT_EQ(expressionToExpect5, expression5);
}

TEST(ExpressionTest, SetWorks) {
    Expression expression;
    WrappedTerms const wrappedTerms{Term(true), Term(false)};

    expression.set(OperatorLevel::And, wrappedTerms);

    EXPECT_EQ("([true]&[false])", convertToString(expression));
}

TEST(ExpressionTest, SetTermWorks) {
    Expression expression1(createExpressionIfPossible({true, "&", "x"}));
    Expression expression2(createExpressionIfPossible({true, "&", "x"}));
    Expression expression3(createExpressionIfPossible({true, "&", "x"}));

    expression1.setTerm(Term());
    expression2.setTerm(Term(true));
    expression3.setTerm(Term(createExpressionIfPossible({false, "|", "energy"})));

    Expression const expressionToExpect1;
    Expression const expressionToExpect2(createOrCopyExpressionFromATerm(true));
    Expression const expressionToExpect3(createExpressionIfPossible({"energy"}));
    EXPECT_EQ(expressionToExpect1, expression1);
    EXPECT_EQ(expressionToExpect2, expression2);
    EXPECT_EQ(expressionToExpect3, expression3);
}

TEST(ExpressionTest, SimplifyWorks) {
    Expression expressionToTest(createExpressionIfPossible({true, "&", true, "|", true}));

    expressionToTest.simplify();

    Expression const expressionToExpect(createOrCopyExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SimplifyWorksWhenIsSimplifiedIsNotSet) {
    Expression expressionToTest(createExpressionIfPossible({true, "&", true, "|", true}));

    expressionToTest.simplify();

    Expression const expressionToExpect(createOrCopyExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SimplifyWorksAsSkippedWhenIsSimplifiedIsSet) {
    Expression expressionToTest(createExpressionIfPossible({true, "&", true, "|", true}));
    expressionToTest.setAsSimplified();

    expressionToTest.simplify();

    Expression const expressionToExpect(createOrCopyExpressionFromATerm(true));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(ExpressionTest, SortWorks) {
    Expression expression(createExpressionIfPossible({"x", "&", "x'", "&", "y", "&", "z"}));

    expression.sort();

    Expression const expressionToExpect(createExpressionIfPossible({"x", "&", "x'", "&", "y", "&", "z"}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, NegateWorks) {
    Expression expression(createExpressionIfPossible({"x", "&", "x'", "&", "y", "&", "z"}));

    expression.negate();

    Expression const expressionToExpect(createExpressionIfPossible({"x'", "|", "x", "|", "y'", "|", "z'"}));
    EXPECT_EQ(expressionToExpect, expression);
}

TEST(ExpressionTest, GetWrappedTermsReferenceWorks) {
    Expression expressionToTest(createExpressionIfPossible({"x", "&", "y"}));

    WrappedTerms& wrappedTerms(expressionToTest.getWrappedTermsReference());
    wrappedTerms.emplace_back(Term("a"));
    wrappedTerms.emplace_back(Term("b"));

    Expression const expressionToExpect(createExpressionIfPossible({"x", "&", "y", "&", "a", "&", "b"}));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

}  // namespace alba::booleanAlgebra
