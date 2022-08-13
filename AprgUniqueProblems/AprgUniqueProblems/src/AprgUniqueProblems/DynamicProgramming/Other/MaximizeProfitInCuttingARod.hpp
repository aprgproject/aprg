#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba {

class MaximizeProfitInCuttingARod {
public:
    using Index = int;
    using Length = int;
    using Profit = int;
    using RodIndex = int;
    using Rod = std::pair<Length, Profit>;
    using Profits = std::vector<Profit>;
    using Rods = std::vector<Rod>;    using ProfitMatrix = matrix::AlbaMatrix<Profit>;
    static constexpr Profit UNUSED_PROFIT = std::numeric_limits<Profit>::max();

    MaximizeProfitInCuttingARod(Length const length, Rods const rods);

    Profit getBestProfitUsingNaiveRecursion() const;
    Profit getBestProfitUsingMemoizationDP() const;
    Profit getBestProfitUsingIterativeDP() const;

private:
    Profit getBestProfitUsingNaiveRecursion(Length const remainingLength) const;
    Profit getBestProfitUsingMemoizationDP(Profits& partialProfits, Length const remainingLength) const;
    Length getSmallestItemLength() const;
    Length const m_length;
    Rods const m_rods;
};

}  // namespace alba

// Given a rod of length n inches and an array of prices that includes prices of all pieces of size smaller than n.
// Determine the maximum value obtainable by cutting up the rod and selling the pieces.

// NOTE: This is almost the same with "MaximizeProfitInKnapsack"

// For example, if the length of the rod is 8 and the values of different pieces are given as the following,
// then the maximum obtainable value is 22 (by cutting in two pieces of lengths 2 and 6)
// length   | 1   2   3   4   5   6   7   8
// price    | 1   5   8   9  10  17  17  20

// And if the prices are as following, then the maximum obtainable value is 24 (by cutting in eight pieces of length 1)
// length   | 1   2   3   4   5   6   7   8
// price    | 3   5   8   9  10  17  17  20

// A naive solution to this problem is to generate all configurations of different pieces and find the highest-priced
// configuration. This solution is exponential in terms of time complexity. A naive solution to this problem is to
// generate all configurations of different pieces and find the highest-priced configuration. This solution is
// exponential in terms of time complexity.

// 1) Optimal Substructure:
// We can get the best price by making a cut at different positions and comparing the values obtained after a cut.
// We can recursively call the same function for a piece obtained after a cut.
// Let cutRod(n) be the required (best possible price) value for a rod of length n. cutRod(n) can be written as follows.
// cutRod(n) = max(price[i] + cutRod(n-i-1)) for all i in {0, 1 .. n-1}
