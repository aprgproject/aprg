#pragma once

#include <vector>

namespace alba {

class GreedyAlgorithmForFewestCoins {
public:
    using Coin = int;
    using Coins = std::vector<Coin>;
    using Value = int;
    explicit GreedyAlgorithmForFewestCoins(Coins const& availableCoins);
    explicit GreedyAlgorithmForFewestCoins(Coins&& availableCoins);
    [[nodiscard]] int getFewestNumberOfCoins(Value const value) const;

private:
    void initialize();
    Coins m_sortedAvailableCoins;
};

}  // namespace alba

// This is a variant of Fractional Knapsack Problem
// Given a value V, if we want to make a change for V Rs, and we have an infinite supply of each of the denominations in
// Indian currency, i.e., we have an infinite supply of { 1, 2, 5, 10, 20, 50, 100, 500, 1000} valued coins/notes, what
// is the minimum number of coins and/or notes needed to make the change?
// Examples:
// -> Input: V = 70
// ---> Output: 2
// ---> We need a 50 Rs note and a 20 Rs note.
// -> Input: V = 121
// ---> Output: 3
// ---> We need a 100 Rs note, a 20 Rs note and a 1 Rs coin.
// Solution: Greedy Approach.
// Approach: A common intuition would be to take coins with greater value first.
// -> This can reduce the total number of coins needed.
// -> Start from the largest possible denomination and keep adding denominations while the remaining value is greater
// than 0.
// Algorithm:
// -> Sort the array of coins in decreasing order.
// -> Initialize result as empty.
// -> Find the largest denomination that is smaller than current amount.
// -> Add found denomination to result. Subtract value of found denomination from amount.
// -> If amount becomes 0, then print result.
// -> Else repeat steps 3 and 4 for new value of V.
// Complexity Analysis:
// -> Time Complexity: O(V).
// -> Auxiliary Space: O(V).
// Note: The above approach may not work for all denominations.
// For example, it doesn’t work for denominations {9, 6, 5, 1} and V = 11.
// The above approach would print 9, 1 and 1.
// But we can use 2 denominations 5 and 6.
