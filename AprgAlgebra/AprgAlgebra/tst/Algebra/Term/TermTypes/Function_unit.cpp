#include <Algebra/Term/TermTypes/Function.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(FunctionTest, ConstructionWorks)
{
    Function();
    Function("functionName", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
}

TEST(FunctionTest, GetFunctionNameWorks)
{
    Function function1;
    Function function2("functionName", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_TRUE(function1.getFunctionName().empty());
    EXPECT_EQ("functionName", function2.getFunctionName());
}

TEST(FunctionTest, EqualityWorks)
{
    Function function1;
    Function function2("functionName1", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", createOrCopyExpressionFromATerm(Term(10)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_TRUE(function1==function1);
    EXPECT_FALSE(function1==function2);
    EXPECT_TRUE(function2==function2);
    EXPECT_FALSE(function2==function3);
    EXPECT_FALSE(function2==function4);
}

TEST(FunctionTest, InequalityOperatorWorks)
{
    Function function1;
    Function function2("functionName1", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", createOrCopyExpressionFromATerm(Term(10)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_FALSE(function1!=function1);
    EXPECT_TRUE(function1!=function2);
    EXPECT_FALSE(function2!=function2);
    EXPECT_TRUE(function2!=function3);
    EXPECT_TRUE(function2!=function4);
}

TEST(FunctionTest, LessThanOperatorWorks)
{
    Function function1;
    Function function2("functionName1", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", createOrCopyExpressionFromATerm(Term(10)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    EXPECT_FALSE(function1 < function1);
    EXPECT_FALSE(function2 < function2);
    EXPECT_TRUE(function1 < function2);
    EXPECT_TRUE(function2 < function3);
    EXPECT_TRUE(function3 < function4);
}

TEST(FunctionTest, IsInputExpressionAConstantWorks)
{
    Function function1;
    Function function2("functionName", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName", createOrCopyExpressionFromATerm(Term("x")), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_FALSE(function1.isInputExpressionAConstant());
    EXPECT_TRUE(function2.isInputExpressionAConstant());
    EXPECT_FALSE(function3.isInputExpressionAConstant());
}

TEST(FunctionTest, PerformFunctionAndReturnResultIfPossibleWorks)
{
    Function function1;
    Function function2("functionName", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName", createOrCopyExpressionFromATerm(Term("x")), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ(Constant(), function1.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ(Constant(5), function2.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ(Constant(), function3.performFunctionAndReturnResultIfPossible());
}

TEST(FunctionTest, GetInputExpressionConstReferenceWorks)
{
    Function function1;
    Function function2("functionName", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    Expression expressionToExpect1;
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(Term(5)));
    EXPECT_EQ(expressionToExpect1, function1.getInputExpressionConstReference());
    EXPECT_EQ(expressionToExpect2, function2.getInputExpressionConstReference());
}

TEST(FunctionTest, GetInputExpressionReferenceWorks)
{
    Function function1;
    Function function2("functionName", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    Expression expressionToExpect1;
    Expression expressionToExpect2(createOrCopyExpressionFromATerm(Term(5)));
    EXPECT_EQ(expressionToExpect1, function1.getInputExpressionReference());
    EXPECT_EQ(expressionToExpect2, function2.getInputExpressionReference());
}

TEST(FunctionTest, SimplifyWorks)
{
    Function function1("functionName", createExpressionIfPossible({Term(5), Term("+"), Term(5)}), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    function1.simplify();

    Expression expressionToExpect1(createOrCopyExpressionFromATerm(Term(10)));
    EXPECT_EQ(expressionToExpect1, function1.getInputExpressionReference());
}

TEST(FunctionTest, GetDisplayableStringWorks)
{
    Function function1("functionName", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ("functionName(5)", function1.getDisplayableString());
}

TEST(FunctionTest, GetDebugStringWorks)
{
    Function function1("functionName", createOrCopyExpressionFromATerm(Term(5)), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ("functionName( {?}||5{Constant}{POS} )", function1.getDebugString());
}

}

}
