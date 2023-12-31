#include <Algebra/Retrieval/NumberOfTermsRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::algebra {

TEST(NumberOfTermsRetrieverTest, RetrieveFromConstantWorks) {
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromConstant(Constant(1.234));

    EXPECT_EQ(1, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromVariableWorks) {
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromVariable(Variable("x"));

    EXPECT_EQ(1, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromMonomialWorks) {
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromMonomial(Monomial(34, {{"x", 5}, {"y", 6}}));

    EXPECT_EQ(1, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromExpressionWorks) {
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromExpression(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));

    EXPECT_EQ(3, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromFunctionWorks) {
    NumberOfTermsRetriever retriever;
    Function const functionObject(
        "functionName", Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromFunction(functionObject);

    EXPECT_EQ(4, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromEquationsWorks) {
    NumberOfTermsRetriever retriever;
    Equation const equation1(Monomial(34, {{"x", 5}}), "=", Monomial(41, {{"y", 6}}));
    Equation const equation2(Monomial(95, {{"x", 7}}), "=", Monomial(18, {{"y", 8}}));

    retriever.retrieveFromEquations({equation1, equation2});

    EXPECT_EQ(4, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromEquationWorks) {
    NumberOfTermsRetriever retriever;
    Term const leftHandTerm(Monomial(34, {{"x", 5}}));
    Term const rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation const equation(leftHandTerm, "=", rightHandTerm);

    retriever.retrieveFromEquation(equation);

    EXPECT_EQ(2, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromTermWorks) {
    NumberOfTermsRetriever retriever;
    Function const functionObject(
        "functionName", Term(createExpressionIfPossible({"a", "^", 2})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    retriever.retrieveFromTerm(Constant(1.234));
    retriever.retrieveFromTerm(Variable("b"));
    retriever.retrieveFromTerm(Monomial(34, {{"c", 5}, {"d", 6}}));
    retriever.retrieveFromTerm(Polynomial{Monomial(516, {{"e", 7}}), Monomial(643, {{"f", 8}})});
    retriever.retrieveFromTerm(createExpressionIfPossible({678, "+", Monomial(576, {{"g", 9}})}));
    retriever.retrieveFromTerm(functionObject);

    EXPECT_EQ(12, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromPolynomialWorks) {
    NumberOfTermsRetriever retriever;

    retriever.retrieveFromPolynomial(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});

    EXPECT_EQ(2, retriever.getNumberOfTerms());
}

TEST(NumberOfTermsRetrieverTest, RetrieveFromPolynomialsWorks) {
    NumberOfTermsRetriever retriever;
    Polynomials polynomials;
    polynomials.emplace_back(Monomials{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})});
    polynomials.emplace_back(Monomials{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})});
    retriever.retrieveFromPolynomials(polynomials);

    EXPECT_EQ(4, retriever.getNumberOfTerms());
}

}  // namespace alba::algebra
