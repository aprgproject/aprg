#pragma once

#include <algorithm>
#include <set>
#include <vector>

namespace alba::algorithm {

template <typename Values>
class CombinationsWithSum {
public:
    using Value = typename Values::value_type;
    using Combination = std::multiset<Value>;
    using Combinations = std::set<Combination>;
    using VectorOfCombinations = std::vector<Combinations>;
    explicit CombinationsWithSum(Values const& values) : m_inputValues(values) {}

    Combinations getCombinationsWithSumUsingRecursion(Value const total) {
        // this recursion method is exponential
        if (total >= static_cast<Value>(m_combinations.size())) {
            auto&& [minIt, maxIt] = std::minmax_element(m_inputValues.cbegin(), m_inputValues.cend());
            int const newSize = std::max(total + 1, *maxIt);
            m_combinations.resize(newSize);
        }
        if (m_combinations[total].empty()) {
            for (Value const inputValue : m_inputValues) {
                if (total > inputValue) {
                    Combinations const subCombinations(getCombinationsWithSumUsingRecursion(total - inputValue));
                    for (Combination const& subcombination : subCombinations) {
                        Combination combination(subcombination);
                        combination.emplace(inputValue);
                        m_combinations[total].emplace(combination);
                    }
                } else if (total == inputValue) {
                    m_combinations[inputValue].emplace(Combination{{inputValue}});
                }
            }
        }
        return m_combinations[total];
    }

    Combinations getCombinationsWithSumUsingLoops(Value const total) {
        // using loops
        if (total >= static_cast<Value>(m_combinations.size())) {
            Value const initialValue = m_combinations.size();
            Value const newSize =
                std::max(total + 1, *(std::minmax_element(m_inputValues.cbegin(), m_inputValues.cend()).second));
            m_combinations.resize(newSize);

            for (Value const inputValue : m_inputValues) {
                if (m_combinations[inputValue].empty()) {
                    m_combinations[inputValue].emplace(Combination{inputValue});
                }
            }

            for (Value partialValue = initialValue; partialValue < newSize; ++partialValue) {
                // iterate to all values with no combination (partialValue)
                Combinations& combinations(m_combinations[partialValue]);
                for (Value const inputValue : m_inputValues) {
                    // check for each value if can be part of combination
                    if (partialValue > inputValue) {
                        for (Combination const& combinationWithoutValue :
                             m_combinations.at(partialValue - inputValue)) {
                            // check combinations in partialValue-inputValue
                            Combination combinationWithValue(combinationWithoutValue);
                            combinationWithValue.emplace(inputValue);
                            combinations.emplace(combinationWithValue);  // add this combination for this partial value
                        }
                    }
                }
            }
        }
        return m_combinations[total];
    }

private:
    Values const& m_inputValues;
    VectorOfCombinations m_combinations;  // dynamic programming
};

}  // namespace alba::algorithm
