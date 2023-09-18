#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(TermsWithAssociationTest, TermsWithAssociationEqualityOperatorWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(20), TermAssociationType::Positive);
    TermsWithAssociation const terms1{termWithDetails1};
    TermsWithAssociation const terms2{termWithDetails1};
    TermsWithAssociation const terms3{termWithDetails2};
    TermsWithAssociation const terms4{termWithDetails1, termWithDetails1};

    EXPECT_TRUE(terms1 == terms1);
    EXPECT_TRUE(terms1 == terms2);
    EXPECT_FALSE(terms1 == terms3);
    EXPECT_FALSE(terms1 == terms4);
}

TEST(TermsWithAssociationTest, TermsWithAssociationInequalityOperatorWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(20), TermAssociationType::Positive);
    TermsWithAssociation const terms1{termWithDetails1};
    TermsWithAssociation const terms2{termWithDetails1};
    TermsWithAssociation const terms3{termWithDetails2};
    TermsWithAssociation const terms4{termWithDetails1, termWithDetails1};

    EXPECT_FALSE(terms1 != terms1);
    EXPECT_FALSE(terms1 != terms2);
    EXPECT_TRUE(terms1 != terms3);
    EXPECT_TRUE(terms1 != terms4);
}

TEST(TermsWithAssociationTest, TermsWithAssociationLessThanOperatorWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails const termWithDetails2(Term(9), TermAssociationType::Positive);
    TermWithDetails const termWithDetails3(Term(11), TermAssociationType::Positive);
    TermsWithAssociation const terms1{termWithDetails1, termWithDetails1};
    TermsWithAssociation const terms2{termWithDetails1};
    TermsWithAssociation const terms3{termWithDetails1, termWithDetails1, termWithDetails1};
    TermsWithAssociation const terms4{termWithDetails2};
    TermsWithAssociation const terms5{termWithDetails3};

    EXPECT_FALSE(terms1 < terms1);
    EXPECT_FALSE(terms1 < terms2);
    EXPECT_TRUE(terms1 < terms3);
    EXPECT_FALSE(terms2 < terms4);
    EXPECT_TRUE(terms2 < terms5);
}

TEST(TermsWithAssociationTest, GetFirstTermWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(20), TermAssociationType::Positive);
    TermsWithAssociation const terms1{termWithDetails1};
    TermsWithAssociation const terms2{termWithDetails2};

    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(terms1.getFirstTerm()));
    EXPECT_EQ(Term(20), getTermConstReferenceFromBaseTerm(terms2.getFirstTerm()));
}

TEST(TermsWithAssociationTest, GetFirstAssociationTypeWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(20), TermAssociationType::Positive);
    TermsWithAssociation const terms1{termWithDetails1};
    TermsWithAssociation const terms2{termWithDetails2};

    EXPECT_EQ(TermAssociationType::Negative, terms1.getFirstAssociationType());
    EXPECT_EQ(TermAssociationType::Positive, terms2.getFirstAssociationType());
}

TEST(TermsWithAssociationTest, GetTermsWithDetailsWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(20), TermAssociationType::Positive);
    TermsWithAssociation const terms{termWithDetails1, termWithDetails2};

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());

    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_TRUE(termWithDetails1 == termsToVerify[0]);
    EXPECT_TRUE(termWithDetails2 == termsToVerify[1]);
}

TEST(TermsWithAssociationTest, ClearWorks) {
    TermWithDetails const termWithDetails1(Term(30), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(20), TermAssociationType::Positive);
    TermWithDetails const termWithDetails3(Term(10), TermAssociationType::Positive);
    TermsWithAssociation terms{termWithDetails1, termWithDetails2, termWithDetails3};

    terms.clear();

    TermsWithDetails const termsToVerify(terms.getTermsWithDetails());
    EXPECT_TRUE(termsToVerify.empty());
}

TEST(TermsWithAssociationTest, SortWorksWhileIncludingFirstItem) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(Term(20), TermAssociationType::Positive);
    TermWithDetails const termWithDetails3(Term(30), TermAssociationType::Positive);
    TermsWithAssociation terms{termWithDetails1, termWithDetails2, termWithDetails3};

    terms.sort(false);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(20), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[0].association);
    EXPECT_EQ(Term(30), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[1].association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[2].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[2].association);
}

TEST(TermsWithAssociationTest, SortWorksWhileNotIncludingFirstItem) {
    TermWithDetails const termWithDetails1(Term(30), TermAssociationType::Positive);
    TermWithDetails const termWithDetails2(Term(20), TermAssociationType::Positive);
    TermWithDetails const termWithDetails3(Term(10), TermAssociationType::Positive);
    TermsWithAssociation terms{termWithDetails1, termWithDetails2, termWithDetails3};

    terms.sort(true);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(Term(30), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[0].association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[1].association);
    EXPECT_EQ(Term(20), getTermConstReferenceFromUniquePointer(termsToVerify[2].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[2].association);
}

TEST(TermsWithAssociationTest, PutTermWithDetailsWorks) {
    TermsWithAssociation terms;
    TermWithDetails const termWithDetails(Term(10), TermAssociationType::Negative);

    terms.putTermWithDetails(termWithDetails);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[0].association);
}

TEST(TermsWithAssociationTest, PutTermsWithDetailsWorksUsingInitializerList) {
    TermsWithAssociation terms;

    terms.putTermsWithDetails(
        {TermWithDetails(Term(100), TermAssociationType::Positive),
         TermWithDetails(Term(2), TermAssociationType::Negative)});

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(Term(100), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[0].association);
    EXPECT_EQ(Term(2), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[1].association);
}

TEST(TermsWithAssociationTest, PutTermsWithDetailsWorksUsingConstReference) {
    TermsWithAssociation terms;
    TermsWithDetails const termsWithDetails{
        TermWithDetails(Term(100), TermAssociationType::Positive),
        TermWithDetails(Term(2), TermAssociationType::Negative)};

    terms.putTermsWithDetails(termsWithDetails);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(Term(100), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[0].association);
    EXPECT_EQ(Term(2), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[1].association);
}

TEST(TermsWithAssociationTest, PutTermWithAssociationWorks) {
    TermsWithAssociation terms;

    terms.putTermWithAssociation(Term(10), TermAssociationType::Negative);

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[0].association);
}

TEST(TermsWithAssociationTest, PutTermWithPositiveAssociationWorks) {
    TermsWithAssociation terms;

    terms.putTermWithPositiveAssociation(Term(10));

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify[0].association);
}

TEST(TermsWithAssociationTest, PutTermWithNegativeAssociationWorks) {
    TermsWithAssociation terms;

    terms.putTermWithNegativeAssociation(Term(10));

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[0].association);
}

TEST(TermsWithAssociationTest, ReverseTheAssociationOfTheTermsWorks) {
    TermWithDetails const termWithDetails(Term(10), TermAssociationType::Positive);
    TermsWithAssociation terms{termWithDetails, termWithDetails};

    terms.reverseTheAssociationOfTheTerms();

    TermsWithDetails termsToVerify(terms.getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[0].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[0].association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termsToVerify[1].baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify[1].association);
}

TEST(TermsWithAssociationTest, GetSizeWorks) {
    TermWithDetails const termWithDetails(Term(10), TermAssociationType::Negative);
    TermsWithAssociation const terms1;
    TermsWithAssociation const terms2{termWithDetails};
    TermsWithAssociation const terms3{termWithDetails, termWithDetails};

    EXPECT_EQ(0, terms1.getSize());
    EXPECT_EQ(1, terms2.getSize());
    EXPECT_EQ(2, terms3.getSize());
}

TEST(TermsWithAssociationTest, IsEmptyWorks) {
    TermWithDetails const termWithDetails(Term(10), TermAssociationType::Negative);
    TermsWithAssociation const terms1;
    TermsWithAssociation const terms2{termWithDetails};
    TermsWithAssociation const terms3{termWithDetails, termWithDetails};

    EXPECT_TRUE(terms1.isEmpty());
    EXPECT_FALSE(terms2.isEmpty());
    EXPECT_FALSE(terms3.isEmpty());
}

}  // namespace alba::algebra
