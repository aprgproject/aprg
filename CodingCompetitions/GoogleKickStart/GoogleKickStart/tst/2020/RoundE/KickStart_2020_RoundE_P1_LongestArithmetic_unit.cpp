#include "KickStart_2020_RoundE_P1_LongestArithmetic.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2020_RoundE_P1_LongestArithmetic {

TEST(KickStart2020RoundEP1LongestArithmeticTest, DISABLED_Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "4                  "
                         "\n"
                      << "7                  "
                         "\n"
                      << "10 7 4 6 8 10 11   "
                         "\n"
                      << "4                  "
                         "\n"
                      << "9 7 5 3            "
                         "\n"
                      << "9                  "
                         "\n"
                      << "5 5 4 5 5 5 4 5 6  "
                         "\n"
                      << "10                 "
                         "\n"
                      << "5 4 3 2 1 2 3 4 5 6"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 4"
        "\n"
        "Case #2: 4"
        "\n"
        "Case #3: 3"
        "\n"
        "Case #4: 6"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2020_RoundE_P1_LongestArithmetic

/*
Problem

An arithmetic array is an array that contains at least two integers and the differences between consecutive integers are
equal. For example, [9, 10], [3, 3, 3], and [9, 7, 5, 3] are arithmetic arrays, while [1, 3, 3, 7], [2, 1, 2], and [1,
2, 4] are not arithmetic arrays.

Sarasvati has an array of N non-negative integers. The i-th integer of the array is Ai. She wants to choose a contiguous
arithmetic subarray from her array that has the maximum length. Please help her to determine the length of the longest
contiguous arithmetic subarray. Input

The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line
containing the integer N. The second line contains N integers. The i-th integer is Ai. Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is
the length of the longest contiguous arithmetic subarray. Limits

Time limit: 20 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
0 ≤ Ai ≤ 109.
Test Set 1

2 ≤ N ≤ 2000.
Test Set 2

2 ≤ N ≤ 2 × 105 for at most 10 test cases.
For the remaining cases, 2 ≤ N ≤ 2000.
Sample

Input

Output


4
7
10 7 4 6 8 10 11
4
9 7 5 3
9
5 5 4 5 5 5 4 5 6
10
5 4 3 2 1 2 3 4 5 6





Case #1: 4
Case #2: 4
Case #3: 3
Case #4: 6



In Sample Case #1, the integers inside the bracket in the following represent the longest contiguous arithmetic
subarray: 10 7 [4 6 8 10] 11

In Sample Case #2, the whole array is an arithmetic array, thus the longest contiguous arithmetic subarray is the whole
array.

In Sample Case #3, the longest contiguous arithmetic subarray is either [5, 5, 5] (a subarray from the fourth integer to
the sixth integer) or [4, 5, 6] (a subarray from the seventh integer to the ninth integer).

In Sample Case #4, the longest contiguous arithmetic subarray is the last six integers.
*/
