#include <Algebra/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForLcmDenominatorWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({1}, {2});
    TermsOverTerms const fraction2({1}, {3});
    TermsOverTerms const fraction3({1}, {4});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression const expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression const subExpression1(createExpressionIfPossible({createMonomialFromNumber(6)}));
    Expression const subExpression2(createExpressionIfPossible({createMonomialFromNumber(4)}));
    Expression const subExpression3(createExpressionIfPossible({createMonomialFromNumber(3)}));
    Expression const subExpression4(
        createExpressionIfPossible({subExpression1, "+", subExpression2, "+", subExpression3}));
    Expression const expressionToExpect(createExpressionIfPossible({subExpression4, "/", 12}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionUsingExample1Works) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({4}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}});
    TermsOverTerms const fraction2(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}},
        {Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}});
    TermsOverTerms const fraction3(
        {Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}},
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression const expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Polynomial const polynomial1{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    Polynomial const polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial const polynomial3{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomial const polynomial4{Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Expression const subExpression1(createExpressionIfPossible({4, "*", polynomial1}));
    Expression const subExpression2(createExpressionIfPossible({polynomial3}));
    Expression const subExpression3(createExpressionIfPossible({polynomial4, "*", polynomial2}));
    Expression const subExpression4(
        createExpressionIfPossible({subExpression1, "+", subExpression2, "+", subExpression3}));
    Expression const expressionToExpect(
        createExpressionIfPossible({subExpression4, "/", polynomial2, "/", polynomial1}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(
    AdditionAndSubtractionOfTermsOverTermsTest,
    GetCombinedExpressionAndSimplifyWorksOnExponentPlusPolynomialDenominator) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Expression const exponentExpression(createExpressionIfPossible({2, "^", "x"}));
    TermsOverTerms const fraction1({exponentExpression}, {});
    TermsOverTerms const fraction2({}, {polynomial});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    string const stringToExpect("((1+(x*(2^x))+(2^(1[x] + 1)))/(1[x] + 2))");
    EXPECT_EQ(stringToExpect, convertToString(expressionToVerify));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionAndSimplifyUsingExample1Works) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({4}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}});
    TermsOverTerms const fraction2(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}},
        {Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}});
    TermsOverTerms const fraction3(
        {Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}},
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    Polynomial const polynomialToExpect1{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 2}}), Monomial(-4, {})};
    Expression const expressionToExpect(createExpressionIfPossible({polynomialToExpect1, "/", polynomialToExpect2}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForNumeratorTermsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({7}, {1});
    TermsOverTerms const fraction2({11}, {1});
    TermsOverTerms const fraction3({13}, {1});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsSubtraction(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression const expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression const subExpression1(createExpressionIfPossible({7}));
    Expression const subExpression2(createExpressionIfPossible({11}));
    Expression const subExpression3(createExpressionIfPossible({13}));
    Expression const subExpression4(
        createExpressionIfPossible({subExpression1, "-", subExpression2, "+", subExpression3}));
    Expression const expressionToExpect(createExpressionIfPossible({subExpression4}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForRevisedNumeratorTermsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({7}, {2});
    TermsOverTerms const fraction2({11}, {3});
    TermsOverTerms const fraction3({13}, {4});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsSubtraction(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression const expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression const subExpression1(createExpressionIfPossible({7, "*", createMonomialFromNumber(6)}));
    Expression const subExpression2(createExpressionIfPossible({11, "*", createMonomialFromNumber(4)}));
    Expression const subExpression3(createExpressionIfPossible({13, "*", createMonomialFromNumber(3)}));
    Expression const subExpression4(
        createExpressionIfPossible({subExpression1, "-", subExpression2, "+", subExpression3}));
    Expression const expressionToExpect(createExpressionIfPossible({subExpression4, "/", 12}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionAndSimplifyUsingExample2Works) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial const polynomial1{Monomial(2, {{"x", 1}}), Monomial(-1, {})};
    Polynomial const polynomial2{Monomial(2, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-6, {})};
    Polynomial const polynomial3{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomial const polynomial4{Monomial(6, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(-12, {})};
    Polynomial const polynomial5{Monomial(2, {{"x", 1}}), Monomial(-3, {})};
    Polynomial const polynomial6{Monomial(3, {{"x", 2}}), Monomial(-10, {{"x", 1}}), Monomial(8, {})};
    TermsOverTerms const fraction1({polynomial1}, {polynomial2});
    TermsOverTerms const fraction2({polynomial3}, {polynomial4});
    TermsOverTerms const fraction3({polynomial5}, {polynomial6});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsSubtraction(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(-10, {{"x", 1}}), Monomial(7, {})};
    Polynomial const polynomialToExpect2{
        Monomial(6, {{"x", 3}}), Monomial(-11, {{"x", 2}}), Monomial(-14, {{"x", 1}}), Monomial(24, {})};
    Expression const expressionToExpect(createExpressionIfPossible({polynomialToExpect1, "/", polynomialToExpect2}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, ConstructionWorks) {
    AdditionAndSubtractionOfTermsOverTerms const additionAndSubtraction;

    EXPECT_TRUE(additionAndSubtraction.getItems().empty());
    EXPECT_TRUE(additionAndSubtraction.getAssociations().empty());
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsAdditionWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction({487}, {756});

    additionAndSubtraction.putAsAddition(fraction);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, itemsToVerify.size());
    Terms const& numerators(itemsToVerify[0].getNumerators());
    Terms const& denominators(itemsToVerify[0].getDenominators());
    ASSERT_EQ(1U, numerators.size());
    EXPECT_EQ(Term(487), numerators[0]);
    ASSERT_EQ(1U, denominators.size());
    EXPECT_EQ(Term(756), denominators[0]);
    ASSERT_EQ(1U, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, associationToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsSubtractionWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction({487}, {756});

    additionAndSubtraction.putAsSubtraction(fraction);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, itemsToVerify.size());
    Terms const& numerators(itemsToVerify[0].getNumerators());
    Terms const& denominators(itemsToVerify[0].getDenominators());
    ASSERT_EQ(1U, numerators.size());
    EXPECT_EQ(Term(487), numerators[0]);
    ASSERT_EQ(1U, denominators.size());
    EXPECT_EQ(Term(756), denominators[0]);
    ASSERT_EQ(1U, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Negative, associationToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsAddOrSubtractionWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction({487}, {756});

    additionAndSubtraction.putAsAddOrSubtraction(fraction, TermAssociationType::Negative);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, itemsToVerify.size());
    Terms const& numerators(itemsToVerify[0].getNumerators());
    Terms const& denominators(itemsToVerify[0].getDenominators());
    ASSERT_EQ(1U, numerators.size());
    EXPECT_EQ(Term(487), numerators[0]);
    ASSERT_EQ(1U, denominators.size());
    EXPECT_EQ(Term(756), denominators[0]);
    ASSERT_EQ(1U, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Negative, associationToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexUsingAComplicatedExampleWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({4}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}});
    TermsOverTerms const fraction2(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}},
        {Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}});
    TermsOverTerms const fraction3(
        {Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}},
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);
    Terms const denominatorTerms(additionAndSubtraction.getLcmOfDenominatorTerms());

    Terms termsToVerify1(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, denominatorTerms));
    Terms termsToVerify2(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(1, denominatorTerms));
    Terms termsToVerify3(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(2, denominatorTerms));

    Term const termToExpect1(4);
    Term const termToExpect2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const termToExpect3(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})});
    Term const termToExpect4(Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term const termToExpect5(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    ASSERT_EQ(2U, termsToVerify1.size());
    EXPECT_EQ(termToExpect1, termsToVerify1[0]);
    EXPECT_EQ(termToExpect2, termsToVerify1[1]);
    ASSERT_EQ(1U, termsToVerify2.size());
    EXPECT_EQ(termToExpect3, termsToVerify2[0]);
    ASSERT_EQ(2U, termsToVerify3.size());
    EXPECT_EQ(termToExpect4, termsToVerify3[0]);
    EXPECT_EQ(termToExpect5, termsToVerify3[1]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithNoTermsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({1}, {});
    TermsOverTerms const fraction2({1}, {});
    TermsOverTerms const fraction3({1}, {});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term const termToExpect1(1);
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithTermsThatAreEmptyWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({1}, {Term()});
    TermsOverTerms const fraction2({1}, {Term()});
    TermsOverTerms const fraction3({1}, {Term()});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term const termToExpect1(1);
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithAllOneWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({1}, {1});
    TermsOverTerms const fraction2({1}, {1});
    TermsOverTerms const fraction3({1}, {1});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term const termToExpect1(1);
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithLcmMonomialWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({1}, {Polynomial{Monomial(3, {{"x", 3}})}});
    TermsOverTerms const fraction2({1}, {Monomial(5, {{"x", 5}})});
    TermsOverTerms const fraction3({1}, {Monomial(7, {{"y", 7}})});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term const termToExpect1(Monomial(105, {{"x", 5}, {"y", 7}}));
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithNoCommonFactorsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({1}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}});
    TermsOverTerms const fraction2({1}, {Polynomial{Monomial(1, {{"y", 1}}), Monomial(5, {})}});
    TermsOverTerms const fraction3({1}, {Polynomial{Monomial(1, {{"z", 1}}), Monomial(7, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term const termToExpect1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})});
    Term const termToExpect2(Polynomial{Monomial(1, {{"y", 1}}), Monomial(5, {})});
    Term const termToExpect3(Polynomial{Monomial(1, {{"z", 1}}), Monomial(7, {})});
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
    EXPECT_EQ(termToExpect2, termsToVerify[1]);
    EXPECT_EQ(termToExpect3, termsToVerify[2]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithCommonFactorsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    TermsOverTerms const fraction1({1}, {polynomial});
    TermsOverTerms const fraction2({1}, {Term(), polynomial});
    TermsOverTerms const fraction3({1}, {polynomial, polynomial, polynomial});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term const termToExpect1(polynomial);
    Term const termToExpect2(createExpressionIfPossible({polynomial, "^", 3}));
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
    EXPECT_EQ(termToExpect2, termsToVerify[1]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithFactorsOfDifferenceOfSquaresWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction1({1}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}});
    TermsOverTerms const fraction2({1}, {Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}});
    TermsOverTerms const fraction3({1}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term const termToExpect1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term const termToExpect2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
    EXPECT_EQ(termToExpect2, termsToVerify[1]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexUsingOutOfRangeIndexReturnsEmpty) {
    AdditionAndSubtractionOfTermsOverTerms const additionAndSubtraction;

    Terms const termsToVerify1(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {}));
    Terms const termsToVerify2(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(1, {}));
    Terms const termsToVerify3(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(2, {}));

    ASSERT_TRUE(termsToVerify1.empty());
    ASSERT_TRUE(termsToVerify2.empty());
    ASSERT_TRUE(termsToVerify3.empty());
}

TEST(
    AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsNumeratorTermsWhenLcmIsEmpty) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction({Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})}}, {1});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {}));

    Term const termToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})});
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsNumeratorTermsWhenLcmIsOne) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction({Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})}}, {1});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {1}));

    Term const termToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})});
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsGcfOfDenominatorAndLcm) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms const fraction({1}, {Monomial(4, {{"x", 5}, {"y", 3}})});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(
        additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {Monomial(52, {{"x", 7}, {"y", 8}})}));

    Term const termToExpect(Monomial(13, {{"x", 2}, {"y", 5}}));
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(
    AdditionAndSubtractionOfTermsOverTermsTest,
    GetNumeratorTermsBasedOnLcmOnIndexReturnsWithCommonFactorsFromDenominatorAndLcmRemoved) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    TermsOverTerms const fraction({1}, {polynomial});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(
        additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {polynomial, polynomial, polynomial}));

    Term const termToExpect(polynomial);
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify[0]);
    EXPECT_EQ(termToExpect, termsToVerify[1]);
}

}  // namespace alba::algebra
