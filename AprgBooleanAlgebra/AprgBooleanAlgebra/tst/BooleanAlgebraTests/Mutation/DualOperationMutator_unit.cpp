#include <BooleanAlgebra/Mutation/DualOperationMutator.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::booleanAlgebra {

TEST(DualOperationMutatorTest, MutateTermWorks) {
    DualOperationMutator mutator;
    Term term1(true);
    Term term2("a");
    Term term3(createExpressionIfPossible({"a", "&", "b"}));

    mutator.mutateTerm(term1);
    mutator.mutateTerm(term2);
    mutator.mutateTerm(term3);

    Term const termToExpect1(true);
    Term const termToExpect2("a");
    Term const termToExpect3(createExpressionIfPossible({"a", "|", "b"}));
    EXPECT_EQ(termToExpect1, term1);
    EXPECT_EQ(termToExpect2, term2);
    EXPECT_EQ(termToExpect3, term3);
}

TEST(DualOperationMutatorTest, MutateConstantWorks) {
    DualOperationMutator mutator;
    Constant constant(true);

    mutator.mutateConstant(constant);

    Constant const constantToExpect(true);
    EXPECT_EQ(constantToExpect, constant);
}

TEST(DualOperationMutatorTest, MutateVariableTermWorks) {
    DualOperationMutator mutator;
    VariableTerm variable("a");

    mutator.mutateVariableTerm(variable);

    VariableTerm const variableToExpect("a");
    EXPECT_EQ(variableToExpect, variable);
}

TEST(DualOperationMutatorTest, MutateExpressionWorks) {
    DualOperationMutator mutator;
    Expression expression(createExpressionIfPossible({"a", "&", "b", "|", "c"}));

    mutator.mutateExpression(expression);

    Expression const subExpression(createExpressionIfPossible({"a", "|", "b"}));
    Expression const expressionToExpect(createExpressionIfPossible({subExpression, "&", "c"}));
    EXPECT_EQ(expressionToExpect, expression);
}

}  // namespace alba::booleanAlgebra
