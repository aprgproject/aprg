#include <BooleanAlgebra/Term/Operators/TermTypeOperators.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(TermTypesOperatorsTest, UnaryNotOperatorNotConstantOperationWorks) {
    Term const term(~Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, UnaryNotOperatorNotVariableTermOperationWorks) {
    Term const term(~VariableTerm("x"));

    EXPECT_EQ(Term("x'"), term);
}

TEST(TermTypesOperatorsTest, UnaryNotOperatorNotExpressionOperationWorks) {
    Term const term(~createExpressionIfPossible({false}));

    EXPECT_EQ(Term(createExpressionIfPossible({true})), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorEmptyAndConstantOperationWorks) {
    Term const term(Term() & Constant(true));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndEmptyOperationWorks) {
    Term const term(Constant(true) & Term());

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndConstantOperationWorks) {
    Term const term(Constant(true) & Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndVariableTermOperationWorks) {
    Term const term(Constant(true) & VariableTerm("x"));

    Term const termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndExpressionOperationWorks) {
    Term const term(Constant(true) & createExpressionIfPossible({false}));

    Term const termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndTermOperationWorks) {
    Term const term(Constant(true) & Term(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorVariableTermAndConstantOperationWorks) {
    Term const term(VariableTerm("x") & Constant(true));

    Term const termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorVariableTermAndVariableTermOperationWorks) {
    Term const term(VariableTerm("x") & VariableTerm("y"));

    Term const termToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorVariableTermAndExpressionOperationWorks) {
    Term const term(VariableTerm("x") & createExpressionIfPossible({true}));

    Term const termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorVariableTermAndTermOperationWorks) {
    Term const term(VariableTerm("x") & Term(true));

    Term const termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorExpressionAndConstantOperationWorks) {
    Term const term(createExpressionIfPossible({false}) & Constant(true));

    Term const termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorExpressionAndVariableTermOperationWorks) {
    Term const term(createExpressionIfPossible({true}) & VariableTerm("x"));

    Term const termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorExpressionAndTermOperationWorks) {
    Term const term(createExpressionIfPossible({false}) & Term(true));

    Term const termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorTermAndConstantOperationWorks) {
    Term const term(Term(true) & Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorTermAndVariableTermOperationWorks) {
    Term const term(Term(true) & VariableTerm("x"));

    Term const termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorTermAndExpressionOperationWorks) {
    Term const term(Term(true) & createExpressionIfPossible({false}));

    Term const termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorEmptyOrConstantOperationWorks) {
    Term const term(Term() | Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrEmptyOperationWorks) {
    Term const term(Constant(false) | Term());

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrConstantOperationWorks) {
    Term const term(Constant(true) | Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrVariableTermOperationWorks) {
    Term const term(Constant(false) | VariableTerm("x"));

    Term const termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrExpressionOperationWorks) {
    Term const term(Constant(true) | createExpressionIfPossible({false}));

    Term const termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrTermOperationWorks) {
    Term const term(Constant(true) | Term(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorVariableTermOrConstantOperationWorks) {
    Term const term(VariableTerm("x") | Constant(false));

    Term const termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorVariableTermOrVariableTermOperationWorks) {
    Term const term(VariableTerm("x") | VariableTerm("y"));

    Term const termToExpect(createExpressionIfPossible({"x", "|", "y"}));
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorVariableTermOrExpressionOperationWorks) {
    Term const term(VariableTerm("x") | createExpressionIfPossible({false}));

    Term const termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorVariableTermOrTermOperationWorks) {
    Term const term(VariableTerm("x") | Term(false));

    Term const termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorExpressionOrConstantOperationWorks) {
    Term const term(createExpressionIfPossible({false}) | Constant(true));

    Term const termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorExpressionOrVariableTermOperationWorks) {
    Term const term(createExpressionIfPossible({false}) | VariableTerm("x"));

    Term const termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorExpressionOrTermOperationWorks) {
    Term const term(createExpressionIfPossible({false}) | Term(true));

    Term const termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorTermOrConstantOperationWorks) {
    Term const term(Term(true) | Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorTermOrVariableTermOperationWorks) {
    Term const term(Term(false) | VariableTerm("x"));

    Term const termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorTermOrExpressionOperationWorks) {
    Term const term(Term(true) | createExpressionIfPossible({false}));

    Term const termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

}  // namespace alba::booleanAlgebra
