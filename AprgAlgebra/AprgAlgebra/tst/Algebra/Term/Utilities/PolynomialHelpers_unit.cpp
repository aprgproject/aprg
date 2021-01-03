#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(PolynomialHelpersTest, DoesThePolynomialHaveOnlyOneConstantWorks)
{
    EXPECT_FALSE(doesThePolynomialHaveOnlyOneConstant(Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"x", 3}}), Monomial(-16, {})}));
    EXPECT_FALSE(doesThePolynomialHaveOnlyOneConstant(Polynomial{Monomial(-16, {}), Monomial(32, {})}));
    EXPECT_TRUE(doesThePolynomialHaveOnlyOneConstant(Polynomial{Monomial(-16, {})}));
}

TEST(PolynomialHelpersTest, DoesThePolynomialHaveOnlyOneVariableWorks)
{
    EXPECT_FALSE(doesThePolynomialHaveOnlyOneVariable(Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"y", 3}}), Monomial(-16, {})}));
    EXPECT_TRUE(doesThePolynomialHaveOnlyOneVariable(Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"x", 3}}), Monomial(-16, {})}));
}

TEST(PolynomialHelpersTest, GetRemainderForOneVariablePolynomialDividedByVariableMinusConstantValueWorks)
{
    Polynomial polynomial{Monomial(5, {{"x", 3}}), Monomial(-8, {{"x", 2}}), Monomial(6, {{"x", 1}}), Monomial(4, {})};

    AlbaNumber expectedRemainder(24);
    EXPECT_EQ(expectedRemainder, getRemainderForOneVariablePolynomialDividedByVariableMinusConstantValue(polynomial, 2));
}

TEST(PolynomialHelpersTest, GetRootsWorksAndRootsIsEmptyWhenConstantIsGiven)
{
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(-16, {})}));

    EXPECT_TRUE(roots.empty());
}

TEST(PolynomialHelpersTest, GetRootsWorksAndRootsIsEmptyWhenMultipleVariablesAreGiven)
{
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"y", 3}}), Monomial(-16, {})}));

    EXPECT_TRUE(roots.empty());
}

TEST(PolynomialHelpersTest, GetRootsWorksAndFactorizesAPolynomial)
{
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", 2}}), Monomial(-16, {})}));

    ASSERT_EQ(2U, roots.size());
    EXPECT_EQ(AlbaNumber(-4), roots.at(0));
    EXPECT_EQ(AlbaNumber(4), roots.at(1));
}

TEST(PolynomialHelpersTest, GetRootsWorksAndRootIsZeroWhenExponentIsPositive)
{
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", AlbaNumber(4)/3}})}));

    ASSERT_EQ(1U, roots.size());
    EXPECT_EQ(AlbaNumber(0), roots.at(0));
}

TEST(PolynomialHelpersTest, GetRootsWorksAndZeroIsNotIncludedWhenExponentIsNegative)
{
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", AlbaNumber(-4)/3}})}));

    EXPECT_TRUE(roots.empty());
}

TEST(PolynomialHelpersTest, GetRootsWorksAndWhenPolynomialIsNotSorted)
{
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(-16, {}), Monomial(1, {{"x", 1}})}));

    ASSERT_EQ(1U, roots.size());
    EXPECT_EQ(AlbaNumber(16), roots.at(0));
}

TEST(PolynomialHelpersTest, GetRootsWorksAndRootIsCorrectlyCalculatedWhenExponentIsNotAnInteger)
{
    AlbaNumbers roots(getRoots(RootType::RealRootsOnly, Polynomial{Monomial(1, {{"x", AlbaNumber(4)/3}}), Monomial(-16, {})}));

    ASSERT_EQ(1U, roots.size());
    EXPECT_EQ(AlbaNumber(8), roots.at(0));
}

TEST(PolynomialHelpersTest, RaiseBinomialToAPowerUsingBinomialExpansionWorks)
{
    Polynomial binomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};

    Polynomial actualExpansion(raiseBinomialToAPowerUsingBinomialExpansion(binomial, 4));

    Polynomial expectedExpansion{
        Monomial(1, {{"x", 4}}),
                Monomial(4, {{"x", 3}, {"y", 1}}),
                Monomial(6, {{"x", 2}, {"y", 2}}),
                Monomial(4, {{"x", 1}, {"y", 3}}),
                Monomial(1, {{"y", 4}})
    };
    EXPECT_EQ(expectedExpansion, actualExpansion);
}

}

}
