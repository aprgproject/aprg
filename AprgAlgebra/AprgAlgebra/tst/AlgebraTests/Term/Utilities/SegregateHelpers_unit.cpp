#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::algebra {

TEST(MonomialHelpersTest, SegregateMonomialsWithAndWithoutVariable) {
    Monomials const monomialsToSegregate(
        {Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(4, {{"y", 5}, {"z", 6}}), Monomial(7, {{"x", 8}, {"z", 9}})});

    Monomials monomialWithVariable;
    Monomials monomialWithoutVariable;
    segregateMonomialsWithAndWithoutVariable(monomialsToSegregate, "x", monomialWithVariable, monomialWithoutVariable);

    ASSERT_EQ(2U, monomialWithVariable.size());
    EXPECT_EQ(Monomial(1, {{"x", 2}, {"y", 3}}), monomialWithVariable[0]);
    EXPECT_EQ(Monomial(7, {{"x", 8}, {"z", 9}}), monomialWithVariable[1]);
    ASSERT_EQ(1U, monomialWithoutVariable.size());
    EXPECT_EQ(Monomial(4, {{"y", 5}, {"z", 6}}), monomialWithoutVariable[0]);
}

TEST(SegregateHelpersTest, SegregateMonomialsAndNonMonomialsWorksForTerms) {
    Terms monomialTerms;
    Terms nonMonomialTerms;
    Term const termExpression(createExpressionIfPossible({"x", "^", "x"}));

    segregateMonomialsAndNonMonomials({234, termExpression}, monomialTerms, nonMonomialTerms);

    ASSERT_EQ(1U, monomialTerms.size());
    EXPECT_EQ(Term(234), monomialTerms[0]);
    ASSERT_EQ(1U, nonMonomialTerms.size());
    EXPECT_EQ(termExpression, nonMonomialTerms[0]);
}

TEST(SegregateHelpersTest, SegregateMonomialsAndNonMonomialsWorksForTermsWithDetails) {
    TermsWithAssociation termsWithAssociation;
    TermsWithDetails monomialTerms;
    TermsWithDetails nonMonomialTerms;
    Term const termExpression(createExpressionIfPossible({"x", "^", "x"}));
    termsWithAssociation.putTermWithNegativeAssociation(Term(753));
    termsWithAssociation.putTermWithPositiveAssociation(termExpression);

    segregateMonomialsAndNonMonomials(termsWithAssociation.getTermsWithDetails(), monomialTerms, nonMonomialTerms);

    ASSERT_EQ(1U, monomialTerms.size());
    TermWithDetails const& termWithDetails1(monomialTerms[0]);
    EXPECT_EQ(Term(753), getTermConstReferenceFromUniquePointer(termWithDetails1.baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails1.association);
    ASSERT_EQ(1U, nonMonomialTerms.size());
    TermWithDetails const& termWithDetails2(nonMonomialTerms[0]);
    EXPECT_EQ(termExpression, getTermConstReferenceFromUniquePointer(termWithDetails2.baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails2.association);
}

TEST(SegregateHelpersTest, SegregatePolynomialAndNonPolynomialsWorks) {
    Terms polynomialTerms;
    Terms nonPolynomialTerms;
    Term const termExpression(createExpressionIfPossible({"x", "^", "x"}));

    segregatePolynomialAndNonPolynomials({234, termExpression}, polynomialTerms, nonPolynomialTerms);

    ASSERT_EQ(1U, polynomialTerms.size());
    EXPECT_EQ(Term(234), polynomialTerms[0]);
    ASSERT_EQ(1U, nonPolynomialTerms.size());
    EXPECT_EQ(termExpression, nonPolynomialTerms[0]);
}

TEST(SegregateHelpersTest, SegregateNonExpressionsAndExpressionsWorks) {
    TermsWithAssociation termsWithAssociation;
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    Term const termExpression(createExpressionIfPossible({"x", "^", "x"}));
    termsWithAssociation.putTermWithNegativeAssociation(Term(753));
    termsWithAssociation.putTermWithPositiveAssociation(termExpression);

    segregateNonExpressionsAndExpressions(
        termsWithAssociation.getTermsWithDetails(), termsWithNonExpressions, termsWithExpressions);

    ASSERT_EQ(1U, termsWithNonExpressions.size());
    TermWithDetails const& termWithDetails1(termsWithNonExpressions[0]);
    EXPECT_EQ(Term(753), getTermConstReferenceFromUniquePointer(termWithDetails1.baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails1.association);
    ASSERT_EQ(1U, termsWithExpressions.size());
    TermWithDetails const& termWithDetails2(termsWithExpressions[0]);
    EXPECT_EQ(termExpression, getTermConstReferenceFromUniquePointer(termWithDetails2.baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails2.association);
}

TEST(SegregateHelpersTest, SegregateTermsWithPositiveAndNegativeAssociationsWorks) {
    TermsWithAssociation termsWithAssociation;
    TermsWithDetails termsInPositive;
    TermsWithDetails termsInNegative;
    termsWithAssociation.putTermWithNegativeAssociation(Term(753));
    termsWithAssociation.putTermWithPositiveAssociation(Term(159));

    segregateTermsWithPositiveAndNegativeAssociations(
        termsWithAssociation.getTermsWithDetails(), termsInPositive, termsInNegative);

    ASSERT_EQ(1U, termsInPositive.size());
    TermWithDetails const& termWithDetails1(termsInPositive[0]);
    EXPECT_EQ(Term(159), getTermConstReferenceFromUniquePointer(termWithDetails1.baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails1.association);
    ASSERT_EQ(1U, termsInNegative.size());
    TermWithDetails const& termWithDetails2(termsInNegative[0]);
    EXPECT_EQ(Term(753), getTermConstReferenceFromUniquePointer(termWithDetails2.baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails2.association);
}

}  // namespace alba::algebra
