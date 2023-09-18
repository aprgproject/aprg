#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Vector/PlaneMotionUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra::VectorUtilities {

TEST(PlaneMotionUtilitiesTest, GetInstantaneousVelocityWorks) {
    Term const x(createExpressionIfPossible({getEAsATerm(), "^", "(", -2, "*", "t", ")"}));
    Term const y(createExpressionIfPossible({3, "*", getEAsATerm(), "^", "t"}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getInstantaneousVelocity(termVector, "t"));

    string const stringToExpect("{(-2/((e)^2[t])), (3*((e)^t))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(PlaneMotionUtilitiesTest, GetInstantaneousAccelerationFromVelocityWorks) {
    Term const x(createExpressionIfPossible({getEAsATerm(), "^", "(", -2, "*", "t", ")"}));
    Term const y(createExpressionIfPossible({3, "*", getEAsATerm(), "^", "t"}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getInstantaneousAccelerationFromVelocity(termVector, "t"));

    string const stringToExpect("{(-2/((e)^2[t])), (3*((e)^t))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(PlaneMotionUtilitiesTest, GetInstantaneousAccelerationFromPathWorks) {
    Term const x(Monomial(2, {{"t", 3}}));
    Term const y(Monomial(4, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getInstantaneousAccelerationFromPath(termVector, "t"));

    string const stringToExpect("{12[t], 8}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(PlaneMotionUtilitiesTest, GetTangentPartOfAccelerationWorks) {
    Term const x(Monomial(2, {{"t", 3}}));
    Term const y(Monomial(4, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getTangentPartOfAcceleration(termVector, "t"));

    string const stringToExpect(
        "{((36[t^5] + 216[t^3] + 192[t])/((1[t^2] + 4)^(3/2))/((9[t^2] + 16)^(1/2))), ((48[t^4] + 288[t^2] + "
        "256)/((1[t^2] + 4)^(3/2))/((9[t^2] + 16)^(1/2)))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(PlaneMotionUtilitiesTest, GetNormalPartOfAccelerationWorks) {
    Term const x(Monomial(2, {{"t", 3}}));
    Term const y(Monomial(4, {{"t", 2}}));
    MathVectorOfTwoTerms const termVector{x, y};

    MathVectorOfTwoTerms const vectorToVerify(getNormalPartOfAcceleration(termVector, "t"));

    string const stringToExpect(
        "{((864[t^5] + 4608[t^3] + 6144[t])/(81[t^6] + 612[t^4] + 1408[t^2] + 1024)), ((-648[t^6] + -3456[t^4] + "
        "-4608[t^2])/(81[t^6] + 612[t^4] + 1408[t^2] + 1024))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

}  // namespace alba::algebra::VectorUtilities
