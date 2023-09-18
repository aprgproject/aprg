#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

TEST(ContinuityTest, GetContinuityTypeAtWorksForRemovableDiscontinuityFunction) {
    Function const functionToTest("functionToTest", Term("x"), [](AlbaNumber const& number) {
        AlbaNumber result;
        if (number == 3) {
            result = 2;
        } else {
            result = getAbsoluteValue(number - 3);
        }
        return result;
    });
    Term const functionTermToTest(functionToTest);

    EXPECT_EQ(ContinuityType::DiscontinuousWithRemovableDiscontinuity, getContinuityTypeAt(functionTermToTest, "x", 3));
}

TEST(ContinuityTest, GetContinuityTypeAtWorksForEssentialDiscontinuityFunction) {
    Function const functionToTest("functionToTest", Term("x"), [](AlbaNumber const& number) {
        AlbaNumber result;
        if (number <= 1) {
            result = number + 3;
        } else {
            result = number - 3;
        }
        return result;
    });
    Term const functionTermToTest(functionToTest);

    EXPECT_EQ(ContinuityType::DiscontinuousWithEssentialDiscontinuity, getContinuityTypeAt(functionTermToTest, "x", 1));
}

TEST(ContinuityTest, GetContinuityTypeAtWorksForPolynomialOverPolynomial) {
    Polynomial const numerator{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})};
    Polynomial const denominator{Monomial(1, {{"x", 1}}), Monomial(-4, {})};
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(ContinuityType::DiscontinuousWithRemovableDiscontinuity, getContinuityTypeAt(termToTest, "x", 4));
}

TEST(ContinuityTest, GetContinuityDomainWorksOnPolynomial) {
    Term const polynomialTerm(
        Polynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(1, {})});

    SolutionSet const continuityDomain(getContinuityDomain(polynomialTerm));

    AlbaNumberIntervals const& intervalToVerify(continuityDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify.size());
    EXPECT_EQ(createAllRealValuesInterval(), intervalToVerify.front());
}

TEST(ContinuityTest, GetContinuityDomainWorksOnPolynomialOverPolynomial) {
    Polynomial const numerator{Monomial(1, {{"x", 3}}), Monomial(1, {})};
    Polynomial const denominator{Monomial(1, {{"x", 2}}), Monomial(-9, {})};
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    SolutionSet const continuityDomain(getContinuityDomain(termToTest));

    AlbaNumberIntervals const& intervalToVerify(continuityDomain.getAcceptedIntervals());
    ASSERT_EQ(3U, intervalToVerify.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(-3)), intervalToVerify[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3)), intervalToVerify[1]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(3), createPositiveInfinityOpenEndpoint()), intervalToVerify[2]);
}

TEST(ContinuityTest, GetContinuityDomainWorksOnSquareRootOfPolynomial) {
    Term const polynomialTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {})});
    Term const termToTest(createExpressionIfPossible({polynomialTerm, "^", AlbaNumber::createFraction(1, 2)}));

    SolutionSet const continuityDomain(getContinuityDomain(termToTest));

    AlbaNumberIntervals const& intervalToVerify(continuityDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-2), createCloseEndpoint(2)), intervalToVerify[0]);
}

TEST(ContinuityTest, GetContinuityDomainWorksOnFunctions) {
    SolutionSet const continuityDomain1(getContinuityDomain(Functions::abs("x")));
    SolutionSet const continuityDomain2(getContinuityDomain(Functions::sin("x")));
    SolutionSet const continuityDomain3(getContinuityDomain(Functions::cos("x")));
    SolutionSet const continuityDomain4(getContinuityDomain(Functions::tan("x")));

    AlbaNumberIntervals const& intervalToVerify1(continuityDomain1.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify1.size());
    EXPECT_EQ(createAllRealValuesInterval(), intervalToVerify1.front());
    AlbaNumberIntervals const& intervalToVerify2(continuityDomain2.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify2.size());
    EXPECT_EQ(createAllRealValuesInterval(), intervalToVerify2.front());
    AlbaNumberIntervals const& intervalToVerify3(continuityDomain3.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify3.size());
    EXPECT_EQ(createAllRealValuesInterval(), intervalToVerify3.front());
    AlbaNumberIntervals const& intervalToVerify4(continuityDomain4.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify4.size());
    EXPECT_EQ(createAllRealValuesInterval(), intervalToVerify4.front());
}

TEST(ContinuityTest, IsContinuousAtWorks) {
    Polynomial const denominator{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    Term const termToTest(createExpressionIfPossible({1, "/", denominator}));

    EXPECT_FALSE(isContinuousAt(termToTest, "x", 2));
    EXPECT_TRUE(isContinuousAt(termToTest, "x", 3));
}

TEST(ContinuityTest, IsContinuousAtWorksForContinuousPieceWiseFunction) {
    Function const functionToTest("functionToTest", Term("x"), [](AlbaNumber const& number) {
        AlbaNumber result;
        if (number <= 10) {
            result = number;
        } else {
            result = number * 0.7 + 3;
        }
        return result;
    });
    Term const functionTermToTest(functionToTest);

    EXPECT_TRUE(isContinuousAt(functionTermToTest, "x", 10, LimitAtAValueApproachType::BothSides));
}

TEST(ContinuityTest, IsContinuousAtWorksForDiscontinuousPieceWiseFunction) {
    Function const functionToTest("functionToTest", Term("x"), [](AlbaNumber const& number) {
        AlbaNumber result;
        if (number == 1) {
            result = 2;
        } else {
            result = number * 2 + 3;
        }
        return result;
    });
    Term const functionTermToTest(functionToTest);

    EXPECT_FALSE(isContinuousAt(functionTermToTest, "x", 1, LimitAtAValueApproachType::BothSides));
}

TEST(ContinuityTest, IsContinuousAtWorksOnTheEdgesOfSquareRootOfPolynomial) {
    Term const polynomialTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {})});
    Term const termToTest(createExpressionIfPossible({polynomialTerm, "^", AlbaNumber::createFraction(1, 2)}));

    EXPECT_FALSE(isContinuousAt(termToTest, "x", -2, LimitAtAValueApproachType::BothSides));
    EXPECT_TRUE(isContinuousAt(termToTest, "x", -2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_FALSE(isContinuousAt(termToTest, "x", -2, LimitAtAValueApproachType::NegativeSide));
    EXPECT_FALSE(isContinuousAt(termToTest, "x", 2, LimitAtAValueApproachType::BothSides));
    EXPECT_FALSE(isContinuousAt(termToTest, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_TRUE(isContinuousAt(termToTest, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(ContinuityTest, IsContinuousAtWorksWithIsDifferentiableAtValue) {
    Term const polynomialTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {})});
    Term const termToTest(createExpressionIfPossible({polynomialTerm, "^", AlbaNumber::createFraction(1, 2)}));

    EXPECT_FALSE(isContinuousAt(termToTest, "x", -2, LimitAtAValueApproachType::BothSides, false));
    EXPECT_TRUE(isContinuousAt(termToTest, "x", -2, LimitAtAValueApproachType::BothSides, true));
}

TEST(LimitTest, GetLimitWithMultipleVariablesWithDifferentApproachesWorksWhenItExists) {
    Term const numerator(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-1, {{"y", 4}})});
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})});
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SubstitutionsOfVariablesToTerms substitutions;
    // NOLINTBEGIN(hicpp-use-emplace,modernize-use-emplace)
    substitutions.emplace_back(SubstitutionOfVariablesToTerms{{"y", "x"}});
    substitutions.emplace_back(SubstitutionOfVariablesToTerms{{"y", Monomial(1, {{"x", 2}})}});
    // NOLINTEND(hicpp-use-emplace,modernize-use-emplace)
    EXPECT_TRUE(isContinuousAtWithMultipleVariablesWithDifferentApproaches(termToTest, "x", 0, substitutions));
}

TEST(LimitTest, GetLimitWithMultipleVariablesWithDifferentApproachesWorksWhenDoesNotItExist) {
    Term const numerator(Monomial(1, {{"x", 1}, {"y", 1}}));
    Term const denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})});
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SubstitutionsOfVariablesToTerms substitutions;
    // NOLINTBEGIN(hicpp-use-emplace,modernize-use-emplace)
    substitutions.emplace_back(SubstitutionOfVariablesToTerms{{"y", "x"}});
    substitutions.emplace_back(SubstitutionOfVariablesToTerms{{"y", Monomial(1, {{"x", 2}})}});
    // NOLINTEND(hicpp-use-emplace,modernize-use-emplace)
    EXPECT_FALSE(isContinuousAtWithMultipleVariablesWithDifferentApproaches(termToTest, "x", 0, substitutions));
}

TEST(ContinuityTest, IsIntermediateValueTheoremSatisfiedWorks) {
    Polynomial const numerator{Monomial(2, {})};
    Polynomial const denominator{Monomial(1, {{"x", 1}}), Monomial(-4, {})};
    Term const termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_FALSE(isIntermediateValueTheoremSatisfied(termToTest, "x", 2, 5, 4));
    EXPECT_TRUE(isIntermediateValueTheoremSatisfied(termToTest, "x", 5, 7, 6));
}

}  // namespace alba::algebra
