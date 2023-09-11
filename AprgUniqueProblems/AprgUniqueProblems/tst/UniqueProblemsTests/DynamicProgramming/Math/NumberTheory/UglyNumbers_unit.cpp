#include <UniqueProblems/DynamicProgramming/Math/NumberTheory/UglyNumbers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(UglyNumbersTest, GetNthUglyNumberOnExample1) {
    UglyNumbers const queryForTest(0);

    EXPECT_EQ(0, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(0, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample2) {
    UglyNumbers const queryForTest(1);

    EXPECT_EQ(1, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(1, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample3) {
    UglyNumbers const queryForTest(7);

    EXPECT_EQ(8, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(8, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample4) {
    UglyNumbers const queryForTest(15);

    EXPECT_EQ(24, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(24, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample5) {
    UglyNumbers const queryForTest(150);

    EXPECT_EQ(5832, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(5832, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

}  // namespace alba
