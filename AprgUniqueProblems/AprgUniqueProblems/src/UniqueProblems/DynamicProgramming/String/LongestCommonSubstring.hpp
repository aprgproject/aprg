#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <string>

namespace alba {

class LongestCommonSubstring {
public:
    using Index = int;
    using Count = int;
    using Counts = std::vector<Count>;
    using CountGrid = matrix::AlbaMatrix<Count>;
    LongestCommonSubstring(std::string const& string1, std::string const& string2);
    LongestCommonSubstring(std::string&& string1, std::string&& string2);
    static constexpr Index UNUSED_INDEX = std::numeric_limits<Index>::max();
    [[nodiscard]] Count getLongestCommonSubstringLengthUsingNaiveRecursion() const;
    [[nodiscard]] Count getLongestCommonSubstringLengthUsingMemoizationDP() const;
    [[nodiscard]] Count getLongestCommonSubstringLengthUsingIterativeDP() const;
    [[nodiscard]] Count getLongestCommonSubstringLengthUsingIterativeDPAndSpaceEfficient() const;
    [[nodiscard]] std::string getLongestCommonSubstringUsingIterativeDPAndSpaceEfficient() const;

private:
    [[nodiscard]] Count getLongestCommonSubstringLengthUsingNaiveRecursion(
        Index const index1, Index const index2) const;

    Count getLongestCommonSubstringLengthUsingMemoizationDP(
        CountGrid& lengthGrid, Index const index1, Index const index2) const;

    std::string m_string1;
    std::string m_string2;
};

}  // namespace alba

//
