#include <Algebra/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra::Factorization {

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenItsSingleMonomial) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenExponentsAreNotDivisible) {
    Polynomial const polynomialToTest{
        Monomial(1, {{"x", 13}}),
        Monomial(1, {{"x", 17}}),
    };

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(
    FactorizationOfIncreasingAndDecreasingExponentFormTest,
    FactorizeIfPossibleIsEmptyWhenSomeVariablesAreDifferentFromStartAndEndMonomials) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(144, {})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(
    FactorizationOfIncreasingAndDecreasingExponentFormTest,
    FactorizeIfPossibleWorksOnQuadraticExpressionWithFirstCoefficientIsNotOne) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(
    FactorizationOfIncreasingAndDecreasingExponentFormTest,
    FactorizeIfPossibleWorksOnQuadraticExpressionWithFractionFirstCoefficients) {
    Polynomial const polynomialToTest{
        Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}), Monomial(AlbaNumber::createFraction(5, 2), {{"x", 1}}),
        Monomial(25, {})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial const polynomialToExpect3{Monomial(AlbaNumber::createFraction(1, 16), {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(
    FactorizationOfIncreasingAndDecreasingExponentFormTest,
    FactorizeIfPossibleWorksOnQuadraticExpressionWithFractionSecondCoefficients) {
    Polynomial const polynomialToTest{
        Monomial(25, {{"x", 2}}), Monomial(AlbaNumber::createFraction(5, 2), {{"x", 1}}),
        Monomial(AlbaNumber::createFraction(1, 16), {})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber::createFraction(1, 4), {})};
    Polynomial const polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber::createFraction(1, 4), {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionExample1) {
    Polynomial const polynomialToTest{
        Monomial(2, {{"x", 2}}), Monomial(-23, {{"x", 1}, {"y", 1}}), Monomial(-39, {{"y", 2}})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-13, {{"y", 1}})};
    Polynomial const polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnCubicExpressionExample1) {
    Polynomial const polynomialToTest{
        Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    Polynomial const polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial const polynomialToExpect3{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(
    FactorizationOfIncreasingAndDecreasingExponentFormTest,
    FactorizeIfPossibleWorksOnQuadraticExpressionWithFirstCoefficientIsOne) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(-4, {})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksBigExponentDifferenceOfSquares) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 64}}), Monomial(-1, {{"y", 16}})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 32}}), Monomial(-1, {{"y", 8}})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 32}}), Monomial(1, {{"y", 8}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksComplicatedPolynomial) {
    Polynomial const polynomialToTest{
        Monomial(2112, {{"x", 4}}), Monomial(-296, {{"x", 3}}), Monomial(-5878, {{"x", 2}}), Monomial(409, {{"x", 1}}),
        Monomial(4095, {})};

    Polynomials polynomialsToVerify;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(4U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    Polynomial const polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial const polynomialToExpect3{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    Polynomial const polynomialToExpect4{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify[3]);
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizePolynomialFormWorks) {
    Polynomial const polynomialToTest{
        Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    AlbaNumbers const coefficients({1, 3, 3, 1});

    Polynomials polynomialsToVerify;
    factorizePolynomialForm(
        polynomialsToVerify, polynomialToTest, coefficients, Monomial::VariablesToExponentsMap{{"x", 1}},
        Monomial::VariablesToExponentsMap{});

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify[2]);
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FixCoefficientsOfFactorsWorks) {
    AlbaNumber aCoefficient1(11);
    AlbaNumber firstRoot1(12);
    AlbaNumber secondRoot1(13);
    AlbaNumber aCoefficient2(35);
    AlbaNumber firstRoot2(1);
    AlbaNumber secondRoot2(AlbaNumber::createFraction(1, 7));

    fixCoefficientsOfFactors(aCoefficient1, firstRoot1, secondRoot1);
    fixCoefficientsOfFactors(aCoefficient2, firstRoot2, secondRoot2);

    EXPECT_DOUBLE_EQ(11, aCoefficient1.getDouble());
    EXPECT_DOUBLE_EQ(12, firstRoot1.getDouble());
    EXPECT_DOUBLE_EQ(13, secondRoot1.getDouble());
    EXPECT_DOUBLE_EQ(5, aCoefficient2.getDouble());
    EXPECT_DOUBLE_EQ(7, firstRoot2.getDouble());
    EXPECT_DOUBLE_EQ(1, secondRoot2.getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, GetMaxAbsoluteValueForRootFindingWorks) {
    AlbaNumbers const coefficients1{1, 2, 3, 4};
    AlbaNumbers const coefficients2{4, 3, 2, 1};

    EXPECT_DOUBLE_EQ(4, getMaxAbsoluteValueForRootFinding(coefficients1).getDouble());
    EXPECT_DOUBLE_EQ(4, getMaxAbsoluteValueForRootFinding(coefficients2).getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, GetCoefficientsInMonomialsWithExponentsInOrderWorks) {
    Polynomial const polynomial1{
        Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    Monomials const monomials1{
        Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial const polynomial2{
        Monomial(1, {{"y", 3}}), Monomial(3, {{"y", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    Monomials const monomials2{
        Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(1, {})};

    AlbaNumbers const coefficients1(getCoefficientsInMonomialsWithExponentsInOrder(Polynomial{}, Monomials{}));
    AlbaNumbers coefficients2(getCoefficientsInMonomialsWithExponentsInOrder(polynomial1, monomials1));
    AlbaNumbers coefficients3(getCoefficientsInMonomialsWithExponentsInOrder(polynomial2, monomials2));

    EXPECT_TRUE(coefficients1.empty());
    ASSERT_EQ(4U, coefficients2.size());
    EXPECT_DOUBLE_EQ(1, coefficients2[0].getDouble());
    EXPECT_DOUBLE_EQ(3, coefficients2[1].getDouble());
    EXPECT_DOUBLE_EQ(3, coefficients2[2].getDouble());
    EXPECT_DOUBLE_EQ(1, coefficients2[3].getDouble());
    ASSERT_EQ(4U, coefficients3.size());
    EXPECT_DOUBLE_EQ(0, coefficients3[0].getDouble());
    EXPECT_DOUBLE_EQ(0, coefficients3[1].getDouble());
    EXPECT_DOUBLE_EQ(3, coefficients3[2].getDouble());
    EXPECT_DOUBLE_EQ(1, coefficients3[3].getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, CalculatePolynomialRootsWorks) {
    AlbaNumbers const quadraticCoefficients{1, 2, 1};
    AlbaNumbers const cubicCoefficients{1, 3, 3, 1};

    AlbaNumbers quadraticRoots(calculatePolynomialRoots(quadraticCoefficients));
    AlbaNumbers cubicRoots(calculatePolynomialRoots(cubicCoefficients));

    ASSERT_EQ(2U, quadraticRoots.size());
    EXPECT_DOUBLE_EQ(-1, quadraticRoots[0].getDouble());
    EXPECT_DOUBLE_EQ(-1, quadraticRoots[1].getDouble());
    ASSERT_EQ(3U, cubicRoots.size());
    EXPECT_DOUBLE_EQ(-1, cubicRoots[0].getDouble());
    EXPECT_DOUBLE_EQ(-1, cubicRoots[1].getDouble());
    EXPECT_DOUBLE_EQ(-1, cubicRoots[2].getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, CalculatePolynomialRootsUsingBrentMethodWorks) {
    AlbaNumbers const cubicCoefficients{1, 3, 3, 1};
    AlbaNumbers const previousDerivativeCoefficients{3, 6, 3};

    AlbaNumbers roots(calculatePolynomialRootsUsingBrentMethod(previousDerivativeCoefficients, cubicCoefficients));

    ASSERT_EQ(1U, roots.size());
    EXPECT_DOUBLE_EQ(-1, roots[0].getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, GetDerivativeCoefficientsWorks) {
    AlbaNumbers const cubicCoefficients{1, 3, 3, 1};

    AlbaNumbers derivativeCoefficients(getDerivativeCoefficients(cubicCoefficients));

    ASSERT_EQ(3U, derivativeCoefficients.size());
    EXPECT_DOUBLE_EQ(3, derivativeCoefficients[0].getDouble());
    EXPECT_DOUBLE_EQ(6, derivativeCoefficients[1].getDouble());
    EXPECT_DOUBLE_EQ(3, derivativeCoefficients[2].getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, GetMonomialsWithExponentsInOrderWorks) {
    Monomials monomialsToVerify(getMonomialsWithExponentsInOrder(3, Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})));

    ASSERT_EQ(4U, monomialsToVerify.size());
    EXPECT_EQ(Monomial(1, {{"x", 3}}), monomialsToVerify[0]);
    EXPECT_EQ(Monomial(1, {{"x", 2}, {"y", 1}}), monomialsToVerify[1]);
    EXPECT_EQ(Monomial(1, {{"x", 1}, {"y", 2}}), monomialsToVerify[2]);
    EXPECT_EQ(Monomial(1, {{"y", 3}}), monomialsToVerify[3]);
}

TEST(
    FactorizationOfIncreasingAndDecreasingExponentFormTest,
    FactorizeIncreasingAndDecreasingExponentsFormWorksWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial const& polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
}

TEST(
    FactorizationOfIncreasingAndDecreasingExponentFormTest,
    FactorizeIncreasingAndDecreasingExponentsFormWorksWhenItCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, CalculateMaxExponentDivisorWorks) {
    EXPECT_EQ(0, calculateMaxExponentDivisor(Monomial(1, {}), Monomial(1, {})));
    EXPECT_EQ(7, calculateMaxExponentDivisor(Monomial(1, {{"x", 7}}), Monomial(1, {{"y", 7}})));
    EXPECT_EQ(7, calculateMaxExponentDivisor(Monomial(1, {{"x", 3}}), Monomial(1, {{"y", 7}})));
    EXPECT_EQ(9, calculateMaxExponentDivisor(Monomial(1, {{"x", 9}}), Monomial(1, {{"y", 7}})));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, AreAllMonomialsFoundInMonomialsWithExponentsInOrderWorks) {
    Monomials const monomials1{Monomial(2, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(4, {})};
    Monomials const monomials2{Monomial(6, {{"y", 2}}), Monomial(7, {{"y", 1}}), Monomial(8, {})};
    Monomials const monomials3{Monomial(1, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Monomials const monomials4{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 1}}), Monomial(1, {})};

    EXPECT_TRUE(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials1, monomials1));
    EXPECT_FALSE(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials1, monomials2));
    EXPECT_TRUE(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials1, monomials3));
    EXPECT_FALSE(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials1, monomials4));
}

}  // namespace alba::algebra::Factorization
