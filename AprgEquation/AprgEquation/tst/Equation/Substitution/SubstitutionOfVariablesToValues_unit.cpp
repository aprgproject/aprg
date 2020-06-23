#include <Equation/Substitution/SubstitutionOfVariablesToValues.hpp>

#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(SubstitutionOfVariablesToValuesTest, ConstructionWorks)
{
    SubstitutionOfVariablesToValues substitution1({{"x", 1}, {"y", 2}});
    VariablesToValuesMap variableWithValues{{"x", 1}, {"y", 2}};
    SubstitutionOfVariablesToValues substitution2(variableWithValues);
}

TEST(SubstitutionOfVariablesToValuesTest, IsVariableFoundWorks)
{
    SubstitutionOfVariablesToValues substitution({{"x", 1}, {"y", 2}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_TRUE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, GetValueForVariableWorks)
{
    SubstitutionOfVariablesToValues substitution({{"x", 1}, {"y", 2}});

    EXPECT_EQ(AlbaNumber(1), substitution.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(2), substitution.getValueForVariable("y"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("a"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnVariable)
{
    SubstitutionOfVariablesToValues substitution({{"x", 2}});
    Variable variable1;
    Variable variable2("x");
    Variable variable3("y");

    Term verifyTerm1(substitution.performSubstitutionTo(variable1));
    Term verifyTerm2(substitution.performSubstitutionTo(variable2));
    Term verifyTerm3(substitution.performSubstitutionTo(variable3));

    Term expectTerm1(Variable(""));
    Term expectTerm2(2);
    Term expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnMonomial)
{
    SubstitutionOfVariablesToValues substitution({{"x", 2}});
    Monomial monomial1;
    Monomial monomial2(7, {{"x", 3}});
    Monomial monomial3(11, {{"x", 3}, {"y", 4}});

    Term verifyTerm1(substitution.performSubstitutionTo(monomial1));
    Term verifyTerm2(substitution.performSubstitutionTo(monomial2));
    Term verifyTerm3(substitution.performSubstitutionTo(monomial3));

    Term expectTerm1(Constant(0));
    Term expectTerm2(56);
    Term expectTerm3(Monomial(88, {{"y", 4}}));
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnPolynomial)
{
    SubstitutionOfVariablesToValues substitution({{"x", 2}, {"y", 5}});
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(100, {}), Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(10, {})};
    Polynomial polynomial3{Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 3}})};

    Term verifyTerm1(substitution.performSubstitutionTo(polynomial1));
    Term verifyTerm2(substitution.performSubstitutionTo(polynomial2));
    Term verifyTerm3(substitution.performSubstitutionTo(polynomial3));

    Term expectTerm1(Constant(0));
    Term expectTerm2(Polynomial{Monomial(2500, {{"z", 4}}), Monomial(2414, {})});
    Term expectTerm3(235);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnExpression)
{
    SubstitutionOfVariablesToValues substitution({{"x", 2}, {"y", 5}});
    Expression expression1;
    Expression expression2(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));

    Term verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term expectTerm1;
    Term expectTerm2(32);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnTerm)
{
    SubstitutionOfVariablesToValues substitution({{"x", 2}, {"y", 5}});
    Term term1;
    Term term2("x");
    Term term3(Monomial(7, {{"x", 3}}));
    Term term4(Polynomial{Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 3}})});
    Term term5(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));

    Term verifyTerm1(substitution.performSubstitutionTo(term1));
    Term verifyTerm2(substitution.performSubstitutionTo(term2));
    Term verifyTerm3(substitution.performSubstitutionTo(term3));
    Term verifyTerm4(substitution.performSubstitutionTo(term4));
    Term verifyTerm5(substitution.performSubstitutionTo(term5));

    Term expectTerm1;
    Term expectTerm2(2);
    Term expectTerm3(56);
    Term expectTerm4(235);
    Term expectTerm5(32);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
}

}

}
