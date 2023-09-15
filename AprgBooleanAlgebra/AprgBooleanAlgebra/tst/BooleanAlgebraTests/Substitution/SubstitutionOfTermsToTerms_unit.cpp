#include <BooleanAlgebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionForExpressionWorks) {
    SubstitutionOfTermsToTerms const substitution({{"x", "a"}, {"y", true}});
    Expression const expression(createExpressionIfPossible({"x", "&", "y"}));

    Expression const verifyExpression(substitution.performSubstitutionForExpression(expression));

    Expression const expectExpression(createExpressionIfPossible({"a", "&", true}));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfTermsToTermsTest, GetTermForTermWorks) {
    SubstitutionOfTermsToTerms const substitution({{"x", false}, {"y", true}});

    EXPECT_EQ(Term(false), substitution.getTermForTerm("x"));
    EXPECT_EQ(Term(true), substitution.getTermForTerm("y"));
    EXPECT_EQ(Term(), substitution.getTermForTerm("a"));
    EXPECT_EQ(Term(), substitution.getTermForTerm("b"));
}

TEST(SubstitutionOfTermsToTermsTest, ConstructionWorks) {
    SubstitutionOfTermsToTerms const substitution1;
    SubstitutionOfTermsToTerms const substitution2{{"x", false}, {"y", true}};
    TermToTermMap const variableWithValues{{"x", false}, {"y", true}};
    SubstitutionOfTermsToTerms const substitution3{variableWithValues};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(2, substitution2.getSize());
    EXPECT_EQ(Term(false), substitution2.getTermForTerm("x"));
    EXPECT_EQ(Term(true), substitution2.getTermForTerm("y"));
    EXPECT_EQ(2, substitution3.getSize());
    EXPECT_EQ(Term(false), substitution3.getTermForTerm("x"));
    EXPECT_EQ(Term(true), substitution3.getTermForTerm("y"));
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfTermsToTerms const substitution({{"x", false}, {"y", true}});
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({"x", "&", "y"}));

    Term const verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term const verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term const expectTerm1;
    Term const expectTerm2(false);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfTermsToTermsTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfTermsToTerms const substitution({{"x", false}, {"y", true}});
    Term const term1;
    Term const term2("x");
    Term const term3(createExpressionIfPossible({"x", "&", "y"}));
    Term const term4(true);

    Term const verifyTerm1(substitution.performSubstitutionTo(term1));
    Term const verifyTerm2(substitution.performSubstitutionTo(term2));
    Term const verifyTerm3(substitution.performSubstitutionTo(term3));
    Term const verifyTerm4(substitution.performSubstitutionTo(term4));

    Term const expectTerm1;
    Term const expectTerm2(false);
    Term const expectTerm3(false);
    Term const expectTerm4(true);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
}

TEST(SubstitutionOfTermsToTermsTest, GetSizeWorks) {
    SubstitutionOfTermsToTerms const substitution1;
    SubstitutionOfTermsToTerms const substitution2({{"x", false}, {"y", true}});

    EXPECT_EQ(0, substitution1.getSize());
    EXPECT_EQ(2, substitution2.getSize());
}

TEST(SubstitutionOfTermsToTermsTest, IsEmptyWorks) {
    SubstitutionOfTermsToTerms const substitution1;
    SubstitutionOfTermsToTerms const substitution2({{"x", false}, {"y", true}});

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfTermsToTermsTest, IsTermFoundWorks) {
    SubstitutionOfTermsToTerms const substitution({{"x", false}, {"y", true}});

    EXPECT_TRUE(substitution.isTermFound("x"));
    EXPECT_TRUE(substitution.isTermFound("y"));
    EXPECT_FALSE(substitution.isTermFound("a"));
    EXPECT_FALSE(substitution.isTermFound("b"));
}

}  // namespace alba::booleanAlgebra
