#include <Algebra/Term/Operators/TermOperators.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(TermOperatorsTest, UnaryPlusOperatorWorksWithEmptyTerm) {
    Term const term(+Term());

    EXPECT_EQ(Term(), term);
}

TEST(TermOperatorsTest, UnaryPlusOperatorWorks) {
    Term const term(+Term(6));

    EXPECT_EQ(Term(6), term);
}

TEST(TermOperatorsTest, UnaryMinusOperatorWorksWithEmptyTerm) {
    Term const term(-Term());

    EXPECT_EQ(Term(), term);
}

TEST(TermOperatorsTest, UnaryMinusOperatorWorks) {
    Term const term(-Term(6));

    EXPECT_EQ(Term(-6), term);
}

TEST(TermOperatorsTest, BinaryPlusOperatorWorks) {
    Term const term(Term(6) + Term(3));

    EXPECT_EQ(Term(9), term);
}

TEST(TermOperatorsTest, BinaryPlusAssignmentOperatorWorks) {
    Term term(6);
    term += 3;

    EXPECT_EQ(Term(9), term);
}

TEST(TermOperatorsTest, BinaryMinusOperatorWorks) {
    Term const term(Term(6) - Term(3));

    EXPECT_EQ(Term(3), term);
}

TEST(TermOperatorsTest, BinaryMinusAssignmentOperatorWorks) {
    Term term(6);
    term -= 3;

    EXPECT_EQ(Term(3), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperatorWorks) {
    Term const term(Term(6) * Term(3));

    EXPECT_EQ(Term(18), term);
}

TEST(TermOperatorsTest, BinaryMultiplyAssignmentOperatorWorks) {
    Term term(6);
    term *= 3;

    EXPECT_EQ(Term(18), term);
}

TEST(TermOperatorsTest, BinaryDivideOperatorWorks) {
    Term const term(Term(6) / Term(3));

    EXPECT_EQ(Term(2), term);
}

TEST(TermOperatorsTest, BinaryDivideAssignmentOperatorWorks) {
    Term term(6);
    term /= 3;

    EXPECT_EQ(Term(2), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperatorWorks) {
    Term const term(Term(6) ^ Term(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerAssignmentOperatorWorks) {
    Term term(6);
    term ^= 2;

    EXPECT_EQ(Term(36), term);
}

}  // namespace alba::algebra
