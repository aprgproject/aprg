#include <Algebra/Constructs/PolynomialRaiseToAnUnsignedInt.hpp>

#include <gtest/gtest.h>

namespace alba::algebra {

TEST(PolynomialRaiseToAnUnsignedIntTest, GetBaseWorks) {
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToAnUnsignedInt.getBase());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, ConstructionWorks) {
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(1, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithCommonMonomialAndFactorsButExponentIsStillOneWorks) {
    Polynomial const polynomial{Monomial(5, {{"x", 1}}), Monomial(-20, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(1, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectSquare) {
    Polynomial const polynomial{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(4, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial const expectedBase{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(2, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectSquareWithNegativeConstant) {
    Polynomial const polynomial{Monomial(-7, {{"x", 2}}), Monomial(-28, {{"x", 1}}), Monomial(-28, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial const& expectedBase(polynomial);
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(1, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectSquareAndCommonFactor) {
    Polynomial const polynomial{
        Monomial(4, {{"x", 6}, {"y", 2}}), Monomial(16, {{"x", 5}, {"y", 2}}), Monomial(16, {{"x", 4}, {"y", 2}})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial const expectedBase{Monomial(2, {{"x", 3}, {"y", 1}}), Monomial(4, {{"x", 2}, {"y", 1}})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(2, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectCube) {
    Polynomial const polynomial{
        Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial const expectedBase{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(3, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectCubeAndCommonFactor) {
    Polynomial const polynomial{
        Monomial(8, {{"x", 3}}), Monomial(24, {{"x", 2}}), Monomial(24, {{"x", 1}}), Monomial(8, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial const expectedBase{Monomial(2, {{"x", 1}}), Monomial(2, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(3, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectSquaresAndPerfect4thPowerAndCommonFactor) {
    Polynomial const commonFactor{Monomial(256, {{"y", 4}})};
    Polynomial perfectSquare{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    perfectSquare.raiseToUnsignedInteger(2);
    Polynomial perfect4thPower{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    perfect4thPower.raiseToUnsignedInteger(4);
    Polynomial polynomialToTest(commonFactor);
    polynomialToTest.multiplyPolynomial(perfectSquare);
    polynomialToTest.multiplyPolynomial(perfect4thPower);
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomialToTest);

    Polynomial const expectedBase{
        Monomial(16, {{"x", 3}, {"y", 2}}), Monomial(160, {{"x", 2}, {"y", 2}}), Monomial(512, {{"x", 1}, {"y", 2}}),
        Monomial(512, {{"y", 2}})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(2, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, GetExponentWorks) {
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_EQ(1, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, IsExponentOneWorks) {
    Polynomial const polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt const polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_TRUE(polynomialRaiseToAnUnsignedInt.isExponentOne());
}

}  // namespace alba::algebra
