#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

TEST(SubstitutionOfVariablesToValuesTest, GetValueForVariableWorks) {
    SubstitutionOfVariablesToValues const substitution({{"x", 1}, {"y", 2}});

    EXPECT_EQ(AlbaNumber(1), substitution.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(2), substitution.getValueForVariable("y"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("a"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, ConstructionWorks) {
    SubstitutionOfVariablesToValues const substitution1;
    SubstitutionOfVariablesToValues const substitution2{{"x", 1}, {"y", 2}};
    VariablesToValuesMap const variableWithValues{{"x", 1}, {"y", 2}};
    SubstitutionOfVariablesToValues const substitution3{variableWithValues};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(2, substitution2.getSize());
    EXPECT_EQ(AlbaNumber(1), substitution2.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(2), substitution2.getValueForVariable("y"));
    EXPECT_EQ(2, substitution3.getSize());
    EXPECT_EQ(AlbaNumber(1), substitution3.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(2), substitution2.getValueForVariable("y"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValuesWorksUsingInitializerList) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariablesWithValues({{"x", 1}, {"y", 2}});

    EXPECT_EQ(AlbaNumber(1), substitution.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(2), substitution.getValueForVariable("y"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("a"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValuesWorksUsingMap) {
    SubstitutionOfVariablesToValues substitution;
    VariablesToValuesMap variablesWithValues;
    variablesWithValues.emplace("x", 1);
    variablesWithValues.emplace("y", 2);

    substitution.putVariablesWithValues(variablesWithValues);

    EXPECT_EQ(AlbaNumber(1), substitution.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(2), substitution.getValueForVariable("y"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("a"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValueWorks) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariableWithValue("x", 5);

    EXPECT_EQ(AlbaNumber(5), substitution.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("a"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValueWorksWithSavingTheLastValue) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariableWithValue("x", 5);
    substitution.putVariableWithValue("x", 29);

    EXPECT_EQ(AlbaNumber(29), substitution.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("a"));
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnVariable) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}});
    Variable const variable1;
    Variable const variable2("x");
    Variable const variable3("y");

    Term const verifyTerm1(substitution.performSubstitutionTo(variable1));
    Term const verifyTerm2(substitution.performSubstitutionTo(variable2));
    Term const verifyTerm3(substitution.performSubstitutionTo(variable3));

    Term const expectTerm1(Variable{});
    Term const expectTerm2(2);
    Term const expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnMonomial) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}});
    Monomial const monomial1;
    Monomial const monomial2(7, {{"x", 3}});
    Monomial const monomial3(11, {{"x", 3}, {"y", 4}});

    Term const verifyTerm1(substitution.performSubstitutionTo(monomial1));
    Term const verifyTerm2(substitution.performSubstitutionTo(monomial2));
    Term const verifyTerm3(substitution.performSubstitutionTo(monomial3));

    Term const expectTerm1(0);
    Term const expectTerm2(56);
    Term const expectTerm3(Monomial(88, {{"y", 4}}));
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnPolynomial) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}, {"y", 5}});
    Polynomial const polynomial1;
    Polynomial const polynomial2{
        Monomial(100, {}), Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(10, {})};
    Polynomial const polynomial3{
        Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}),
        Monomial(5, {{"x", 3}})};

    Term const verifyTerm1(substitution.performSubstitutionTo(polynomial1));
    Term const verifyTerm2(substitution.performSubstitutionTo(polynomial2));
    Term const verifyTerm3(substitution.performSubstitutionTo(polynomial3));

    Term const expectTerm1(0);
    Term const expectTerm2(Polynomial{Monomial(2500, {{"z", 4}}), Monomial(2414, {})});
    Term const expectTerm3(235);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}, {"y", 5}});
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({"x", "^", "y"}));

    Term const verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term const verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term const expectTerm1;
    Term const expectTerm2(32);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnFunction) {
    SubstitutionOfVariablesToValues const substitution({{"x", -2}});
    Function const function1;
    Function const function2(abs("x"));

    Term const verifyTerm1(substitution.performSubstitutionTo(function1));
    Term const verifyTerm2(substitution.performSubstitutionTo(function2));

    Term const expectTerm1(Function{});
    Term const expectTerm2(2);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}, {"y", 5}});
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
    Term const expectTerm3(56);
    Term const expectTerm4(235);
    Term const expectTerm5(32);
    Term const expectTerm6(10);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionForExpressionWorks) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}, {"y", 5}});
    Expression const expression(createExpressionIfPossible({"x", "^", "y"}));

    Expression const verifyExpression(substitution.performSubstitutionForExpression(expression));

    Expression const expectExpression(createOrCopyExpressionFromATerm(32));
    EXPECT_EQ(expectExpression, verifyExpression);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionForFunctionWorks) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}, {"y", 5}});
    Term const subTerm(createExpressionIfPossible({"x", "^", "y"}));
    Function const functionToTest(abs(subTerm));

    Function const verifyFunction(substitution.performSubstitutionForFunction(functionToTest));

    Function const expectExpression(abs(Term(32)));
    EXPECT_EQ(expectExpression, verifyFunction);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionForMonomialWorks) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}, {"y", 5}});
    Monomial const monomial(5, {{"x", 2}, {"y", 3}});

    Monomial const verifyMonomial(substitution.performSubstitutionForMonomial(monomial));

    Monomial const expectMonomial(createMonomialFromNumber(2500));
    EXPECT_EQ(expectMonomial, verifyMonomial);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionForPolynomialWorks) {
    SubstitutionOfVariablesToValues const substitution({{"x", 2}, {"y", 5}});
    Polynomial const polynomial{Monomial(5, {{"x", 2}, {"y", 3}}), Monomial(7, {{"x", 3}, {"y", 4}})};

    Polynomial const verifyPolynomial(substitution.performSubstitutionForPolynomial(polynomial));

    Polynomial const expectPolynomial(createPolynomialFromNumber(37500));
    EXPECT_EQ(expectPolynomial, verifyPolynomial);
}

TEST(SubstitutionOfVariablesToValuesTest, GetSizeWorks) {
    SubstitutionOfVariablesToValues const substitution1;
    SubstitutionOfVariablesToValues const substitution2({{"x", 1}, {"y", 2}});

    EXPECT_EQ(0, substitution1.getSize());
    EXPECT_EQ(2, substitution2.getSize());
}

TEST(SubstitutionOfVariablesToValuesTest, IsEmptyWorks) {
    SubstitutionOfVariablesToValues const substitution1;
    SubstitutionOfVariablesToValues const substitution2({{"x", 1}, {"y", 2}});

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfVariablesToValuesTest, IsVariableFoundWorks) {
    SubstitutionOfVariablesToValues const substitution({{"x", 1}, {"y", 2}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_TRUE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

}  // namespace alba::algebra
