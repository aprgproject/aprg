#include <BooleanAlgebra/Term/Operators/TermTypeOperators.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(TermTypesOperatorsTest, UnaryNotOperatorNotConstantOperationWorks) {
    Term term(~Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, UnaryNotOperatorNotVariableTermOperationWorks) {
    Term term(~VariableTerm("x"));

    EXPECT_EQ(Term("x'"), term);
}

TEST(TermTypesOperatorsTest, UnaryNotOperatorNotExpressionOperationWorks) {
    Term term(~createExpressionIfPossible({false}));

    EXPECT_EQ(Term(createExpressionIfPossible({true})), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorEmptyAndConstantOperationWorks) {
    Term term(Term() & Constant(true));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndEmptyOperationWorks) {
    Term term(Constant(true) & Term());

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndConstantOperationWorks) {
    Term term(Constant(true) & Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndVariableTermOperationWorks) {
    Term term(Constant(true) & VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndExpressionOperationWorks) {
    Term term(Constant(true) & createExpressionIfPossible({false}));

    Term termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorConstantAndTermOperationWorks) {
    Term term(Constant(true) & Term(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorVariableTermAndConstantOperationWorks) {
    Term term(VariableTerm("x") & Constant(true));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorVariableTermAndVariableTermOperationWorks) {
    Term term(VariableTerm("x") & VariableTerm("y"));

    Term termToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorVariableTermAndExpressionOperationWorks) {
    Term term(VariableTerm("x") & createExpressionIfPossible({true}));

    Term termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorVariableTermAndTermOperationWorks) {
    Term term(VariableTerm("x") & Term(true));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorExpressionAndConstantOperationWorks) {
    Term term(createExpressionIfPossible({false}) & Constant(true));

    Term termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorExpressionAndVariableTermOperationWorks) {
    Term term(createExpressionIfPossible({true}) & VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorExpressionAndTermOperationWorks) {
    Term term(createExpressionIfPossible({false}) & Term(true));

    Term termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorTermAndConstantOperationWorks) {
    Term term(Term(true) & Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorTermAndVariableTermOperationWorks) {
    Term term(Term(true) & VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperatorTermAndExpressionOperationWorks) {
    Term term(Term(true) & createExpressionIfPossible({false}));

    Term termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorEmptyOrConstantOperationWorks) {
    Term term(Term() | Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrEmptyOperationWorks) {
    Term term(Constant(false) | Term());

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrConstantOperationWorks) {
    Term term(Constant(true) | Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrVariableTermOperationWorks) {
    Term term(Constant(false) | VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrExpressionOperationWorks) {
    Term term(Constant(true) | createExpressionIfPossible({false}));

    Term termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorConstantOrTermOperationWorks) {
    Term term(Constant(true) | Term(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorVariableTermOrConstantOperationWorks) {
    Term term(VariableTerm("x") | Constant(false));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorVariableTermOrVariableTermOperationWorks) {
    Term term(VariableTerm("x") | VariableTerm("y"));

    Term termToExpect(createExpressionIfPossible({"x", "|", "y"}));
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorVariableTermOrExpressionOperationWorks) {
    Term term(VariableTerm("x") | createExpressionIfPossible({false}));

    Term termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorVariableTermOrTermOperationWorks) {
    Term term(VariableTerm("x") | Term(false));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorExpressionOrConstantOperationWorks) {
    Term term(createExpressionIfPossible({false}) | Constant(true));

    Term termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorExpressionOrVariableTermOperationWorks) {
    Term term(createExpressionIfPossible({false}) | VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorExpressionOrTermOperationWorks) {
    Term term(createExpressionIfPossible({false}) | Term(true));

    Term termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorTermOrConstantOperationWorks) {
    Term term(Term(true) | Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorTermOrVariableTermOperationWorks) {
    Term term(Term(false) | VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperatorTermOrExpressionOperationWorks) {
    Term term(Term(true) | createExpressionIfPossible({false}));

    Term termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

}  // namespace alba::booleanAlgebra
