#include <Expression.hpp>
#include <Term.hpp>
#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(ExpressionTest, ConstructionWorks)
{
    Expression();
}

TEST(ExpressionTest, GetWrappedTermsReferenceWorksCorrectly)
{
    Expression expression(createExpression(Terms{Term(5), Term("+"), Term("interest")}));
    BaseTermSharedPointers & baseTermPointersToVerify(expression.getWrappedTermsReference().getBaseTermPointersReference());

    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(5, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("+", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("interest", term3.getVariableConstReference().getVariableName());
}

TEST(ExpressionTest, GetWrappedTermsConstReferenceWorksCorrectly)
{
    Expression expression(createExpression(Terms{Term(6), Term("*"), Term("force")}));

    BaseTermSharedPointers const& baseTermPointersToVerify(expression.getWrappedTermsConstReference().getBaseTermPointersConstReference());

    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(6, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("*", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("force", term3.getVariableConstReference().getVariableName());
}

}

}
