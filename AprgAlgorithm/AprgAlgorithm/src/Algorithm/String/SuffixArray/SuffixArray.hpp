#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <string_view>

namespace alba::algorithm {

template <typename Index>
class SuffixArray {
public:
    using Indexes = std::vector<Index>;
    using StringViews = std::vector<std::string_view>;

    explicit SuffixArray(std::string const& mainString) : m_mainString(mainString), m_mainStringIndexes() {
        initialize();
    }

    explicit SuffixArray(std::string&& mainString) : m_mainString(mainString), m_mainStringIndexes() { initialize(); }

    [[nodiscard]] Index getSize() const { return m_mainStringIndexes.size(); }
    [[nodiscard]] Index getIndexOnMainStringOfSuffixAt(Index const index) const { return m_mainStringIndexes[index]; }

    [[nodiscard]] Index getRank(std::string_view const key) const {
        Index low = 0;
        Index high = getSize() - 1;
        while (low <= high) {
            Index mid = getMidpointOfIndexes(low, high);
            auto compareValue = key.compare(getSuffixViewAt(mid));
            if (compareValue < 0) {
                high = mid - 1;
            } else if (compareValue > 0) {
                low = mid + 1;
            } else {
                low = mid;
                break;
            }
        }
        return low;
    }

    [[nodiscard]] std::string getLongestCommonPrefixOfTwoSuffixes(Index const index1, Index const index2) const {
        return stringHelper::getLongestCommonPrefix(getSuffixViewAt(index1), getSuffixViewAt(index2));
    }

    [[nodiscard]] std::string_view getSuffixViewAt(Index const index) const {
        Index mainStringIndex = m_mainStringIndexes[index];
        return std::string_view(m_mainString.data() + mainStringIndex, m_mainStringIndexes.size() - mainStringIndex);
    }

private:
    void initialize() {
        Index length = m_mainString.length();
        StringViews suffixViews;
        suffixViews.reserve(length);
        auto suffixPointer = m_mainString.data();
        for (int suffixLength = length; suffixLength > 0; ++suffixPointer, --suffixLength) {
            suffixViews.emplace_back(suffixPointer, suffixLength);
        }
        std::sort(suffixViews.begin(), suffixViews.end());
        m_mainStringIndexes.reserve(length);
        for (auto const& suffixView : suffixViews) {
            m_mainStringIndexes.emplace_back(length - suffixView.length());
        }
    }

    std::string m_mainString;
    Indexes m_mainStringIndexes;
};

}  // namespace alba::algorithm

// Check Manber-Myers MSD is really efficient
