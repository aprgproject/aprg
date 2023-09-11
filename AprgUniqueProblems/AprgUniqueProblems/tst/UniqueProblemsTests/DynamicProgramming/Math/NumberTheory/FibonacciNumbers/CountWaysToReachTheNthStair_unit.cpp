#include <UniqueProblems/DynamicProgramming/Math/NumberTheory/FibonacciProblems/CountWaysToReachTheNthStair.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountWaysToReachTheNthStairTest, GetCountWorksOnExample1) {
    CountWaysToReachTheNthStair const queryForTest(1);

    EXPECT_EQ(1, queryForTest.getCountUsingFibonacci());
}

TEST(CountWaysToReachTheNthStairTest, GetCountWorksOnExample2) {
    CountWaysToReachTheNthStair const queryForTest(2);

    EXPECT_EQ(2, queryForTest.getCountUsingFibonacci());
}

TEST(CountWaysToReachTheNthStairTest, GetCountWorksOnExample3) {
    CountWaysToReachTheNthStair const queryForTest(4);

    EXPECT_EQ(5, queryForTest.getCountUsingFibonacci());
}

TEST(CountWaysToReachTheNthStairTest, GetCountWorksOnExample4) {
    CountWaysToReachTheNthStair const queryForTest(10);

    EXPECT_EQ(89, queryForTest.getCountUsingFibonacci());
}

}  // namespace alba
