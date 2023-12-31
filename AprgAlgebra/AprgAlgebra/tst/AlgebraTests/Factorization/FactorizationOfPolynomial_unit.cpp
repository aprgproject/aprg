#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba::algebra::Factorization {

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialIfPossibleIsEmptyWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeCommonMonomialIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialIfPossibleIsEmptyWhenItsOneMonomial) {
    Polynomial const polynomialToTest{Monomial(7, {{"x", 7}})};

    Polynomials polynomialsToVerify;
    factorizeCommonMonomialIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialIfPossibleWorksWhenGettingTheGcfMonomial) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify;
    factorizeCommonMonomialIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial const polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, PutFactorizedPolynomialsIfPossibleWorksAtDefault) {
    Polynomial const polynomial{Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(0.56789, {{"x", 3}})};
    Polynomials const polynomials{polynomial};

    Polynomials result;
    putFactorizedPolynomialsIfPossible(result, polynomials);

    ASSERT_EQ(1U, result.size());
    EXPECT_EQ(polynomial, result[0]);
}

TEST(FactorizationOfPolynomialsTest, PutFactorizedPolynomialsIfPossibleWorksWhenFlagIsSet) {
    ConfigurationDetails configurationDetails(getDefaultConfigurationDetails<ConfigurationDetails>());
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Polynomial const polynomial{Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(0.56789, {{"x", 3}})};
    Polynomials const polynomials{polynomial};

    Polynomials result;
    putFactorizedPolynomialsIfPossible(result, polynomials);

    EXPECT_TRUE(result.empty());
}

TEST(FactorizationOfPolynomialsTest, CommonConstantCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(4, {{"x", 1}}), Monomial(20, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(4, {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, CommonMonomialCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial const polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfSquaresCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfSquaresInReverseCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(-9, {{"x", 8}, {"y", 2}}), Monomial(16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(-1, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfSquaresWithNegativeExponentsCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", -4}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"z", -4}})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(+4, {})};
    Polynomial const polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(-4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfSquaresWithBigExponent) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 64}}), Monomial(-1, {{"y", 16}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(5U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 32}}), Monomial(1, {{"y", 8}})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 16}}), Monomial(1, {{"y", 4}})};
    Polynomial const polynomialToExpect3{Monomial(1, {{"x", 8}}), Monomial(1, {{"y", 2}})};
    Polynomial const polynomialToExpect4{Monomial(1, {{"x", 4}}), Monomial(1, {{"y", 1}})};
    Polynomial const polynomialToExpect5{Monomial(1, {{"x", 4}}), Monomial(-1, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify[3]);
    EXPECT_EQ(polynomialToExpect5, polynomialsToVerify[4]);
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfCubesCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfCubesInReverseCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(-1, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial const polynomialToExpect3{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfCubesWithNegativeExponentsCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(27, {{"x", 3}}), Monomial(-8, {{"y", -3}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"y", -3}})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 1}, {"y", 1}}), Monomial(-2, {})};
    Polynomial const polynomialToExpect3{
        Monomial(9, {{"x", 2}, {"y", 2}}), Monomial(6, {{"x", 1}, {"y", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, SumOfCubesCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, SumOfCubesInReverseCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(-1, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect3{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, SumOfCubesWithNegativeExponentsCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(27, {{"x", 3}}), Monomial(8, {{"y", -3}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"y", -3}})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 1}, {"y", 1}}), Monomial(2, {})};
    Polynomial const polynomialToExpect3{
        Monomial(9, {{"x", 2}, {"y", 2}}), Monomial(-6, {{"x", 1}, {"y", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionWithFirstCoefficientIsOne) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(-4, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionWithFirstCoefficientIsNotOne) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionWithFractionFirstCoefficients) {
    Polynomial const polynomialToTest{
        Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}), Monomial(AlbaNumber::createFraction(5, 2), {{"x", 1}}),
        Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(AlbaNumber::createFraction(1, 16), {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial const polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionWithFractionSecondCoefficients) {
    Polynomial const polynomialToTest{
        Monomial(25, {{"x", 2}}), Monomial(AlbaNumber::createFraction(5, 2), {{"x", 1}}),
        Monomial(AlbaNumber::createFraction(1, 16), {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(AlbaNumber::createFraction(1, 16), {})};
    Polynomial const polynomialToExpect2{Monomial(20, {{"x", 1}}), Monomial(1, {})};
    Polynomial const polynomialToExpect3{Monomial(20, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionExample1) {
    Polynomial const polynomialToTest{
        Monomial(2, {{"x", 2}}), Monomial(-23, {{"x", 1}, {"y", 1}}), Monomial(-39, {{"y", 2}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-13, {{"y", 1}})};
    Polynomial const polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, CubicExpressionExample1) {
    Polynomial const polynomialToTest{
        Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    Polynomial const polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial const polynomialToExpect3{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, FactorizeWorksBySplittingByPolynomialDegree) {
    Polynomial const polynomialToTest{Monomial(25, {{"x", 2}}), Monomial(30, {{"x", 1}, {"y", 1}}),
                                      Monomial(9, {{"y", 2}}),  Monomial(15, {{"x", 1}}),
                                      Monomial(9, {{"y", 1}}),  Monomial(2, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(1, {})};
    Polynomial const polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, FactorizeWorksBySplittingByDivisibilityOfExponents) {
    Polynomial const polynomialToTest{
        Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(-1, {{"z", 2}}),
        Monomial(-2, {{"y", 1}, {"z", 1}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(1, {{"z", 1}})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {{"z", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, FactorizeWorksBySplittingByFirstVariable) {
    Polynomial const polynomialToTest{
        Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(-1, {{"a", 1}, {"y", 1}}), Monomial(-1, {{"b", 1}, {"y", 1}}),
        Monomial(1, {{"b", 1}, {"x", 1}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationOfPolynomialsTest, AXPlusBTimesCXPlusD) {
    Polynomial const polynomialToTest{
        Monomial(1, {{"a", 1}, {"c", 1}, {"x", 2}}), Monomial(1, {{"a", 1}, {"d", 1}, {"x", 1}}),
        Monomial(1, {{"b", 1}, {"c", 1}, {"x", 1}}), Monomial(1, {{"b", 1}, {"d", 1}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"c", 1}, {"x", 1}}), Monomial(1, {{"d", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(
    FactorizationOfPolynomialsTest,
    FactorizeWorksAndDoesNotContinueWhenShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValueIsDefault) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(-5, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-2.23606797749979, {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(+2.23606797749979, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(
    FactorizationOfPolynomialsTest,
    FactorizeWorksAndDoesNotContinueWhenShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValueIsTrue) {
    ConfigurationDetails configurationDetails(getDefaultConfigurationDetails<ConfigurationDetails>());
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Polynomial const polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(-5, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect{Monomial(1, {{"x", 2}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify[0]);
}

TEST(FactorizationOfPolynomialsTest, Example1) {
    Polynomial const polynomialToTest{Monomial(2, {{"x", 3}}), Monomial(28, {{"x", 2}}), Monomial(98, {{"x", 1}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(2, {{"x", 1}})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Polynomial const polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, Example2) {
    Polynomial const polynomialToTest{
        Monomial(4, {{"x", 3}}), Monomial(-12, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(3, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial const polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(-1, {})};
    Polynomial const polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(-3, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, Example3) {
    Polynomial const polynomialToTest{
        Monomial(3, {{"x", 4}}), Monomial(-32, {{"x", 2}}), Monomial(-80, {{"x", 1}}), Monomial(-12, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(4U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(0.160246899469294, {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-4.16024689946928, {})};
    Polynomial const polynomialToExpect3{Monomial(3, {})};
    Polynomial const polynomialToExpect4{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(6, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify[3]);
}

TEST(FactorizationOfPolynomialsTest, PolynomialWithPositiveInfinityNumber) {
    Polynomial const polynomialToTest{Monomial(4, {{"x", 1}}), Monomial(ALBA_NUMBER_POSITIVE_INFINITY, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect{Monomial(4, {{"x", 1}}), Monomial(ALBA_NUMBER_POSITIVE_INFINITY, {})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify[0]);
}

TEST(FactorizationOfPolynomialsTest, FactorizePolynomialsWorksWhenPolynomialsCannotBeFactorized) {
    Polynomial const polynomial1{Monomial(1, {{"x", 1}}), Monomial(11, {})};
    Polynomial const polynomial2{Monomial(1, {{"y", 1}}), Monomial(13, {})};
    Polynomial const polynomial3{Monomial(1, {{"z", 1}}), Monomial(17, {})};
    Polynomials const polynomials{polynomial1, polynomial2, polynomial3};

    Polynomials polynomialsToVerify(factorizePolynomials(polynomials));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const& polynomialToExpect1(polynomial1);
    Polynomial const& polynomialToExpect2(polynomial2);
    Polynomial const& polynomialToExpect3(polynomial3);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationOfPolynomialsTest, FactorizePolynomialsWorksWhenPolynomialsCanBeFactorized) {
    Polynomial const polynomial1{Monomial(1, {{"x", 2}}), Monomial(-1, {})};
    Polynomial const polynomial2{Monomial(1, {{"y", 2}}), Monomial(-1, {})};
    Polynomials const polynomials{polynomial1, polynomial2};

    Polynomials polynomialsToVerify(factorizePolynomials(polynomials));

    ASSERT_EQ(4U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial const polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial const polynomialToExpect3{Monomial(1, {{"y", 1}}), Monomial(1, {})};
    Polynomial const polynomialToExpect4{Monomial(1, {{"y", 1}}), Monomial(-1, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify[3]);
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialWorksWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeCommonMonomial(polynomialToTest));

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial const& polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialWorksWhenItCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorizeCommonMonomial(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial const polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

}  // namespace alba::algebra::Factorization
