#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationGeometryUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(IntegrationGeometryUtilitiesTest, GetAreaInBetweenTwoTermsInAnIntervalWorks) {
    Term const lowerTerm(Monomial(1, {{"x", 2}}));
    Term const higherTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(
        Term(AlbaNumber::createFraction(8, 3)),
        getAreaInBetweenTwoTermsInAnInterval(lowerTerm, higherTerm, {"x", 0, 2}));
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnCrossSectionalAreaWorksOnPyramidWithSquareBase) {
    Term const ratio = Term("side") / Term("height");
    Term const crossSectionalArea(createExpressionIfPossible({"(", ratio, "*", "z", ")", "^", 2}));

    Term const termToVerify(getVolumeUsingOnCrossSectionalArea(crossSectionalArea, {"z", 0, "height"}));

    Term const termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"height", 1}, {"side", 2}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownCone) {
    Term const edgeOfTheConeInY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));

    Term const termToVerify(getVolumeUsingOnSolidOfRevolution(edgeOfTheConeInY, {"y", 0, "height"}));

    Term const termToExpect(Monomial(AlbaNumber(1.047197551196598), {{"height", 1}, {"radius", 2}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeAndSurfaceAreaBasedOnSolidOfRevolutionWorksOnGabrielsHorn) {
    // The painters paradox (volume is definite, but surface are is infinite).
    // Computation of the volume:
    // The horn follows the form y=1/x and starts at x=1 and ends at infinity
    Term const edgeOfHornInX(Monomial(1, {{"x", -1}}));

    Term const actualVolume(getVolumeUsingOnSolidOfRevolution(edgeOfHornInX, {"x", 1, getPositiveInfinityAsATerm()}));
    // Term actualSurfaceArea(getSurfaceAreaUsingOnSolidOfRevolution(edgeOfHornInX, {"x", 1,
    // getPositiveInfinityAsATerm()}));
    // The surface area is hard to integrate: (((1[x^4] + 1)^(1/2))/1[x^3])
    // This can be solved via integration by parts u = (1+x4)^(1/2), v' = 1/(x^3), check symbolab.com
    Term const expectedVolume(getPiAsATerm());
    // Term expectedSurfaceArea(getPositiveInfinityAsATerm());
    EXPECT_EQ(expectedVolume, actualVolume);
    // EXPECT_EQ(expectedSurfaceArea, actualSurfaceArea);
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeBasedOnSolidOfRevolutionWorksOnUpsideDownConeWithUpsideDownConeHole) {
    Term const edgeOfTheCone1InY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));
    Term const edgeOfTheCone2InY(
        Polynomial{Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}), Monomial(1, {{"edgeDistance", 1}})});

    Term const termToVerify(
        getVolumeUsingOnSolidOfRevolution(edgeOfTheCone1InY, edgeOfTheCone2InY, {"y", 0, "height"}));

    Term const termToExpect(Monomial(getPi(), {{"edgeDistance", 2}, {"height", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetSurfaceAreaBasedOnSolidOfRevolutionWorksOnUpsideDownCone) {
    Term const edgeOfTheConeInY(Monomial(1, {{"radius", 1}, {"height", -1}, {"y", 1}}));

    Term const termToVerify(getSurfaceAreaUsingOnSolidOfRevolution(edgeOfTheConeInY, {"y", 0, "height"}));

    string const stringToExpect("((pi)[radius]*((1[height^2] + 1[radius^2])^(1/2)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(IntegrationGeometryUtilitiesTest, GetVolumeUsingCylindricalShellsWorksOnParabolaCupHole) {
    Term const edgeOfTheParabolaInX(Monomial(1, {{"x", 2}}));

    Term const termToVerify(getVolumeUsingCylindricalShells(edgeOfTheParabolaInX, {"x", 0, "radius"}));

    Term const termToExpect(Monomial(1.570796326794897, {{"radius", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLengthOfArcWorks) {
    Term const termToTest(Monomial(1, {{"x", AlbaNumber::createFraction(2, 3)}}));

    Term const termToVerify(getLengthOfArc(termToTest, {"x", 1, 8}));

    Term const termToExpect(7.63370541601624);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLengthOfArcInPolarCoordinatesWorks) {
    Term const radiusOfLimacon(Monomial(2, {{"theta", 1}}));

    Term const termToVerify(getLengthOfArcInPolarCoordinates(radiusOfLimacon, {"theta", 0, getPiAsATerm()}));

    Term const termToExpect(12.21983866791859);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfARodWorks) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    Term const termToVerify(getTotalMassOfARod(termToTest, {"x", 0, "l"}));

    Term const termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"l", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfARodWorks) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    Term const termToVerify(getMomentOfMassOfARod(termToTest, {"x", 0, "l"}));

    Term const termToExpect(Monomial(AlbaNumber::createFraction(1, 4), {{"l", 4}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfARodWorks) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    Term const termToVerify(getCenterOfMassOfARod(termToTest, {"x", 0, "l"}));

    Term const termToExpect(Monomial(AlbaNumber::createFraction(3, 4), {{"l", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfALaminaWorks) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    Term const termToVerify(getTotalMassOfALamina(termToTest, {"x", 0, "x"}));

    Term const termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTotalMassOfALaminaWorksWithXDetailsAndYDetails) {
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};

    Term const termToVerify(getTotalMassOfALamina(termToTest, xDetails, yDetails));

    Term const termToExpect(24);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetRadiusOfGyrationWorksWithXDetailsAndYDetails) {
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};
    Term const momentOfInertiaAboutTheYAxis(getMomentOfInertiaAboutTheYAxis(termToTest, xDetails, yDetails));
    Term const totalMassOfALamina(getTotalMassOfALamina(termToTest, xDetails, yDetails));

    Term const termToVerify(getRadiusOfGyration(momentOfInertiaAboutTheYAxis, totalMassOfALamina));

    Term const termToExpect(0.6324555320336759);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetWorkWorks) {
    Term const force(Monomial(1, {{"x", 2}}));

    Term const termToVerify(getWork(force, {"x", 0, "x"}));

    Term const termToExpect(Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetLiquidPressureWorks) {
    Term const length(Monomial(1, {{"depth", 2}}));

    Term const termToVerify(getLiquidPressure("raw", "g", length, {"depth", 0, 2}));

    Term const termToExpect(Monomial(4, {{"g", 1}, {"raw", 1}}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, IntegrateInPolarCoordinatesWorks) {
    Term const radiusOfLimacon(createExpressionIfPossible({2, "+", 2, "*", cos("theta")}));

    Term const termToVerify(integrateInPolarCoordinates(radiusOfLimacon, {"theta", 0, getPiAsATerm()}));

    Term const termToExpect(18.84955592153876);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInCartesianCoordinatesWorksOnExample1) {
    // Evaluate the double integral Integral[3y-2*x^2]dA
    // if R is the region consisting of all points (x, y) for which -1<x<2 and 1<y<3
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};

    Term const termToVerify(getDoubleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails));

    Term const termToExpect(24);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInCartesianCoordinatesWorksOnExample2) {
    // Find the volume z = 4 - 1/9*x^2 - 1/16*y^2
    // bounded by the surface x=3, y=2 and the three coordinate planes
    Term const termToTest(Polynomial{
        Monomial(4, {}), Monomial(AlbaNumber::createFraction(-1, 9), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(-1, 16), {{"y", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", 0, 3};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 0, 2};

    Term const termToVerify(getDoubleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails));

    Term const termToExpect(AlbaNumber::createFraction(43, 2));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWithRespectToXAxisWorksWithXDetailsAndYDetails) {
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};

    Term const termToVerify(getMomentOfMassOfALaminaWithRespectToXAxis(termToTest, xDetails, yDetails));

    Term const termToExpect(54);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWithRespectToYAxisWorksWithXDetailsAndYDetails) {
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};

    Term const termToVerify(getMomentOfMassOfALaminaWithRespectToYAxis(termToTest, xDetails, yDetails));

    Term const termToExpect(3);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheXAxisWorksWithXDetailsAndYDetails) {
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};

    Term const termToVerify(getMomentOfInertiaAboutTheXAxis(termToTest, xDetails, yDetails));

    Term const termToExpect(128);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheYAxisWorksWithXDetailsAndYDetails) {
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};

    Term const termToVerify(getMomentOfInertiaAboutTheYAxis(termToTest, xDetails, yDetails));

    Term const termToExpect(AlbaNumber::createFraction(48, 5));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfInertiaAboutTheOriginWorksWithXDetailsAndYDetails) {
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};

    Term const termToVerify(getMomentOfInertiaAboutTheOrigin(termToTest, xDetails, yDetails));

    Term const termToExpect(AlbaNumber::createFraction(688, 5));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInPolarCoordinatesWorksOnExample1) {
    // Find the volume of the soild in the first octant bounded by the code z = r and the cylinder r = 3 sin(theta)
    Term const termToTest("r");
    DetailsForDefiniteIntegralWithTerms const radiusDetails{"r", 0, 3 * sin("theta")};
    DetailsForDefiniteIntegralWithTerms const thetaDetails{"theta", 0, getPiAsATerm() / 2};

    Term const termToVerify(getDoubleIntegralInPolarCoordinates(termToTest, radiusDetails, thetaDetails));

    Term const termToExpect(6);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetDoubleIntegralInPolarCoordinatesWorksOnExample2) {
    // Find the area of the region enclosed by one leaf of the rose r =  sin(3 * theta)
    Term const termToTest(1);
    DetailsForDefiniteIntegralWithTerms const radiusDetails{"r", 0, sin(Monomial(3, {{"theta", 1}}))};
    DetailsForDefiniteIntegralWithTerms const thetaDetails{"theta", 0, getPiAsATerm() / 3};

    Term const termToVerify(getDoubleIntegralInPolarCoordinates(termToTest, radiusDetails, thetaDetails));

    Term const termToExpect(0.2617993877991494);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, DISABLED_GetSurfaceAreaWithZInCartesianCoordinatesWorksOnExample1) {
    // Disabled because integration does not work here (possible trig sub problem)
    // Find the area of the surface that is cut from the cylinder x^2 + z^2 = 16 by the planes x=0, x=2, y=0, y=3
    Term const insideSquareRoot(Polynomial{Monomial(16, {}), Monomial(-1, {{"x", 2}})});
    Term const z(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", 0, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 0, 3};

    Term const termToVerify(getSurfaceAreaWithZInCartesianCoordinates(z, xDetails, yDetails));

    Term const termToExpect(1);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetSurfaceAreaWithZInCartesianCoordinatesWorksOnExample2) {
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", 0, 3};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 0, 4};

    Term const termToVerify(getSurfaceAreaWithZInCartesianCoordinates("z", xDetails, yDetails));

    Term const termToExpect(12);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInCartesianCoordinatesWorks) {
    // Find by triple integration the volume of the solid bounded by elliptic paraboloid z = x^2 + 4*y^2 and cylinder
    // x^2 + 4*y^2 = 4
    Term const termToTest(4);  // because this is done for each quadrant
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", 0, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{
        "y", 0,
        createExpressionIfPossible(
            {Polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})}, "^", AlbaNumber::createFraction(1, 2), "/", 2})};
    DetailsForDefiniteIntegralWithTerms const zDetails{
        "z", 0, Polynomial{Monomial(1, {{"x", 2}}), Monomial(4, {{"y", 2}})}};

    Term const termToVerify(getTripleIntegralInCartesianCoordinates(termToTest, xDetails, yDetails, zDetails));

    Term const termToExpect(12.56637061435917);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInCylindricalCoordinatesWorks) {
    // Get volume of cylinder with radius=2 and height=3
    Term const termToTest(1);
    DetailsForDefiniteIntegralWithTerms const radiusDetails{"r", 0, 2};
    DetailsForDefiniteIntegralWithTerms const thetaDetails{"theta", 0, getPiAsATerm() * 2};
    DetailsForDefiniteIntegralWithTerms const zDetails{"z", 0, 3};

    Term const termToVerify(
        getTripleIntegralInCylindricalCoordinates(termToTest, radiusDetails, thetaDetails, zDetails));

    Term const termToExpect(37.69911184307752);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetTripleIntegralInSphericalCoordinatesWorks) {
    // Get volume of sphere with raw=2
    Term const termToTest(8);  // integrate a sphere on each quadrant
    DetailsForDefiniteIntegralWithTerms const rawDetails{"raw", 0, 2};
    DetailsForDefiniteIntegralWithTerms const thetaDetails{"theta", 0, getPiAsATerm() / 2};
    DetailsForDefiniteIntegralWithTerms const phiDetails{"phi", 0, getPiAsATerm() / 2};

    Term const termToVerify(getTripleIntegralInSphericalCoordinates(termToTest, rawDetails, thetaDetails, phiDetails));

    Term const termToExpect(33.51032163829112);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationGeometryUtilitiesTest, GetMomentOfMassOfALaminaWorks) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    TermPair const termPairToVerify(getMomentOfMassOfALamina(termToTest, {"x", 0, "x"}));

    Term const termToExpectInX(Monomial(AlbaNumber::createFraction(1, 10), {{"x", 5}}));
    Term const termToExpectInY(Monomial(AlbaNumber::createFraction(1, 4), {{"x", 4}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfALaminaWorks) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    TermPair const termPairToVerify(getCenterOfMassOfALamina(termToTest, {"x", 0, "x"}));

    Term const termToExpectInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term const termToExpectInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x", 1}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCenterOfMassOfALaminaWorksWithXDetailsAndYDetails) {
    Term const termToTest(Polynomial{Monomial(3, {{"y", 1}}), Monomial(-2, {{"x", 2}})});
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 2};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 1, 3};

    TermPair const termPairToVerify(getCenterOfMassOfALamina(termToTest, xDetails, yDetails));

    Term const termToExpect1(AlbaNumber::createFraction(1, 8));
    Term const termToExpect2(AlbaNumber::createFraction(9, 4));
    EXPECT_EQ(termToExpect1, termPairToVerify.first);
    EXPECT_EQ(termToExpect2, termPairToVerify.second);
}

TEST(IntegrationGeometryUtilitiesTest, GetCentroidWorks) {
    Term const termToTest(Monomial(1, {{"x", 2}}));

    TermPair const termPairToVerify(getCentroid(termToTest, {"x", 0, "x"}));

    Term const termToExpectInX(Monomial(AlbaNumber::createFraction(3, 10), {{"x", 2}}));
    Term const termToExpectInY(Monomial(AlbaNumber::createFraction(3, 4), {{"x", 1}}));
    EXPECT_EQ(termToExpectInX, termPairToVerify.first);
    EXPECT_EQ(termToExpectInY, termPairToVerify.second);
}

}  // namespace alba::algebra
