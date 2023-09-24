#include <Algebra/Solution/Solver/NewtonMethod.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba::algebra {

TEST(NewtonMethodTest, GetCurrentValueWorks) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod const newtonMethod(5, functionToIterate);

    EXPECT_EQ(AlbaNumber(5), newtonMethod.getCurrentValue());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedWorksWhenMaxIterationIsReached) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(4);

    EXPECT_EQ(AlbaNumber(4.0022575248056222463), newtonMethod.getCurrentValue());
    EXPECT_EQ(4, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedWorksWhenMaxIterationIsNotReached) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(100);

    EXPECT_EQ(AlbaNumber(4), newtonMethod.getCurrentValue());
    EXPECT_EQ(6, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedWorksForXToXForm) {
    // NOLINTNEXTLINE(misc-redundant-expression)
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ number) - 256; };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(100);

    EXPECT_EQ(AlbaNumber(4), newtonMethod.getCurrentValue());
    EXPECT_EQ(44, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedWorks) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runUntilFinished();

    EXPECT_EQ(AlbaNumber(4), newtonMethod.getCurrentValue());
    EXPECT_EQ(6, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, RunOneIterationWorks) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runOneIteration();

    EXPECT_EQ(AlbaNumber(8.5000000043790038262), newtonMethod.getCurrentValue());
}

TEST(NewtonMethodTest, ConstructionWorks) {
    NewtonMethod(16, [](AlbaNumber const& number) { return (number ^ 2) - 16; });
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedFailsToGetSolutionWithXToXForm) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) {
        // NOLINTNEXTLINE(misc-redundant-expression)
        return (number ^ number) + 823543;
    };
    NewtonMethod newtonMethod(-16, functionToIterate);

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(100);

    EXPECT_TRUE(newtonMethod.getCurrentValue().isNotANumber());
    EXPECT_EQ(1, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, GetNumberOfIterationsExecutedWorksWhenNoIterationsAreExecuted) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod const newtonMethod(5, functionToIterate);

    EXPECT_EQ(0, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, GetNumberOfIterationsExecutedWorksWhenOneIterationIsExecuted) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod newtonMethod(5, functionToIterate);
    newtonMethod.runOneIteration();

    EXPECT_EQ(1, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, IsSolvedWorks) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod const newtonMethod1(4, functionToIterate);
    NewtonMethod const newtonMethod2(16, functionToIterate);

    EXPECT_TRUE(newtonMethod1.isSolved());
    EXPECT_FALSE(newtonMethod2.isSolved());
}

TEST(NewtonMethodTest, IsFinishedWorks) {
    NewtonMethod::Function const functionToIterate = [](AlbaNumber const& number) { return (number ^ 2) - 16; };
    NewtonMethod const newtonMethod1(4, functionToIterate);
    NewtonMethod const newtonMethod2(16, functionToIterate);
    NewtonMethod const newtonMethod3(ALBA_NUMBER_POSITIVE_INFINITY, functionToIterate);

    EXPECT_TRUE(newtonMethod1.isFinished());
    EXPECT_FALSE(newtonMethod2.isFinished());
    EXPECT_TRUE(newtonMethod3.isFinished());
}

}  // namespace alba::algebra
