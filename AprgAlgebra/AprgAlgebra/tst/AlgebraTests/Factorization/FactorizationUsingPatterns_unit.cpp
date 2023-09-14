#include <Algebra/Factorization/FactorizationUsingPatterns.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra::Factorization {

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsIfPossibleWorksWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeUsingPatternsIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsIfPossibleWorksWhenDifferenceOfSquares) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify;
    factorizeUsingPatternsIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsIfPossibleWorksWhenDifferenceOfCubes) {
    Polynomial const polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify;
    factorizeUsingPatternsIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsIfPossibleWorksWhenSumOfCubes) {
    Polynomial const polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify;
    factorizeUsingPatternsIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfSquaresIfPossibleIsEmptyWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeDifferenceOfSquaresIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfSquaresIfPossibleWorksWhenFirstMonomialIsPositive) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify;
    factorizeDifferenceOfSquaresIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfSquaresIfPossibleWorksWhenFirstMonomialIsNegative) {
    Polynomial const polynomialToTest{Monomial(-9, {{"x", 8}, {"y", 2}}), Monomial(16, {{"z", 4}})};

    Polynomials polynomialsToVerify;
    factorizeDifferenceOfSquaresIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(-1, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfCubesIfPossibleIsEmptyWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeDifferenceOfCubesIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfCubesIfPossibleWorksWhenFirstMonomialIsPositive) {
    Polynomial const polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify;
    factorizeDifferenceOfCubesIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfCubesIfPossibleWorksWhenFirstMonomialIsNegative) {
    Polynomial const polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify;
    factorizeDifferenceOfCubesIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(-1, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial const polynomialToExpect3{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationUsingPatternsTest, FactorizeSumOfCubesIfPossibleIsEmptyWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeSumOfCubesIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUsingPatternsTest, FactorizeSumOfCubesIfPossibleWorksWhenBothMonomialsArePositive) {
    Polynomial const polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify;
    factorizeSumOfCubesIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationUsingPatternsTest, FactorizeSumOfCubesIfPossibleWorksWhenBothMonomialsAreNegative) {
    Polynomial const polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify;
    factorizeSumOfCubesIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(-1, {})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect3{
        Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationUsingPatternsTest, AddFactorsOfDifferenceOfSquaresWorks) {
    Polynomial const polynomial1{Monomial(9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial const polynomial2{Monomial(-9, {{"x", 4}}), Monomial(16, {{"y", 2}})};

    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfDifferenceOfSquares(polynomialsToVerify1, polynomial1);
    addFactorsOfDifferenceOfSquares(polynomialsToVerify2, polynomial2);

    ASSERT_EQ(2U, polynomialsToVerify1.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(4, {{"y", 1}})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 2}}), Monomial(-4, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify1[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify1[1]);
    ASSERT_EQ(3U, polynomialsToVerify2.size());
    Polynomial const polynomialToExpect3{Monomial(-1, {})};
    Polynomial const polynomialToExpect4{Monomial(3, {{"x", 2}}), Monomial(4, {{"y", 1}})};
    Polynomial const polynomialToExpect5{Monomial(3, {{"x", 2}}), Monomial(-4, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify2[0]);
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify2[1]);
    EXPECT_EQ(polynomialToExpect5, polynomialsToVerify2[2]);
}

TEST(FactorizationUsingPatternsTest, AddFactorsOfDifferenceOfCubesWorks) {
    Polynomial const polynomial1{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial const polynomial2{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};

    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfDifferenceOfCubes(polynomialsToVerify1, polynomial1);
    addFactorsOfDifferenceOfCubes(polynomialsToVerify2, polynomial2);

    ASSERT_EQ(2U, polynomialsToVerify1.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(-4, {{"y", 1}})};
    Polynomial const polynomialToExpect2{
        Monomial(9, {{"x", 4}}), Monomial(12, {{"x", 2}, {"y", 1}}), Monomial(16, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify1[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify1[1]);
    ASSERT_EQ(3U, polynomialsToVerify2.size());
    Polynomial const polynomialToExpect3{Monomial(-1, {})};
    Polynomial const polynomialToExpect4{Monomial(3, {{"x", 2}}), Monomial(-4, {{"y", 1}})};
    Polynomial const polynomialToExpect5{
        Monomial(9, {{"x", 4}}), Monomial(12, {{"x", 2}, {"y", 1}}), Monomial(16, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify2[0]);
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify2[1]);
    EXPECT_EQ(polynomialToExpect5, polynomialsToVerify2[2]);
}

TEST(FactorizationUsingPatternsTest, AddFactorsOfSumOfCubesWorks) {
    Polynomial const polynomial1{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial const polynomial2{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};

    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfSumOfCubes(polynomialsToVerify1, polynomial1);
    addFactorsOfSumOfCubes(polynomialsToVerify2, polynomial2);

    ASSERT_EQ(2U, polynomialsToVerify1.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(4, {{"y", 1}})};
    Polynomial const polynomialToExpect2{
        Monomial(9, {{"x", 4}}), Monomial(-12, {{"x", 2}, {"y", 1}}), Monomial(16, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify1[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify1[1]);
    ASSERT_EQ(3U, polynomialsToVerify2.size());
    Polynomial const polynomialToExpect3{Monomial(-1, {})};
    Polynomial const polynomialToExpect4{Monomial(3, {{"x", 2}}), Monomial(4, {{"y", 1}})};
    Polynomial const polynomialToExpect5{
        Monomial(9, {{"x", 4}}), Monomial(-12, {{"x", 2}, {"y", 1}}), Monomial(16, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify2[0]);
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify2[1]);
    EXPECT_EQ(polynomialToExpect5, polynomialsToVerify2[2]);
}

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsWorksWhenItCannotBeFactored) {
    Polynomial const polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeUsingPatterns(polynomialToTest));

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial const& polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
}

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsWorksWhenItCanBeFactored) {
    Polynomial const polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeUsingPatterns(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial const polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial const polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationUsingPatternsTest, IsDifferenceOfSquaresWorks) {
    Polynomial const polynomial1;
    Polynomial const polynomial2{Monomial(9, {{"x", 4}}), Monomial(16, {{"y", 2}})};
    Polynomial const polynomial3{Monomial(-9, {{"x", 4}}), Monomial(16, {{"y", 2}})};
    Polynomial const polynomial4{Monomial(9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial const polynomial5{Monomial(-9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial const polynomial6{Monomial(10, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial const polynomial7{Monomial(9, {{"x", 4}}), Monomial(-15, {{"y", 2}})};
    Polynomial const polynomial8{Monomial(9, {{"x", 5}}), Monomial(-16, {{"y", 2}})};
    Polynomial const polynomial9{Monomial(9, {{"x", 4}}), Monomial(-16, {{"y", 3}})};

    EXPECT_FALSE(isDifferenceOfSquares(polynomial1));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial2));
    EXPECT_TRUE(isDifferenceOfSquares(polynomial3));
    EXPECT_TRUE(isDifferenceOfSquares(polynomial4));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial5));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial6));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial7));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial8));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial9));
}

TEST(FactorizationUsingPatternsTest, IsDifferenceOfCubesWorks) {
    Polynomial const polynomial1;
    Polynomial const polynomial2{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial const polynomial3{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial const polynomial4{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial const polynomial5{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial const polynomial6{Monomial(28, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial const polynomial7{Monomial(27, {{"x", 6}}), Monomial(-63, {{"y", 3}})};
    Polynomial const polynomial8{Monomial(27, {{"x", 7}}), Monomial(-64, {{"y", 3}})};
    Polynomial const polynomial9{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 4}})};

    EXPECT_FALSE(isDifferenceOfCubes(polynomial1));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial2));
    EXPECT_TRUE(isDifferenceOfCubes(polynomial3));
    EXPECT_TRUE(isDifferenceOfCubes(polynomial4));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial5));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial6));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial7));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial8));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial9));
}

TEST(FactorizationUsingPatternsTest, IsSumOfCubesWorks) {
    Polynomial const polynomial1;
    Polynomial const polynomial2{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial const polynomial3{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial const polynomial4{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial const polynomial5{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial const polynomial6{Monomial(28, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial const polynomial7{Monomial(27, {{"x", 6}}), Monomial(63, {{"y", 3}})};
    Polynomial const polynomial8{Monomial(27, {{"x", 7}}), Monomial(64, {{"y", 3}})};
    Polynomial const polynomial9{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 4}})};

    EXPECT_FALSE(isSumOfCubes(polynomial1));
    EXPECT_TRUE(isSumOfCubes(polynomial2));
    EXPECT_FALSE(isSumOfCubes(polynomial3));
    EXPECT_FALSE(isSumOfCubes(polynomial4));
    EXPECT_TRUE(isSumOfCubes(polynomial5));
    EXPECT_FALSE(isSumOfCubes(polynomial6));
    EXPECT_FALSE(isSumOfCubes(polynomial7));
    EXPECT_FALSE(isSumOfCubes(polynomial8));
    EXPECT_FALSE(isSumOfCubes(polynomial9));
}

}  // namespace alba::algebra::Factorization
