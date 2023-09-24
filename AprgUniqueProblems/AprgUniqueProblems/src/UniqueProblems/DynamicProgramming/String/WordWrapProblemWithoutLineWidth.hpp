#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <limits>
#include <string>

namespace alba {

class WordWrapProblemWithoutLineWidth {
public:
    using Index = int;
    using Cost = int;
    using Indices = std::vector<Index>;
    using Costs = std::vector<Cost>;

    struct RecursionDetails {
        Index maxLength;
        Indices lengths;
    };

    explicit WordWrapProblemWithoutLineWidth(stringHelper::strings const& words);
    explicit WordWrapProblemWithoutLineWidth(stringHelper::strings&& words);
    static constexpr Cost MAX_COST = std::numeric_limits<Cost>::max();
    [[nodiscard]] Cost getOptimizedCostUsingNaiveRecursion() const;
    [[nodiscard]] Cost getOptimizedCostByTryingAllLengths() const;

private:
    [[nodiscard]] Cost getOptimizedCostUsingNaiveRecursion(
        RecursionDetails const& recursionDetails, Index const wordIndex) const;

    [[nodiscard]] Cost getTotalLength() const;
    static Cost getCost(Index const maxLength, Indices const& lengths);
    static Cost getCostFromExtraSpaces(Index const numberOfExtraSpaces);
    stringHelper::strings m_words;
};

}  // namespace alba

// Given a sequence of words put line breaks in the given sequence such that the lines are printed neatly.
// Assume that the length of each word is smaller than the line width.
