#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfTermsToTerms const substitution({{"x", 2}, {"y", 5}});
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({"x", "^", "y"}));

    Term const verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term const verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term const expectTerm1;
    Term const expectTerm2(32);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnFunction) {
    SubstitutionOfTermsToTerms const substitution({{"x", -2}});
    Function const function1;
    Function const function2(abs("x"));

    Term const verifyTerm1(substitution.performSubstitutionTo(function1));
    Term const verifyTerm2(substitution.performSubstitutionTo(function2));

    Term const expectTerm1(Function{});
    Term const expectTerm2(2);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfTermsToTerms const substitution({{"x", 2}, {"y", 5}});
    Term const term1;
    Term const term2("x");
    Term const term3(Monomial(7, {{"x", 3}}));
    Term const term4(Polynomial{
        Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}),
        Monomial(5, {{"x", 3}})});
    Term const term5(createExpressionIfPossible({"x", "^", "y"}));
    Term const term6(10);

    Term const verifyTerm1(substitution.performSubstitutionTo(term1));
    Term const verifyTerm2(substitution.performSubstitutionTo(term2));
    Term const verifyTerm3(substitution.performSubstitutionTo(term3));
    Term const verifyTerm4(substitution.performSubstitutionTo(term4));
    Term const verifyTerm5(substitution.performSubstitutionTo(term5));
    Term const verifyTerm6(substitution.performSubstitutionTo(term6));

    Term const expectTerm1;
    Term const expectTerm2(2);
    Term const& expectTerm3(term3);
    Term const& expectTerm4(term4);
    Term const expectTerm5(32);
    Term const expectTerm6(10);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionForExpressionWorks) {
    SubstitutionOfTermsToTerms const substitution({{"x", 2}, {"y", 5}});
    Expression const expression(createExpressionIfPossible({"x", "^", "y"}));

    Expression const verifyExpression(substitution.performSubstitutionForExpression(expression));

    Expression const expectExpression(createOrCopyExpressionFromATerm(32));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionForFunctionWorks) {
    SubstitutionOfTermsToTerms const substitution({{"x", 2}, {"y", 5}});
    Term const subTerm(createExpressionIfPossible({"x", "^", "y"}));
    Function const functionToTest(abs(subTerm));

    Function const verifyFunction(substitution.performSubstitutionForFunction(functionToTest));

    Function const expectExpression(abs(Term(32)));
    EXPECT_EQ(expectExpression, verifyFunction);
}

TEST(SubstitutionOfTermsToTermsTest, GetTermForTermWorks) {
    SubstitutionOfTermsToTerms const substitution({{"x", 2}, {"y", 5}});

    EXPECT_EQ(Term(2), substitution.getTermForTerm("x"));
    EXPECT_EQ(Term(5), substitution.getTermForTerm("y"));
    EXPECT_EQ(Term(), substitution.getTermForTerm("a"));
    EXPECT_EQ(Term(), substitution.getTermForTerm("b"));
}

TEST(SubstitutionOfTermsToTermsTest, ConstructionWorks) {
    SubstitutionOfTermsToTerms const substitution1;
    SubstitutionOfTermsToTerms const substitution2{{"x", 2}, {"y", 5}};
    TermToTermMap const variableWithValues{{"x", 2}, {"y", 5}};
    SubstitutionOfTermsToTerms const substitution3{variableWithValues};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(2, substitution2.getSize());
    EXPECT_EQ(Term(2), substitution2.getTermForTerm("x"));
    EXPECT_EQ(Term(5), substitution2.getTermForTerm("y"));
    EXPECT_EQ(2, substitution3.getSize());
    EXPECT_EQ(Term(2), substitution3.getTermForTerm("x"));
    EXPECT_EQ(Term(5), substitution3.getTermForTerm("y"));
}

TEST(SubstitutionOfTermsToTermsTest, GetSizeWorks) {
    SubstitutionOfTermsToTerms const substitution1;
    SubstitutionOfTermsToTerms const substitution2({{"x", 2}, {"y", 5}});

    EXPECT_EQ(0, substitution1.getSize());
    EXPECT_EQ(2, substitution2.getSize());
}

TEST(SubstitutionOfTermsToTermsTest, IsEmptyWorks) {
    SubstitutionOfTermsToTerms const substitution1;
    SubstitutionOfTermsToTerms const substitution2({{"x", 2}, {"y", 5}});

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfTermsToTermsTest, IsTermFoundWorks) {
    SubstitutionOfTermsToTerms const substitution({{"x", 2}, {"y", 5}});

    EXPECT_TRUE(substitution.isTermFound("x"));
    EXPECT_TRUE(substitution.isTermFound("y"));
    EXPECT_FALSE(substitution.isTermFound("a"));
    EXPECT_FALSE(substitution.isTermFound("b"));
}

}  // namespace alba::algebra
