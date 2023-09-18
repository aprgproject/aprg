#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Vector/MathVectorOfTermsUtilities.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra::VectorUtilities {

TEST(MathVectorOfTermsUtilitiesTest, GetTangentPlaneOnAPointOfASurfaceWorks) {
    Term const surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation const equationToTest(surfaceLeftPart, "=", 0);

    Equation const equationToVerify(getTangentPlaneOnAPointOfASurface(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string const stringToExpect("(2[x] + 1[y] + -2[z] + -4) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetPerpendicularLineOnAPointOfASurfaceWorks) {
    Term const surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation const equationToTest(surfaceLeftPart, "=", 0);

    Equations equationsToVerify(getPerpendicularLineOnAPointOfASurface(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string const stringToExpect1("(1[x] + -2[y] + 6) = 0");
    string const stringToExpect2("(1[x] + 1[z] + -4) = 0");
    ASSERT_EQ(2U, equationsToVerify.size());
    EXPECT_EQ(stringToExpect1, convertToString(equationsToVerify[0]));
    EXPECT_EQ(stringToExpect2, convertToString(equationsToVerify[1]));
}

TEST(MathVectorOfTermsUtilitiesTest, GetNormalOfASurfaceOnAPointWorks) {
    Term const surfaceLeftPart(Polynomial{Monomial(4, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-16, {{"z", 1}})});
    Equation const equationToTest(surfaceLeftPart, "=", 0);

    MathVectorOfThreeTerms const vectorToVerify(
        getNormalOfASurfaceOnAPoint(equationToTest, {"x", "y", "z"}, {2, 4, 2}));

    string const stringToExpect("{16, 8, -16}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurlWorks) {
    Term const x(createExpressionIfPossible({getEAsATerm(), "^", Monomial(2, {{"x", 1}})}));
    Term const y(Monomial(3, {{"x", 2}, {"y", 1}, {"z", 1}}));
    Term const z(Polynomial{Monomial(2, {{"y", 2}, {"z", 1}}), Monomial(1, {{"x", 1}})});
    MathVectorOfThreeTerms const vectorField{x, y, z};

    MathVectorOfThreeTerms const vectorToVerify(getCurl(vectorField, {"x", "y", "z"}));

    string const stringToExpect("{(-3[x^2][y] + 4[y][z]), -1, 6[x][y][z]}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetDyOverDxWorks) {
    Term const x(Polynomial{Monomial(4, {}), Monomial(-1, {{"t", 2}})});
    Term const y(Polynomial{Monomial(1, {{"t", 2}}), Monomial(4, {{"t", 1}})});
    MathVectorOfTwoTerms const termVector{x, y};

    Term const termToVerify(getDyOverDx(termVector, "t"));

    string const stringToExpect("(-1 + -2[t^-1])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetDirectionalDerivativeInTwoDimensionsWorks) {
    Term const termToTest(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(1, 9), {{"y", 2}})});
    AlbaAngle const angle(AngleUnitType::Radians, getPi() / 4);

    Term const termToVerify(getDirectionalDerivativeInTwoDimensions(termToTest, {"x", "y"}, angle));

    string const stringToExpect("(0.0883883[x] + 0.157135[y])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetDirectionalDerivativeInThreeDimensionsWorks) {
    Term const termToTest(Polynomial{
        Monomial(3, {{"x", 2}}), Monomial(1, {{"x", 1}, {"y", 1}}), Monomial(-2, {{"y", 2}}),
        Monomial(-1, {{"y", 1}, {"z", 1}}), Monomial(1, {{"z", 2}})});
    AlbaAngle const alpha(AngleUnitType::Radians, getPi() / 4);
    AlbaAngle const beta(AngleUnitType::Radians, getPi() / 5);
    AlbaAngle const gamma(AngleUnitType::Radians, getPi() / 6);

    Term const termToVerify(
        getDirectionalDerivativeInThreeDimensions(termToTest, {"x", "y", "z"}, {alpha, beta, gamma}));

    string const stringToExpect("(5.05166[x] + -3.39499[y] + 0.923034[z])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralOfAClosedNonIntersectingPathUsingGreensTheoremWorks) {
    Term const xInVectorField(Monomial(1, {{"y", 2}}));
    Term const yInVectorField(Monomial(4, {{"x", 1}, {"y", 1}}));
    MathVectorOfTwoTerms const vectorField{xInVectorField, yInVectorField};
    DetailsForDefiniteIntegralWithTerms const xDetailsForLinePath{"x", 0, 2};
    DetailsForDefiniteIntegralWithTerms const yDetailsForLinePath{
        "y", Monomial(2, {{"x", 1}}), Monomial(1, {{"x", 2}})};

    Term const termToVerify(getLineIntegralOfAClosedNonIntersectingPathUsingGreensTheorem(
        vectorField, {"x", "y"}, xDetailsForLinePath, yDetailsForLinePath));

    string const stringToExpect("(-64/15)");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetAreaOfAClosedNonIntersectingPathUsingGreensTheoremWorks) {
    // Get area of ellipse
    Term const xInLinePath("a" * cos("t"));  // ellipse parameterized in X
    Term const yInLinePath("b" * sin("t"));  // ellipse parameterized in Y
    MathVectorOfTwoTerms const linePath{xInLinePath, yInLinePath};

    Term const termToVerify(
        getAreaOfAClosedNonIntersectingPathUsingGreensTheorem({"x", "y"}, linePath, {"t", 0, 2 * getPiAsATerm()}));

    string const stringToExpect("(pi)[a][b]");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, IsDivergenceOfCurlZeroWorks) {
    Term const x(createExpressionIfPossible({getEAsATerm(), "^", Monomial(2, {{"x", 1}})}));
    Term const y(Monomial(3, {{"x", 2}, {"y", 1}, {"z", 1}}));
    Term const z(Polynomial{Monomial(2, {{"y", 2}, {"z", 1}}), Monomial(1, {{"x", 1}})});
    MathVectorOfThreeTerms const vectorField{x, y, z};

    EXPECT_TRUE(isDivergenceOfCurlZero(vectorField, {"x", "y", "z"}));
}

TEST(MathVectorOfTermsUtilitiesTest, IsGaussDivergenceTheoremInAPlaneTrueWorks) {
    Term const xInVectorField(Monomial(2, {{"y", 1}}));
    Term const yInVectorField(Monomial(5, {{"x", 1}}));
    MathVectorOfTwoTerms const vectorField{xInVectorField, yInVectorField};
    MathVectorOfTwoTerms const regionOfLineIntegral{cos("t"), sin("t")};
    MathVectorOfTwoTerms const unitOutwardNormal{cos("t"), sin("t")};
    DetailsForDefiniteIntegralWithTerms const lineIntegralDetails{"t", 0, 2 * getPiAsATerm()};
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", -1, 1};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", -1, 1};

    EXPECT_TRUE(isGaussDivergenceTheoremInAPlaneTrue(
        vectorField, regionOfLineIntegral, unitOutwardNormal, lineIntegralDetails, xDetails, yDetails, {"x", "y"}));
}

TEST(MathVectorOfTermsUtilitiesTest, IsStokesTheoremInAPlaneTrueWorks) {
    Term const xInVectorField(Monomial(2, {{"y", 1}}));
    Term const yInVectorField(Monomial(5, {{"x", 1}}));
    MathVectorOfTwoTerms const vectorField{xInVectorField, yInVectorField};
    MathVectorOfTwoTerms const regionOfLineIntegral{cos("t"), sin("t")};
    MathVectorOfTwoTerms const unitTangent{sin("t") * -1, cos("t")};
    DetailsForDefiniteIntegralWithTerms const lineIntegralDetails{"t", 0, 2 * getPiAsATerm()};
    DetailsForDefiniteIntegralWithTerms const xDetails{"x", 0, 1};
    DetailsForDefiniteIntegralWithTerms const yDetails{"y", 0, getPiAsATerm()};

    EXPECT_TRUE(isStokesTheoremInAPlaneTrue(
        vectorField, regionOfLineIntegral, unitTangent, lineIntegralDetails, xDetails, yDetails, {"x", "y"}));
}

TEST(MathVectorOfTermsUtilitiesTest, IsContinuousAtWorks) {
    Term const x(cos("t"));
    Term const y(createExpressionIfPossible({2, "*", getEAsATerm(), "^", "t"}));
    MathVectorOfTwoTerms const termVector{x, y};

    EXPECT_TRUE(isContinuousAt(termVector, "t", 0));
}

TEST(MathVectorOfTermsUtilitiesTest, IsDifferentiableAtWorks) {
    Term const x("t");
    Term const y("t");
    MathVectorOfTwoTerms const termVector{x, y};

    EXPECT_TRUE(isDifferentiableAt(termVector, "t", 0));
}

TEST(MathVectorOfTermsUtilitiesTest, AreOriginalAndDerivativeVectorsOrthogonalWorks) {
    MathVectorOfTwoTerms const termVector{7, 8};

    EXPECT_TRUE(areOriginalAndDerivativeVectorsOrthogonal(termVector));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcDerivativeWorks) {
    Term const x(Monomial(1, {{"t", 3}}));
    Term const y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    Term const termToVerify(getLengthOfArcDerivative(termVector, "t"));

    string const stringToExpect("((9[t^4] + 16[t^2])^(1/2))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcWorks) {
    Term const x(Monomial(1, {{"t", 3}}));
    Term const y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    Term const termToVerify(getLengthOfArc(termVector, "t"));

    string const stringToExpect("(((9[t^2] + 16)^(3/2))/27)");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLengthOfArcFromStartToEndWorks) {
    Term const x(Monomial(1, {{"t", 3}}));
    Term const y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    Term const termToVerify(getLengthOfArcFromStartToEnd(termVector, {"t", -2, 0}));

    EXPECT_EQ(Term(-11.5176789869724), termToVerify);
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurvatureWorks) {
    Term const x(Monomial(1, {{"t", 3}}));
    Term const y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    Term const termToVerify(getCurvature(termVector, "t"));

    string const stringToExpect("(12[t^-1]/((9[t^2] + 16)^(3/2)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetTermThatYieldsToThisGradientWorksWithExample1) {
    Term const x(Polynomial{Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(4, {})});
    Term const y(Polynomial{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(4, {{"y", 1}}), Monomial(-5, {})});
    MathVectorOfTwoTerms const gradient{x, y};

    bool isExactDifferential(false);
    Term const termToVerify(getTermThatYieldsToThisGradient(gradient, {"x", "y"}, isExactDifferential));

    string const stringToExpect("(1[x][y^2] + 1[x^2] + 2[y^2] + 4[x] + -5[y])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
    EXPECT_TRUE(isExactDifferential);
}

TEST(MathVectorOfTermsUtilitiesTest, GetTermThatYieldsToThisGradientWorksWithExample2) {
    Term const x(Polynomial{Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(4, {})});
    Term const y(5);
    MathVectorOfTwoTerms const gradient{x, y};

    bool isExactDifferential(false);
    Term const termToVerify(getTermThatYieldsToThisGradient(gradient, {"x", "y"}, isExactDifferential));

    string const stringToExpect("{EmptyTerm}");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
    EXPECT_FALSE(isExactDifferential);
}

TEST(MathVectorOfTermsUtilitiesTest, GetTermThatYieldsToThisGradientWorksWithExample3) {
    Term const eToTheX(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    Term const x(createExpressionIfPossible({eToTheX, "*", sin("z"), "+", Monomial(2, {{"y", 1}, {"z", 1}})}));
    Term const y(Polynomial{Monomial(2, {{"x", 1}, {"z", 1}}), Monomial(2, {{"y", 1}})});
    Term const z(createExpressionIfPossible(
        {eToTheX, "*", cos("z"), "+", Polynomial{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(3, {{"z", 2}})}}));
    MathVectorOfThreeTerms const gradient{x, y, z};

    bool isExactDifferential(false);
    Term const termToVerify(getTermThatYieldsToThisGradient(gradient, {"x", "y", "z"}, isExactDifferential));

    string const stringToExpect("((2[x][y][z] + 1[z^3] + 1[y^2])+(((e)^x)*sin(z)))");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
    EXPECT_TRUE(isExactDifferential);
}

TEST(MathVectorOfTermsUtilitiesTest, GetPotentialFunctionForVectorFieldGradientWorks) {
    Term const x(Monomial(1, {{"y", -1}}));
    Term const y(Monomial(-1, {{"x", 1}, {"y", -2}}));
    MathVectorOfTwoTerms const gradient{x, y};

    bool isConservative(false);
    Term const termToVerify(getPotentialFunctionForVectorFieldGradient(gradient, {"x", "y"}, isConservative));

    string const stringToExpect("1[x][y^-1]");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
    EXPECT_TRUE(isConservative);
}

TEST(MathVectorOfTermsUtilitiesTest, GetDivergenceWorks) {
    Term const x(createExpressionIfPossible({getEAsATerm(), "^", Monomial(2, {{"x", 1}})}));
    Term const y(Monomial(3, {{"x", 2}, {"y", 1}, {"z", 1}}));
    Term const z(Polynomial{Monomial(2, {{"y", 2}, {"z", 1}}), Monomial(1, {{"x", 1}})});
    MathVectorOfThreeTerms const vectorField{x, y, z};

    Term const termToVerify(getDivergence(vectorField, {"x", "y", "z"}));

    string const stringToExpect("((2*((e)^2[x]))+3[x^2][z]+2[y^2])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLaplaceTermWorks) {
    Term const x(createExpressionIfPossible({getEAsATerm(), "^", Monomial(2, {{"x", 1}})}));
    Term const y(Monomial(3, {{"x", 2}, {"y", 2}, {"z", 1}}));
    Term const z(Polynomial{Monomial(2, {{"y", 2}, {"z", 2}}), Monomial(1, {{"x", 1}})});
    MathVectorOfThreeTerms const vectorField{x, y, z};

    Term const termToVerify(getLaplaceTerm(vectorField, {"x", "y", "z"}));

    string const stringToExpect("((4*((e)^2[x]))+6[x^2][z]+4[y^2])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralWorksOnExample1) {
    // Suppose a particle moves along the parabola y=x^2 from the point (-1,1) to the point (2,4).
    // Find the total work done if the motion is caused by the force field F(x, y) = (x^2 + y^2)i + (3*x^2*y)j
    Term const forceInX(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})});
    Term const forceInY(Monomial(3, {{"x", 2}, {"y", 1}}));
    MathVectorOfTwoTerms const vectorField{forceInX, forceInY};
    MathVectorOfTwoTerms const linePath{"t", Monomial(1, {{"t", 2}})};  // this is a parabola
    Term const termToVerify(getLineIntegral(vectorField, {"x", "y"}, linePath, {"t", -1, 2}));

    string const stringToExpect("(363/5)");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralWorksOnExample2) {
    Term const fieldInX(Monomial(3, {{"x", 1}, {"d[x]", 1}}));
    Term const fieldInY(Monomial(2, {{"x", 1}, {"y", 1}, {"d[y]", 1}}));
    Term const fieldInZ(Monomial(1, {{"z", 1}, {"d[z]", 1}}));
    MathVectorOfThreeTerms const vectorField{fieldInX, fieldInY, fieldInZ};
    MathVectorOfThreeTerms const linePath{cos("t"), sin("t"), "t"};

    Term const termToVerify(getLineIntegral(vectorField, {"x", "y", "z"}, linePath, {"t", 0, 2 * getPiAsATerm()}));

    string const stringToExpect("19.7392");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralEqualsGetLineIntegralIndependentOfPath) {
    Term const x(Polynomial{Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(4, {})});
    Term const y(Polynomial{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(4, {{"y", 1}}), Monomial(-5, {})});
    MathVectorOfTwoTerms const vectorField{x, y};
    MathVectorOfTwoTerms const linePath{"t", "t"};

    Term const lineIntegral(getLineIntegral(vectorField, {"x", "y"}, linePath, {"t", 0, 1}));
    Term const lineIntegralIndependentOfPath(getLineIntegralIndependentOfPath(vectorField, {"x", "y"}, {0, 0}, {1, 1}));

    EXPECT_EQ(lineIntegral, lineIntegralIndependentOfPath);
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralIndependentOfPathWorksOnExample1) {
    Term const x(Polynomial{Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(4, {})});
    Term const y(Polynomial{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(4, {{"y", 1}}), Monomial(-5, {})});
    MathVectorOfTwoTerms const vectorField{x, y};

    Term const termToVerify(getLineIntegralIndependentOfPath(vectorField, {"x", "y"}, {0, 0}, {1, 1}));

    string const stringToExpect("3");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLineIntegralIndependentOfPathWorksOnExample2) {
    Term const x(Polynomial{Monomial(4, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(-1, {{"z", 1}})});
    Term const y(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-2, {{"y", 1}}), Monomial(1, {{"z", 1}})});
    Term const z(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}}), Monomial(2, {{"z", 1}})});
    MathVectorOfThreeTerms const vectorField{x, y, z};

    Term const termToVerify(getLineIntegralIndependentOfPath(vectorField, {"x", "y", "z"}, {4, -2, 1}, {-1, 2, 0}));

    string const stringToExpect("-13");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetLimitWorks) {
    Term const x(cos("t"));
    Term const y(createExpressionIfPossible({2, "*", getEAsATerm(), "^", "t"}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getLimit(termVector, "t", 0));

    string const stringToExpect("{1, 2}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, DifferentiateWorks) {
    Term const x(createExpressionIfPossible({2, "+", sin("t")}));
    Term const y(cos("t"));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(differentiate(termVector, "t"));

    string const stringToExpect("{cos(t), (-1*sin(t))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, IntegrateWorks) {
    Term const x(sin("t"));
    Term const y(createExpressionIfPossible({-3, "*", cos("t")}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(integrate(termVector, "t"));

    string const stringToExpect("{(-1*cos(t)), (-3*sin(t))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetUnitTangentVectorWorks) {
    Term const x(Monomial(1, {{"t", 3}}));
    Term const y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getUnitTangentVector(termVector, "t"));

    string const stringToExpect("{(3[t]/((9[t^2] + 16)^(1/2))), (4/((9[t^2] + 16)^(1/2)))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetUnitNormalVectorWorks) {
    Term const x(Monomial(1, {{"t", 3}}));
    Term const y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getUnitNormalVector(termVector, "t"));

    string const stringToExpect("{(4/((9[t^2] + 16)^(1/2))), (-3[t]/((9[t^2] + 16)^(1/2)))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetCurvatureVectorWorks) {
    Term const x(Monomial(1, {{"t", 3}}));
    Term const y(Monomial(2, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getCurvatureVector(termVector, "t"));

    string const stringToExpect("{(48/(81[t^5] + 288[t^3] + 256[t])), (-36/(81[t^4] + 288[t^2] + 256))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetGradientWorks) {
    Term const termToTest(Polynomial{
        Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}),
        Monomial(AlbaNumber::createFraction(1, 9), {{"y", 2}})});

    MathVectorOfTwoTerms const vectorToVerify(getGradient<2U>(termToTest, {"x", "y"}));

    string const stringToExpect("{(1/8)[x], (2/9)[y]}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(MathVectorOfTermsUtilitiesTest, GetDelWorks) {
    Term const x(Monomial(1, {{"x", 1}, {"y", 2}}));
    Term const y(Monomial(1, {{"x", 3}, {"y", 4}}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getDel(termVector, {"x", "y"}));

    string const stringToExpect("{1[y^2], 4[x^3][y^3]}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

}  // namespace alba::algebra::VectorUtilities
