#pragma once

#include <CodeUtilities/Common/Index.hpp>
#include <CodeUtilities/Common/Pattern.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::CodeUtilities {

class CPlusPlusReorganizeItems {
public:
    struct SortItem {
        int headerIndex;
        int score;
        int numberOfLines;
        bool isDivider;
        bool isAccessControl;
        bool isCommentOrWhiteSpace;
        int itemsIndex;
    };
    using SortItems = std::vector<SortItem>;

    CPlusPlusReorganizeItems(
        stringHelper::strings const& items, stringHelper::strings const& scopeNames,
        stringHelper::strings const& headerSignatures);
    CPlusPlusReorganizeItems(
        stringHelper::strings&& items, stringHelper::strings&& scopeNames, stringHelper::strings&& headerSignatures);
    [[nodiscard]] Terms getSortedAggregateTerms() const;

private:
    [[nodiscard]] SortItems getSortedItems() const;
    [[nodiscard]] SortItems getSortItems() const;
    static void sortByComparingItems(SortItems& sortItems);
    void saveDetailsFromItemContent(SortItem& sortItem, std::string const& item) const;
    void saveDetailsFromHeaderSignatures(SortItem& sortItem, std::string const& item) const;
    void putAdditionalDetailsOnCommentsAndWhiteSpace(SortItems& sortItems) const;
    [[nodiscard]] static Patterns getSearchPatterns();
    [[nodiscard]] bool processAndShouldStop(
        Terms& terms, int& termIndex, SortItem& sortItem, Indexes const& hitIndexes) const;
    static void moveToEndParenthesis(Terms const& terms, int& termIndex, int const parenthesisIndex);
    int getBestHeaderIndex(std::string const& item) const;
    [[nodiscard]] static std::string getIdentifierBeforeParenthesis(Terms const& terms, int const parenthesisIndex);
    [[nodiscard]] static int getTotalNumberLines(SortItems const& sortItems);
    [[nodiscard]] static bool hasMultilineItem(SortItems const& sortItems);
    [[nodiscard]] static bool isMultiLine(int const numberOfLines);
    stringHelper::strings m_items;
    stringHelper::strings m_scopeNames;
    stringHelper::strings m_headerSignatures;
};

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2);

}  // namespace alba::CodeUtilities
