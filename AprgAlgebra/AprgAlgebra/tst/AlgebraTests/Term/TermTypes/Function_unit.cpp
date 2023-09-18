#include <Algebra/Term/TermTypes/Function.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(FunctionTest, EqualityWorks) {
    Function const function1;
    Function const function2("functionName1", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function3("functionName2", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function4("functionName2", Term(10), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    EXPECT_TRUE(function1 == function1);
    EXPECT_FALSE(function1 == function2);
    EXPECT_TRUE(function2 == function2);
    EXPECT_FALSE(function2 == function3);
    EXPECT_FALSE(function2 == function4);
}

TEST(FunctionTest, InequalityOperatorWorks) {
    Function const function1;
    Function const function2("functionName1", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function3("functionName2", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function4("functionName2", Term(10), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    EXPECT_FALSE(function1 != function1);
    EXPECT_TRUE(function1 != function2);
    EXPECT_FALSE(function2 != function2);
    EXPECT_TRUE(function2 != function3);
    EXPECT_TRUE(function2 != function4);
}

TEST(FunctionTest, LessThanOperatorWorks) {
    Function const function1;
    Function const function2("functionName1", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function3("functionName2", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function4("functionName2", Term(10), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    EXPECT_FALSE(function1 < function1);
    EXPECT_FALSE(function2 < function2);
    EXPECT_TRUE(function1 < function2);
    EXPECT_TRUE(function2 < function3);
    EXPECT_TRUE(function3 < function4);
}

TEST(FunctionTest, OutputStreamOperatorWorks) {
    stringstream ss;
    Function const functionObject(
        "functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    ss << functionObject;

    EXPECT_EQ("functionName(5)", ss.str());
}

TEST(FunctionTest, PerformFunctionAndReturnResultIfPossibleWorks) {
    Function const function1;
    Function const function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Function const function3("functionName", Term("x"), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    EXPECT_EQ(AlbaNumber(), function1.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ(AlbaNumber(5), function2.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ(AlbaNumber(), function3.performFunctionAndReturnResultIfPossible());
}

TEST(FunctionTest, ConstructionWorks) {
    Function const function1;
    Function const function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    EXPECT_TRUE(function1.getFunctionName().empty());
    EXPECT_EQ(Term(), getTermConstReferenceFromBaseTerm(function1.getInputTerm()));
    EXPECT_EQ(AlbaNumber(), function1.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ("functionName", function2.getFunctionName());
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(function2.getInputTerm()));
    EXPECT_EQ(AlbaNumber(5), function2.performFunctionAndReturnResultIfPossible());
}

TEST(FunctionTest, SimplifyWorks) {
    Function::EvaluationFunction const evaluationFunction = [](AlbaNumber const& number) -> AlbaNumber {
        return number;
    };
    Function functionObject("functionName", Term(createExpressionIfPossible({5, "+", 5})), evaluationFunction);

    functionObject.simplify();

    EXPECT_EQ("functionName", functionObject.getFunctionName());
    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
    Function::EvaluationFunction const& evaluationFunctionToVerify(functionObject.getEvaluationFunction());
    EXPECT_EQ(AlbaNumber(100), evaluationFunctionToVerify(100));
}

TEST(FunctionTest, SimplifyWorksWhenIsSimplifiedIsNotSet) {
    Function::EvaluationFunction const evaluationFunction = [](AlbaNumber const& number) -> AlbaNumber {
        return number;
    };
    Function functionObject("functionName", Term(createExpressionIfPossible({5, "+", 5})), evaluationFunction);

    functionObject.simplify();

    EXPECT_EQ("functionName", functionObject.getFunctionName());
    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
    Function::EvaluationFunction const& evaluationFunctionToVerify(functionObject.getEvaluationFunction());
    EXPECT_EQ(AlbaNumber(100), evaluationFunctionToVerify(100));
}

TEST(FunctionTest, SimplifyWorksAsSkippedWhenIsSimplifiedIsSet) {
    Function::EvaluationFunction const evaluationFunction = [](AlbaNumber const& number) -> AlbaNumber {
        return number;
    };
    Function functionObject("functionName", Term(createExpressionIfPossible({5, "+", 5})), evaluationFunction);
    functionObject.setAsSimplified();

    functionObject.simplify();

    Term const inputTermToExpect(createExpressionIfPossible({5, "+", 5}));
    EXPECT_EQ("functionName", functionObject.getFunctionName());
    EXPECT_EQ(inputTermToExpect, getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
    Function::EvaluationFunction const& evaluationFunctionToVerify(functionObject.getEvaluationFunction());
    EXPECT_EQ(AlbaNumber(100), evaluationFunctionToVerify(100));
}

TEST(FunctionTest, GetEvaluationFunctionWorks) {
    Function::EvaluationFunction const evaluationFunction = [](AlbaNumber const& number) -> AlbaNumber {
        return number;
    };
    Function const functionObject("functionName", Term(5), evaluationFunction);

    Function::EvaluationFunction const& evaluationFunctionToVerify(functionObject.getEvaluationFunction());
    EXPECT_EQ(AlbaNumber(100), evaluationFunctionToVerify(100));
}

TEST(FunctionTest, GetInputTermWorks) {
    Function const function1;
    Function const function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    EXPECT_EQ(Term(), getTermConstReferenceFromBaseTerm(function1.getInputTerm()));
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(function2.getInputTerm()));
}

TEST(FunctionTest, ClearAllInnerSimplifiedFlagsWorks) {
    Term inputTerm;
    inputTerm.setAsSimplified();
    Function functionObject("functionName1", inputTerm, [](AlbaNumber const& number) -> AlbaNumber { return number; });
    functionObject.setAsSimplified();
    EXPECT_TRUE(functionObject.isSimplified());
    EXPECT_TRUE(getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()).isSimplified());

    functionObject.clearAllInnerSimplifiedFlags();

    EXPECT_FALSE(functionObject.isSimplified());
    EXPECT_FALSE(getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()).isSimplified());
}

TEST(FunctionTest, GetInputTermReferenceWorks) {
    Function functionObject;

    Term& inputTermToChange(getTermReferenceFromBaseTerm(functionObject.getInputTermReference()));
    inputTermToChange = Term(10);

    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
}

TEST(FunctionTest, GetFunctionNameWorks) {
    Function const function1;
    Function const function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    EXPECT_TRUE(function1.getFunctionName().empty());
    EXPECT_EQ("functionName", function2.getFunctionName());
}

TEST(FunctionTest, GetDebugStringWorks) {
    Function const functionObject(
        "functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });

    EXPECT_EQ("functionName(5{Constant})", functionObject.getDebugString());
}

TEST(FunctionTest, FunctionThatIsDefaultConstructedHasIsSimplifiedFlagNotSet) {
    Function const function;

    EXPECT_FALSE(function.isSimplified());
}

TEST(FunctionTest, FunctionThatIsCopyConstructedHasIsSimplifiedFlagCopied) {
    Function const functionWithSimplifiedNotSet;
    Function functionWithSimplifiedSet;
    functionWithSimplifiedSet.setAsSimplified();

    EXPECT_FALSE(functionWithSimplifiedNotSet.isSimplified());
    EXPECT_TRUE(functionWithSimplifiedSet.isSimplified());
}

TEST(FunctionTest, IsSimplifiedWorks) {
    Function const function1;
    Function function2;
    function2.setAsSimplified();

    EXPECT_FALSE(function1.isSimplified());
    EXPECT_TRUE(function2.isSimplified());
}

TEST(FunctionTest, SetAsSimplifiedWorks) {
    Function functionObject;

    functionObject.setAsSimplified();

    EXPECT_TRUE(functionObject.isSimplified());
}

TEST(FunctionTest, ClearSimplifiedFlagWorks) {
    Function functionObject;
    functionObject.setAsSimplified();

    functionObject.clearSimplifiedFlag();

    EXPECT_FALSE(functionObject.isSimplified());
}

}  // namespace alba::algebra
