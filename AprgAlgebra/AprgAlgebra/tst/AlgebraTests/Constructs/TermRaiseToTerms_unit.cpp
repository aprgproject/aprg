#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;

namespace alba::algebra {

TEST(TermRaiseToTermsTest, GetCombinedTermWorks) {
    TermRaiseToTerms const termRaiseToTerms("base", {"exponent1", "exponent2"});

    Term const expectedTerm(
        createExpressionIfPossible({"base", "^", Monomial(1, {{"exponent1", 1}, {"exponent2", 1}})}));
    EXPECT_EQ(expectedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithSimplifyingToFactors) {
    Term const base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, 5);
    termRaiseToTerms.setAsShouldSimplifyToFactors(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails const expectedExponents{TermWithDetails(Term(5), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term const expectedCombinedTerm(
        createExpressionIfPossible({Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", 5}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsZero) {
    Term const base(0);
    TermRaiseToTerms termRaiseToTerms(base, {"a", "b"});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(0), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(0), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsOne) {
    Term const base(1);
    TermRaiseToTerms termRaiseToTerms(base, {"a", "b"});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(1), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenThereAreNoExponents) {
    Term const base("base");
    TermRaiseToTerms termRaiseToTerms(base, Terms{});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term("base"), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentIsZero) {
    Term const base("base");
    TermRaiseToTerms termRaiseToTerms(base, {0, "anotherExponent"});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(1), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentIsOne) {
    Term const base("base");
    TermRaiseToTerms termRaiseToTerms(base, {1, 1});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term("base"), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsMonomialAndExponentIsNumber) {
    Term const base(Monomial(1, {{"x", 2}}));
    TermRaiseToTerms termRaiseToTerms(base, AlbaNumber::createFraction(1, 2));

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(Term("x"), termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenBaseIsPolynomialAndExponentIsNumber) {
    Term const base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, 2);

    termRaiseToTerms.simplify();

    EXPECT_EQ(
        Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}),
        termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_EQ(
        Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}),
        termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentsResultsInAnMultiplicationExpression) {
    Term const base("base");
    Term const absoluteValueOfA(abs("a"));
    Term const absoluteValueOfB(abs("b"));
    Terms const exponents{absoluteValueOfA, absoluteValueOfB};
    TermRaiseToTerms termRaiseToTerms(base, exponents);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    Term const expectedExponent(createExpressionIfPossible({absoluteValueOfA, "*", absoluteValueOfB}));
    TermsWithDetails const expectedExponents{TermWithDetails(expectedExponent, TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term const expectedCombinedTerm(createExpressionIfPossible({base, "^", expectedExponent}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWhenExponentsResultsInAnAdditionExpression) {
    Term const base("base");
    Term const exponent(createExpressionIfPossible({abs("a"), "+", abs("b")}));
    TermRaiseToTerms termRaiseToTerms(base, {exponent});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term("base"), termRaiseToTerms.getBase());
    TermsWithDetails const expectedExponents{TermWithDetails(exponent, TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term const expectedCombinedTerm(createExpressionIfPossible({base, "^", exponent}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithReducingExponentialToLogarithmic) {
    Term const polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term const base(getEAsATerm());
    Term const exponent(ln(polynomialTerm));
    TermRaiseToTerms termRaiseToTerms(base, exponent);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    Term const& expectedCombinedTerm(polynomialTerm);
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithReducingExponentialToLogarithmicWithMultipleExponents) {
    Term const polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term const base(getEAsATerm());
    Term const exponent(ln(polynomialTerm));
    TermRaiseToTerms termRaiseToTerms(base, {2, exponent});

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails const expectedExponents{TermWithDetails(Term(2), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
    Term const expectedCombinedTerm(
        createExpressionIfPossible({Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", 2}));
    EXPECT_EQ(expectedCombinedTerm, termRaiseToTerms.getCombinedTerm());
}

TEST(TermRaiseToTermsTest, SimplifyWorksWithNegativeNumberRaiseToInfinity) {
    Term const base(-1);
    Term const exponent(ALBA_NUMBER_POSITIVE_INFINITY);
    TermRaiseToTerms termRaiseToTerms(base, exponent);

    termRaiseToTerms.simplify();

    EXPECT_TRUE(isNan(termRaiseToTerms.getBase()));
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
    EXPECT_TRUE(isNan(termRaiseToTerms.getCombinedTerm()));
}

TEST(TermRaiseToTermsTest, GetCombinedExponentsWorks) {
    TermRaiseToTerms const termRaiseToTerms("base", {"exponent1", "exponent2"});

    Term const expectedTerm(Monomial(1, {{"exponent1", 1}, {"exponent2", 1}}));
    EXPECT_EQ(expectedTerm, termRaiseToTerms.getCombinedExponents());
}

TEST(TermRaiseToTermsTest, ConstructionWithTermsWithDetailsWorks) {
    TermsWithDetails termsInRaiseToPowerExpression;
    termsInRaiseToPowerExpression.emplace_back(Term("x"), TermAssociationType::Positive);
    termsInRaiseToPowerExpression.emplace_back(Term("y"), TermAssociationType::Positive);
    TermRaiseToTerms const termRaiseToTerms(termsInRaiseToPowerExpression);

    TermsWithDetails const expectedExponents{TermWithDetails(Term("y"), TermAssociationType::Positive)};
    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, ConstructionWithBaseAndExponentsWorks) {
    Term const base("x");
    Terms const exponents{"y"};
    TermRaiseToTerms const termRaiseToTerms(base, exponents);

    EXPECT_EQ(base, termRaiseToTerms.getBase());
    TermsWithDetails const expectedExponents{TermWithDetails(Term("y"), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, ConstructionWithBaseAndExponentWorks) {
    Term const base("x");
    Term const exponent("y");
    TermRaiseToTerms const termRaiseToTerms(base, exponent);

    EXPECT_EQ(base, termRaiseToTerms.getBase());
    TermsWithDetails const expectedExponents{TermWithDetails(exponent, TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, ConstructionWithNoArgumentWorks) {
    TermRaiseToTerms const termRaiseToTerms;

    EXPECT_TRUE(termRaiseToTerms.getBase().isEmpty());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
}

TEST(TermRaiseToTermsTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorks) {
    Term const base(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    TermRaiseToTerms termRaiseToTerms(base, "x");
    termRaiseToTerms.setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), termRaiseToTerms.getBase());
    TermsWithDetails const expectedExponents{
        TermWithDetails(Term(Monomial(2, {{"x", 1}})), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorks) {
    Term const base(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Terms const exponents{4, AlbaNumber::createFraction(1, 2)};
    TermRaiseToTerms termRaiseToTerms(base, exponents);
    termRaiseToTerms.setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(true);

    termRaiseToTerms.simplify();

    EXPECT_EQ(Term(abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})})), termRaiseToTerms.getBase());
    TermsWithDetails const expectedExponents{TermWithDetails(Term(2), TermAssociationType::Positive)};
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, DoesEvenExponentCancellationHappenWorks) {
    TermRaiseToTerms const termRaiseToTerms1("base", {3, 5});
    TermRaiseToTerms const termRaiseToTerms2("base", {3, AlbaNumber::createFraction(1, 3)});
    TermRaiseToTerms const termRaiseToTerms3(
        "base", {AlbaNumber::createFraction(4, 3), AlbaNumber::createFraction(1, 3)});
    TermRaiseToTerms const termRaiseToTerms4(
        "base", {AlbaNumber::createFraction(1, 3), AlbaNumber::createFraction(1, 6)});
    TermRaiseToTerms const termRaiseToTerms5(
        "base", {AlbaNumber::createFraction(4, 3), AlbaNumber::createFraction(1, 6)});

    EXPECT_FALSE(termRaiseToTerms1.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms2.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms3.doesEvenExponentCancellationHappen());
    EXPECT_FALSE(termRaiseToTerms4.doesEvenExponentCancellationHappen());
    EXPECT_TRUE(termRaiseToTerms5.doesEvenExponentCancellationHappen());
}

}  // namespace alba::algebra
