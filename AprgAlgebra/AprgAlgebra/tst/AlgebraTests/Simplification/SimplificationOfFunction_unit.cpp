#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfFunction.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra::Simplification {

TEST(SimplificationOfFunctionTest, SimplifyWorksOnAbsoluteValueExpressionWithPositiveFirstCoefficient) {
    SimplificationOfFunction simplification(
        Functions::abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}));

    simplification.simplify();

    Function const actualEquation(simplification.getFunction());
    Function const expectedFunction(Functions::abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}));
    EXPECT_EQ(expectedFunction, actualEquation);
}

TEST(SimplificationOfFunctionTest, SimplifyWorksOnAbsoluteValueExpressionWithNegativeFirstCoefficient) {
    SimplificationOfFunction simplification(
        Functions::abs(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}})}));

    simplification.simplify();

    Function const actualEquation(simplification.getFunction());
    Function const expectedFunction(Functions::abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}));
    EXPECT_EQ(expectedFunction, actualEquation);
}

}  // namespace alba::algebra::Simplification
