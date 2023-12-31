#include <Algebra/Term/TermTypes/TermWithDetails.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(TermWithDetailsTest, ConstructionWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const termWithDetails2(termWithDetails1);

    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termWithDetails1.baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails1.association);
    EXPECT_EQ(Term(10), getTermConstReferenceFromUniquePointer(termWithDetails2.baseTermPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails2.association);
}

TEST(TermWithDetailsTest, EqualityOperatorWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const& termWithDetails2(termWithDetails1);
    TermWithDetails const termWithDetails3(Term(20), TermAssociationType::Negative);
    TermWithDetails const termWithDetails4(Term(10), TermAssociationType::Positive);

    EXPECT_TRUE(termWithDetails1 == termWithDetails1);
    EXPECT_TRUE(termWithDetails1 == termWithDetails2);
    EXPECT_FALSE(termWithDetails1 == termWithDetails3);
    EXPECT_FALSE(termWithDetails1 == termWithDetails4);
}

TEST(TermWithDetailsTest, InequalityOperatorWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Negative);
    TermWithDetails const& termWithDetails2(termWithDetails1);
    TermWithDetails const termWithDetails3(Term(20), TermAssociationType::Negative);
    TermWithDetails const termWithDetails4(Term(10), TermAssociationType::Positive);

    EXPECT_FALSE(termWithDetails1 != termWithDetails1);
    EXPECT_FALSE(termWithDetails1 != termWithDetails2);
    EXPECT_TRUE(termWithDetails1 != termWithDetails3);
    EXPECT_TRUE(termWithDetails1 != termWithDetails4);
}

TEST(TermWithDetailsTest, LessThanOperatorWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails const termWithDetails2(Term(10), TermAssociationType::Negative);
    TermWithDetails const termWithDetails3(Term(9), TermAssociationType::Positive);
    TermWithDetails const termWithDetails4(Term(11), TermAssociationType::Positive);

    EXPECT_FALSE(termWithDetails1 < termWithDetails1);
    EXPECT_TRUE(termWithDetails1 < termWithDetails2);
    EXPECT_FALSE(termWithDetails2 < termWithDetails1);
    EXPECT_FALSE(termWithDetails1 < termWithDetails3);
    EXPECT_TRUE(termWithDetails1 < termWithDetails4);
}

TEST(TermWithDetailsTest, GetAssociationPriorityWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails const termWithDetails2(Term(10), TermAssociationType::Negative);

    EXPECT_EQ(1, termWithDetails1.getAssociationPriority());
    EXPECT_EQ(2, termWithDetails2.getAssociationPriority());
}

TEST(TermWithDetailsTest, HasPositiveAssociationWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails const termWithDetails2(Term(10), TermAssociationType::Negative);

    EXPECT_TRUE(termWithDetails1.hasPositiveAssociation());
    EXPECT_FALSE(termWithDetails2.hasPositiveAssociation());
}

TEST(TermWithDetailsTest, HasNegativeAssociationWorks) {
    TermWithDetails const termWithDetails1(Term(10), TermAssociationType::Positive);
    TermWithDetails const termWithDetails2(Term(10), TermAssociationType::Negative);

    EXPECT_FALSE(termWithDetails1.hasNegativeAssociation());
    EXPECT_TRUE(termWithDetails2.hasNegativeAssociation());
}

TEST(TermWithDetailsTest, ClearWorks) {
    TermWithDetails termWithDetails(Term(10), TermAssociationType::Negative);

    termWithDetails.clear();

    EXPECT_EQ(nullptr, termWithDetails.baseTermPointer.get());
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails.association);
}

}  // namespace alba::algebra
