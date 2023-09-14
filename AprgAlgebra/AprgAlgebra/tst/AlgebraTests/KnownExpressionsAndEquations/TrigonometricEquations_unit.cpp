#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/KnownExpressionsAndEquations/TrigonometricEquations.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

TEST(TrigonometricEquationsTest, GetTrigonometricPythagoreanIdentityWorks) {
    Equation const actualEquation(getTrigonometricPythagoreanIdentity("x"));

    Term const expectedSineSquaredTerm(createExpressionIfPossible({sin("x"), "^", 2}));
    Term const expectedCosineSquaredTerm(createExpressionIfPossible({cos("x"), "^", 2}));
    Term const leftHandSide(createExpressionIfPossible({expectedSineSquaredTerm, "+", expectedCosineSquaredTerm}));
    Equation const expectedEquation(leftHandSide, "=", 1);
    EXPECT_EQ(expectedEquation, actualEquation);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", 5);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetSineEquationOfRightTriangleWorks) {
    Equation const actualEquation(getSineEquationOfRightTriangle("x", "o", "h"));

    Term const leftHandSide(sin("x"));
    Term const rightHandSide(createExpressionIfPossible({"o", "/", "h"}));
    Equation const expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 6);
    substitution.putVariableWithValue("o", 5);
    substitution.putVariableWithValue("h", 10);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetCosineEquationOfRightTriangleWorks) {
    Equation const actualEquation(getCosineEquationOfRightTriangle("x", "a", "h"));

    Term const leftHandSide(cos("x"));
    Term const rightHandSide(createExpressionIfPossible({"a", "/", "h"}));
    Equation const expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 6);
    substitution.putVariableWithValue("a", 5 * sqrt(3));
    substitution.putVariableWithValue("h", 10);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetTangentEquationOfRightTriangleWorks) {
    Equation const actualEquation(getTangentEquationOfRightTriangle("x", "o", "a"));

    Term const leftHandSide(tan("x"));
    Term const rightHandSide(createExpressionIfPossible({"o", "/", "a"}));
    Equation const expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 6);
    substitution.putVariableWithValue("o", 5);
    substitution.putVariableWithValue("a", 5 * sqrt(3));
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetLawOfSineEquationWorks) {
    Equation const actualEquation(getLawOfSineEquation("s1", "a1", "s2", "a2"));

    Term const leftHandSide(createExpressionIfPossible({"s1", "/", sin("a1")}));
    Term const rightHandSide(createExpressionIfPossible({"s2", "/", sin("a2")}));
    Equation const expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("s1", 5);
    substitution.putVariableWithValue("a1", getPi() / 6);
    substitution.putVariableWithValue("s2", 5 * sqrt(3));
    substitution.putVariableWithValue("a2", getPi() / 3);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetLawOfCosineEquationWorks) {
    Equation const actualEquation(getLawOfCosineEquation("s1", "s2", "s3", "a1"));

    Term const side1Squared(createExpressionIfPossible({"s1", "^", 2}));
    Term const side2Squared(createExpressionIfPossible({"s2", "^", 2}));
    Term const side3Squared(createExpressionIfPossible({"s3", "^", 2}));
    Term const cosinePart(createExpressionIfPossible({2, "*", "s2", "*", "s3", "*", cos("a1")}));
    Term const& leftHandSide(side1Squared);
    Term const rightHandSide(createExpressionIfPossible({side2Squared, "+", side3Squared, "-", cosinePart}));
    Equation const expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("s1", 5);
    substitution.putVariableWithValue("s2", 5 * sqrt(3));
    substitution.putVariableWithValue("s3", 10);
    substitution.putVariableWithValue("a1", getPi() / 6);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetSineSquaredWorks) {
    Term const actualTerm(getSineSquared("x"));

    Term const expectedTerm(createExpressionIfPossible({sin("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetCosineOfDoubledValueWorks) {
    Term const actualCosineOfDoubledValue(getCosineOfDoubledValue("x"));

    Term const expectedCosineOfDoubledValue(
        createExpressionIfPossible({getCosineSquared("x"), "-", getSineSquared("x")}));
    EXPECT_EQ(expectedCosineOfDoubledValue, actualCosineOfDoubledValue);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualCosineOfDoubledValue));
}

TEST(TrigonometricEquationsTest, GetSineSquaredInCosineWorks) {
    Term const actualTerm(getSineSquaredInCosine("x"));

    Term const expectedTerm(createExpressionIfPossible({1, "-", cos("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetCosineSquaredWorks) {
    Term const actualTerm(getCosineSquared("x"));

    Term const expectedTerm(createExpressionIfPossible({cos("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetCosineSquaredInSineWorks) {
    Term const actualTerm(getCosineSquaredInSine("x"));

    Term const expectedTerm(createExpressionIfPossible({1, "-", sin("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetTangentSquaredWorks) {
    Term const actualTerm(getTangentSquared("x"));

    Term const expectedTerm(createExpressionIfPossible({tan("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 4);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetTangentOfDoubledValueWorks) {
    Term const actualTangentOfDoubledValue(getTangentOfDoubledValue("x"));

    Term const expectedNumerator(createExpressionIfPossible({2, "*", tan("x")}));
    Term const expectedDenominator(createExpressionIfPossible({1, "-", getTangentSquared("x")}));
    Term const expectedTangentOfDoubledValue(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expectedTangentOfDoubledValue, actualTangentOfDoubledValue);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 8);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(expectedTangentOfDoubledValue));
}

TEST(TrigonometricEquationsTest, GetSineOfSumOrDifferenceOfTwoTermsWorks) {
    Term const actualSineOfSumOfValues(getSineOfSumOrDifferenceOfTwoTerms("x", Operator("+"), "y"));
    Term const actualSineOfDifferenceOfValues(getSineOfSumOrDifferenceOfTwoTerms("x", Operator("-"), "y"));

    Term const firstPart(createExpressionIfPossible({sin("x"), "*", cos("y")}));
    Term const secondPart(createExpressionIfPossible({cos("x"), "*", sin("y")}));
    Term const expectedSineOfSumOfValues(createExpressionIfPossible({firstPart, "+", secondPart}));
    Term const expectedSineOfDifferenceOfValues(createExpressionIfPossible({firstPart, "-", secondPart}));
    EXPECT_EQ(expectedSineOfSumOfValues, actualSineOfSumOfValues);
    EXPECT_EQ(expectedSineOfDifferenceOfValues, actualSineOfDifferenceOfValues);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 12);
    substitution.putVariableWithValue("y", getPi() / 12);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualSineOfSumOfValues));
    EXPECT_EQ(Term(0), substitution.performSubstitutionTo(actualSineOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetCosineOfSumOrDifferenceOfTwoTermsWorks) {
    Term const actualCosineOfSumOfValues(getCosineOfSumOrDifferenceOfTwoTerms("x", Operator("+"), "y"));
    Term const actualCosineOfDifferenceOfValues(getCosineOfSumOrDifferenceOfTwoTerms("x", Operator("-"), "y"));

    Term const firstPart(createExpressionIfPossible({cos("x"), "*", cos("y")}));
    Term const secondPart(createExpressionIfPossible({sin("x"), "*", sin("y")}));
    Term const expectedCosineOfSumOfValues(createExpressionIfPossible({firstPart, "-", secondPart}));
    Term const expectedCosineOfDifferenceOfValues(createExpressionIfPossible({firstPart, "+", secondPart}));
    EXPECT_EQ(expectedCosineOfSumOfValues, actualCosineOfSumOfValues);
    EXPECT_EQ(expectedCosineOfDifferenceOfValues, actualCosineOfDifferenceOfValues);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 6);
    substitution.putVariableWithValue("y", getPi() / 6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualCosineOfSumOfValues));
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualCosineOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetTangentOfSumOrDifferenceOfTwoTermsWorks) {
    Term const actualTangentOfSumOfValues(getTangentOfSumOrDifferenceOfTwoTerms("x", Operator("+"), "y"));
    Term const actualTangentOfDifferenceOfValues(getTangentOfSumOrDifferenceOfTwoTerms("x", Operator("-"), "y"));

    Term const numeratorSum(createExpressionIfPossible({tan("x"), "+", tan("y")}));
    Term const denominatorSum(
        createExpressionIfPossible({1, "-", createExpressionIfPossible({tan("x"), "*", tan("y")})}));
    Term const numeratorDifference(createExpressionIfPossible({tan("x"), "-", tan("y")}));
    Term const denominatorDifference(
        createExpressionIfPossible({1, "+", createExpressionIfPossible({tan("x"), "*", tan("y")})}));
    Term const expectedTangentOfSumOfValues(createExpressionIfPossible({numeratorSum, "/", denominatorSum}));
    Term const expectedTangentOfDifferenceOfValues(
        createExpressionIfPossible({numeratorDifference, "/", denominatorDifference}));
    EXPECT_EQ(expectedTangentOfSumOfValues, actualTangentOfSumOfValues);
    EXPECT_EQ(expectedTangentOfDifferenceOfValues, actualTangentOfDifferenceOfValues);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 8);
    substitution.putVariableWithValue("y", getPi() / 8);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualTangentOfSumOfValues));
    EXPECT_EQ(Term(0), substitution.performSubstitutionTo(actualTangentOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetSineOfDoubledValueWorks) {
    Term const actualSineOfDoubledValue(getSineOfDoubledValue("x"));

    Term const expectedSineOfDoubledValue(createExpressionIfPossible({2, "*", sin("x"), "*", cos("x")}));
    EXPECT_EQ(expectedSineOfDoubledValue, actualSineOfDoubledValue);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 12);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualSineOfDoubledValue));
}

TEST(TrigonometricEquationsTest, GetSineOfHalvedValueWorks) {
    Term const actualPositiveRoot(getSineOfHalvedValue("x", true));
    Term const actualNegativeRoot(getSineOfHalvedValue("x", false));

    Term const numerator(createExpressionIfPossible({1, "-", cos("x")}));
    Term const squaredValue(createExpressionIfPossible({numerator, "/", 2}));
    Term const expectedPositiveRoot(createExpressionIfPossible({squaredValue, "^", AlbaNumber::createFraction(1, 2)}));
    Term const expectedNegativeRoot(createExpressionIfPossible({-1, "*", expectedPositiveRoot}));
    EXPECT_EQ(expectedPositiveRoot, actualPositiveRoot);
    EXPECT_EQ(expectedNegativeRoot, actualNegativeRoot);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() / 3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualPositiveRoot));
    EXPECT_EQ(Term(AlbaNumber::createFraction(-1, 2)), substitution.performSubstitutionTo(actualNegativeRoot));
}

TEST(TrigonometricEquationsTest, GetCosineOfHalvedValueWorks) {
    Term const actualPositiveRoot(getCosineOfHalvedValue("x", true));
    Term const actualNegativeRoot(getCosineOfHalvedValue("x", false));

    Term const numerator(createExpressionIfPossible({1, "+", cos("x")}));
    Term const squaredValue(createExpressionIfPossible({numerator, "/", 2}));
    Term const expectedPositiveRoot(createExpressionIfPossible({squaredValue, "^", AlbaNumber::createFraction(1, 2)}));
    Term const expectedNegativeRoot(createExpressionIfPossible({-1, "*", expectedPositiveRoot}));
    EXPECT_EQ(expectedPositiveRoot, actualPositiveRoot);
    EXPECT_EQ(expectedNegativeRoot, actualNegativeRoot);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi() * 2 / 3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualPositiveRoot));
    EXPECT_EQ(Term(AlbaNumber::createFraction(-1, 2)), substitution.performSubstitutionTo(actualNegativeRoot));
}

TEST(TrigonometricEquationsTest, GetSineSquaredOfHalvedValueWorks) {
    Term const termToVerify(getSineSquaredOfHalvedValue("x"));

    Term const numerator(createExpressionIfPossible({1, "-", cos("x")}));
    Term const termToExpect(createExpressionIfPossible({numerator, "/", 2}));
    EXPECT_EQ(termToExpect, termToVerify);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi());
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(termToVerify));
}

TEST(TrigonometricEquationsTest, GetCosineSquaredOfHalvedValueWorks) {
    Term const termToVerify(getCosineSquaredOfHalvedValue("x"));

    Term const numerator(createExpressionIfPossible({1, "+", cos("x")}));
    Term const termToExpect(createExpressionIfPossible({numerator, "/", 2}));
    EXPECT_EQ(termToExpect, termToVerify);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi());
    EXPECT_EQ(Term(0), substitution.performSubstitutionTo(termToVerify));
}

}  // namespace alba::algebra
