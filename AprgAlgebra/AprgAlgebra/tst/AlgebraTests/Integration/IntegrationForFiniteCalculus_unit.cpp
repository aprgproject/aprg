#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(IntegrationForFiniteCalculusTest, IntegrateConstantWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");

    EXPECT_EQ(Monomial(5, {{"x", 1}}), integrationForX.integrateConstant(Constant(5)));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateVariableWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");

    Polynomial const polynomialToVerify1(integrationForX.integrateVariable(Variable("x")));
    Polynomial const polynomialToVerify2(integrationForX.integrateVariable(Variable("y")));

    Polynomial const expectedPolynomial01{
        Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})};
    Polynomial const expectedPolynomial02{Monomial(1, {{"x", 1}, {"y", 1}})};
    EXPECT_EQ(expectedPolynomial01, polynomialToVerify1);
    EXPECT_EQ(expectedPolynomial02, polynomialToVerify2);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForTerm) {
    IntegrationForFiniteCalculus const integrationForX("x");
    Term const termToTest(5);

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(termToTest));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForConstant) {
    IntegrationForFiniteCalculus const integrationForX("x");

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(Constant(5)));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForVariable) {
    IntegrationForFiniteCalculus const integrationForX("x");

    Term const termToVerify1(integrationForX.integrate(Variable("x")));
    Term const termToVerify2(integrationForX.integrate(Variable("y")));

    Term const termToExpect1(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term const termToExpect2(Monomial(1, {{"x", 1}, {"y", 1}}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForMonomial) {
    IntegrationForFiniteCalculus const integrationForX("x");

    Term const termToVerify1(integrationForX.integrate(Monomial(1, {{"x", 1}})));
    Term const termToVerify2(integrationForX.integrate(Monomial(1, {{"x", 2}})));
    Term const termToVerify3(integrationForX.integrate(Monomial(2, {{"x", 1}, {"y", 3}})));

    Term const termToExpect1(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term const termToExpect2(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}), Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    Term const termToExpect3(Polynomial{Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(-1, {{"x", 1}, {"y", 3}})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForPolynomial) {
    IntegrationForFiniteCalculus const integrationForX("x");
    Polynomial const polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};

    Term const termToVerify(integrationForX.integrate(polynomial));

    Term const termToExpect(Polynomial{
        Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})});
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForExpression) {
    IntegrationForFiniteCalculus const integrationForX("x");
    Expression const expression1(createExpressionIfPossible({"x"}));
    Expression const expression2(createExpressionIfPossible({5, "^", "x"}));
    Expression const expression3(createExpressionIfPossible({5, "^", Monomial(1, {{"x", 2}})}));

    Term const termToVerify(integrationForX.integrate(expression3));

    Term const termToExpect1(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term const termToExpect2(createExpressionIfPossible({5, "^", "x", "/", 4}));
    EXPECT_EQ(termToExpect1, integrationForX.integrate(expression1));
    EXPECT_EQ(termToExpect2, integrationForX.integrate(expression2));
    ASSERT_TRUE(termToVerify.isConstant());
    EXPECT_TRUE(termToVerify.getAsNumber().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForFunction) {
    IntegrationForFiniteCalculus const integrationForX("x");

    Term const termToVerify(alba::algebra::IntegrationForFiniteCalculus::integrate(sin("x")));

    ASSERT_TRUE(termToVerify.isConstant());
    EXPECT_TRUE(termToVerify.getAsNumber().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksWithTermRaiseToTerm) {
    IntegrationForFiniteCalculus const integrationForX("x");
    Term const termToTest1(createExpressionIfPossible({"n", "^", "n"}));
    Term const termToTest2(createExpressionIfPossible({"n", "^", "x"}));
    Term const termToTest3(createExpressionIfPossible({"x", "^", "n"}));
    Term const termToTest4(createExpressionIfPossible({"x", "^", "x"}));

    Term const termToVerify1(integrationForX.integrate(termToTest1));
    Term const termToVerify2(integrationForX.integrate(termToTest2));
    Term const termToVerify3(integrationForX.integrate(termToTest3));
    Term const termToVerify4(integrationForX.integrate(termToTest4));

    Term const nMinusOne(Polynomial{Monomial(1, {{"n", 1}}), Monomial(-1, {})});
    Term const termToExpect1(createExpressionIfPossible({"n", "^", "n", "*", "x"}));
    Term const termToExpect2(createExpressionIfPossible({"n", "^", "x", "/", nMinusOne}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_TRUE(isNan(termToVerify3));
    EXPECT_TRUE(isNan(termToVerify4));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWithPlusCWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");

    Term const termToVerify(integrationForX.integrateWithPlusC(Constant(5)));

    Term const termToExpect(Polynomial{Monomial(1, {{C, 1}}), Monomial(5, {{"x", 1}})});
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateAtDefiniteValuesWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");

    EXPECT_EQ(Term(9), integrationForX.integrateAtDefiniteValues("x", 4, 6));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateTermWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");
    Polynomial const polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Expression const expression(createExpressionIfPossible({5, "^", "x"}));

    Term const termToVerify1(integrationForX.integrateTerm(5));
    Term const termToVerify2(integrationForX.integrateTerm("x"));
    Term const termToVerify3(integrationForX.integrateTerm(Monomial(1, {{"x", 2}})));
    Term const termToVerify4(integrationForX.integrateTerm(polynomial));
    Term const termToVerify5(integrationForX.integrateTerm(expression));
    Term const termToVerify6(integrationForX.integrateTerm(sin("x")));

    Term const termToExpect1(Monomial(5, {{"x", 1}}));
    Term const termToExpect2(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term const termToExpect3(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}), Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    Term const termToExpect4(Polynomial{
        Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})});
    Term const termToExpect5(createExpressionIfPossible({5, "^", x, "/", 4}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    ASSERT_TRUE(termToVerify6.isConstant());
    EXPECT_TRUE(termToVerify6.getAsNumber().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateMonomialWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");

    Term const termToVerify1(integrationForX.integrateMonomial(Monomial(1, {{"x", 1}})));
    Term const termToVerify2(integrationForX.integrateMonomial(Monomial(1, {{"x", 2}})));
    Term const termToVerify3(integrationForX.integrateMonomial(Monomial(2, {{"x", 1}, {"y", 3}})));
    Term const termToVerify4(integrationForX.integrateMonomial(Monomial(1, {{"x", -3}})));
    Term const termToVerify5(integrationForX.integrateMonomial(Monomial(5, {{"x", -1}, {"y", 4}})));

    Term const termToExpect1(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term const termToExpect2(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}), Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    Term const termToExpect3(Polynomial{Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(-1, {{"x", 1}, {"y", 3}})});
    Term const termToExpect5(createExpressionIfPossible({Monomial(5, {{"y", 4}}), "*", harmonicNumber("x")}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    ASSERT_TRUE(termToVerify4.isConstant());
    EXPECT_TRUE(termToVerify4.getAsNumber().isNotANumber());
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(IntegrationForFiniteCalculusTest, IntegratePolynomialWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");
    Polynomial const polynomial1{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};

    Term const termToVerify(integrationForX.integratePolynomial(polynomial1));

    Polynomial const expectedPolynomial{
        Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})};
    Term const termToExpect(expectedPolynomial);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateExpressionWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");
    Expression const expression1(createExpressionIfPossible({x}));
    Expression const expression2(createExpressionIfPossible({5, "^", "x"}));
    Expression const expression3(createExpressionIfPossible({5, "^", Monomial(1, {{"x", 2}})}));

    Term const termToVerify1(integrationForX.integrateExpression(expression1));
    Term const termToVerify2(integrationForX.integrateExpression(expression2));
    Term const termToVerify3(integrationForX.integrateExpression(expression3));

    Term const termToExpect1(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term const termToExpect2(createExpressionIfPossible({5, "^", "x", "/", 4}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    ASSERT_TRUE(termToVerify3.isConstant());
    EXPECT_TRUE(termToVerify3.getAsNumber().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateFunctionWorks) {
    IntegrationForFiniteCalculus const integrationForX("x");

    Term const termToVerify(alba::algebra::IntegrationForFiniteCalculus::integrateFunction(sin("x")));
    ASSERT_TRUE(termToVerify.isConstant());
    EXPECT_TRUE(termToVerify.getAsNumber().isNotANumber());
}

}  // namespace alba::algebra
