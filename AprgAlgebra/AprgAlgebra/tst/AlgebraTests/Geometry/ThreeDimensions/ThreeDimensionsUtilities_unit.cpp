#include <Algebra/Geometry/ThreeDimensions/ThreeDimensionsUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra::ThreeDimensions {

TEST(ThreeDimensionsUtilitiesTest, GetEllipsoidEquationWorks) {
    Equation const equationToVerify(getEllipsoidEquation());

    string const stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))+(((z-z0)^2)/(c^2))) = 1");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticConeEquationWorks) {
    Equation const equationToVerify(getEllipticConeEquation());

    string const stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))+(((z-z0)^2)/(c^2))) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticHyperboloidEquationEquationWorks) {
    Equation const equationToVerify1(getEllipticHyperboloidEquation(false));
    Equation const equationToVerify2(getEllipticHyperboloidEquation(true));

    string const stringToExpect1("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))-(((z-z0)^2)/(c^2))) = 1");
    string const stringToExpect2("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))-(((z-z0)^2)/(c^2))) = -1");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
}

TEST(ThreeDimensionsUtilitiesTest, GetEllipticParaboloidEquationEquationWorks) {
    Equation const equationToVerify(getEllipticParaboloidEquation());

    string const stringToExpect("((((x-x0)^2)/(a^2))+(((y-y0)^2)/(b^2))) = ((z-z0)/c)");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetHyperbolicParaboloidEquationEquationWorks) {
    Equation const equationToVerify(getHyperbolicParaboloidEquation());

    string const stringToExpect("((((y-y0)^2)/(b^2))-(((x-x0)^2)/(a^2))) = ((z-z0)/c)");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetPlaneEquationWorks) {
    Equation const equationToVerify(getPlaneEquation());

    string const stringToExpect("((a*x)+(b*y)+(c*z)+d) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetPlaneEquationWithPointCoordinatesWorks) {
    Equation const equationToVerify(getPlaneEquationWithPointCoordinates());

    string const stringToExpect("((a*x)-(a*x0)+(b*y)-(b*y0)+(c*z)-(c*z0)) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetSphereEquationWorks) {
    Equation const equationToVerify(getSphereEquation());

    string const stringToExpect("(((x-x0)^2)+((y-y0)^2)+((z-z0)^2)) = (r^2)");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(ThreeDimensionsUtilitiesTest, GetLineEquationsWorks) {
    Equations equationsToVerify(getLineEquations());

    string const stringToExpect1("((x-x0)/a) = ((y-y0)/b)");
    string const stringToExpect2("((x-x0)/a) = ((z-z0)/c)");
    ASSERT_EQ(2U, equationsToVerify.size());
    EXPECT_EQ(stringToExpect1, convertToString(equationsToVerify[0]));
    EXPECT_EQ(stringToExpect2, convertToString(equationsToVerify[1]));
}

}  // namespace alba::algebra::ThreeDimensions
