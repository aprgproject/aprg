#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;

namespace alba::algebra {

TEST(RetrieveHelpersTest, RetrieveTermsFromTermsWithDetailsWorks) {
    TermsWithDetails const termsWithDetails{
        TermWithDetails(Term(10), TermAssociationType::Positive),
        TermWithDetails(Term(9), TermAssociationType::Negative),
        TermWithDetails(Term(11), TermAssociationType::Positive)};

    Terms terms;
    retrieveTermsFromTermsWithDetails(terms, termsWithDetails);

    ASSERT_EQ(3U, terms.size());
    EXPECT_EQ(Term(10), terms[0]);
    EXPECT_EQ(Term(9), terms[1]);
    EXPECT_EQ(Term(11), terms[2]);
}

TEST(RetrieveHelpersTest, GetCoefficientOfMonomialWithNoVariablesWorks) {
    Polynomial const polynomial1;
    Polynomial const polynomial2{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})};
    Polynomial const polynomial3{Monomial(587, {{"x", 9}}), Monomial(975, {})};

    EXPECT_EQ(AlbaNumber(0), getCoefficientOfMonomialWithNoVariables(polynomial1));
    EXPECT_EQ(AlbaNumber(0), getCoefficientOfMonomialWithNoVariables(polynomial2));
    EXPECT_EQ(AlbaNumber(975), getCoefficientOfMonomialWithNoVariables(polynomial3));
}

TEST(RetrieveHelpersTest, GetCoefficientOfMonomialWithVariableOnlyWorks) {
    Polynomial const polynomial1;
    Polynomial const polynomial2{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})};
    Polynomial const polynomial3{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})};

    EXPECT_EQ(AlbaNumber(0), getCoefficientOfMonomialWithVariableOnly(polynomial1, "x"));
    EXPECT_EQ(AlbaNumber(516), getCoefficientOfMonomialWithVariableOnly(polynomial2, "a"));
    EXPECT_EQ(AlbaNumber(975), getCoefficientOfMonomialWithVariableOnly(polynomial3, "y"));
}

TEST(RetrieveHelpersTest, RetrieveSubExpressionsAndSubFunctionsWorks) {
    Term const expesssionTerm(createExpressionIfPossible({"a", "^", 2}));
    Function const functionObject(
        "functionName", expesssionTerm, [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term const functionTerm(functionObject);

    Terms terms(retrieveSubExpressionsAndSubFunctions(functionTerm));

    ASSERT_EQ(1U, terms.size());
    EXPECT_EQ(expesssionTerm, terms[0]);
}

TEST(RetrieveHelpersTest, RetrieveSubTermsWorks) {
    Term const expesssionTerm(createExpressionIfPossible({"a", "^", 2}));
    Function const functionObject(
        "functionName", expesssionTerm, [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term const functionTerm(functionObject);

    Terms terms(retrieveSubTerms(functionTerm));

    ASSERT_EQ(3U, terms.size());
    EXPECT_EQ(Term(2), terms[0]);
    EXPECT_EQ(Term("a"), terms[1]);
    EXPECT_EQ(expesssionTerm, terms[2]);
}

TEST(RetrieveHelpersTest, GetTermsWithDetailsThatSatisfiesCondition) {
    TermsWithDetails const termsWithDetails{
        TermWithDetails(Term("x"), TermAssociationType::Positive),
        TermWithDetails(Term("y"), TermAssociationType::Positive),
        TermWithDetails(Term("z"), TermAssociationType::Negative)};

    TermsWithDetails termsWithDetailsToVerify = retrieveTermsWithDetailsThatSatisfiesCondition(
        termsWithDetails,
        [](TermWithDetails const& termWithDetails) { return termWithDetails.hasNegativeAssociation(); });

    ASSERT_EQ(1U, termsWithDetailsToVerify.size());
    EXPECT_EQ(Term("z"), getTermConstReferenceFromUniquePointer(termsWithDetailsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetailsToVerify[0].association);
}

TEST(RetrieveHelpersTest, GetCoefficientsForVariablesOnlyWorks) {
    Polynomial const polynomial{
        Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}}), Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})};

    VariableToValueMap const variableToValueMap(getCoefficientsForVariablesOnly(polynomial));

    ASSERT_EQ(4U, variableToValueMap.size());
    auto it = variableToValueMap.cbegin();
    EXPECT_EQ("a", it->first);
    EXPECT_EQ(AlbaNumber(516), it->second);
    ++it;
    EXPECT_EQ("b", it->first);
    EXPECT_EQ(AlbaNumber(643), it->second);
    ++it;
    EXPECT_EQ("x", it->first);
    EXPECT_EQ(AlbaNumber(587), it->second);
    ++it;
    EXPECT_EQ("y", it->first);
    EXPECT_EQ(AlbaNumber(975), it->second);
    ++it;
}

TEST(RetrieveHelpersTest, HasAnyFunctionsWorks) {
    Term const term1(5);
    Term const term2(Functions::abs(5));

    EXPECT_FALSE(hasAnyFunctions(term1));
    EXPECT_TRUE(hasAnyFunctions(term2));
}

TEST(RetrieveHelpersTest, IsVariableFoundInTermWorks) {
    Term const term1("a");
    Term const term2("x");

    EXPECT_FALSE(isVariableFoundInTerm(term1, "x"));
    EXPECT_TRUE(isVariableFoundInTerm(term2, "x"));
}

}  // namespace alba::algebra
