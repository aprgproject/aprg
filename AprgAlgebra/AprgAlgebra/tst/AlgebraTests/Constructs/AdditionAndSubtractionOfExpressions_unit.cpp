#include <Algebra/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(AdditionAndSubtractionOfExpressionsTest, DefaultConstructionWorks) {
    AdditionAndSubtractionOfExpressions const additionAndSubtraction;

    EXPECT_TRUE(additionAndSubtraction.getExpressions().empty());
    EXPECT_TRUE(additionAndSubtraction.getAssociations().empty());
}

TEST(AdditionAndSubtractionOfExpressionsTest, TermsWithDetailsConstructionWorks) {
    Expression const expression1(createExpressionIfPossible({"x"}));
    Expression const expression2(createExpressionIfPossible({"y"}));
    TermWithDetails const termWithDetails1(Term(expression1), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(expression2), TermAssociationType::Positive);
    TermsWithDetails const termsWithDetails{termWithDetails1, termWithDetails2};
    AdditionAndSubtractionOfExpressions const additionAndSubtraction(termsWithDetails);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expression1, expressions[0]);
    EXPECT_EQ(expression2, expressions[1]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations[0]);
    EXPECT_EQ(TermAssociationType::Positive, associations[1]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsAdditionWorks) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression(createExpressionIfPossible({"x"}));

    additionAndSubtraction.putAsAddition(expression);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expression, expressions[0]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
}

TEST(
    AdditionAndSubtractionOfExpressionsTest,
    CombineExpressionIfPossibleWorksOnAddingAndSubtractingRaiseToPowerExpressions) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression1(createExpressionIfPossible({5, "*", "y", "^", "y"}));
    Expression const expression2(createExpressionIfPossible({"y", "^", "y"}));
    Expression const expression3(createExpressionIfPossible({3, "*", "y", "^", "y"}));
    additionAndSubtraction.putAsAddition(expression1);
    additionAndSubtraction.putAsAddition(expression2);
    additionAndSubtraction.putAsSubtraction(expression3);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression const subExpression(createExpressionIfPossible({"y", "^", "y"}));
    Expression const expressionToExpect(createExpressionIfPossible({3, "*", subExpression}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expressionToExpect, expressions[0]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
}

TEST(
    AdditionAndSubtractionOfExpressionsTest,
    CombineExpressionIfPossibleWorksOnAddingAndSubtractingMultipleRaiseToPowerExpressions) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression1(createExpressionIfPossible({"x", "^", "y"}));
    Expression const expression2(createExpressionIfPossible({2, "*", "y", "^", "y"}));
    Expression const expression3(createExpressionIfPossible({3, "*", "x", "^", "y"}));
    Expression const expression4(createExpressionIfPossible({"y", "^", "y"}));
    Expression const expression5(createExpressionIfPossible({4, "*", "x", "^", "y"}));
    Expression const expression6(createExpressionIfPossible({5, "*", "y", "^", "y"}));
    additionAndSubtraction.putAsAddition(expression1);
    additionAndSubtraction.putAsSubtraction(expression2);
    additionAndSubtraction.putAsSubtraction(expression3);
    additionAndSubtraction.putAsAddition(expression4);
    additionAndSubtraction.putAsAddition(expression5);
    additionAndSubtraction.putAsAddition(expression6);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression const subExpression1(createExpressionIfPossible({"x", "^", "y"}));
    Expression const subExpression2(createExpressionIfPossible({"y", "^", "y"}));
    Expression const expressionToExpect1(createExpressionIfPossible({2, "*", subExpression1}));
    Expression const expressionToExpect2(createExpressionIfPossible({4, "*", subExpression2}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expressionToExpect1, expressions[0]);
    EXPECT_EQ(expressionToExpect2, expressions[1]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
    EXPECT_EQ(TermAssociationType::Positive, associations[1]);
}

TEST(
    AdditionAndSubtractionOfExpressionsTest,
    CombineExpressionIfPossibleWorksOnAddingAndSubtractingNonSortedRaiseToPowerExpressions) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression1(createExpressionIfPossible({100, "*", "y", "^", "y", "*", "x", "^", "x"}));
    Expression const expression2(createExpressionIfPossible({10, "*", "x", "^", "x", "*", "y", "^", "y"}));
    additionAndSubtraction.putAsAddition(expression1);
    additionAndSubtraction.putAsSubtraction(expression2);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression const subExpression1(createExpressionIfPossible({"x", "^", "x"}));
    Expression const subExpression2(createExpressionIfPossible({"y", "^", "y"}));
    Expression const subExpression3(createExpressionIfPossible({subExpression1, "*", subExpression2}));
    Expression const expressionToExpect(createExpressionIfPossible({90, "*", subExpression3}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expressionToExpect, expressions[0]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
}

TEST(
    AdditionAndSubtractionOfExpressionsTest,
    CombineExpressionIfPossibleWorksOnAddingAndSubtractingRaiseToPowerExpressionsThatCannotBeAdded) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression1(createExpressionIfPossible({10, "*", "y", "^", "y"}));
    Expression const expression2(createExpressionIfPossible({"x", "*", "y", "^", "y"}));
    Expression const expression3(createExpressionIfPossible({8, "*", "y", "^", "y"}));
    Expression const expression4(createExpressionIfPossible({6, "*", "x", "*", "y", "^", "y"}));
    additionAndSubtraction.putAsAddition(expression1);
    additionAndSubtraction.putAsAddition(expression2);
    additionAndSubtraction.putAsSubtraction(expression3);
    additionAndSubtraction.putAsSubtraction(expression4);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression const subExpression1(createExpressionIfPossible({"y", "^", "y"}));
    Expression const expressionToExpect1(createExpressionIfPossible({2, "*", subExpression1}));
    Expression const expressionToExpect2(createExpressionIfPossible({Monomial(-5, {{"x", 1}}), "*", subExpression1}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expressionToExpect1, expressions[0]);
    EXPECT_EQ(expressionToExpect2, expressions[1]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
    EXPECT_EQ(TermAssociationType::Positive, associations[1]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksWithEToTheXWithTrigonometricExpressions) {
    Term const eToTheX(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    Term const eToTheXTimesSinX(createExpressionIfPossible({eToTheX, "*", sin("x")}));
    Term const eToTheXTimesCosX(createExpressionIfPossible({eToTheX, "*", cos("x")}));
    Term const eToTheXTimesSinXTimes2(createExpressionIfPossible({2, "*", eToTheXTimesSinX}));
    Term const eToTheXTimesCosXTimes2(createExpressionIfPossible({2, "*", eToTheXTimesCosX}));
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    additionAndSubtraction.putAsAddition(Expression(eToTheXTimesSinXTimes2));
    additionAndSubtraction.putAsSubtraction(Expression(eToTheXTimesCosXTimes2));
    additionAndSubtraction.putAsSubtraction(Expression(eToTheXTimesSinX));
    additionAndSubtraction.putAsAddition(Expression(eToTheXTimesCosX));

    additionAndSubtraction.combineExpressionsIfPossible();

    Term const negativeEToTheXTimesCosX(createExpressionIfPossible({-1, "*", eToTheXTimesCosX}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(eToTheXTimesSinX, expressions[0]);
    EXPECT_EQ(negativeEToTheXTimesCosX, expressions[1]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
    EXPECT_EQ(TermAssociationType::Positive, associations[1]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksWithSinLogarithmicExpressions) {
    Term const lnOfX(ln("x"));
    Term const sinOfLnOfX(sin(lnOfX));
    Term const cosOfLnOfX(cos(lnOfX));
    Term const twoX(Monomial(2, {{"x", 1}}));
    Term const twoXTimesSinOfLnOfX(createExpressionIfPossible({twoX, "*", sinOfLnOfX}));
    Term const twoXTimesCosOfLnOfX(createExpressionIfPossible({twoX, "*", cosOfLnOfX}));
    Term const xTimesSinOfLnOfX(createExpressionIfPossible({"x", "*", sinOfLnOfX}));
    Term const xTimesCosOfLnOfX(createExpressionIfPossible({"x", "*", cosOfLnOfX}));
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    additionAndSubtraction.putAsAddition(Expression(twoXTimesSinOfLnOfX));
    additionAndSubtraction.putAsSubtraction(Expression(twoXTimesCosOfLnOfX));
    additionAndSubtraction.putAsSubtraction(Expression(xTimesSinOfLnOfX));
    additionAndSubtraction.putAsAddition(Expression(xTimesCosOfLnOfX));

    additionAndSubtraction.combineExpressionsIfPossible();

    Term const negativeXTimesCosOfLnOfX(createExpressionIfPossible({Monomial(-1, {{"x", 1}}), "*", cosOfLnOfX}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(xTimesSinOfLnOfX, expressions[0]);
    EXPECT_EQ(negativeXTimesCosOfLnOfX, expressions[1]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
    EXPECT_EQ(TermAssociationType::Positive, associations[1]);
}

TEST(
    AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksAndSquareRootExpressionAreAddedCorrectly) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression const squareRootOfXPlusOne(
        createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    additionAndSubtraction.putAsAddition(squareRootOfXPlusOne);
    additionAndSubtraction.putAsAddition(squareRootOfXPlusOne);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression const expressionToExpect(createExpressionIfPossible({2, "*", squareRootOfXPlusOne}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expressionToExpect, expressions[0]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
}

TEST(
    AdditionAndSubtractionOfExpressionsTest,
    CombineExpressionIfPossibleWorksWithNegativeTermWithTrigonometricFunctions) {
    Expression const positiveCosX(createExpressionIfPossible({cos("x")}));
    Expression const negativeSinX(createExpressionIfPossible({-1, "*", sin("x")}));
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    additionAndSubtraction.putAsAddition(positiveCosX);
    additionAndSubtraction.putAsAddition(negativeSinX);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression const cosX(createExpressionIfPossible({cos("x")}));
    Expression const sinX(createExpressionIfPossible({sin("x")}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(cosX, expressions[0]);
    EXPECT_EQ(sinX, expressions[1]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
    EXPECT_EQ(TermAssociationType::Negative, associations[1]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsSubtractionWorks) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression(createExpressionIfPossible({"x"}));

    additionAndSubtraction.putAsSubtraction(expression);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expression, expressions[0]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations[0]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsAddOrSubtractionWorks) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression(createExpressionIfPossible({"x"}));

    additionAndSubtraction.putAsAddOrSubtraction(expression, TermAssociationType::Negative);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expression, expressions[0]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations[0]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutTermsWithDetailsWorks) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression1(createExpressionIfPossible({"x"}));
    Expression const expression2(createExpressionIfPossible({"y"}));
    TermWithDetails const termWithDetails1(Term(expression1), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(expression2), TermAssociationType::Positive);
    TermsWithDetails const termsWithDetails{termWithDetails1, termWithDetails2};

    additionAndSubtraction.putTermsWithDetails(termsWithDetails);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expression1, expressions[0]);
    EXPECT_EQ(expression2, expressions[1]);
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations[0]);
    EXPECT_EQ(TermAssociationType::Positive, associations[1]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetExpressionsWorks) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression1(createExpressionIfPossible({"x"}));
    Expression const expression2(createExpressionIfPossible({"y"}));
    additionAndSubtraction.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    Expressions const& expressions(additionAndSubtraction.getExpressions());

    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expression1, expressions[0]);
    EXPECT_EQ(expression2, expressions[1]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetAssociationsWorks) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression1(createExpressionIfPossible({"x"}));
    Expression const expression2(createExpressionIfPossible({"y"}));
    additionAndSubtraction.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());

    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations[0]);
    EXPECT_EQ(TermAssociationType::Negative, associations[1]);
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetAsTermsWithDetailsWorks) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression const expression1(createExpressionIfPossible({"x"}));
    Expression const expression2(createExpressionIfPossible({"y"}));
    additionAndSubtraction.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    TermsWithDetails termsWithDetails(additionAndSubtraction.getAsTermsWithDetails());

    ASSERT_EQ(2U, termsWithDetails.size());
    Term const& term1(getTermConstReferenceFromUniquePointer(termsWithDetails[0].baseTermPointer));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getAsVariable().getVariableName());
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetails[0].association);
    Term const& term2(getTermConstReferenceFromUniquePointer(termsWithDetails[1].baseTermPointer));
    ASSERT_EQ(TermType::Variable, term2.getTermType());
    EXPECT_EQ("y", term2.getAsVariable().getVariableName());
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetails[1].association);
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetSizeWorks) {
    AdditionAndSubtractionOfExpressions const additionAndSubtraction1;
    AdditionAndSubtractionOfExpressions additionAndSubtraction2;
    Expression const expression1(createExpressionIfPossible({"x"}));
    Expression const expression2(createExpressionIfPossible({"y"}));
    additionAndSubtraction2.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction2.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    EXPECT_EQ(0, additionAndSubtraction1.getSize());
    EXPECT_EQ(2, additionAndSubtraction2.getSize());
}

}  // namespace alba::algebra
