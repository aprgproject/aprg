#include <UniqueProblems/DynamicProgramming/Math/NumberTheory/FibonacciProblems/CountNumberOfBinaryStringsWithoutConsecutiveOnes.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample1) {
    CountNumberOfBinaryStringsWithoutConsecutiveOnes const queryForTest(1);

    EXPECT_EQ(2, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(2, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(2, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(2, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample2) {
    CountNumberOfBinaryStringsWithoutConsecutiveOnes const queryForTest(2);

    EXPECT_EQ(3, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(3, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(3, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(3, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample3) {
    CountNumberOfBinaryStringsWithoutConsecutiveOnes const queryForTest(3);

    EXPECT_EQ(5, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(5, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(5, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(5, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample4) {
    CountNumberOfBinaryStringsWithoutConsecutiveOnes const queryForTest(10);

    EXPECT_EQ(144, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(144, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(144, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(144, queryForTest.getCountUsingFibonacci());
}

}  // namespace alba
