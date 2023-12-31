#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::algebra {

TEST(VariableNamesRetrieverTest, RetrieveFromVariableWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(1U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromMonomialWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(2U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromEquationsWorks) {
    VariableNamesRetriever retriever;
    Equation const equation1("a", "=", "b");
    Equation const equation2("x", "=", "y");
    Equation const equation3("r", "!=", "p");

    retriever.retrieveFromEquations(Equations{equation1, equation2, equation3});

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(6U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
    EXPECT_EQ("p", *(it++));
    EXPECT_EQ("r", *(it++));
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromEquationWorks) {
    VariableNamesRetriever retriever;
    Term const leftHandTerm(Monomial(34, {{"x", 5}}));
    Term const rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation const equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(2U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromTermWorks) {
    VariableNamesRetriever retriever;
    Function const functionObject(
        "functionName", Term(createExpressionIfPossible({"a", "^", 2})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromTerm(Constant(1.234));
    retriever.retrieveFromTerm(Variable("b"));
    retriever.retrieveFromTerm(Monomial(34, {{"c", 5}, {"d", 6}}));
    retriever.retrieveFromTerm(Polynomial{Monomial(516, {{"e", 7}}), Monomial(643, {{"f", 8}})});
    retriever.retrieveFromTerm(createExpressionIfPossible({678, "+", Monomial(576, {{"g", 9}})}));
    retriever.retrieveFromTerm(functionObject);

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(7U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
    EXPECT_EQ("c", *(it++));
    EXPECT_EQ("d", *(it++));
    EXPECT_EQ("e", *(it++));
    EXPECT_EQ("f", *(it++));
    EXPECT_EQ("g", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromConstantWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromConstant(Constant(1.234));

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    EXPECT_TRUE(variableNamesSet.empty());
}

TEST(VariableNamesRetrieverTest, RetrieveFromPolynomialWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(2U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromExpressionWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromExpression(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(1U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromFunctionWorks) {
    VariableNamesRetriever retriever;
    Function const functionObject(
        "functionName", Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromFunction(functionObject);

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(1U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromPolynomialsWorks) {
    VariableNamesRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Monomials{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})});
    polynomials.emplace_back(Monomials{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});
    retriever.retrieveFromPolynomials(polynomials);

    VariableNamesSet const& variableNamesSet(retriever.getVariableNames());
    ASSERT_EQ(4U, variableNamesSet.size());
    auto it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

}  // namespace alba::algebra
