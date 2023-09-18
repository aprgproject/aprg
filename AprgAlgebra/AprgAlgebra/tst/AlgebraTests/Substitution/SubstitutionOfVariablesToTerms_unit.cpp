#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnVariable) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
    Variable const variable1;
    Variable const variable2("x");
    Variable const variable3("y");

    Term const verifyTerm1(substitution.performSubstitutionTo(variable1));
    Term const verifyTerm2(substitution.performSubstitutionTo(variable2));
    Term const verifyTerm3(substitution.performSubstitutionTo(variable3));

    Term const expectTerm1(Variable{});
    Term const expectTerm2("y");
    Term const expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnMonomial) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
    Monomial const monomial1;
    Monomial const monomial2(7, {{"x", 3}});
    Monomial const monomial3(11, {{"x", 3}, {"y", 4}});

    Term const verifyTerm1(substitution.performSubstitutionTo(monomial1));
    Term const verifyTerm2(substitution.performSubstitutionTo(monomial2));
    Term const verifyTerm3(substitution.performSubstitutionTo(monomial3));

    Term const expectTerm1(0);
    Term const expectTerm2(Monomial(7, {{"y", 3}}));
    Term const expectTerm3(Monomial(11, {{"y", 7}}));
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnPolynomial) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
    Polynomial const polynomial1;
    Polynomial const polynomial2{
        Monomial(100, {}), Monomial(5, {{"x", 5}, {"y", 3}}), Monomial(9, {{"x", 8}}), Monomial(10, {})};
    Polynomial const polynomial3{
        Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}),
        Monomial(5, {{"x", 3}})};
    Polynomial const polynomial4{
        Monomial(-2, {{"x", 3}}), Monomial(-3, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(-5, {})};

    Term const verifyTerm1(substitution.performSubstitutionTo(polynomial1));
    Term const verifyTerm2(substitution.performSubstitutionTo(polynomial2));
    Term const verifyTerm3(substitution.performSubstitutionTo(polynomial3));
    Term const verifyTerm4(substitution.performSubstitutionTo(polynomial4));

    Term const expectTerm1;
    Term const expectTerm2(Polynomial{Monomial(14, {{"y", 8}}), Monomial(110, {})});
    Term const expectTerm3(Monomial(8, {{"y", 3}}));
    Term const expectTerm4(
        Polynomial{Monomial(-2, {{"y", 3}}), Monomial(-3, {{"y", 2}}), Monomial(-4, {{"y", 1}}), Monomial(-5, {})});
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({"x", "^", "y"}));

    Term const verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term const verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term const expectTerm1;
    Expression const expressionToExpect(createExpressionIfPossible({"y", "^", "y"}));
    Term const expectTerm2(expressionToExpect);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnFunction) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
    Function const function1;
    Function const function2(abs("x"));

    Term const verifyTerm1(substitution.performSubstitutionTo(function1));
    Term const verifyTerm2(substitution.performSubstitutionTo(function2));

    Function const functionToExpect(abs("y"));
    Term const expectTerm1(Function{});
    Term const expectTerm2(functionToExpect);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfVariablesToTerms const substitution({{"x", "y"}});
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
    Term const expectTerm2("y");
    Term const expectTerm3(Monomial(7, {{"y", 3}}));
    Term const expectTerm4(Monomial(8, {{"y", 3}}));
    Expression const expressionToExpect(createExpressionIfPossible({"y", "^", "y"}));
    Term const expectTerm5(expressionToExpect);
    Term const expectTerm6(10);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfVariablesToTermsTest, VariableToPolynomialSubstitutionWorks) {
    SubstitutionOfVariablesToTerms const substitution({{"x", Polynomial{Monomial(1, {{"y", 2}}), Monomial(1, {})}}});
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
    Term const expectTerm2(Polynomial{Monomial(1, {{"y", 2}}), Monomial(1, {})});
    Term const expectTerm3(
        Polynomial{Monomial(7, {{"y", 6}}), Monomial(21, {{"y", 4}}), Monomial(21, {{"y", 2}}), Monomial(7, {})});
    Term const expectTerm4(Polynomial{
        Monomial(5, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(16, {{"y", 4}}), Monomial(3, {{"y", 3}}),
        Monomial(16, {{"y", 2}}), Monomial(1, {{"y", 1}}), Monomial(5, {})});
    Expression const expressionToExpect(createExpressionIfPossible({expectTerm2, "^", "y"}));
    Term const expectTerm5(expressionToExpect);
    Term const expectTerm6(10);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionForMonomialWorks) {
    SubstitutionOfVariablesToTerms const substitution({{"x", 2}, {"y", 5}});
    Monomial const monomial(5, {{"x", 2}, {"y", 3}});

    Expression const verifyExpression(substitution.performSubstitutionForMonomial(monomial));

    Expression const expectExpression(createOrCopyExpressionFromATerm(2500));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionForPolynomialWorks) {
    SubstitutionOfVariablesToTerms const substitution({{"x", 2}, {"y", 5}});
    Polynomial const polynomial{Monomial(5, {{"x", 2}, {"y", 3}}), Monomial(7, {{"x", 3}, {"y", 4}})};

    Expression const verifyExpression(substitution.performSubstitutionForPolynomial(polynomial));

    Expression const expectExpression(createOrCopyExpressionFromATerm(37500));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionForExpressionWorks) {
    SubstitutionOfVariablesToTerms const substitution({{"x", 2}, {"y", 5}});
    Expression const expression(createExpressionIfPossible({"x", "^", "y"}));

    Expression const verifyExpression(substitution.performSubstitutionForExpression(expression));

    Expression const expectExpression(createOrCopyExpressionFromATerm(32));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionForFunctionWorks) {
    SubstitutionOfVariablesToTerms const substitution({{"x", 2}, {"y", 5}});
    Term const subTerm(createExpressionIfPossible({"x", "^", "y"}));
    Function const functionToTest(abs(subTerm));

    Function const verifyFunction(substitution.performSubstitutionForFunction(functionToTest));

    Function const expectExpression(abs(Term(32)));
    EXPECT_EQ(expectExpression, verifyFunction);
}

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

}  // namespace alba::algebra
