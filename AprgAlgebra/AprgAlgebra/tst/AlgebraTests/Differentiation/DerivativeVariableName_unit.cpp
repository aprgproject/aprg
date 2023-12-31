#include <Algebra/Differentiation/DerivativeVariableName.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(DerivativeVariableNameTest, ConstructionUsingParameterWorks) {
    DerivativeVariableName const derivativeVariableName(2, "x", "y");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(2, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("y", derivativeVariableName.getDependentVariable());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationExpressionWorksWithOneCharacterVariables) {
    DerivativeVariableName const derivativeVariableName("d[y]/d[x]");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(1, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("y", derivativeVariableName.getDependentVariable());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationExpressionWorksWithMultipleCharacterVariables) {
    DerivativeVariableName const derivativeVariableName("d[distance]/d[time]");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(1, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("time", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("distance", derivativeVariableName.getDependentVariable());
}

TEST(
    DerivativeVariableNameTest,
    ConstructionUsingLeibnizNotationExpressionWorksWithOneCharacterVariablesAndMultipleNumbers) {
    DerivativeVariableName const derivativeVariableName("d32[y]/d[x]32");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(32, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("y", derivativeVariableName.getDependentVariable());
}

TEST(
    DerivativeVariableNameTest,
    ConstructionUsingLeibnizNotationExpressionWorksWithMultipleCharacterVariablesAndMultipleNumbers) {
    DerivativeVariableName const derivativeVariableName("d175[distance]/d[time]175");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(175, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("time", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("distance", derivativeVariableName.getDependentVariable());
}

TEST(DerivativeVariableNameTest, GetNameInLeibnizNotationWorksWhenDifferentiationLevelIsOne) {
    DerivativeVariableName const derivativeVariableName(1, "time", "volume");

    EXPECT_EQ("d[volume]/d[time]", derivativeVariableName.getNameInLeibnizNotation());
}

TEST(DerivativeVariableNameTest, GetNameInLeibnizNotationWorksWhenDifferentiationLevelIsNotOne) {
    DerivativeVariableName const derivativeVariableName(46, "time", "volume");

    EXPECT_EQ("d46[volume]/d[time]46", derivativeVariableName.getNameInLeibnizNotation());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationExpressionWorksWithInvalidFormatResultsToInvalid) {
    DerivativeVariableName const derivativeVariableName("oisuadhfh");

    EXPECT_FALSE(derivativeVariableName.isValid());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationExpressionWorksWithNotEqualNumbersResultsToInvalid) {
    DerivativeVariableName const derivativeVariableName("d175[distance]/d[time]471");

    EXPECT_FALSE(derivativeVariableName.isValid());
}

}  // namespace alba::algebra
