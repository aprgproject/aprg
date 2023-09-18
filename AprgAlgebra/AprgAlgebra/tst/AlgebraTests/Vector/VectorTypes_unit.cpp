#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Vector/VectorTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(VectorTypesTest, GettingMagnitudeWorks) {
    Term const x(createExpressionIfPossible({2, "*", cos("t")}));
    Term const y(createExpressionIfPossible({2, "*", sin("t")}));
    MathVectorOfTwoTerms const termVector{x, y};

    Term magnitude(termVector.getMagnitude());
    magnitude.simplify();

    string const stringToExpect("((((2*cos(t))^2)+((2*sin(t))^2))^(1/2))");
    EXPECT_EQ(stringToExpect, convertToString(magnitude));
}

}  // namespace alba::algebra
