#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(IsolationOfOneVariableOnEqualityEquationTest, GetIdenticalExponentForVariableIfPossibleWorksOnPolynomialEquation) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    EXPECT_EQ(AlbaNumber(1), isolation.getIdenticalExponentForVariableIfPossible("x"));
    EXPECT_EQ(AlbaNumber(2), isolation.getIdenticalExponentForVariableIfPossible("y"));
    EXPECT_EQ(AlbaNumber(0), isolation.getIdenticalExponentForVariableIfPossible("z"));
    EXPECT_EQ(AlbaNumber(3), isolation.getIdenticalExponentForVariableIfPossible("a"));
    EXPECT_EQ(AlbaNumber(4), isolation.getIdenticalExponentForVariableIfPossible("b"));
    EXPECT_EQ(AlbaNumber(0), isolation.getIdenticalExponentForVariableIfPossible("c"));
}

TEST(
    IsolationOfOneVariableOnEqualityEquationTest,
    GetIdenticalExponentForVariableIfPossibleWorksOnPolynomialEquationWithMultipleVariableMonomials) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}, {"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}, {"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    EXPECT_EQ(AlbaNumber(1), isolation.getIdenticalExponentForVariableIfPossible("x"));
    EXPECT_EQ(AlbaNumber(2), isolation.getIdenticalExponentForVariableIfPossible("y"));
    EXPECT_EQ(AlbaNumber(0), isolation.getIdenticalExponentForVariableIfPossible("z"));
    EXPECT_EQ(AlbaNumber(3), isolation.getIdenticalExponentForVariableIfPossible("a"));
    EXPECT_EQ(AlbaNumber(4), isolation.getIdenticalExponentForVariableIfPossible("b"));
    EXPECT_EQ(AlbaNumber(0), isolation.getIdenticalExponentForVariableIfPossible("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableOnLeftSideOfEquationWorks) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    Term const expectedIsolatedBLeftSide(Monomial(1, {{"b", 4}}));
    Term const expectedIsolatedBRightSide(Polynomial{
        Monomial(AlbaNumber(-3) / 4, {{"a", 3}}), Monomial(AlbaNumber(1) / 2, {{"y", 2}}),
        Monomial(AlbaNumber(1) / 4, {{"x", 1}})});
    EXPECT_EQ(
        Equation(expectedIsolatedBLeftSide, "=", expectedIsolatedBRightSide),
        isolation.isolateTermWithVariableOnLeftSideOfEquation("b"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableOnRightSideOfEquationWorks) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    Term const expectedIsolatedBLeftSide(Polynomial{
        Monomial(AlbaNumber(-3) / 4, {{"a", 3}}), Monomial(AlbaNumber(1) / 2, {{"y", 2}}),
        Monomial(AlbaNumber(1) / 4, {{"x", 1}})});
    Term const expectedIsolatedBRightSide(Monomial(1, {{"b", 4}}));
    EXPECT_EQ(
        Equation(expectedIsolatedBLeftSide, "=", expectedIsolatedBRightSide),
        isolation.isolateTermWithVariableOnRightSideOfEquation("b"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, GetTermByIsolatingVariableWorks) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    Polynomial const polynomialForX{Monomial(4, {{"b", 4}}), Monomial(3, {{"a", 3}}), Monomial(-2, {{"y", 2}})};
    Polynomial const polynomialForY{
        Monomial(2, {{"b", 4}}), Monomial(AlbaNumber(3) / 2, {{"a", 3}}), Monomial(AlbaNumber(-1) / 2, {{"x", 1}})};
    Polynomial const polynomialForA{
        Monomial(AlbaNumber(-4) / 3, {{"b", 4}}), Monomial(AlbaNumber(2) / 3, {{"y", 2}}),
        Monomial(AlbaNumber(1) / 3, {{"x", 1}})};
    Polynomial const polynomialForB{
        Monomial(AlbaNumber(-3) / 4, {{"a", 3}}), Monomial(AlbaNumber(1) / 2, {{"y", 2}}),
        Monomial(AlbaNumber(1) / 4, {{"x", 1}})};
    Term const expectedTermForX(polynomialForX);
    Term const expectedTermForY(createExpressionIfPossible({polynomialForY, "^", AlbaNumber::createFraction(1, 2)}));
    Term const expectedTermForA(createExpressionIfPossible({polynomialForA, "^", AlbaNumber::createFraction(1, 3)}));
    Term const expectedTermForB(createExpressionIfPossible({polynomialForB, "^", AlbaNumber::createFraction(1, 4)}));
    EXPECT_EQ(expectedTermForX, isolation.getEquivalentTermByIsolatingAVariable("x"));
    EXPECT_EQ(expectedTermForY, isolation.getEquivalentTermByIsolatingAVariable("y"));
    EXPECT_EQ(expectedTermForA, isolation.getEquivalentTermByIsolatingAVariable("a"));
    EXPECT_EQ(expectedTermForB, isolation.getEquivalentTermByIsolatingAVariable("b"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, CanBeIsolatedWorksOnPolynomialEquation) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    EXPECT_TRUE(isolation.canBeIsolated("x"));
    EXPECT_TRUE(isolation.canBeIsolated("y"));
    EXPECT_FALSE(isolation.canBeIsolated("z"));
    EXPECT_TRUE(isolation.canBeIsolated("a"));
    EXPECT_TRUE(isolation.canBeIsolated("b"));
    EXPECT_FALSE(isolation.canBeIsolated("c"));
}

TEST(
    IsolationOfOneVariableOnEqualityEquationTest, CanBeIsolatedWorksOnPolynomialEquationWithMultipleVariableMonomials) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}, {"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}, {"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    EXPECT_TRUE(isolation.canBeIsolated("x"));
    EXPECT_TRUE(isolation.canBeIsolated("y"));
    EXPECT_FALSE(isolation.canBeIsolated("z"));
    EXPECT_TRUE(isolation.canBeIsolated("a"));
    EXPECT_TRUE(isolation.canBeIsolated("b"));
    EXPECT_FALSE(isolation.canBeIsolated("c"));
}

TEST(IsolationOfOneVariableOnEqualityEquationTest, IsolateTermWithVariableWorksOnPolynomialEquation) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}}), Monomial(4, {{"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    Term termWithVariable;
    Term termWithoutVariable;
    Term const expectedTermWithX("x");
    Term const expectedTermWithoutX(
        Polynomial{Monomial(4, {{"b", 4}}), Monomial(3, {{"a", 3}}), Monomial(-2, {{"y", 2}})});
    Term const expectedTermWithY(Monomial(1, {{"y", 2}}));
    Term const expectedTermWithoutY(Polynomial{
        Monomial(2, {{"b", 4}}), Monomial(AlbaNumber(3) / 2, {{"a", 3}}), Monomial(AlbaNumber(-1) / 2, {{"x", 1}})});
    Term const expectedTermWithA(Monomial(1, {{"a", 3}}));
    Term const expectedTermWithoutA(Polynomial{
        Monomial(AlbaNumber(-4) / 3, {{"b", 4}}), Monomial(AlbaNumber(2) / 3, {{"y", 2}}),
        Monomial(AlbaNumber(1) / 3, {{"x", 1}})});
    Term const expectedTermWithB(Monomial(1, {{"b", 4}}));
    Term const expectedTermWithoutB(Polynomial{
        Monomial(AlbaNumber(-3) / 4, {{"a", 3}}), Monomial(AlbaNumber(1) / 2, {{"y", 2}}),
        Monomial(AlbaNumber(1) / 4, {{"x", 1}})});
    isolation.isolateTermWithVariable("x", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithX, termWithVariable);
    EXPECT_EQ(expectedTermWithoutX, termWithoutVariable);
    isolation.isolateTermWithVariable("y", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithY, termWithVariable);
    EXPECT_EQ(expectedTermWithoutY, termWithoutVariable);
    isolation.isolateTermWithVariable("a", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithA, termWithVariable);
    EXPECT_EQ(expectedTermWithoutA, termWithoutVariable);
    isolation.isolateTermWithVariable("b", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithB, termWithVariable);
    EXPECT_EQ(expectedTermWithoutB, termWithoutVariable);
}

TEST(
    IsolationOfOneVariableOnEqualityEquationTest,
    IsolateTermWithVariableWorksOnPolynomialEquationWithMultipleVariableMonomials) {
    Polynomial const leftHandSide{Monomial(1, {{"x", 1}, {"y", 2}})};
    Polynomial const rightHandSide{Monomial(3, {{"a", 3}, {"b", 4}})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    Term termWithVariable;
    Term termWithoutVariable;
    Term const expectedTermWithX("x");
    Term const expectedTermWithoutX(Monomial(3, {{"a", 3}, {"b", 4}, {"y", -2}}));
    Term const expectedTermWithY(Monomial(1, {{"y", 2}}));
    Term const expectedTermWithoutY(Monomial(3, {{"a", 3}, {"b", 4}, {"x", -1}}));
    Term const expectedTermWithA(Monomial(1, {{"a", 3}}));
    Term const expectedTermWithoutA(Monomial(AlbaNumber(1) / 3, {{"b", -4}, {"x", 1}, {"y", 2}}));
    Term const expectedTermWithB(Monomial(1, {{"b", 4}}));
    Term const expectedTermWithoutB(Monomial(AlbaNumber(1) / 3, {{"a", -3}, {"x", 1}, {"y", 2}}));
    isolation.isolateTermWithVariable("x", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithX, termWithVariable);
    EXPECT_EQ(expectedTermWithoutX, termWithoutVariable);
    isolation.isolateTermWithVariable("y", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithY, termWithVariable);
    EXPECT_EQ(expectedTermWithoutY, termWithoutVariable);
    isolation.isolateTermWithVariable("a", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithA, termWithVariable);
    EXPECT_EQ(expectedTermWithoutA, termWithoutVariable);
    isolation.isolateTermWithVariable("b", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithB, termWithVariable);
    EXPECT_EQ(expectedTermWithoutB, termWithoutVariable);
}

TEST(
    IsolationOfOneVariableOnEqualityEquationTest,
    IsolateTermWithVariableWorksOnExpressionWithAdditionAndSubtractionOperation) {
    Term const leftHandSide(Polynomial{Monomial(1, {{"x", 1}, {"y", 2}})});
    Term const rightHandSide(createExpressionIfPossible({2, "^", "z"}));
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    Term termWithVariable;
    Term termWithoutVariable;
    Term const expectedTermWithX("x");
    isolation.isolateTermWithVariable("x", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithX, termWithVariable);
    EXPECT_EQ("((2^z)/1[y^2])", convertToString(termWithoutVariable));
}

TEST(
    IsolationOfOneVariableOnEqualityEquationTest,
    IsolateTermWithVariableWorksOnPolynomialEquationWorksWithExample1UsingDerivatives) {
    Polynomial const leftHandSide{
        Monomial(18, {{"dy/dx", 1}, {"y", 5}}), Monomial(5, {{"dy/dx", 1}, {"y", 4}}), Monomial(-6, {{"x", 5}}),
        Monomial(-2, {{"dy/dx", 1}, {"y", 1}}), Monomial(2, {{}})};
    Polynomial const rightHandSide{Monomial(0, {})};
    Equation const equation(leftHandSide, "=", rightHandSide);
    IsolationOfOneVariableOnEqualityEquation const isolation(equation);

    Term termWithVariable;
    Term termWithoutVariable;
    Polynomial const numerator{Monomial(6, {{"x", 5}}), Monomial(-2, {})};
    Polynomial const denominator{Monomial(18, {{"y", 5}}), Monomial(5, {{"y", 4}}), Monomial(-2, {{"y", 1}})};
    Term const expectedTermWithDerivative("dy/dx");
    Term const expectedTermWithoutDerivative(createExpressionIfPossible({numerator, "/", denominator}));
    isolation.isolateTermWithVariable("dy/dx", termWithVariable, termWithoutVariable);
    EXPECT_EQ(expectedTermWithDerivative, termWithVariable);
    EXPECT_EQ(expectedTermWithoutDerivative, termWithoutVariable);
}

}  // namespace alba::algebra
