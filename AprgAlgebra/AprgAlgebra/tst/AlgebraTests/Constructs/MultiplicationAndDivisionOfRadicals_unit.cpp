#include <Algebra/Constructs/MultiplicationAndDivisionOfRadicals.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::algebra {

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningConstantAndRadicalPolynomialInMultiplicationWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails const termsWithDetails{
        {Term(2), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const subTerm(Polynomial{Monomial(4, {{"x", 1}}), Monomial(4, {})});
    Term const termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningNegativeConstantAndRadicalPolynomialInMultiplicationWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails const termsWithDetails{
        {Term(-2), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const termToExpect(createExpressionIfPossible({-2, "*", squareRootOfXPlusOneTerm}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningConstantAndRadicalPolynomialInDivisionWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails const termsWithDetails{
        {Term(2), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const subTerm(createExpressionIfPossible({4, "/", xPlusOneTerm}));
    Term const termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialAndRadicalPolynomialInMultiplicationWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails const termsWithDetails{
        {Term("x"), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}})});
    Term const termToExpect(createExpressionIfPossible({insideSquareRootTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialAndRadicalPolynomialInDivisionWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails const termsWithDetails{
        {Term("x"), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const subTerm(createExpressionIfPossible({Monomial(1, {{"x", 2}}), "/", xPlusOneTerm}));
    Term const termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningRadicalPolynomialsInMultiplicationWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails const termsWithDetails{
        {squareRootOfXPlusOneTerm, TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term const termToExpect(createExpressionIfPossible({insideSquareRootTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningRadicalPolynomialsInDivisionWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Term const xPlusOneSquaredExpandedTerm(
        Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneSquaredTerm(
        createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails const termsWithDetails{
        {squareRootOfXPlusOneSquaredTerm, TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const subTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term const termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialWithCubeRootAndRadicalSquaredCubeRootWorks) {
    Term const xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term xPlusOneRadicalTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(2, 3)}));
    TermsWithDetails const termsWithDetails{
        {Term(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}})), TermAssociationType::Positive},
        {xPlusOneRadicalTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const subTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(2, {{"x", 2}}), Monomial(1, {{"x", 1}})});
    Term const termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 3)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningVariableAndMonomialWorks) {
    TermsWithDetails const termsWithDetails{
        {Term("x"), TermAssociationType::Positive},
        {Term(Monomial(1, {{"x", AlbaNumber::createFraction(3, 2)}})), TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term const termToExpect(Monomial(1, {{"x", AlbaNumber::createFraction(5, 2)}}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

}  // namespace alba::algebra
