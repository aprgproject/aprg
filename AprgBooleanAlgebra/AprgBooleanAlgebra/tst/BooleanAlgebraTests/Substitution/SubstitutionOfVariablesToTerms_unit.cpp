#include <BooleanAlgebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(SubstitutionOfVariablesToTermsTest, GetValueForVariableWorks) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});

    Term const termToExpect("y");
    EXPECT_EQ(termToExpect, substitution.getTermForVariable("x"));
    EXPECT_EQ(Term{}, substitution.getTermForVariable("y"));
    EXPECT_EQ(Term{}, substitution.getTermForVariable("a"));
    EXPECT_EQ(Term{}, substitution.getTermForVariable("b"));
}

TEST(SubstitutionOfVariablesToTermsTest, ConstructionWorks) {
    SubstitutionOfVariablesToTerms const substitution1;
    SubstitutionOfVariablesToTerms const substitution2{{"x", "y"}};
    VariablesToTermsMap const variableWithExpressions{{"x", "y"}};
    SubstitutionOfVariablesToTerms const substitution3{variableWithExpressions};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(1, substitution2.getSize());
    EXPECT_EQ(Term("y"), substitution2.getTermForVariable("x"));
    EXPECT_EQ(1, substitution3.getSize());
    EXPECT_EQ(Term("y"), substitution3.getTermForVariable("x"));
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnVariableTerm) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
    VariableTerm const variableTerm1;
    VariableTerm const variableTerm2("x");
    VariableTerm const variableTerm3("y");

    Term const verifyTerm1(substitution.performSubstitutionTo(variableTerm1));
    Term const verifyTerm2(substitution.performSubstitutionTo(variableTerm2));
    Term const verifyTerm3(substitution.performSubstitutionTo(variableTerm3));

    Term const expectTerm1(VariableTerm{});
    Term const expectTerm2("y");
    Term const expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({"x", "&", "y"}));

    Term const verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term const verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term const expectTerm1;
    Term const expectTerm2("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
    Term const term1;
    Term const term2("x");
    Term const term3(createExpressionIfPossible({"x", "&", "y"}));
    Term const term4(true);

    Term const verifyTerm1(substitution.performSubstitutionTo(term1));
    Term const verifyTerm2(substitution.performSubstitutionTo(term2));
    Term const verifyTerm3(substitution.performSubstitutionTo(term3));
    Term const verifyTerm4(substitution.performSubstitutionTo(term4));

    Term const expectTerm1;
    Term const expectTerm2("y");
    Term const expectTerm3("y");
    Term const expectTerm4(true);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
}

TEST(SubstitutionOfVariablesToTermsTest, VariableToExpressionSubstitutionWorks) {
    SubstitutionOfVariablesToTerms const substitution({{"x", createExpressionIfPossible({"a", "&", "b"})}});
    Term const term1;
    Term const term2("x");
    Term const term3(createExpressionIfPossible({"x", "&", "y"}));
    Term const term4(true);

    Term const verifyTerm1(substitution.performSubstitutionTo(term1));
    Term const verifyTerm2(substitution.performSubstitutionTo(term2));
    Term const verifyTerm3(substitution.performSubstitutionTo(term3));
    Term const verifyTerm4(substitution.performSubstitutionTo(term4));

    Term const expectTerm1;
    Term const expectTerm2(createExpressionIfPossible({"a", "&", "b"}));
    Term const expectTerm3(createExpressionIfPossible({"a", "&", "b", "&", "y"}));
    Term const expectTerm4(true);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
}

TEST(SubstitutionOfVariablesToTermsTest, GetSizeWorks) {
    SubstitutionOfVariablesToTerms const substitution1;
    SubstitutionOfVariablesToTerms const substitution2({{"x", "y"}});

    EXPECT_EQ(0, substitution1.getSize());
    EXPECT_EQ(1, substitution2.getSize());
}

TEST(SubstitutionOfVariablesToTermsTest, IsEmptyWorks) {
    SubstitutionOfVariablesToTerms const substitution1;
    SubstitutionOfVariablesToTerms const substitution2({{"x", "y"}});

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfVariablesToTermsTest, IsVariableFoundWorks) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_FALSE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

}  // namespace alba::booleanAlgebra
