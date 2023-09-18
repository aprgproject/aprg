#include <Algebra/Summation/SummationUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;

namespace alba::algebra {

TEST(SummationUtilitiesTest, GetSummationOfArithmeticSeriesWorks) {
    Term const term(getSummationOfArithmeticSeries("n"));

    EXPECT_EQ("((1/2)[n^2] + (1/2)[n])", convertToString(term));
}

TEST(SummationUtilitiesTest, GetSummationOfArithmeticSeriesForSquaresWorks) {
    Term const term(getSummationOfArithmeticSeriesForSquares("n"));

    EXPECT_EQ("((1/3)[n^3] + (1/2)[n^2] + 1[n])", convertToString(term));
}

TEST(SummationUtilitiesTest, GetSummationOfArithmeticSeriesForCubesWorks) {
    Term const term(getSummationOfArithmeticSeriesForCubes("n"));

    EXPECT_EQ("((1/4)[n^4] + (1/2)[n^3] + (1/4)[n^2])", convertToString(term));
}

TEST(SummationUtilitiesTest, GetSummationOfFiniteGeometricSeriesWorks) {
    Term const term(getSummationOfFiniteGeometricSeries("x", "n"));

    EXPECT_EQ("((-1+(x^(1[n] + 1)))/(1[x] + -1))", convertToString(term));
}

TEST(SummationUtilitiesTest, GetSummationOfInfiniteGeometricSeriesWorks) {
    Term const term(getSummationOfInfiniteGeometricSeries("n"));

    EXPECT_EQ("(-1/(1[n] + -1))", convertToString(term));
}

TEST(SummationUtilitiesTest, GetSummationOfHarmonicSeriesWorks) {
    Term const term(getSummationOfHarmonicSeries("n"));

    EXPECT_EQ("(ln(n)+1)", convertToString(term));
}

TEST(SummationUtilitiesTest, GetSummationOfPowersOfTwoWorks) {
    Term const term(getSummationOfPowersOfTwo("n"));

    EXPECT_EQ("(-1+(2^(1[n] + 1)))", convertToString(term));
}

}  // namespace alba::algebra
