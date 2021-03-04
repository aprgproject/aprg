#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Vector/VectorTypes.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(VectorTypesTest, GettingMagnitudeWorks)
{
    Term t("t");
    Term x(createExpressionIfPossible({2, "*", cos(t)}));
    Term y(createExpressionIfPossible({2, "*", sin(t)}));
    MathVectorOfTwoTerms termVector{x, y};

    Term magnitude(termVector.getMagnitude());
    magnitude.simplify();

    string stringToExpect("((((2*cos(t))^2)+((2*sin(t))^2))^(1/2))");
    EXPECT_EQ(stringToExpect, magnitude.getDisplayableString());
}

}

}
