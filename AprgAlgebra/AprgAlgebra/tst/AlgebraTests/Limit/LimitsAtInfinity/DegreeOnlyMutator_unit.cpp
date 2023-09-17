#include <Algebra/Limit/LimitsAtInfinity/DegreeOnlyMutator.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(DegreeOnlyMutatorTest, MutateEquationWorks) {
    DegreeOnlyMutator mutator("x");
    Term const leftHandTerm(Monomial(34, {{"x", 5}}));
    Term const rightHandTerm(Monomial(41, {{"y", 6}}));
    Equation equation(leftHandTerm, "=", rightHandTerm);

    mutator.mutateEquation(equation);

    Term const expectedLeftHandTerm(Monomial(1, {{"x", 5}}));
    Term const expectedRightHandTerm(1);
    Equation const expectedEquation(expectedLeftHandTerm, "=", expectedRightHandTerm);
    EXPECT_EQ(expectedEquation, equation);
}

TEST(DegreeOnlyMutatorTest, MutateConstantWorks) {
    DegreeOnlyMutator mutator("x");
    Constant constant(110);

    mutator.mutateConstant(constant);

    EXPECT_EQ(Constant(110), constant);
}

TEST(DegreeOnlyMutatorTest, MutateVariableWorks) {
    DegreeOnlyMutator mutator("x");
    Variable variable("x");

    mutator.mutateVariable(variable);

    EXPECT_EQ(Variable("x"), variable);
}

TEST(DegreeOnlyMutatorTest, MutateFunctionWorks) {
    DegreeOnlyMutator mutator("x");
    Function functionObject(
        "functionName", Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; });

    mutator.mutateFunction(functionObject);

    Function const expectedFunction(
        "functionName", Term(Monomial(1, {{"x", 10}})), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    EXPECT_EQ(expectedFunction, functionObject);
}

TEST(DegreeOnlyMutatorTest, MutateTermWorks) {
    DegreeOnlyMutator mutator("x");
    Term constantTerm(Constant(110));
    Term variableTerm(Variable("x"));
    Term monomialTerm(Monomial(34, {{"x", 5}, {"y", 6}}));
    Term polynomialTerm(Polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})});
    Term expressionTerm(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));
    Term functionTerm(Function(
        "functionName", Term(createExpressionIfPossible({4516, "+", Monomial(7895, {{"x", 10}})})),
        [](AlbaNumber const& number) -> AlbaNumber { return number; }));

    mutator.mutateTerm(constantTerm);
    mutator.mutateTerm(variableTerm);
    mutator.mutateTerm(monomialTerm);
    mutator.mutateTerm(polynomialTerm);
    mutator.mutateTerm(expressionTerm);
    mutator.mutateTerm(functionTerm);

    EXPECT_EQ(Term(110), constantTerm);
    EXPECT_EQ(Term("x"), variableTerm);
    EXPECT_EQ(Term(Monomial(1, {{"x", 5}})), monomialTerm);
    EXPECT_EQ(Term(Monomial(1, {{"x", 7}})), polynomialTerm);
    EXPECT_EQ(Term(Monomial(1, {{"x", 9}})), expressionTerm);
    Term const expectedFunctionTerm(Function(
        "functionName", Term(Monomial(1, {{"x", 10}})), [](AlbaNumber const& number) -> AlbaNumber { return number; }));
    EXPECT_EQ(expectedFunctionTerm, functionTerm);
}

TEST(DegreeOnlyMutatorTest, MutateMonomialWorks) {
    DegreeOnlyMutator mutator("x");
    Monomial monomial(34, {{"x", 5}, {"y", 6}});

    mutator.mutateMonomial(monomial);

    Monomial const expectedMonomial(1, {{"x", 5}});
    EXPECT_EQ(expectedMonomial, monomial);
}

TEST(DegreeOnlyMutatorTest, MutatePolynomialWorks) {
    DegreeOnlyMutator mutator("x");
    Polynomial polynomial{Monomial(516, {{"x", 7}}), Monomial(643, {{"y", 8}})};

    mutator.mutatePolynomial(polynomial);

    Polynomial const expectedPolynomial{Monomial(1, {{"x", 7}})};
    EXPECT_EQ(expectedPolynomial, polynomial);
}

TEST(DegreeOnlyMutatorTest, MutateExpressionWorks) {
    DegreeOnlyMutator mutator("x");
    Expression expression(createExpressionIfPossible({678, "+", Monomial(576, {{"x", 9}})}));

    mutator.mutateExpression(expression);

    Expression const expectedExpression(Term(Monomial(1, {{"x", 9}})));
    EXPECT_EQ(expectedExpression, expression);
}

TEST(DegreeOnlyMutatorTest, MutateExpressionWorksWhenRaiseToPowerFractionalExponent) {
    DegreeOnlyMutator mutator("x");
    Term const base(Polynomial{Monomial(516, {{"x", 16}}), Monomial(643, {{"y", 8}})});
    Expression expression(createExpressionIfPossible({base, "^", AlbaNumber::createFraction(3, 4)}));

    mutator.mutateExpression(expression);

    Expression const expectedExpression(Term(Monomial(1, {{"x", 12}})));
    EXPECT_EQ(expectedExpression, expression);
}

}  // namespace alba::algebra
