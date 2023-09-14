#include <Math/NumberTheory/PythagoreanTripleUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::math {

TEST(PythagoreanTripleTest, GetNewPythagoreanTripleUsingMultiplierWorks) {
    PythagoreanTriple const tripleToVerify(getNewPythagoreanTripleUsingMultiplier(PythagoreanTriple{3U, 4U, 5U}, 5));

    PythagoreanTriple const tripleToExpect{15U, 20U, 25U};
    EXPECT_EQ(tripleToExpect, tripleToVerify);
}

TEST(PythagoreanTripleTest, GetPrimitivePythagoreanTripleUsingEuclidFormulaWorks) {
    PythagoreanTriple const tripleToVerify1(getPrimitivePythagoreanTripleUsingEuclidFormula(1U, 2U));
    PythagoreanTriple const tripleToVerify2(getPrimitivePythagoreanTripleUsingEuclidFormula(23U, 44U));

    PythagoreanTriple const tripleToExpect1{3U, 4U, 5U};
    PythagoreanTriple const tripleToExpect2{1407U, 2024U, 2465U};
    EXPECT_EQ(tripleToExpect1, tripleToVerify1);
    EXPECT_EQ(tripleToExpect2, tripleToVerify2);
}

TEST(PythagoreanTripleTest, IsPythagoreanTripleWorks) {
    EXPECT_FALSE(isPythagoreanTriple(PythagoreanTriple{5U, 6U, 7U}));
    EXPECT_TRUE(isPythagoreanTriple(PythagoreanTriple{3U, 4U, 5U}));
    EXPECT_TRUE(isPythagoreanTriple(PythagoreanTriple{5U, 12U, 13U}));
}

TEST(PythagoreanTripleTest, IsPrimitiveWorks) {
    EXPECT_TRUE(isPrimitive(PythagoreanTriple{5U, 6U, 7U}));  // still true even if not pythagorean triple
    EXPECT_TRUE(isPrimitive(PythagoreanTriple{3U, 4U, 5U}));
    EXPECT_FALSE(isPrimitive(PythagoreanTriple{6U, 8U, 10U}));
}

}  // namespace alba::math
