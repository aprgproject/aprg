#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(PolynomialOverPolynomialTest, ConstructionWorks) {
    PolynomialOverPolynomial const actual1;
    PolynomialOverPolynomial const actual2(Polynomial{}, Polynomial{});
    PolynomialOverPolynomial const actual3(Polynomial{Monomial(10, {})}, Polynomial{Monomial(100, {})});

    EXPECT_EQ(Polynomial(), actual1.getNumerator());
    EXPECT_EQ(Polynomial(), actual1.getDenominator());
    EXPECT_EQ(Polynomial(), actual2.getNumerator());
    EXPECT_EQ(Polynomial(), actual2.getDenominator());
    EXPECT_EQ(Polynomial{Monomial(10, {})}, actual3.getNumerator());
    EXPECT_EQ(Polynomial{Monomial(100, {})}, actual3.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksWithZeroOverDouble) {
    Polynomial const numerator(createPolynomialFromNumber(0));
    Polynomial const denominator(createPolynomialFromNumber(1.17157287525381));
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    EXPECT_EQ(Polynomial(), polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(createPolynomialFromNumber(1.17157287525381), polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksWithZeroOverZero) {
    Polynomial const numerator(createPolynomialFromNumber(0));
    Polynomial const denominator(createPolynomialFromNumber(0));
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    EXPECT_EQ(Polynomial(), polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(Polynomial(), polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnConvertingFractionCoefficientsToInteger) {
    Polynomial const numerator{
        Monomial(AlbaNumber::createFraction(1, 2), {{"x", 1}}), Monomial(AlbaNumber::createFraction(1, 3), {{"y", 1}})};
    Polynomial const denominator{
        Monomial(AlbaNumber::createFraction(1, 5), {{"x", 1}}),
        Monomial(AlbaNumber::createFraction(1, 10), {{"y", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(15, {{"x", 1}}), Monomial(10, {{"y", 1}})};
    Polynomial const denominatorToExpect{Monomial(6, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnRemovingCommonFactorInCoefficients) {
    Polynomial const numerator{Monomial(0.3, {}), Monomial(2, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial const denominator{Monomial(2, {{"y", 1}}), Monomial(2, {{"z", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}}), Monomial(0.15, {})};
    Polynomial const denominatorToExpect{Monomial(1, {{"y", 1}}), Monomial(1, {{"z", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnConvertingNegativeExponentsToPositive) {
    Polynomial const numerator{Monomial(1, {{"x", 1}, {"y", -1}}), Monomial(2, {{"x", -1}, {"y", 1}})};
    Polynomial const denominator{Monomial(3, {{"y", 1}}), Monomial(4, {{"z", -1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(1, {{"x", 2}, {"z", 1}}), Monomial(2, {{"y", 2}, {"z", 1}})};
    Polynomial const denominatorToExpect{
        Monomial(3, {{"x", 1}, {"y", 2}, {"z", 1}}), Monomial(4, {{"x", 1}, {"y", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnConvertingNegativeExponentsToPositiveAndDenominatorIsOne) {
    Polynomial const numerator{Monomial(1, {}), Monomial(2, {{"x", -1}})};
    Polynomial const denominator{Monomial(1, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial const denominatorToExpect{Monomial(1, {{"x", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCommonNegativeSignInNumerator) {
    Polynomial const numerator{Monomial(-1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    Polynomial const denominator{Monomial(-1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    Polynomial const denominatorToExpect{Monomial(1, {{"a", 1}}), Monomial(-1, {{"b", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCommonNegativeSignInDenominator) {
    Polynomial const numerator{Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    Polynomial const denominator{Monomial(-1, {{"a", 1}}), Monomial(-1, {{"b", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    Polynomial const denominatorToExpect{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCommonNegativeSignInNumeratorAndDenominator) {
    Polynomial const numerator{Monomial(-1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    Polynomial const denominator{Monomial(-1, {{"a", 1}}), Monomial(-1, {{"b", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    Polynomial const denominatorToExpect{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCancellingFactorsExample1) {
    Polynomial const numerator{Monomial(4, {{"x", 2}}), Monomial(-9, {{"y", 2}})};
    Polynomial const denominator{Monomial(2, {{"x", 1}}), Monomial(-3, {{"y", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    Polynomial const denominatorToExpect{Monomial(1, {})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCancellingFactorsExample2) {
    Polynomial const numerator{Monomial(2, {{"x", 2}}), Monomial(-14, {{"x", 1}}), Monomial(20, {})};
    Polynomial const denominator{Monomial(-2, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(-6, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(-2, {{"x", 1}}), Monomial(10, {})};
    Polynomial const denominatorToExpect{Monomial(2, {{"x", 1}}), Monomial(-3, {})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCancellingFactorsExample3) {
    Polynomial const numerator{Monomial(1, {{"a", 1}, {"b", -1}}), Monomial(1, {{"c", 1}, {"d", -1}})};
    Polynomial const denominator{Monomial(1, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(1, {{"a", 1}, {"d", 1}}), Monomial(1, {{"b", 1}, {"c", 1}})};
    Polynomial const denominatorToExpect{Monomial(1, {{"b", 1}, {"d", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCancellingFactorsExample4) {
    Polynomial const numerator{
        Monomial(15, {{"a", 1}, {"b", 1}}), Monomial(-20, {{"a", 1}}), Monomial(-21, {{"b", 1}}), Monomial(28, {})};
    Polynomial const denominator{Monomial(21, {}), Monomial(-1, {{"a", 1}}), Monomial(-10, {{"a", 2}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial const numeratorToExpect{Monomial(3, {{"b", 1}}), Monomial(-4, {})};
    Polynomial const denominatorToExpect{Monomial(-2, {{"a", 1}}), Monomial(-3, {})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, DivideWithNoRemainder) {
    Polynomial const numerator{
        Monomial(3, {{"x", 3}}), Monomial(-4, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 1}, {"y", 2}}),
        Monomial(6, {{"y", 3}})};
    Polynomial const denominator{Monomial(1, {{"x", 2}}), Monomial(-2, {{"x", 1}, {"y", 1}}), Monomial(3, {{"y", 2}})};
    PolynomialOverPolynomial const polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(polynomialOverPolynomial.divide());

    Polynomial const quotientToExpect{Monomial(3, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial const remainderToExpect{};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, DivideOnAQuarticWithNoRemainder) {
    Polynomial const numerator{
        Monomial(2112, {{"x", 4}}), Monomial(-296, {{"x", 3}}), Monomial(-5878, {{"x", 2}}), Monomial(409, {{"x", 1}}),
        Monomial(4095, {})};
    Polynomial const denominator{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    PolynomialOverPolynomial const polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(polynomialOverPolynomial.divide());

    Polynomial const quotientToExpect{
        Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};
    Polynomial const remainderToExpect{};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, DivideWithRemainder) {
    Polynomial const numerator{Monomial(5, {{"x", 3}}), Monomial(-14, {{"x", 1}}), Monomial(3, {})};
    Polynomial const denominator{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    PolynomialOverPolynomial const polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(polynomialOverPolynomial.divide());

    Polynomial const quotientToExpect{Monomial(5, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(6, {})};
    Polynomial const remainderToExpect{Monomial(15, {})};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, IsEmptyWorks) {
    PolynomialOverPolynomial const actual1;
    PolynomialOverPolynomial const actual2(Polynomial{}, Polynomial{});
    PolynomialOverPolynomial const actual3(Polynomial{}, (Polynomial{Monomial(100, {})}));
    PolynomialOverPolynomial const actual4((Polynomial{Monomial(10, {})}), (Polynomial{Monomial(100, {})}));

    EXPECT_TRUE(actual1.isEmpty());
    EXPECT_TRUE(actual2.isEmpty());
    EXPECT_FALSE(actual3.isEmpty());
    EXPECT_FALSE(actual4.isEmpty());
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWorksWithZeroOverDouble) {
    Polynomial const numerator(createPolynomialFromNumber(0));
    Polynomial const denominator(createPolynomialFromNumber(1.17157287525381));
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(
        polynomialOverPolynomial.simplifyAndDivide());

    EXPECT_EQ(Polynomial(), quotientAndRemainder.quotient);
    EXPECT_EQ(Polynomial(), quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWorksWithZeroOverZero) {
    Polynomial const numerator(createPolynomialFromNumber(0));
    Polynomial const denominator(createPolynomialFromNumber(0));
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(
        polynomialOverPolynomial.simplifyAndDivide());

    EXPECT_EQ(Polynomial(), quotientAndRemainder.quotient);
    EXPECT_EQ(Polynomial(), quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWorksWithNoRemainder) {
    Polynomial const numerator{
        Monomial(3, {{"x", 3}}), Monomial(-4, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 1}, {"y", 2}}),
        Monomial(6, {{"y", 3}})};
    Polynomial const denominator{Monomial(1, {{"x", 2}}), Monomial(-2, {{"x", 1}, {"y", 1}}), Monomial(3, {{"y", 2}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(
        polynomialOverPolynomial.simplifyAndDivide());

    Polynomial const quotientToExpect{Monomial(3, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial const remainderToExpect{};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWorksOnAQuarticWithNoRemainder) {
    Polynomial const numerator{
        Monomial(2112, {{"x", 4}}), Monomial(-296, {{"x", 3}}), Monomial(-5878, {{"x", 2}}), Monomial(409, {{"x", 1}}),
        Monomial(4095, {})};
    Polynomial const denominator{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(
        polynomialOverPolynomial.simplifyAndDivide());

    Polynomial const quotientToExpect{
        Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};
    Polynomial const remainderToExpect{};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWorksWithRemainder) {
    Polynomial const numerator{
        Monomial(5, {{"x", 3}}), Monomial(-8, {{"x", 2}}), Monomial(6, {{"x", 1}}), Monomial(4, {})};
    Polynomial const denominator{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder const quotientAndRemainder(
        polynomialOverPolynomial.simplifyAndDivide());

    Polynomial const quotientToExpect{Monomial(5, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(10, {})};
    Polynomial const remainderToExpect{Monomial(24, {})};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

}  // namespace alba::algebra
