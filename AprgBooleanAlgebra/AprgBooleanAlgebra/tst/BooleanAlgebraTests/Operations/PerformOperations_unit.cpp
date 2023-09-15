#include <BooleanAlgebra/Operations/PerformOperations.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(PerformOperationsTest, PerformOperationUnaryOperationWorks) {
    Term const termToVerify1(performOperation(Operator("~"), false));
    Term const termToVerify2(performOperation(Operator("~"), true));

    EXPECT_EQ(Term(true), termToVerify1);
    EXPECT_EQ(Term(false), termToVerify2);
}

TEST(PerformOperationsTest, PerformOperationBinaryOperationWorks) {
    Term const termToVerify1(performOperation(Operator("&"), false, false));
    Term const termToVerify2(performOperation(Operator("&"), false, true));
    Term const termToVerify3(performOperation(Operator("&"), true, false));
    Term const termToVerify4(performOperation(Operator("&"), true, true));
    Term const termToVerify5(performOperation(Operator("|"), false, false));
    Term const termToVerify6(performOperation(Operator("|"), false, true));
    Term const termToVerify7(performOperation(Operator("|"), true, false));
    Term const termToVerify8(performOperation(Operator("|"), true, true));

    EXPECT_EQ(Term(false), termToVerify1);
    EXPECT_EQ(Term(false), termToVerify2);
    EXPECT_EQ(Term(false), termToVerify3);
    EXPECT_EQ(Term(true), termToVerify4);
    EXPECT_EQ(Term(false), termToVerify5);
    EXPECT_EQ(Term(true), termToVerify6);
    EXPECT_EQ(Term(true), termToVerify7);
    EXPECT_EQ(Term(true), termToVerify8);
}

TEST(PerformOperationsTest, PerformNotWorks) {
    Term const termToVerify1(performNot(false));
    Term const termToVerify2(performNot(true));

    EXPECT_EQ(Term(true), termToVerify1);
    EXPECT_EQ(Term(false), termToVerify2);
}

TEST(PerformOperationsTest, PerformAndWorks) {
    Term const termToVerify1(performAnd(false, false));
    Term const termToVerify2(performAnd(false, true));
    Term const termToVerify3(performAnd(true, false));
    Term const termToVerify4(performAnd(true, true));

    EXPECT_EQ(Term(false), termToVerify1);
    EXPECT_EQ(Term(false), termToVerify2);
    EXPECT_EQ(Term(false), termToVerify3);
    EXPECT_EQ(Term(true), termToVerify4);
}

TEST(PerformOperationsTest, PerformOrWorks) {
    Term const termToVerify1(performOr(false, false));
    Term const termToVerify2(performOr(false, true));
    Term const termToVerify3(performOr(true, false));
    Term const termToVerify4(performOr(true, true));

    EXPECT_EQ(Term(false), termToVerify1);
    EXPECT_EQ(Term(true), termToVerify2);
    EXPECT_EQ(Term(true), termToVerify3);
    EXPECT_EQ(Term(true), termToVerify4);
}

}  // namespace alba::booleanAlgebra
