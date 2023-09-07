#pragma once

#include <CodeUtilities/Common/Index.hpp>
#include <CodeUtilities/Common/Pattern.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::CodeUtilities {

class CPlusPlusReorganizeItems {
public:
    struct SortItem {
        int headerItemPosition;
        int score;
        bool isDivider;
        bool addNewLineAtEnd;
        int itemsIndex;
    };
    using SortItems = std::vector<SortItem>;

    CPlusPlusReorganizeItems(
        stringHelper::strings const& scopeNames, stringHelper::strings const& items,
        stringHelper::strings const& headerItems);
    CPlusPlusReorganizeItems(
        stringHelper::strings&& scopeNames, stringHelper::strings&& items, stringHelper::strings&& headerItems);
    [[nodiscard]] Terms getSortedAggregateTerms() const;

private:
    [[nodiscard]] SortItems getSortedItems() const;
    [[nodiscard]] SortItems getSortItems() const;
    static void sortByComparingItems(SortItems& sortItems);
    void saveDetailsFromHeaderItemPosition(SortItem& sortItem, std::string const& item) const;
    void saveDetailsFromItemContent(SortItem& sortItem, std::string const& item) const;
    [[nodiscard]] static Patterns getSearchPatterns();
    [[nodiscard]] bool processAndShouldStop(
        Terms& terms, int& termIndex, SortItem& sortItem, Indexes const& hitIndexes) const;
    static void moveToEndParenthesis(Terms const& terms, int& termIndex, int const parenthesisIndex);
    [[nodiscard]] static std::string getIdentifierBeforeParenthesis(Terms const& terms, int const parenthesisIndex);
    //[[nodiscard]] static std::string getFunctionSignature(std::string const& item);
    stringHelper::strings m_scopeNames;
    stringHelper::strings m_items;
    stringHelper::strings m_headerItems;
};

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2);

}  // namespace alba::CodeUtilities
