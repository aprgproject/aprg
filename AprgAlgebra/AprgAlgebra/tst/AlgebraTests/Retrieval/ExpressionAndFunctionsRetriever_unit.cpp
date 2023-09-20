#include <Algebra/Retrieval/ExpressionAndFunctionsRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::algebra {

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromPolynomialWorks) {
    ExpressionAndFunctionsRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromExpressionWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Expression const expression(createExpressionIfPossible({678, "+", Monomial(576, {{"g", 9}})}));

    retriever.retrieveFromExpression(expression);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    ASSERT_EQ(1U, termsSet.size());
    auto it = termsSet.cbegin();
    EXPECT_EQ(Term(expression), *(it++));
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromFunctionWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Expression const expression(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})}));
    Function const functionObject(
        "functionName", Term(expression), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromFunction(functionObject);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    ASSERT_EQ(2U, termsSet.size());
    auto it = termsSet.cbegin();
    EXPECT_EQ(Term(expression), *(it++));
    EXPECT_EQ(Term(functionObject), *(it++));
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromEquationsWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Equation const equation1(Monomial(34, {{"x", 5}}), "=", Monomial(41, {{"y", 6}}));
    Equation const equation2(Monomial(95, {{"x", 7}}), "=", Monomial(18, {{"y", 8}}));

    retriever.retrieveFromEquations({equation1, equation2});

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromEquationWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Term const leftHandTerm(Monomial(34, {{"x", 5}}));
    Term const rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation const equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromTermWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Term const expesssionTerm1(createExpressionIfPossible({"a", "^", 2}));
    Term const expesssionTerm2(createExpressionIfPossible({678, "+", Monomial(576, {{"g", 9}})}));
    Function const functionObject(
        "functionName", expesssionTerm1, [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term const functionTerm1(functionObject);

    retriever.retrieveFromTerm(Constant(1.234));
    retriever.retrieveFromTerm(Variable("b"));
    retriever.retrieveFromTerm(Monomial(34, {{"c", 5}, {"d", 6}}));
    retriever.retrieveFromTerm(Polynomial{Monomial(516, {{"e", 7}}), Monomial(643, {{"f", 8}})});
    retriever.retrieveFromTerm(expesssionTerm2);
    retriever.retrieveFromTerm(functionTerm1);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    ASSERT_EQ(3U, termsSet.size());
    auto it = termsSet.cbegin();
    EXPECT_EQ(expesssionTerm1, *(it++));
    EXPECT_EQ(expesssionTerm2, *(it++));
    EXPECT_EQ(functionTerm1, *(it++));
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromConstantWorks) {
    ExpressionAndFunctionsRetriever retriever;

    retriever.retrieveFromConstant(Constant(1.234));

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromVariableWorks) {
    ExpressionAndFunctionsRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromMonomialWorks) {
    ExpressionAndFunctionsRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

TEST(ExpressionAndFunctionsRetrieverTest, RetrieveFromPolynomialsWorks) {
    ExpressionAndFunctionsRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Monomials{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})});
    polynomials.emplace_back(Monomials{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});
    retriever.retrieveFromPolynomials(polynomials);

    TermSet const& termsSet(retriever.getExpressionsAndFunctions());
    EXPECT_TRUE(termsSet.empty());
}

}  // namespace alba::algebra
