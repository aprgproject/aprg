#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba {

class LongestPalindromicSubstring {
public:
    using Index = int;
    using Indices = std::vector<Index>;
    using IndexMatrix = matrix::AlbaMatrix<Index>;
    using BoolMatrix = matrix::AlbaMatrix<bool>;
    explicit LongestPalindromicSubstring(std::string const& stringParameter);
    explicit LongestPalindromicSubstring(std::string&& stringParameter);
    static constexpr Index MAX_INDEX = std::numeric_limits<Index>::max();
    [[nodiscard]] Index getLongestLengthUsingNaiveRecursion() const;
    [[nodiscard]] Index getLongestLengthUsingMemoizationDP() const;
    [[nodiscard]] Index getLongestLengthUsingIterativeDP() const;
    [[nodiscard]] Index getLongestLengthUsingIterativeDPAndSpaceEfficient() const;
    [[nodiscard]] std::string getLongestStringUsingIterativeDPAndSpaceEfficient() const;

private:
    [[nodiscard]] Index getLongestLengthUsingNaiveRecursion(Index const left, Index const right) const;
    Index getLongestLengthUsingMemoizationDP(IndexMatrix& lengthMatrix, Index const left, Index const right) const;
    std::string m_string;
};

}  // namespace alba

// Given a string, find the longest substring which is palindrome.
// For example,
// -> Input: Given string :"forgeeksskeegfor",
// ---> Output: "geeksskeeg"
// -> Input: Given string :"Geeks",
// ---> Output: "ee"
