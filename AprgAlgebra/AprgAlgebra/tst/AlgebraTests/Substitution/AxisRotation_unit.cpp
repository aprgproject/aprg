#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/AxisRotation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(AxisRotationTest, RotateTermByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Term const term1(5);
    Term const term2("x");
    Term const term3(Monomial(7, {{"x", 1}}));
    Term const term4(Polynomial{Monomial(9, {{"x", 1}}), Monomial(11, {{"y", 1}})});
    Term const term5(createExpressionIfPossible({"x", "^", "y"}));
    Term const term6(sin("x"));

    Term const termToVerify1(rotation.rotateTermByAngle(term1));
    Term const termToVerify2(rotation.rotateTermByAngle(term2));
    Term const termToVerify3(rotation.rotateTermByAngle(term3));
    Term const termToVerify4(rotation.rotateTermByAngle(term4));
    Term const termToVerify5(rotation.rotateTermByAngle(term5));
    Term const termToVerify6(rotation.rotateTermByAngle(term6));

    string const stringToExpect1("5");
    string const stringToExpect2("-1[x]");
    string const stringToExpect3("-7[x]");
    string const stringToExpect4("(-9[x] + -11[y])");
    string const stringToExpect5("(-1[x]^-1[y])");
    string const stringToExpect6("sin(-1[x])");
    EXPECT_EQ(stringToExpect1, convertToString(termToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(termToVerify2));
    EXPECT_EQ(stringToExpect3, convertToString(termToVerify3));
    EXPECT_EQ(stringToExpect4, convertToString(termToVerify4));
    EXPECT_EQ(stringToExpect5, convertToString(termToVerify5));
    EXPECT_EQ(stringToExpect6, convertToString(termToVerify6));
}

TEST(AxisRotationTest, RotateConstantByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Constant const constant(5);

    Term const termToVerify(rotation.rotateConstantByAngle(constant));

    string const stringToExpect("5");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotateVariableByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Variable const variable("x");

    Term const termToVerify(rotation.rotateVariableByAngle(variable));

    string const stringToExpect("-1[x]");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotateMonomialByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Monomial const monomial(7, {{"x", 1}});

    Term const termToVerify(rotation.rotateMonomialByAngle(monomial));

    string const stringToExpect("-7[x]");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotatePolynomialByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Polynomial const polynomial{Monomial(9, {{"x", 1}}), Monomial(11, {{"y", 1}})};

    Term const termToVerify(rotation.rotatePolynomialByAngle(polynomial));

    string const stringToExpect("(-9[x] + -11[y])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotateExpressionByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Expression const expression(createExpressionIfPossible({"x", "^", "y"}));

    Term const termToVerify(rotation.rotateExpressionByAngle(expression));

    string const stringToExpect("(-1[x]^-1[y])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

TEST(AxisRotationTest, RotateFunctionByAngleWorks) {
    AxisRotation rotation("x", "y", ALBA_NUMBER_PI.getDouble(), false);
    Function const functionObject(sin("x"));

    Term const termToVerify(rotation.rotateFunctionByAngle(functionObject));

    string const stringToExpect("sin(-1[x])");
    EXPECT_EQ(stringToExpect, convertToString(termToVerify));
}

}  // namespace alba::algebra
