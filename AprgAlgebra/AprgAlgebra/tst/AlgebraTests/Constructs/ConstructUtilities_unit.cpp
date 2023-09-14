#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromRaiseToPowerExpressionWorks) {
    Expression const raiseToPowerExpression(createExpressionIfPossible({abs("x"), "^", 100}));

    TermRaiseToANumber result;
    createTermRaiseToANumberFromRaiseToPowerExpression(result, raiseToPowerExpression);

    EXPECT_EQ(Term(abs("x")), result.getBase());
    EXPECT_EQ(AlbaNumber(100), result.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromMultiplicationAndDivisionExpressionWorks) {
    Monomial const numerator(32, {{"x", 5}});
    Polynomial const polynomialForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression const denominator(createExpressionIfPossible({polynomialForDenominator, "^", 10}));
    Expression const multiplicationAndDivisionExpression(createExpressionIfPossible({numerator, "/", denominator}));

    TermRaiseToANumber result;
    createTermRaiseToANumberFromMultiplicationAndDivisionExpression(result, multiplicationAndDivisionExpression);

    Term const expectedBase(createExpressionIfPossible({2, "*", "x", "/", polynomialForDenominator, "^", 2}));
    EXPECT_EQ(expectedBase, result.getBase());
    EXPECT_EQ(AlbaNumber(5), result.getExponent());
}

TEST(
    ConstructUtilitiesTest,
    CreatePolynomialOverPolynomialFromTermIfPossibleWorksForTermThatCanBeConvertedToPolynomial) {
    Polynomial const polynomial{Monomial(3, {{"x", 3}}), Monomial(6, {{"y", 3}})};
    Term const polynomialTerm(polynomial);

    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(polynomialTerm));

    ASSERT_TRUE(popOptional);
    PolynomialOverPolynomial const& pop(popOptional.value());
    EXPECT_EQ(polynomial, pop.getNumerator());
    EXPECT_EQ(createPolynomialFromNumber(1), pop.getDenominator());
}

TEST(
    ConstructUtilitiesTest,
    CreatePolynomialOverPolynomialFromTermIfPossibleWorksForExpressionThatHaveMonomialsOnMultiplyAndDivide) {
    Expression const expression(createExpressionIfPossible(
        {Monomial(1, {{"x", 9}}), "*", Monomial(2, {{"y", 8}}), "/", Monomial(3, {{"z", 7}})}));
    Term const expressionTerm(expression);

    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(expressionTerm));

    Polynomial const expectedNumerator{Monomial(2, {{"x", 9}, {"y", 8}})};
    Polynomial const expectedDenominator{Monomial(3, {{"z", 7}})};
    ASSERT_TRUE(popOptional);
    PolynomialOverPolynomial const& pop(popOptional.value());
    EXPECT_EQ(expectedNumerator, pop.getNumerator());
    EXPECT_EQ(expectedDenominator, pop.getDenominator());
}

TEST(
    ConstructUtilitiesTest,
    CreatePolynomialOverPolynomialFromTermIfPossibleWorksForExpressionThatHavePolynomialsOnMultiplyAndDivide) {
    Expression const expression(createExpressionIfPossible(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "*",
         Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "/",
         Polynomial{Monomial(2, {{"x", 1}}), Monomial(3, {})}}));
    Term const expressionTerm(expression);

    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(expressionTerm));

    Polynomial const expectedNumerator{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial const expectedDenominator{Monomial(2, {{"x", 1}}), Monomial(3, {})};
    ASSERT_TRUE(popOptional);
    PolynomialOverPolynomial const& pop(popOptional.value());
    EXPECT_EQ(expectedNumerator, pop.getNumerator());
    EXPECT_EQ(expectedDenominator, pop.getDenominator());
}

TEST(ConstructUtilitiesTest, CreatePolynomialOverPolynomialFromTermIfPossibleWorksAsEmptyWhenThereIsNoPolynomial) {
    Expression const expression(createExpressionIfPossible({"x", "^", "x"}));
    Term const expressionTerm(expression);

    PolynomialOverPolynomialOptional const popOptional(
        createPolynomialOverPolynomialFromTermIfPossible(expressionTerm));

    EXPECT_FALSE(popOptional);
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForNonMonomialOrExpression) {
    Term const nonMonomialOrExpressionTerm("x");

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(nonMonomialOrExpressionTerm));

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForMonomialWithSingleVariable) {
    Term const monomialTerm(Monomial(1, {{"x", 1.78}}));

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(monomialTerm));

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1.78), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForMonomialWithMultipleVariables) {
    Term const monomialTerm(Monomial(
        1, {{"x", AlbaNumber::createFraction(1, 2)},
            {"y", AlbaNumber::createFraction(2, 7)},
            {"z", AlbaNumber::createFraction(9, 5)}}));

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(monomialTerm));

    Term const baseToExpect(Monomial(1, {{"x", 35}, {"y", 20}, {"z", 126}}));
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber::createFraction(1, 70), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForNonRaiseToPowerExpression) {
    Term const nonRaiseToPowerExpressionTerm(createExpressionIfPossible({"x", "+", "y"}));

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(nonRaiseToPowerExpressionTerm));

    Term const baseToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForRaiseToPowerExpressionWithOneTerm) {
    Expression raiseToPowerExpression(Term("x"));
    raiseToPowerExpression.setCommonOperatorLevel(OperatorLevel::RaiseToPower);
    Term const raiseToPowerExpressionTerm(raiseToPowerExpression);

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForRaiseToPowerExpressionWithTwoTerms) {
    Term const baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term const raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, "^", 1.79}));

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(baseTerm, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1.79), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForRaiseToPowerExpressionWithThreeTerms) {
    Term const baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term const raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, "^", 1.79, "^", "y"}));

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(raiseToPowerExpressionTerm));

    Term const baseToExpect(createExpressionIfPossible({baseTerm, "^", "y"}));
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1.79), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForRaiseToPowerExpressionWithMonomialExponent) {
    Term const baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term const exponentTerm(Monomial(2.84, {{"x", 2}, {"y", 3}}));
    Term const raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, "^", exponentTerm}));

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(raiseToPowerExpressionTerm));

    Term const exponentInBaseToExpect(Monomial(1, {{"x", 2}, {"y", 3}}));
    Term const baseToExpect(createExpressionIfPossible({baseTerm, "^", exponentInBaseToExpect}));
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(2.84), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromMonomialWorks) {
    TermRaiseToANumber const termRaiseToANumber(
        createTermRaiseToANumberFromMonomial(Monomial(64, {{"x", 18}, {"y", 12}})));

    Term const baseToExpect(Monomial(2, {{"x", 3}, {"y", 2}}));
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(6), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromPolynomialWorks) {
    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromPolynomial(
        Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}));

    Term const baseToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(2), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorksWithAdditionAndSubtractionOperation) {
    Expression const additionAndSubtractionExpression(createExpressionIfPossible({abs("x"), "+", 100}));

    TermRaiseToANumber const termRaiseToANumber(
        createTermRaiseToANumberFromExpression(additionAndSubtractionExpression));

    Term const expectedBase(additionAndSubtractionExpression);
    EXPECT_EQ(expectedBase, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorksWithMultiplicationAndDivisionOperation) {
    Monomial const numerator(32, {{"x", 5}});
    Polynomial const polynomialForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression const denominator(createExpressionIfPossible({polynomialForDenominator, "^", 10}));
    Expression const multiplicationAndDivisionExpression(createExpressionIfPossible({numerator, "/", denominator}));

    TermRaiseToANumber const termRaiseToANumber(
        createTermRaiseToANumberFromExpression(multiplicationAndDivisionExpression));

    Term const expectedBase(createExpressionIfPossible({2, "*", "x", "/", polynomialForDenominator, "^", 2}));
    EXPECT_EQ(expectedBase, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(5), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorksWithRaiseToPowerOperation) {
    Expression const raiseToPowerExpression(createExpressionIfPossible({abs("x"), "^", 100}));

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromExpression(raiseToPowerExpression));

    EXPECT_EQ(Term(abs("x")), termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(100), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorksWithRaiseToPowerOperationAndMultipleExponents) {
    Expression const raiseToPowerExpression(
        createExpressionIfPossible({abs("x"), "^", 10, "^", 20, "^", Monomial(30, {{"x", 1}})}));

    TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromExpression(raiseToPowerExpression));

    Term const expectedBase(createExpressionIfPossible({abs("x"), "^", "x"}));
    EXPECT_EQ(expectedBase, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(6000), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorksWithDivisionOperationOnly) {
    Polynomial const polynomial1ForDenominator{Monomial(1, {{"x", 1}}), Monomial(5, {})};
    Polynomial const polynomial2ForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression const denominator(
        createExpressionIfPossible({polynomial1ForDenominator, "^", 2, "*", polynomial2ForDenominator, "^", 4}));
    Expression const multiplicationAndDivisionExpression(createExpressionIfPossible({1, "/", denominator}));

    TermRaiseToANumber const termRaiseToANumber(
        createTermRaiseToANumberFromExpression(multiplicationAndDivisionExpression));

    Term const expectedBase(
        createExpressionIfPossible({polynomial1ForDenominator, "*", polynomial2ForDenominator, "^", 2}));
    EXPECT_EQ(expectedBase, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(-2), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForNonMonomialOrExpression) {
    Term const nonMonomialOrExpressionTerm("x");

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromTerm(nonMonomialOrExpressionTerm));

    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForMonomialWithSingleVariable) {
    Term const monomialTerm(Monomial(1, {{"x", 1.78}}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromTerm(monomialTerm));

    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1.78), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForMonomialWithMultipleVariables) {
    Term const monomialTerm(Monomial(
        1, {{"x", AlbaNumber::createFraction(1, 2)},
            {"y", AlbaNumber::createFraction(2, 7)},
            {"z", AlbaNumber::createFraction(9, 5)}}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromTerm(monomialTerm));

    Term const baseToExpect(Monomial(1, {{"x", 35}, {"y", 20}, {"z", 126}}));
    EXPECT_EQ(baseToExpect, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 70)), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForNonRaiseToPowerExpression) {
    Term const nonRaiseToPowerExpressionTerm(createExpressionIfPossible({"x", "+", "y"}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromTerm(nonRaiseToPowerExpressionTerm));

    Term const baseToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    EXPECT_EQ(baseToExpect, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForRaiseToPowerExpressionWithOneTerm) {
    Expression raiseToPowerExpression(Term("x"));
    raiseToPowerExpression.setCommonOperatorLevel(OperatorLevel::RaiseToPower);
    Term const raiseToPowerExpressionTerm(raiseToPowerExpression);

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForRaiseToPowerExpressionWithTwoTerms) {
    Term const baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term const raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, "^", 1.79}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(baseTerm, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1.79), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForRaiseToPowerExpressionWithThreeTerms) {
    Term const baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term const raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, "^", 1.79, "^", "y"}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromTerm(raiseToPowerExpressionTerm));

    Term const expectedExponent(Monomial(1.79, {{"y", 1}}));
    EXPECT_EQ(baseTerm, termRaiseToTerms.getBase());
    EXPECT_EQ(expectedExponent, termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForRaiseToPowerExpressionWithMonomialExponent) {
    Term const baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term const exponentTerm(Monomial(2.84, {{"x", 2}, {"y", 3}}));
    Term const raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, "^", exponentTerm}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(baseTerm, termRaiseToTerms.getBase());
    EXPECT_EQ(exponentTerm, termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorksWithAdditionAndSubtractionOperation) {
    Expression const additionAndSubtractionExpression(createExpressionIfPossible({abs("x"), "+", 100}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromExpression(additionAndSubtractionExpression));

    Term const expectedBase(additionAndSubtractionExpression);
    EXPECT_EQ(expectedBase, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorksWithMultiplicationAndDivisionOperation) {
    Monomial const numerator(32, {{"x", 5}});
    Polynomial const polynomialForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression const denominator(createExpressionIfPossible({polynomialForDenominator, "^", 10}));
    Expression const multiplicationAndDivisionExpression(createExpressionIfPossible({numerator, "/", denominator}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromExpression(multiplicationAndDivisionExpression));

    Term const expectedNumerator(Monomial(2, {{"x", 1}}));
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(14, {{"x", 1}}), Monomial(49, {})});
    Term const expectedBase(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expectedBase, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(5), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorksWithRaiseToPowerOperation) {
    Expression const raiseToPowerExpression(createExpressionIfPossible({abs("x"), "^", 100}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromExpression(raiseToPowerExpression));

    EXPECT_EQ(Term(abs("x")), termRaiseToTerms.getBase());
    EXPECT_EQ(Term(100), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorksWithRaiseToPowerOperationAndMultipleExponents) {
    Expression const raiseToPowerExpression(
        createExpressionIfPossible({abs("x"), "^", 10, "^", 20, "^", Monomial(30, {{"x", 1}})}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromExpression(raiseToPowerExpression));

    Term const expectedBase(abs("x"));
    Term const expectedExponent(Monomial(6000, {{"x", 1}}));
    EXPECT_EQ(expectedBase, termRaiseToTerms.getBase());
    EXPECT_EQ(expectedExponent, termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorksWithDivisionOperationOnly) {
    Polynomial const polynomial1ForDenominator{Monomial(1, {{"x", 1}}), Monomial(5, {})};
    Polynomial const polynomial2ForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression const denominator(
        createExpressionIfPossible({polynomial1ForDenominator, "^", 2, "*", polynomial2ForDenominator, "^", 4}));
    Expression const multiplicationAndDivisionExpression(createExpressionIfPossible({1, "/", denominator}));

    TermRaiseToTerms const termRaiseToTerms(createTermRaiseToTermsFromExpression(multiplicationAndDivisionExpression));

    Term const expectedBase(
        Polynomial{Monomial(1, {{"x", 3}}), Monomial(19, {{"x", 2}}), Monomial(119, {{"x", 1}}), Monomial(245, {})});
    EXPECT_EQ(expectedBase, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(-2), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermsOverTermsFromTermWorksForNonExpression) {
    Term const nonExpressionTerm("x");

    TermsOverTerms const termsOverTerms(createTermsOverTermsFromTerm(nonExpressionTerm));

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term("x"), numeratorsToVerify[0]);
    Terms const& denominatorsToVerify(termsOverTerms.getDenominators());
    EXPECT_TRUE(denominatorsToVerify.empty());
}

TEST(ConstructUtilitiesTest, CreateTermsOverTermsFromTermWorksForNonMultiplicationDivisionExpression) {
    Term const nonMultiplicationDivisionExpressionTerm(createExpressionIfPossible({"x", "^", "x"}));

    TermsOverTerms const termsOverTerms(createTermsOverTermsFromTerm(nonMultiplicationDivisionExpressionTerm));

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(nonMultiplicationDivisionExpressionTerm, numeratorsToVerify[0]);
    Terms const& denominatorsToVerify(termsOverTerms.getDenominators());
    EXPECT_TRUE(denominatorsToVerify.empty());
}

TEST(ConstructUtilitiesTest, CreateTermsOverTermsFromTermWorksForMultiplicationDivisionExpression) {
    Term const multiplicationDivisionExpressionTerm(createExpressionIfPossible({"x", "/", "y"}));

    TermsOverTerms const termsOverTerms(createTermsOverTermsFromTerm(multiplicationDivisionExpressionTerm));

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term("x"), numeratorsToVerify[0]);
    Terms const& denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term("y"), denominatorsToVerify[0]);
}

}  // namespace alba::algebra
