#include <Algebra/Term/Utilities/MonomialHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::algebra {

TEST(MonomialHelpersTest, GetDegreeWorks) {
    Monomial const monomial1;
    Monomial const monomial2(-54, {{"x", 6}, {"y1", -1.25}});
    Monomial const monomial3(-54, {{"x", 1}});
    Monomial const monomial4(-54, {{"x", 2}});
    Monomial const monomial5(0, {{"x", 3}});
    Monomial const monomial6(1, {{"x", 4}});
    Monomial const monomial7(1, {});

    EXPECT_DOUBLE_EQ(0, getDegree(monomial1).getDouble());
    EXPECT_DOUBLE_EQ(4.75, getDegree(monomial2).getDouble());
    EXPECT_DOUBLE_EQ(1, getDegree(monomial3).getDouble());
    EXPECT_DOUBLE_EQ(2, getDegree(monomial4).getDouble());
    EXPECT_DOUBLE_EQ(3, getDegree(monomial5).getDouble());
    EXPECT_DOUBLE_EQ(4, getDegree(monomial6).getDouble());
    EXPECT_DOUBLE_EQ(0, getDegree(monomial7).getDouble());
}

TEST(MonomialHelpersTest, GetMaxExponentWorks) {
    Monomial const monomial1;
    Monomial const monomial2(23, {});
    Monomial const monomial3(-23, {});
    Monomial const monomial4(-54, {{"x", 6}});
    Monomial const monomial5(-54, {{"x", -6}});
    Monomial const monomial6(-54, {{"x", 6}, {"y", 1.25}});
    Monomial const monomial7(-54, {{"x", 6}, {"y", -1.25}});
    Monomial const monomial8(-54, {{"x", -6}, {"y", 1.25}});
    Monomial const monomial9(-54, {{"x", -6}, {"y", -1.25}});

    EXPECT_DOUBLE_EQ(0, getMaxExponent(monomial1).getDouble());
    EXPECT_DOUBLE_EQ(0, getMaxExponent(monomial2).getDouble());
    EXPECT_DOUBLE_EQ(0, getMaxExponent(monomial3).getDouble());
    EXPECT_DOUBLE_EQ(6, getMaxExponent(monomial4).getDouble());
    EXPECT_DOUBLE_EQ(-6, getMaxExponent(monomial5).getDouble());
    EXPECT_DOUBLE_EQ(6, getMaxExponent(monomial6).getDouble());
    EXPECT_DOUBLE_EQ(6, getMaxExponent(monomial7).getDouble());
    EXPECT_DOUBLE_EQ(1.25, getMaxExponent(monomial8).getDouble());
    EXPECT_DOUBLE_EQ(-1.25, getMaxExponent(monomial9).getDouble());
}

TEST(MonomialHelpersTest, GetGcfOfExponentsInMonomialWorks) {
    Monomial const monomial(
        1, {{"x", AlbaNumber::createFraction(1, 2)},
            {"y", AlbaNumber::createFraction(2, 7)},
            {"z", AlbaNumber::createFraction(9, 5)}});

    EXPECT_EQ(AlbaNumber::createFraction(1, 70), getGcfOfExponentsInMonomial(monomial));
}

TEST(MonomialHelpersTest, GetGcfOfCoefficientsInMonomialsWorks) {
    EXPECT_EQ(AlbaNumber(2), getGcfOfCoefficientsInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    EXPECT_EQ(AlbaNumber(4), getGcfOfCoefficientsInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    EXPECT_EQ(AlbaNumber(1), getGcfOfCoefficientsInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {{"x", 9}})}));
    EXPECT_EQ(
        AlbaNumber::createFraction(1, 4),
        getGcfOfCoefficientsInMonomials({Monomial(AlbaNumber::createFraction(1, 4), {{"x", 1}}), Monomial(5, {})}));
    EXPECT_EQ(AlbaNumber(5), getGcfOfCoefficientsInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    EXPECT_EQ(AlbaNumber(3), getGcfOfCoefficientsInMonomials({Monomial(6, {}), Monomial(9, {})}));
}

TEST(MonomialHelpersTest, GetLcmOfCoefficientsInMonomialsWorks) {
    EXPECT_EQ(AlbaNumber(2), getLcmOfCoefficientsInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    EXPECT_EQ(AlbaNumber(8), getLcmOfCoefficientsInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    EXPECT_EQ(AlbaNumber(4), getLcmOfCoefficientsInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {{"x", 9}})}));
    EXPECT_EQ(
        AlbaNumber(5),
        getLcmOfCoefficientsInMonomials({Monomial(AlbaNumber::createFraction(1, 4), {{"x", 1}}), Monomial(5, {})}));
    EXPECT_EQ(AlbaNumber(5), getLcmOfCoefficientsInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    EXPECT_EQ(AlbaNumber(18), getLcmOfCoefficientsInMonomials({Monomial(6, {}), Monomial(9, {})}));
}

TEST(MonomialHelpersTest, GetCommonSignInMonomialsWorks) {
    EXPECT_EQ(AlbaNumber(1), getCommonSignInMonomials({}));
    EXPECT_EQ(AlbaNumber(1), getCommonSignInMonomials({Monomial(2, {}), Monomial(2, {}), Monomial(2, {})}));
    EXPECT_EQ(AlbaNumber(-1), getCommonSignInMonomials({Monomial(-2, {}), Monomial(-2, {}), Monomial(-2, {})}));
}

TEST(MonomialHelpersTest, GetGcfMonomialInMonomialsWorks) {
    Monomial const monomialToVerify1(getGcfMonomialInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial const monomialToVerify2(getGcfMonomialInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial const monomialToVerify3(getGcfMonomialInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {{"x", 9}})}));
    Monomial const monomialToVerify4(
        getGcfMonomialInMonomials({Monomial(AlbaNumber::createFraction(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial const monomialToVerify5(getGcfMonomialInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    Monomial const monomialToVerify6(getGcfMonomialInMonomials({Monomial(6, {}), Monomial(9, {})}));
    Monomial const monomialToVerify7(getGcfMonomialInMonomials({Monomial(-6, {}), Monomial(9, {})}));
    Monomial const monomialToVerify8(getGcfMonomialInMonomials({Monomial(6, {}), Monomial(-9, {})}));
    Monomial const monomialToVerify9(getGcfMonomialInMonomials({Monomial(1, {}), Monomial(1, {})}));
    Monomial const monomialToVerify10(getGcfMonomialInMonomials({Monomial(1, {}), Monomial(-1, {})}));
    Monomial const monomialToVerify11(getGcfMonomialInMonomials({Monomial(-1, {}), Monomial(1, {})}));
    Monomial const monomialToVerify12(getGcfMonomialInMonomials({Monomial(-1, {}), Monomial(-11, {})}));

    Monomial const monomialToExpect1(2, {{"x", 3}});
    Monomial const monomialToExpect2(4, {});
    Monomial const monomialToExpect3(1, {{"x", 1}});
    Monomial const monomialToExpect4(AlbaNumber::createFraction(1, 4), {});
    Monomial const monomialToExpect5(5, {{"x", -1}});
    Monomial const monomialToExpect6(3, {});
    Monomial const monomialToExpect7(-3, {});
    Monomial const monomialToExpect8(3, {});
    Monomial const monomialToExpect9(1, {});
    Monomial const monomialToExpect10(1, {});
    Monomial const monomialToExpect11(1, {});
    Monomial const monomialToExpect12(1, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
    EXPECT_EQ(monomialToExpect7, monomialToVerify7);
    EXPECT_EQ(monomialToExpect8, monomialToVerify8);
    EXPECT_EQ(monomialToExpect9, monomialToVerify9);
    EXPECT_EQ(monomialToExpect10, monomialToVerify10);
    EXPECT_EQ(monomialToExpect11, monomialToVerify11);
    EXPECT_EQ(monomialToExpect12, monomialToVerify12);
}

TEST(MonomialHelpersTest, GetLcmMonomialInMonomialsWorks) {
    Monomial const monomialToVerify1(getLcmMonomialInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial const monomialToVerify2(getLcmMonomialInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial const monomialToVerify3(getLcmMonomialInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {})}));
    Monomial const monomialToVerify4(
        getLcmMonomialInMonomials({Monomial(AlbaNumber::createFraction(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial const monomialToVerify5(getLcmMonomialInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    Monomial const monomialToVerify6(getLcmMonomialInMonomials({Monomial(6, {}), Monomial(9, {})}));

    Monomial const monomialToExpect1(2, {{"x", 7}});
    Monomial const monomialToExpect2(8, {{"x", 3}, {"y", 7}});
    Monomial const monomialToExpect3(4, {{"x", 1}});
    Monomial const monomialToExpect4(5, {{"x", 1}});
    Monomial const monomialToExpect5(5, {{"x", 1}});
    Monomial const monomialToExpect6(18, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
}

TEST(MonomialHelpersTest, CompareMonomialsAndSaveMinimumExponentsForEachVariableWorks) {
    Monomial const monomial1(85, {{"a", -5}, {"b", 10}, {"x", 3}, {"y", 4}});
    Monomial const monomial2(356, {{"a", 10}, {"b", -5}, {"x", 5}, {"y", 2}});

    Monomial const monomialToVerify(compareMonomialsAndSaveMinimumExponentsForEachVariable(monomial1, monomial2));

    EXPECT_DOUBLE_EQ(1, monomialToVerify.getCoefficient().getDouble());
    Monomial::VariablesToExponentsMap const& variableMapToVerify(monomialToVerify.getVariablesToExponentsMap());
    ASSERT_EQ(4U, variableMapToVerify.size());
    EXPECT_DOUBLE_EQ(-5, variableMapToVerify.at("a").getDouble());
    EXPECT_DOUBLE_EQ(-5, variableMapToVerify.at("b").getDouble());
    EXPECT_DOUBLE_EQ(3, variableMapToVerify.at("x").getDouble());
    EXPECT_DOUBLE_EQ(2, variableMapToVerify.at("y").getDouble());
}

TEST(MonomialHelpersTest, CompareMonomialsAndSaveMaximumExponentsForEachVariableWorks) {
    Monomial const monomial1(85, {{"a", -5}, {"b", 10}, {"x", 3}, {"y", 4}});
    Monomial const monomial2(356, {{"a", 10}, {"b", -5}, {"x", 5}, {"y", 2}});

    Monomial const monomialToVerify(compareMonomialsAndSaveMaximumExponentsForEachVariable(monomial1, monomial2));

    EXPECT_DOUBLE_EQ(1, monomialToVerify.getCoefficient().getDouble());
    Monomial::VariablesToExponentsMap const& variableMapToVerify(monomialToVerify.getVariablesToExponentsMap());
    ASSERT_EQ(4U, variableMapToVerify.size());
    EXPECT_DOUBLE_EQ(10, variableMapToVerify.at("a").getDouble());
    EXPECT_DOUBLE_EQ(10, variableMapToVerify.at("b").getDouble());
    EXPECT_DOUBLE_EQ(5, variableMapToVerify.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMapToVerify.at("y").getDouble());
}

TEST(MonomialHelpersTest, GetMonomialWithMinimumExponentsInMonomialsWorks) {
    Monomial const monomialToVerify1(
        getMonomialWithMinimumExponentsInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial const monomialToVerify2(
        getMonomialWithMinimumExponentsInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial const monomialToVerify3(
        getMonomialWithMinimumExponentsInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {{"x", 9}})}));
    Monomial const monomialToVerify4(getMonomialWithMinimumExponentsInMonomials(
        {Monomial(AlbaNumber::createFraction(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial const monomialToVerify5(
        getMonomialWithMinimumExponentsInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    Monomial const monomialToVerify6(getMonomialWithMinimumExponentsInMonomials({Monomial(6, {}), Monomial(9, {})}));

    Monomial const monomialToExpect1(1, {{"x", 3}});
    Monomial const monomialToExpect2(1, {});
    Monomial const monomialToExpect3(1, {{"x", 1}});
    Monomial const monomialToExpect4(1, {});
    Monomial const monomialToExpect5(1, {{"x", -1}});
    Monomial const monomialToExpect6(1, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
}

TEST(MonomialHelpersTest, GetMonomialWithMaximumExponentsInMonomialsWorks) {
    Monomial const monomialToVerify1(
        getMonomialWithMaximumExponentsInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial const monomialToVerify2(
        getMonomialWithMaximumExponentsInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial const monomialToVerify3(
        getMonomialWithMaximumExponentsInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {})}));
    Monomial const monomialToVerify4(getMonomialWithMaximumExponentsInMonomials(
        {Monomial(AlbaNumber::createFraction(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial const monomialToVerify5(
        getMonomialWithMaximumExponentsInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    Monomial const monomialToVerify6(getMonomialWithMaximumExponentsInMonomials({Monomial(6, {}), Monomial(9, {})}));

    Monomial const monomialToExpect1(1, {{"x", 7}});
    Monomial const monomialToExpect2(1, {{"x", 3}, {"y", 7}});
    Monomial const monomialToExpect3(1, {{"x", 1}});
    Monomial const monomialToExpect4(1, {{"x", 1}});
    Monomial const monomialToExpect5(1, {{"x", 1}});
    Monomial const monomialToExpect6(1, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
}

TEST(MonomialHelpersTest, GetFirstVariableNameFunctionWorks) {
    Monomial const monomial1;
    Monomial const monomial2(-54, {{"x1", 6}, {"y1", -1.25}});
    Monomial const monomial3(-54, {{"x2", 6}});
    Monomial const monomial4(-54, {{"x3", 1}});
    Monomial const monomial5(0, {{"x4", 1}});
    Monomial const monomial6(1, {{"x5", 1}});
    Monomial const monomial7(1, {});

    EXPECT_TRUE(getFirstVariableName(monomial1).empty());
    EXPECT_EQ("x1", getFirstVariableName(monomial2));
    EXPECT_EQ("x2", getFirstVariableName(monomial3));
    EXPECT_EQ("x3", getFirstVariableName(monomial4));
    EXPECT_EQ("x4", getFirstVariableName(monomial5));
    EXPECT_EQ("x5", getFirstVariableName(monomial6));
    EXPECT_TRUE(getFirstVariableName(monomial7).empty());
}

TEST(MonomialHelpersTest, CanBeMergedByAdditionOrSubtractionForTermsWorks) {
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(73), Term(84)));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Variable("x")), Term(Variable("x"))));
    EXPECT_TRUE(
        canBeMergedInAMonomialByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Variable("x"))));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Variable("x")), Term(Monomial(96, {{"x", 1}}))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Variable("x")), Term(Variable("y"))));
    EXPECT_FALSE(
        canBeMergedInAMonomialByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Monomial(96, {{"x", 5}}))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Monomial(96, {{"a", 1}})), Term(Variable("x"))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Variable("x")), Term(Monomial(96, {{"a", 1}}))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Expression()), Term(Expression())));
}

TEST(MonomialHelpersTest, CanBeMergedByAdditionOrSubtractionForBothMonomialsWorks) {
    Monomial const monomial1;
    Monomial const monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial const monomial3(100, {{"x", 6}, {"y", -1.25}});
    Monomial const monomial4(100, {{"x", 5}, {"y", -1}});
    Monomial const monomial5(645, {{"i", 20}, {"y", 30}});

    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial1, monomial1));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, monomial2));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial3, monomial3));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial4, monomial4));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial5, monomial5));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial1, monomial2));
    // NOLINTBEGIN(readability-suspicious-call-argument)
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, monomial3));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, monomial4));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, monomial5));
    // NOLINTEND(readability-suspicious-call-argument)
}

TEST(MonomialHelpersTest, CanBeMergedByAdditionOrSubtractionForMonomialAndVariableWorks) {
    Monomial const monomial1;
    Monomial const monomial2(12, {{"x", 1}});
    Monomial const monomial3(34, {{"x", 1.25}});
    Monomial const monomial4(56, {{"x", 1}, {"y", 1}});
    Variable const variable("x");

    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial1, variable));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, variable));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial3, variable));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial4, variable));
}

TEST(MonomialHelpersTest, CanBeMergedByAdditionOrSubtractionForBothVariablesWorks) {
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Variable("x"), Variable("x")));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Variable("x"), Variable("w")));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Variable("w"), Variable("x")));
}

TEST(MonomialHelpersTest, DoesCoefficientsHaveSameSignWorks) {
    EXPECT_TRUE(doesCoefficientsHaveSameSign(Monomial(23, {}), Monomial(23, {})));
    EXPECT_FALSE(doesCoefficientsHaveSameSign(Monomial(-23, {}), Monomial(23, {})));
    EXPECT_FALSE(doesCoefficientsHaveSameSign(Monomial(23, {}), Monomial(-23, {})));
    EXPECT_TRUE(doesCoefficientsHaveSameSign(Monomial(-23, {}), Monomial(-23, {})));
}

TEST(MonomialHelpersTest, HasNegativeExponentsWorks) {
    EXPECT_FALSE(hasNegativeExponents(Monomial()));
    EXPECT_FALSE(hasNegativeExponents(Monomial(23, {})));
    EXPECT_FALSE(hasNegativeExponents(Monomial(-23, {})));
    EXPECT_FALSE(hasNegativeExponents(Monomial(-54, {{"x", 6}})));
    EXPECT_TRUE(hasNegativeExponents(Monomial(-54, {{"x", -6}})));
    EXPECT_FALSE(hasNegativeExponents(Monomial(-54, {{"x", 6}, {"y", 1.25}})));
    EXPECT_TRUE(hasNegativeExponents(Monomial(-54, {{"x", 6}, {"y", -1.25}})));
    EXPECT_TRUE(hasNegativeExponents(Monomial(-54, {{"x", -6}, {"y", 1.25}})));
    EXPECT_TRUE(hasNegativeExponents(Monomial(-54, {{"x", -6}, {"y", -1.25}})));
}

TEST(MonomialHelpersTest, IsConstantOnlyFunctionWorks) {
    Monomial const monomial1;
    Monomial const monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial const monomial3(23, {});

    EXPECT_TRUE(isConstantOnly(monomial1));
    EXPECT_FALSE(isConstantOnly(monomial2));
    EXPECT_TRUE(isConstantOnly(monomial3));
}

TEST(MonomialHelpersTest, IsVariableOnlyFunctionWorks) {
    Monomial const monomial1;
    Monomial const monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial const monomial3(-54, {{"x", 6}});
    Monomial const monomial4(-54, {{"x", 1}});
    Monomial const monomial5(0, {{"x", 1}});
    Monomial const monomial6(1, {{"x", 1}, {"y", 1}});
    Monomial const monomial7(1, {{"x", 1}});

    EXPECT_FALSE(isVariableOnly(monomial1));
    EXPECT_FALSE(isVariableOnly(monomial2));
    EXPECT_FALSE(isVariableOnly(monomial3));
    EXPECT_FALSE(isVariableOnly(monomial4));
    EXPECT_FALSE(isVariableOnly(monomial5));
    EXPECT_FALSE(isVariableOnly(monomial6));
    EXPECT_TRUE(isVariableOnly(monomial7));
}

TEST(MonomialHelpersTest, HasASingleVariableWorks) {
    Monomial const monomial1;
    Monomial const monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial const monomial3(-54, {{"x", 6}});

    EXPECT_FALSE(hasASingleVariable(monomial1));
    EXPECT_FALSE(hasASingleVariable(monomial2));
    EXPECT_TRUE(hasASingleVariable(monomial3));
}

}  // namespace alba::algebra
