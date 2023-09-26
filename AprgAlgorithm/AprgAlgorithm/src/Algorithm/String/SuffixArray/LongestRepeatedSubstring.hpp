#pragma once

#include <Algorithm/String/SuffixArray/SuffixArray.hpp>

namespace alba::algorithm {

template <typename Index>
class LongestRepeatedSubstring {
public:
    LongestRepeatedSubstring() = delete;
    ~LongestRepeatedSubstring() = delete;
    LongestRepeatedSubstring(LongestRepeatedSubstring const &) = delete;
    LongestRepeatedSubstring(LongestRepeatedSubstring &&) noexcept = delete;
    LongestRepeatedSubstring &operator=(LongestRepeatedSubstring const &) = delete;
    LongestRepeatedSubstring &operator=(LongestRepeatedSubstring &&) noexcept = delete;

    static std::string getLongestRepeatedSubstring(std::string const &stringToCheck) {
        SuffixArray<Index> const suffixArray(stringToCheck);
        std::string result;
        Index length(stringToCheck.length());
        for (Index i = 1; i < length; ++i) {
            std::string const commonPrefix(suffixArray.getLongestCommonPrefixOfTwoSuffixes(i - 1, i));
            if (result.size() < commonPrefix.size()) {
                result = commonPrefix;
            }
        }
        return result;
    }
};

}  // namespace alba::algorithm
