#include <BooleanAlgebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnVariableTerm) {
    SubstitutionOfVariablesToValues const substitution({{"x", true}});
    VariableTerm const variableTerm1;
    VariableTerm const variableTerm2("x");
    VariableTerm const variableTerm3("y");

    Term const verifyTerm1(substitution.performSubstitutionTo(variableTerm1));
    Term const verifyTerm2(substitution.performSubstitutionTo(variableTerm2));
    Term const verifyTerm3(substitution.performSubstitutionTo(variableTerm3));

    Term const expectTerm1(VariableTerm{});
    Term const expectTerm2(true);
    Term const expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfVariablesToValues const substitution({{"x", false}, {"y", true}});
    Expression const expression1;
    Expression const expression2(createExpressionIfPossible({"x", "&", "y"}));

    Term const verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term const verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term const expectTerm1;
    Term const expectTerm2(false);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfVariablesToValues const substitution({{"x", false}, {"y", true}});
    Term const term1;
    Term const term2("x");
    Term const term5(createExpressionIfPossible({"x", "&", "y"}));
    Term const term6(true);

    Term const verifyTerm1(substitution.performSubstitutionTo(term1));
    Term const verifyTerm2(substitution.performSubstitutionTo(term2));
    Term const verifyTerm5(substitution.performSubstitutionTo(term5));
    Term const verifyTerm6(substitution.performSubstitutionTo(term6));

    Term const expectTerm1;
    Term const expectTerm2(false);
    Term const expectTerm5(false);
    Term const expectTerm6(true);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfVariablesToValuesTest, GetSizeWorks) {
    SubstitutionOfVariablesToValues const substitution1;
    SubstitutionOfVariablesToValues const substitution2({{"x", false}, {"y", true}});

    EXPECT_EQ(0, substitution1.getSize());
    EXPECT_EQ(2, substitution2.getSize());
}

TEST(SubstitutionOfVariablesToValuesTest, ConstructionWorks) {
    SubstitutionOfVariablesToValues const substitution1;
    SubstitutionOfVariablesToValues const substitution2{{"x", false}, {"y", true}};
    VariablesToValuesMap const variableWithValues{{"x", false}, {"y", true}};
    SubstitutionOfVariablesToValues const substitution3{variableWithValues};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(2, substitution2.getSize());
    EXPECT_FALSE(substitution2.getValueForVariable("x"));
    EXPECT_TRUE(substitution2.getValueForVariable("y"));
    EXPECT_EQ(2, substitution3.getSize());
    EXPECT_FALSE(substitution3.getValueForVariable("x"));
    EXPECT_TRUE(substitution2.getValueForVariable("y"));
}

TEST(SubstitutionOfVariablesToValuesTest, IsEmptyWorks) {
    SubstitutionOfVariablesToValues const substitution1;
    SubstitutionOfVariablesToValues const substitution2({{"x", false}, {"y", true}});

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfVariablesToValuesTest, IsVariableFoundWorks) {
    SubstitutionOfVariablesToValues const substitution({{"x", false}, {"y", true}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_TRUE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, GetValueForVariableWorks) {
    SubstitutionOfVariablesToValues const substitution({{"x", false}, {"y", true}});

    EXPECT_FALSE(substitution.getValueForVariable("x"));
    EXPECT_TRUE(substitution.getValueForVariable("y"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
    EXPECT_FALSE(substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValuesWorksUsingInitializerList) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariablesWithValues({{"x", false}, {"y", true}});

    EXPECT_FALSE(substitution.getValueForVariable("x"));
    EXPECT_TRUE(substitution.getValueForVariable("y"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
    EXPECT_FALSE(substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValuesWorksUsingMap) {
    SubstitutionOfVariablesToValues substitution;
    VariablesToValuesMap variablesWithValues;
    variablesWithValues.emplace("x", false);
    variablesWithValues.emplace("y", true);

    substitution.putVariablesWithValues(variablesWithValues);

    EXPECT_FALSE(substitution.getValueForVariable("x"));
    EXPECT_TRUE(substitution.getValueForVariable("y"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
    EXPECT_FALSE(substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValueWorks) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariableWithValue("x", true);

    EXPECT_TRUE(substitution.getValueForVariable("x"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValueWorksWithSavingTheLastValue) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariableWithValue("x", true);
    substitution.putVariableWithValue("x", false);

    EXPECT_FALSE(substitution.getValueForVariable("x"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
}

}  // namespace alba::booleanAlgebra
