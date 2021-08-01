#pragma once

#include <map>
#include <vector>

namespace alba
{

class LongestIncreasingSubsequence
{
public:
    using Length = unsigned int;
    using Value = unsigned int;
    using Sequence = std::vector<Value>;
    using LengthToIndexMap = std::multimap<Length, Length>;
    using Sequences = std::vector<Sequence>;

    LongestIncreasingSubsequence(Sequence const& sequenceToCheck);

    Length getLongestIncreasingSubsequenceLength();
    Sequence getLongestIncreasingSubsequence();
private:
    Sequence m_sequenceToCheck;

};

}

// A subsequence is a sequence of (not necessarily consecutive) characters in a string in their original order.
// A string of length n has 2n-1 subsequences.
// For example, the subsequences of ABCD are A, B, C, D, AB, AC, AD, BC, BD, CD, ABC, ABD, ACD, BCD and ABCD.


// Our first problem is to find the longest increasing subsequence in an array of n elements.
// This is a maximum-length sequence of array elements that goes from left to right,
// and each element in the sequence is larger than the previous element.

// Recurrence formulation:
// -> Let length(k) denote the length of the longest increasing subsequence that ends at position k.
// -> Thus, if we calculate all values of length(k) where 0<=k<=n-1, we will find out the length of the longest increasing subsequence.

// Other discussions:
// The Longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a given sequence
// such that all elements of the subsequence are sorted in increasing order.
// For example, the length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is {10, 22, 33, 50, 60, 80}.

//Examples:
// -> Input: arr[] = {3, 10, 2, 1, 20}
// ---> Output: Length of LIS = 3
// ---> The longest increasing subsequence is 3, 10, 20
// -> Input: arr[] = {3, 2}
// ---> Output: Length of LIS = 1
// ---> The longest increasing subsequences are {3} and {2}
// -> Input: arr[] = {50, 3, 10, 7, 40, 80}
// ---> Output: Length of LIS = 4
// ---> The longest increasing subsequence is {3, 7, 40, 80}

// So this problem has Overlapping Substructure property and recomputation of same subproblems
// can be avoided by either using Memoization or Tabulation.

// Complexity Analysis:
// Time Complexity: O(n2). As nested loop is used.
// Auxiliary Space: O(n). Use of any array to store LIS values at each index.
