#include <Algebra/Constructs/RationalizeTermOverTerm.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(RationalizeTermOverTermTest, ConstructionWorks) {
    RationalizeTermOverTerm const rationalizeTermOverTerm1;
    RationalizeTermOverTerm const rationalizeTermOverTerm2("x", "y");

    EXPECT_TRUE(rationalizeTermOverTerm1.getNumerator().isEmpty());
    EXPECT_TRUE(rationalizeTermOverTerm1.getDenominator().isEmpty());
    EXPECT_EQ(Term("x"), rationalizeTermOverTerm2.getNumerator());
    EXPECT_EQ(Term("y"), rationalizeTermOverTerm2.getDenominator());
}

TEST(
    RationalizeTermOverTermTest, RationalizeNumeratorWorksForPolynomialOverPolynomialWithSquareRootWithPlusSecondTerm) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term const expectedDenominator(
        Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(
    RationalizeTermOverTermTest,
    RationalizeNumeratorWorksForPolynomialOverPolynomialWithSquareRootWithMinusSecondTerm) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term const expectedDenominator(
        Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForPolynomialOverPolynomialWithCubeRoot) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-8, {})});
    Term const expectedDenominator(Polynomial{
        Monomial(1, {{"x", 1}}), Monomial(-1, {{"x", AlbaNumber::createFraction(2, 3)}}),
        Monomial(-2, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-12, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForPolynomialOverPolynomialWith6thRoot) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term const expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-64, {})});
    Term const expectedDenominator(Polynomial{
        Monomial(1, {{"x", 1}}), Monomial(-1, {{"x", AlbaNumber::createFraction(5, 6)}}),
        Monomial(-2, {{"x", AlbaNumber::createFraction(2, 3)}}),
        Monomial(-4, {{"x", AlbaNumber::createFraction(1, 2)}}),
        Monomial(-8, {{"x", AlbaNumber::createFraction(1, 3)}}),
        Monomial(-16, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-96, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForExpressionOverExpressionWithSquareRoot) {
    Term const numeratorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const numeratorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term const numeratorPart1Radical(
        createExpressionIfPossible({numeratorPart1, "^", AlbaNumber::createFraction(1, 2)}));
    Term const numeratorPart2Radical(
        createExpressionIfPossible({numeratorPart2, "^", AlbaNumber::createFraction(1, 2)}));
    Term const numerator(createExpressionIfPossible({numeratorPart1Radical, "+", numeratorPart2Radical}));
    Term const denominatorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term const denominatorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const denominatorPart1Radical(
        createExpressionIfPossible({denominatorPart1, "^", AlbaNumber::createFraction(1, 2)}));
    Term const denominatorPart2Radical(
        createExpressionIfPossible({denominatorPart2, "^", AlbaNumber::createFraction(1, 2)}));
    Term const denominator(createExpressionIfPossible({denominatorPart1Radical, "+", denominatorPart2Radical}));
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term const expectedNumerator(1);
    string const expectedDenominatorString(
        "(((1[x^2] + -6[x] + 8)^(1/2))-((1[x^2] + -7[x] + 12)^(1/2))"
        "+((1[x^2] + -7[x] + 10)^(1/2))-((1[x^2] + -8[x] + 15)^(1/2)))");
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominatorString, convertToString(rationalizeTermOverTerm.getDenominator()));
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksForExpressionOverExpressionWithCubeRoot) {
    Term const numeratorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const numeratorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term const numeratorPart1Radical(
        createExpressionIfPossible({numeratorPart1, "^", AlbaNumber::createFraction(1, 3)}));
    Term const numeratorPart2Radical(
        createExpressionIfPossible({numeratorPart2, "^", AlbaNumber::createFraction(1, 3)}));
    Term const numerator(createExpressionIfPossible({numeratorPart1Radical, "+", numeratorPart2Radical}));
    Term const denominatorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term const denominatorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const denominatorPart1Radical(
        createExpressionIfPossible({denominatorPart1, "^", AlbaNumber::createFraction(1, 3)}));
    Term const denominatorPart2Radical(
        createExpressionIfPossible({denominatorPart2, "^", AlbaNumber::createFraction(1, 3)}));
    Term const denominator(createExpressionIfPossible({denominatorPart1Radical, "+", denominatorPart2Radical}));
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    Term const expectedNumerator(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-5, {})});
    string const expectedDenominatorString(
        "(((1[x^3] + -8[x^2] + 20[x] + -16)^(1/3))-((1[x^3] + -9[x^2] + 26[x] + -24)^(1/3))+((1[x^3] + -10[x^2] + "
        "33[x] + -36)^(1/3))"
        "+((1[x^3] + -9[x^2] + 24[x] + -20)^(1/3))-((1[x^3] + -10[x^2] + 31[x] + -30)^(1/3))+((1[x^3] + -11[x^2] + "
        "39[x] + -45)^(1/3)))");
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominatorString, convertToString(rationalizeTermOverTerm.getDenominator()));
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorForExample1) {
    Term const numeratorPart1(Polynomial{Monomial(1, {{"deltaX", 1}}), Monomial(-2, {})});
    Term const numeratorPart1Radical(
        createExpressionIfPossible({numeratorPart1, "^", AlbaNumber::createFraction(1, 3)}));
    Term const numerator(createExpressionIfPossible({numeratorPart1Radical, "-", 1.259921049894873}));
    Term const denominator("deltaX");
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    string const expectedNumeratorString("(1[deltaX] + -4)");
    string const expectedDenominatorString(
        "(1.5874[deltaX]+((1[deltaX^(5/2)] + -2[deltaX^(3/2)])^(2/3))+((2[deltaX^4] + -4[deltaX^3])^(1/3)))");
    EXPECT_EQ(expectedNumeratorString, convertToString(rationalizeTermOverTerm.getNumerator()));
    EXPECT_EQ(expectedDenominatorString, convertToString(rationalizeTermOverTerm.getDenominator()));
}

TEST(RationalizeTermOverTermTest, RationalizeNumeratorWorksOnWithInnerAndOuterFractions) {
    Term const innerNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term const innerDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-3, {})});
    Term const innerFraction(createExpressionIfPossible({innerNumerator, "/", innerDenominator}));
    Term const outerNumerator(
        createExpressionIfPossible({innerFraction, "^", AlbaNumber::createFraction(1, 2), "-", 2}));
    Term const outerDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(outerNumerator, outerDenominator);

    rationalizeTermOverTerm.rationalizeNumerator();

    string const stringToExpect1("((-3[x^(1/2)] + 10)/(1[x^(1/2)] + -3))");
    string const stringToExpect2(
        "((2[x^(1/2)] + -6)+(((1[x^(3/2)] + -2[x])/(1[x^(1/2)] + -3))^(1/2))-(((9[x^(1/2)] + -18)/(1[x^(1/2)] + "
        "-3))^(1/2)))");
    EXPECT_EQ(stringToExpect1, convertToString(rationalizeTermOverTerm.getNumerator()));
    EXPECT_EQ(stringToExpect2, convertToString(rationalizeTermOverTerm.getDenominator()));
}

TEST(
    RationalizeTermOverTermTest,
    RationalizeDenominatorWorksForPolynomialOverPolynomialWithSquareRootWithPlusSecondTerm) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    Term const expectedNumerator(
        Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-9, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(
    RationalizeTermOverTermTest,
    RationalizeDenominatorWorksForPolynomialOverPolynomialWithSquareRootWithMinusSecondTerm) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    Term const expectedNumerator(
        Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-9, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForPolynomialOverPolynomialWithCubeRoot) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    Term const expectedNumerator(Polynomial{
        Monomial(1, {{"x", 1}}), Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}),
        Monomial(3, {{"x", AlbaNumber::createFraction(1, 3)}}), Monomial(-18, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-27, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForPolynomialOverPolynomialWith6thRoot) {
    Term const numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-2, {})});
    Term const denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-3, {})});
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    Term const expectedNumerator(Polynomial{
        Monomial(1, {{"x", 1}}), Monomial(1, {{"x", AlbaNumber::createFraction(5, 6)}}),
        Monomial(3, {{"x", AlbaNumber::createFraction(2, 3)}}), Monomial(9, {{"x", AlbaNumber::createFraction(1, 2)}}),
        Monomial(27, {{"x", AlbaNumber::createFraction(1, 3)}}),
        Monomial(81, {{"x", AlbaNumber::createFraction(1, 6)}}), Monomial(-486, {})});
    Term const expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-729, {})});
    EXPECT_EQ(expectedNumerator, rationalizeTermOverTerm.getNumerator());
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForExpressionOverExpressionWithSquareRoot) {
    Term const numeratorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const numeratorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term const numeratorPart1Radical(
        createExpressionIfPossible({numeratorPart1, "^", AlbaNumber::createFraction(1, 2)}));
    Term const numeratorPart2Radical(
        createExpressionIfPossible({numeratorPart2, "^", AlbaNumber::createFraction(1, 2)}));
    Term const numerator(createExpressionIfPossible({numeratorPart1Radical, "+", numeratorPart2Radical}));
    Term const denominatorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term const denominatorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const denominatorPart1Radical(
        createExpressionIfPossible({denominatorPart1, "^", AlbaNumber::createFraction(1, 2)}));
    Term const denominatorPart2Radical(
        createExpressionIfPossible({denominatorPart2, "^", AlbaNumber::createFraction(1, 2)}));
    Term const denominator(createExpressionIfPossible({denominatorPart1Radical, "+", denominatorPart2Radical}));
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    string const expectedNumeratorString(
        "(((1[x^2] + -6[x] + 8)^(1/2))-((1[x^2] + -7[x] + 10)^(1/2))"
        "+((1[x^2] + -7[x] + 12)^(1/2))-((1[x^2] + -8[x] + 15)^(1/2)))");
    Term const expectedDenominator(1);
    EXPECT_EQ(expectedNumeratorString, convertToString(rationalizeTermOverTerm.getNumerator()));
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

TEST(RationalizeTermOverTermTest, RationalizeDenominatorWorksForExpressionOverExpressionWithCubeRoot) {
    Term const numeratorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term const numeratorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-3, {})});
    Term const numeratorPart1Radical(
        createExpressionIfPossible({numeratorPart1, "^", AlbaNumber::createFraction(1, 3)}));
    Term const numeratorPart2Radical(
        createExpressionIfPossible({numeratorPart2, "^", AlbaNumber::createFraction(1, 3)}));
    Term const numerator(createExpressionIfPossible({numeratorPart1Radical, "+", numeratorPart2Radical}));
    Term const denominatorPart1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term const denominatorPart2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term const denominatorPart1Radical(
        createExpressionIfPossible({denominatorPart1, "^", AlbaNumber::createFraction(1, 3)}));
    Term const denominatorPart2Radical(
        createExpressionIfPossible({denominatorPart2, "^", AlbaNumber::createFraction(1, 3)}));
    Term const denominator(createExpressionIfPossible({denominatorPart1Radical, "+", denominatorPart2Radical}));
    RationalizeTermOverTerm rationalizeTermOverTerm(numerator, denominator);

    rationalizeTermOverTerm.rationalizeDenominator();

    string const expectedNumeratorString(
        "(((1[x^3] + -10[x^2] + 32[x] + -32)^(1/3))-((1[x^3] + -11[x^2] + 38[x] + -40)^(1/3))+((1[x^3] + -12[x^2] + "
        "45[x] + -50)^(1/3))"
        "+((1[x^3] + -11[x^2] + 40[x] + -48)^(1/3))-((1[x^3] + -12[x^2] + 47[x] + -60)^(1/3))+((1[x^3] + -13[x^2] + "
        "55[x] + -75)^(1/3)))");
    Term const expectedDenominator(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-9, {})});
    EXPECT_EQ(expectedNumeratorString, convertToString(rationalizeTermOverTerm.getNumerator()));
    EXPECT_EQ(expectedDenominator, rationalizeTermOverTerm.getDenominator());
}

}  // namespace alba::algebra
